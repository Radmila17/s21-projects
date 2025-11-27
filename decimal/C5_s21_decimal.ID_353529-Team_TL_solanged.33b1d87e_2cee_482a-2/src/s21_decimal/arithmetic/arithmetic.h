
#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "../../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_find_great_divid(s21_big_decimal value_1, s21_big_decimal value_2,
                         s21_big_decimal *temp_dividend);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mantissas_div(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                      s21_big_decimal *big_temp_dividend,
                      s21_big_decimal *big_result);

#endif