#include "transforms.h"

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

Suite* Create_suite() {
  Suite* suite = suite_create("Transforms test");
  TCase* tcase_core = tcase_create("Core");
  tcase_add_test(tcase_core, test_translate_matrix);

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
