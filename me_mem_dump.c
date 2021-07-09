#include <psptypes.h>
#include <mecache.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
	int size;
	char *addr, *dst;
	addr = (char *)atoi(argv[0]);
	size = atoi(argv[1]);
	dst = (char *)(0x88400000 - size);
	memcpy(dst, addr, size);
	_sw(dst, 0xbfc00604);
	pspMeDcacheWritebackInvalidateAll();
	while(1) _sw(0, 0xbfc00600);
}
