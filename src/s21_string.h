#ifndef S21_STRING_H
#define S21_STRING_H

#include <stdarg.h>

// NULL для наших функций
#define S21_NULL ((void*)0)
// size_t для наших функций
typedef unsigned long s21_size_t;

// структура для всех .с
typedef struct {
  int minus;
  int plus;
  int space;
  int width;
  int zero;
  int precision;
  int precision_set;
  char length;
  char specifier;
} s21_format;

// функции
s21_size_t s21_strlen(const char* str);
void* s21_memset(void* str, int c, s21_size_t n);
void* s21_memcpy(void* dest, const void* src, s21_size_t n);
int s21_memcmp(const void* str1, const void* str2, s21_size_t n);
void* s21_memchr(const void* str, int c, s21_size_t n);
char* s21_strchr(const char* str, int c);
char* s21_strrchr(const char* str, int c);
int s21_strncmp(const char* str1, const char* str2, s21_size_t n);
char* s21_strncpy(char* dest, const char* src, s21_size_t n);
char* s21_strncat(char* dest, const char* src, s21_size_t n);
s21_size_t s21_strcspn(const char* str1, const char* str2);
char* s21_strpbrk(const char* str1, const char* str2);
char* s21_strstr(const char* haystack, const char* needle);
char* s21_strerror(int errnum);
char* s21_strtok(char* str, const char* delim);
int s21_sprintf(char* str, const char* format, ...);
void s21_format_int(char* str, int* result, va_list* args, s21_format* current);
void s21_format_float(char* str, int* result, va_list* args,
                      s21_format* current);

#endif