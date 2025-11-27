#include "test_s21_decimal.h"

START_TEST(fail_mul_1) {
  // степень 29
  s21_decimal decimal1 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, 0);
}

START_TEST(fail_mul_2) {
  // биты 0-15 не нули
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, 0);
}

START_TEST(fail_mul_3) {
  // биты 24-30 не нули
  s21_decimal decimal1 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, 0);
}

START_TEST(fail_mul_4) {
  // 7922816251426433759354395032.8
  s21_decimal decimal1 = {{0xFFFFFFF8, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 10.000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1B0000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_mul_5) {
  // 792281625142643.37593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
  // 782281625142643.37593543950335
  s21_decimal decimal2 = {{0x17FFFFFF, 0x602F7FC3, 0xFCC4D1C3, 0xE0000}};
  s21_decimal result;

  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_mul_6) {
  // 7922816251426433759354395032.8
  s21_decimal decimal1 = {{0xFFFFFFF8, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -10.000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801B0000}};
  s21_decimal result;

  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_eq(code, 2);
}

START_TEST(mul_1) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x100000}};
  // 3074.4573456182586025
  s21_decimal answer = {{0xAAAAAAA9, 0xAAAAAAAA, 0x1, 0x100000}};
  s21_decimal result;

  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(mul_2) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
  // 162389070814544768680495185.58
  s21_decimal answer = {{0x9C3D3FDE, 0xD33DA3EB, 0x34788254, 0x20000}};
  s21_decimal result;

  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(mul_3) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 12297829382473034409.999999385
  s21_decimal answer = {{0x82EE2199, 0xAAAAAAAA, 0x27BC86AA, 0x90000}};
  s21_decimal result;

  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(mul_4) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -3074457345618258602.4999999994
  s21_decimal answer = {{0x475359FA, 0xAAAAAAAA, 0x635750AA, 0x800A0000}};
  s21_decimal result;

  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(mul_5) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // -4871672124436343060.4148555676
  s21_decimal answer = {{0xD4B7BF9C, 0x79B8EBC2, 0x9D6986FE, 0x800A0000}};
  s21_decimal result;

  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(mul_6) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x150000}};
  // 162389070776735616809194041.03
  s21_decimal answer = {{0xFD781E47, 0x9EC52196, 0x34788254, 0x20000}};
  s21_decimal result;

  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(mul_7) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 6148914689804861439.9999999994
  s21_decimal answer = {{0xFFFFFFFA, 0x8EA6B3FF, 0xC6AEA154, 0xA0000}};
  s21_decimal result;

  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(mul_8) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 48716721233020685042.758212308
  s21_decimal answer = {{0xF8685AD4, 0xDC4F64C4, 0x9D6986FD, 0x90000}};
  s21_decimal result;

  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(mul_9) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x80100000}};
  // -15372.2867245121536000
  s21_decimal answer = {{0x0, 0x5555554D, 0x8, 0x80100000}};
  s21_decimal result;

  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

START_TEST(mul_10) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -7055.820576069728775806815669
  s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x80180000}};
  // -43385638788822555067041.628136
  s21_decimal answer = {{0xDEC6BFE8, 0x79C37D33, 0x8C2FC25F, 0x80060000}};
  s21_decimal result;

  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, answer), 1);
  ck_assert_int_eq(code, 0);
}

// START_TEST(mul_11) {
//     // 0.5
//     s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
//     // 7.9228162514264337593543950335
//     s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
//     // 8.422816251426433759354395034
//     s21_decimal answer = {{0xD99999A, 0xE981D9B8, 0x1B3730B7, 0x1B0000}};
//     s21_decimal result;

//     int code = s21_mul(decimal1, decimal2, &result);

//     ck_assert_int_eq(s21_is_equal(result, answer), 1);
//     ck_assert_int_eq(code, 0);
// }

// START_TEST(mul_12) {
//     // 0.5
//     s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
//     // -7.9228162514264337593543950335
//     s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
//     0x801C0000}};
//     // -7.4228162514264337593543950335
//     s21_decimal answer = {{0x77FFFFFF, 0xE0ED7ECF, 0xEFD818D0, 0x801C0000}};
//     s21_decimal result;

//     int code = s21_mul(decimal1, decimal2, &result);

//     ck_assert_int_eq(s21_is_equal(result, answer), 1);
//     ck_assert_int_eq(code, 0);
// }

// START_TEST(mul_13) {
//     // 0.5
//     s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
//     // -8
//     s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
//     // -7.5
//     s21_decimal answer = {{0x4B, 0x0, 0x0, 0x80010000}};
//     s21_decimal result;

//     int code = s21_mul(decimal1, decimal2, &result);

//     ck_assert_int_eq(s21_is_equal(result, answer), 1);
//     ck_assert_int_eq(code, 0);
// }

