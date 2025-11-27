#include "other.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (s21_two_values_validate(value, result) != OK) {
    return 1;
  }
  *result = value;
  int scale = s21_get_scale(value);
  if (scale != 0) {
    for (int i = 0; i < scale; i++) {
      s21_div_by_ten(result);
    }

    s21_set_scale(result, 0);
  }
  return OK;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (s21_two_values_validate(value, result) != OK) {
    return 1;
  }
  *result = value;
  if (s21_get_sign(value) == 0) {
    s21_set_sign(result, 1);
  } else if (s21_get_sign(value) == 1) {
    s21_set_sign(result, 0);
  }
  return OK;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  if (s21_two_values_validate(value, result) != OK) {
    return 1;
  }
  int flag = OK;
  // int last_digit = 0;
  int scale = s21_get_scale(value);
  *result = value;
  int sign = s21_get_sign(*result);
  if (sign == 1) {
    s21_negate(*result, result);
  }
  s21_decimal single_one = {{1, 0, 0, 0}};
  while (scale > 0) {
    int digit = s21_div_by_ten(result);
    // if (scale == s21_get_scale(value))
    // {
    //     last_digit = digit;
    // }
    if (scale == 1) {
      if (digit >= 5) {
        s21_bitwise_addition(*result, single_one, result);
      }
      // if (digit == 5)
      // {
      //     if (s21_get_scale(value) > 1 && last_digit > 0)
      //     {
      //         s21_bitwise_addition(*result, single_one, result);
      //     }
      // }
    }
    scale--;
  }

  s21_set_scale(result, 0);
  s21_set_sign(result, sign);
  return flag;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (s21_two_values_validate(value, result) != OK) {
    return 1;
  }
  int last_digit = 0;
  int not_only_zero_digit = 0;
  int flag = OK;
  int scale = s21_get_scale(value);
  *result = value;
  int sign = s21_get_sign(*result);
  s21_decimal single_one = {{1, 0, 0, 0}};
  while (scale > 0) {
    last_digit = s21_div_by_ten(result);
    if (last_digit != 0 && not_only_zero_digit == 0) {
      not_only_zero_digit = 1;
    }
    scale--;
  }
  if (sign == 1 && s21_get_scale(value) > 0 && not_only_zero_digit == 1) {
    s21_bitwise_addition(*result, single_one, result);
  }
  s21_set_scale(result, 0);
  s21_set_sign(result, sign);
  return flag;
}

int s21_bank_round(s21_big_decimal big_temp, s21_big_decimal *big_result,
                   int *check_zero_digit) {
  *big_result = big_temp;
  int scale = s21_big_get_scale(big_temp);
  int last_digit = s21_big_div_by_ten(&big_temp);
  s21_big_div_by_ten(big_result);
  int ower_flow_flag =
      s21_owerflow_check(big_temp);  // 0.0000000000000000000026409387 49
  int previous_digit = s21_big_div_by_ten(&big_temp);
  // if (s21_owerflow_check(big_temp) == OK && after_point_digit == 4)
  // {
  //     last_digit = 3;
  // }

  // printf("%d %d\n", last_digit, previous_digit);
  if (ower_flow_flag != OK && last_digit != 0) {
    *check_zero_digit += 1;
  }
  if ((last_digit == 5 && ower_flow_flag == OK &&
       ((previous_digit % 2 != 0) || *check_zero_digit > 0)) ||
      (last_digit > 5 && ower_flow_flag == OK)) {
    s21_big_decimal single_one = {{1, 0, 0, 0, 0, 0, 0, 0}};
    s21_big_bitwise_addition(*big_result, single_one, big_result);
  }
  scale--;
  s21_big_set_scale(big_result, scale);
  return OK;
}

/*    *big_result = big_value;
    int scale = s21_big_get_scale(big_value);
    if (s21_owerflow_check(big_value) != OK && scale != 0)
    {
        s21_bank_round(big_value)
    }*/

int s21_big_truncate(s21_big_decimal value, s21_big_decimal *result) {
  *result = value;
  int scale = s21_big_get_scale(value);
  if (scale != 0) {
    for (int i = 0; i < scale; i++) {
      s21_big_div_by_ten(result);
    }

    s21_big_set_scale(result, 0);
  }
  return OK;
}