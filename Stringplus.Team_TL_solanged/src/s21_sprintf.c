#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  char *p = str;
  va_list params;
  va_start(params, format);
  parse(p, format, &params);
  va_end(params);
  return (p - str);
}

void parse(char *p, const char *format, va_list *params) {
  struct options opt = {0};
  opt.percent_flag = 0;
  opt.num_system = 10;
  const size_t format_len = s21_strlen(format);
  for (size_t i = 0; i < format_len;) {
    if ((format[i] == '%') || opt.percent_flag == 1) {
      i++;
      opt.percent_flag = 1;
      if (!is_simple_text(format[i], &opt)) {
        collect_options(&opt, format[i], params);
        if (opt.percent == 1) {
          *p = '%';
          p++;
          *p = '\0';
          opt.percent = 0;
        }
        if (opt.spec != 0) {
          s21_modify(p, &opt, params);
          p = p + s21_strlen(p);
          *p = '\0';
          opt.percent_flag = 0;
          i++;
          update_struct(&opt);
        }
      }
    } else {
      *p = format[i];
      p++;
      *p = '\0';
      i++;
    }
  }
}

void update_struct(struct options *opt) {
  opt->minus = 0;
  opt->plus = 0;
  opt->space = 0;
  opt->zero = 0;
  opt->width = 0;
  s21_memset(opt->width_arr, '\0', s21_strlen(opt->width_arr));
  opt->precision = 0;
  s21_memset(opt->precision_arr, '\0', s21_strlen(opt->precision_arr));
  opt->width_count = 0;
  opt->precision_count = 0;
  opt->dot = 0;
  opt->percent = 0;
  opt->num_system = 10;
  opt->length = 0;
  opt->spec = 0;
  opt->negative = 0;
  opt->int_count = 0;
  opt->percent_flag = 0;
  opt->zero_flag = 0;
  opt->hash = 0;
}

int collect_options(struct options *opt, const char format, va_list *params) {
  int flag = 0;
  if (format == '-') {
    opt->minus = 1;
  } else if (format == '+') {
    opt->plus = 1;
  } else if (format == ' ') {
    opt->space = 1;
  } else if (format == '0' && opt->zero_flag == 0) {
    opt->zero = 1;
  } else if (format == '%') {
    opt->percent = 1;
  } else if (format == '.') {
    opt->dot = 1;
  } else if (format == '#') {
    opt->hash = 1;
  } else if (format == '*' && opt->dot == 0) {
    opt->width = va_arg(*params, int);
  } else if (format == '*' && opt->dot == 1) {
    opt->precision = va_arg(*params, int);
    opt->dot = 0;
  } else if (opt->dot == 0 && isdigit(format) != 0) {
    opt->width_arr[opt->width_count] = format;
    opt->width_count++;
    opt->zero_flag = 1;
  } else if (opt->dot == 1 && isdigit(format) != 0) {
    opt->precision_arr[opt->precision_count] = format;
    opt->precision_count++;
  }
  if ((opt->plus == 1) && (opt->space == 1)) {
    opt->space = 0;
  }
  if ((opt->minus == 1) && (opt->zero == 1)) {
    opt->zero = 0;
  } else if (is_length(format)) {
    opt->length = format;
  } else if (is_specifier(format)) {
    opt->spec = format;
    flag = 1;
  }
  if (opt->spec != 0)
    opt->precision = read_int(opt->precision_arr, &opt->precision_count);
  if (opt->spec != 0) opt->width = read_int(opt->width_arr, &opt->width_count);
  return flag;
}

int is_simple_text(const char format, struct options *opt) {
  int flag = 1;
  if (s21_strchr("+-.#0% ", format) != NULL) {
    flag = 0;
  } else if ((is_specifier(format) || isdigit(format)) && opt->percent_flag) {
    flag = 0;
  }
  return flag;
}

int is_specifier(char format) {
  if (s21_strchr("cdfsuoEe", format) != NULL) {
    return 1;
  } else {
    return 0;
  }
}

