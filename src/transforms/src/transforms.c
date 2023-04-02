#include "transforms.h"

void translate_matrix(float* matrix, float x, float y, float z) {
  if (!matrix) return;
  matrix[12] += x;
  matrix[13] += y;
  matrix[14] += z;
}

void scale_matrix(float* matrix, float scale) {
  if (!matrix) return;
  for (int i = 0; i < 12; i++) matrix[i] *= scale;
}
