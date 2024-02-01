#include "../Pages.h"
#include "../Utils.h"
#include <IndustryStandard/Acpi.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Protocol/Shell.h>
#include <Uefi.h>

PageItem signature = {
    .name = L"Signature",
    .moreInformation = L"Signature",
    .value = NULL,
    .page = NULL,
};

PageItem oemId = {
    .name = L"OEM ID",
    .moreInformation = L"OEM ID",
    .value = NULL,
    .page = NULL,
};

PageItem items = {
    .name = L"Items",
    .moreInformation = L"Items",
    .value = L"...",
    .page = NULL,
};

VOID MakeSubTables(PageItem *items, EFI_ACPI_DESCRIPTION_HEADER *table) {
  UINTN entryCount =
      (table->Length - sizeof(EFI_ACPI_DESCRIPTION_HEADER)) / sizeof(UINT64);

  if (entryCount == 0) {
    items->page = NULL;
    items->value = L"--";
    return;
  }

  if (items->page == NULL) {
    gBS->AllocatePool(EfiLoaderData, sizeof(Page), (VOID **)&items->page);
    SetMem(items->page, sizeof(Page), 0);
  }
  items->page->itemCount = entryCount;
  items->page->name = L"Subtable Items";
  items->page->Filler = NULL;
  PageItem **pageItems = items->page->pageItems;
  // Iterate over subtables
  for (UINTN i = 0; i < entryCount; i++) {
    UINT64 EntryAddress = ((UINT64 *)(table + 1))[i];
    EFI_ACPI_DESCRIPTION_HEADER *subtable =
        (EFI_ACPI_DESCRIPTION_HEADER *)(UINTN)EntryAddress;

    if (items->page->pageItems[i] == NULL) {
      gBS->AllocatePool(EfiLoaderData, sizeof(PageItem),
                        (VOID **)&(pageItems[i]));
      SetMem(pageItems[i], sizeof(PageItem), 0);
    }
    PageItem *pageItem = pageItems[i];

    if (pageItem->name == NULL) {
      gBS->AllocatePool(EfiLoaderData, MAX_NAME_LEN * sizeof(CHAR16),
                        (VOID **)&pageItem->name);
    }
    for (int j = 0; j < 4; j++) {
      pageItem->name[j] = ((CHAR8 *)&subtable->Signature)[j];
    }
    pageItem->name[4] = L'\0';
    pageItem->moreInformation =
        L"Item's name is subtable's signature and value is subtable's OEM ID";
    if (pageItem->value == NULL) {
      gBS->AllocatePool(EfiLoaderData, MAX_NAME_LEN * sizeof(CHAR16),
                        (VOID **)&pageItem->value);
      SetMem(pageItem->value, MAX_NAME_LEN * sizeof(CHAR16), 0);
    }
    for (int j = 0; j < 6; j++) {
      pageItem->value[j] = ((CHAR8 *)&subtable->OemId)[j];
    }
    pageItem->page = NULL;
  }
}

VOID FillAcpiPage() {
  EFI_ACPI_2_0_ROOT_SYSTEM_DESCRIPTION_POINTER *RSDP = NULL;

  for (UINTN i = 0; i < gST->NumberOfTableEntries; i++) {
    if (CompareGuid(&(gST->ConfigurationTable[i].VendorGuid),
                    &gEfiAcpi20TableGuid)) {
      RSDP = gST->ConfigurationTable[i].VendorTable;
      if (signature.value == NULL) {
        gBS->AllocatePool(EfiLoaderData, MAX_NAME_LEN * sizeof(CHAR16),
                          (VOID **)&signature.value);
      }
      for (int j = 0; j < 8; j++) {
        signature.value[j] = ((CHAR8 *)&RSDP->Signature)[j];
      }
      signature.value[8] = L'\0';

      if (oemId.value == NULL) {
        gBS->AllocatePool(EfiLoaderData, MAX_NAME_LEN * sizeof(CHAR16),
                          (VOID **)&oemId.value);
      }
      for (int j = 0; j < 6; j++) {
        oemId.value[j] = ((CHAR8 *)&RSDP->OemId)[j];
      }
      oemId.value[6] = L'\0';

      MakeSubTables(&items,
                    (EFI_ACPI_DESCRIPTION_HEADER *)(UINTN)RSDP->XsdtAddress);
      break;
    }
  }
}

Page acpiPage = {
    .name = L"ACPI Page",
    .itemCount = 3,
    .pageItems =
        {
            &signature,
            &oemId,
            &items,
        },
    .Filler = FillAcpiPage,
};