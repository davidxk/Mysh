#include "mysh/Executor.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtin/Cd.h"
#include "builtin/Exit.h"
#include "builtin/Ls.h"
#include "builtin/Pwd.h"

Job job;
int fdIn, fdOut;
int fdStdin, fdStdout;

void execute(Job aJob)
{
	job = aJob;
	if( !findRunCmd() )
	{
		decoratePath();
		forkThread();
	}
}

bool findRunCmd()
{
	bool isBuiltIn = true;
	if( !strcmp(job.path, "pwd") )
		prepareIO(), pwd(job.argv);
	else if( !strcmp(job.path, "cd") )
		prepareIO(), cd(job.argv);
	else if( !strcmp(job.path, "ls") )
		prepareIO(), ls(job.argv);
	else if( !strcmp(job.path, "ln") )
		/*prepareIO(), ln(job.argv);*/
		;
	else if( !strcmp(job.path, "rm") )
		/*prepareIO(), rm(job.argv);*/
		;
	else if( !strcmp(job.path, "exit") )
		prepareIO(), eXIT(job.argv);
	else
		isBuiltIn = false;
	resetIO();
	return isBuiltIn;
}

void resetIO()
{
	if(job.inOpt == FIN)
		close(fdIn), dup2(fdStdin, 0);

	if(job.outOpt == FOUT || job.outOpt == FAPP)
		close(fdOut), dup2(fdStdout, 1);
}

void decoratePath()
{

}

void prepareIO()
{
	if(job.inOpt == FIN)
	{
		fdStdin = dup(0);
		close(0);
		if ( (fdIn = open(job.inputFrom, O_RDONLY, -1)) )
			exit(1);
	}

	if(job.outOpt == FOUT)
	{
		fdStdout = dup(1);
		close(1);
		if( (fdOut = open(job.outputTo, O_WRONLY | O_CREAT | O_TRUNC, 0644))
				== -1 )
			exit(1);
	}
	else if(job.outOpt == FAPP)
	{
		fdStdout = dup(1);
		close(1);
		if( (fdOut = open(job.outputTo, O_WRONLY | O_CREAT | O_APPEND, 0644))
				== -1 )
			exit(1);
	}
}

void forkThread()
{
	short pid;
	if ((pid = fork()) == 0 )
	{
		prepareIO();
		char *envp[] = { NULL };
		execve(job.path, job.argv, envp);

		/* we won’t get here unless execve failed */
		if (errno == ENOENT)
		{
			fprintf (stderr, "mysh : command not found : %s\n", job.path) ;
			exit (1) ;
		}
		else
		{
			fprintf(stderr, "mysh: execution of %s failed: %s\n",
					job.path, strerror(errno));
			exit(1);
		}
	}
	/*else*/
	wait(NULL);
}
