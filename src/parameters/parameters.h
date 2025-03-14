#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <string.h>
#include <stdlib.h>

typedef struct {
	char** parameters;
	char* parameter_string;
	int nr_of_parameters;
} Parameter;

Parameter* Parameter_create(int argc, char* argv[]);
char* Parameter_get(Parameter* param, int nr);
char* Parameter_to_string(Parameter* param);
int Parameter_get_nr_of_parameters(Parameter* param);
void Parameter_destroy(Parameter* param);

#endif
