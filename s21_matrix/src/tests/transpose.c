#include "test_s21_matrix.h"

START_TEST(transpose_null) {
  ck_assert_int_eq(s21_transpose(NULL, NULL), INCORRECT);
}

START_TEST(transpose_invalid_size) {
  matrix_t A = {NULL, -1, -1};
  matrix_t result;
  ck_assert_int_eq(s21_transpose(&A, &result), INCORRECT);
  matrix_t A_1 = {NULL, 1, 4};
  ck_assert_int_eq(s21_transpose(&A_1, NULL), INCORRECT);
}

START_TEST(transpose_empty) {
  matrix_t A = {0};
  matrix_t result;
  s21_create_matrix(0, 0, &A);
  ck_assert_int_eq(s21_transpose(&A, &result), INCORRECT);
  s21_remove_matrix(&A);
}

START_TEST(transpose_1x1) {
  matrix_t A = {0};
  matrix_t result;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;
  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 5.0, EPS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}

START_TEST(transpose_3x2) {
  matrix_t A = {0};
  matrix_t result;
  s21_create_matrix(3, 2, &A);
  s21_filling_matrix(&A, 1.0, 1.0);

  ck_assert_int_eq(s21_transpose(&A, &result), OK);

  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 3);
  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], 3.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][2], 5.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], 2.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], 4.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][2], 6.0, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}

START_TEST(transpose_only_row) {
  matrix_t A = {0};
  matrix_t result;
  s21_create_matrix(3, 1, &A);
  s21_filling_matrix(&A, 1.0, 1.0);
  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], 2.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][2], 3.0, EPS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}

Suite *suite_s21_transpose() {
  Suite *s = suite_create("transpose_matrix");
  TCase *tc = tcase_create("transpose_matrix");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, transpose_null);
  tcase_add_test(tc, transpose_invalid_size);
  tcase_add_test(tc, transpose_empty);
  tcase_add_test(tc, transpose_1x1);
  tcase_add_test(tc, transpose_3x2);
  tcase_add_test(tc, transpose_only_row);
  return s;
}