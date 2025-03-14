#include "parameters.h"

Parameter* Parameter_create(int argc, char* argv[])
{
	int full_string_length = 0;
	Parameter* param = malloc(sizeof(Parameter));
	if(!param)
	{
		return NULL;
	}
	
	param->parameters = malloc(sizeof(char*) * (argc - 1));
	param->nr_of_parameters = argc - 1;
	if(!param->nr_of_parameters)
	{
		return NULL;
	}
	// starting at 1 to remove name of executable
	for(int i = 1; i < argc; i++)
	{
		param->parameters[i - 1] = malloc(strlen(argv[i]) + 1);
		memcpy(param->parameters[i - 1], argv[i], strlen(argv[i]));
		full_string_length += strlen(argv[i]);
	}
	param->parameter_string = malloc(sizeof(char) * full_string_length + argc);
	if(!param->parameter_string)
	{
		return NULL;
	}
	for(int i = 1; i < argc; i++)
	{
		strncat(param->parameter_string, argv[i], strlen(argv[i]));
		if(i < argc - 1)
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
