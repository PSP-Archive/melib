#include <psptypes.h>
#include <sys/unistd.h>
#include <errno.h>

#define ME_HEAP_BOTTOM (void *)0x80000220	/* just after exception vectors */
#define ME_HEAP_TOP (void *)0x80200000

extern int _me_stack_size;
static void *_me_heap_ptr = ME_HEAP_BOTTOM;

void *_sbrk(ptrdiff_t incr)
{
	void *new_brk;
	if(incr)
	{
		new_brk = _me_heap_ptr + incr;
		if((new_brk + _me_stack_size) > ME_HEAP_TOP)
		{
			errno = ENOMEM;
			return (void *)-1;
		}
		if(new_brk < ME_HEAP_BOTTOM)
			new_brk = ME_HEAP_BOTTOM;
		_me_heap_ptr = new_brk;
	}
	return _me_heap_ptr;
}
