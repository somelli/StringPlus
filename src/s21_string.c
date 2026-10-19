#include "s21_string.h"

#ifdef __APPLE__
#define S21_MAX_ERROR 107
#define S21_UNKNOWN_ERROR "Unknown error: "
// использовать массив ошибок macOS
const char* s21_errors[] = {"Undefined error: 0",
                            "Operation not permitted",
                            "No such file or directory",
                            "No such process",
                            "Interrupted system call",
                            "Input/output error",
                            "Device not configured",
                            "Argument list too long",
                            "Exec format error",
                            "Bad file descriptor",
                            "No child processes",
                            "Resource deadlock avoided",
                            "Cannot allocate memory",
                            "Permission denied",
                            "Bad address",
                            "Block device required",
                            "Resource busy",
                            "File exists",
                            "Cross-device link",
                            "Operation not supported by device",
                            "Not a directory",
                            "Is a directory",
                            "Invalid argument",
                            "Too many open files in system",
                            "Too many open files",
                            "Inappropriate ioctl for device",
                            "Text file busy",
                            "File too large",
                            "No space left on device",
                            "Illegal seek",
                            "Read-only file system",
                            "Too many links",
                            "Broken pipe",
                            "Numerical argument out of domain",
                            "Result too large",
                            "Resource temporarily unavailable",
                            "Operation now in progress",
                            "Operation already in progress",
                            "Socket operation on non-socket",
                            "Destination address required",
                            "Message too long",
                            "Protocol wrong type for socket",
                            "Protocol not available",
                            "Protocol not supported",
                            "Socket type not supported",
                            "Operation not supported",
                            "Protocol family not supported",
                            "Address family not supported by protocol family",
                            "Address already in use",
                            "Can't assign requested address",
                            "Network is down",
                            "Network is unreachable",
                            "Network dropped connection on reset",
                            "Software caused connection abort",
                            "Connection reset by peer",
                            "No buffer space available",
                            "Socket is already connected",
                            "Socket is not connected",
                            "Can't send after socket shutdown",
                            "Too many references: can't splice",
                            "Operation timed out",
                            "Connection refused",
                            "Too many levels of symbolic links",
                            "File name too long",
                            "Host is down",
                            "No route to host",
                            "Directory not empty",
                            "Too many processes",
                            "Too many users",
                            "Disc quota exceeded",
                            "Stale NFS file handle",
                            "Too many levels of remote in path",
                            "RPC struct is bad",
                            "RPC version wrong",
                            "RPC prog. not avail",
                            "Program version wrong",
                            "Bad procedure for program",
                            "No locks available",
                            "Function not implemented",
                            "Inappropriate file type or format",
                            "Authentication error",
                            "Need authenticator",
                            "Device power is off",
                            "Device error",
                            "Value too large to be stored in data type",
                            "Bad executable (or shared library)",
                            "Bad CPU type in executable",
                            "Shared library version mismatch",
                            "Malformed Mach-o file",
                            "Operation canceled",
                            "Identifier removed",
                            "No message of desired type",
                            "Illegal byte sequence",
                            "Attribute not found",
                            "Bad message",
                            "EMULTIHOP (Reserved)",
                            "No message available on STREAM",
                            "ENOLINK (Reserved)",
                            "No STREAM resources",
                            "Not a STREAM",
                            "Protocol error",
                            "STREAM ioctl timeout",
                            "Operation not supported on socket",
                            "Policy not found",
                            "State not recoverable",
                            "Previous owner died",
                            "Interface output queue is full",
                            "Capabilities insufficient"};

#elif defined(__linux__)
// использовать массив ошибок linux
#define S21_MAX_ERROR 133
#define S21_UNKNOWN_ERROR "Unknown error "

