/* elf loader from payload.c (c)mrbrown */

#include <psptypes.h>
#include <string.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <malloc.h>

void me_run();
void me_end();

#define ELF_MAGIC	0x464c457f
#define ELF_PT_LOAD	1

typedef struct {
	u8	ident[16];
	u16	type;
	u16	machine;
	u32	version;
	u32	entry;
	u32	phoff;
	u32	shoff;
	u32	flags;
	u16	ehsize;
	u16	phentsize;
	u16	phnum;
	u16	shentsize;
	u16	shnum;
	u16	shstrndx;
} elf_header_t;

typedef struct {
	u32	type;
	u32	offset;
	void	*vaddr;
	u32	paddr;
	u32	filesz;
	u32	memsz;
	u32	flags;
	u32	align;
} elf_pheader_t;

static void me_reset(u32 start, u32 args)
{
	SceModuleInfo *sysreg_driver;
	memcpy((void *)0xbfc00040, me_run, (int)(me_end - me_run));
	_sw(start, 0xbfc00600);
	_sw(args, 0xbfc00604);
	sceKernelDcacheWritebackAll();
	sceSysregMeResetEnable();
	sceSysregMeBusClockEnable();
	sceSysregMeResetDisable();
}

static u32 load_elf(char *filename)
{
	int fd, size, i;
	char *boot_elf;
	elf_header_t *eh;
	elf_pheader_t *eph;
	void *pdata;

	if ((fd = sceIoOpen(filename, PSP_O_RDONLY, 0777)) < 0)
		return 0; 

	size = sceIoLseek(fd, 0, PSP_SEEK_END);
	if (!size) 
		return 0;

	boot_elf = malloc(size);
	eh = (elf_header_t *)boot_elf;
	sceIoLseek(fd, 0, PSP_SEEK_SET);

	sceIoRead(fd, boot_elf, size);
	sceIoClose(fd);

	/* Load the ELF into RAM.  */
	if (_lw((u32)&eh->ident) != ELF_MAGIC) 
		return 0;

	eph = (elf_pheader_t *)(boot_elf + eh->phoff);

	/* Scan through the ELF's program headers and copy them into RAM, then
	   zero out any non-loaded regions. */

	for (i = 0; i < eh->phnum; i++) {
		if (eph[i].type != ELF_PT_LOAD)
			continue;

		pdata = (void *)(boot_elf + eph[i].offset);
		memcpy(eph[i].vaddr, pdata, eph[i].filesz);

		if (eph[i].memsz > eph[i].filesz)
			memset(eph[i].vaddr + eph[i].filesz, 0,
					eph[i].memsz - eph[i].filesz);
	}

	return eh->entry;
}

int pspMeLoadExec(char *filename, char *args)
{
	u32 start, me_args, arg_len;
	if(!(start = load_elf(filename)))
		return -1;
	if(args)
	{
		arg_len = strlen(args) + 1;
		me_args = 0x88400000 - arg_len;
		memcpy((char *)me_args, args, arg_len);
	}
	else me_args = 0;
	me_reset(start, me_args);
	return 0;
}
