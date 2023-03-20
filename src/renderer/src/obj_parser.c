/*****************************
 *                           *
 *   .obj file parser.       *
 *   Part of 3D_Viewer.      *
 *       @simphoniia         *
 *                           *
 *****************************/

#include "../includes/obj_parser.h"

int parse_obj_file(Point* points, Vertex* vertex, FILE* fptr) {
  if (!fptr) return NO_FILE;
  int err_code = OK;
  init_structs(points, vertex);
  err_code = count_number_of_vertex_points(points, vertex, fptr);
  if (!err_code) err_code = allocate_structs_memory(points, vertex, fptr);
  return err_code;
}

void init_structs(Point* points, Vertex* vertex) {
  points->point_count = 0;
  points->poses = NULL;
  vertex->each_row_vertexes = NULL;
  vertex->vertex = NULL;
  vertex->vertex_count = 0;
}

int count_number_of_vertex_points(Point* points, Vertex* vertex, FILE* fptr) {
  if (!points || !vertex || !fptr) return INPUT_POINTER_ERROR;
  char buff[8] = {0};
  while (fgets(buff, 8, fptr)) {
    if (!strncmp(buff, "v ", 2)) points->point_count++;
    if (!strncmp(buff, "f ", 2)) vertex->vertex_count++;
  }
  rewind(fptr);
  return OK;
}

int allocate_structs_memory(Point* points, Vertex* vertex, FILE* fptr) {
  int err_code = OK;
  if (!points || !vertex || !fptr) return INPUT_POINTER_ERROR;
  err_code = allocate_point_memory(points);
  if (!err_code) err_code = obj_proccesing_by_point(points, fptr);
  if (!err_code) err_code = allocate_vertex_memory(vertex);
  if (!err_code) err_code = obj_processing_by_vertex(vertex, fptr);
  return err_code;
}

void free_structs(Point* points, Vertex* vertex) {
  if (points) {
    for (int i = 0; i < points->point_count; i++) {
      if (points->poses[i]) free(points->poses[i]);
    }
    if (points->poses) free(points->poses);
  }
  if (vertex) {
    for (int i = 0; i < vertex->vertex_count; i++) {
      if (vertex->vertex)
        if (vertex->vertex[i]) free(vertex->vertex[i]);
    }
    if (vertex->each_row_vertexes) free(vertex->each_row_vertexes);
    if (vertex->vertex) free(vertex->vertex);
  }
}

// int main(void) {
//   double time_spent = 0.0;
//   clock_t begin = clock();
//   FILE* fptr = fopen("castle.obj", "r");
//   Point p;
//   Vertex v;
//   int result = parse_obj_file(&p, &v, fptr);
//   printf("RESULT OF PARSE = %d\n", result);
//   printf("POINTS = %d\n", p.point_count);
//   printf("VERTEX = %d\n", v.vertex_count);
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