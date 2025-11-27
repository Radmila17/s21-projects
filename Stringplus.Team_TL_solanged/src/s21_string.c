#include "s21_string.h"

#include <stdio.h>
#include <stdlib.h>

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    dest[i] = src[i];
  }
  dest[n] = '\0';
  return dest;
}

char *s21_strrchr(const char *str, int c) {
  char *result = s21_NULL;
  while (*str != '\0') {
    if (*str == c) result = (char *)str;
    str++;
  }
  if (c == '\0') {
    result = (char *)str;
  }

  return result;
}

char *s21_strchr(const char *str, int c) {
  int flag = 0;
  char *result = s21_NULL;
  while (*str != '\0' && flag != 1) {
    if (*str == c) {
      result = (char *)str;
      flag = 1;
    }
    str++;
  }
  if (c == '\0') {
    result = (char *)str;
  }
  return result;
}

char *s21_strtok(char *str, const char *delim) {
  static char *saved_str = s21_NULL;
  char *token_str = s21_NULL;
  if (str != s21_NULL) {
    saved_str = str;
  }
  if (saved_str == s21_NULL) {
    token_str = s21_NULL;
  } else {
    while (*saved_str != '\0' && s21_strchr(delim, *saved_str)) {
      saved_str++;
    }
    if (*saved_str == '\0') {
      saved_str = s21_NULL;
      token_str = s21_NULL;
    } else {
      token_str = saved_str;
      while (*saved_str != '\0' && !s21_strchr(delim, *saved_str)) {
        saved_str++;
      }
      if (*saved_str == '\0') {
        saved_str = s21_NULL;
      } else {
        *saved_str = '\0';
        saved_str++;
      }
    }
  }
  return token_str;
}

int s21_strncmp(const char *str1, const char *str2, size_t n) {
  int result = 0;
  int flag = 0;
  for (size_t i = 0; i < n && flag != 1; i++, str1++, str2++) {
    if (*str1 != *str2) {
      flag = 1;
    }
    result = *str1 - *str2;
  }
  return result;
}
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *dest_end = dest + s21_strlen(dest);
  while (n > 0 && *src != '\0') {
    *dest_end++ = *src++;
    n--;
  }
  *dest_end = '\0';
  return dest;
}

s21_size_t s21_strlen(const char *str) {
  int length = 0;
  if (str[0] != '\0') {
    while (str[length] != '\0') {
      length++;
    }
  }
  return length;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *ptr_1 = (const unsigned char *)str1;
  const unsigned char *ptr_2 = (const unsigned char *)str2;
  int result = 0;
  for (s21_size_t i = 0; i < n; i++, ptr_1++, ptr_2++) {
    if (*ptr_1 != *ptr_2) {
      result = *ptr_1 - *ptr_2;
      break;
    }
  }
  return result;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *ptr = (const unsigned char *)str;
  void *result = s21_NULL;
  int flag = 0;
  for (s21_size_t i = 0; i < n && flag == 0; i++) {
    if (ptr[i] == c) {
      result = (void *)(ptr + i);
      flag = 1;
    }
  }
  return result;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *d = (unsigned char *)dest;
  const unsigned char *s = (const unsigned char *)src;
  s21_size_t i = 0;
  for (; i < n; i++) {
    d[i] = s[i];
  }
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  for (s21_size_t x = 0; x < n; x++) {
    ((unsigned char *)str)[x] = (unsigned char)c;
  }
  return str;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t l1 = s21_strlen(str1);
  s21_size_t l2 = s21_strlen(str2);
  s21_size_t count = 0;
  s21_size_t flag = 0;
  for (s21_size_t i = 0; i < l1; i++) {
    for (s21_size_t j = 0; j < l2; j++) {
      if (str1[i] == str2[j]) flag = 1;
    }
    if (flag) break;
    count++;
  }
  return count;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = s21_NULL;
  s21_size_t flag = 0;
  while (*str1 != '\0') {
    const char *temp = str2;
    while (*temp != '\0') {
      if (*str1 == *temp) {
        flag = 1;
        result = (char *)str1;
      }
      temp++;
    }
    if (flag) break;
    str1++;
  }
  return result;
}
char *s21_strstr(const char *haystack, const char *needle) {
  char *new_ptr = (char *)haystack;
  int flag = 0;
  for (s21_size_t i = 0; i < s21_strlen(haystack) && flag == 0; i++) {
    if (s21_memcmp(new_ptr, needle, sizeof(char) * s21_strlen(needle)) == 0) {
      flag = 1;
    } else {
      new_ptr++;
    }
  }
  if (s21_strlen(new_ptr) == 0) {
    new_ptr = s21_NULL;
  }
  return new_ptr;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *return_str_copy;
  if (!str || !src || start_index > s21_strlen(src)) {
    return_str_copy = s21_NULL;
  } else {
    char *str_copy =
        calloc(s21_strlen(str) + s21_strlen(src) + 1, sizeof(char));
    if (!str_copy) {
      return_str_copy = s21_NULL;
    } else {
      return_str_copy = str_copy;
      s21_memcpy(str_copy, src, sizeof(char) * start_index);
      str_copy += start_index;
      s21_memcpy(str_copy, str, sizeof(char) * s21_strlen(str));
      str_copy += s21_strlen(str);
      src += start_index;
      s21_memcpy(str_copy, src, sizeof(char) * s21_strlen(src));
    }
  }
  return return_str_copy;
}

