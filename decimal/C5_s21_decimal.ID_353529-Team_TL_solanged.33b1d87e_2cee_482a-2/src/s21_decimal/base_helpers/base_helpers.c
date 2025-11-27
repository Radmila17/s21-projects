#include "base_helpers.h"

/*      Decimal base helpers:        */
int s21_get_bit(s21_decimal value, unsigned index) {
  return (((value.bits[index / 32]) & (1u << index % 32))) >> index % 32;
}

void s21_set_bit(s21_decimal *value, unsigned index, unsigned num) {
  if (num == 1) {
    value->bits[index / 32] |= 1 << (index % 32);
  } else if (num == 0) {
    value->bits[index / 32] &= ~(1 << (index % 32));
  }
}
int s21_get_sign(s21_decimal value) { return s21_get_bit(value, 127); }

void s21_set_sign(s21_decimal *value, unsigned sign) {
  s21_set_bit(value, 127, sign);
}

int s21_get_scale(s21_decimal value) { return (value.bits[3] >> 16) & 0X0FFF; }

void s21_set_scale(s21_decimal *value, unsigned exponent) {
  value->bits[3] &= 0XF0000000;
  value->bits[3] |= (exponent << 16);
}

/*          Big decimal base helpers:        */

int s21_big_get_bit(s21_big_decimal big_value, unsigned index) {
  return (((big_value.bits[index / 32]) & (1u << index % 32))) >> index % 32;
}

void s21_big_set_bit(s21_big_decimal *big_value, unsigned index, unsigned num) {
  if (num == 1) {
    big_value->bits[index / 32] |= 1 << (index % 32);
  } else if (num == 0) {
    big_value->bits[index / 32] &= ~(1 << (index % 32));
  }
}

int s21_big_get_sign(s21_big_decimal big_value) {
  return s21_big_get_bit(big_value, 255);
}

void s21_big_set_sign(s21_big_decimal *big_value, unsigned sign) {
  s21_big_set_bit(big_value, 255, sign);
}

int s21_big_get_scale(s21_big_decimal big_value) {
  return (big_value.bits[7] >> 16) & 0X0FFF;
}

void s21_big_set_scale(s21_big_decimal *big_value, unsigned exponent) {
  big_value->bits[7] &= 0XF0000000;
  big_value->bits[7] |= (exponent << 16);
}

/*      Other helpers:       */

/* Funtion of multiplieng to 2*/

void s21_big_shift_left(s21_big_decimal *value, unsigned shift_value) {
  if (shift_value > 0 && s21_is_big_dec_zero(*value) ==
                             FALSE)  // Checking shift_value is bigger than 0
  {
    for (unsigned i = 0; i < shift_value; i++) {
      s21_big_left_shift_by_one(value);
    }
  }
}

void s21_big_left_shift_by_one(s21_big_decimal *big_value) {
  int carry = 0;
  for (int i = 0; i < 7; ++i) {
    int next_carry = (big_value->bits[i] >> 31) & 1;
    big_value->bits[i] <<= 1;
    big_value->bits[i] |= carry;
    carry = next_carry;
  }
}

void s21_big_shift_right(s21_big_decimal *value, unsigned shift_value) {
  if (shift_value > 0 && s21_is_big_dec_zero(*value) == FALSE &&
      shift_value <
          226)  // Checking shift_value is bigger than 0 and value is not NULL.
  {
    for (unsigned i = 0; i < shift_value; i++) {
      for (unsigned j = 0; j + 1 < 32 * 7; j++) {
        s21_big_set_bit(value, j, s21_big_get_bit(*value, j + 1));
      }
    }
  }
}
