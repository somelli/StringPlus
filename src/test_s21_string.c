#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

// сравниваем длину строк
START_TEST(test_strlen) {
  const char str[][30] = {"Hello",      "",         "a",      "Hello World",
                          "1234567890", "!@#$%^&*", "       "};

  for (int i = 0; i < 7; i++) {
    ck_assert_int_eq(s21_strlen(str[i]), strlen(str[i]));
  }
}
END_TEST

// заменяем в заданном массиве все ячейки на заданную переменную
START_TEST(test_memset) {
  char str1[][30] = {"Hello", "School21", "abcdef", "Test"};
  char str2[][30] = {"Hello", "School21", "abcdef", "Test"};
  char ch[] = {'X', 'A', 'Z', 'Q'};
  int num[] = {3, 1, 6, 0};

  for (int i = 0; i < 4; i++) {
    s21_memset(str1[i], ch[i], num[i]);
    memset(str2[i], ch[i], num[i]);
    ck_assert_str_eq(str1[i], str2[i]);
  }
}
END_TEST

// копируем в новый массив заданное количество чаров из исходного
START_TEST(test_memcpy) {
  char str1[][30] = {"Hello", "School21", "abcdef", "Test"};
  char str11[4][20] = {0};
  char str2[][30] = {"Hello", "School21", "abcdef", "Test"};
  char str22[4][20] = {0};
  int num[] = {6, 5, 0, 3};

  for (int i = 0; i < 4; i++) {
    s21_memcpy(str11[i], str1[i], num[i]);
    memcpy(str22[i], str2[i], num[i]);

    ck_assert_str_eq(str11[i], str22[i]);
  }
}
END_TEST

// сравниваем две строки по принципу (больше, меньше, равно)
START_TEST(test_memcmp) {
  char str1[][30] = {"abc", "abc", "abd", "abc", "abcdef"};
  char str2[][30] = {"abc", "abd", "abc", "xyz", "abcxyz"};
  int num[] = {3, 3, 3, 0, 3};

  for (int i = 0; i < 5; i++) {
    int result1 = s21_memcmp(str1[i], str2[i], num[i]);
    int result2 = memcmp(str1[i], str2[i], num[i]);

    if (result2 == 0) {
      ck_assert_int_eq(result1, 0);
    } else if (result2 < 0) {
      ck_assert_int_lt(result1, 0);
    } else {
      ck_assert_int_gt(result1, 0);
    }
  }
}
END_TEST

// возвращаем адрес первой найденной переменной в заданном размере массива
START_TEST(test_memchr) {
  char str[][30] = {"Hello", "Hello", "Hello", "School21", "abc"};
  char ch[] = {'l', 'z', 'o', 'S', 'a'};
  int num[] = {5, 5, 4, 1, 0};

  for (int i = 0; i < 5; i++) {
    ck_assert_ptr_eq(s21_memchr(str[i], ch[i], num[i]),
                     memchr(str[i], ch[i], num[i]));
  }
}
END_TEST

// возвращаем адрес первой найденной переменной
START_TEST(test_strchr) {
  char str[][30] = {"Hello", "Hello", "School21", "abcabc", "Hello"};
  char ch[] = {'l', 'z', 'S', 'c', '\0'};

  for (int i = 0; i < 5; i++) {
    ck_assert_ptr_eq(s21_strchr(str[i], ch[i]), strchr(str[i], ch[i]));
  }
}
END_TEST

// возвращаем адрес последней найденной переменной
START_TEST(test_strrchr) {
  char str[][30] = {"Hello", "Hello", "School21", "abcabc", "Hello"};
  char ch[] = {'l', 'z', 'S', 'c', '\0'};

  for (int i = 0; i < 5; i++) {
    ck_assert_ptr_eq(s21_strrchr(str[i], ch[i]), strrchr(str[i], ch[i]));
  }
}
END_TEST

START_TEST(test_strncmp) {
  char str1[][30] = {"abc", "abc", "abd", "abc", "abcdef", "abc"};
  char str2[][30] = {"abc", "abd", "abc", "xyz", "abcxyz", "abc"};
  int num[] = {3, 3, 3, 0, 3, 10};

  for (int i = 0; i < 6; i++) {
    int result1 = s21_strncmp(str1[i], str2[i], num[i]);
    int result2 = strncmp(str1[i], str2[i], num[i]);

    if (result2 == 0) {
      ck_assert_int_eq(result1, 0);
    } else if (result2 < 0) {
      ck_assert_int_lt(result1, 0);
    } else {
      ck_assert_int_gt(result1, 0);
    }
  }
}
END_TEST