void *s21_trim(const char *src, const char *trim_chars) {
  int l_occ = 0;
  int r_occ = 0;
  char *new_str;
  if (!src || !trim_chars) {
    new_str = s21_NULL;
  } else {
    new_str = calloc(s21_strlen(src) + 1 - l_occ - r_occ, sizeof(char));
    if (!new_str) {
      src = s21_NULL;
    } else {
      const char *left_ptr = src;
      const char *right_ptr = src + s21_strlen(src) - 1;
      int count = 0;
      while (left_ptr <= right_ptr) {
        if ((*trim_chars == 0 && 0 < *left_ptr && *left_ptr < 33)) {
          left_ptr += 1;
        } else if ((s21_strchr(trim_chars, *left_ptr) && l_occ == 0)) {
          left_ptr += 1;
        } else {
          l_occ = 1;
        }
        if ((*trim_chars == 0 && 0 < *right_ptr && *right_ptr < 33)) {
          right_ptr -= 1;
        } else if ((s21_strchr(trim_chars, *right_ptr) && r_occ == 0) ||
                   (*trim_chars == 0 && 0 < *right_ptr && *right_ptr < 33)) {
          right_ptr -= 1;
        } else {
          r_occ = 1;
        }
        if (l_occ == 1 && r_occ == 1) {
          new_str[count] = *left_ptr;
          count += 1;
          left_ptr += 1;
        }
      }
    }
  }
  return new_str;
}

void *s21_to_lower(const char *str) {
  char *str_copy;
  if (!str) {
    str_copy = s21_NULL;
  } else {
    str_copy = calloc(s21_strlen(str) + 1, sizeof(char));
    if (!str_copy) {
      str_copy = s21_NULL;
    } else {
      for (s21_size_t i = 0; i < s21_strlen(str); i++) {
        if (str[i] > 'Z' || str[i] < 'A') {
          str_copy[i] = str[i];
        } else {
          str_copy[i] = str[i] + 32;
        }
      }
    }
  }
  return str_copy;
}

void *s21_to_upper(const char *str) {
  char *str_copy;
  if (str == s21_NULL) {
    str_copy = s21_NULL;
  } else {
    str_copy = calloc(s21_strlen(str) + 1, sizeof(char));
    if (!str_copy) {
      str_copy = s21_NULL;
    } else {
      for (s21_size_t i = 0; i < s21_strlen(str); i++) {
        if (str[i] > 'z' || str[i] < 'a') {
          str_copy[i] = str[i];
        } else {
          str_copy[i] = str[i] - 32;
        }
      }
    }
  }
  return str_copy;
}

char *s21_strerror(int errnum) {
  static char resn[500] = {0};
  char *res = resn;
#if defined __APPLE__
  char *strerrors[1000] = {
      "Undefined error: 0",
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
  };
  if (0 <= errnum && errnum < 107) {
    res = strerrors[errnum];
  } else {
    s21_sprintf(res, "Unknown error: %d", errnum);
  }
#elif defined __linux__
  char *strerrors[1000] = {
      "Success",
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
      "Memory page has hardware error",
  };
  if (0 <= errnum && errnum < 134) {
    res = strerrors[errnum];
  } else {
    s21_sprintf(res, "Unknown error %d", errnum);
  }
#endif
  return res;
}
