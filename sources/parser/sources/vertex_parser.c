#include "../includes/vertex_parser.h"

bool increase_vertex_row_size(Vertex* vertex, int row, int* row_capacity);
void push_digits(Vertex* vertex, int row, int* column_i, int* row_capacity,
                 char* digits);
int filling_vertex_array(int row, const char* str, Vertex* vertex);
bool move_ptr_to_next_value(const char* str, size_t* i, size_t strlen);

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

int obj_processing_by_vertex(Vertex* vertex, FILE* fptr) {
  int err_code = OK;
  if (!vertex || !fptr) return INPUT_POINTER_ERROR;
  int row_it = 0;
  char str_buff[256] = {0};
  while (fgets(str_buff, 256, fptr) && row_it < vertex->vertex_count) {
    if (str_buff[0] == VERTEX_NAME && str_buff[1] == ' ')
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
  if (vertex->vertex[row] == NULL) {
    err_code = MEMORY_ALLOCATING_ERROR;
  } else {
    str_length = strlen(str);
    for (size_t i = 0; i < str_length && !end_line_flag; i++) {
      bool is_digit = isdigit(str[i]);
      bool is_no_digits_in_buffer = (digits[0] == '\0');
      if (is_digit) strncat(digits, &str[i], 1);
      if (!is_no_digits_in_buffer) {
        end_line_flag = move_ptr_to_next_value(str, &i, str_length);
        push_digits(vertex, row, &column_iterator, &row_capacity, digits);
      }
    }
    if (column_iterator < 3) err_code = OBJ_FILE_ERROR;
  }
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

