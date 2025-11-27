#include "normalization.h"

void s21_normalise(s21_big_decimal *big_value_1, s21_big_decimal *big_value_2) {
  int scale_1 = s21_big_get_scale(*big_value_1);
  int scale_2 = s21_big_get_scale(*big_value_2);
  if (scale_1 != scale_2) {
    unsigned diff_scale = 0;
    if (scale_1 > scale_2) {
      diff_scale = scale_1 - scale_2;
      s21_big_mul_by_ten(big_value_2, diff_scale);
      s21_big_set_scale(big_value_2, scale_1);
    } else {
      diff_scale = scale_2 - scale_1;
      s21_big_mul_by_ten(big_value_1, diff_scale);
      s21_big_set_scale(big_value_1, scale_2);
    }
  }
}

void s21_big_mul_by_ten(s21_big_decimal *big_value, unsigned diff_scale) {
  for (unsigned i = 0; i < diff_scale; i++) {
    s21_big_once_mul_by_ten(big_value);
  }
}

void s21_big_once_mul_by_ten(s21_big_decimal *big_value) {
  s21_big_decimal temp = *big_value;
  s21_big_shift_left(big_value, 3);
  s21_big_shift_left(&temp, 1);
  s21_big_bitwise_addition(*big_value, temp, big_value);
}