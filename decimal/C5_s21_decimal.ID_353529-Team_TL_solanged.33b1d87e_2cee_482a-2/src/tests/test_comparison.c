#include "test_s21_decimal.h"

// 0x80000000 = -
// 0x130000 = scale 19
START_TEST(is_equal_true) {
  s21_decimal a = {{23, 0, 0, 0x80000000}};
  s21_decimal b = {{23, 0, 0, 0x80000000}};

  ck_assert_int_eq(s21_is_equal(a, b), TRUE);
}

START_TEST(is_equal_false) {
  s21_decimal a = {{24, 0, 0, 0}};
  s21_decimal b = {{23, 0, 0, 0}};

  ck_assert_int_eq(s21_is_equal(a, b), FALSE);
}

START_TEST(is_greater_true) {
  s21_decimal a = {{24, 0, 0, 0}};
  s21_decimal b = {{23, 0, 0, 0}};

  ck_assert_int_eq(s21_is_greater(a, b), TRUE);
}

START_TEST(is_greater_false) {
  s21_decimal a = {{27, 0, 0, 0}};
  s21_decimal b = {{90, 0, 0, 0}};

  ck_assert_int_eq(s21_is_greater(a, b), FALSE);
}

START_TEST(is_greater_false_first_negative) {
  s21_decimal a = {{27, 0, 0, 0}};
  s21_decimal b = {{90, 0, 0, 0}};

  ck_assert_int_eq(s21_is_greater(a, b), FALSE);
}

START_TEST(is_greater_false_second_negative) {
  s21_decimal a = {{27, 0, 0, 0}};
  s21_decimal b = {{90, 0, 0, 0x80000000}};

  ck_assert_int_eq(s21_is_greater(a, b), TRUE);
}

START_TEST(is_less_true_first_negative) {
  s21_decimal a = {{27, 0, 0, 0x80000000}};
  s21_decimal b = {{90, 0, 0, 0}};

  ck_assert_int_eq(s21_is_less(a, b), TRUE);
}

START_TEST(is_less_false_second_negative) {
  s21_decimal a = {{27, 0, 0, 0}};
  s21_decimal b = {{90, 0, 0, 0x80000000}};

  ck_assert_int_eq(s21_is_less(a, b), FALSE);
}

START_TEST(is_less_true) {
  s21_decimal a = {{27, 0, 0, 0}};
  s21_decimal b = {{90, 0, 0, 0}};

  ck_assert_int_eq(s21_is_less(a, b), TRUE);
}

START_TEST(is_less_true_scale) {
  s21_decimal a = {{27, 0, 0, 0x130000}};
  s21_decimal b = {{90, 0, 0, 0}};

  ck_assert_int_eq(s21_is_less(a, b), TRUE);
}

START_TEST(is_less_false) {
  s21_decimal a = {{27, 0, 0, 0}};
  s21_decimal b = {{90, 0, 0, 0x130000}};

  ck_assert_int_eq(s21_is_less(a, b), FALSE);
}

START_TEST(is_equal_false_scale) {
  s21_decimal a = {{90, 0, 0, 0}};
  s21_decimal b = {{90, 0, 0, 0x130000}};

  ck_assert_int_eq(s21_is_equal(a, b), FALSE);
}

START_TEST(is_less_or_equal_false_scale) {
  s21_decimal a = {{90, 0, 0, 0}};
  s21_decimal b = {{90, 0, 0, 0}};

  ck_assert_int_eq(s21_is_less_or_equal(a, b), TRUE);
}

START_TEST(is_greater_or_equal_true) {
  s21_decimal a = {{90, 0, 0, 0}};
  s21_decimal b = {{90, 0, 0, 0}};

  ck_assert_int_eq(s21_is_greater_or_equal(a, b), TRUE);
}

START_TEST(is_not_equal_false) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_is_not_equal(a, b), FALSE);
}

START_TEST(is_not_equal_true) {
  s21_decimal a = {{90, 0, 0, 0}};
  s21_decimal b = {{91, 0, 0, 0}};

  ck_assert_int_eq(s21_is_not_equal(a, b), TRUE);
}

Suite *suite_s21_comparison() {
  Suite *comparison = suite_create("comparison");
  TCase *test = tcase_create("test");
  suite_add_tcase(comparison, test);
  tcase_add_test(test, is_equal_true);
  tcase_add_test(test, is_equal_false);
  tcase_add_test(test, is_greater_false);
  tcase_add_test(test, is_greater_false_first_negative);
  tcase_add_test(test, is_greater_false_second_negative);
  tcase_add_test(test, is_less_true_first_negative);
  tcase_add_test(test, is_less_false_second_negative);
  tcase_add_test(test, is_less_true_scale);
  tcase_add_test(test, is_less_false);
  tcase_add_test(test, is_equal_false_scale);
  tcase_add_test(test, is_less_true);
  tcase_add_test(test, is_greater_true);
  tcase_add_test(test, is_less_or_equal_false_scale);
  tcase_add_test(test, is_greater_or_equal_true);
  tcase_add_test(test, is_not_equal_true);
  tcase_add_test(test, is_not_equal_false);
  return comparison;
}