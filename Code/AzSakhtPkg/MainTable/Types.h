#ifndef TYPES_H_
#define TYPES_H_

#pragma pack(1) // Ensures byte alignment

#include "Settings.h"
#include <Uefi.h>

struct PageItem;

typedef struct {
  CHAR16* name;
  INT32 itemCount;
  struct PageItem **pageItems[HEIGHT];
  VOID (*Filler)();
} Page;

typedef struct PageItem {
  CHAR16 *name;
  CHAR16 *value;
  CHAR16 *moreInformation;
  Page *page;
} PageItem;

typedef struct {
  UINTN onHeader;    // Which of the two numbers below are valid
  UINTN headerIndex; // Main window, Search, Filter
  UINTN rowNumber;
} Position;

#endif // TYPES_H_