const char* s21_errors[] = {"Success",
                            "Operation not permitted",
                            "No such file or directory",
                            "No such process",
                            "Interrupted system call",
                            "Input/output error",
                            "No such device or address",
                            "Argument list too long",
                            "Exec format error",
                            "Bad file descriptor",
                            "No child processes",
                            "Resource temporarily unavailable",
                            "Cannot allocate memory",
                            "Permission denied",
                            "Bad address",
                            "Block device required",
                            "Device or resource busy",
                            "File exists",
                            "Invalid cross-device link",
                            "No such device",
                            "Not a directory",
                            "Is a directory",
                            "Invalid argument",
                            "Too many open files in system",
                            "Too many open files",
                            "Inappropriate ioctl for device",
                            "Text file busy",
                            "File too large",
                            "No space left on device",
                            "Illegal seek",
                            "Read-only file system",
                            "Too many links",
                            "Broken pipe",
                            "Numerical argument out of domain",
                            "Numerical result out of range",
                            "Resource deadlock avoided",
                            "File name too long",
                            "No locks available",
                            "Function not implemented",
                            "Directory not empty",
                            "Too many levels of symbolic links",
                            "Unknown error 41",
                            "No message of desired type",
                            "Identifier removed",
                            "Channel number out of range",
                            "Level 2 not synchronized",
                            "Level 3 halted",
                            "Level 3 reset",
                            "Link number out of range",
                            "Protocol driver not attached",
                            "No CSI structure available",
                            "Level 2 halted",
                            "Invalid exchange",
                            "Invalid request descriptor",
                            "Exchange full",
                            "No anode",
                            "Invalid request code",
                            "Invalid slot",
                            "Unknown error 58",
                            "Bad font file format",
                            "Device not a stream",
                            "No data available",
                            "Timer expired",
                            "Out of streams resources",
                            "Machine is not on the network",
                            "Package not installed",
                            "Object is remote",
                            "Link has been severed",
                            "Advertise error",
                            "Srmount error",
                            "Communication error on send",
                            "Protocol error",
                            "Multihop attempted",
                            "RFS specific error",
                            "Bad message",
                            "Value too large for defined data type",
                            "Name not unique on network",
                            "File descriptor in bad state",
                            "Remote address changed",
                            "Can not access a needed shared library",
                            "Accessing a corrupted shared library",
                            ".lib section in a.out corrupted",
                            "Attempting to link in too many shared libraries",
                            "Cannot exec a shared library directly",
                            "Invalid or incomplete multibyte or wide character",
                            "Interrupted system call should be restarted",
                            "Streams pipe error",
                            "Too many users",
                            "Socket operation on non-socket",
                            "Destination address required",
                            "Message too long",
                            "Protocol wrong type for socket",
                            "Protocol not available",
                            "Protocol not supported",
                            "Socket type not supported",
                            "Operation not supported",
                            "Protocol family not supported",
                            "Address family not supported by protocol",
                            "Address already in use",
                            "Cannot assign requested address",
                            "Network is down",
                            "Network is unreachable",
                            "Network dropped connection on reset",
                            "Software caused connection abort",
                            "Connection reset by peer",
                            "No buffer space available",
                            "Transport endpoint is already connected",
                            "Transport endpoint is not connected",
                            "Cannot send after transport endpoint shutdown",
                            "Too many references: cannot splice",
                            "Connection timed out",
                            "Connection refused",
                            "Host is down",
                            "No route to host",
                            "Operation already in progress",
                            "Operation now in progress",
                            "Stale file handle",
                            "Structure needs cleaning",
                            "Not a XENIX named type file",
                            "No XENIX semaphores available",
                            "Is a named type file",
                            "Remote I/O error",
                            "Disk quota exceeded",
                            "No medium found",
                            "Wrong medium type",
                            "Operation canceled",
                            "Required key not available",
                            "Key has expired",
                            "Key has been revoked",
                            "Key was rejected by service",
                            "Owner died",
                            "State not recoverable",
                            "Operation not possible due to RF-kill",
                            "Memory page has hardware error"};

#endif

// !функция для подсчета чаров
s21_size_t s21_strlen(const char* str) {  // получаем адрес первого чара
  s21_size_t count = 0;                   // нулевой счетчик
  while (str[count] != '\0') {  // пока не натыкаемся на конец строки ++
    count++;
  }
  return count;
}

// !функция для присваивания чара в указанное кол-во байт памяти
// void *str - потому что memset должна уметь работать с любой памятью.
// void *str - получаем адрес памяти
// void * - функция должна вернуть указатель на память str
void* s21_memset(void* str, int c,
                 s21_size_t n) {  // s21_size_t - беззнаковый тип для хранения
                                  // размеров и количества байтов/элементов.
  unsigned char* ptr =
      str;  // доп указатель на str с приведенным типом - байты (unsigned char)
  // s21_size_t чтобы все переменные были одного типа
  // меняем полученное С в заданном кол-ве байт
  for (s21_size_t i = 0; i < n; i++) {
    ptr[i] = (unsigned char)c;  // явно приводим к unsigned char
  }
  return str;
}

