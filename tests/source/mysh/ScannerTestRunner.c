#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(Scanner)
{
	RUN_TEST_CASE(Scanner, testUnGetNext);
	RUN_TEST_CASE(Scanner, testGetToken);
}
