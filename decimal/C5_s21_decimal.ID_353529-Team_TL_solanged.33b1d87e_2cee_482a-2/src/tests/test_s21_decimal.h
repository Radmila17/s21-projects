#ifndef TEST_S21_DECIMAL_H
#define TEST_S21_DECIMAL_H

#include <check.h>
#include <time.h>

#include "../s21_decimal.h"

#define TRUE 1
#define FALSE 0

Suite *suite_s21_add(void);
Suite *suite_s21_comparison(void);
Suite *suite_s21_div(void);
Suite *suite_s21_sub(void);
Suite *suite_s21_mul(void);
Suite *suite_s21_conversion(void);
Suite *suite_s21_other(void);

void run_tests();
void run_testcase(Suite *testcase, int *all_fails);

#endif