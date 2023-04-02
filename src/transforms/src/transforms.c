#include "transforms.h"

void translate_matrix(float* matrix, float x, float y, float z) {
    if (!matrix) return;
    matrix[12] += x;
    matrix[13] += y;
    matrix[14] += z;
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
