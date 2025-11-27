#include "test_s21_matrix.h"

START_TEST(mult_1) {
  int my_res = s21_mult_matrix(NULL, NULL, NULL);
  ck_assert_int_eq(my_res, INCORRECT);
}

START_TEST(mult_2) {
  int rows = 3;
  int columns = 4;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(3, 5, &B);
  int res = s21_mult_matrix(&A, &B, &result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  ck_assert_int_eq(res, CALCULATION_ERROR);
}

START_TEST(mult_3) {
  int rows = 3;
  int columns = 4;
  matrix_t A = {0};
  matrix_t result = {0};
  s21_create_matrix(rows, columns, &A);
  int res = s21_mult_matrix(&A, NULL, &result);
  ck_assert_int_eq(res, INCORRECT);
  s21_remove_matrix(&A);
}

START_TEST(mult_4) {
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 5, &B);
  int res = s21_mult_matrix(NULL, &B, &result);
  ck_assert_int_eq(res, INCORRECT);
  s21_remove_matrix(&B);
}

START_TEST(mult_5) {
  int rows = 2;
  int columns = 3;
  double start = 0;
  double step = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t my_result = {0};
  matrix_t result = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(3, 2, &B);
  s21_create_matrix(2, 2, &result);
  s21_filling_matrix(&A, 0, 0);
  s21_filling_matrix(&B, start, step);
  int res = s21_mult_matrix(&A, &B, &my_result);
  ck_assert_int_eq(res, OK);
  result.matrix[0][0] = 0.0;
  result.matrix[0][1] = 0.0;
  result.matrix[1][0] = 0.0;
  result.matrix[1][1] = 0.0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], my_result.matrix[i][j], EPS);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&my_result);
}

START_TEST(mult_6) {
  int rows = 3;
  int columns = 4;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(2, 4, &B);
  int res = s21_mult_matrix(&A, &B, &result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  ck_assert_int_eq(res, CALCULATION_ERROR);
}

START_TEST(mult_7) {
  int rows = 3;
  int columns = 4;
  matrix_t A = {0};
  s21_create_matrix(rows, columns, &A);
  matrix_t B = {0};
  s21_create_matrix(rows, columns, &B);
  int res = s21_mult_matrix(&B, &A, NULL);
  ck_assert_int_eq(res, INCORRECT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(mult_num_1) {
  int my_res = s21_mult_number(NULL, 5.0, NULL);
  ck_assert_int_eq(my_res, INCORRECT);
}

START_TEST(mult_num_2) {
  int rows = 3;
  int columns = 4;
  matrix_t A = {0};
  s21_create_matrix(rows, columns, &A);
  int res = s21_mult_number(&A, 2.5, NULL);
  s21_remove_matrix(&A);
  ck_assert_int_eq(res, INCORRECT);
}

START_TEST(mult_num_3) {
  matrix_t result = {0};
  int res = s21_mult_number(NULL, 3.0, &result);
  ck_assert_int_eq(res, INCORRECT);
}

START_TEST(mult_num_4) {
  int rows = 2;
  int columns = 3;
  matrix_t A = {0};
  matrix_t result = {0};
  matrix_t expected = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &expected);
  double counter = 1.0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = counter;
      expected.matrix[i][j] = counter * 2.5;
      counter += 1.0;
    }
  }
  int res = s21_mult_number(&A, 2.5, &result);
  ck_assert_int_eq(res, OK);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq_tol(expected.matrix[i][j], result.matrix[i][j], EPS);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}

START_TEST(mult_num_5) {
  int rows = 3;
  int columns = 3;
  matrix_t A = {0};
  matrix_t result = {0};
  matrix_t expected = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &expected);
  int res = s21_mult_number(&A, 10.0, &result);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = 0.0;
      expected.matrix[i][j] = 0.0;
    }
  }
  ck_assert_int_eq(res, OK);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq_tol(expected.matrix[i][j], result.matrix[i][j], EPS);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}

Suite *suite_s21_mult_matrix() {
  Suite *s = suite_create("mult_matrix");
  TCase *tc = tcase_create("mult_matrix");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, mult_1);
  tcase_add_test(tc, mult_2);
  tcase_add_test(tc, mult_3);
  tcase_add_test(tc, mult_4);
  tcase_add_test(tc, mult_5);
  tcase_add_test(tc, mult_6);
  tcase_add_test(tc, mult_7);
  tcase_add_test(tc, mult_num_1);
  tcase_add_test(tc, mult_num_2);
  tcase_add_test(tc, mult_num_3);
  tcase_add_test(tc, mult_num_4);
  tcase_add_test(tc, mult_num_5);
  return s;
}