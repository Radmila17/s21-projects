#ifndef PRINT_HELPERS_H
#define PRINT_HELPERS_H

#include "../../s21_decimal.h"

/* Print helpers */
void s21_print_binary(s21_decimal value);
void s21_big_print_binary(s21_big_decimal big_value);

/* Lisa's helpers*/
void s21_parse_and_store(s21_decimal *decimal, const char *input);
void s21_print_normal_num(s21_decimal dec);

#endif