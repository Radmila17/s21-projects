#include "test_s21_matrix.h"

int main() {
  run_tests();
  return 0;
}

void run_testcase(Suite *current_testcase, int *all_fails) {
  static int counter_testcase = 0;
  printf("\nCURRENT TEST: %d\n", ++counter_testcase);
  SRunner *runner = srunner_create(current_testcase);
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  *all_fails += srunner_ntests_failed(runner);
  srunner_free(runner);
}

void run_tests() {
  int all_fails = 0;

  Suite *list_cases[] = {
      suite_s21_create_delete_matrix(),
      suite_s21_sum_sub_matrix(),
      suite_s21_mult_matrix(),
      suite_s21_transpose(),
      suite_s21_eq_matrix(),
      suite_s21_calc_complements(),
      suite_s21_determinant(),
      suite_s21_inverse_matrix(),
      NULL,
  };

  for (Suite **current_suit = list_cases; *current_suit; current_suit++) {
    run_testcase(*current_suit, &all_fails);
  }
  printf("________________________________\n");
  printf("\nThe number of all fails: %d\n\n", all_fails);
}
