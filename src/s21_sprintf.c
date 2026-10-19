// для функций va_list
#include <stdarg.h>
// наша библиотека с функциями
#include "s21_string.h"

// парсер
void s21_parse_format(const char* format, int* i, s21_format* current) {
  // проверяем flags (пока они есть)
  while (format[*i] == '-' || format[*i] == '+' || format[*i] == ' ' ||
         format[*i] == '0') {
    switch (format[*i]) {
      case '-':
        current->minus = 1;
        break;
      case '+':
        current->plus = 1;
        break;
      case ' ':
        current->space = 1;
        break;
      case '0':
        current->zero = 1;
        break;
    }
    (*i)++;
  }

  // проверяем width (идем по числам пока они не кончатся)
  while (format[*i] >= '0' && format[*i] <= '9') {
    // собираем все чары чисел в одного супер-инт-чара
    current->width = current->width * 10 + (format[*i] - '0');
    (*i)++;
  }

  // проверяем precision (ищем точку)
  if (format[*i] == '.') {
    current->precision_set = 1;
    (*i)++;

    // повторяем супер-инт-чара
    while (format[*i] >= '0' && format[*i] <= '9') {
      current->precision = current->precision * 10 + (format[*i] - '0');
      (*i)++;
    }
  }

  // проверяем length
  if (format[*i] == 'l' || format[*i] == 'h') {
    current->length = format[*i];
    (*i)++;
  }

  // выбираем спецификатор через нашу strchr (ищем нужный чар в этой куче)
  if (s21_strchr("cdfsu%", format[*i]) != S21_NULL) {
    current->specifier = format[*i];
  }
}

// функция написания пробелов
void s21_write_spaces(char* str, int* result, int spaces) {
  for (int i = 0; i < spaces; i++) {
    str[*result] = ' ';
    (*result)++;
  }
}

// обработка %
static void s21_handle_percent(char* str, int* result) {
  str[*result] = '%';
  (*result)++;
}

// обработка c
static void s21_handle_char(char* str, int* result, va_list* args,
                            s21_format* current) {
  int value = va_arg(*args, int);
  char ch = (char)value;
  int spaces = 0;

  if (current->width > 1) {
    spaces = current->width - 1;
  }

  if (current->minus == 0) {
    s21_write_spaces(str, result, spaces);
    str[*result] = ch;
    (*result)++;
  } else {
    str[*result] = ch;
    (*result)++;
    s21_write_spaces(str, result, spaces);
  }
}

// обработка s
static void s21_handle_string(char* str, int* result, va_list* args,
                              s21_format* current) {
  char* text = va_arg(*args, char*);
  int text_length = s21_strlen(text);

  if (current->precision_set == 1 && current->precision < text_length) {
    text_length = current->precision;
  }

  int spaces = 0;
  if (current->width > text_length) {
    spaces = current->width - text_length;
  }

  if (current->minus == 0) {
    s21_write_spaces(str, result, spaces);
    for (int j = 0; j < text_length; j++) {
      str[*result] = text[j];
      (*result)++;
    }
  } else {
    for (int j = 0; j < text_length; j++) {
      str[*result] = text[j];
      (*result)++;
    }
    s21_write_spaces(str, result, spaces);
  }
}

// выбор обработчика
static void s21_process_specifier(char* str, int* result, va_list* args,
                                  s21_format* current) {
  if (current->specifier == '%') {
    s21_handle_percent(str, result);
  } else if (current->specifier == 'c') {
    s21_handle_char(str, result, args, current);
  } else if (current->specifier == 's') {
    s21_handle_string(str, result, args, current);
  } else if (current->specifier == 'd' || current->specifier == 'u') {
    s21_format_int(str, result, args, current);
  } else if (current->specifier == 'f') {
    s21_format_float(str, result, args, current);
  }
}

// запись обычного символа
static void s21_handle_ordinary_char(char* str, int* result, char ch) {
  str[*result] = ch;
  (*result)++;
}

int s21_sprintf(char* str, const char* format, ...) {
  va_list args;
  va_start(args, format);

  int i = 0;
  int result = 0;

  for (; format[i] != '\0'; i++) {
    if (format[i] == '%') {
      s21_format current = {0};
      i++;
      s21_parse_format(format, &i, &current);
      s21_process_specifier(str, &result, &args, &current);
    } else {
      s21_handle_ordinary_char(str, &result, format[i]);
    }
  }

  str[result] = '\0';
  va_end(args);
  return result;
}