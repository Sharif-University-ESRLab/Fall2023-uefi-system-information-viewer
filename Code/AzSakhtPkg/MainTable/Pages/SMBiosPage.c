#include "../Pages.h"
#include "../Utils.h"
#include <IndustryStandard/SmBios.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Protocol/MmMp.h>
#include <Protocol/Smbios.h>
#include <Uefi.h>

#define CHECK_UPDATE                                                           \
  UpdateSmbiosProtocol();                                                      \
  if (SmbiosProtocol == NULL) {                                                \
    return;                                                                    \
  }

EFI_SMBIOS_PROTOCOL *SmbiosProtocol = NULL;

CHAR8 *GetRecordString(EFI_SMBIOS_TABLE_HEADER *Record, UINTN number) {
  if (!number)
    return "";

  CHAR8 *String = (CHAR8 *)Record + Record->Length;
  UINTN i = 1;
  while (i < number) {
    String = String + AsciiStrSize(String);
    i++;
  }
  return String;
}

VOID EFIAPI UpdateSmbiosProtocol() {
  if (SmbiosProtocol != NULL) {
    return;
  }

  EFI_STATUS Status = gBS->LocateProtocol(&gEfiSmbiosProtocolGuid, NULL,
                                          (VOID **)&SmbiosProtocol);
  if (EFI_ERROR(Status)) {
    Print(L"Error locating SMBIOS protocol: %r\n", Status);
    return;
  }
}

PageItem biosVersion = {
    .name = L"BIOS Version",
    .value = NULL,
    .moreInformation = L"Version number or identifier of the system's BIOS.",
    .page = NULL,
};

PageItem biosReleaseDate = {
    .name = L"BIOS Release Date",
    .value = NULL,
    .moreInformation = L"Release date of the system's BIOS.",
    .page = NULL,
};

PageItem manufacturer = {
    .name = L"Manufacturer",
    .value = NULL,
    .moreInformation = L"Manufacturer of the system",
    .page = NULL,
};

PageItem productName = {
    .name = L"Product Name",
    .value = NULL,
    .moreInformation = NULL,
    .page = NULL,
};

PageItem processorVersion = {
    .name = L"Processor Version",
    .value = NULL,
    .moreInformation = NULL,
    .page = NULL,
};

PageItem processorManufacturer = {
    .name = L"Processor Manufacturer",
    .value = NULL,
    .moreInformation = L"Manufacturer of Processor",
    .page = NULL,
};

PageItem processorMaxSpeed = {
    .name = L"Processor Max Speed",
    .value = NULL,
    .moreInformation = L"Maximum speed of the processor",
    .page = NULL,
};

PageItem memorySize = {
    .name = L"Memory size MB",
    .value = NULL,
    .moreInformation = L"Size of the memory",
    .page = NULL,
};

PageItem cacheSize = {
    .name = L"Cache size",
    .value = NULL,
    .moreInformation = L"Installed size of cache",
    .page = NULL,
};

PageItem coreCount = {
    .name = L"Core count",
    .value = NULL,
    .moreInformation = L"Core count",
    .page = NULL,
};

