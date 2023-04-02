#ifndef SUB_FUNCTIONS_H
#define SUB_FUNCTIONS_H

#include "obj_parser.h"

int group_processing(int* group, Scene* scene, int* faces_capacity);
FILE* open_file(const char* filename);
void initialize_scene(Scene* scene);
int allocate_structs_memory(Scene* scene);
int create_new_object(Scene* scene, int group);
int fill_array(Scene* scene, FILE* fptr);
int push_vertices(const char* str, Scene* scene, int* capacity);
int push_faces(const char* str, Scene* scene, int group, int* capacity);
void push_face_value(Scene* scene, int face_index, int* values, int i);
void fill_array_values_from_str(int* dest, const char* str, int* arr_size);
int is_digit(const char symb);
int reallocate_faces(Scene* scene, int group, int* capacity);
int move_to_next_value(const char* str, size_t i);

#endif  // SUB_FUNCTIONS_H