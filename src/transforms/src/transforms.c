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

void rotate_matrix(float* matrix, float angel, float x, float y, float z) {
  if (!matrix) return;
  angel *= M_PI / 180;
  if (x) {
    matrix[0] = x;
    matrix[1] = 0;
    matrix[2] = 0;

    matrix[4] = 0;
    matrix[5] = cos(angel);
    matrix[6] = sin(angel);

    matrix[8] = 0;
    matrix[9] = -sin(angel);
    matrix[10] = cos(angel);

  } else if (y) {
    matrix[0] = cos(angel);
    matrix[1] = 0;
    matrix[2] = -sin(angel);

    matrix[4] = 0;
    matrix[5] = y;
    matrix[6] = 0;

    matrix[8] = sin(angel);
    matrix[9] = 0;
    matrix[10] = cos(angel);
  } else if (z) {
    matrix[0] = cos(angel);
    matrix[1] = sin(angel);
    matrix[2] = 0;

    matrix[4] = -sin(angel);
    matrix[5] = cos(angel);
    matrix[6] = 0;

    matrix[8] = 0;
    matrix[9] = 0;
    matrix[10] = z;
  }
}