VOID FillSmbiosPage() {
  CHECK_UPDATE

  EFI_STATUS Status;
  EFI_SMBIOS_HANDLE SmbiosHandle = SMBIOS_HANDLE_PI_RESERVED;
  EFI_SMBIOS_TABLE_HEADER *Record;

  Status = SmbiosProtocol->GetNext(SmbiosProtocol, &SmbiosHandle, NULL, &Record,
                                   NULL);
  while (!EFI_ERROR(Status)) {
    switch (Record->Type) {
    case EFI_SMBIOS_TYPE_BIOS_INFORMATION: {
      SMBIOS_TABLE_TYPE0 *Type0Record = (SMBIOS_TABLE_TYPE0 *)Record;
      if (biosVersion.value == NULL) {
        gBS->AllocatePool(EfiLoaderData, MAX_NAME_LEN * sizeof(CHAR16),
                          (VOID **)&biosVersion.value);
      }
      AsciiStrToUnicodeStrS(GetRecordString(Record, Type0Record->BiosVersion),
                            biosVersion.value, MAX_NAME_LEN);
      if (biosReleaseDate.value == NULL) {
        gBS->AllocatePool(EfiLoaderData, MAX_NAME_LEN * sizeof(CHAR16),
                          (VOID **)&biosReleaseDate.value);
      }
      AsciiStrToUnicodeStrS(
          GetRecordString(Record, Type0Record->BiosReleaseDate),
          biosReleaseDate.value, MAX_NAME_LEN);
      break;
    }
    case EFI_SMBIOS_TYPE_SYSTEM_INFORMATION: {
      SMBIOS_TABLE_TYPE1 *Type1Record = (SMBIOS_TABLE_TYPE1 *)Record;
      if (manufacturer.value == NULL) {
        gBS->AllocatePool(EfiLoaderData, MAX_NAME_LEN * sizeof(CHAR16),
                          (VOID **)&manufacturer.value);
      }
      AsciiStrToUnicodeStrS(GetRecordString(Record, Type1Record->Manufacturer),
                            manufacturer.value, MAX_NAME_LEN);
      productName.value = L"...";
      if (productName.moreInformation == NULL) {
        gBS->AllocatePool(EfiLoaderData, MAX_DESCRIPTION_LEN * sizeof(CHAR16),
                          (VOID **)&productName.moreInformation);
      }
      AsciiStrToUnicodeStrS(GetRecordString(Record, Type1Record->ProductName),
                            productName.moreInformation, MAX_DESCRIPTION_LEN);
      break;
    }
    case EFI_SMBIOS_TYPE_PROCESSOR_INFORMATION: {
      SMBIOS_TABLE_TYPE4 *Type4Record = (SMBIOS_TABLE_TYPE4 *)Record;
      processorVersion.value = L"...";
      if (processorVersion.moreInformation == NULL) {
        gBS->AllocatePool(EfiLoaderData, MAX_DESCRIPTION_LEN * sizeof(CHAR16),
                          (VOID **)&processorVersion.moreInformation);
        SetMem(processorVersion.moreInformation, MAX_DESCRIPTION_LEN * sizeof(CHAR16), 0);
      }
      AsciiStrToUnicodeStrS(
          GetRecordString(Record, Type4Record->ProcessorVersion),
          processorVersion.moreInformation, MAX_DESCRIPTION_LEN);
      if (processorManufacturer.value == NULL) {
        gBS->AllocatePool(EfiLoaderData, MAX_NAME_LEN * sizeof(CHAR16),
                          (VOID **)&processorManufacturer.value);
      }
      AsciiStrToUnicodeStrS(
          GetRecordString(Record, Type4Record->ProcessorManufacturer),
          processorManufacturer.value, MAX_NAME_LEN);
      if (processorMaxSpeed.value == NULL) {
        gBS->AllocatePool(EfiLoaderData, MAX_NAME_LEN * sizeof(CHAR16),
                          (VOID **)&processorMaxSpeed.value);
      }
      Int2Str(Type4Record->MaxSpeed, processorMaxSpeed.value);
      if (coreCount.value == NULL) {
        gBS->AllocatePool(EfiLoaderData, MAX_NAME_LEN * sizeof(CHAR16),
                          (VOID **)&coreCount.value);
      }
      Int2Str(Type4Record->CoreCount, coreCount.value);
      break;
    }
    case EFI_SMBIOS_TYPE_CACHE_INFORMATION: {
      SMBIOS_TABLE_TYPE7 *Type7Record = (SMBIOS_TABLE_TYPE7 *)Record;
      if (cacheSize.value == NULL) {
        gBS->AllocatePool(EfiLoaderData, MAX_NAME_LEN * sizeof(CHAR16),
                          (VOID **)&cacheSize.value);
      }
      Int2Str(Type7Record->InstalledSize, cacheSize.value);
      break;
    }
    case EFI_SMBIOS_TYPE_MEMORY_DEVICE: {
      SMBIOS_TABLE_TYPE17 *Type17Record = (SMBIOS_TABLE_TYPE17 *)Record;
      if (memorySize.value == NULL) {
        gBS->AllocatePool(EfiLoaderData, MAX_NAME_LEN * sizeof(CHAR16),
                          (VOID **)&memorySize.value);
      }
      Int2Str(Type17Record->Size, memorySize.value);
      break;
    }
    }
    Status = SmbiosProtocol->GetNext(SmbiosProtocol, &SmbiosHandle, NULL,
                                     &Record, NULL);
  }
}

Page smbiosPage = {
    .name = L"System Management BIOS Page",
    .itemCount = 10,
    .pageItems =
        {
            &biosVersion,
            &biosReleaseDate,
            &manufacturer,
            &productName,
            &processorVersion,
            &processorManufacturer,
            &processorMaxSpeed,
            &coreCount,
            &memorySize,
            &cacheSize,
        },
    .Filler = FillSmbiosPage,
};