// !функция для копирования из source в destination
// получаем адреса памяти destination и source, кол-во байт для копирования
void* s21_memcpy(void* dest, const void* src, s21_size_t n) {
  unsigned char* ptr_dest = dest;
  const unsigned char* ptr_src = src;
  for (s21_size_t i = 0; i < n; i++) {  // копируем из source в destination
    ptr_dest[i] = ptr_src[i];
  }
  return dest;
}

// !функция для сравнения байт памаяти в 2х источниках
int s21_memcmp(const void* str1, const void* str2, s21_size_t n) {
  const unsigned char* ptr_str1 = str1;
  const unsigned char* ptr_str2 = str2;
  int result = 0;

  s21_size_t i = 0;
  while (i < n && result == 0) {
    if (ptr_str1[i] < ptr_str2[i]) {
      result = -1;
    } else if (ptr_str1[i] > ptr_str2[i]) {
      result = 1;
    }
    i++;
  }

  return result;
}

// !функция поиска указанного байта в представленном размере памяти
void* s21_memchr(const void* str, int c, s21_size_t n) {
  const unsigned char* ptr_str = str;
  void* result = S21_NULL;  // присваиваем нулевой адрес
  for (s21_size_t i = 0; i < n; i++) {
    if (ptr_str[i] ==
        (unsigned char)c) {  // если находим искомый символ, выдаем его адрес
      result = (void*)(ptr_str + i);
      break;
    }
  }
  return result;
}

// !функция поиска первого символа в строке
char* s21_strchr(const char* str, int c) {
  char* result = S21_NULL;  // chr * так как str указатель на char
  s21_size_t i =
      0;  // выносим i чтобы результат циклов сохранился и указыавл на \0
  for (; str[i] != '\0'; i++) {
    if ((unsigned char)str[i] == (unsigned char)c) {
      result = (char*)(str + i);
      break;
    }
  }
  if (c == '\0') {
    result = (char*)(str + i);
  }
  return result;
}

// !функция поиска последнего символа в строке
char* s21_strrchr(const char* str, int c) {
  char* result = S21_NULL;  // chr * так как str указатель на char
  s21_size_t i =
      0;  // выносим i чтобы результат циклов сохранился и указыавл на \0
  for (; str[i] != '\0'; i++) {
    if ((unsigned char)str[i] == (unsigned char)c) {
      result = (char*)(str + i);
    }
  }

  if (c == '\0') {
    result = (char*)(str + i);
  }
  return result;
}

// !функция для сравнения символов в 2х источниках на выбранное кол-во символов
int s21_strncmp(const char* str1, const char* str2, s21_size_t n) {
  int result = 0;

  s21_size_t i = 0;
  while (i < n && result == 0) {
    // защита от крайних значений signed/unsigned
    if ((unsigned char)str1[i] < (unsigned char)str2[i]) {
      result = -1;
    } else if ((unsigned char)str1[i] > (unsigned char)str2[i]) {
      result = 1;
    }

    if (str1[i] == '\0' || str2[i] == '\0') {
      break;
    }
    i++;
  }

  return result;
}

// !функция для копирования из source в destination и контроля конца строки
char* s21_strncpy(char* dest, const char* src, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {  // копируем из source в destination
    if (src[i] ==
        '\0') {  // если в источнике конец строки, добиваем destination нулями
      for (s21_size_t j = i; j < n; j++) {
        dest[j] = '\0';
      }
      break;  // и выходим из циклов
    } else {
      dest[i] = src[i];
    }
  }
  return dest;
}

// !функция для добавления из source в destination указанного кол-ва символов
char* s21_strncat(char* dest, const char* src, s21_size_t n) {
  s21_size_t i = 0;
  s21_size_t j = 0;
  for (; dest[i] != '\0'; i++) {  // ищем конец строки
  }

  for (; j < n; j++) {  // копируем source в destination
    dest[i + j] = src[j];
    if (src[j] == '\0') {
      break;
    }
  }
  dest[i + j] = '\0';
  return dest;
}

