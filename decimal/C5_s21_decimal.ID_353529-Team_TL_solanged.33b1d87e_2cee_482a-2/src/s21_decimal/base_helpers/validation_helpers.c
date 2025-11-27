#include "base_helpers.h"

int s21_dec_validate(s21_decimal value) {
  int flag = OK;
  if (s21_get_scale(value) > 28) {
    flag = VALIDATION_ERROR;
  }
  for (int i = 96; i <= 111 && flag == OK; i++) {
    if (s21_get_bit(value, i) == 1) {
      flag = VALIDATION_ERROR;
    }
  }
  for (int i = 117; i <= 126 && flag == OK; i++) {
    if (s21_get_bit(value, i) == 1) {
      flag = VALIDATION_ERROR;
    }
  }
  return flag;
}

int s21_two_values_validate(s21_decimal value_1, s21_decimal *result) {
  int flag = OK;
  if (result == NULL || s21_dec_validate(value_1) != OK) {
    flag = VALIDATION_ERROR;
  }
  return flag;
}

int s21_three_values_validate(s21_decimal value_1, s21_decimal value_2,
                              s21_decimal *result) {
  int flag = OK;
  if (result == NULL || s21_dec_validate(value_1) != OK ||
      s21_dec_validate(value_2) != OK) {
    flag = VALIDATION_ERROR;
  }
  return flag;
}

int s21_owerflow_check(s21_big_decimal value) {
  int flag = OK;
  int sign = s21_big_get_sign(value);

  for (int i = 3; (i < 7) && (flag == OK); i++) {
    if (s21_is_big_int_zero(value, i) != TRUE)  // If overflow
    {
      if (sign == 1)  // if negative owerflow, return 2
      {
        flag = TOO_SMALL_NUM;  // = 2
      } else                   // if positive owerflow, return 1
      {
        flag = TOO_LARGE_POSITIVE_NUM;  // = 1
      }
    }
  }
  return flag;
}

int s21_return_code(s21_big_decimal *value, int *scale) {
  int flag = OK;
  s21_big_decimal integer_part = *value;
  s21_decimal temp = s21_big_to_decimal(*value);
  s21_big_truncate(integer_part, &integer_part);
  flag = s21_owerflow_check(integer_part);
  int check_zero_digit = 0;
  if (flag == OK) {
    flag = s21_owerflow_check(*value);
    while (((flag != OK && *scale > 0) || (*scale > 28))) {
      s21_bank_round(*value, value, &check_zero_digit);
      flag = s21_owerflow_check(*value);

      *scale = *scale - 1;
    }
    if ((s21_is_big_dec_zero(*value) == TRUE &&
         s21_is_decimal_zero(temp) != TRUE)) {
      flag = TOO_SMALL_NUM;
    }
  }
  return flag;
}
