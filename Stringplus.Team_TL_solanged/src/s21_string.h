#ifndef S21_STRING_H
#define S21_STRING_H

#include <ctype.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#define BUF_SIZE 3000
#define s21_NULL ((void *)0)
#define OK 1
#define FAIL 0

typedef unsigned long s21_size_t;
typedef struct options {
  int minus;
  int plus;
  int space;
  int zero;
  int width;
  char width_arr[BUF_SIZE];
  int precision;
  char precision_arr[BUF_SIZE];
  int width_count;
  int precision_count;
  int dot;
  int percent;
  int num_system;
  int length;
  char spec;
  int negative;
  int int_count;
  int percent_flag;
  int zero_flag;
  int hash;
} options;

typedef struct sscanf_t {
  int percent;
  int percent_flag;
  char spec;
  char num_size_buf[300];
  int num_count;
  int num;
  int star;
  int minus;
  int num_flag;
  int s_flag;
} sscanf_t;

s21_size_t s21_strlen(const char *str);
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strrchr(const char *str, int c);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

////
int s21_sscanf(const char *str, const char *format, ...);
int s21_sprintf(char *str, const char *format, ...);
int collect_options(struct options *opt, const char format, va_list *params);
void parse(char *p, const char *format, va_list *params);

int read_int(const char *format, int *size);
int is_simple_text(const char format, struct options *opt);
int is_specifier(char format);
int is_length(char format);
int find_digits_count(unsigned long long temp, struct options *opt);
void write_scientific(char *str, double num, struct options *opt);

void s21_modify(char *str, struct options *opt, va_list *params);
void print_symbol(char *result, int len, char sym);
char *write_formatted_string(char *str, char *format, struct options *opt,
                             char *temp_str, int blank_count, int temp_size);
void to_one_string(char *str, char *format, struct options *opt);

void write_int(char *str, unsigned long long int temp, struct options *opt);
void write_char(char *str, char temp);
void write_float(char *str, long double temp, struct options *opt);
void update_struct(struct options *opt);
char *s21_strerror(int errnum);

/// sscanf
void sscanf_parse(const char *str, const char *format, va_list *params,
                  int *return_count);
void sscanf_modify(const char *str, sscanf_t *opt, va_list *params, int *p,
                   int *return_count);
void sscanf_collect_options(sscanf_t *opt, const char format);
void reset_opt(sscanf_t *opt);
float read_float(const char *buf_num, int *size);
void work_with_float(const char *str, sscanf_t *opt, va_list *params, int *p,
                     int *return_count);
void work_with_integer(const char *str, sscanf_t *opt, va_list *params, int *p,
                       int *return_count);
void work_with_string(const char *str, sscanf_t *opt, va_list *params, int *p,
                      int *return_count);
#endif