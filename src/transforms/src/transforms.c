#include "transforms.h"

void translate_matrix(float* matrix, float x, float y, float z) {
    if (!matrix) return;
    matrix[12] += x;
    matrix[13] += y;
    matrix[14] += z;
}

void rotate_matrix(float* matrix, float angle, float x, float y, float z) {
   if (!matrix) return;
   angle *= M_PI/180;
   float c = cos(angle);
   float s = sin(angle);
   float len = sqrt(x * x + y * y + z * z);

   if (len != 0.0) {
       x /= len;
       y /= len;
       z /= len;
   }

   float nc = 1.0 - c;
   float xy = x * y;
   float yz = y * z;
   float zx = z * x;
   float xs = x * s;
   float ys = y * s;
   float zs = z * s;

   float rmat[16] = {
       x*x*nc + c,  xy*nc - zs, zx*nc + ys, 0.0,
       xy*nc + zs,  y*y*nc + c, yz*nc - xs, 0.0,
       zx*nc - ys,  yz*nc + xs, z*z*nc + c, 0.0,
       0.0,         0.0,        0.0,        1.0
   };

   float rotation_matrix[16] = { 0 };

   for (int i = 0; i < 16; i++) {
       rotation_matrix[i] = rmat[i];
   }

   float result[16] = { 0 };

   mul_matrix(result, matrix, rotation_matrix);
   for (int i = 0; i < 16; i++) {
     matrix[i] = result[i];
   }
}

void scale_matrix(float* matrix, float scale) {
    if (!matrix) return;
    for (int i = 0; i < 12; i++)
        matrix[i] *= scale;
}

void mul_matrix(float* result, float a[16], float b[16]) {
    if (!result) return;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float sum = 0.0f;
            for (int k = 0; k < 4; k++) {
                sum += a[k + j * 4] * b[i + k * 4];
            }
            result[i + j * 4] = sum;
        }
    }
}
