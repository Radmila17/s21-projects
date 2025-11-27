
#include "test_s21_matrix.h"

START_TEST(sum_1) {
  int my_res = s21_sum_matrix(NULL, NULL, NULL);
  ck_assert_int_eq(my_res, INCORRECT);
}

START_TEST(sum_2) {
  int rows = 3;
  int columns = 4;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(3, 5, &B);
  int res = s21_sum_matrix(&A, &B, &result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  ck_assert_int_eq(res, CALCULATION_ERROR);
}

START_TEST(sum_3) {
  int rows = 3;
  int columns = 4;
  matrix_t A = {0};
  matrix_t result = {0};
  s21_create_matrix(rows, columns, &A);
  int res = s21_sum_matrix(&A, NULL, &result);
  ck_assert_int_eq(res, INCORRECT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}

START_TEST(sum_4) {
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 5, &B);
  int res = s21_sum_matrix(NULL, &B, &result);
  ck_assert_int_eq(res, INCORRECT);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}

START_TEST(sum_5) {
  int rows = 2;
  int columns = 3;
  double start = 0;
  double step = 1;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t my_result = {0};
  matrix_t result = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(2, 3, &B);
  s21_create_matrix(rows, columns, &result);
  s21_filling_matrix(&A, 0, 1);
  s21_filling_matrix(&B, start, step);
  // s21_create_matrix(rows, columns, &my_result); verter and other users
  // shouldn't do this shouldn't do this
  int res = s21_sum_matrix(&A, &B, &my_result);
  ck_assert_int_eq(res, OK);
  result.matrix[0][0] = 0.0;
  result.matrix[0][1] = 2.0;
  result.matrix[0][2] = 4.0;
  result.matrix[1][0] = 6.0;
  result.matrix[1][1] = 8.0;
  result.matrix[1][2] = 10.0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], my_result.matrix[i][j], EPS);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&my_result);
}

START_TEST(sum_6) {
  int rows = 3;
  int columns = 4;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(2, 4, &B);
  s21_create_matrix(rows, columns, &result);
  int res = s21_sum_matrix(&A, &B, &result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  ck_assert_int_eq(res, CALCULATION_ERROR);
}

START_TEST(sum_7) {
  int rows = 3;
  int columns = 4;
  matrix_t A = {0};
  s21_create_matrix(rows, columns, &A);
  matrix_t B = {0};
  s21_create_matrix(rows, columns, &B);
  int res = s21_sum_matrix(&B, &A, NULL);
  ck_assert_int_eq(res, INCORRECT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(sub_1) {
  int my_res = s21_sub_matrix(NULL, NULL, NULL);
  ck_assert_int_eq(my_res, INCORRECT);
}

START_TEST(sub_2) {
  int rows = 3;
  int columns = 4;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(3, 5, &B);
  int res = s21_sub_matrix(&A, &B, &result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  ck_assert_int_eq(res, CALCULATION_ERROR);
}

START_TEST(sub_3) {
  int rows = 3;
  int columns = 4;
  matrix_t A = {0};
  matrix_t result = {0};
  s21_create_matrix(rows, columns, &A);
  int res = s21_sub_matrix(&A, NULL, &result);
  ck_assert_int_eq(res, INCORRECT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}

START_TEST(sub_4) {
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 5, &B);
  int res = s21_sub_matrix(NULL, &B, &result);
  ck_assert_int_eq(res, INCORRECT);
  s21_remove_matrix(&B);
}

START_TEST(sub_5) {
  int rows = 2;
  int columns = 3;
  double start = 0;
  double step = 1;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t my_result = {0};
  matrix_t result = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(2, 3, &B);
  s21_create_matrix(rows, columns, &result);
  s21_filling_matrix(&A, 0, 1);
  s21_filling_matrix(&B, start, step);
  int res = s21_sub_matrix(&A, &B, &my_result);
  ck_assert_int_eq(res, OK);
  result.matrix[0][0] = 0.0;
  result.matrix[0][1] = 0.0;
  result.matrix[0][2] = 0.0;
  result.matrix[1][0] = 0.0;
  result.matrix[1][1] = 0.0;
  result.matrix[1][2] = 0.0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], my_result.matrix[i][j], EPS);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&my_result);
}

START_TEST(sub_6) {
  int rows = 3;
  int columns = 4;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(2, 4, &B);
  s21_create_matrix(rows, columns, &result);
  int res = s21_sub_matrix(&A, &B, &result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  ck_assert_int_eq(res, CALCULATION_ERROR);
}

START_TEST(sub_7) {
  int rows = 3;
  int columns = 4;
  matrix_t A = {0};
  s21_create_matrix(rows, columns, &A);
  matrix_t B = {0};
  s21_create_matrix(rows, columns, &B);
  int res = s21_sub_matrix(&B, &A, NULL);
  ck_assert_int_eq(res, INCORRECT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

Suite *suite_s21_sum_sub_matrix() {
  Suite *s = suite_create("sum_sub_matrix");
  TCase *tc = tcase_create("sum_sub_matrix");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, sum_1);
  tcase_add_test(tc, sum_2);
  tcase_add_test(tc, sum_3);
  tcase_add_test(tc, sum_4);
  tcase_add_test(tc, sum_5);
  tcase_add_test(tc, sum_6);
  tcase_add_test(tc, sum_7);
  tcase_add_test(tc, sub_1);
  tcase_add_test(tc, sub_2);
  tcase_add_test(tc, sub_3);
  tcase_add_test(tc, sub_4);
  tcase_add_test(tc, sub_5);
  tcase_add_test(tc, sub_6);
  tcase_add_test(tc, sub_7);

  return s;
}