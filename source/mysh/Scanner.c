#include "global.h"
#include "mysh/Scanner.h"

void scanInit(char* line)
{
	ptr = line;
	cnt = 0;
}

char getNextChar()
{
	return ptr[ cnt++ ];
}

void ungetNextChar()
{
	cnt--;
}

TokenType getToken()
{
	int tokenStringIndex = 0;
	TokenType currentToken;
	StateType state=START;

	bool save;
	while(state != DONE)
	{
		char cc = getNextChar();
		save = true;
		switch(state)
		{
			case START:
				if( cc==' ' || cc=='\t' )
					save = false;
				else if(cc == '<')
				{
					currentToken = FILE_IN;
					state = DONE;
				}
				else if(cc == '>')
					state = INAPP;
				else if(cc == '\n' || cc == '\0' || cc == '\r')
				{
					currentToken = ENT_EOF;
					state = DONE;
				}
				else
					state = INID;
				break;
			case INAPP:
				if(cc == '>')
				{
					state = DONE;
					currentToken = FILE_APP;
				}
				else
				{
					ungetNextChar();
					save = false;
					state = DONE;
					currentToken = FILE_OUT;
				}
				break;
			case INID:
				switch(cc)
				{
					case ' ': case '\t': case '>': case '<': case '\n':
						ungetNextChar();
						save = false;
						state = DONE;
						currentToken = ID;
						break;
				}
				break;
			case DONE: break;
			default:
				state = DONE;
				currentToken = ERROR;
				break;
		}
		if( save && tokenStringIndex<=MAXTOKENLEN )
			tokenString[tokenStringIndex++] = cc;

		if(state == DONE)
			tokenString[tokenStringIndex++]='\0';
	}
	return currentToken;
}
