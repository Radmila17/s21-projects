#include "test_s21_decimal.h"

START_TEST(div_1) {
  s21_decimal decimal1 = {{10, 0, 0, 0}};

  s21_decimal decimal2 = {{2, 0, 0, 0}};
  s21_decimal answer = {{5, 0, 0, 0}};
  s21_decimal result;

  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(div_2) {
  s21_decimal decimal1 = {{10, 0, 0, 0x80000000}};
  s21_decimal decimal2 = {{2, 0, 0, 0}};

  s21_decimal answer = {{5, 0, 0, 0x80000000}};
  s21_decimal result;

  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(div_3) {
  // 79228162514264337593543950320
  s21_decimal decimal1 = {{0xFFFFFFF0, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.9999999999999999999999999998
  s21_decimal decimal2 = {{0xFFFFFFE, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(div_4) {
  // 79228162514264337593543950320
  s21_decimal decimal2 = {{0xFFFFFFF0, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.9999999999999999999999999998
  s21_decimal decimal1 = {{0xFFFFFFE, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_eq(code, 2);
}

START_TEST(div_5) {
  // 79228162514264337593543950320
  s21_decimal decimal1 = {{0xFFFFFFF0, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.9999999999999999999999999998
  s21_decimal decimal2 = {{0, 0, 0, 0}};
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_eq(code, 3);
}

START_TEST(div_6) {
  // 79228162514264337593543950320
  s21_decimal decimal1 = {{0xFFFFFFF0, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.9999999999999999999999999998
  s21_decimal decimal2 = {{0, 0, 0, 0}};

  int code = s21_div(decimal1, decimal2, NULL);

  ck_assert_int_eq(code, 3);
}

Suite *suite_s21_div(void) {
  Suite *s = suite_create("div");
  TCase *tc = tcase_create("div");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, div_1);
  tcase_add_test(tc, div_2);
  tcase_add_test(tc, div_3);
  tcase_add_test(tc, div_4);
  tcase_add_test(tc, div_5);
  tcase_add_test(tc, div_6);

  return s;
}