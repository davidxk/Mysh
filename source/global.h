#ifndef _GLOABL_H_
#define _GLOABL_H_

/* global bool type */
typedef enum Bool{ true = 1, false = 0 } bool;

/* for passing data from parser to executor */
typedef enum outputOptions {
	STDOUT, FOUT, FAPP
} OutputOption;

typedef enum inputOption {
	STDIN, FIN
} InputOption;

typedef struct job {
	char* path;
	char* argv[20];
	OutputOption outOpt;
	char* outputTo;
	InputOption inOpt;
	char* inputFrom;
}Job;

/* global variable */
extern bool isExit;

#endif