START_TEST(test_strncpy) {
  char str1[][30] = {"School21", "Hi", "abcdef", "Hello", ""};
  char str11[5][30] = {0};
  char str2[][30] = {"School21", "Hi", "abcdef", "Hello", ""};
  char str22[5][30] = {0};
  int num[] = {6, 6, 6, 0, 5};

  for (int i = 0; i < 5; i++) {
    s21_strncpy(str11[i], str1[i], num[i]);
    strncpy(str22[i], str2[i], num[i]);
    ck_assert_int_eq(memcmp(str11[i], str22[i], 30), 0);
  }
}
END_TEST

START_TEST(test_strncat) {
  char dest1[][30] = {"Hello ", "abc", "", "Hi", "A"};
  char dest2[][30] = {"Hello ", "abc", "", "Hi", "A"};
  char src[][30] = {"School21", "XYZ", "Test", "", "BC"};
  int num[] = {6, 0, 4, 5, 10};

  for (int i = 0; i < 5; i++) {
    s21_strncat(dest1[i], src[i], num[i]);
    strncat(dest2[i], src[i], num[i]);

    ck_assert_str_eq(dest1[i], dest2[i]);
  }
}
END_TEST

START_TEST(test_strcspn) {
  char str1[][30] = {"Hello World", "abcdef", "abcdef", "", "School21"};
  char str2[][30] = {"lo", "xyz", "a", "abc", "12"};

  for (int i = 0; i < 5; i++) {
    ck_assert_int_eq(s21_strcspn(str1[i], str2[i]), strcspn(str1[i], str2[i]));
  }
}
END_TEST

START_TEST(test_strpbrk) {
  char str1[][30] = {"Hello World", "abcdef", "abcdef", "", "School21"};
  char str2[][30] = {"od", "xyz", "a", "abc", "12"};

  for (int i = 0; i < 5; i++) {
    ck_assert_ptr_eq(s21_strpbrk(str1[i], str2[i]), strpbrk(str1[i], str2[i]));
  }
}
END_TEST

START_TEST(test_strstr) {
  char haystack[][30] = {"xxSchool21xx", "abcdef", "abcdef",
                         "abcdef",       "",       "aaaaab"};
  char needle[][30] = {"School", "xyz", "abc", "", "abc", "aaab"};

  for (int i = 0; i < 6; i++) {
    ck_assert_ptr_eq(s21_strstr(haystack[i], needle[i]),
                     strstr(haystack[i], needle[i]));
  }
}
END_TEST

START_TEST(test_strtok) {
  char str1[][30] = {"cat, dog, elephant", ",,cat,,,dog,", "cat;dog,bird",
                     ",,,", ""};
  char str2[][30] = {"cat, dog, elephant", ",,cat,,,dog,", "cat;dog,bird",
                     ",,,", ""};
  char delim[][30] = {",", ",", ",;", ",", ","};

  for (int i = 0; i < 5; i++) {
    char* result1 = s21_strtok(str1[i], delim[i]);
    char* result2 = strtok(str2[i], delim[i]);

    while (result1 != S21_NULL && result2 != NULL) {
      ck_assert_str_eq(result1, result2);
      result1 = s21_strtok(S21_NULL, delim[i]);
      result2 = strtok(NULL, delim[i]);
    }

    ck_assert_ptr_eq(result1, result2);
  }
}
END_TEST

START_TEST(test_strerror) {
  int errors[] = {0, 1, 2, 5, 999, -5, INT_MIN};

  for (int i = 0; i < 7; i++) {
    ck_assert_str_eq(s21_strerror(errors[i]), strerror(errors[i]));
  }
}
END_TEST

