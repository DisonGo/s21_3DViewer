#ifndef PARSER_TYPES_H
#define PARSER_TYPES_H

#define VERTEX_NAME 'v'
#define INDEX_NAME 'f'
#define GROUP_NAME 'g'

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

typedef struct {
  float x, y, z;
} Vertex;

typedef struct {
  unsigned int index[3];
  int arr_size;
} Face;

typedef struct {
    int num_faces;
    Face* faces;
} Object;

typedef struct {
  Vertex* vertices;
  int vertices_count;
  Object* objects;
  int objects_count;
} Scene;


#endif  //  PARSER_TYPES_H
