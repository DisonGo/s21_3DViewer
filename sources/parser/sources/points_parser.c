#include "../includes/points_parser.h"

int filling_point_array(int row, const char* str, Point* points);
int is_digit_part(const int c);
int is_string_empty(const char* str);

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

int obj_proccesing_by_point(Point* points, FILE* fptr) {
  int err_code = OK;
  if (!points || !fptr) return INPUT_POINTER_ERROR;
  int row = 0;
  char str_buffer[256] = {0};
  while (!err_code && fgets(str_buffer, 256, fptr)) {
    if (str_buffer[0] == POINT_NAME && str_buffer[1] == ' ')
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