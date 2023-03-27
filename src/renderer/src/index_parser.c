#include "../includes/vertex_parser.h"

#define START_ARRAY_SIZE 10

_bool increase_index_arr_size(Indexes* indexes, int new_size);
void push_digits(Indexes* indexes, int* capacity, char* digits);
int filling_index_array(const char* str, Indexes* indexes, int* capacity);
_bool move_ptr_to_next_value(const char* str, size_t* i, size_t strlen);

int allocate_indexes_memory(Indexes* indexes) {
  int err_code = OK;
  if (!indexes) return INPUT_POINTER_ERROR;
  indexes->indexes = (int*)calloc(START_ARRAY_SIZE, sizeof(int));
  if (indexes->indexes == NULL) err_code = MEMORY_ALLOCATING_ERROR;
  return err_code;
}

int obj_processing_by_indexes(Indexes* indexes, FILE* fptr) {
  if (!indexes || !fptr) return INPUT_POINTER_ERROR;
  int err_code = OK;
  indexes->index_count = 0;
  int arr_capacity = START_ARRAY_SIZE;
  char str_buff[256] = {0};
  while (fgets(str_buff, 256, fptr)) {
    if (str_buff[0] == INDEX_NAME && str_buff[1] == ' ')
      err_code = filling_index_array(str_buff, indexes, &arr_capacity);
  }
  return err_code;
}

_bool increase_index_arr_size(Indexes* indexes, int new_size) {
  indexes->indexes = (int*)realloc(indexes->indexes, sizeof(int) * new_size);
  return _true;
}

void push_digits(Indexes* indexes, int* capacity, char* digits) {
  if (indexes->index_count == (*capacity))
    increase_index_arr_size(indexes, (*capacity *= 1.5));
  indexes->indexes[indexes->index_count++] = atoi(digits);
  memset(digits, '\0', 16);
}

int filling_index_array(const char* str, Indexes* indexes, int* capacity) {
  int err_code = OK;
  int end_line_flag = 0;
  int column_iterator = 0;
  char digits[32] = {0};
  size_t str_length = 0;
  str_length = strlen(str);
  for (size_t i = 0; i < str_length && !end_line_flag; i++) {
    _bool is_digit = isdigit(str[i]);
    _bool is_no_digits_in_buffer = (digits[0] == '\0');
    if (is_digit) strncat(digits, &str[i], 1);
    if (!is_no_digits_in_buffer) {
      end_line_flag = move_ptr_to_next_value(str, &i, str_length);
      push_digits(indexes, capacity, digits);
      column_iterator++;
    }
  }
  if (column_iterator < 3) err_code = OBJ_FILE_ERROR;
  return err_code;
}

_bool move_ptr_to_next_value(const char* str, size_t* i, size_t strlen) {
  int move_offset = -1;
  for (size_t j = *i; j < strlen && move_offset == -1; j++) {
    const char current = str[j];
    const char previous = str[j - 1];
    _bool current_is_digit = isdigit(current);
    _bool previous_is_space = (previous == ' ');
    if (current_is_digit && previous_is_space) move_offset = j - *i;
  }
  _bool i_moved = (move_offset > 0);
  if (i_moved) *i += (move_offset - 1);
  return !i_moved;
}
