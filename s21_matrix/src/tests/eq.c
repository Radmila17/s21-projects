#include "test_s21_matrix.h"

START_TEST(eq_null) {
  ck_assert_int_eq(s21_eq_matrix(NULL, NULL), FAILURE);
  matrix_t A = {0};
  s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(s21_eq_matrix(&A, NULL), FAILURE);
  ck_assert_int_eq(s21_eq_matrix(NULL, &A), FAILURE);
  s21_remove_matrix(&A);
}

START_TEST(eq_diff_size) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(3, 3, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(eq_identical) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      A.matrix[i][j] = i + j + 0.5;
      B.matrix[i][j] = i + j + 0.5;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(eq_not_identical) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      A.matrix[i][j] = i + j + 0.5;
      B.matrix[i][j] = i + j + 0.5 + 0.0000001;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

Suite *suite_s21_eq_matrix() {
  Suite *s = suite_create("eq_matrix");
  TCase *tc = tcase_create("eq_matrix");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, eq_null);
  tcase_add_test(tc, eq_diff_size);
  tcase_add_test(tc, eq_identical);
  tcase_add_test(tc, eq_not_identical);

  return s;
}