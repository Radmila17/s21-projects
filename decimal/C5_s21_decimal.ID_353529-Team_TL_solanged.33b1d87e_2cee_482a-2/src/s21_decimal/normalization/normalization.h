#ifndef NORMALIZATION_H
#define NORMALIZATION_H

#include "../../s21_decimal.h"

void s21_normalise(s21_big_decimal *big_value_1, s21_big_decimal *big_value_2);
void s21_big_mul_by_ten(s21_big_decimal *big_value, unsigned diff_scale);
void s21_big_once_mul_by_ten(s21_big_decimal *big_value);

#endif