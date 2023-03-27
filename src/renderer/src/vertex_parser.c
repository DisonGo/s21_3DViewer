#include "../includes/vertex_parser.h"

int filling_vertex_array(const char* str, Vertexes* vertexes);
int is_digit_part(const int c);
int is_string_empty(const char* str);

int allocate_vertex_memory(Vertexes* vertexes) {
  int err_code = OK;
  if (!vertexes) return INPUT_POINTER_ERROR;
  if ((vertexes->vertex =
           (float*)calloc(vertexes->point_count * 3, sizeof(float))) == NULL)
    err_code = MEMORY_ALLOCATING_ERROR;
  if (!err_code) vertexes->point_count = 0;
  return err_code;
}

int obj_proccesing_by_vertex(Vertexes* vertexes, FILE* fptr) {
  int err_code = OK;
  if (!vertexes || !fptr) return INPUT_POINTER_ERROR;
  char str_buffer[256] = {0};
  while (!err_code && fgets(str_buffer, 256, fptr)) {
    if (str_buffer[0] == VERTEX_NAME && str_buffer[1] == ' ')
      err_code = filling_vertex_array(str_buffer, vertexes);
  }
  rewind(fptr);
  return err_code;
}

int filling_vertex_array(const char* str, Vertexes* vertexes) {
  int err_code = OK;
  int column = 0;
  char number_buffer[16] = {0};
  size_t str_length = strlen(str);
  for (size_t i = 0; i < str_length; i++) {
    if (is_digit_part(str[i])) {
      strncat(number_buffer, &str[i], 1);
    } else if (!is_string_empty(number_buffer)) {
      if (column < 3)
        vertexes->vertex[vertexes->point_count++] = (float)atof(number_buffer);
      column++;
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