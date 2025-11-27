
#include "test_s21_matrix.h"

START_TEST(create_1) {
  int rows = 5;
  int columns = 3;
  matrix_t A = {0};
  int res = s21_create_matrix(rows, columns, &A);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(rows, A.rows);
  ck_assert_int_eq(columns, A.columns);
  ck_assert_ptr_ne(A.matrix, NULL);
  s21_remove_matrix(&A);
}

START_TEST(create_2) {
  int rows = 3;
  int columns = 4;
  int res = s21_create_matrix(rows, columns, NULL);
  ck_assert_int_eq(res, INCORRECT);
}

START_TEST(create_3) {
  int rows = 0;
  int columns = 0;
  matrix_t A = {0};
  int res = s21_create_matrix(rows, columns, &A);
  ck_assert_int_eq(res, INCORRECT);
}

START_TEST(create_4) {
  int rows = 4;
  int columns = -3;
  matrix_t A;
  int res = s21_create_matrix(rows, columns, &A);
  ck_assert_int_eq(res, INCORRECT);
}

START_TEST(create_5_only_columns) {
  int rows = 1;
  int columns = 3;
  matrix_t A;
  int res = s21_create_matrix(rows, columns, &A);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(rows, A.rows);
  ck_assert_int_eq(columns, A.columns);
  ck_assert_ptr_ne(A.matrix, NULL);
  s21_remove_matrix(&A);
}

START_TEST(create_6_only_rows) {
  int rows = 5;
  int columns = 1;
  matrix_t A;
  int res = s21_create_matrix(rows, columns, &A);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(rows, A.rows);
  ck_assert_int_eq(columns, A.columns);
  ck_assert_ptr_ne(A.matrix, NULL);
  s21_remove_matrix(&A);
}

START_TEST(delete_1) {
  int rows = 4;
  int columns = 3;
  matrix_t A;
  s21_create_matrix(rows, columns, &A);
  s21_remove_matrix(&A);
  ck_assert_ptr_eq(A.matrix, NULL);
}

START_TEST(create_1000000) {
  int rows = 2147483647;
  int columns = 2147483647;
  matrix_t A = {0};
  int res = s21_create_matrix(rows, columns, &A);
  ck_assert_int_eq(res, INCORRECT);
}

START_TEST(delete_2) { s21_remove_matrix(NULL); }

Suite *suite_s21_create_delete_matrix() {
  Suite *s = suite_create("create_and_delete_matrix");
  TCase *tc = tcase_create("create_and_delete_matrix");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, create_1);
  tcase_add_test(tc, create_2);
  tcase_add_test(tc, create_3);
  tcase_add_test(tc, create_4);
  tcase_add_test(tc, create_5_only_columns);
  tcase_add_test(tc, create_6_only_rows);
  tcase_add_test(tc, delete_1);
  tcase_add_test(tc, delete_2);
  tcase_add_test(tc, create_1000000);
  return s;
}