// START_TEST(mul_14) {
//      // 0.5
//      s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
//      // 49704001422.391670881925172831
//      s21_decimal decimal2 = {{0x7F7B8E5F, 0x2B4271A6, 0xA09A2FB4, 0x120000}};
//      // 49704001422.891670881925172831
//      s21_decimal answer = {{0x532D8E5F, 0x3232CD00, 0xA09A2FB4, 0x120000}};
//     s21_decimal result;

//     int code = s21_mul(decimal1, decimal2, &result);

//     ck_assert_int_eq(s21_is_equal(result, answer), 1);
//     ck_assert_int_eq(code, 0);
// }

// START_TEST(mul_15) {
//     // -0.5
//     s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x80010000}};
//     // 79228162514264337593543950335
//     s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
//     // 79228162514264337593543950334
//     s21_decimal answer = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
//     s21_decimal result;

//     int code = s21_mul(decimal1, decimal2, &result);

//     ck_assert_int_eq(s21_is_equal(result, answer), 1);
//     ck_assert_int_eq(code, 0);
// }

// START_TEST(mul_16) {
//     // 1431655765
//     s21_decimal decimal1 = {{0x55555555, 0x0, 0x0, 0x0}};
//     // 0
//     s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
//     // 1431655765
//     s21_decimal answer = {{0x55555555, 0x0, 0x0, 0x0}};
//     s21_decimal result;

//     int code = s21_mul(decimal1, decimal2, &result);

//     ck_assert_int_eq(s21_is_equal(result, answer), 1);
//     ck_assert_int_eq(code, 0);
// }

// START_TEST(mul_17) {
//     // 1431655765
//     s21_decimal decimal1 = {{0x55555555, 0x0, 0x0, 0x0}};
//     // -649244002.20841517182548587502
//     s21_decimal decimal2 = {{0x122233EE, 0x5675EBE6, 0xD1C83484,
//     0x80140000}};
//     // 782411762.79158482817451412498
//     s21_decimal answer = {{0x222DCC12, 0xFBF79F60, 0xFCCF9588, 0x140000}};
//     s21_decimal result;

//     int code = s21_mul(decimal1, decimal2, &result);

//     ck_assert_int_eq(s21_is_equal(result, answer), 1);
//     ck_assert_int_eq(code, 0);
// }

// START_TEST(mul_18) {
//     // -1431655765
//     s21_decimal decimal1 = {{0x55555555, 0x0, 0x0, 0x80000000}};
//     // 79228162514264337593543950335
//     s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
//     // 79228162514264337592112294570
//     s21_decimal answer = {{0xAAAAAAAA, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
//     s21_decimal result;

//     int code = s21_mul(decimal1, decimal2, &result);

//     ck_assert_int_eq(s21_is_equal(result, answer), 1);
//     ck_assert_int_eq(code, 0);
// }

// START_TEST(mul_19) {
//     // -1431655765
//     s21_decimal decimal1 = {{0x55555555, 0x0, 0x0, 0x80000000}};
//     // -7922816251426433759354395035
//     s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999,
//     0x80000000}};
//     // -7922816251426433760786050800
//     s21_decimal answer = {{0xEEEEEEF0, 0x99999999, 0x19999999, 0x80000000}};
//     s21_decimal result;

//     int code = s21_mul(decimal1, decimal2, &result);

//     ck_assert_int_eq(s21_is_equal(result, answer), 1);
//     ck_assert_int_eq(code, 0);
// }

Suite *suite_s21_mul(void) {
  Suite *mul = suite_create("mul");
  TCase *tc_mul = tcase_create("mul");

  suite_add_tcase(mul, tc_mul);
  // tcase_add_test(tc, mul);
  // tcase_add_test(tc, first_negative_mul);
  tcase_add_test(tc_mul, fail_mul_1);
  tcase_add_test(tc_mul, fail_mul_2);
  tcase_add_test(tc_mul, fail_mul_3);
  tcase_add_test(tc_mul, fail_mul_4);
  tcase_add_test(tc_mul, fail_mul_5);
  tcase_add_test(tc_mul, fail_mul_6);
  tcase_add_test(tc_mul, mul_1);
  tcase_add_test(tc_mul, mul_2);
  tcase_add_test(tc_mul, mul_3);
  tcase_add_test(tc_mul, mul_4);
  tcase_add_test(tc_mul, mul_5);
  tcase_add_test(tc_mul, mul_6);
  tcase_add_test(tc_mul, mul_7);
  tcase_add_test(tc_mul, mul_8);
  tcase_add_test(tc_mul, mul_9);
  tcase_add_test(tc_mul, mul_10);
  // tcase_add_test(tc, mul_11);
  // tcase_add_test(tc, mul_12);
  // tcase_add_test(tc, mul_13);
  // tcase_add_test(tc, mul_14);
  // tcase_add_test(tc, mul_15);
  // tcase_add_test(tc, mul_16);
  // tcase_add_test(tc, mul_17);
  // tcase_add_test(tc, mul_18);
  // tcase_add_test(tc, mul_19);

  return mul;
}