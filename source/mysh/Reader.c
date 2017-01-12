#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mysh/Reader.h"

/* Don't see any obvious way to avoid fixed-sized array */
const int bufferSize = 128;

void prompt(char* PS1)
{
	write(1, PS1, strlen(PS1));
}

char* readline()
{
	char* buffer = (char*) malloc( bufferSize );
	read(0, buffer, bufferSize);
	return buffer;
}
