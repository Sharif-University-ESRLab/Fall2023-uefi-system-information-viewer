#include "Utils.h"

#include <Library/UefiLib.h>
#include <Uefi.h>

UINTN Int2Str(INT32 num, CHAR16 *res) {
  UINTN len = 0;
  INT32 n = num;
  while (num > 0) {
    num /= 10;
    len ++;
  }
  UINTN l = len;
  num = n;
  res[len] = '\0';
  while (num > 0) {
    res[--len] = num % 10 + '0';
    num /= 10;
  }

  return l;
}

INT32 NoneString(CHAR16 *res) {
  res[0] = '\0';
  return 0;
}

INT32 MatchIndex(const CHAR16 *name, const CHAR16 *lookupTerm) {
  for (INT32 k = 0; k < StrLen(name) - StrLen(lookupTerm) + 1; k++) {
    INT32 equal = 0;
    for (INT32 j = 0; j < StrLen(lookupTerm); j++) {
      if (lookupTerm[j] != name[k + j]) {
        equal = -1;
      }
    }
    if (equal == 0)
      return k;
  }
  return -1;
}

VOID UpdateTerm(EFI_INPUT_KEY key, CHAR16 *term) {
  if (key.UnicodeChar != 0) {
    if (key.UnicodeChar == CHAR_BACKSPACE) {
      if (StrLen(term) == 0) {
        return;
      }
      term[StrLen(term) - 1] = L'\0';
      return;
    }

    if (StrLen(term) >= MAX_NAME_LEN - 1) {
      return;
    }
    term[StrLen(term) + 1] = L'\0';
    term[StrLen(term)] = key.UnicodeChar;
  } else {
    if (key.ScanCode == CHAR_BACKSPACE) {
      if (StrLen(term) == 0) {
        return;
      }
      term[StrLen(term) - 1] = L'\0';
    }
  }
}