#include "arithmetic.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (s21_three_values_validate(value_1, value_2, result) != OK) {
    return 4;
  }
  int flag = OK;
  s21_big_decimal big_value_1 = s21_decimal_to_big_decimal(value_1);
  s21_big_decimal big_value_2 = s21_decimal_to_big_decimal(value_2);
  s21_big_decimal big_result = {0};
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);

  s21_normalise(&big_value_1, &big_value_2);
  if (sign_1 == sign_2) {
    s21_big_bitwise_addition(big_value_1, big_value_2, &big_result);
    int scale = s21_big_get_scale(big_value_1);
    s21_big_set_scale(&big_result, scale);
    s21_big_set_sign(&big_result, sign_1);

    s21_remove_last_zero(&big_result);
    flag = s21_return_code(&big_result, &scale);
    if (flag == OK) {
      *result = s21_big_to_decimal(big_result);
    }
  } else if (sign_2 > sign_1) {
    s21_set_sign(&value_2, sign_1);
    s21_sub(value_1, value_2, result);
  } else {
    s21_set_sign(&value_1, sign_2);
    s21_sub(value_2, value_1, result);
  }
  return flag;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (s21_three_values_validate(value_1, value_2, result) != OK) {
    return 4;
  }
  int flag = OK;
  s21_decimal temp_value_2 = value_2;
  s21_big_decimal big_value_1 = s21_decimal_to_big_decimal(value_1);
  s21_big_decimal big_value_2 = s21_decimal_to_big_decimal(value_2);
  s21_big_decimal big_result = {0};
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);
  if (sign_1 != sign_2 || sign_2 == 1) {
    s21_set_sign(&temp_value_2, sign_1);
    if (sign_2 == 1) {
      s21_set_sign(&temp_value_2, 0);
    }
    flag = s21_add(value_1, temp_value_2, result);  /// ARE YOU SHURE?
  } else {
    s21_normalise(&big_value_1, &big_value_2);
    int comp_res = s21_compare_mantissas(value_1, value_2);
    if (comp_res == 1) {
      s21_bitwise_subtraction(big_value_1, big_value_2, &big_result);
    } else if (comp_res == -1) {
      s21_bitwise_subtraction(big_value_2, big_value_1, &big_result);
      s21_big_set_sign(&big_result, 1);
    }
    int scale = s21_big_get_scale(big_value_1);
    s21_big_set_scale(&big_result, scale);
    s21_remove_last_zero(&big_result);
    flag = s21_return_code(&big_result, &scale);
    if (flag == OK) {
      *result = s21_big_to_decimal(big_result);
    }
  }
  return flag;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (s21_three_values_validate(value_1, value_2, result) != OK) {
    return 4;
  }
  int flag = OK;
  s21_big_decimal big_value_1 = s21_decimal_to_big_decimal(value_1);
  s21_big_decimal big_value_2 = s21_decimal_to_big_decimal(value_2);
  s21_big_decimal big_result = {0};
  s21_remove_last_zero(&big_value_1);
  s21_remove_last_zero(&big_value_2);
  int res_scale =
      s21_big_get_scale(big_value_1) + s21_big_get_scale(big_value_2);
  if (s21_get_sign(value_1) != s21_get_sign(value_2)) {
    s21_big_set_sign(&big_result, 1);
  }
  s21_big_set_scale(&big_result, res_scale);
  s21_bitwise_multiplication(big_value_1, big_value_2, &big_result);

  flag = s21_return_code(&big_result, &res_scale);
  *result = s21_big_to_decimal(big_result);
  return flag;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (s21_three_values_validate(value_1, value_2, result) != OK ||
      s21_is_decimal_zero(value_2) == TRUE) {
    return 3;
  }
  int flag = 7;
  s21_big_decimal big_value_1 = s21_decimal_to_big_decimal(value_1);
  s21_big_decimal big_value_2 = s21_decimal_to_big_decimal(value_2);
  s21_big_decimal big_result = s21_decimal_to_big_decimal(*result);
  s21_big_decimal big_temp_dividend = {0};
  int scale = 0;
  s21_normalise(&big_value_1, &big_value_2);
  scale = 0;
  int return_code = OK;
  int i = 0;
  int exit = 0;
  while ((s21_is_big_dec_zero(big_temp_dividend) != TRUE || i == 0) &&
         exit == 0) {
    s21_big_equate_to_zero(&big_result);
    s21_big_equate_to_zero(&big_temp_dividend);
    if (scale == 28) {
      exit = 1;
    }
    return_code = s21_mantissas_div(big_value_1, big_value_2,
                                    &big_temp_dividend, &big_result);
    // s21_big_print_binary(big_value_1);
    // s21_big_print_binary(big_value_2);
    // printf("temp flag %d , flag %d\n", temp_flag, flag);
    if ((s21_is_big_dec_zero(big_temp_dividend) != TRUE || return_code != OK) &&
        scale < 28) {
      if (s21_is_big_int_zero(big_value_1, 6)) {
        s21_big_once_mul_by_ten(&big_value_1);
        scale++;
      } else {
        exit = 1;
      }
    }

    s21_big_set_scale(&big_result, scale);
    if (s21_get_sign(value_1) != s21_get_sign(value_2)) {
      s21_big_set_sign(&big_result, 1);
    }
    if ((s21_is_big_dec_zero(big_temp_dividend) == TRUE) || exit == 1) {
      flag = s21_return_code(&big_result, &scale);
    }

    if (flag == OK) {
      *result = s21_big_to_decimal(big_result);
    }
    i++;
  }
  if (return_code != OK && !s21_is_big_dec_zero(big_value_1)) {
    flag = 2;
  }

  return flag;
}

