#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include <math.h>

void translate_matrix(float* matrix, float x, float y, float z);
void rotate_matrix(float* matrix, float angle, float x, float y, float z);
void scale_matrix(float* matrix, float scale);
void mul_matrix(float* result, const float* a, const float* b);

#endif  //  TRANSFORMS_H
