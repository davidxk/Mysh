#ifndef _SCANNER_C_
#define _SCANNER_C_

static const int MAXTOKENLEN = 256;
char tokenString[ MAXTOKENLEN ];

static int cnt = 0;
char* ptr;

typedef enum{ START, INREDIR, INID, INAPP, DONE } StateType;
typedef enum{ FILE_IN, FILE_OUT, FILE_APP, ID, ERROR, ENT_EOF } TokenType;

static struct {
	char* str;
	TokenType tok;
} reservedWords[]= { {"<", FILE_IN}, {">", FILE_OUT} };

void scanInit(char* line);
char getNextChar();
void ungetNextChar();
TokenType getToken();
#endif
