#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "points_parser.h"
#include "vertex_parser.h"
#include "parser_types.h"

int parse_obj_file(Point* points, Vertex* vertex, FILE* fptr);
void init_structs(Point* points, Vertex* vertex);
int count_number_of_vertex_points(Point* points, Vertex* vertex, FILE* fptr);
int allocate_structs_memory(Point* points, Vertex* vertex, FILE* fptr);
void free_structs(Point* points, Vertex* vertex);

#endif  //  OBJ_PARSER_H