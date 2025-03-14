#ifndef SEARCH_H
#define SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include "../parameters/parameters.h"

#define DATA_LENGTH 512

typedef struct {
	FILE* logfiles;
	Parameter* parameter;
} Search;

Search* Search_create(int argc, char* argv[], SearchOption so);
void Search_analyse_logfiles(Search* search);
void Search_destroy(Search* search);

#endif
