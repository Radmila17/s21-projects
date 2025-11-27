#include "test_s21_matrix.h"

START_TEST(det_null) {
  double result;
  ck_assert_int_eq(s21_determinant(NULL, &result), INCORRECT);
  matrix_t A = {0};
  s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(s21_determinant(&A, NULL), INCORRECT);
  s21_remove_matrix(&A);
}

START_TEST(det_not_square) {
  matrix_t A = {0};
  double result;
  s21_create_matrix(2, 3, &A);
  ck_assert_int_eq(s21_determinant(&A, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
START_TEST(det_1x1) {
  matrix_t A = {0};
  double result;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;
  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq_tol(result, 5.0, EPS);
  s21_remove_matrix(&A);
}

START_TEST(det_2x2) {
  matrix_t A = {0};
  double result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq_tol(result, -2.0, EPS);
  s21_remove_matrix(&A);
}

START_TEST(det_3x3) {
  matrix_t A = {0};
  double result;
  s21_create_matrix(3, 3, &A);
  double values[3][3] = {{2, 4, 1}, {0, 3, -1}, {1, 2, 0}};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) A.matrix[i][j] = values[i][j];

  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq_tol(result, -3, EPS);
  s21_remove_matrix(&A);
}

START_TEST(det_zero) {
  matrix_t A = {0};
  double result = 0;
  s21_create_matrix(3, 3, &A);
  double values[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) A.matrix[i][j] = values[i][j];

  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq_tol(result, 0.0, 1e-6);
  s21_remove_matrix(&A);
}

START_TEST(det_4x4) {
  matrix_t A = {0};
  double result = 0;
  s21_create_matrix(4, 4, &A);
  double values[4][4] = {
      {2, 4, 1, 1}, {0, 3, -1, 1}, {1, 2, 0, 1}, {3, 4, 5, 6}};
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) A.matrix[i][j] = values[i][j];

  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq_tol(result, -24, EPS);
  s21_remove_matrix(&A);
}
START_TEST(det_5x5) {
  matrix_t A = {0};
  double result;
  s21_create_matrix(5, 5, &A);
  double values[5][5] = {{4, 18.34, 8.12, 3, 5},
                         {9, 17, 29.2, 13, 4},
                         {-35.6, 45.23424, -1, 0, 4},
                         {4.69, 5.2, 2, 1, 4},
                         {-3.6, 4, -5, 0, 32}};
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++) A.matrix[i][j] = values[i][j];

  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq_tol(result, -193411.41326067, EPS);

  s21_remove_matrix(&A);
}

START_TEST(find_det) {
  matrix_t A = {0};
  A.rows = 0;
  A.columns = 0;
  ck_assert_double_eq_tol(s21_find_determinant(&A), 1, EPS);
  s21_remove_matrix(&A);
}

Suite *suite_s21_determinant() {
  Suite *s = suite_create("matrix_determinant");
  TCase *tc = tcase_create("matrix_determinant");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, det_null);
  tcase_add_test(tc, det_not_square);
  tcase_add_test(tc, det_1x1);
  tcase_add_test(tc, det_2x2);
  tcase_add_test(tc, det_3x3);
  tcase_add_test(tc, det_zero);
  tcase_add_test(tc, det_4x4);
  tcase_add_test(tc, det_5x5);
  tcase_add_test(tc, find_det);

  return s;
}