int is_length(char format) {
  return (format == 'l' || format == 'L' || format == 'h') ? 1 : 0;
}

int read_int(const char *format, int *size) {
  unsigned long int value = 0;
  int i = 0;
  int minus = 0;
  if (format[i] == '-') {
    i++;
    minus = 1;
  }
  for (; i < *size; i++) {
    value *= 10;
    value += format[i] - '0';
  }
  if (minus == 1) {
    value *= -1;
  }
  return value;
}

void s21_modify(char *str, struct options *opt, va_list *params) {
  char temp_str[BUF_SIZE] = {0};
  char *t = temp_str;
  setlocale(LC_ALL, "");
  if (opt->spec == 'd') {
    if (opt->length == 0 || opt->length == 'h') {
      int temp = va_arg(*params, int);
      write_int(t, temp, opt);
      to_one_string(str, temp_str, opt);
    } else if (opt->length == 'l') {
      long long temp = va_arg(*params, long long int);
      write_int(t, temp, opt);
      to_one_string(str, temp_str, opt);
    }
  } else if (opt->spec == 'u') {
    unsigned long long int temp = va_arg(*params, unsigned long long int);
    opt->plus = 0;
    write_int(t, temp, opt);
    to_one_string(str, temp_str, opt);
  } else if (opt->spec == 'c') {
    opt->precision = 1;
    if (opt->length == 0 || opt->length == 'h') {
      char character = (char)va_arg(*params, int);
      write_char(t, character);
      to_one_string(str, temp_str, opt);
    } else if (opt->length == 'l') {
      wchar_t wtemp = va_arg(*params, wchar_t);
      char multi_str[1000];
      wctomb(multi_str, wtemp);
      s21_strncpy(temp_str, multi_str, s21_strlen(multi_str));
      to_one_string(str, temp_str, opt);
    }
  } else if (opt->spec == 's') {
    if (opt->length == 0 || opt->length == 'h') {
      char *temp = va_arg(*params, char *);
      to_one_string(str, temp, opt);
    } else if (opt->length == 'l') {
      wchar_t *wtemp = va_arg(*params, wchar_t *);
      char multi_str[1000];
      wcstombs(multi_str, wtemp, sizeof(multi_str));
      s21_strncpy(temp_str, multi_str, s21_strlen(multi_str));
      to_one_string(str, temp_str, opt);
    }
  } else if (opt->spec == 'f') {
    if (opt->precision == 0) {
      opt->precision = 6;
    }
    if (opt->length == 'L') {
      long double temp = va_arg(*params, long double);
      write_float(t, temp, opt);
      to_one_string(str, temp_str, opt);
    } else {
      double temp = va_arg(*params, double);
      write_float(t, temp, opt);
      to_one_string(str, temp_str, opt);
    }
  } else if (opt->spec == 'o') {
    unsigned long long int temp = va_arg(*params, unsigned long long int);
    opt->num_system = 8;
    write_int(t, temp, opt);
    to_one_string(str, temp_str, opt);

  } else if (opt->spec == 'e' || opt->spec == 'E') {
    double num = va_arg(*params, double);
    if (opt->precision < 0) {
      opt->precision = 6;
    }
    write_scientific(temp_str, num, opt);
    to_one_string(str, temp_str, opt);
  }
}

char *write_formatted_string(char *str, char *format, struct options *opt,
                             char *temp_str, int blank_count, int tempsize) {
  char *s = str;
  char fill_char = opt->zero ? '0' : ' ';
  int format_copy_len = tempsize;
  if (opt->spec == 'e' || opt->spec == 'E') {
    format_copy_len = s21_strlen(format);
  } else if (opt->precision >= 0) {
    format_copy_len = opt->precision;
  }

  if (opt->minus == 1) {
    s21_strncpy(s, temp_str, s21_strlen(temp_str));
    s += s21_strlen(temp_str);
    s21_strncpy(s, format, format_copy_len);
    s += format_copy_len;
    while (blank_count-- > 0) *s++ = fill_char;
  } else {
    if (opt->zero) {
      s21_strncpy(s, temp_str, s21_strlen(temp_str));
      s += s21_strlen(temp_str);
      while (blank_count-- > 0) *s++ = fill_char;
    } else {
      while (blank_count-- > 0) *s++ = fill_char;
      s21_strncpy(s, temp_str, s21_strlen(temp_str));
      s += s21_strlen(temp_str);
    }
    s21_strncpy(s, format, format_copy_len);
    s += format_copy_len;
  }

  return s;
}

