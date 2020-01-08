#pragma once

#include "stdafx.h"

bool PlaceBytes(void* dst, uint8_t* src, size_t len);
uint32_t FindPattern(uint32_t address, size_t len, uint8_t *bMask, char *szMask);
bool ComparePattern(const uint8_t* pData, const uint8_t* bMask, const char* szMask);

// used to prevent cheap signature scans?
#define junkasm __asm _emit 0xEB __asm _emit 0x11 __asm _emit 0x4A __asm _emit 0x61 __asm _emit 0x73 __asm _emit 0x6D __asm _emit 0x69 __asm _emit 0x6E __asm _emit 0x57 __asm _emit 0x61 __asm _emit 0x6C __asm _emit 0x65 __asm _emit 0x72 __asm _emit 0x69 __asm _emit 0x61 __asm _emit 0x53 __asm _emit 0x6F __asm _emit 0x72 __asm _emit 0x61