#include <psptypes.h>
#include "cacheops.h"

#define CACHE_OP(op,addr) __asm__ __volatile__("cache %0, 0(%1)\n"::"i" (op), "r" (addr))
#define CLEAR_TAG() __asm__ __volatile__ ("mtc zero, $28\nmtc zero, $29\n")

void pspMeDcacheWritebackAll()
{
}

void pspMeDcacheWritebackInvalidateAll()
{
	int i;
	for(i = 0; i < TAG_SIZE * LINE_SIZE; i += LINE_SIZE)
	{
		CACHE_OP(DXIWBINV, i);
		CACHE_OP(DXIWBINV, i);
	}
}

void pspMeDcacheInvalidateAll()
{
	int i;
	for(i = 0; i < TAG_SIZE * LINE_SIZE; i += LINE_SIZE)
		CACHE_OP(DXIINV, i);
}

void pspMeDcacheWritebackRange(u32 addr, u32 size)
{
}

void pspMeDcacheWritebackInvalidateRange(u32 addr, u32 size)
{
}

void pspMeDcacheInvalidateRange(u32 addr, u32 size)
{
}

void pspMeIcacheInvalidateAll()
{
	int i;
	for(i = 0; i < TAG_SIZE * LINE_SIZE; i += LINE_SIZE)
		CACHE_OP(IXIINV, i);
}

void pspMeIcacheInvalidateRange(u32 addr, u32 size)
{
}
