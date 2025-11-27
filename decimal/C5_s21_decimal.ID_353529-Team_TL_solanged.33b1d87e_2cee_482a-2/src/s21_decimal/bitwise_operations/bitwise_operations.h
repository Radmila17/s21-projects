#ifndef BITWISE_OPERATIONS_H
#define BITWISE_OPERATIONS_H

#include "../../s21_decimal.h"
void s21_bitwise_addition(s21_decimal value_1, s21_decimal value_2,
                          s21_decimal *result);
void s21_big_bitwise_addition(s21_big_decimal big_value_1,
                              s21_big_decimal big_value_2,
                              s21_big_decimal *result);
void s21_bitwise_subtraction(s21_big_decimal big_value_1,
                             s21_big_decimal big_value_2,
                             s21_big_decimal *big_result);
void s21_bitwise_multiplication(s21_big_decimal big_value_1,
                                s21_big_decimal big_value_2,
                                s21_big_decimal *result);
void s21_helper_for_mul(
    int size, s21_big_decimal big_value_1, s21_big_decimal big_value_2,
    s21_big_decimal *result);  // made to avoid code reiteration

int s21_big_get_first_bit_index(
    s21_big_decimal big_value);  // This func can also help you find the size
                                 // (or width) of a decimal in binary
                                 // representation by adding one to the index
int s21_get_first_bit_index(s21_decimal value);
int s21_bitwise_division(s21_big_decimal dividend, s21_big_decimal divisor,
                         s21_big_decimal *result, int index);
#endif