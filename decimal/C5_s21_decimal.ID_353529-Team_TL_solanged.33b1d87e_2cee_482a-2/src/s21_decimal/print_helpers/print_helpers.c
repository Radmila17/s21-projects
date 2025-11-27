#include "print_helpers.h"

#include <math.h>

#include "../base_helpers/base_helpers.h"
/* Print helpers */

void s21_big_print_binary(s21_big_decimal big_value) {
  printf("\n");
  for (int j = 7; j >= 0; j--) {
    int counter = 0;
    for (int i = 31; i >= 0; i--) {
      int bit = (big_value.bits[j] >> i) & 1;
      if (counter % 4 == 0) {
        printf(" %d", bit);
      } else {
        printf("%d", bit);
      }
      counter++;
    }
    printf("\n");
  }
}

void s21_print_binary(s21_decimal value) {
  printf("\n");
  for (int j = 3; j >= 0; j--) {
    int counter = 0;
    for (int i = 31; i >= 0; i--) {
      int bit = (value.bits[j] >> i) & 1;
      if (counter % 4 == 0) {
        printf(" %d", bit);
      } else {
        printf("%d", bit);
      }
      counter++;
    }
    printf("\n");
  }
}

/* Lisa's helpers */
void s21_parse_and_store(s21_decimal *value, const char *input) {
  int exponent = 0;
  char str_mantissa[100] = {0};
  int sign = 0;
  if (input[0] == '-') {
    sign = 1;
    input++;
  }
  s21_set_sign(value, sign);
  char integer[50] = {0};
  char fraction[50] = {0};
  char *dot_position = strchr(input, '.');
  if (dot_position != NULL) {
    strncpy(integer, input, dot_position - input);
    strcpy(fraction, dot_position + 1);
    exponent = strlen(fraction);
  } else {
    strcpy(integer, input);
  }
  s21_set_scale(value, exponent);
  sprintf(str_mantissa, "%s%s", integer, fraction);
  printf("\n____________________\nMantissa is : %s\n", str_mantissa);

  long long mantissa = atoll(str_mantissa);
  value->bits[0] = mantissa;
  printf("\n");
}

void s21_print_normal_num(s21_decimal dec) {
  printf("\n");
  long long int norm_num = 0;
  for (int i = 3 * 32; i >= 0; i--) {
    if (s21_get_bit(dec, i) == 1) {
      norm_num += pow(2, i);
    }
  }
  if (s21_get_sign(dec) == 1) {
    norm_num *= -1;
  }
  printf("%lld\n", norm_num);
}