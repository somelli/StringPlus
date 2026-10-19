#include <math.h>

#include "s21_string.h"

#define S21_FLOAT_BUFFER_SIZE 512

static int s21_float_precision(s21_format* current) {
  return current->precision_set ? current->precision : 6;
}

static int s21_float_sign(double value, s21_format* current) {
  int sign = 0;
  if (signbit(value)) {
    sign = '-';
  } else if (current->plus) {
    sign = '+';
  } else if (current->space) {
    sign = ' ';
  }
  return sign;
}

static void s21_float_reverse(char* str, int length) {
  for (int i = 0; i < length / 2; i++) {
    char temp = str[i];
    str[i] = str[length - i - 1];
    str[length - i - 1] = temp;
  }
}

static int s21_float_integer(long double value, char* number) {
  int length = 0;

  if (value < 1.0L) {
    number[length++] = '0';
  } else {
    while (value >= 1.0L && length < S21_FLOAT_BUFFER_SIZE - 1) {
      long double digit = fmodl(value, 10.0L);
      number[length++] = (char)('0' + (int)digit);
      value = floorl(value / 10.0L);
    }
    s21_float_reverse(number, length);
  }

  return length;
}

static void s21_float_increment_integer(char* number, int* length) {
  int position = *length - 1;
  while (position >= 0 && number[position] == '9') {
    number[position] = '0';
    position--;
  }

  if (position >= 0) {
    number[position]++;
  } else if (*length < S21_FLOAT_BUFFER_SIZE - 1) {
    for (int i = *length; i > 0; i--) {
      number[i] = number[i - 1];
    }
    number[0] = '1';
    (*length)++;
  }
}

static int s21_float_special(double value, char* number) {
  const char* special = isnan(value) ? "nan" : isinf(value) ? "inf" : 0;
  int length = 0;
  if (special == 0) {
  } else {
    for (int i = 0; special[i] != '\0'; i++) {
      number[i] = special[i];
    }
    number[3] = '\0';
    length = 3;
  }
  return length;
}

static long double s21_float_fraction_digits(long double fraction,
                                             int precision, char* digits) {
  for (int i = 0; i < precision; i++) {
    fraction *= 10.0L;
    digits[i] = (char)('0' + (int)fraction);
    fraction -= floorl(fraction);
  }
  return fraction;
}

static void s21_float_round_fraction(long double fraction, int precision,
                                     char* digits, char* number, int* length) {
  fraction *= 10.0L;
  int last_digit =
      precision > 0 ? digits[precision - 1] - '0' : number[*length - 1] - '0';
  int round_up =
      (int)fraction > 5 || ((int)fraction == 5 && (last_digit % 2 != 0));
  if (round_up) {
    int position = precision - 1;
    while (position >= 0 && digits[position] == '9') {
      digits[position] = '0';
      position--;
    }
    if (position >= 0) {
      digits[position]++;
    } else {
      s21_float_increment_integer(number, length);
    }
  }
}

static int s21_float_append_fraction(char* number, int length, int precision,
                                     const char* digits) {
  if (precision > 0) {
    number[length++] = '.';
    for (int i = 0; i < precision; i++) {
      number[length++] = digits[i];
    }
  }
  number[length] = '\0';
  return length;
}

static int s21_float_number(double value, s21_format* current, char* number) {
  int special_length = s21_float_special(value, number);
  int length = special_length;
  if (special_length == 0) {
    int precision = s21_float_precision(current);
    long double absolute = fabsl((long double)value);
    long double integer_part;
    long double fraction = modfl(absolute, &integer_part);
    length = s21_float_integer(integer_part, number);
    int available = S21_FLOAT_BUFFER_SIZE - length - 2;

    if (precision > available) {
      precision = available;
    }

    char fraction_digits[S21_FLOAT_BUFFER_SIZE];
    fraction = s21_float_fraction_digits(fraction, precision, fraction_digits);
    s21_float_round_fraction(fraction, precision, fraction_digits, number,
                             &length);
    length =
        s21_float_append_fraction(number, length, precision, fraction_digits);
  }
  return length;
}

static void s21_float_write(char* str, int* result, char sign,
                            const char* number, int number_length,
                            s21_format* current) {
  int special = number[0] == 'i' || number[0] == 'n';
  int sign_length = sign != 0;
  int spaces = current->width - sign_length - number_length;
  if (spaces < 0) {
    spaces = 0;
  }

  if (current->minus == 0 && (current->zero == 0 || special != 0)) {
    for (int i = 0; i < spaces; i++) {
      str[(*result)++] = ' ';
    }
  }

  if (sign != 0) {
    str[(*result)++] = sign;
  }

  if (current->minus == 0 && current->zero != 0 && special == 0) {
    for (int i = 0; i < spaces; i++) {
      str[(*result)++] = '0';
    }
  }

  for (int i = 0; i < number_length; i++) {
    str[(*result)++] = number[i];
  }

  if (current->minus != 0) {
    for (int i = 0; i < spaces; i++) {
      str[(*result)++] = ' ';
    }
  }
}

void s21_format_float(char* str, int* result, va_list* args,
                      s21_format* current) {
  double value = va_arg(*args, double);
  char number[512];
  int number_length = s21_float_number(value, current, number);
  char sign = s21_float_sign(value, current);

  s21_float_write(str, result, sign, number, number_length, current);
}
