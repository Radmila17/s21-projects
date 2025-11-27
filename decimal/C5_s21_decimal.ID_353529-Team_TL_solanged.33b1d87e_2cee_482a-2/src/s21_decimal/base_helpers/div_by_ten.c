#include "base_helpers.h"

int s21_div_by_ten(s21_decimal *value) {
  unsigned long long current_value = 0;
  int remeinder = 0;

  for (int i = 2; i >= 0; --i) {
    current_value = value->bits[i];

    if (i ==
        2) {  // для самой старшей части числа без переноса из предыдущей части
      remeinder = current_value % 10;
      value->bits[i] = current_value / 10;
    } else {
      // для остальных частей числа добавляем перенос из предыдущей итерации
      current_value += remeinder * 4294967296;
      remeinder = current_value % 10;
      value->bits[i] = current_value / 10;
    }
  }
  return remeinder;
}

int s21_big_div_by_ten(s21_big_decimal *big_value) {
  unsigned long long current_value = 0;
  int remeinder = 0;

  for (int i = 6; i >= 0; --i) {
    current_value = big_value->bits[i];

    if (i ==
        6) {  // для самой старшей части числа без переноса из предыдущей части
      remeinder = current_value % 10;
      big_value->bits[i] = current_value / 10;
    } else {
      // для остальных частей числа добавляем перенос из предыдущей итерации
      current_value += remeinder * 4294967296;
      remeinder = current_value % 10;
      big_value->bits[i] = current_value / 10;
    }
  }
  return remeinder;
}