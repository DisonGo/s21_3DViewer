#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "index_parser.h"
#include "vertex_parser.h"
#include "parser_types.h"

int parse_obj_file(Vertexes* vertexes, Indexes* indexes, FILE* fptr);
void init_structs(Vertexes* vertexes, Indexes* indexes);
int count_number_of_vertex_points(Vertexes* vertexes, Indexes* indexes, FILE* fptr);
int allocate_structs_memory(Vertexes* vertexes, Indexes* indexes, FILE* fptr);
void free_structs(Vertexes* vertexes, Indexes* indexes);

#endif  //  OBJ_PARSER_H