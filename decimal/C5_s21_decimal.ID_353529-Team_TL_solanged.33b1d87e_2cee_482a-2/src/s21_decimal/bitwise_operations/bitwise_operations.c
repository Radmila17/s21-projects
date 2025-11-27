#include "bitwise_operations.h"

void s21_big_bitwise_addition(s21_big_decimal big_value_1,
                              s21_big_decimal big_value_2,
                              s21_big_decimal *result) {
  unsigned memo = 0;
  for (int i = 0; i < 32 * 7; i++) {
    unsigned result_bit = s21_big_get_bit(big_value_1, i) +
                          s21_big_get_bit(big_value_2, i) + memo;
    memo = result_bit / 2;
    result_bit %= 2;
    s21_big_set_bit(result, i, result_bit);
  }
}

void s21_bitwise_addition(s21_decimal value_1, s21_decimal value_2,
                          s21_decimal *result) {
  unsigned memo = 0;
  for (int i = 0; i < 32 * 3; i++) {
    unsigned result_bit =
        s21_get_bit(value_1, i) + s21_get_bit(value_2, i) + memo;
    memo = result_bit / 2;
    result_bit %= 2;
    s21_set_bit(result, i, result_bit);
  }
}

void s21_bitwise_subtraction(s21_big_decimal big_value_1,
                             s21_big_decimal big_value_2,
                             s21_big_decimal *result) {
  int memo = 0;
  for (int i = 0; i < 32 * 7; i++) {
    int result_bit = s21_big_get_bit(big_value_1, i) -
                     s21_big_get_bit(big_value_2, i) - memo;
    if (result_bit < 0) {
      result_bit = result_bit + 2;
      memo = 1;
    } else {
      memo = 0;
    }
    s21_big_set_bit(result, i, result_bit);
  }
}

void s21_bitwise_multiplication(s21_big_decimal big_value_1,
                                s21_big_decimal big_value_2,
                                s21_big_decimal *result) {
  int size_1 = s21_big_get_first_bit_index(big_value_1);
  int size_2 = s21_big_get_first_bit_index(big_value_2);

  if (size_1 >= size_2) {
    s21_helper_for_mul(size_2, big_value_2, big_value_1, result);
  } else {
    s21_helper_for_mul(size_1, big_value_1, big_value_2, result);
  }
}

void s21_helper_for_mul(int size, s21_big_decimal big_value_1,
                        s21_big_decimal big_value_2, s21_big_decimal *result) {
  s21_big_decimal temp_value = {0};

  for (int i = size; i >= 0; i--) {
    if (s21_big_get_bit(big_value_1, i) == 1) {
      temp_value = big_value_2;
      s21_big_shift_left(&temp_value, i);
      s21_big_bitwise_addition(*result, temp_value, result);
    }
  }
}

int s21_bitwise_division(s21_big_decimal dividend, s21_big_decimal divisor,
                         s21_big_decimal *result, int index) {
  int bit = 0;
  if (index != 0) {
    s21_big_left_shift_by_one(result);
  }

  if (s21_big_compare_mantissas(dividend, divisor) >= 0) {
    s21_big_set_bit(result, 0, 1);
    bit = 1;
  } else {
    s21_big_set_bit(result, 0, 0);
  }

  return bit;
}

int s21_big_get_first_bit_index(
    s21_big_decimal big_value)  // This func can also help you find the size (or
                                // width) of a decimal in binary representation
                                // by adding one to the index
{
  int index = 0;
  for (int i = 32 * 7 - 1; i >= 0 && index == 0; i--) {
    if (s21_big_get_bit(big_value, i) == 1) {
      index = i;
    }
  }
  return index;
}

int s21_get_first_bit_index(
    s21_decimal
        value)  // This func can also help you find the size (or width) of a
                // decimal in binary representation by adding one to the index
{
  int index = 0;
  for (int i = 32 * 3 - 1; i >= 0 && index == 0; i--) {
    if (s21_get_bit(value, i) == 1) {
      index = i;
    }
  }
  return index;
}