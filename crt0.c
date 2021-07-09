#include <psptypes.h>
#include <string.h>
#include <malloc.h>

#define ARG_MAX 10

int _me_stack_size = (16 * 1024);

void _start(char *args)
{
	char *argv[ARG_MAX + 1], *arg_ptr;
	int argc = 0;
	if(args)
	{
		arg_ptr = malloc(strlen(arg_ptr) + 1);
		strcpy(arg_ptr, args);
		while(arg_ptr && (argc < ARG_MAX))
		{
			argv[argc++] = arg_ptr;
			arg_ptr = strchr(arg_ptr, ' ');
			if(arg_ptr)
			{
				arg_ptr[0] = 0;
				arg_ptr++;
			}
		}
	}
	else argv[0] = NULL;
	main(argc, argv);
	while(1);
}
