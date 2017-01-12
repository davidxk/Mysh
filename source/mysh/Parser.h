#ifndef _PARSER_C_
#define _PARSER_C_

#include "mysh/Scanner.h"
#include "global.h"

void match(TokenType expected);
void errorMsg();
Job parse(char* line);
void getParams(char* line);
void freeJob();
#endif