int s21_find_great_divid(s21_big_decimal value_1, s21_big_decimal value_2,
                         s21_big_decimal *temp_dividend) {
  int flag = OK;
  int dividend_width = s21_big_get_first_bit_index(value_1);  // делимое
  int divisor_width = s21_big_get_first_bit_index(value_2);   // делитель
  *temp_dividend = value_1;
  s21_big_decimal temp_divisor = value_2;
  if (s21_big_compare_mantissas(*temp_dividend, temp_divisor) >=
      0)  // Сначала ищем число, от старшего разряда которое первое было бы
          // больше чем делитель
  {
    int width_diff = dividend_width - divisor_width;
    s21_big_shift_right(temp_dividend,
                        width_diff - 1);  // 10101 превращается в 1010
    int last_bit = s21_big_get_bit(
        *temp_dividend, 0);  // запоминаем последний бит, для 1010 это 0
    s21_big_shift_right(temp_dividend, 1);  // 1010 превращается в 101
    if (s21_big_compare_mantissas(*temp_dividend, temp_divisor) <
        0)  // так как 101 меньше чем делитель, значит мы должны вернуть
            // предыдущий шаг и превратить 101 в 1010
    {
      s21_big_shift_left(temp_dividend, 1);
      s21_big_set_bit(temp_dividend, 0, last_bit);
    }
  } else {
    flag = 1;
  }
  return flag;
}

int s21_mantissas_div(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                      s21_big_decimal *big_temp_dividend,
                      s21_big_decimal *big_result) {
  int temp_divid_width = 0;
  int next_divid_bit = 0;
  int next_bit_index = 0;
  int divid_width = 0;
  int bit_of_result = 0;
  int i = 0;
  int return_code =
      s21_find_great_divid(big_value_1, big_value_2, big_temp_dividend);

  if (return_code == OK) {
    divid_width = s21_big_get_first_bit_index(big_value_1);
    temp_divid_width = s21_big_get_first_bit_index(*big_temp_dividend);
    while (temp_divid_width + i <= divid_width) {
      bit_of_result =
          s21_bitwise_division(*big_temp_dividend, big_value_2, big_result, i);

      if (bit_of_result == 1) {
        s21_bitwise_subtraction(*big_temp_dividend, big_value_2,
                                big_temp_dividend);
      }

      if (temp_divid_width + i + 1 <= divid_width) {
        next_bit_index = divid_width - temp_divid_width - i - 1;
        next_divid_bit = s21_big_get_bit(big_value_1, next_bit_index);
        s21_big_left_shift_by_one(big_temp_dividend);
        s21_big_set_bit(big_temp_dividend, 0, next_divid_bit);
      }
      i++;
    }
  }
  return return_code;
}