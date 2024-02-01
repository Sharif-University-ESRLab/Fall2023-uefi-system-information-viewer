#include "../Pages.h"
#include "../Utils.h"
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Protocol/MmMp.h>
#include <Protocol/MpService.h>
#include <Uefi.h>

EFI_MP_SERVICES_PROTOCOL *MpService = NULL;

PageItem numberOfProcessors = {
    .name = L"Number of Processors",
    .value = NULL,
    .moreInformation = L"Number of Processors",
    .page = NULL,
};

PageItem numberOfEnabledProcessors = {
    .name = L"Number of Enabled Processors",
    .value = NULL,
    .moreInformation = L"Number of Enabled Processors",
    .page = NULL,
};

VOID FillProcessorPageTable() {
  EFI_STATUS Status = gBS->LocateProtocol(&gEfiMpServiceProtocolGuid, NULL,
                                          (VOID **)&MpService);
  if (EFI_ERROR(Status)) {
    Print(L"Failed to locate MP Service Protocol: %r\n", Status);
    return;
  }

  gBS->AllocatePool(EfiLoaderData, MAX_NAME_LEN * sizeof(CHAR16),
                    (VOID**) &numberOfProcessors.value);
  gBS->AllocatePool(EfiLoaderData, MAX_NAME_LEN * sizeof(CHAR16),
                    (VOID**) &numberOfEnabledProcessors.value);

  UINTN NumberOfProcessors;
  UINTN NumberOfEnabledProcessors;
  MpService->GetNumberOfProcessors(MpService, &NumberOfProcessors,
                                   &NumberOfEnabledProcessors);

  Int2Str(NumberOfProcessors, numberOfProcessors.value);
  Int2Str(NumberOfEnabledProcessors, numberOfEnabledProcessors.value);
}

Page processorPage = {
    .name = L"Processors Count Page",
    .itemCount = 2,
    .pageItems =
        {
            &numberOfProcessors,
            &numberOfEnabledProcessors,
        },
    .Filler = FillProcessorPageTable,
};
