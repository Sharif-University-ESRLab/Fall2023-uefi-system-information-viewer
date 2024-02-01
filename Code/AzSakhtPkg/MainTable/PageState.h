#ifndef PAGE_STATE_H_
#define PAGE_STATE_H_

#pragma pack(1) // Ensures byte alignment

#include "Types.h"
#include <Uefi.h>

extern Page *currentPage;

extern CHAR16 filterTerm[MAX_NAME_LEN];
extern CHAR16 searchTerm[MAX_NAME_LEN];

extern Position position;

VOID UpdateScreen();
VOID HandleKeyStroke(EFI_INPUT_KEY key);

#endif // PAEGS_STATE_H_
