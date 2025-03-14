#include "parameters.h"

Parameter* Parameter_create(int argc, char* argv[], SearchOption so)
{
	int full_string_length = 0;
	int start = 0;
	Parameter* param = malloc(sizeof(Parameter));
	if(!param)
	{
		return NULL;
	}
	param->so = so;
	// if option is or, second argument is '-o' and not a search attribute
	if (so == OPTION_OR)
	{
		start = 2;
		param->parameters = malloc(sizeof(char*) * (argc - 2));
		param->nr_of_parameters = argc - 2;
	}
	else 
	{
		start = 1;
		param->parameters = malloc(sizeof(char*) * (argc - 1));
		param->nr_of_parameters = argc - 1;
	}
	if (!param->parameters)
	{
		Parameter_destroy(param);
		return NULL;
	}
	for(int i = start; i < argc; i++)
	{
		param->parameters[i - start] = malloc(strlen(argv[i]) + 1);
		memcpy(param->parameters[i - start], argv[i], strlen(argv[i]));
		full_string_length += strlen(argv[i]);
	}
	param->parameter_string = malloc(sizeof(char) * full_string_length + argc);
	if(!param->parameter_string)
	{
		return NULL;
	}
	for(int i = start; i < argc; i++)
	{
		strncat(param->parameter_string, argv[i], strlen(argv[i]));
		if(i < argc - start)
		{
			strncat(param->parameter_string, " ", 2);
		}
	}
	return param;
}

char* Parameter_get(Parameter* param, int nr)
{
	if(nr <= param->nr_of_parameters)
	{
		return param->parameters[nr];
	}
	return NULL;
}

char* Parameter_to_string(Parameter* param)
{
	return param->parameter_string;
}

int Parameter_get_nr_of_parameters(Parameter* param)
{
	return param->nr_of_parameters;
}

SearchOption Parameter_get_search_option(Parameter* param)
{
	return param->so;
}

void Parameter_destroy(Parameter* param)
{
	
	for(int i = 0; i < param->nr_of_parameters; i++)
	{
		if(param->parameters[i])
			free(param->parameters[i]);
	}
	if(param->parameters)
	{
		free(param->parameters);
	}
	if(param->parameter_string)
	{
		free(param->parameter_string);
	}
	free(param);
}
