#include "global.h"
#include "mysh/Executor.h"
#include "mysh/Mysh.h"
#include "mysh/Reader.h"
#include "mysh/Parser.h"
#include <stdlib.h>
#include <stdio.h>

char* PS1 = "$ ";
bool isExit = false;

void init()
{

}

void mysh()
{
	init();
	while( !isExit )
	{
		prompt( PS1 );
		char* line = readline();
		/* todo: check if the line's too long */
		Job job = parse( line );
		execute( job );
		free( line );
		freeJob();
	}
}
