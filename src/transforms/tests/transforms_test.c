#include "transforms.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "check.h"

START_TEST(test_translate_matrix) {
  float matrix[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 2.0f, 3.0f, 1.0f};
  float expected[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 3.0f, 4.0f, 1.0f};

  translate_matrix(matrix, 1.0f, 1.0f, 1.0f);

  for (int i = 0; i < 16; i++) {
    ck_assert_float_eq_tol(matrix[i], expected[i], 1e-5);
  }
}
END_TEST

START_TEST(test_transform_matrix) {
  float matrix[16] = {1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f,
                      5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f, 8.0f, 8.5f};
  float expected_matrix[16] = {2.0f, 3.0f, 4.0f,  5.0f,  6.0f,  7.0f,
                               8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f,
                               7.0f, 7.5f, 8.0f,  8.5f};

  scale_matrix(matrix, 2);
  for (int i = 0; i < 16; i++) {
    ck_assert_float_eq_tol(matrix[i], expected_matrix[i], 1e-3);
  }
}
END_TEST

START_TEST(test_rotate_matrix) {
  float matrix[16] = {0};
  float angel = 90;
  float translated_angel = angel * M_PI / 180;
  float expected_matrix_x[16] = {1,
                                 0,
                                 0,
                                 0,
                                 0,
                                 cos(translated_angel),
                                 sin(translated_angel),
                                 0,
                                 0,
                                 -sin(translated_angel),
                                 cos(translated_angel),
                                 0,
                                 0,
                                 0,
                                 0,
                                 0};
  float expected_matrix_y[16] = {
      cos(translated_angel), 0, -sin(translated_angel), 0, 0, 1, 0, 0,
      sin(translated_angel), 0, cos(translated_angel),  0, 0, 0, 0, 0};
  float expected_matrix_z[16] = {cos(translated_angel),
                                 sin(translated_angel),
                                 0,
                                 0,
                                 -sin(translated_angel),
                                 cos(translated_angel),
                                 0,
                                 0,
                                 0,
                                 0,
                                 1,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0};

  rotate_matrix(matrix, angel, 1, 0, 0);
  for (int i = 0; i < 16; i++)
    ck_assert_float_eq(matrix[i], expected_matrix_x[i]);

  rotate_matrix(matrix, angel, 0, 1, 0);
  for (int i = 0; i < 16; i++)
    ck_assert_float_eq(matrix[i], expected_matrix_y[i]);

  rotate_matrix(matrix, angel, 0, 0, 1);
  for (int i = 0; i < 16; i++)
    ck_assert_float_eq(matrix[i], expected_matrix_z[i]);
}
END_TEST

Suite* Create_suite() {
  Suite* suite = suite_create("Transforms test");
  TCase* tcase_core = tcase_create("Core");
  tcase_add_test(tcase_core, test_translate_matrix);
  tcase_add_test(tcase_core, test_transform_matrix);
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
