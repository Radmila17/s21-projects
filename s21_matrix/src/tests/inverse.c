#include "test_s21_matrix.h"

START_TEST(inverse_null) {
  matrix_t result;
  ck_assert_int_eq(s21_inverse_matrix(NULL, &result), INCORRECT);
  matrix_t A = {0};
  s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(s21_inverse_matrix(&A, NULL), INCORRECT);
  s21_remove_matrix(&A);
}

START_TEST(inverse_not_square) {
  matrix_t A = {0}, result;
  s21_create_matrix(2, 3, &A);
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
}

START_TEST(inverse_1x1) {
  matrix_t A = {0}, result;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.2, 1e-6);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}

START_TEST(inverse_2x2) {
  matrix_t A = {0}, result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 4.0;
  A.matrix[0][1] = 7.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 6.0;

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.6, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], -0.7, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][0], -0.2, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][1], 0.4, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}

START_TEST(inverse_zero_determinant) {
  matrix_t A = {0}, result;
  s21_create_matrix(3, 3, &A);
  double values[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) A.matrix[i][j] = values[i][j];
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
}

START_TEST(inverse_3x3) {
  matrix_t A = {0}, result;
  s21_create_matrix(3, 3, &A);
  double values[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) A.matrix[i][j] = values[i][j];

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], -1.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][1], 41.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}

START_TEST(inverse_5x5) {
  matrix_t A = {0}, result;
  s21_create_matrix(5, 5, &A);
  double values[5][5] = {{4, 18.34, 8.12, 3, 5},
                         {9, 17, 29.2, 13, 4},
                         {-35.6, 45.23424, -1, 0, 4},
                         {4.69, 5.2, 2, 1, 4},
                         {-3.6, 4, -5, 0, 32}};
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++) A.matrix[i][j] = values[i][j];

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], -0.03459274, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], -0.0078198717237, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][1], -0.00664188311508, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}

START_TEST(inverse_without_allocating_memory) {
  matrix_t A = {0};
  matrix_t result = {0};
  A.rows = 2;
  A.columns = 2;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), INCORRECT);
}

Suite *suite_s21_inverse_matrix() {
  Suite *s = suite_create("inverse_matrix");
  TCase *tc = tcase_create("inverse_matrix");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, inverse_null);
  tcase_add_test(tc, inverse_not_square);
  tcase_add_test(tc, inverse_1x1);
  tcase_add_test(tc, inverse_2x2);
  tcase_add_test(tc, inverse_zero_determinant);
  tcase_add_test(tc, inverse_3x3);
  tcase_add_test(tc, inverse_5x5);
  tcase_add_test(tc, inverse_without_allocating_memory);

  return s;
}