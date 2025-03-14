#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <string.h>
#include <stdlib.h>

typedef enum {
	OPTION_AND,
	OPTION_OR
} SearchOption;

typedef struct {
	char** parameters;
	char* parameter_string;
	int nr_of_parameters;
	SearchOption so;
} Parameter;

Parameter* Parameter_create(int argc, char* argv[], SearchOption so);
char* Parameter_get(Parameter* param, int nr);
char* Parameter_to_string(Parameter* param);
int Parameter_get_nr_of_parameters(Parameter* param);
SearchOption Parameter_get_search_option(Parameter* param);
void Parameter_destroy(Parameter* param);

#endif
