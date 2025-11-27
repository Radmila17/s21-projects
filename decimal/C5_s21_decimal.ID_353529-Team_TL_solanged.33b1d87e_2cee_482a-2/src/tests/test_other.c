
#include "test_s21_decimal.h"

START_TEST(fail_floor_1) {
  // степень 29
  s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_floor_2) {
  s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_floor_3) {
  // биты 24-30 не нули
  s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_floor_4) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  int code = s21_floor(decimal, NULL);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_negate_1) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  int code = s21_negate(decimal, NULL);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_negate_2) {
  // степень 29
  s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_negate_3) {
  // биты 0-15 не нули
  s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_negate_4) {
  // биты 24-30 не нули
  s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_round_1) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  int code = s21_round(decimal, NULL);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_round_2) {
  // степень 29
  s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_round_3) {
  // биты 0-15 не нули
  s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_round_4) {
  // биты 24-30 не нули
  s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_truncate_1) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  int code = s21_truncate(decimal, NULL);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_truncate_2) {
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal = {{0, 0, 0, 1000000000}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_truncate_3) {
  // степень 29
  s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(floor_1) {
  // 79228162514264337593543.950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}};
  // 79228162514264337593543
  s21_decimal answer = {{0x8D36B4C7, 0xF7A0B5ED, 0x10C6, 0x0}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(floor_2) {
  // -792281625142643375.93543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800B0000}};
  // -792281625142643376
  s21_decimal answer = {{0xBCB24AB0, 0xAFEBFF0, 0x0, 0x80000000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(floor_3) {
  // -792.28162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801A0000}};
  // -793
  s21_decimal answer = {{0x319, 0x0, 0x0, 0x80000000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(floor_4) {
  // -7.9228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -8
  s21_decimal answer = {{0x8, 0x0, 0x0, 0x80000000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(floor_5) {
  // -79.228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801B0000}};
  // -80
  s21_decimal answer = {{0x50, 0x0, 0x0, 0x80000000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(floor_6) {
  // 5281877500950955839283265536.0
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
  // 5281877500950955839283265536
  s21_decimal answer = {{0x0, 0x11111111, 0x11111111, 0x0}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(floor_7) {
  // 1.2297829382473034410
  s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};
  // 1
  s21_decimal answer = {{0x1, 0x0, 0x0, 0x0}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(negate_1) {
  // -5.2818775009509558392832655360
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x801C0000}};
  // 5.2818775009509558392832655360
  s21_decimal answer = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x1C0000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(negate_2) {
  // 52818774997211729013222932480
  s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x0}};
  // -52818774997211729013222932480
  s21_decimal answer = {{0x0, 0x0, 0xAAAAAAAA, 0x80000000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(negate_3) {
  // 286331.1530
  s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x40000}};
  // -286331.1530
  s21_decimal answer = {{0xAAAAAAAA, 0x0, 0x0, 0x80040000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(negate_4) {
  // 1.0
  s21_decimal decimal = {{0xA, 0x0, 0x0, 0x10000}};
  // -1.0
  s21_decimal answer = {{0xA, 0x0, 0x0, 0x80010000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(round_1) {
  // 1.2297829382473034410
  s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};
  // 1
  s21_decimal answer = {{0x1, 0x0, 0x0, 0x0}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(round_2) {
  // -1.2297829382473034410
  s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80130000}};
  // -1
  s21_decimal answer = {{0x1, 0x0, 0x0, 0x80000000}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(round_3) {
  // 122978293.79609722880
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0xB0000}};
  // 122978294
  s21_decimal answer = {{0x7547FF6, 0x0, 0x0, 0x0}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(round_4) {
  // 2640938750475477.9196416327680
  s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0xD0000}};
  // 2640938750475478
  s21_decimal answer = {{0x78187CD6, 0x961EB, 0x0, 0x0}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(truncate_1) {
  // -7922816251426433759354.3950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80070000}};
  // -7922816251426433759354
  s21_decimal answer = {{0xF485787A, 0x7F29ABCA, 0x1AD, 0x80000000}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(truncate_2) {
  // 792281625142643375935.43950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000}};
  // 792281625142643375935
  s21_decimal answer = {{0x1873BF3F, 0xF31DC461, 0x2A, 0x0}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(truncate_3) {
  // 7922.8162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x190000}};
  // 7922
  s21_decimal answer = {{0x1EF2, 0x0, 0x0, 0x0}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(truncate_4) {
  // 79228.162514264337593543950334
  s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x180000}};
  // 79228
  s21_decimal answer = {{0x1357C, 0x0, 0x0, 0x0}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(truncate_5) {
  // -999999999.999999999
  s21_decimal decimal = {{0xA763FFFF, 0xDE0B6B3, 0x0, 0x80090000}};
  // -999999999
  s21_decimal answer = {{0x3B9AC9FF, 0x0, 0x0, 0x80000000}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(truncate_6) {
  // 0.9999999
  s21_decimal decimal = {{0x98967F, 0x0, 0x0, 0x70000}};
  // 0
  s21_decimal answer = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

Suite *suite_s21_other(void) {
  Suite *s = suite_create("other");
  TCase *tc = tcase_create("other");

  suite_add_tcase(s, tc);

  tcase_add_test(tc, fail_floor_1);
  tcase_add_test(tc, fail_floor_2);
  tcase_add_test(tc, fail_floor_3);
  tcase_add_test(tc, fail_floor_4);

  tcase_add_test(tc, fail_negate_1);
  tcase_add_test(tc, fail_negate_2);
  tcase_add_test(tc, fail_negate_3);
  tcase_add_test(tc, fail_negate_4);

  tcase_add_test(tc, fail_round_1);
  tcase_add_test(tc, fail_round_2);
  tcase_add_test(tc, fail_round_3);
  tcase_add_test(tc, fail_round_4);

  tcase_add_test(tc, fail_truncate_1);
  tcase_add_test(tc, fail_truncate_2);
  tcase_add_test(tc, fail_truncate_3);

  tcase_add_test(tc, floor_1);
  tcase_add_test(tc, floor_2);
  tcase_add_test(tc, floor_3);
  tcase_add_test(tc, floor_4);
  tcase_add_test(tc, floor_5);
  tcase_add_test(tc, floor_6);
  tcase_add_test(tc, floor_7);

  tcase_add_test(tc, negate_1);
  tcase_add_test(tc, negate_2);
  tcase_add_test(tc, negate_3);
  tcase_add_test(tc, negate_4);

  tcase_add_test(tc, round_1);
  tcase_add_test(tc, round_2);
  tcase_add_test(tc, round_3);
  tcase_add_test(tc, round_4);

  tcase_add_test(tc, truncate_1);
  tcase_add_test(tc, truncate_2);
  tcase_add_test(tc, truncate_3);
  tcase_add_test(tc, truncate_4);
  tcase_add_test(tc, truncate_5);
  tcase_add_test(tc, truncate_6);

  return s;
}