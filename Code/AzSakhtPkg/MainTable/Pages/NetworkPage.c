#include "../Pages.h"
#include "../Utils.h"
#include <IndustryStandard/Acpi.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Protocol/Shell.h>
#include <Protocol/SimpleNetwork.h>
#include <Uefi.h>

CHAR16 *NetworkInterfaceType(UINT8 type) {
  switch (type) {
  case 0:
    return L"--";
  case 1:
    return L"Other";
  case 2:
    return L"Ethernet";
  case 3:
    return L"TokenRing";
  case 4:
    return L"FDDI";
  case 5:
    return L"ATM";
  case 6:
    return L"Wireless";
  case 7:
    return L"InfiniBand";
  case 8:
    return L"Fabric";
  default:
    return L"Unknown";
  }
}

VOID MakeNetworkItem(PageItem *item, EFI_SIMPLE_NETWORK_PROTOCOL *snp) {
  if (item == NULL) {
    return;
  }
  item->name = L"Network Interface";
  item->moreInformation = L"Information of the network interface";
  item->value = L"";

  if (item->page == NULL) {
    gBS->AllocatePool(EfiLoaderData, sizeof(Page), (VOID **)&item->page);
    SetMem(item->page, sizeof(Page), 0);
  }
  item->page->name = L"Network Interface Info";
  item->page->Filler = NULL;

  PageItem state = {.name = L"State",
                    .moreInformation = L"Status of the network interface",
                    .value = L"Unknown",
                    .page = NULL};
  switch (snp->Mode->State) {
  case EfiSimpleNetworkStopped:
    state.value = L"Stopped";
    break;
  case EfiSimpleNetworkStarted:
    state.value = L"Started";
    break;
  case EfiSimpleNetworkInitialized:
    state.value = L"Initialized";
    break;
  case EfiSimpleNetworkMaxState:
    state.value = L"MaxState";
    break;
  default:
    break;
  }

  PageItem hwAddress = {.name = L"Hardware Address",
                        .moreInformation =
                            L"MAC address of the network interface",
                        .value = NULL,
                        .page = NULL};
  // format MAC address into value as a string
  UINT8 *mac = snp->Mode->CurrentAddress.Addr;
  UINTN macLength = snp->Mode->HwAddressSize;
  CHAR16 *temp;
  hwAddress.value = CatSPrint(NULL, L"%02X", mac[0]);
  for (UINTN i = 1; i < macLength; i++) {
    temp = CatSPrint(hwAddress.value, L":%02X", mac[i]);
    gBS->FreePool(hwAddress.value);
    hwAddress.value = temp;
  }
  Print(L" is the mac: %s\n", hwAddress.value);

  PageItem mediaState = {.name = L"Media State",
                         .moreInformation =
                             L"Media state of the network interface",
                         .value = L"Unknown",
                         .page = NULL};

  switch (snp->Mode->MediaPresent) {
  case TRUE:
    mediaState.value = L"Present";
    break;
  case FALSE:
    mediaState.value = L"Not Present";
    break;
  default:
    break;
  }

  PageItem interfaceType = {.name = L"Interface Type",
                            .moreInformation =
                                L"Interface type of the network interface",
                            .value = NetworkInterfaceType(snp->Mode->IfType),
                            .page = NULL};

  item->page->itemCount = 5;
  for (int i = 0; i < item->page->itemCount; i++) {
    if (item->page->pageItems[i] == NULL) {
      gBS->AllocatePool(EfiLoaderData, sizeof(PageItem),
                        (VOID **)&(item->page->pageItems[i]));
      SetMem(item->page->pageItems[i], sizeof(PageItem), 0);
    } else {
      if (i == 1) {
        gBS->FreePool(item->page->pageItems[i]->value);
      }
    }
  }
  CopyMem(item->page->pageItems[0], &state, sizeof(PageItem));
  CopyMem(item->page->pageItems[1], &hwAddress, sizeof(PageItem));
  CopyMem(item->page->pageItems[2], &mediaState, sizeof(PageItem));
  CopyMem(item->page->pageItems[3], &interfaceType, sizeof(PageItem));
  item->page->pageItems[4] = NULL;
}

VOID FillNetworkPage() {
  EFI_STATUS Status;
  UINTN HandleCount;
  EFI_HANDLE *HandleBuffer;
  EFI_SIMPLE_NETWORK_PROTOCOL *Snp;

  // Locate all handles that support the Simple Network Protocol
  Status = gBS->LocateHandleBuffer(ByProtocol, &gEfiSimpleNetworkProtocolGuid,
                                   NULL, &HandleCount, &HandleBuffer);

  if (EFI_ERROR(Status)) {
    Print(L"Failed to locate network interfaces\n");
    return;
  }

  // Iterate through all network interfaces
  networkPage.itemCount = HandleCount;
  for (UINTN i = 0; i < HandleCount; i++) {
    Status = gBS->HandleProtocol(HandleBuffer[i],
                                 &gEfiSimpleNetworkProtocolGuid, (VOID **)&Snp);

    if (!EFI_ERROR(Status)) {
      if (networkPage.pageItems[i] == NULL) {
        gBS->AllocatePool(EfiLoaderData, sizeof(PageItem),
                          (VOID **)&(networkPage.pageItems[i]));
        SetMem(networkPage.pageItems[i], sizeof(PageItem), 0);
      }
      MakeNetworkItem(networkPage.pageItems[i], Snp);
    }
  }

  // Free the handle buffer
  gBS->FreePool(HandleBuffer);
}

Page networkPage = {
    .name = L"Network Page",
    .itemCount = 0,
    .pageItems = {},
    .Filler = FillNetworkPage,
};
