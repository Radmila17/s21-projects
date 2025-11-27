
#include "test_s21_decimal.h"

START_TEST(fail_from_dec_to_float_1) {
  // степень 29
  s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
  float result = 0.0;
  int code = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_from_dec_to_float_2) {
  // биты 0-15 не нули
  s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
  float result = 0.0;
  int code = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_from_dec_to_float_3) {
  // биты 24-30 не нули
  s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
  float result = 0.0;
  int code = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_from_dec_to_int_1) {
  // степень 29
  s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
  int result = 0.0;
  int code = s21_from_decimal_to_int(decimal, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_from_dec_to_int_2) {
  // биты 0-15 не нули
  s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
  int result = 0.0;
  int code = s21_from_decimal_to_int(decimal, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_from_dec_to_int_3) {
  // биты 24-30 не нули
  s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
  int result = 0.0;
  int code = s21_from_decimal_to_int(decimal, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_from_dec_to_int_4) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_from_decimal_to_int(decimal, NULL);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_from_dec_to_int_5) {
  // 79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int result = 0;
  int code = s21_from_decimal_to_int(decimal, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_from_int_to_dec_1) {
  int number = -2147483648;
  int code = s21_from_int_to_decimal(number, NULL);

  ck_assert_int_eq(code, 1);
}

// START_TEST(fail_from_int_to_dec_2) {
//    // биты 0-15 не нули
//    s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
//    int result = 0.0;
//    int code = s21_from_int_to_decimal(decimal, &result);

//    ck_assert_int_eq(code, 1);
// }

// START_TEST(fail_from_int_to_dec_3) {
//    // биты 24-30 не нули
//    s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
//    int result = 0.0;
//    int code = s21_from_int_to_decimal(decimal, &result);

//    ck_assert_int_eq(code, 1);
// }

// START_TEST(fail_from_int_to_dec_4) {
//       // 792281625.14264337593543950335
//       s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
//    int code = s21_from_int_to_decimal(decimal, NULL);

//    ck_assert_int_eq(code, 1);
// }

START_TEST(from_dec_to_float_1) {
  s21_decimal decimal = {{0x0, 0x109, 0x0, 0xA0000}};
  float answer = 113.8166333440;
  float result = 0;

  int code = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(code, 0);
}

START_TEST(from_dec_to_float_2) {
  s21_decimal decimal = {{0x0, 0x109, 0x0, 0x800A0000}};
  float answer = -113.8166333440;
  float result = 0;

  int code = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(code, 0);
}

START_TEST(from_dec_to_float_3) {
  s21_decimal decimal = {{0x0, 0x80000000, 0x84, 0x800D0000}};
  float answer = -244419358.9766515589120;
  float result = 0;

  int code = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(code, 0);
}

START_TEST(from_dec_to_int_1) {
  s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x90000}};
  int answer = 2;
  int result = 0;

  int code = s21_from_decimal_to_int(decimal, &result);

  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(code, 0);
}

START_TEST(from_dec_to_int_2) {
  s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x80090000}};
  int answer = -2;
  int result = 0;

  int code = s21_from_decimal_to_int(decimal, &result);

  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(code, 0);
}

START_TEST(from_dec_to_int_3) {
  s21_decimal decimal = {{0x513ADEE4, 0x0, 0x0, 0x80000000}};
  int answer = -1362812644;
  int result = 0;

  int code = s21_from_decimal_to_int(decimal, &result);

  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(code, 0);
}

START_TEST(from_int_to_dec_1) {
  int number = -2147483648;
  // Converted the Int32 value -2147483648 to the Decimal value -2147483648.
  s21_decimal answer = {{0x80000000, 0x0, 0x0, 0x80000000}};
  s21_decimal result = {0};
  printf("tut\n");
  int code = s21_from_int_to_decimal(number, &result);
  printf("end\n");
  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(from_int_to_dec_2) {
  int number = 1;
  // Converted the Int32 value 1 to the Decimal value 1.
  s21_decimal answer = {{0x1, 0x0, 0x0, 0x0}};
  s21_decimal result = {0};

  int code = s21_from_int_to_decimal(number, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(from_int_to_dec_3) {
  int number = -1000;
  // Converted the Int32 value -1000 to the Decimal value -1000.
  s21_decimal answer = {{0x3E8, 0x0, 0x0, 0x80000000}};
  s21_decimal result = {0};

  int code = s21_from_int_to_decimal(number, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(float_to_decimal_test_1) {
  float number = 0.123456789;
  s21_decimal decimal = {0};
  s21_decimal exptected_decimal = {{1234568, 0, 0, 0}};
  s21_set_scale(&exptected_decimal, 7);

  ck_assert_int_eq(s21_from_float_to_decimal(number, &decimal), 0);
  ck_assert_int_eq(s21_is_equal(decimal, exptected_decimal), 1);
}

START_TEST(float_to_decimal_test_3) {
  float number = 1e-29;
  s21_decimal decimal = {0};
  s21_decimal exptected_decimal = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_from_float_to_decimal(number, &decimal), 1);
  ck_assert_int_eq(s21_is_equal(decimal, exptected_decimal), 1);
}
END_TEST

// START_TEST(test_int_to_dec_null_first_param) {
//   int result;
//   int code = s21_from_int_to_decimal(4, &result);

//   ck_assert_int_eq(code, 0);
// }

Suite* suite_s21_conversion(void) {
  Suite* s = suite_create("conversion");
  TCase* tc = tcase_create("conversion");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, fail_from_dec_to_float_1);
  tcase_add_test(tc, fail_from_dec_to_float_2);
  tcase_add_test(tc, fail_from_dec_to_float_3);

  tcase_add_test(tc, fail_from_dec_to_int_1);
  tcase_add_test(tc, fail_from_dec_to_int_2);
  tcase_add_test(tc, fail_from_dec_to_int_3);
  tcase_add_test(tc, fail_from_dec_to_int_4);
  tcase_add_test(tc, fail_from_dec_to_int_5);

  tcase_add_test(tc, fail_from_int_to_dec_1);

  tcase_add_test(tc, from_dec_to_float_1);
  tcase_add_test(tc, from_dec_to_float_2);
  tcase_add_test(tc, from_dec_to_float_3);

  tcase_add_test(tc, from_dec_to_int_1);
  tcase_add_test(tc, from_dec_to_int_2);
  tcase_add_test(tc, from_dec_to_int_3);

  tcase_add_test(tc, from_int_to_dec_1);
  tcase_add_test(tc, from_int_to_dec_2);
  tcase_add_test(tc, from_int_to_dec_3);

  tcase_add_test(tc, float_to_decimal_test_1);
  tcase_add_test(tc, float_to_decimal_test_3);

  // tcase_add_test(tc, test_int_to_dec_null_first_param);

  return s;
}