#ifndef PARSER_TYPES_H
#define PARSER_TYPES_H

#define POINT_NAME 'v'
#define VERTEX_NAME 'f'

typedef enum {
    false = 0,
    true = 1
} bool;

typedef enum errors {
  OK = 0,
  OBJ_FILE_ERROR = 1,
  INPUT_POINTER_ERROR = 2,
  MEMORY_ALLOCATING_ERROR = 3,
  NO_FILE = 4
} errors;

typedef struct Vertex {
  int vertex_count;
  int* each_row_vertexes;
  int** vertex;
} Vertex;

typedef struct Point {
  int point_count;
  float** poses;
} Point;

#endif  //  PARSER_TYPES_H