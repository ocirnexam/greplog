#include "search.h"

static void safe_exit(Search* s, char* message)
{
	Search_destroy(s);
	fprintf(stderr, "EXIT: %s:%d: %s\n", __FILE__, __LINE__, message);
	exit(1);
}

void Search_destroy(Search* s)
{
	if(s)
	{
		if(s->parameter)
		{
			Parameter_destroy(s->parameter);
		}
		if(s->logfiles)
		{
			fclose(s->logfiles);
		}
		free(s);
	}
}

Search* Search_create(int argc, char* argv[])
{
	Parameter* param = Parameter_create(argc, argv);
	if(!param)
	{
		return NULL;
	}
	char* home_dir = getenv("HOME");
	char* filename = "/.logfind";
	Search* s = malloc(sizeof(Search));
	if (!s)
	{
		safe_exit(s, "Failed to allocate memory");
	}
	s->parameter = param;
	s->logfiles = fopen(strcat(home_dir, filename), "r+");
	if (!s->logfiles)
	{
		safe_exit(s, "Failed to open ~/.logfind");
	}
	return s;
}

void Search_analyse_logfiles(Search* search)
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
			for(i = 0; i < Parameter_get_nr_of_parameters(search->parameter); i++)
			{
				if(strstr(line, Parameter_get(search->parameter, i)) != NULL)
				{
					search_attributes_found += 1;
				}
			}
			if (search_attributes_found == Parameter_get_nr_of_parameters(search->parameter))
			{
				printf("%s: %s:%d\n", Parameter_to_string(search->parameter), filename, line_count);
			}
		}
		fclose(logfile);
	}
}

