#include "mysh/Scanner.h"
#include "unity.h"
#include "unity_fixture.h"
#include <string.h>

TEST_GROUP(Scanner);

TEST_SETUP(Scanner) { }
TEST_TEAR_DOWN(Scanner) { }

TEST(Scanner, testUnGetNext)
{
	char* line = "Test";
	scanInit(line);
	TEST_ASSERT(getNextChar() == 'T');
	TEST_ASSERT(getNextChar() == 'e');
	TEST_ASSERT(getNextChar() == 's');
	ungetNextChar();
	TEST_ASSERT(getNextChar() == 's');
	TEST_ASSERT(getNextChar() == 't');
}

TEST(Scanner, testGetToken)
{
	char* line = "dir -R >out.txt<in.txt -1 >> app.txt\n";
	scanInit(line);
	TEST_ASSERT(ID == getToken());
	TEST_ASSERT_EQUAL_STRING("dir", tokenString);

	TEST_ASSERT(ID == getToken());
	TEST_ASSERT_EQUAL_STRING("-R", tokenString);

	TEST_ASSERT(FILE_OUT == getToken());
	TEST_ASSERT(ID == getToken());
	TEST_ASSERT_EQUAL_STRING("out.txt", tokenString);

	TEST_ASSERT(FILE_IN == getToken());
	TEST_ASSERT(ID == getToken());
	TEST_ASSERT_EQUAL_STRING("in.txt", tokenString);

	TEST_ASSERT(ID == getToken());
	TEST_ASSERT_EQUAL_STRING("-1", tokenString);

	TEST_ASSERT(FILE_APP == getToken());
	TEST_ASSERT(ID == getToken());
	TEST_ASSERT_EQUAL_STRING("app.txt", tokenString);
}
