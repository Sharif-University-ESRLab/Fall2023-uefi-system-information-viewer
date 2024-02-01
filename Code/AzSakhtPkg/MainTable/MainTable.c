#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Uefi.h>

#include "Pages.h"
#include "PageState.h"
#include "Types.h"

Page *currentPage = &mainPage;
Position position = {1, 0, 0};

EFI_STATUS EFIAPI UefiMain(EFI_HANDLE ImageHandle,
                           EFI_SYSTEM_TABLE *SystemTable) {
  // TODO: I defined it for now because I was defining an array, but it looked nice.
  // EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *SimpleTextOut;
  // SystemTable->BootServices->LocateProtocol(&gEfiSimpleTextOutProtocolGuid,
  //                                           NULL, (VOID **)&SimpleTextOut);

  // if (SimpleTextOut != NULL) {
  //   SimpleTextOut->QueryMode(SimpleTextOut, 0, &WIDTH, &HEIGHT);   // Character width per line
  // }
  UpdateScreen();
  EFI_INPUT_KEY Key;

  while (1) {
    SystemTable->BootServices->WaitForEvent(1, &SystemTable->ConIn->WaitForKey, NULL);
    SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &Key);
    if (Key.ScanCode + Key.UnicodeChar) {
      HandleKeyStroke(Key);
      UpdateScreen();
    }
  }

  return EFI_SUCCESS;
}
