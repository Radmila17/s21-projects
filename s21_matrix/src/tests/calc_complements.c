#include "test_s21_matrix.h"

START_TEST(calc_comp_null) {
  matrix_t result = {0};
  ck_assert_int_eq(s21_calc_complements(NULL, &result), INCORRECT);
  matrix_t A = {0};
  s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(s21_calc_complements(&A, NULL), INCORRECT);
  s21_remove_matrix(&A);
}

START_TEST(calc_comp_1x1) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;
  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 1, EPS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}

START_TEST(calc_comp_2x2) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  double values[2][2] = {{1, 2}, {3, 4}};

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      A.matrix[i][j] = values[i][j];
    }
  }
  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 4.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], -3.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], -2.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], 1.0, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}

START_TEST(calc_comp_3x3) {
  matrix_t A = {0}, result;
  s21_create_matrix(3, 3, &A);
  double values[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) A.matrix[i][j] = values[i][j];
  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], -1, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], -41, EPS);
  ck_assert_double_eq_tol(result.matrix[2][2], -24, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}

START_TEST(calc_comp_1x3) {
  matrix_t A = {0}, result;
  s21_create_matrix(1, 3, &A);
  ck_assert_int_eq(s21_calc_complements(&A, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
}

// START_TEST(inverse_3x3) {
//   matrix_t A = {0}, result;
//   s21_create_matrix(3, 3, &A);
//   double values[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
//   for (int i = 0; i < 3; i++)
//     for (int j = 0; j < 3; j++) A.matrix[i][j] = values[i][j];

//   ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
//   ck_assert_double_eq_tol(result.matrix[0][0], 1.0, 1e-6);
//   ck_assert_double_eq_tol(result.matrix[0][1], -1.0, 1e-6);
//   ck_assert_double_eq_tol(result.matrix[1][1], 41.0, 1e-6);

//   s21_remove_matrix(&A);
//   s21_remove_matrix(&result);
// }

Suite *suite_s21_calc_complements() {
  Suite *s = suite_create("calc_ccomplements");
  TCase *tc = tcase_create("calc_ccomplements");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, calc_comp_null);
  tcase_add_test(tc, calc_comp_1x1);
  tcase_add_test(tc, calc_comp_2x2);
  tcase_add_test(tc, calc_comp_3x3);
  tcase_add_test(tc, calc_comp_1x3);
  return s;
}