void to_one_string(char *str, char *format, struct options *opt) {
  int blank_count = 0, zeroCount = 0, sign = 0;
  int tempsize = s21_strlen(format);
  char temp_str[1000] = {0};
  char *p = temp_str;
  if (opt->space == 1) {
    print_symbol(p, 1, ' ');
    p++;
  }
  if ((opt->spec != 'c') && (opt->spec != 's') && (opt->spec != 'o')) {
    if (opt->plus == 1) {
      print_symbol(p, 1, ((opt->negative == 1) ? '-' : '+'));
      sign = 1;
      p++;
    } else if (opt->plus == 0 && opt->negative == 1) {
      print_symbol(p, 1, '-');
      p++;
    }
  }

  if (opt->spec == 'o') {
    if (opt->hash == 1 && format[0] != '0') {
      print_symbol(p, 1, '0');
      p++;
      tempsize++;
    }
    if (opt->precision > tempsize) {
      zeroCount = opt->precision - tempsize;
      print_symbol(p, zeroCount, '0');
      p += zeroCount;
    } else if (opt->precision == 0 && format[0] == '0') {
      tempsize = 0;
    } else {
      opt->precision = tempsize;
    }
  }

  if (opt->spec == 'e' || opt->spec == 'E') {
    char *exp_ptr = s21_strchr(format, (opt->spec == 'E') ? 'E' : 'e');

    if (exp_ptr) {
      int mantissa_len = exp_ptr - format;
      if (opt->precision >= 0) {
        char *dot_ptr = s21_strchr(format, '.');
        int current_precision = 0;
        if (dot_ptr && dot_ptr < exp_ptr) {
          current_precision = exp_ptr - dot_ptr - 1;
        }
        if (opt->precision != current_precision) {
          tempsize = mantissa_len + 5;
        }
      }
    }
  }

  if (opt->spec == 'd' || opt->spec == 'u') {
    if ((opt->precision > 0) && (opt->precision < tempsize)) {
      opt->precision = tempsize;
    } else if (opt->precision > tempsize) {
      zeroCount = opt->precision - tempsize;
      print_symbol(p, zeroCount, '0');
      p += zeroCount;
    } else {
      opt->precision = tempsize;
    }
  }
  if (opt->spec == 's') {
    if ((opt->precision > 0) && (opt->precision < tempsize)) {
      blank_count = opt->width - opt->precision;
    } else {
      opt->precision = tempsize;
    }
  }
  if (opt->spec == 'f') {
    opt->precision += opt->int_count;
  }

  if (opt->spec != 's') {
    if ((opt->width > 0) && (opt->width < tempsize)) {
      opt->width = tempsize;
    } else if (opt->width > tempsize) {
      blank_count = opt->width - sign - tempsize - zeroCount;
    } else {
      opt->width = tempsize;
    }
  }

  if (opt->spec == 's') {
    opt->zero = 0;
  }
  str =
      write_formatted_string(str, format, opt, temp_str, blank_count, tempsize);
  *str = '\0';
}

void print_symbol(char *result, int len, char sym) {
  for (int i = 0; i < len; i++) {
    *result = sym;
    result++;
  }
}

int find_digits_count(unsigned long long temp, struct options *opt) {
  int count = 0;
  do {
    temp /= opt->num_system;
    count++;
  } while (temp != 0);
  return count;
}

