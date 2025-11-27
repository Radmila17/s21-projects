
#include "conversion.h"

#include <math.h>

#include "../print_helpers/print_helpers.h"
#include "string.h"

int s21_from_int_to_decimal(int src, s21_decimal* dst) {
  if (dst == NULL) {
    return 1;
  }
  dst->bits[0] = 0;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;
  int flag = OK;
  int sign = 0;
  if (src >= 0) {
    dst->bits[0] = src;
  } else {
    sign = 1;
    if (src != -2147483648) {
      src = -src;
    }
    dst->bits[0] = src;
  }
  s21_set_sign(dst, sign);
  s21_print_binary(*dst);
  return flag;
}

int s21_from_decimal_to_int(s21_decimal src, int* dst) {
  if (dst == NULL || s21_dec_validate(src) != OK) {
    return 1;
  }
  int flag = OK;
  s21_decimal temp = {0};
  int sign = s21_get_sign(src);
  if (s21_get_scale(src) != 0) {
    s21_truncate(src, &temp);
    src = temp;
  }
  if (s21_is_int_zero(src, 2) == TRUE && s21_is_int_zero(src, 1) == TRUE &&
      (src.bits[0] < MAX_INT || (sign == 1 && src.bits[0] == MAX_INT))) {
    *dst = src.bits[0];
    if (sign == 1) {
      *dst *= -1;
    }
  } else {
    flag = CONVERTATION_ERROR;
  }
  return flag;
}

void get_float_params(char* since_notation, int* float_mantissa,
                      int* float_scale) {
  *float_mantissa = 0;
  int i = 0;

  while (i < 7) {
    if (*since_notation >= 48 && *since_notation <= 57) {
      *float_mantissa += pow(10, 7 - i - 1) * (*since_notation - 48);
      i++;
    }
    since_notation++;
  }
  since_notation++;
  *float_scale = atoi(since_notation);

  if (*float_scale <= -23 && *float_scale >= -28) {
    int shift = -(22 + *float_scale);
    while (shift != 0) {
      *float_mantissa = round((double)*float_mantissa / 10);
      shift--;
      (*float_scale)++;
    }
  }
}

int s21_from_float_to_decimal(float src, s21_decimal* dst) {
  if (dst == NULL || s21_dec_validate(*dst) != OK) {
    return 1;
  }
  char Chungus[20];
  int float_mantissa;
  int float_scale;
  sprintf(Chungus, "%E", src);
  get_float_params(Chungus, &float_mantissa, &float_scale);
  s21_equate_to_zero(dst);
  if (Chungus[0] == '-') s21_set_sign(dst, 1);
  dst->bits[0] = float_mantissa;

  int scale = 6 - float_scale;
  int error = 0;
  if (scale > 34) {
    s21_equate_to_zero(dst);
    error = 1;
  }

  if (scale < 0) {
    s21_decimal multiplier_ten = {{10, 0, 0, 0}};

    while (scale != 0 && !error) {
      if (s21_mul(multiplier_ten, *dst, dst) != OK) error = 1;
      scale++;
    }
  }
  s21_set_scale(dst, scale);
  return error;
}

int s21_from_decimal_to_float(s21_decimal src, float* dst) {
  if (dst == NULL || s21_dec_validate(src) != OK) {
    return 1;
  }
  double res = 0.0;
  int flag = 0;
  *dst = 0.0;
  int scale = s21_get_scale(src);
  int sign = s21_get_sign(src);
  for (int i = 0; i < 96; i++) {
    if (s21_get_bit(src, i) == 1) {
      res += pow(2, i);
    }
  }

  if (scale > 0) {
    res /= pow(10, scale);
  }
  if (sign == 1) {
    res *= (-1);
  }
  *dst = res;
  return flag;
}

/* Converting funcs: */
