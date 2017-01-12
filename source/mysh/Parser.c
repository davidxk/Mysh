#include "mysh/Parser.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

int paramCnt = 0;

Job job = {
	.path = NULL,
	.outOpt = STDOUT,
	.outputTo = NULL,
	.inOpt = STDIN,
	.inputFrom = NULL,
};

void match(TokenType expected)
{
	if(getToken() == expected)
		return;
	else
		errorMsg();
}

void errorMsg()
{
	char error[80] = "mysh: Unexpected ";
	strcat(error, tokenString);
	write(2, error, strlen(error));
}

Job parse(char* line)
{
	// init
	job.path = NULL;
	job.outOpt = STDOUT;
	job.outputTo = NULL;
	job.inOpt = STDIN;
	job.inputFrom = NULL;
	paramCnt = 0;
	scanInit(line);

	// match command
	match( ID );
	job.path = (char*) malloc(strlen(tokenString));
	strcpy(job.path, tokenString);
	job.argv[paramCnt] = (char*) malloc(strlen(tokenString));
	strcpy(job.argv[paramCnt++], tokenString);

	// match param
	getParams(line);
	job.argv[paramCnt++] = NULL;

	return job;
}

void getParams(char* line)
{
	TokenType token;
	while( (token = getToken()) != ENT_EOF )
	{
		switch( token )
		{
			case ID:
				job.argv[paramCnt] = (char*) malloc(strlen(tokenString));
				strcpy(job.argv[paramCnt++], tokenString);
				break;
			case FILE_OUT:
				job.outOpt = FOUT;
				match( ID );
				job.outputTo = (char*) malloc(strlen(tokenString));
				strcpy(job.outputTo, tokenString);
				break;
			case FILE_APP:
				job.outOpt = FAPP;
				match( ID );
				job.outputTo = (char*) malloc(strlen(tokenString));
				strcpy(job.outputTo, tokenString);
				break;
			case FILE_IN:
				job.inOpt = FIN;
				match( ID );
				job.inputFrom = (char*) malloc(strlen(tokenString));
				strcpy(job.inputFrom, tokenString);
				break;
			default:
				errorMsg();
				break;
		}
	}
	job.argv[paramCnt++] = NULL;
}

void freeJob()
{
	free(job.path);
	free(job.inputFrom);
	free(job.outputTo);
	paramCnt--;
	for(int i=0; i<paramCnt; i++)
		free(job.argv[i]);
}
