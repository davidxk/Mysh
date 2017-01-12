#include "unity_fixture.h"

static void RunAllTests(void)
{
	RUN_TEST_GROUP(Parser);
	RUN_TEST_GROUP(Scanner);
}
int main(int argc, const char * argv[])
{
	return UnityMain(argc, argv, RunAllTests);
}
