/*****************************
 *                           *
 *   .obj file parser.       *
 *   Part of 3D_Viewer.      *
 *       @simphoniia         *
 *                           *
 *****************************/

#include "../includes/obj_parser.h"

#include "../includes/sub_functions.h"

int parse_obj_file(Scene* scene, const char* filename) {
  if (!scene) return INPUT_POINTER_ERROR;
  initialize_scene(scene);
  FILE* fptr = open_file(filename);
  if (!fptr) return NO_FILE;
  int retval = OK;

  retval = allocate_structs_memory(scene);
  if (!retval) retval = fill_array(scene, fptr);
  if (!retval) scene->objects_count++;
  fclose(fptr);
  return retval;
}

void initialize_scene(Scene* scene) {
  scene->objects_count = 0;
  scene->vertices_count = 0;
  scene->objects = NULL;
  scene->vertices = NULL;
}

FILE* open_file(const char* filename) {
  FILE* fptr = fopen(filename, "r");
  return fptr;
}

int allocate_structs_memory(Scene* scene) {
  if (!scene) return INPUT_POINTER_ERROR;
  int allocate_state = OK;

  if ((scene->vertices = (Vertex*)calloc(START_SIZE, sizeof(Vertex))) == NULL)
    allocate_state = MEMORY_ALLOCATING_ERROR;
  if (!allocate_state &&
      (scene->objects = (Object*)calloc(1, sizeof(Object))) == NULL)
    allocate_state = MEMORY_ALLOCATING_ERROR;
  if (!allocate_state && (scene->objects[0].faces =
                              (Face*)calloc(START_SIZE, sizeof(Face))) == NULL)
    allocate_state = MEMORY_ALLOCATING_ERROR;
  if (!allocate_state) scene->objects[0].num_faces = 0;

  return allocate_state;
}

int fill_array(Scene* scene, FILE* fptr) {
  if (!scene || !fptr) return INPUT_POINTER_ERROR;
  int retval = OK;
  int group = 0;
  char current_str[256] = {0};

  int vertices_capacity = START_SIZE;
  int faces_capacity = START_SIZE;

  _bool is_space = 0;

  rewind(fptr);
  while (fgets(current_str, 256, fptr) && retval == OK) {
    is_space = (current_str[1] == ' ');
    if (current_str[0] == VERTEX_NAME && is_space)
      retval = push_vertices(current_str, scene, &vertices_capacity);
    else if (current_str[0] == INDEX_NAME && is_space)
      retval = push_faces(current_str, scene, group, &faces_capacity);
    else if (current_str[0] == GROUP_NAME_ &&
             (is_space || current_str[1] == '\n')) {
      retval = group_processing(&group, scene, &faces_capacity);
    }
  }

  return retval;
}

int group_processing(int* group, Scene* scene, int* faces_capacity) {
  if (!group || !scene || !faces_capacity) return INPUT_POINTER_ERROR;
  if (*group == scene->objects_count && scene->objects[*group].num_faces > 0) {
    (*group)++;
    *faces_capacity = START_SIZE;
  }
  return OK;
}

int push_vertices(const char* str, Scene* scene, int* capacity) {
  if (!str || !scene) return INPUT_POINTER_ERROR;
  int retval = OK;
  if (scene->vertices_count == ((*capacity) - 1)) {
    (*capacity) *= MULTIPLY_FACTOR;
    if ((scene->vertices = (Vertex*)realloc(
             scene->vertices, sizeof(Vertex) * (*capacity))) == NULL)
      retval = MEMORY_ALLOCATING_ERROR;
  }
  if (!retval) {
    if (sscanf(str, "v %f %f %f", &scene->vertices[scene->vertices_count].x,
               &scene->vertices[scene->vertices_count].y,
               &scene->vertices[scene->vertices_count].z) != 3)
      retval = OBJ_FILE_ERROR;
  }
  if (!retval) scene->vertices_count++;
  return retval;
}

int push_faces(const char* str, Scene* scene, int group, int* capacity) {
  int retval = OK;
  int counter = 0;
  int values[10] = {0};
  _bool is_need_reallocate = _false;

  fill_array_values_from_str(values, str, &counter);

  if (group > scene->objects_count) create_new_object(scene, group);

  if (!retval) {
    int* face_index = &scene->objects[group].num_faces;
    for (int i = 0; i < counter - 2; i++) {
      is_need_reallocate = (*face_index == (*capacity) - 1);
      if (is_need_reallocate) retval = reallocate_faces(scene, group, capacity);
      push_face_value(scene, *face_index, values, i);
      (*face_index)++;
    }
  }
  return retval;
}

int create_new_object(Scene* scene, int group) {
  int retval = OK;
  if ((scene->objects = (Object*)realloc(scene->objects,
                                         sizeof(Object) * (group + 1))) == NULL)
    retval = MEMORY_ALLOCATING_ERROR;
  if (!retval) {
    if ((scene->objects[group].faces =
             (Face*)calloc(START_SIZE, sizeof(Face))) == NULL)
      retval = MEMORY_ALLOCATING_ERROR;
    if (!retval) {
      scene->objects[group].num_faces = 0;
      scene->objects_count++;
    }
  }
  return retval;
}

int reallocate_faces(Scene* scene, int group, int* capacity) {
  int retval = OK;
  (*capacity) *= MULTIPLY_FACTOR;
  if ((scene->objects[group].faces = realloc(
           scene->objects[group].faces, sizeof(Face) * (*capacity))) == NULL)
    retval = MEMORY_ALLOCATING_ERROR;
  return retval;
}

void fill_array_values_from_str(int* dest, const char* str, int* arr_size) {
  if (!str || !arr_size) return;
  int offset = 1;
  int counter = 0;
  int i = 0;
  char num_buff[12] = {0};
  while (offset) {
    for (; str[i] != '\0' && is_digit(str[i]); i++) {
      strncat(num_buff, &str[i], 1);
    }
    if (*num_buff != '\0' && counter < 10) dest[counter++] = atoi(num_buff);
    offset = move_to_next_value(str, i);
    i += offset;
    memset(num_buff, '\0', 12);
  }
  *arr_size = counter;
}

void push_face_value(Scene* scene, int face_index, int* values, int i) {
  scene->objects[scene->objects_count].faces[face_index].index[0] = values[0];
  scene->objects[scene->objects_count].faces[face_index].index[1] =
      values[i + 1];
  scene->objects[scene->objects_count].faces[face_index].index[2] =
      values[i + 2];
}

int move_to_next_value(const char* str, size_t i) {
  int offset = 0;
  size_t start_position = i;
  int is_current_digit = 0;
  int is_past_space = 0;
  for (; str[i] != '\0' && !offset; i++) {
    is_current_digit = is_digit(str[i]);
    if (i > 0) is_past_space = (str[i - 1] == ' ');
    if (is_current_digit && is_past_space) {
      offset = i - start_position;
    }
  }
  return offset;
}

int is_digit(const char symb) {
  int retval = 0;
  if (symb >= '0' && symb <= '9') retval = 1;
  if (symb == '.') retval = 1;
  return retval;
}

void free_structs(Scene* scene) {
  if (!scene) return;

  if (scene->vertices) free(scene->vertices);

  if (scene->objects) {
    for (int i = 0; i < scene->objects_count; i++) {
      if (scene->objects[i].faces) free(scene->objects[i].faces);
    }
    free(scene->objects);
  }
}
