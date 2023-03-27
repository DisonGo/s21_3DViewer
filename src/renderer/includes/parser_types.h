#ifndef PARSER_TYPES_H
#define PARSER_TYPES_H

#define VERTEX_NAME 'v'
#define INDEX_NAME 'f'

typedef enum {
    _false = 0,
    _true = 1
} _bool;

typedef enum errors {
  OK = 0,
  OBJ_FILE_ERROR = 1,
  INPUT_POINTER_ERROR = 2,
  MEMORY_ALLOCATING_ERROR = 3,
  NO_FILE = 4
} errors;

typedef struct Indexes {
  int index_count;
  int* indexes;
} Indexes;

typedef struct Vertexes {
  int point_count;
  float* vertex;
} Vertexes;

#endif  //  PARSER_TYPES_H
