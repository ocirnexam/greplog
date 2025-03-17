#include <stdio.h>
#include <string.h>
#include "search/search.h"

void print_help(void)
{
	char* separator = "------------------------------------------";
	printf("%s\nGREPLOG - Analyse your log files\n%s\n\n", separator, separator);
	printf("Usage: greplog [-o] <search_argument1> <search_argument2> ...\n\n");
	printf("-h: show this help message\n");
	printf("-o: arguments are treated as or instead of and\n%s\n", separator);
}

int main(int argc, char* argv[])
{
	SearchOption so = OPTION_AND;
	if (argc < 2)
	{
		fprintf(stderr, "[ERROR] You have to enter at least one search argument!\n\n Type greplog -h for help\n");
		exit(1);
	}
	char* second_argument = argv[1];	

	// check if second_argument is an option
	if (strncmp(second_argument, "-o", 3) == 0)
	{
		if (argc < 3)
		{
			fprintf(stderr, "[ERROR] You have to enter at least one search argument!\n\n Type greplog -h for help\n");
			exit(1);
		}
		so = OPTION_OR;
	}
	else if (strncmp(second_argument, "-h", 3) == 0)
	{
		print_help();
		exit(0);
	}
	else {
		// no default
	}

	// create search and analyse log files
	Search* search = Search_create(argc, argv, so);
	if(!Search_analyse_logfiles(search))
	{
		fprintf(stderr, "[ERROR]: failed to analyse logfiles\n");
		exit(1);
	}
	Search_destroy(search);
	return 0;
}
