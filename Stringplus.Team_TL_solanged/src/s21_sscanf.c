#include "s21_string.h"

int s21_sscanf(const char *str, const char *format, ...) {
  va_list params;
  va_start(params, format);
  int return_count = 0;
  sscanf_parse(str, format, &params, &return_count);
  va_end(params);
  return return_count;
}
void sscanf_parse(const char *str, const char *format, va_list *params,
                  int *return_count) {
  sscanf_t opt = {0};
  size_t len_format = s21_strlen(format);
  int p = 0;
  int flag = 0;
  for (size_t i = 0; i < len_format && flag != 1;) {
    if ((format[i] != str[p] && format[i] == '%') || opt.percent_flag == 1) {
      if (format[i] == '%') {
        i++;
        opt.percent_flag = 1;
      }
      sscanf_collect_options(&opt, format[i]);
      if (opt.spec != 0) {
        sscanf_modify(str, &opt, params, &p, return_count);
        reset_opt(&opt);
      }
    } else {
      if (format[i] == ' ') {
        while (str[p] == ' ') {
          p++;
        }
      } else {
        if (str[p] != format[i]) {
          flag = 1;
        }
        p++;
      }
    }
    i++;
  }
}

void reset_opt(sscanf_t *opt) {
  opt->percent = 0;
  opt->percent_flag = 0;
  opt->spec = 0;
  s21_memset(opt->num_size_buf, '\0', s21_strlen(opt->num_size_buf));
  opt->num_count = 0;
  opt->num = 0;
  opt->star = 0;
  opt->minus = 0;
  opt->num_flag = 0;
}
void sscanf_collect_options(sscanf_t *opt, const char format) {
  if (format == '*') {
    opt->star = 1;
  } else if (isdigit(format) != 0) {
    opt->num_flag = 1;
    opt->num_size_buf[opt->num_count] = format;
    opt->num_count++;
    opt->num = read_int(opt->num_size_buf, &opt->num_count);
  } else if (is_specifier(format)) {
    opt->spec = format;
  }
}

void sscanf_modify(const char *str, sscanf_t *opt, va_list *params, int *p,
                   int *return_count) {
  if (opt->spec == 'd' || opt->spec == 'u') {
    if ((str[*p] == ' ' || str[*p] == '-' || str[*p] == '+') ||
        isdigit(str[*p]) != 0) {
      work_with_integer(str, opt, params, p, return_count);
    } else {
    }
  }
  if (opt->spec == 'c') {
    if (opt->star != 1) {
      char *ptr = va_arg(*params, char *);
      *ptr = str[*p];
      if (opt->s_flag != 1) {
        *return_count = *return_count + 1;
      }
    }
    (*p)++;
  }
  if (opt->spec == 'f' || opt->spec == 'e' || opt->spec == 'E' ||
      opt->spec == 'G' || opt->spec == 'g') {
    if (str[*p] == ' ') {
      (*p)++;
    }
    if (((str[*p] == '-' || str[*p] == '+') && isdigit(str[(*p) + 1]) != 0) ||
        isdigit(str[*p]) != 0 ||
        (str[*p] == '.' && isdigit(str[(*p) + 1]) != 0)) {
      work_with_float(str, opt, params, p, return_count);
    } else {
      opt->s_flag = 1;
    }
  }
  if (opt->spec == 's') {
    work_with_string(str, opt, params, p, return_count);
  }
}

float read_float(const char *buf_num, int *size) {
  char integer[300] = {0}, frac[300] = {0}, e_buf[300] = {0};
  int count = 0, exp_flag = 0, minus = 0, e_size = 0;
  for (; buf_num[count] != '.' && buf_num[count] != 'e' && count < *size &&
         buf_num[count] != 'E';
       count++) {
    integer[count] = buf_num[count];
  }
  double res_int = (double)read_int(integer, &count);
  int dot = 0;
  double e_res_num = 0;
  if (buf_num[count] == '.' || buf_num[count] == 'e' || buf_num[count] == 'E') {
    if (buf_num[count] == '.') {
      dot = 1;
    } else {
      exp_flag = 1;
    }
    count += 1;
  }
  int i = 0;
  for (; dot == 1 && count < *size &&
         (buf_num[count] != 'e' && buf_num[count] != 'E');
       count++) {
    frac[i] = buf_num[count];
    i++;
  }
  double res_frac = (double)read_int(frac, &i);
  if (buf_num[count] == 'e' || buf_num[count] == 'E') {
    exp_flag = 1;
    count++;
  }
  if (exp_flag == 1) {
    if (buf_num[count] == '+') {
      count++;
    }
    for (; count < *size; count++, e_size++) {
      e_buf[e_size] = buf_num[count];
    }
    e_res_num = (double)read_int(e_buf, &e_size);
  }
  if (res_int < 0) {
    minus = 1;
    res_int *= -1;
  }
  double without_e = res_int + (res_frac / pow(10, i));
  double res = without_e * pow(10, e_res_num);
  if (minus == 1) {
    res *= -1;
  }
  return res;
}

