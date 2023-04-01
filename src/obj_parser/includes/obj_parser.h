#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H

#include "parser_types.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define START_SIZE 5
#define MULTIPLY_FACTOR 2

int parse_obj_file(Scene* scene, const char* filename);
void free_structs(Scene* scene);

#endif  //  OBJ_PARSER_H