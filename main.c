/* elf loader from payload.c (c)mrbrown */

#include <psptypes.h>
#include <string.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <meinit.h>
#include <stdio.h>

PSP_MODULE_INFO("ME_test", 0x1000, 1, 1);
PSP_MAIN_THREAD_ATTR(0);

#define ME_ADDR 0x88000000
#define ME_SIZE 0x20000

void test()
{
	int fd;
	char buffer[ME_SIZE];
	while(_lw(0xbfc00600));
	sceKernelDcacheWritebackInvalidateAll();
	fd = sceIoOpen("ms0:/me_dump", PSP_O_CREAT|PSP_O_TRUNC|PSP_O_WRONLY, 0777);
	if(fd > 0)
	{
		sceIoWrite(fd, _lw(0xbfc00604), ME_SIZE);
		sceIoClose(fd);
	}
}

int main(int argc, char **argv)
{
	u32 start;
	char args[100], addr[20], size[20];
	pspDebugInstallErrorHandler(NULL);
	pspDebugScreenInit();
	sprintf(args, "%d %d", ME_ADDR, ME_SIZE);
	pspDebugScreenPrintf("start %s\n", args);
	if(pspMeLoadExec("ms0:/metest.elf", args) != -1)
		test();
	sceKernelExitGame();
	return 0;
}
