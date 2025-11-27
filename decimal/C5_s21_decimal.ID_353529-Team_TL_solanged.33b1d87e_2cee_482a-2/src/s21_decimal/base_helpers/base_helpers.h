#ifndef BASE_HELPERS_H
#define BASE_HELPERS_H

#include "../../s21_decimal.h"
/* Decimal base helpers*/

int s21_get_sign(s21_decimal value);
void s21_set_sign(s21_decimal *value, unsigned sign);

void s21_set_scale(s21_decimal *value, unsigned exponent);
int s21_get_scale(s21_decimal value);

int s21_get_bit(s21_decimal value, unsigned index);
void s21_set_bit(s21_decimal *value, unsigned index, unsigned num);

/* Big decimal base helpers */

int s21_big_get_sign(s21_big_decimal big_value);
void s21_big_set_sign(s21_big_decimal *big_value, unsigned sign);

void s21_big_set_scale(s21_big_decimal *value, unsigned exponent);
int s21_big_get_scale(s21_big_decimal value);

void s21_big_set_bit(s21_big_decimal *value, unsigned index, unsigned num);
int s21_big_get_bit(s21_big_decimal value, unsigned index);

/* Other helpers */

void s21_big_left_shift_by_one(s21_big_decimal *big_value);
void s21_big_shift_left(s21_big_decimal *big_value, unsigned shift_value);

void s21_big_shift_right(s21_big_decimal *value, unsigned shift_value);

/* With zero operations*/
void s21_equate_to_zero(s21_decimal *value);
void s21_big_equate_to_zero(s21_big_decimal *value);

int s21_is_decimal_zero(s21_decimal value);

int s21_is_big_dec_zero(s21_big_decimal value);

int s21_is_int_zero(s21_decimal value, unsigned i);

int s21_is_big_int_zero(s21_big_decimal value, unsigned i);

void s21_remove_last_zero(s21_big_decimal *big_value);

/* Validation helpers */
int s21_owerflow_check(s21_big_decimal value);

// DO WE REALLY NEED THE NEXT FUNCS??????????????
// CLEVER THOUGHTS FOLLOWED ME, BUT I'M FASTER
int s21_dec_validate(s21_decimal value);
int s21_two_values_validate(s21_decimal value_1, s21_decimal *result);
int s21_three_values_validate(s21_decimal value_1, s21_decimal value_2,
                              s21_decimal *result);
// int s21_big_dec_validate(s21_big_decimal value);
// int s21_input_data_validate(s21_decimal value_1, s21_decimal value_2,
// s21_decimal *result);

/* Other funcs */
int s21_div_by_ten(s21_decimal *value);
int s21_big_div_by_ten(s21_big_decimal *big_value);
int s21_return_code(s21_big_decimal *value, int *scale);
#endif
