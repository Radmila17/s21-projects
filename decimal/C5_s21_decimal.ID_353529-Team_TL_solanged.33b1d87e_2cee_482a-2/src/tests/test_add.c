
#include "test_s21_decimal.h"

START_TEST(add) {
  s21_decimal a = {{123, 0, 0, 0}}, b = {{456, 0, 0, 0}}, c = {{579, 0, 0, 0}},
              res;
  s21_set_scale(&a, 5);
  s21_set_scale(&b, 5);
  s21_set_scale(&c, 5);

  s21_add(a, b, &res);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}

START_TEST(first_negative_add) {
  s21_decimal a = {{123, 0, 0, 0}}, b = {{456, 0, 0, 0}}, c = {{333, 0, 0, 0}},
              res;
  s21_set_scale(&a, 5);
  s21_set_scale(&b, 5);
  s21_set_scale(&c, 5);
  s21_set_sign(&a, 1);

  int code = s21_add(a, b, &res);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(fail_add_1) {
  // степень 29
  s21_decimal decimal1 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, 0);
}

START_TEST(fail_add_2) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, 0);
}

START_TEST(fail_add_3) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, 0);
}

START_TEST(fail_add_4) {
  // overflow
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0, 0, 0}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_add_5) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  s21_decimal result;

  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(add_1) {
  // 7.922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x1B0000}};
  // 3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x1C0000}};
  // 11.884224377139650639031592551
  s21_decimal answer = {{0x66666667, 0x66666666, 0x26666666, 0x1B0000}};
  s21_decimal result;

  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(add_2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1
  s21_decimal answer = {{0x1, 0x0, 0x0, 0x0}};
  s21_decimal result;

  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(add_3) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 71305346262837903834189555302
  s21_decimal answer = {{0x66666666, 0x66666666, 0xE6666666, 0x0}};
  s21_decimal result;

  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(add_4) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 71305346262837903834189555302
  s21_decimal answer = {{0x66666666, 0x66666666, 0xE6666666, 0x0}};
  s21_decimal result;

  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(add_5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // 71305346262837903834189555301
  s21_decimal answer = {{0x66666665, 0x66666666, 0xE6666666, 0x0}};
  s21_decimal result;

  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(add_6) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593543950334
  s21_decimal answer = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal result;

  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(add_7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 79228162514264337593543950334
  s21_decimal answer = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal result;

  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(add_8) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 79228162514264337593543950334
  s21_decimal answer = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal result;

  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(add_9) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // 79228162514264337592112294570
  s21_decimal answer = {{0xAAAAAAAA, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal result;

  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(add_10) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387.704754779197847983445
  s21_decimal decimal2 = {{0x1B755555, 0x2CE411B0, 0x55555560, 0x80150000}};
  // 79228162514264337593517540947
  s21_decimal answer = {{0xFE6D0653, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal result;

  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

Suite *suite_s21_add(void) {
  Suite *s = suite_create("add");
  TCase *tc = tcase_create("add");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, add);
  tcase_add_test(tc, first_negative_add);
  tcase_add_test(tc, fail_add_1);
  tcase_add_test(tc, fail_add_2);
  tcase_add_test(tc, fail_add_3);
  tcase_add_test(tc, fail_add_4);
  tcase_add_test(tc, fail_add_5);
  tcase_add_test(tc, add_1);
  tcase_add_test(tc, add_2);
  tcase_add_test(tc, add_3);
  tcase_add_test(tc, add_4);
  tcase_add_test(tc, add_5);
  tcase_add_test(tc, add_6);
  tcase_add_test(tc, add_7);
  tcase_add_test(tc, add_8);
  tcase_add_test(tc, add_9);
  tcase_add_test(tc, add_10);

  return s;
}