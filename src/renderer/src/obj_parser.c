/*****************************
 *                           *
 *   .obj file parser.       *
 *   Part of 3D_Viewer.      *
 *       @simphoniia         *
 *                           *
 *****************************/

#include "obj_parser.h"

int parse_obj_file(Scene* scene, FILE* fptr) {
  if (!scene) return INPUT_POINTER_ERROR;
  initialize_scene(scene);
  if (!fptr) return NO_FILE;
  int retval = OK;

  retval = allocate_structs_memory(scene);
  if (!retval) retval = fill_array(scene, fptr);
  if (!retval) scene->objects_count++;
  return retval;
}

void initialize_scene(Scene* scene) {
  scene->objects_count = 0;
  scene->vertices_count = 0;
  scene->objects = NULL;
  scene->vertices = NULL;
}

int allocate_structs_memory(Scene* scene) {
  if (!scene) return INPUT_POINTER_ERROR;
  int retval = OK;
  scene->vertices = calloc(START_SIZE, sizeof(Vertex));
  if (!scene->vertices) retval = MEMORY_ALLOCATING_ERROR;
  if (!retval) scene->objects = calloc(1, sizeof(Object));
  if (!scene->objects) retval = MEMORY_ALLOCATING_ERROR;
  if (!retval) scene->objects[0].faces = calloc(START_SIZE, sizeof(Face));
  if (!scene->objects[0].faces) retval = MEMORY_ALLOCATING_ERROR;
  if (!retval) scene->objects[0].num_faces = 0;

  return retval;
}

int fill_array(Scene* scene, FILE* fptr) {
  if (!scene || !fptr) return INPUT_POINTER_ERROR;
  int retval = OK;
  int group = 0;
  char current_str[256] = { 0 };

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
    else if (current_str[0] == GROUP_NAME_ && is_space) {
        printf("num_faces = %d\n", scene->objects[group].num_faces);
        if (scene->objects[scene->objects_count].num_faces > 0) {
          group++;
          faces_capacity = START_SIZE;
        }
    }
  }
  return retval;
}

int push_vertices(const char* str, Scene* scene, int* capacity) {
  if (!str || !scene) return INPUT_POINTER_ERROR;
  int retval = OK;
  if (scene->vertices_count == ((*capacity) - 1)) {
    (*capacity) *= MULTIPLY_FACTOR;
    scene->vertices = realloc(scene->vertices, sizeof(Vertex) * (*capacity));
    if (!scene->vertices) retval = MEMORY_ALLOCATING_ERROR;
  }
  if (!retval) {
    if (sscanf(str, "v %f %f %f", &scene->vertices[scene->vertices_count].x,
                                  &scene->vertices[scene->vertices_count].y,
                                  &scene->vertices[scene->vertices_count].z) != 3) retval = OBJ_FILE_ERROR;
  }
  if (!retval)
    scene->vertices_count++;
  return retval;
}

int push_faces(const char* str, Scene* scene, int group, int* capacity) {
  int retval = OK;
  int offset = 1;
  size_t i = 0;
  int counter = 0;
  char num_buff[8] = { 0 };
  int values[10] = { 0 };
  while (offset) {
      for (; str[i] != '\0' && is_digit(str[i]); i++) {
          strncat(num_buff, &str[i], 1);
      }
      if (*num_buff != '\0') 
        values[counter++] = atoi(num_buff);
      offset = move_to_next_value(str, i);
      i += offset;
      memset(num_buff, '\0', 8);
  }

  if (group > scene->objects_count) {
    scene->objects_count++;
    scene->objects = realloc(scene->objects, sizeof(Object) * group + 1);
    scene->objects[group].faces = calloc(START_SIZE, sizeof(Face));
    scene->objects[group].num_faces = 0;
  }


  int* face_index = &scene->objects[group].num_faces;

  for (int i = 0; i < counter - 2; i++) {
      if (*face_index == (*capacity) - 1) {
        (*capacity) *= MULTIPLY_FACTOR;
        scene->objects[group].faces = realloc(scene->objects[group].faces, 
                                              sizeof(Face) * (*capacity));

      }
      scene->objects[group].faces[*face_index].index[0] = values[0];
      scene->objects[group].faces[*face_index].index[1] = values[i + 1];
      scene->objects[group].faces[*face_index].index[2] = values[i + 2];

      (*face_index)++;
  }
  return retval;
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
  
  if (scene->vertices)
    free(scene->vertices);

  for (int i = 0; i < scene->objects_count; i++) {
    if (scene->objects[i].faces)
      free(scene->objects[i].faces);
  }
  
  free(scene->objects);
}

// int main() {
//   Scene scene;
//   FILE* fptr = fopen("test.txt", "r");
//   int result = parse_obj_file(&scene, fptr);

//   unsigned sum_of_faces = 0;

//   printf("VERTICES_COUNT = %d\n", scene.vertices_count);
//   printf("GROUP_COUNT = %d\n", scene.objects_count);
//   for (int i = 0; i < scene.objects_count; i++) {
//     sum_of_faces += scene.objects[i].num_faces;
//   }
//   printf("FACES_COUNT = %d\n", sum_of_faces);

//   if (fptr)
//     fclose(fptr);

//   // printf("VERTICES ============ \n");

//   // for (int i = 0; i < scene.vertices_count; i++) {
//   //   float x = scene.vertices[i].x;
//   //   float y = scene.vertices[i].y;
//   //   float z = scene.vertices[i].z;
//   //   printf("%d. %f %f %f\n", i + 1, x, y, z);
//   // }

//   printf("\nFACES ============ \n");

//   for (int i = 0; i < scene.objects_count; i++) {
//     printf("group #%d\n", i);
//     for (int j = 0; j < scene.objects[i].num_faces; j++) {
//       for (int k = 0; k < 3; k++) {
//         printf("%d ", scene.objects[i].faces[j].index[k]);
//       }
//       printf("\n");
//     }
//   }


//   if (!result)
//     printf("\nSUCCESS!\n");
//   else
//     printf("\nERROR! ! ! CODE OF ERROR IS 0x%d\n", result);

//   free_structs(&scene);
//   return 0;
// }
