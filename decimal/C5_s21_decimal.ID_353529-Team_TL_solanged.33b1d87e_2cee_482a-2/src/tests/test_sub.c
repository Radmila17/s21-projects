#include "test_s21_decimal.h"

START_TEST(fail_sub_1) {
  // степень 29
  s21_decimal decimal1 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, 0);
}

START_TEST(fail_sub_2) {
  // биты 0-15 не нули
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, 0);
}

START_TEST(fail_sub_3) {
  // биты 24-30 не нули
  s21_decimal decimal1 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, 0);
}

START_TEST(fail_sub_4) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_sub_5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  s21_decimal result;

  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_sub_6) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal result;

  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_eq(code, 2);
}

START_TEST(sub_1) {
  // -7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // -7922816251426433759380804421
  s21_decimal answer = {{0x9B2C9345, 0x99999999, 0x19999999, 0x80000000}};
  s21_decimal result;

  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(sub_2) {
  // -7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // -7922816251426433759354395034
  s21_decimal answer = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  s21_decimal result;

  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(sub_3) {
  // -7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // 60233732531769558296976156804
  s21_decimal decimal2 = {{0x4C23E884, 0x648C702C, 0xC2A02CFF, 0x0}};
  // -68156548783195992056330551838
  s21_decimal answer = {{0xE5BD821E, 0xFE2609C5, 0xDC39C698, 0x80000000}};
  s21_decimal result;

  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(sub_4) {
  // 7922816251426433759354395035
  s21_decimal decimal1 = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 1.5
  s21_decimal answer = {{0xF, 0x0, 0x0, 0x10000}};
  s21_decimal result;

  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(sub_5) {
  // 7922816251426433759354395035
  s21_decimal decimal1 = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -18486571247179430748688726970
  s21_decimal answer = {{0xBBBBBBBA, 0x66666666, 0x3BBBBBBB, 0x80000000}};
  s21_decimal result;

  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(sub_6) {
  // -7922816251426433759354395035
  s21_decimal decimal1 = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -7922816251426433759354395034
  s21_decimal answer = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  s21_decimal result;

  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(sub_7) {
  // 26409387
  s21_decimal decimal1 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // 1458065152
  s21_decimal answer = {{0x56E84F00, 0x0, 0x0, 0x0}};
  s21_decimal result;

  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(sub_8) {
  // 26409387
  s21_decimal decimal1 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal answer = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;

  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(sub_9) {
  // 26409387
  s21_decimal decimal1 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // -3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  // 26409390.6336660283201536
  s21_decimal answer = {{0x5F6C1800, 0x8F3187B5, 0x37EC, 0x100000}};
  s21_decimal result;

  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(sub_10) {
  // -26409387
  s21_decimal decimal1 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // -52818774.498605864508043122005
  s21_decimal answer = {{0xAA355555, 0xF8741FF5, 0xAAAAAA8E, 0x80150000}};
  s21_decimal result;

  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

// START_TEST(sub_11) {
//     // 0.5
//     s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
//     // 7.9228162514264337593543950335
//     s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
//     // 8.422816251426433759354395034
//     s21_decimal answer = {{0xD99999A, 0xE981D9B8, 0x1B3730B7, 0x1B0000}};
//     s21_decimal result;

//     int code = s21_sub(decimal1, decimal2, &result);

//     ck_assert_int_eq(s21_is_equal(result, answer), 1);
//     ck_assert_int_eq(code, 0);
// }

// START_TEST(sub_12) {
//     // 0.5
//     s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
//     // -7.9228162514264337593543950335
//     s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
//     0x801C0000}};
//     // -7.4228162514264337593543950335
//     s21_decimal answer = {{0x77FFFFFF, 0xE0ED7ECF, 0xEFD818D0, 0x801C0000}};
//     s21_decimal result;

//     int code = s21_sub(decimal1, decimal2, &result);

//     ck_assert_int_eq(s21_is_equal(result, answer), 1);
//     ck_assert_int_eq(code, 0);
// }

// START_TEST(sub_13) {
//     // 0.5
//     s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
//     // -8
//     s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
//     // -7.5
//     s21_decimal answer = {{0x4B, 0x0, 0x0, 0x80010000}};
//     s21_decimal result;

//     int code = s21_sub(decimal1, decimal2, &result);

//     ck_assert_int_eq(s21_is_equal(result, answer), 1);
//     ck_assert_int_eq(code, 0);
// }

// START_TEST(sub_14) {
//      // 0.5
//      s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
//      // 49704001422.391670881925172831
//      s21_decimal decimal2 = {{0x7F7B8E5F, 0x2B4271A6, 0xA09A2FB4, 0x120000}};
//      // 49704001422.891670881925172831
//      s21_decimal answer = {{0x532D8E5F, 0x3232CD00, 0xA09A2FB4, 0x120000}};
//     s21_decimal result;

//     int code = s21_sub(decimal1, decimal2, &result);

//     ck_assert_int_eq(s21_is_equal(result, answer), 1);
//     ck_assert_int_eq(code, 0);
// }

// START_TEST(sub_15) {
//     // -0.5
//     s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x80010000}};
//     // 79228162514264337593543950335
//     s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
//     // 79228162514264337593543950334
//     s21_decimal answer = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
//     s21_decimal result;

//     int code = s21_sub(decimal1, decimal2, &result);

//     ck_assert_int_eq(s21_is_equal(result, answer), 1);
//     ck_assert_int_eq(code, 0);
// }

// START_TEST(sub_16) {
//     // 1431655765
//     s21_decimal decimal1 = {{0x55555555, 0x0, 0x0, 0x0}};
//     // 0
//     s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
//     // 1431655765
//     s21_decimal answer = {{0x55555555, 0x0, 0x0, 0x0}};
//     s21_decimal result;

//     int code = s21_sub(decimal1, decimal2, &result);

//     ck_assert_int_eq(s21_is_equal(result, answer), 1);
//     ck_assert_int_eq(code, 0);
// }

// START_TEST(sub_17) {
//     // 1431655765
//     s21_decimal decimal1 = {{0x55555555, 0x0, 0x0, 0x0}};
//     // -649244002.20841517182548587502
//     s21_decimal decimal2 = {{0x122233EE, 0x5675EBE6, 0xD1C83484,
//     0x80140000}};
//     // 782411762.79158482817451412498
//     s21_decimal answer = {{0x222DCC12, 0xFBF79F60, 0xFCCF9588, 0x140000}};
//     s21_decimal result;

//     int code = s21_sub(decimal1, decimal2, &result);

//     ck_assert_int_eq(s21_is_equal(result, answer), 1);
//     ck_assert_int_eq(code, 0);
// }

// START_TEST(sub_18) {
//     // -1431655765
//     s21_decimal decimal1 = {{0x55555555, 0x0, 0x0, 0x80000000}};
//     // 79228162514264337593543950335
//     s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
//     // 79228162514264337592112294570
//     s21_decimal answer = {{0xAAAAAAAA, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
//     s21_decimal result;

//     int code = s21_sub(decimal1, decimal2, &result);

//     ck_assert_int_eq(s21_is_equal(result, answer), 1);
//     ck_assert_int_eq(code, 0);
// }

// START_TEST(sub_19) {
//     // -1431655765
//     s21_decimal decimal1 = {{0x55555555, 0x0, 0x0, 0x80000000}};
//     // -7922816251426433759354395035
//     s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999,
//     0x80000000}};
//     // -7922816251426433760786050800
//     s21_decimal answer = {{0xEEEEEEF0, 0x99999999, 0x19999999, 0x80000000}};
//     s21_decimal result;

//     int code = s21_sub(decimal1, decimal2, &result);

//     ck_assert_int_eq(s21_is_equal(result, answer), 1);
//     ck_assert_int_eq(code, 0);
// }

Suite *suite_s21_sub(void) {
  Suite *s_sub = suite_create("sub");
  TCase *tc_sub = tcase_create("sub");

  suite_add_tcase(s_sub, tc_sub);
  // tcase_add_test(tc, sub);
  // tcase_add_test(tc, first_negative_sub);
  tcase_add_test(tc_sub, fail_sub_1);
  tcase_add_test(tc_sub, fail_sub_2);
  tcase_add_test(tc_sub, fail_sub_3);
  tcase_add_test(tc_sub, fail_sub_4);
  tcase_add_test(tc_sub, fail_sub_5);
  tcase_add_test(tc_sub, fail_sub_6);
  tcase_add_test(tc_sub, sub_1);
  tcase_add_test(tc_sub, sub_2);
  tcase_add_test(tc_sub, sub_3);
  tcase_add_test(tc_sub, sub_4);
  tcase_add_test(tc_sub, sub_5);
  tcase_add_test(tc_sub, sub_6);
  tcase_add_test(tc_sub, sub_7);
  tcase_add_test(tc_sub, sub_8);
  tcase_add_test(tc_sub, sub_9);
  tcase_add_test(tc_sub, sub_10);
  // tcase_add_test(tc, sub_11);
  // tcase_add_test(tc, sub_12);
  // tcase_add_test(tc, sub_13);
  // tcase_add_test(tc, sub_14);
  // tcase_add_test(tc, sub_15);
  // tcase_add_test(tc, sub_16);
  // tcase_add_test(tc, sub_17);
  // tcase_add_test(tc, sub_18);
  // tcase_add_test(tc, sub_19);

  return s_sub;
}