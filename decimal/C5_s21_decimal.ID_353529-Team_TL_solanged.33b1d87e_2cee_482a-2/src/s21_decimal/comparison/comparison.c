#include "comparison.h"

// flag == 0 равны
// flag == 1 первое число больше
// flag == -1 первое число меньше

int s21_compare_mantissas(s21_decimal value_1, s21_decimal value_2) {
  int flag = 0;  // values are equal
  s21_big_decimal big_value_1 = s21_decimal_to_big_decimal(value_1);
  s21_big_decimal big_value_2 = s21_decimal_to_big_decimal(value_2);
  flag = s21_big_compare_mantissas(big_value_1, big_value_2);
  return flag;
}

int s21_big_compare_mantissas(s21_big_decimal big_value_1,
                              s21_big_decimal big_value_2) {
  int flag = 0;
  if (s21_big_get_scale(big_value_1) != s21_big_get_scale(big_value_2)) {
    s21_normalise(&big_value_1, &big_value_2);
  }
  for (int i = 32 * 7 - 1; (i >= 0) & (flag == 0); i--) {
    if (s21_big_get_bit(big_value_1, i) > s21_big_get_bit(big_value_2, i)) {
      flag = 1;  // value_1 greater than value_1
    } else if (s21_big_get_bit(big_value_1, i) <
               s21_big_get_bit(big_value_2, i)) {
      flag = -1;  // value_1 less than value_1
    }
  }
  return flag;
}

int s21_compare_dec(s21_decimal value_1, s21_decimal value_2)

{
  int flag = 0;  // value_1 equal to value_1
  s21_big_decimal big_value_1 = s21_decimal_to_big_decimal(value_1);
  s21_big_decimal big_value_2 = s21_decimal_to_big_decimal(value_2);
  if (s21_big_get_sign(big_value_1) < s21_big_get_sign(big_value_2)) {
    flag = 1;  // value_1 greater than value_1
  } else if (s21_big_get_sign(big_value_1) > s21_big_get_sign(big_value_2)) {
    flag = -1;
  }
  if (s21_is_big_dec_zero(big_value_1) == TRUE &&
      s21_is_big_dec_zero(big_value_2) == TRUE) {
    flag = 4;  // чтобы войти в следующее условие приравниваю не 0, а 4
  }
  if (flag == 0) {
    flag = s21_compare_mantissas(value_1, value_2);
    if (s21_big_get_sign(big_value_1) == 1)  // если оба числа отрицательные
    {
      flag *= -1;
    }
  }
  if (flag == 4) {
    flag = 0;
  }
  return flag;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int flag = 0;
  int comp_res = s21_compare_dec(value_1, value_2);
  if (comp_res == -1) {
    flag = 1;
  }
  return flag;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int flag = 0;
  int comp_res = s21_compare_dec(value_1, value_2);
  if (comp_res == -1 || comp_res == 0) {
    flag = 1;
  }
  return flag;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int flag = 0;
  int comp_res = s21_compare_dec(value_1, value_2);
  if (comp_res == 1) {
    flag = 1;
  }
  return flag;
}
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int flag = 0;
  int comp_res = s21_compare_dec(value_1, value_2);
  if (comp_res == 1 || comp_res == 0) {
    flag = 1;
  }
  return flag;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int flag = 0;
  int comp_res = s21_compare_dec(value_1, value_2);
  if (comp_res == 0) {
    flag = 1;
  }
  return flag;
}
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  int flag = 0;
  int comp_res = s21_compare_dec(value_1, value_2);
  if (comp_res != 0) {
    flag = 1;
  }
  return flag;
}
