#include "test_s21_decimal.h"

int main() {
  run_tests();
  return 0;
}

void run_testcase(Suite *current_testcase, int *all_fails) {
  static int counter_testcase = 0;
  printf("\nCURRENT TEST: %d\n", ++counter_testcase);
  SRunner *runner = srunner_create(current_testcase);
  srunner_run_all(runner, CK_NORMAL);
  *all_fails += srunner_ntests_failed(runner);
  srunner_free(runner);
}

void run_tests() {
  int all_fails = 0;

  Suite *list_cases[] = {
      suite_s21_add(),   suite_s21_comparison(),
      suite_s21_div(),   suite_s21_sub(),
      suite_s21_mul(),   suite_s21_conversion(),
      suite_s21_other(), NULL,
  };

  for (Suite **current_testcase = list_cases; *current_testcase;
       current_testcase++) {
    run_testcase(*current_testcase, &all_fails);
  }
  printf("________________________________\n");
  printf("\nThe number of all fails: %d\n\n", all_fails);
}