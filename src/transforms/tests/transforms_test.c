#include <stdio.h>
#include <stdlib.h>

#include "transforms.h"
#include "check.h"

START_TEST(test_mul_matrix_associativity_one)
{
    float a[16] = { 0 };
    float b[16] = { 0 };
    float c[16] = { 0 };
    float result1[16] = { 0 };
    float result2[16] = { 0 };

    for (int i = 0; i < 16; i++) {
        a[i] = (float)rand() / (float)RAND_MAX;
        b[i] = (float)rand() / (float)RAND_MAX;
        c[i] = (float)rand() / (float)RAND_MAX;
    }

    // (A * B) * C = A * (B * C)
    mul_matrix(result1, a, b);
    mul_matrix(result1, result1, c);

    mul_matrix(result2, b, c);
    mul_matrix(result2, a, result2);

    for (int i = 0; i < 16; i++) {
        ck_assert_float_eq_tol(result1[i], result2[i], 1e-4);
    }
}
END_TEST

START_TEST(test_mul_matrix_negative)
{
    float a[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    float b[16] = {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    float expected[16] = {80, 70, 60, 50, 240, 214, 188, 162, 400, 358, 316, 274, 560, 502, 444, 386};
    float result[16] = {0};

    mul_matrix(result, a, b);

    ck_assert_mem_eq(result, expected, sizeof(expected));
}
END_TEST

START_TEST(test_translate_matrix)
{
    float matrix[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 2.0f, 3.0f, 1.0f
    };
    float expected[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        2.0f, 3.0f, 4.0f, 1.0f
    };

    translate_matrix(matrix, 1.0f, 1.0f, 1.0f);

    for (int i = 0; i < 16; i++) {
        ck_assert_float_eq_tol(matrix[i], expected[i], 1e-5);
    }
}
END_TEST

START_TEST(test_rotate_matrix)
{
    float matrix[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 2.0f, 3.0f, 1.0f
    };
    float expected[16] = {
        0.983109f, -0.034899f, 0.179046f, 0.0f,
        0.034899f, 0.999390f, 0.004524f, 0.0f,
        -0.179046f, -0.004524f, 0.983849f, 0.0f,
        1.0f, 2.0f, 3.0f, 1.0f
    };

    rotate_matrix(matrix, M_PI / 10.0f, 1.0f, 1.0f, 1.0f);

    for (int i = 0; i < 16; i++) {
        ck_assert_float_eq_tol(matrix[i], expected[i], 1e-5);
    }
}
END_TEST


Suite* Create_suite() {
  Suite* suite = suite_create("Transforms test");
  TCase* tcase_core = tcase_create("Core");

  tcase_add_test(tcase_core, test_mul_matrix_associativity_one);
  tcase_add_test(tcase_core, test_mul_matrix_negative);
  tcase_add_test(tcase_core, test_translate_matrix);
  tcase_add_test(tcase_core, test_rotate_matrix);

  suite_add_tcase(suite, tcase_core);

  return suite;
}

int main() {
  Suite* suite = Create_suite();
  SRunner* suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);
  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  if (failed_count != 0) {
    printf("ERROR: FAILED COUNT: %d\n", failed_count);
    return EXIT_FAILURE;
  } else {
    printf("INFO: ALL TESTS ARE SUCCESS\n");
  }

  return EXIT_SUCCESS;
}
