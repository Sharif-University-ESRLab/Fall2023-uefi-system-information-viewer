#ifndef PAGES_H_
#define PAGES_H_

#pragma pack(1) // Ensures byte alignment

#include "Types.h"
#include "Utils.h"
#include <Uefi.h>

extern Page mainPage;
extern Page processorPage;
extern Page smbiosPage;
extern Page acpiPage;
extern Page networkPage;

#endif // PAGES_H_
