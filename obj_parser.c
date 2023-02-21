/*****************************
 *                           *
 *   .obj file parser.       *
 *   Part of 3D_Viewer.      *
 *       @Fable1336          *
 *                           *
 *****************************/

#include "obj_parser.h"

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

int allocate_point_memory(Point* points) {
  int err_code = OK;
  if (!points) return INPUT_POINTER_ERROR;
  if ((points->poses = (float**)calloc(points->point_count, sizeof(float*))) ==
      NULL)
    err_code = MEMORY_ALLOCATING_ERROR;
  if (err_code == OK) {
    for (int i = 0; i < points->point_count; i++) {
      if ((points->poses[i] = (float*)calloc(3, sizeof(float))) == NULL)
        err_code = MEMORY_ALLOCATING_ERROR;
    }
  }
  return err_code;
}

int allocate_vertex_memory(Vertex* vertex) {
  int err_code = OK;
  if (!vertex) return INPUT_POINTER_ERROR;
  vertex->vertex = (int**)calloc(vertex->vertex_count, sizeof(int*));
  if (vertex->vertex == NULL) err_code = MEMORY_ALLOCATING_ERROR;
  if (err_code == OK)
    vertex->each_row_vertexes = (int*)calloc(vertex->vertex_count, sizeof(int));
  if (vertex->each_row_vertexes == NULL) err_code = MEMORY_ALLOCATING_ERROR;
  return err_code;
}

int obj_proccesing_by_point(Point* points, FILE* fptr) {
  int err_code = OK;
  if (!points || !fptr) return INPUT_POINTER_ERROR;
  int row = 0;
  char str_buffer[256] = {0};
  while (!err_code && fgets(str_buffer, 256, fptr) && *str_buffer != 'f') {
    if (str_buffer[0] == POINT_NAME)
      err_code = filling_point_array(row++, str_buffer, points);
  }
  if (err_code) printf("Yes");
  rewind(fptr);
  return err_code;
}

int filling_point_array(int row, const char* str, Point* points) {
  int err_code = OK;
  int column = 0;
  char number_buffer[16] = {0};
  size_t str_length = strlen(str);
  for (size_t i = 0; i < str_length; i++) {
    if (is_digit_part(str[i])) {
      strncat(number_buffer, &str[i], 1);
    } else if (!is_string_empty(number_buffer)) {
      if (column < 3) points->poses[row][column++] = (float)atof(number_buffer);
      memset(number_buffer, '\0', 16);
    }
  }
  if (column < 3) err_code = OBJ_FILE_ERROR;
  return err_code;
}

int is_digit_part(const int c) {
  int result = 0;
  if (isdigit(c) || c == '.' || c == '-') result = 1;
  return result;
}

int is_string_empty(const char* str) {
  int result = 1;
  if (str[0] != '\0') result = 0;
  return result;
}

int obj_processing_by_vertex(Vertex* vertex, FILE* fptr) {
  int err_code = OK;
  if (!vertex || !fptr) return INPUT_POINTER_ERROR;
  int row_it = 0;
  char str_buff[256] = {0};
  while (fgets(str_buff, 256, fptr) && row_it < vertex->vertex_count) {
    if (str_buff[0] == VERTEX_NAME)
      err_code = filling_vertex_array(row_it++, str_buff, vertex);
  }
  return err_code;
}
bool increase_vertex_row_size(Vertex* vertex, int row, int* row_capacity) {
  *row_capacity *= 2;
  vertex->vertex[row] =
      (int*)realloc(vertex->vertex[row], sizeof(int) * (*row_capacity));
}
void push_digits(Vertex* vertex, int row, int* column_i, int* row_capacity,
                 char* digits) {
  if (*column_i == *row_capacity)
    increase_vertex_row_size(vertex, row, row_capacity);
  vertex->vertex[row][*column_i] = atoi(digits);
  (*column_i)++;
  vertex->each_row_vertexes[row]++;
  memset(digits, '\0', 16);
}
int filling_vertex_array(int row, const char* str, Vertex* vertex) {
  int err_code = OK;
  int end_line_flag = 0;
  int row_capacity = 3;
  int column_iterator = 0;
  int offset = 0;

  char digits[32] = {0};

  size_t str_length = 0;

  vertex->vertex[row] = (int*)calloc(row_capacity, sizeof(int));
  str_length = strlen(str);

  for (size_t i = 0; i < str_length && !end_line_flag; i++) {
    bool is_digit = isdigit(str[i]);
    bool is_no_digits_in_buffer = is_string_empty(digits);

    if (is_digit) strncat(digits, &str[i], 1);
    if (!is_no_digits_in_buffer) {
      end_line_flag = move_ptr_to_next_value(str, &i, str_length);
      push_digits(vertex, row, &column_iterator, &row_capacity, digits);
    }
  }
  if (column_iterator < 3) err_code = OBJ_FILE_ERROR;
  return err_code;
}

bool move_ptr_to_next_value(const char* str, size_t* i, size_t strlen) {
  int move_offset = -1;
  for (size_t j = *i; j < strlen && move_offset == -1; j++) {
    const char current = str[j];
    const char previous = str[j - 1];

    bool current_is_digit = isdigit(current);
    bool previous_is_space = (previous == ' ');

    if (current_is_digit && previous_is_space) move_offset = j - *i;
  }
  bool i_moved = (move_offset > 0);
  if (i_moved) *i += (move_offset - 1);
  return !i_moved;
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

int main(void) {
  double time_spent = 0.0;
  clock_t begin = clock();
  FILE* fptr = fopen("1.obj", "r");
  Point p;
  Vertex v;
  int result = parse_obj_file(&p, &v, fptr);
  printf("%i\n", result);
  if (!result) {
    for (int i = 0; i < p.point_count; i++) {
      printf("%d.\t\t", i);
      for (int j = 0; j < 3; j++) {
        printf("%f ", p.poses[i][j]);
      }
      printf("\n");
    }
    printf("\n\n");
    for (int i = 0; i < v.vertex_count; i++) {
      printf("%d.\t\t", i);
      if (v.each_row_vertexes != NULL) {
        for (int j = 0; j < v.each_row_vertexes[i]; j++) {
          printf("%d ", v.vertex[i][j]);
        }
      }
      printf("\n");
    }
  }
  switch (result) {
    case 0:
      printf("SUCCESS\n");
      break;
    case 1:
      printf("OBJ FILE ERROR\n");
      break;
    case 2:
      printf("POINTER ERROR\n");
      break;
    case 3:
      printf("MEMORY ALLOCATING ERROR\n");
      break;
    case 4:
      printf("NO FILE\n");
      break;
  }
  free_structs(&p, &v);
  if (fptr) fclose(fptr);
  clock_t end = clock();
  time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
  printf("The elapsed time is %f seconds", time_spent);

  return 0;
}