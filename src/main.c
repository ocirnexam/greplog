#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

#define DATA_LENGTH 500

typedef struct {
	FILE* logfiles;
	char** search_attributes;
	char* all_search_attributes_string;
	int search_attr_count;
} Search;

void Search_destroy(Search* s)
{
	if(s)
	{
		if(s->logfiles)
		{
			fclose(s->logfiles);
		}
		for(int i = 0; i < s->search_attr_count; i++)
		{
			if(s->search_attributes[i])
				free(s->search_attributes[i]);
		}
		if(s->search_attributes)
		{
			free(s->search_attributes);
		}
		free(s);
	}
}

void safe_exit(Search* s, char* message)
{
	Search_destroy(s);
	fprintf(stderr, "EXIT: %s:%d: %s\n", __FILE__, __LINE__, message);
	exit(1);
}

Search* Search_initialize(int argc, char* argv[])
{
	Search* s = malloc(sizeof(Search));
	char* home_dir = getenv("HOME");
	char* filename = "/.logfind";
	size_t full_string_length = 0;
	if (!s)
	{
		safe_exit(s, "Failed to allocate memory");
	}
	s->logfiles = fopen(strcat(home_dir, filename), "r+");
	if (!s->logfiles)
	{
		safe_exit(s, "Failed to open ~/.logfind");
	}
	// executable does not need to be stored
	s->search_attributes = malloc(sizeof(char*) * (argc - 1));
	s->search_attr_count = argc - 1;
	if(!s->search_attributes)
	{
		safe_exit(s, "Failed to allocate memory");
	}
	// starting at 1 to remove name of executable
	for(int i = 1; i < argc; i++)
	{
		s->search_attributes[i - 1] = malloc(DATA_LENGTH);
		memcpy(s->search_attributes[i - 1], argv[i], DATA_LENGTH);
		full_string_length += strlen(argv[i]);
	}
	s->all_search_attributes_string = malloc(sizeof(char) * full_string_length + argc);
	if(!s->all_search_attributes_string)
	{
		safe_exit(s, "Failed to allocate memory");
	}
	for(int i = 1; i < argc; i++)
	{
		strncat(s->all_search_attributes_string, argv[i], strlen(argv[i]));
		if(i < argc - 1)
		{
			strncat(s->all_search_attributes_string, " ", 2);
		}
	}
	return s;
}

void Search_logfiles(Search* search)
{
	char filename[DATA_LENGTH];
	char line[DATA_LENGTH];
	int line_count = 0;
	FILE* logfile;
	int i = 0, search_attributes_found = 0;
	// loop over all logfiles stored in ~/.logfind
	while(fgets(filename, DATA_LENGTH, search->logfiles) != NULL)
	{
		// remove trailing newline
		filename[strcspn(filename, "\r\n")] = 0;
		logfile = fopen(filename, "r");
		if(!logfile)
		{
			printf("Failed to open logfile (%s)\n", filename);
			continue;
		}

		line_count = 0;
		// search every line in the logfile and check for search attributes
		while(fgets(line, DATA_LENGTH, logfile) != NULL)
		{
			// remove trailing newline
			line[strcspn(filename, "\r\n")] = 0;
			line_count++;
			search_attributes_found = 0;
			for(i = 0; i < search->search_attr_count; i++)
			{
				if(strstr(line, search->search_attributes[i]) != NULL)
				{
					search_attributes_found += 1;
				}
			}
			if (search_attributes_found == search->search_attr_count)
			{
				printf("%s: %s:%d\n", search->all_search_attributes_string, filename, line_count);
			}
		}
		fclose(logfile);
	}
}


int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "[ERROR] Usage: ./logfind <search_str1> [-o] <search_str2> ...\n");
		exit(1);
	}
	Search* search = Search_initialize(argc, argv);
	Search_logfiles(search);

	Search_destroy(search);
	return 0;
}
