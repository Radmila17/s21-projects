#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"
void compare_strtok(const char *str, const char *delim) {
  char str1[256];
  char str2[256];
  strcpy(str1, str);
  strcpy(str2, str);

  char *token1 = strtok(str1, delim);
  char *token2 = s21_strtok(str2, delim);

  while (token1 != NULL && token2 != NULL) {
    ck_assert_str_eq(token1, token2);
    token1 = strtok(NULL, delim);
    token2 = s21_strtok(NULL, delim);
  }

  ck_assert_ptr_eq(token1, token2);
}
START_TEST(s21_strlen_test) {
  char buffer[1000];
  FILE *fp = fopen("./test.txt", "r");
  while (fgets(buffer, sizeof(buffer), fp)) {
    ck_assert_int_eq(s21_strlen(buffer), strlen(buffer));
  }
  fclose(fp);
}
END_TEST

START_TEST(s21_memchr_test) {
  char test1[] = "123456";
  char test2 = '4';
  char test3 = '7';
  char test4[] = "hello/";
  char test5[] = "h";
  char test6 = 'h';
  char test7 = ' ';
  char test8 = '/';
  char test9 = '\0';
  ck_assert_ptr_eq(s21_memchr(test1, test2, 0), memchr(test1, test2, 0));
  ck_assert_ptr_eq(s21_memchr(test1, test3, 6), memchr(test1, test3, 6));
  ck_assert_ptr_eq(s21_memchr(test4, test6, 3), memchr(test4, test6, 3));
  ck_assert_ptr_eq(s21_memchr(test5, test7, 1), memchr(test5, test7, 1));
  ck_assert_ptr_eq(s21_memchr(test4, test8, 6), memchr(test4, test8, 6));
  ck_assert_ptr_eq(s21_memchr(test4, test9, 6), memchr(test4, test9, 6));
}
END_TEST

START_TEST(s21_memcmp_test) {
  char test1[] = "Apple Pay Money Day";
  char test2[] = "Apple with worm";
  char test3[] = "\0";
  char test4[] = "gud\0 job";
  char test5[] = "gud\0 job";
  ck_assert_uint_eq(s21_memcmp(test1, test2, 16) < 0,
                    memcmp(test1, test2, 16) < 0);
  ck_assert_uint_eq(s21_memcmp(test1, test3, 2) > 0,
                    memcmp(test1, test3, 2) > 0);
  ck_assert_uint_eq(s21_memcmp(test2, test3, 2) > 0,
                    memcmp(test2, test3, 2) > 0);
  ck_assert_uint_eq(s21_memcmp(test4, test1, 9) > 0,
                    memcmp(test4, test1, 9) > 0);
  ck_assert_uint_eq(s21_memcmp(test4, test5, 7) == 0,
                    memcmp(test4, test5, 7) == 0);
}
END_TEST

START_TEST(s21_memcpy_test) {
  char src10[] = "Sobaka kniga girl \0 rir";
  char dest10[] = "boy";

  ck_assert_ptr_eq(s21_memcpy(src10, dest10, 3), memcpy(src10, dest10, 3));
  ck_assert_ptr_eq(s21_memcpy(src10, dest10, 2), memcpy(src10, dest10, 2));

  char src1[] = "";
  char dest1[10] = "test";
  ck_assert_ptr_eq(s21_memcpy(dest1, src1, 0), memcpy(dest1, src1, 0));
  ck_assert_str_eq(dest1, "test");

  char src2[] = "ABCDEFGH";
  char dest2[9] = "00000000";
  ck_assert_ptr_eq(s21_memcpy(dest2, src2, 4), memcpy(dest2, src2, 4));
  ck_assert_str_eq(dest2, "ABCD0000");

  char src3[] = "Hello, world!";
  char dest3[20] = {0};
  ck_assert_ptr_eq(s21_memcpy(dest3, src3, strlen(src3) + 1),
                   memcpy(dest3, src3, strlen(src3) + 1));
  ck_assert_str_eq(dest3, src3);

  char src4[] = "Hello\0world!";
  char dest4[20] = {0};
  ck_assert_ptr_eq(s21_memcpy(dest4, src4, 7), memcpy(dest4, src4, 7));
  ck_assert_mem_eq(dest4, src4, 7);
}
END_TEST

