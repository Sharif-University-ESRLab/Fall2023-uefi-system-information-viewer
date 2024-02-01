#ifndef UTILS_H_
#define UTILS_H_

#pragma pack(1) // Ensures byte alignment

#include "Settings.h"
#include <Uefi.h>

UINTN Int2Str(INT32 num, CHAR16 *res);

INT32 NoneString(CHAR16 *res);

// Return the index of the first match, or -1 if no match
INT32 MatchIndex(const CHAR16 *name, const CHAR16 *lookupTerm);

VOID UpdateTerm(EFI_INPUT_KEY key, CHAR16 *term);

#endif // UTILS_H_
