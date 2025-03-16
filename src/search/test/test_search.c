#include <unity.h>
#include "search/search.h"

char* argv[] = {"logfind", "hello", "world"};
int argc = 3;

void setUp(void)
{
}

void tearDown(void)
{
}

void test_search_create(void)
{
	SearchOption so = OPTION_AND;
	Search* search = Search_create(argc, argv, so);
	TEST_ASSERT_NOT_EQUAL(NULL, search);

	Search_destroy(search);
}

void test_search_analyse_logfiles(void)
{
	TEST_ASSERT_EQUAL(1, 1);
}

int main(void)
{
	UNITY_BEGIN();

	// TESTS
	RUN_TEST(test_search_create);

	UNITY_END();

	return 0;
}	
