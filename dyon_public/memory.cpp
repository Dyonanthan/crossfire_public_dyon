
#include "memory.h"

bool PlaceBytes(void* dst, uint8_t* src, size_t len)
{
	DWORD dwOldProtect;
	if (!VirtualProtect(dst, len, PAGE_EXECUTE_READWRITE, &dwOldProtect))
		return false;

	memcpy(dst, reinterpret_cast<void*>(src), len);

	return VirtualProtect(dst, len, dwOldProtect, &dwOldProtect) == TRUE;
}

uint32_t FindPattern(uint32_t address, size_t len, uint8_t *pattern, char *mask)
{
	for (uint32_t i = 0; i < len; i++)
		if (ComparePattern(reinterpret_cast<uint8_t*>(address + i), pattern, mask))
			return address + i;
	return 0;
}

bool ComparePattern(const uint8_t *data, const uint8_t *pattern, const char *mask)
{
	for (; *mask; ++mask, ++data, ++pattern)
		if ((*mask != '?') && (*mask == 'x' && *data != *pattern))
			return 0;
	return true;
}