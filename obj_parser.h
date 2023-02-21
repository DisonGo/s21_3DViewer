#ifndef PARCER_H
#define PARCER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define POINT_NAME 'v'
#define VERTEX_NAME 'f'

typedef enum errors {
    OK = 0,
    OBJ_FILE_ERROR = 1,
    INPUT_POINTER_ERROR = 2,
    MEMORY_ALLOCATING_ERROR = 3,
    NO_FILE = 4
} errors;

typedef struct Point {
    int point_count;
    float** poses;
} Point;

typedef struct Vertex {
    int vertex_count;
    int* each_row_vertexes;
    int** vertex;
} Vertex;


int parse_obj_file(Point* points, Vertex* vertex, FILE* fptr);
void init_structs(Point* points, Vertex* vertex);
int count_number_of_vertex_points(Point* points, Vertex* vertex, FILE* fptr);

int allocate_structs_memory(Point* points, Vertex* vertex, FILE* fptr);
int allocate_point_memory(Point* points);
int allocate_vertex_memory(Vertex* vertex);

int obj_proccesing_by_point(Point* points, FILE* fptr);
int filling_point_array(int row, const char* str, Point* points);

int obj_processing_by_vertex(Vertex* vertex, FILE* fptr);
int filling_vertex_array(int row, const char* str, Vertex* vertex);

int is_digit_part(const int c);
int is_string_empty(const char* str);
int move_ptr_to_next_value(const char* str, int iterator, size_t strlen);

void free_structs(Point* points, Vertex* vertex);


#endif  //  PARCER_H