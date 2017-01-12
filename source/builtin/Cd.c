#include <stdio.h>
#include <unistd.h>

void cd(char* argv[])
{
	if( chdir(argv[1]) == -1 )
		perror(argv[0]);
}