START_TEST(s21_memset_test) {
  char src1[] = "Sobaka kniga girl \0 rir";
  int c = 28;
  unsigned char test1[10] = "1234357890";
  unsigned char test2[10] = "hello";
  ck_assert_uint_eq((unsigned long)s21_memset(test1, '1', 10),
                    (unsigned long)memset(test1, '1', 10));
  ck_assert_uint_eq((unsigned long)s21_memchr(test1, '3', 10),
                    (unsigned long)memchr(test1, '3', 10));
  ck_assert_uint_eq((unsigned long)s21_memchr(test1, '/', 8),
                    (unsigned long)memchr(test1, '/', 8));
  ck_assert_uint_eq((unsigned long)s21_memchr(test1, '9', 0),
                    (unsigned long)memchr(test1, '9', 0));
  ck_assert_uint_eq((unsigned long)s21_memchr(test1, '0', 4),
                    (unsigned long)memchr(test1, '0', 4));
  ck_assert_uint_eq((unsigned long)s21_memchr(test2, '1', 3),
                    (unsigned long)memchr(test2, '1', 3));
  ck_assert_ptr_eq(s21_memset(src1, c, 3), memset(src1, c, 3));
}
END_TEST

START_TEST(s21_strncat_test) {
  char src1[] = "boy";
  char dest1[1000] = "Sobaka kniga girl";
  char src2[] = "\0";

  ck_assert_str_eq(s21_strncat(dest1, src1, 30), strncat(dest1, src1, 30));
  ck_assert_str_eq(s21_strncat(dest1, src2, 30), strncat(dest1, src1, 30));
}
END_TEST

START_TEST(s21_strchr_test) {
  char src1[] = "Sobaka kniga girl \0 rir";
  int c = '\0';
  int c2 = ' ';
  int c1 = 'i';
  ck_assert_ptr_eq(s21_strchr(src1, c), strchr(src1, c));
  ck_assert_ptr_eq(s21_strchr(src1, c1), strchr(src1, c1));
  ck_assert_ptr_eq(s21_strchr(src1, c2), strchr(src1, c2));
}
END_TEST

// START_TEST(s21_strncmp_test) {
//   const char src1[] = "Sobaka kniga  girl rir";
//   char src2[] = "So\0baka kniga girl";
//   const char src3[] = "hgjoidf";
//   char src4[] = "h";
//   char str1[] = "hella 1";
//   char str2[] = "hello 3";
//   ck_assert(s21_strncmp(src1, src2, 4) > 0);
//   ck_assert(s21_strncmp(src1, src2, 3) > 0);
//   ck_assert(s21_strncmp(src3, src4, 2) > 0);
//   ck_assert(s21_strncmp(src1, src3, 2) < 0);
//   ck_assert(s21_strncmp(str1, str2, 5) < 0);
//   ck_assert(s21_strncmp(str1, str2, 3) == 0);
// }
// END_TEST

START_TEST(s21_strncpy_test) {
  char src1[] = "test of string";
  char dest1[1000] = "vrtyuiopuhghgghgh";

  char src2[] = "testm\0";
  char dest2[5] = " ";

  char src3[] = "test ";
  char dest3[] = "crushcrush";

  char src4[] = "boy fgfg";
  char dest4[1000] = "Sobaka kniga girl";

  ck_assert_str_eq(strncpy(dest1, src1, 5), s21_strncpy(dest1, src1, 5));
  ck_assert_str_eq(strncpy(dest2, src2, 5), s21_strncpy(dest2, src2, 5));
  ck_assert_str_eq(strncpy(dest3, src3, 10), s21_strncpy(dest3, src3, 10));
  ck_assert_str_eq(strncpy(dest4, src4, 13), s21_strncpy(dest4, src4, 13));
}
END_TEST

