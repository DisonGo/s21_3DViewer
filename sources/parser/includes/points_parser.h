#ifndef POINTS_PARSER_H
#define POINTS_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "parser_types.h"

int allocate_point_memory(Point* points);
int obj_proccesing_by_point(Point* points, FILE* fptr);

#endif  //  POINTS_PARSER_H