void work_with_float(const char *str, sscanf_t *opt, va_list *params, int *p,
                     int *return_count) {
  int dot = 0;
  int exp_flag = 0;
  if ((str[*p] == '-' || str[*p] == '+')) {
    if (str[*p] == '-') {
      opt->minus = 1;
    }
    (*p)++;
  }
  char buf_num[300] = {0};
  int count_digit = 0;
  bool is_prev_element_tire = (str[(*p) - 1] == '-');
  if (is_prev_element_tire) {
    buf_num[count_digit] = str[(*p) - 1];
    count_digit++;
  }
  while (
      ((isdigit(str[*p]) != 0) || (str[*p] == '.' && dot == 0) ||
       ((str[*p] == 'e' || str[*p] == 'E') && exp_flag == 0) ||
       ((str[*p] == '+' || str[*p] == '-') && exp_flag &&
        isdigit(str[(*p) + 1]) != 0)) &&
      ((opt->num_flag == 1 && count_digit < opt->num) || opt->num_flag == 0) &&
      count_digit < 298) {
    if (str[*p] == '.') {
      dot = 1;
    } else if ((str[*p] == 'e' || str[*p] == 'E') && exp_flag == 0) {
      exp_flag = 1;
    }
    buf_num[count_digit] = str[*p];
    count_digit++;
    (*p)++;
  }
  buf_num[count_digit] = '\0';
  if (opt->star != 1) {
    float *res_dub = va_arg(*params, float *);
    *res_dub = read_float(buf_num, &count_digit);
    if (opt->s_flag != 1) {
      *return_count = *return_count + 1;
    }
  }
}

void work_with_integer(const char *str, sscanf_t *opt, va_list *params, int *p,
                       int *return_count) {
  while ((str[*p] == ' ' || str[*p] == '-') && opt->minus == 0 &&
         opt->spec != 'u') {
    if (str[*p] == '-') {
      opt->minus = 1;
    }
    (*p)++;
  }
  char buf_num[300] = {0};
  int count_digit = 0;
  if (opt->minus == 1) {
    buf_num[count_digit] = '-';
    count_digit++;
  }
  while (
      isdigit(str[*p]) != 0 &&
      ((opt->num_flag == 1 && count_digit < opt->num) || opt->num_flag == 0) &&
      count_digit < 298) {
    buf_num[count_digit] = str[(*p)];
    count_digit++;
    (*p)++;
  }
  buf_num[count_digit] = '\0';
  if (opt->star != 1) {
    int *ptr = va_arg(*params, int *);
    *ptr = read_int(buf_num, &count_digit);
    if (opt->s_flag != 1) {
      *return_count = *return_count + 1;
    }
  }
}

void work_with_string(const char *str, sscanf_t *opt, va_list *params, int *p,
                      int *return_count) {
  while (str[*p] == ' ') {
    (*p)++;
  }
  char for_s[1000];
  char *s_buf = for_s;
  int max_chars = 1000;
  if (opt->num_flag == 1) {
    max_chars = opt->num;
  }
  if (opt->star != 1) {
    s_buf = va_arg(*params, char *);
  }
  int i = 0;
  for (; str[*p] != ' ' && str[*p] != '\0' && str[*p] != '\n' && i < max_chars;
       i++, (*p)++) {
    s_buf[i] = str[*p];
  }
  if (str[*p] == '\0') {
    opt->s_flag = 1;
  } else {
    (*p)++;
  }
  s_buf[i] = '\0';
  *return_count = *return_count + 1;
}