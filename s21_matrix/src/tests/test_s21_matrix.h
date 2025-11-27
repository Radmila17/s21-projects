#ifndef TEST_S21_MATRIX_H
#define TEST_S21_MATRIX_H

#include <check.h>
#include <limits.h>

#include "../s21_matrix.h"
#define SUCCESS 1
#define FAILURE 0
#define OK 0
#define INCORRECT 1
#define CALCULATION_ERROR 2
#define EPS 0.0000001
#define MIN_VALUE -3E10
#define MAX_VALUE 3E10

Suite *suite_s21_create_delete_matrix();
Suite *suite_s21_sum_sub_matrix();
Suite *suite_s21_mult_matrix();
Suite *suite_s21_transpose();
Suite *suite_s21_eq_matrix();
Suite *suite_s21_calc_complements();
Suite *suite_s21_determinant();
Suite *suite_s21_inverse_matrix();

void run_tests();
void run_testcase(Suite *testcase, int *all_fails);

#endif
