#include "conversion.h"
s21_big_decimal s21_decimal_to_big_decimal(s21_decimal value) {
  s21_big_decimal big_value = {0};
  for (int i = 0; i < 3; i++) {
    big_value.bits[i] = value.bits[i];
  }
  big_value.bits[7] = value.bits[3];

  return big_value;
}

s21_decimal s21_big_to_decimal(s21_big_decimal big_value) {
  s21_decimal value = {0};
  for (int i = 0; i < 3; i++) {
    value.bits[i] = big_value.bits[i];
  }
  value.bits[3] = big_value.bits[7];

  return value;
}