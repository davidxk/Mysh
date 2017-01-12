#include "mysh/Parser.h"
#include "unity.h"
#include "unity_fixture.h"
#include <string.h>

TEST_GROUP(Parser);

TEST_SETUP(Parser) { }
TEST_TEAR_DOWN(Parser) { }

TEST(Parser, testParse)
{
	char* line = "ls -R >>out.txt<in.txt -1\n";
	Job job = parse(line);
	TEST_ASSERT_EQUAL_STRING("ls", job.path);
	TEST_ASSERT_EQUAL_STRING("ls", job.argv[0]);
	TEST_ASSERT_EQUAL_STRING("-R", job.argv[1]);
	TEST_ASSERT_EQUAL_STRING("-1", job.argv[2]);
	TEST_ASSERT(FAPP == job.outOpt);
	TEST_ASSERT_EQUAL_STRING("out.txt", job.outputTo);
	TEST_ASSERT(FIN == job.inOpt);
	TEST_ASSERT_EQUAL_STRING("in.txt", job.inputFrom);
}