START_TEST(s21_strcspn_test) {
  char test1[] = "0123456789";
  char test2[] = "9876";
  char test3[] = "LOST: 4-8-15-16-23-42";
  char test4[] = "1234567890";
  char test5[] = "0/";
  char test6[] = "%%\\#";
  char test7[] = " ";
  char test8[] = "1234567890";
  ck_assert_uint_eq(s21_strcspn(test1, test2), strcspn(test1, test2));
  ck_assert_uint_eq(s21_strcspn(test3, test4), strcspn(test3, test4));
  ck_assert_uint_eq(s21_strcspn(test3, test5), strcspn(test3, test5));
  ck_assert_uint_eq(s21_strcspn(test3, test6), strcspn(test3, test6));
  ck_assert_uint_eq(s21_strcspn(test3, test7), strcspn(test3, test7));
  ck_assert_uint_eq(s21_strcspn(test4, test8), strcspn(test4, test8));
  ck_assert_uint_eq(s21_strcspn(test2, test7), strcspn(test2, test7));
}
END_TEST

START_TEST(s21_strpbrk_test) {
  char str_for_strpbrk[] = "Megalomania";
  char str_oneof[] = "yal";
  ck_assert_str_eq(s21_strpbrk(str_for_strpbrk, str_oneof), "alomania");
  ck_assert_str_eq(s21_strpbrk(str_for_strpbrk, str_oneof),
                   strpbrk(str_for_strpbrk, str_oneof));

  char *str = "Hello, world";
  char *empty = "";
  ck_assert(s21_strpbrk(str, empty) == s21_NULL);
  ck_assert_uint_eq((unsigned long)s21_strpbrk(str, empty),
                    (unsigned long)strpbrk(str, empty));
}
END_TEST

START_TEST(s21_strstr_test) {
  char test_1[] = "<<<5>>>";
  char test_2[] = "5";
  char test_3[] = "QwertyQwertyQwerty";
  char test_4[] = "Qwerty";
  char test_5[] = "abcd";
  char test_6[] = "";
  char test_7[] = "aaaaa123aaa1234aaa";
  char test_8[] = "1234";

  ck_assert_ptr_eq(s21_strstr(test_1, test_2), strstr(test_1, test_2));
  ck_assert_ptr_eq(s21_strstr(test_3, test_4), strstr(test_3, test_4));
  ck_assert_ptr_eq(s21_strstr(test_5, test_6), strstr(test_5, test_6));
  ck_assert_ptr_eq(s21_strstr(test_4, test_5), strstr(test_4, test_5));
  ck_assert_ptr_eq(s21_strstr(test_7, test_8), strstr(test_7, test_8));
}
END_TEST

