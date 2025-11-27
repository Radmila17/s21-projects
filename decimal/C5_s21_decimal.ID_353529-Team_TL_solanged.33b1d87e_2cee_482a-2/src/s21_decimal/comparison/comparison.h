#ifndef COMPARISON_H
#define COMPARISON_H

#include "../../s21_decimal.h"
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_compare_dec(s21_decimal value_1, s21_decimal value_2);
int s21_big_compare_mantissas(s21_big_decimal big_value_1,
                              s21_big_decimal big_value_2);
int s21_compare_mantissas(s21_decimal value_1, s21_decimal value_2);

#endif