// !возвращает сколько символов от начала str1 прошло до начала str2
s21_size_t s21_strcspn(const char* str1, const char* str2) {
  s21_size_t count = 0;
  s21_size_t result = 0;
  for (s21_size_t i = 0; str1[i] != '\0'; i++) {
    for (s21_size_t j = 0; str2[j] != '\0'; j++) {
      if (str2[j] ==
          str1[i]) {  // если нашли символ результат 1 и выходим из цикла
        result = 1;
        break;
      }
    }
    if (result == 1) {  // если 1 выходим и из второго цикла
      break;
    }
    count++;  // если не нашли, продолжаем считать
  }
  return count;
}

// !возвращает адрес первого символа в str1, который встретился в str2.
char* s21_strpbrk(const char* str1, const char* str2) {
  char* result = S21_NULL;
  for (s21_size_t i = 0; str1[i] != '\0'; i++) {
    for (s21_size_t j = 0; str2[j] != '\0'; j++) {
      if (str2[j] == str1[i]) {
        result = (char*)(&str1[i]);
        break;
      }
    }
    if (result != S21_NULL) {
      break;
    }
  }
  return result;
}

// !функция ищет заданное слово в строке полностью и отдает адрес первого
// совпадения
static int s21_compare_substring(const char* haystack, const char* needle,
                                 s21_size_t start, s21_size_t needle_len) {
  s21_size_t j = 0;
  while (j < needle_len && haystack[start + j] != '\0' &&
         haystack[start + j] == needle[j]) {
    j++;
  }
  return (j == needle_len);
}

char* s21_strstr(const char* haystack, const char* needle) {
  char* result = S21_NULL;

  if (haystack != S21_NULL && needle != S21_NULL) {
    int found = 0;
    s21_size_t needle_len = 0;
    while (needle[needle_len] != '\0') {
      needle_len++;
    }

    if (needle_len == 0) {
      result = (char*)haystack;
      found = 1;
    }

    for (s21_size_t i = 0; !found && haystack[i] != '\0'; i++) {
      if (haystack[i] == needle[0] &&
          s21_compare_substring(haystack, needle, i, needle_len)) {
        result = (char*)&haystack[i];
        found = 1;
      }
    }
  }

  return result;
}

// !функция возврата ошибок + обращение числа в строковый тип
char* s21_strerror(int errnum) {
  char* result = S21_NULL;
  static char unknown_error[50];
  int current[50] = {0};
  if (errnum >= 0 && errnum <= S21_MAX_ERROR) {
    result = (char*)s21_errors[errnum];
  } else {
    long long number = errnum;
    int i = 0;
    s21_size_t text = 0;
    while (S21_UNKNOWN_ERROR[text] != '\0') {
      // копируем макрос сверху
      unknown_error[text] = S21_UNKNOWN_ERROR[text];
      // делаем пропуск
      text++;
    }
    // если минус - прописываем его отдельно
    if (number < 0) {
      unknown_error[text] = '-';
      number *= -1;
      text++;
    }
    // находим все числа и записываем их в current
    for (; number != 0; i++) {
      current[i] = number % 10;
      number /= 10;
    }
    i--;
    // и в обратном порядке записываем в ошибку
    for (; i > -1; i--) {
      unknown_error[text] = current[i] + '0';
      text++;
    }
    // добавляем конец строки
    unknown_error[text] = '\0';
    result = unknown_error;
  }
  return result;
}

// !функция передает адрес строки до разделителя, при повторном вызове
// продолжает с последнего разделителя и отдает адрес новой строки
static int s21_is_delimiter(char c, const char* delim) {
  int result = 0;
  for (s21_size_t j = 0; delim[j] != '\0' && result == 0; j++) {
    if (c == delim[j]) {
      result = 1;
    }
  }
  return result;
}

char* s21_strtok(char* str, const char* delim) {
  static char* last_res = S21_NULL;
  char* result = S21_NULL;

  if (str != S21_NULL) {
    last_res = str;
  }

  if (last_res != S21_NULL && last_res[0] != '\0') {
    while (last_res[0] != '\0' && s21_is_delimiter(last_res[0], delim)) {
      last_res++;
    }

    if (last_res[0] != '\0') {
      result = last_res;

      s21_size_t i = 0;
      while (last_res[i] != '\0' && !s21_is_delimiter(last_res[i], delim)) {
        i++;
      }

      if (last_res[i] == '\0') {
        last_res = S21_NULL;
      } else {
        last_res[i] = '\0';
        last_res = &last_res[i + 1];
      }
    } else {
      last_res = S21_NULL;
    }
  }

  return result;
}
