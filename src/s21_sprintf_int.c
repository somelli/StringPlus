#include <stdarg.h>

#include "s21_string.h"

typedef struct {
  char num_str[64];
  int num_len;
  int is_negative;
  int has_plus;
  int has_space;
  int sign_size;
} s21_number_info;

typedef struct {
  int zeros_to_add;
  int spaces;
  int use_zero_padding;
  int total_length;
} s21_format_params;

static void s21_int_to_str(unsigned long long unum, char* buffer, int* len) {
  if (unum == 0) {
    buffer[0] = '0';
    *len = 1;
    return;
  }

  int i = 0;
  while (unum > 0) {
    buffer[i++] = (char)((unum % 10) + '0');
    unum /= 10;
  }
  *len = i;
}

static void s21_reverse_string(char* str, int len) {
  for (int i = 0; i < len / 2; i++) {
    char temp = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = temp;
  }
}

static unsigned long long s21_extract_unsigned(va_list* args,
                                               s21_format* current) {
  unsigned long long value = 0;

  if (current->length == 'h') {
    value = (unsigned short)va_arg(*args, unsigned int);
  } else if (current->length == 'l') {
    value = va_arg(*args, unsigned long);
  } else {
    value = va_arg(*args, unsigned int);
  }

  return value;
}

static long long s21_extract_signed(va_list* args, s21_format* current) {
  long long value = 0;

  if (current->length == 'h') {
    value = (short)va_arg(*args, int);
  } else if (current->length == 'l') {
    value = va_arg(*args, long);
  } else {
    value = va_arg(*args, int);
  }

  return value;
}

static void s21_calculate_params(s21_number_info* info, s21_format* current,
                                 s21_format_params* params) {
  params->zeros_to_add = 0;
  params->spaces = 0;
  params->use_zero_padding = 0;

  if (current->precision_set && current->precision > info->num_len) {
    params->zeros_to_add = current->precision - info->num_len;
  }

  int total_digits = info->num_len + params->zeros_to_add;
  params->total_length = total_digits + info->sign_size;

  if (current->width > params->total_length) {
    params->spaces = current->width - params->total_length;
  }

  if (current->width > params->total_length && !current->precision_set &&
      current->minus == 0 && current->zero == 1) {
    params->use_zero_padding = 1;
  }
}

static void s21_write_sign(char* str, int* result, s21_number_info* info) {
  if (info->is_negative) {
    str[(*result)++] = '-';
  } else if (info->has_plus) {
    str[(*result)++] = '+';
  } else if (info->has_space) {
    str[(*result)++] = ' ';
  }
}

static void s21_write_number(char* str, int* result, s21_number_info* info,
                             int zeros_to_add) {
  for (int i = 0; i < zeros_to_add; i++) {
    str[(*result)++] = '0';
  }

  for (int i = 0; i < info->num_len; i++) {
    str[(*result)++] = info->num_str[i];
  }
}

static void s21_format_right(char* str, int* result, s21_number_info* info,
                             s21_format_params* params) {
  if (!params->use_zero_padding) {
    for (int i = 0; i < params->spaces; i++) {
      str[(*result)++] = ' ';
    }
  }

  s21_write_sign(str, result, info);

  if (params->use_zero_padding) {
    for (int i = 0; i < params->spaces; i++) {
      str[(*result)++] = '0';
    }
  }

  s21_write_number(str, result, info, params->zeros_to_add);
}

static void s21_format_left(char* str, int* result, s21_number_info* info,
                            s21_format_params* params) {
  s21_write_sign(str, result, info);
  s21_write_number(str, result, info, params->zeros_to_add);

  for (int i = 0; i < params->spaces; i++) {
    str[(*result)++] = ' ';
  }
}

void s21_format_int(char* str, int* result, va_list* args,
                    s21_format* current) {
  s21_number_info info;
  info.num_len = 0;
  info.is_negative = 0;
  info.has_plus = 0;
  info.has_space = 0;
  info.sign_size = 0;

  unsigned long long magnitude = 0;

  if (current->specifier == 'u') {
    magnitude = s21_extract_unsigned(args, current);
  } else {
    long long value = s21_extract_signed(args, current);

    if (value < 0) {
      info.is_negative = 1;
      magnitude = (unsigned long long)(-(value + 1)) + 1ULL;
    } else {
      magnitude = (unsigned long long)value;
      if (current->plus) {
        info.has_plus = 1;
      } else if (current->space) {
        info.has_space = 1;
      }
    }
  }

  if (magnitude == 0 && current->precision_set && current->precision == 0) {
    info.num_len = 0;
    info.num_str[0] = '\0';
  } else {
    s21_int_to_str(magnitude, info.num_str, &info.num_len);
    s21_reverse_string(info.num_str, info.num_len);
  }

  if (info.is_negative || info.has_plus || info.has_space) {
    info.sign_size = 1;
  }

  s21_format_params params;
  s21_calculate_params(&info, current, &params);

  if (current->minus == 0) {
    s21_format_right(str, result, &info, &params);
  } else {
    s21_format_left(str, result, &info, &params);
  }
}