START_TEST(test_sprintf_simple) {
  char str1[100] = {0};
  char str2[100] = {0};

  int result1 = s21_sprintf(str1, "Hello School");
  int result2 = sprintf(str2, "Hello School");

  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "100%% ready");
  result2 = sprintf(str2, "100%% ready");

  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%%");
  result2 = sprintf(str2, "%%");

  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "abc %% def");
  result2 = sprintf(str2, "abc %% def");

  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_sprintf_char) {
  char str1[100] = {0};
  char str2[100] = {0};

  int result1 = s21_sprintf(str1, "%c", 'A');
  int result2 = sprintf(str2, "%c", 'A');
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%5c", 'A');
  result2 = sprintf(str2, "%5c", 'A');
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%-5c", 'A');
  result2 = sprintf(str2, "%-5c", 'A');
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "X%cY", 'A');
  result2 = sprintf(str2, "X%cY", 'A');
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_sprintf_string) {
  char str1[100] = {0};
  char str2[100] = {0};

  int result1 = s21_sprintf(str1, "%s", "School");
  int result2 = sprintf(str2, "%s", "School");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%.3s", "School");
  result2 = sprintf(str2, "%.3s", "School");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%10s", "School");
  result2 = sprintf(str2, "%10s", "School");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%-10s", "School");
  result2 = sprintf(str2, "%-10s", "School");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%10.3s", "School");
  result2 = sprintf(str2, "%10.3s", "School");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%-10.3s", "School");
  result2 = sprintf(str2, "%-10.3s", "School");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%3s", "School");
  result2 = sprintf(str2, "%3s", "School");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%.0s", "School");
  result2 = sprintf(str2, "%.0s", "School");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_sprintf_int_basic) {
  char str1[200] = {0};
  char str2[200] = {0};

  int result1 = s21_sprintf(str1, "%d", 123);
  int result2 = sprintf(str2, "%d", 123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%d", -123);
  result2 = sprintf(str2, "%d", -123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%d", 0);
  result2 = sprintf(str2, "%d", 0);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_sprintf_int_width) {
  char str1[200] = {0};
  char str2[200] = {0};

  int result1 = s21_sprintf(str1, "%5d", 123);
  int result2 = sprintf(str2, "%5d", 123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%5d", -123);
  result2 = sprintf(str2, "%5d", -123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%1d", 123);
  result2 = sprintf(str2, "%1d", 123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_sprintf_int_left_aligned) {
  char str1[200] = {0};
  char str2[200] = {0};

  int result1 = s21_sprintf(str1, "%-5d", 123);
  int result2 = sprintf(str2, "%-5d", 123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%-5d", -123);
  result2 = sprintf(str2, "%-5d", -123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_sprintf_int_precision) {
  char str1[200] = {0};
  char str2[200] = {0};

  int result1 = s21_sprintf(str1, "%.5d", 123);
  int result2 = sprintf(str2, "%.5d", 123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%.5d", -123);
  result2 = sprintf(str2, "%.5d", -123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%.0d", 0);
  result2 = sprintf(str2, "%.0d", 0);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%.0d", 123);
  result2 = sprintf(str2, "%.0d", 123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_sprintf_int_width_precision) {
  char str1[200] = {0};
  char str2[200] = {0};

  int result1 = s21_sprintf(str1, "%10.5d", 123);
  int result2 = sprintf(str2, "%10.5d", 123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%-10.5d", 123);
  result2 = sprintf(str2, "%-10.5d", 123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%10.5d", -123);
  result2 = sprintf(str2, "%10.5d", -123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_sprintf_int_zero_padding) {
  char str1[200] = {0};
  char str2[200] = {0};

  int result1 = s21_sprintf(str1, "%05d", 123);
  int result2 = sprintf(str2, "%05d", 123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%05d", -123);
  result2 = sprintf(str2, "%05d", -123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%05d", 0);
  result2 = sprintf(str2, "%05d", 0);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_sprintf_int_flags) {
  char str1[200] = {0};
  char str2[200] = {0};

  int result1 = s21_sprintf(str1, "%+d", 123);
  int result2 = sprintf(str2, "%+d", 123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%+d", -123);
  result2 = sprintf(str2, "%+d", -123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "% d", 123);
  result2 = sprintf(str2, "% d", 123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "% d", -123);
  result2 = sprintf(str2, "% d", -123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_sprintf_int_length) {
  char str1[200] = {0};
  char str2[200] = {0};

  short s = 123;
  long l = 1234567890L;

  int result1 = s21_sprintf(str1, "%hd", s);
  int result2 = sprintf(str2, "%hd", s);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%ld", l);
  result2 = sprintf(str2, "%ld", l);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_sprintf_unsigned) {
  char str1[200] = {0};
  char str2[200] = {0};

  int result1 = s21_sprintf(str1, "%u", 123);
  int result2 = sprintf(str2, "%u", 123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%u", 0);
  result2 = sprintf(str2, "%u", 0);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%5u", 123);
  result2 = sprintf(str2, "%5u", 123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%-5u", 123);
  result2 = sprintf(str2, "%-5u", 123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%.5u", 123);
  result2 = sprintf(str2, "%.5u", 123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%05u", 123);
  result2 = sprintf(str2, "%05u", 123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_sprintf_unsigned_length) {
  char str1[200] = {0};
  char str2[200] = {0};

  unsigned short us = 123;
  unsigned long ul = 1234567890UL;

  int result1 = s21_sprintf(str1, "%hu", us);
  int result2 = sprintf(str2, "%hu", us);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%lu", ul);
  result2 = sprintf(str2, "%lu", ul);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_sprintf_int_combined) {
  char str1[200] = {0};
  char str2[200] = {0};

  int result1 = s21_sprintf(str1, "%+10.5d", 123);
  int result2 = sprintf(str2, "%+10.5d", 123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%+10.5d", -123);
  result2 = sprintf(str2, "%+10.5d", -123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%-+10.5d", 123);
  result2 = sprintf(str2, "%-+10.5d", 123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_sprintf_float_basic) {
  char str1[200] = {0};
  char str2[200] = {0};

  int result1 = s21_sprintf(str1, "%f", 123.456);
  int result2 = sprintf(str2, "%f", 123.456);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%f", 0.0);
  result2 = sprintf(str2, "%f", 0.0);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_sprintf_float_precision) {
  char str1[200] = {0};
  char str2[200] = {0};

  int result1 = s21_sprintf(str1, "%.2f", 123.456);
  int result2 = sprintf(str2, "%.2f", 123.456);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%.0f", 123.5);
  result2 = sprintf(str2, "%.0f", 123.5);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%.4f", -0.1256);
  result2 = sprintf(str2, "%.4f", -0.1256);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_sprintf_float_width) {
  char str1[200] = {0};
  char str2[200] = {0};

  int result1 = s21_sprintf(str1, "%12.2f", 123.45);
  int result2 = sprintf(str2, "%12.2f", 123.45);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%-12.2f", 123.45);
  result2 = sprintf(str2, "%-12.2f", 123.45);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_sprintf_float_zero_padding) {
  char str1[200] = {0};
  char str2[200] = {0};

  int result1 = s21_sprintf(str1, "%012.2f", 123.45);
  int result2 = sprintf(str2, "%012.2f", 123.45);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%012.2f", -123.45);
  result2 = sprintf(str2, "%012.2f", -123.45);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_sprintf_float_signs) {
  char str1[200] = {0};
  char str2[200] = {0};

  int result1 = s21_sprintf(str1, "%+.2f", 123.45);
  int result2 = sprintf(str2, "%+.2f", 123.45);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "% .2f", 123.45);
  result2 = sprintf(str2, "% .2f", 123.45);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%+.2f", -123.45);
  result2 = sprintf(str2, "%+.2f", -123.45);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_sprintf_integer_limits) {
  char str1[200] = {0};
  char str2[200] = {0};

  int result1 = s21_sprintf(str1, "%ld", LONG_MIN);
  int result2 = sprintf(str2, "%ld", LONG_MIN);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%ld", LONG_MAX);
  result2 = sprintf(str2, "%ld", LONG_MAX);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%lu", ULONG_MAX);
  result2 = sprintf(str2, "%lu", ULONG_MAX);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_sprintf_float_rounding) {
  char str1[200] = {0};
  char str2[200] = {0};

  int result1 = s21_sprintf(str1, "%.0f", 2.5);
  int result2 = sprintf(str2, "%.0f", 2.5);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%.0f", 3.5);
  result2 = sprintf(str2, "%.0f", 3.5);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%.1f", 1.25);
  result2 = sprintf(str2, "%.1f", 1.25);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%.0f", 999.6);
  result2 = sprintf(str2, "%.0f", 999.6);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_sprintf_float_special) {
  char str1[200] = {0};
  char str2[200] = {0};

  int result1 = s21_sprintf(str1, "%010f", INFINITY);
  int result2 = sprintf(str2, "%010f", INFINITY);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%010f", -INFINITY);
  result2 = sprintf(str2, "%010f", -INFINITY);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%010f", NAN);
  result2 = sprintf(str2, "%010f", NAN);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);

  result1 = s21_sprintf(str1, "%f", -0.0);
  result2 = sprintf(str2, "%f", -0.0);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_high_bytes) {
  char str1[] = {(char)0xFF, 'a', '\0'};
  char str2[] = {(char)0x01, 'a', '\0'};

  int result1 = s21_strncmp(str1, str2, 1);
  int result2 = strncmp(str1, str2, 1);

  if (result2 < 0) {
    ck_assert_int_lt(result1, 0);
  } else if (result2 > 0) {
    ck_assert_int_gt(result1, 0);
  } else {
    ck_assert_int_eq(result1, 0);
  }

  ck_assert_ptr_eq(s21_strchr(str1, 0xFF), strchr(str1, 0xFF));
  ck_assert_ptr_eq(s21_strrchr(str1, 0xFF), strrchr(str1, 0xFF));
}
END_TEST

void add_string_tests(TCase* tc) {
  tcase_add_test(tc, test_strlen);
  tcase_add_test(tc, test_memset);
  tcase_add_test(tc, test_memcpy);
  tcase_add_test(tc, test_memcmp);
  tcase_add_test(tc, test_memchr);
  tcase_add_test(tc, test_strchr);
  tcase_add_test(tc, test_strrchr);
  tcase_add_test(tc, test_strncmp);
  tcase_add_test(tc, test_strncpy);
  tcase_add_test(tc, test_strncat);
  tcase_add_test(tc, test_strcspn);
  tcase_add_test(tc, test_strpbrk);
  tcase_add_test(tc, test_strstr);
  tcase_add_test(tc, test_strtok);
  tcase_add_test(tc, test_strerror);
  tcase_add_test(tc, test_high_bytes);
}

void add_sprintf_basic_tests(TCase* tc) {
  tcase_add_test(tc, test_sprintf_simple);
  tcase_add_test(tc, test_sprintf_char);
  tcase_add_test(tc, test_sprintf_string);
}

void add_sprintf_int_tests(TCase* tc) {
  tcase_add_test(tc, test_sprintf_int_basic);
  tcase_add_test(tc, test_sprintf_int_width);
  tcase_add_test(tc, test_sprintf_int_left_aligned);
  tcase_add_test(tc, test_sprintf_int_precision);
  tcase_add_test(tc, test_sprintf_int_width_precision);
  tcase_add_test(tc, test_sprintf_int_zero_padding);
  tcase_add_test(tc, test_sprintf_int_flags);
  tcase_add_test(tc, test_sprintf_int_length);
  tcase_add_test(tc, test_sprintf_unsigned);
  tcase_add_test(tc, test_sprintf_unsigned_length);
  tcase_add_test(tc, test_sprintf_int_combined);
  tcase_add_test(tc, test_sprintf_integer_limits);
}

void add_sprintf_float_tests(TCase* tc) {
  tcase_add_test(tc, test_sprintf_float_basic);
  tcase_add_test(tc, test_sprintf_float_precision);
  tcase_add_test(tc, test_sprintf_float_width);
  tcase_add_test(tc, test_sprintf_float_zero_padding);
  tcase_add_test(tc, test_sprintf_float_signs);
  tcase_add_test(tc, test_sprintf_float_rounding);
  tcase_add_test(tc, test_sprintf_float_special);
}

int main(void) {
  Suite* s = suite_create("s21_string");
  TCase* tc = tcase_create("main");

  add_string_tests(tc);
  add_sprintf_basic_tests(tc);
  add_sprintf_int_tests(tc);
  add_sprintf_float_tests(tc);

  suite_add_tcase(s, tc);

  SRunner* sr = srunner_create(s);
  srunner_run_all(sr, CK_VERBOSE);

  int failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return failed == 0 ? 0 : 1;
}