/*****************************
 *                           *
 *   .obj file parser.       *
 *   Part of 3D_Viewer.      *
 *       @simphoniia         *
 *                           *
 *****************************/

#include "../includes/obj_parser.h"

int parse_obj_file(Vertexes* vertexes, Indexes* indexes, FILE* fptr) {
  if (!fptr) return NO_FILE;
  int err_code = OK;
  init_structs(vertexes, indexes);
  err_code = count_number_of_vertex_points(vertexes, indexes, fptr);
  if (!err_code) err_code = allocate_structs_memory(vertexes, indexes, fptr);
  return err_code;
}

void init_structs(Vertexes* vertexes, Indexes* indexes) {
  vertexes->point_count = 0;
  vertexes->vertex = NULL;
  indexes->indexes = NULL;
  indexes->index_count = 0;
}

int count_number_of_vertex_points(Vertexes* vertexes, Indexes* indexes,
                                  FILE* fptr) {
  if (!vertexes || !indexes || !fptr) return INPUT_POINTER_ERROR;
  char buff[8] = {0};
  while (fgets(buff, 8, fptr)) {
    if (!strncmp(buff, "v ", 2)) vertexes->point_count++;
    if (!strncmp(buff, "f ", 2)) indexes->index_count++;
  }
  rewind(fptr);
  return OK;
}

int allocate_structs_memory(Vertexes* vertexes, Indexes* indexes, FILE* fptr) {
  int err_code = OK;
  if (!vertexes || !indexes || !fptr) return INPUT_POINTER_ERROR;
  err_code = allocate_vertex_memory(vertexes);
  if (!err_code) err_code = obj_proccesing_by_vertex(vertexes, fptr);
  if (!err_code) err_code = allocate_indexes_memory(indexes);
  if (!err_code) err_code = obj_processing_by_indexes(indexes, fptr);
  return err_code;
}

void free_structs(Vertexes* vertexes, Indexes* indexes) {
  if (vertexes) {
    free(vertexes->vertex);
    vertexes->point_count = 0;
  }
  if (indexes) {
    free(vertexes->vertex);
    indexes->index_count = 0;
  }
}

// int main(void) {
//   double time_spent = 0.0;
//   clock_t begin = clock();
//   FILE* fptr = fopen("castle.obj", "r");
//   Point p;
//   indexes v;
//   int result = parse_obj_file(&p, &v, fptr);
//   printf("RESULT OF PARSE = %d\n", result);
//   printf("vertexes = %d\n", p.point_count);
//   printf("indexes = %d\n", v.index_count);
//   switch (result) {
//     case 0:
//       printf("SUCCESS\n");
//       break;
//     case 1:
//       printf("OBJ FILE ERROR\n");
//       break;
//     case 2:
//       printf("POINTER ERROR\n");
//       break;
//     case 3:
//       printf("MEMORY ALLOCATING ERROR\n");
//       break;
//     case 4:
//       printf("NO FILE\n");
//       break;
//   }
//   free_structs(&p, &v);
//   if (fptr) fclose(fptr);
//   clock_t end = clock();
//   time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
//   printf("The elapsed time is %f seconds", time_spent);

//   return 0;
// }