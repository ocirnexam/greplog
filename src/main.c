#include <stdio.h>
#include "search/search.h"

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "[ERROR] Usage: ./logfind <search_str1> [-o] <search_str2> ...\n");
		exit(1);
	}
	Search* search = Search_create(argc, argv);
	Search_analyse_logfiles(search);

	Search_destroy(search);
	return 0;
}
