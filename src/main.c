#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DATA_LENGTH 500

typedef struct {
	FILE* logfiles;
	char** search_attributes;
	int search_attr_count;
} Search;

void safe_exit(Search* s, char* message)
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
	fprintf(stderr, "EXIT: %s:%d: %s\n", __FILE__, __LINE__, message);
	exit(1);
}

Search* initialize_search(int argc, char* argv[])
{
	Search* s = malloc(sizeof(Search));
	char* home_dir = getenv("HOME");
	char* filename = "/.logfind";
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
	}
	return s;
}

void search_logfiles(Search* search)
{
	char filename[DATA_LENGTH];
	char line[DATA_LENGTH];
	int line_count = 0;
	FILE* logfile;
	int i = 0;
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
			for(i = 0; i < search->search_attr_count; i++)
			{
				if(strstr(line, search->search_attributes[i]) != NULL)
				{
					printf("%s: %s:%d\n", search->search_attributes[i], filename, line_count);
				}
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
	Search* search = initialize_search(argc, argv);
	printf("Entered %d search attributes\n", search->search_attr_count);
	for(int i = 0; i < search->search_attr_count; i++)
	{
		printf("Search for: %s\n", search->search_attributes[i]);
	}
	search_logfiles(search);

	safe_exit(search, "Programm exit");
	return 0;
}
