#include "base_helpers.h"

void s21_equate_to_zero(s21_decimal *value) {
  for (int i = 0; i < 4; i++) {
    value->bits[i] = 0;
  }
}

void s21_big_equate_to_zero(s21_big_decimal *value) {
  for (int i = 0; i < 8; i++) {
    value->bits[i] = 0;
  }
}

int s21_is_decimal_zero(s21_decimal value) {
  int flag = TRUE;
  for (int i = 0; i < 3 && flag == TRUE; i++) {
    if (value.bits[i] != 0) {
      flag = FALSE;
    }
  }
  return flag;
}

int s21_is_big_dec_zero(s21_big_decimal value) {
  int flag = TRUE;
  for (int i = 0; i < 7 && flag == TRUE; i++) {
    if (value.bits[i] != 0) {
      flag = FALSE;
    }
  }
  return flag;
}

int s21_is_int_zero(s21_decimal value, unsigned i) {
  int flag = TRUE;  // TRUE
  if (value.bits[i] != 0) {
    flag = FALSE;  // FALSE
  }
  return flag;
}

int s21_is_big_int_zero(s21_big_decimal value, unsigned i) {
  int flag = TRUE;  // TRUE
  if (value.bits[i] != 0) {
    flag = FALSE;  // FALSE
  }
  return flag;
}

void s21_remove_last_zero(s21_big_decimal *big_value) {
  s21_big_decimal temp = *big_value;
  int scale = s21_big_get_scale(temp);
  int last_digit = 0;
  while (scale > 0 && last_digit == 0) {
    last_digit = s21_big_div_by_ten(&temp);
    scale--;
    s21_big_set_scale(&temp, scale);
    if (last_digit == 0) {
      *big_value = temp;
    }
  }
}