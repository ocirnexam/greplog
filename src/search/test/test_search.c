#include <unity.h>
#include <stdbool.h>
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
	SearchOption so = OPTION_AND;
	Search* search = Search_create(argc, argv, so);
	bool rt = Search_analyse_logfiles(search);
	TEST_ASSERT_EQUAL(true, rt);
	Search_destroy(search);	
}

int main(void)
{
	UNITY_BEGIN();

	// TESTS
	RUN_TEST(test_search_create);

	UNITY_END();

	return 0;
}	