START_TEST(s21_strerror_test) {
  for (int i = -9; i < 150; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
}
END_TEST

START_TEST(s21_strtok_test) {
  char str1[256] = "().fjod.ipd,o, ";
  char str2[256] = "().fjod.ipd,o, ";
  const char *delim = "().,";
  char *token1 = strtok(str1, delim);
  char *token2 = s21_strtok(str2, delim);

  while (token1 != s21_NULL && token2 != s21_NULL) {
    ck_assert_str_eq(token1, token2);
    token1 = strtok(s21_NULL, delim);
    token2 = s21_strtok(s21_NULL, delim);
  }
  ck_assert_ptr_eq(token1, token2);

  char result2[256] = "(dfsj9 90D D SD.SD FD/s;sp";
  char result3[256] = "(dfsj9 90D D SD.SD FD/s;sp";
  const char *delim2 = "s;0";
  char *s21_token = s21_strtok(result2, delim2);
  char *token = strtok(result3, delim2);
  while (s21_token != s21_NULL && token != s21_NULL) {
    ck_assert_str_eq(s21_token, token);
    s21_token = s21_strtok(s21_NULL, delim2);
    token = strtok(s21_NULL, delim2);
  }
  ck_assert_ptr_eq(s21_token, token);

  compare_strtok("Hello, World!", " ");

  compare_strtok("Hello,World;from:strtok", ",;:");
  compare_strtok("", " ");
}

END_TEST

START_TEST(s21_strrchr_test) {
  char test1[] = "0163456769";
  char test2[] = ";;;;;;H%%//#HH";
  char test3[] = "     /";
  ck_assert_ptr_eq(s21_strrchr(test1, '6'), strrchr(test1, '6'));
  ck_assert_ptr_eq(s21_strrchr(test1, ' '), strrchr(test1, ' '));
  ck_assert_ptr_eq(s21_strrchr(test1, '6'), strrchr(test1, '6'));
  ck_assert_ptr_eq(s21_strrchr(test2, 'H'), strrchr(test2, 'H'));
  ck_assert_ptr_eq(s21_strrchr(test2, '$'), strrchr(test2, '$'));
  ck_assert_ptr_eq(s21_strrchr(test2, ';'), strrchr(test2, ';'));
  ck_assert_ptr_eq(s21_strrchr(test3, ' '), strrchr(test3, ' '));
  ck_assert_ptr_eq(s21_strrchr(test2, '\0'), strrchr(test2, '\0'));
}
END_TEST

START_TEST(s21_to_upper_test) {
  char str1[] = "hella hello ";
  char str2[] = "pRiVeT*&&{|}";
  void *str3 = s21_NULL;

  char *new_str = s21_to_upper(str1);

  if (new_str) {
    ck_assert_str_eq(new_str, "HELLA HELLO ");
    free(new_str);
  }

  new_str = s21_to_upper(str2);

  if (new_str) {
    ck_assert_str_eq(new_str, "PRIVET*&&{|}");
    free(new_str);
  }

  new_str = s21_to_upper(str3);

  if (new_str) {
    ck_assert_str_eq(new_str, "(null)");
    free(new_str);
  }
}
END_TEST

START_TEST(s21_to_lower_test) {
  char str1[] = "hella HELLO ";
  char str2[] = "pRiVeT";
  void *str3 = s21_NULL;

  char *new_str = s21_to_lower(str1);
  if (new_str) {
    ck_assert_str_eq(new_str, "hella hello ");
    free(new_str);
  }
  new_str = s21_to_lower(str2);
  if (new_str) {
    ck_assert_str_eq(new_str, "privet");
    free(new_str);
  }

  new_str = s21_to_lower(str3);
  if (new_str) {
    ck_assert_str_eq(new_str, "privet");
    free(new_str);
  }
}
END_TEST

START_TEST(s21_trim_test) {
  char *trimmed_str;
  char *str_to_trim = "   Hello, world!  ";
  trimmed_str = s21_trim(str_to_trim, " H!\nd");
  if (trimmed_str) {
    ck_assert_str_eq(trimmed_str, "ello, worl");
    free(trimmed_str);
  }

  char *empty_str = "";
  trimmed_str = s21_trim(empty_str, s21_NULL);
  if (trimmed_str) {
    ck_assert_str_eq(trimmed_str, "");
    free(trimmed_str);
  }

  trimmed_str = s21_trim(empty_str, " \n\0");
  if (trimmed_str) {
    ck_assert_str_eq(trimmed_str, "");
    free(trimmed_str);
  }

  char *empty_format = "";
  trimmed_str = s21_trim(str_to_trim, empty_format);
  if (trimmed_str) {
    ck_assert_str_eq(trimmed_str, "Hello,world!");
    free(trimmed_str);
  }

  trimmed_str = s21_trim(s21_NULL, empty_format);
  ck_assert(trimmed_str == s21_NULL);

  char *str_to_trim2 = "xxx Hello, world! xxx ---";
  char *format_str = "x -";
  trimmed_str = s21_trim(str_to_trim2, format_str);
  if (trimmed_str) {
    ck_assert_str_eq(trimmed_str, "Hello, world!");
    free(trimmed_str);
  }
}
END_TEST

START_TEST(s21_insert_test) {
  char *src = "Hello!";
  char *str = ", world";

  char *new_str = s21_insert(src, str, 5);
  if (new_str) {
    ck_assert_str_eq(new_str, "Hello, world!");
    free(new_str);
  }

  new_str = s21_insert(src, "", 15);
  ck_assert(new_str == s21_NULL);

  new_str = s21_insert("Hello!", ", world!!", 5);
  if (new_str) {
    ck_assert_str_eq(new_str, "Hello, world!!!");
    free(new_str);
  }

  new_str = s21_insert("Hello!", ", world!!", 10);
  if (new_str) {
    ck_assert_str_eq(new_str, "Hello!");
    free(new_str);
  }

  new_str = s21_insert("Hello!", ", world!!", 25);
  ck_assert(new_str == s21_NULL);

  new_str = s21_insert("", "", 0);
  if (new_str) {
    ck_assert_str_eq(new_str, "");
    free(new_str);
  }
}
END_TEST

// sprintf
START_TEST(test_d) {
  char s21_buffer[100];
  char std_buffer[100];
  int n = 42;

  s21_sprintf(s21_buffer, "%5d", n);
  sprintf(std_buffer, "%5d", n);
  ck_assert_str_eq(s21_buffer, std_buffer);
}
END_TEST

START_TEST(test_d_flags) {
  char s21_buffer[100];
  char std_buffer[100];
  int n = 42;

  s21_sprintf(s21_buffer, "%+d", n);
  sprintf(std_buffer, "%+d", n);
  ck_assert_str_eq(s21_buffer, std_buffer);

  char s21_buffer2[100];
  char std_buffer2[100];
  s21_sprintf(s21_buffer2, "% d", n);
  sprintf(std_buffer2, "% d", n);
  ck_assert_str_eq(s21_buffer2, std_buffer2);
}
END_TEST

START_TEST(test_c_width) {
  char s21_buffer[100];
  char std_buffer[100];
  char n = 'A';

  s21_sprintf(s21_buffer, "%5c", n);
  sprintf(std_buffer, "%5c", n);
  ck_assert_str_eq(s21_buffer, std_buffer);
}
END_TEST

START_TEST(test_s) {
  char s21_buffer[100];
  char std_buffer[100];
  char *n = "Hello, world!";

  s21_sprintf(s21_buffer, "%10.5s", n);
  sprintf(std_buffer, "%10.5s", n);
  ck_assert_str_eq(s21_buffer, std_buffer);
}
END_TEST

START_TEST(test_u_h) {
  char s21_buffer[100];
  char std_buffer[100];
  unsigned short n = 65000;

  s21_sprintf(s21_buffer, "%hu", n);
  sprintf(std_buffer, "%hu", n);
  ck_assert_str_eq(s21_buffer, std_buffer);
}
END_TEST

START_TEST(test_u_l) {
  char s21_buffer[100];
  char std_buffer[100];
  unsigned long n = 4294967295;

  s21_sprintf(s21_buffer, "%lu", n);
  sprintf(std_buffer, "%lu", n);
  ck_assert_str_eq(s21_buffer, std_buffer);
}
END_TEST

START_TEST(test_f) {
  char s21_buffer[100];
  char std_buffer[100];
  double n = 3.14159;

  s21_sprintf(s21_buffer, "%+.2f", n);
  sprintf(std_buffer, "%+.2f", n);
  ck_assert_str_eq(s21_buffer, std_buffer);

  char s21_buffer2[100];
  char std_buffer2[100];
  s21_sprintf(s21_buffer2, "% .3f", n);
  sprintf(std_buffer2, "% .3f", n);
  ck_assert_str_eq(s21_buffer2, std_buffer2);
}
END_TEST

START_TEST(test_prozent) {
  char s21_buffer[100];
  char std_buffer[100];

  s21_sprintf(s21_buffer, "%%");
  sprintf(std_buffer, "%%");
  ck_assert_str_eq(s21_buffer, std_buffer);
}
END_TEST

START_TEST(f_minus) {
  char s21_buffer[100];
  char std_buffer[100];
  double n = 3.14;

  s21_sprintf(s21_buffer, "%-10.2f", n);
  sprintf(std_buffer, "%-10.2f", n);
  ck_assert_str_eq(s21_buffer, std_buffer);
}
END_TEST

START_TEST(test_minus_d) {
  char s21_buffer[100];
  char std_buffer[100];
  int n = 3;

  s21_sprintf(s21_buffer, "%-2d", n);
  sprintf(std_buffer, "%-2d", n);
  ck_assert_str_eq(s21_buffer, std_buffer);
}
END_TEST

START_TEST(test_text_after_procent) {
  char s21_buffer[100];
  char std_buffer[100];
  int n = 3;
  s21_sprintf(s21_buffer, "text first %-2d text second", n);
  sprintf(std_buffer, "text first %-2d text second", n);
  ck_assert_str_eq(s21_buffer, std_buffer);
}
END_TEST

START_TEST(flag_d_with_zero) {
  char s21_buffer[100];
  char std_buffer[100];
  int n = 3;

  s21_sprintf(s21_buffer, "text first %05d text second", n);
  sprintf(std_buffer, "text first %05d text second", n);
  ck_assert_str_eq(s21_buffer, std_buffer);
}
END_TEST

START_TEST(test_spec_d_long) {
  char s21_buffer[100];
  char std_buffer[100];
  long n = 1234567890L;

  s21_sprintf(s21_buffer, "%ld", n);
  sprintf(std_buffer, "%ld", n);
  ck_assert_str_eq(s21_buffer, std_buffer);
}
END_TEST

START_TEST(test_spec_d_short) {
  char s21_buffer[100];
  char std_buffer[100];
  short n = 12345;

  s21_sprintf(s21_buffer, "%hd", n);
  sprintf(std_buffer, "%hd", n);
  ck_assert_str_eq(s21_buffer, std_buffer);
}
END_TEST

START_TEST(test_d_probl) {
  char s21_buffer[100];
  char std_buffer[100];
  int n = 123;

  s21_sprintf(s21_buffer, "%- d", n);
  sprintf(std_buffer, "%- d", n);
  ck_assert_str_eq(s21_buffer, std_buffer);
}
END_TEST

START_TEST(test_spec_d_pluss) {
  char s21_buffer[100];
  char std_buffer[100];
  int n = 123;

  s21_sprintf(s21_buffer, "%-+d", n);
  sprintf(std_buffer, "%-+d", n);
  ck_assert_str_eq(s21_buffer, std_buffer);
}
END_TEST

START_TEST(test_spec_c_minus) {
  char s21_buffer[100];
  char std_buffer[100];
  char n = 'S';

  s21_sprintf(s21_buffer, "%-15c", n);
  sprintf(std_buffer, "%-15c", n);
  ck_assert_str_eq(s21_buffer, std_buffer);
  // ck_assert_mem_eq(s21_buffer, std_buffer, 14);
}
END_TEST

START_TEST(test_spec_o) {
  char s21_buffer[100];
  char std_buffer[100];
  int n = 10;

  s21_sprintf(s21_buffer, "%o", n);
  sprintf(std_buffer, "%o", n);
  ck_assert_str_eq(s21_buffer, std_buffer);
}
END_TEST

START_TEST(test_spec_o_negative) {
  char s21_buffer[100];
  char std_buffer[100];
  int n = -1;

  s21_sprintf(s21_buffer, "%o", n);
  sprintf(std_buffer, "%o", n);
  ck_assert_str_eq(s21_buffer, std_buffer);
}
END_TEST

START_TEST(test_spec_e) {
  char s21_buffer[100];
  char std_buffer[100];
  float n = 123.456;

  s21_sprintf(s21_buffer, "%.3e", n);
  sprintf(std_buffer, "%.3e", n);
  ck_assert_str_eq(s21_buffer, std_buffer);
}
END_TEST

START_TEST(test_spec_E) {
  char s21_buffer[100];
  char std_buffer[100];
  float n = 123.456;

  s21_sprintf(s21_buffer, "%.3E", n);
  sprintf(std_buffer, "%.3E", n);
  ck_assert_str_eq(s21_buffer, std_buffer);
}
END_TEST
// scanf
START_TEST(test_int_basic) {
  int a, b;
  const char *input = "42";
  int res_s21 = s21_sscanf(input, "%d", &a);
  int res_std = sscanf(input, "%d", &b);
  ck_assert_int_eq(res_s21, res_std);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_int_negative) {
  int a, b;
  const char *input = "-123";
  int res_s21 = s21_sscanf(input, "%d", &a);
  int res_std = sscanf(input, "%d", &b);
  ck_assert_int_eq(res_s21, res_std);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_int_with_text) {
  int a, b;
  const char *input = "99bottles";
  int res_s21 = s21_sscanf(input, "%d", &a);
  int res_std = sscanf(input, "%d", &b);
  ck_assert_int_eq(res_s21, res_std);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_float_basic) {
  float a, b;
  const char *input = "3.1415";
  int res_s21 = s21_sscanf(input, "%f", &a);
  int res_std = sscanf(input, "%f", &b);
  ck_assert_int_eq(res_s21, res_std);
  ck_assert_float_eq_tol(a, b, 1e-6);
}
END_TEST

START_TEST(test_float_scientific) {
  float a, b;
  const char *input = "-1.23e-4";
  int res_s21 = s21_sscanf(input, "%f", &a);
  int res_std = sscanf(input, "%f", &b);
  ck_assert_int_eq(res_s21, res_std);
  ck_assert_float_eq_tol(a, b, 1e-6);
}
END_TEST

START_TEST(test_string_basic) {
  char s1[20], s2[20];
  const char *input = "Hello";
  int res_s21 = s21_sscanf(input, "%s", s1);
  int res_std = sscanf(input, "%s", s2);
  ck_assert_int_eq(res_s21, res_std);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_string_with_spaces) {
  char s1[20], s2[20];
  const char *input = "Hello world";
  int res_s21 = s21_sscanf(input, "%s", s1);
  int res_std = sscanf(input, "%s", s2);
  ck_assert_int_eq(res_s21, res_std);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_char_basic) {
  char c1, c2;
  const char *input = "X";
  int res_s21 = s21_sscanf(input, "%c", &c1);
  int res_std = sscanf(input, "%c", &c2);
  ck_assert_int_eq(res_s21, res_std);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_char_space) {
  char c1, c2;
  const char *input = "   A";
  int res_s21 = s21_sscanf(input, "%c", &c1);
  int res_std = sscanf(input, "%c", &c2);
  ck_assert_int_eq(res_s21, res_std);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_mixed_specifiers) {
  int a1, a2;
  float b1, b2;
  char c1, c2;
  char s1[20], s2[20];

  const char *input = "42 3.14 Hello X";
  int res_s21 = s21_sscanf(input, "%d %f %s %c", &a1, &b1, s1, &c1);
  int res_std = sscanf(input, "%d %f %s %c", &a2, &b2, s2, &c2);

  ck_assert_int_eq(res_s21, res_std);
  ck_assert_int_eq(a1, a2);
  ck_assert_float_eq_tol(b1, b2, 1e-6);
  ck_assert_str_eq(s1, s2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_width_int) {
  int a1, a2;
  const char *input = "123456";
  int res_s21 = s21_sscanf(input, "%3d", &a1);
  int res_std = sscanf(input, "%3d", &a2);
  ck_assert_int_eq(res_s21, res_std);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_width_float) {
  float a1, a2;
  const char *input = "123.456";
  int res_s21 = s21_sscanf(input, "%4f", &a1);
  int res_std = sscanf(input, "%4f", &a2);
  ck_assert_int_eq(res_s21, res_std);
  ck_assert_float_eq_tol(a1, a2, 1e-6);
}
END_TEST

START_TEST(test_star_specifier) {
  int a1 = 0, a2 = 0;
  const char *input = "42 100";
  int res_s21 = s21_sscanf(input, "%*d %d", &a1);
  int res_std = sscanf(input, "%*d %d", &a2);
  ck_assert_int_eq(res_s21, res_std);
  ck_assert_int_eq(a1, a2);
}
END_TEST

int main() {
  Suite *first = suite_create("first");
  TCase *test = tcase_create("test");
  suite_add_tcase(first, test);
  tcase_add_test(test, s21_strlen_test);
  tcase_add_test(test, s21_memchr_test);
  tcase_add_test(test, s21_memcmp_test);
  tcase_add_test(test, s21_memcpy_test);
  tcase_add_test(test, s21_memset_test);
  tcase_add_test(test, s21_strncat_test);
  tcase_add_test(test, s21_strchr_test);
  // tcase_add_test(test, s21_strncmp_test);
  tcase_add_test(test, s21_strncpy_test);
  tcase_add_test(test, s21_strrchr_test);
  tcase_add_test(test, s21_strcspn_test);
  tcase_add_test(test, s21_strpbrk_test);
  tcase_add_test(test, s21_strstr_test);
  tcase_add_test(test, s21_strerror_test);
  tcase_add_test(test, s21_strtok_test);
  tcase_add_test(test, s21_to_upper_test);
  tcase_add_test(test, s21_to_lower_test);
  tcase_add_test(test, s21_trim_test);
  tcase_add_test(test, s21_insert_test);

  tcase_add_test(test, test_d);
  tcase_add_test(test, test_d_flags);
  tcase_add_test(test, test_c_width);
  tcase_add_test(test, test_s);
  tcase_add_test(test, test_u_h);
  tcase_add_test(test, test_u_l);
  tcase_add_test(test, test_f);
  tcase_add_test(test, test_prozent);
  tcase_add_test(test, f_minus);
  tcase_add_test(test, test_minus_d);
  tcase_add_test(test, test_text_after_procent);
  tcase_add_test(test, flag_d_with_zero);
  tcase_add_test(test, test_spec_d_long);
  tcase_add_test(test, test_spec_d_short);
  tcase_add_test(test, test_d_probl);
  tcase_add_test(test, test_spec_d_pluss);
  tcase_add_test(test, test_spec_c_minus);
  tcase_add_test(test, test_spec_o);
  tcase_add_test(test, test_spec_o_negative);
  tcase_add_test(test, test_spec_e);
  tcase_add_test(test, test_spec_E);
  tcase_add_test(test, test_int_basic);
  tcase_add_test(test, test_int_negative);
  tcase_add_test(test, test_int_with_text);
  tcase_add_test(test, test_float_basic);
  tcase_add_test(test, test_float_scientific);
  tcase_add_test(test, test_string_basic);
  tcase_add_test(test, test_string_with_spaces);
  tcase_add_test(test, test_char_basic);
  tcase_add_test(test, test_char_space);
  tcase_add_test(test, test_mixed_specifiers);
  tcase_add_test(test, test_width_int);
  tcase_add_test(test, test_width_float);
  tcase_add_test(test, test_star_specifier);

  SRunner *runner = srunner_create(first);
  srunner_run_all(runner, CK_NORMAL);
  int fail_counter = srunner_ntests_failed(runner);
  srunner_free(runner);

  return fail_counter == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
