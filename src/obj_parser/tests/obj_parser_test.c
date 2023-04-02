#include <stdlib.h>

#include "obj_parser.h"
#include "parser_types.h"
#include "check.h"

START_TEST(vertex_test)
{
    Scene scene;
    parse_obj_file(&scene, "./tests/tests_files/vertex_test.txt");
    ck_assert_int_eq(scene.vertices_count, 1000000);
    free_structs(&scene);
}
END_TEST

START_TEST(group_test)
{
    Scene scene;
    parse_obj_file(&scene, "./tests/tests_files/group_test.txt");
    ck_assert_int_eq(scene.objects_count, 4);
    free_structs(&scene);
}
END_TEST

START_TEST(long_index_test)
{
    Scene scene;
    parse_obj_file(&scene, "./tests/tests_files/long_index_test.txt");
    ck_assert_int_eq(scene.objects[0].num_faces, 7);
    ck_assert_int_eq(scene.objects[1].num_faces, 7);

    int tmp_value = 2;

    for (int i = 0; i < 7; i++) {
        ck_assert_int_eq(scene.objects[0].faces[i].index[0], 1);
        ck_assert_int_eq(scene.objects[0].faces[i].index[1], tmp_value);
        ck_assert_int_eq(scene.objects[0].faces[i].index[2], ++tmp_value);
    }

    tmp_value = 20;

    for (int i = 0; i < 7; i++) {
        ck_assert_int_eq(scene.objects[1].faces[i].index[0], 10);
        ck_assert_int_eq(scene.objects[1].faces[i].index[1], tmp_value);
        ck_assert_int_eq(scene.objects[1].faces[i].index[2], (tmp_value += 10));
    }

    free_structs(&scene);
}
END_TEST

Suite* Create_suite() {
  Suite* suite = suite_create("Parser test");
  TCase* tcase_core = tcase_create("Core");

  tcase_add_test(tcase_core, vertex_test);
  tcase_add_test(tcase_core, group_test);
  tcase_add_test(tcase_core, long_index_test);

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
