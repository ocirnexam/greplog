#include <string.h>
#include <unity.h>

#include "../parameters.h"

char* argv1[] = {"logfind", "-o", "test", "args"};
char* argv2[] = {"logfind", "test", "args"};

int argc1 = 4;
int argc2 = 3;

Parameter* param1 = NULL;
Parameter* param2 = NULL;

void setUp(void)
{
	SearchOption so1 = OPTION_OR;
	SearchOption so2 = OPTION_AND;

	param1 = Parameter_create(argc1, argv1, so1);
	param2 = Parameter_create(argc2, argv2, so2);
}

void tearDown(void)
{
	Parameter_destroy(param1);
	Parameter_destroy(param2);
}

void test_parameter_create(void)
{
	SearchOption so = OPTION_OR;
	Parameter* param = Parameter_create(argc1, argv1, so);
	TEST_ASSERT_NOT_EQUAL(NULL, param);
	if(param)
	{
		Parameter_destroy(param);
	}
}

void test_parameter_get_arguments(void)
{
	char* arg = Parameter_get(param1, 1);
	TEST_ASSERT_EQUAL_STRING("args", arg);

	arg = Parameter_get(param1, 0);
	TEST_ASSERT_EQUAL_STRING("test", arg);

	arg = Parameter_get(param1, 2);
	TEST_ASSERT_EQUAL_STRING(NULL, arg);
}

void test_parameter_to_string(void)
{
	char* arguments = Parameter_to_string(param1);
	TEST_ASSERT_EQUAL_STRING("test args", arguments);
}

void test_get_nr_of_parameters(void)
{
	int count1 = Parameter_get_nr_of_parameters(param1);
	int count2 = Parameter_get_nr_of_parameters(param2);

	TEST_ASSERT_EQUAL(2, count1);
	TEST_ASSERT_EQUAL(2, count2);
}

void test_parameter_get_search_option(void)
{
	SearchOption so1 = Parameter_get_search_option(param1);
	SearchOption so2 = Parameter_get_search_option(param2);
	
	TEST_ASSERT_EQUAL(OPTION_OR, so1);
	TEST_ASSERT_EQUAL(OPTION_AND, so2);
}

int main(void)
{
	UNITY_BEGIN();

	// TESTS
	RUN_TEST(test_parameter_create);
	RUN_TEST(test_parameter_get_arguments);
	RUN_TEST(test_parameter_to_string);
	RUN_TEST(test_get_nr_of_parameters);
	RUN_TEST(test_parameter_get_search_option);

	UNITY_END();

	return 0;
}