void write_int(char *str, unsigned long long int temp, struct options *opt) {
  if ((long long)temp < 0 && (opt->spec == 'd' || opt->spec == 'i')) {
    opt->negative = 1;
    temp = -(long long)temp;
  }
  int size = find_digits_count(temp, opt);
  for (int i = 0; i < size; i++) {
    if (temp == 0) {
      str[0] = '0';
    } else {
      int res = temp % opt->num_system;
      if (res < 10) {
        str[i] = res + '0';
      } else {
        str[i] = res - 10 + 'a';
      }
      temp /= opt->num_system;
    }
  }
  for (int i = 0; i < size / 2; i++) {
    char x = str[i];
    str[i] = str[size - i - 1];
    str[size - i - 1] = x;
  }
}

void write_char(char *str, char temp) {
  if (str != NULL) {
    str[0] = temp;
  }
}

void write_float(char *str, long double temp, struct options *opt) {
  char *t = str;
  *t = '\0';
  if (temp < 0) {
    opt->negative = 1;
    temp = -temp;
  }
  long long int intPart = (long long int)temp;
  long double fracPart = temp - intPart;
  char intPartStr[100] = {0};
  int size = find_digits_count(intPart, opt);
  opt->int_count = (size + 1);
  for (int i = 0; i < size; i++) {
    if (intPart == 0) {
      intPartStr[0] = '0';
    } else {
      int res = intPart % 10;
      intPartStr[i] = res + '0';
      intPart /= 10;
    }
  }
  for (int i = 0; i < size / 2; i++) {
    char tempChar = intPartStr[i];
    intPartStr[i] = intPartStr[size - i - 1];
    intPartStr[size - i - 1] = tempChar;
  }
  if (opt->precision > 0) {
    s21_strncat(t, intPartStr, s21_strlen(intPartStr));
    s21_strncat(t, ".", 2);
    for (int i = 0; i < opt->precision - 1; i++) {
      fracPart *= 10;
      int fracDigit = (int)fracPart;
      fracPart -= fracDigit;

      if (s21_strlen(t) < 99) {
        t[s21_strlen(t)] = fracDigit + '0';
        t[s21_strlen(t) + 1] = '\0';
      }
    }
    if (opt->precision > 0 && s21_strlen(t) < 99) {
      fracPart *= 10;
      int fracDigit = (int)round(fracPart);
      t[s21_strlen(t)] = fracDigit + '0';
      t[s21_strlen(t) + 1] = '\0';
    }

  } else {
    s21_strncpy(t, intPartStr, s21_strlen(intPartStr));
  }
}

void write_scientific(char *str, double num, struct options *opt) {
  int exponent = 0;

  if (isinf(num)) {
    const char *inf_str = (opt->spec == 'E') ? "INF" : "inf";
    s21_strncpy(str, inf_str, 4);
    return;
  }
  if (isnan(num)) {
    const char *nan_str = (opt->spec == 'E') ? "NAN" : "nan";
    s21_strncpy(str, nan_str, 4);
    return;
  }

  if (num != 0.0) {
    exponent = (int)log10(fabs(num));
    num /= pow(10, exponent);
  }

  char significand[100] = {0};
  struct options float_opt = *opt;
  float_opt.precision = opt->precision;
  write_float(significand, num, &float_opt);

  if (opt->precision == 0) {
    char *dot = s21_strchr(significand, '.');
    if (dot) *dot = '\0';
  }

  char exponent_str[10] = {0};
  char exp_char = (opt->spec == 'E') ? 'E' : 'e';
  exponent_str[0] = exp_char;
  exponent_str[1] = (exponent < 0) ? '-' : '+';

  int abs_exp = abs(exponent);
  if (abs_exp < 10) {
    exponent_str[2] = '0';
    exponent_str[3] = abs_exp + '0';
  } else {
    exponent_str[2] = (abs_exp / 10) + '0';
    exponent_str[3] = (abs_exp % 10) + '0';
  }
  exponent_str[4] = '\0';

  s21_strncpy(str, significand, s21_strlen(significand));
  s21_strncat(str, exponent_str, 5);
}