#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H

#include "parser_types.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define START_SIZE 5
#define MULTIPLY_FACTOR 1.8

int parse_obj_file(Scene* scene, FILE* fptr);
void initialize_scene(Scene* scene);
int allocate_structs_memory(Scene* scene);
int fill_array(Scene* scene, FILE* fptr);
int push_vertices(const char* str, Scene* scene, int* capacity);
int push_faces(const char* str, Scene* scene, int group, int* capacity);
int is_digit(const char symb);
int move_to_next_value(const char* str, size_t i);
void free_structs(Scene* scene);

#endif  //  OBJ_PARSER_H