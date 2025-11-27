#ifndef CONVERSION_H
#define CONVERSION_H

#include "../base_helpers/base_helpers.h"
#include "../other/other.h"
#include "../types.h"

s21_big_decimal s21_decimal_to_big_decimal(s21_decimal value);
s21_decimal s21_big_to_decimal(s21_big_decimal big_value);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
void get_float_params(char *since_notation, int *float_mantissa,
                      int *float_scale);
int s21_from_float_to_decimal(float src, s21_decimal *dst);

#endif