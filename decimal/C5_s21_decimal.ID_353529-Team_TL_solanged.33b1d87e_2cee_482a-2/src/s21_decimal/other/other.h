#ifndef OTHER_H
#define OTHER_H

#include "../../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);

int s21_bank_round(s21_big_decimal big_temp, s21_big_decimal *big_result,
                   int *check_zero_digit);
int s21_big_truncate(s21_big_decimal value, s21_big_decimal *result);
#endif