#ifndef DYN_STRING_H
#define DYN_STRING_H

#include <stddef.h>

/** Self-growing string with automatic null termination. */
typedef struct String String;

/** Creates an empty string. @return String pointer or NULL. */
String *string_create(void);

/** Creates string from C-string. @return String or NULL. */
String *string_create_from(const char *cstr);

/** Creates string from buffer with length limit. @return String or NULL. */
String *string_create_from_n(const char *cstr, size_t max_len);

/** Creates string with specific capacity. @return String or NULL. */
String *string_create_with_capacity(size_t capacity);

/** Frees all string memory. */
void string_destroy(String *str);

/** Appends a character. @return 0 on success, -1 on error. */
int string_push(String *str, char ch);

/** Removes and returns last character. @return 0 on success, -1 on error. */
int string_pop(String *str, char *out_ch);

/** Appends a C-string. @return 0 on success, -1 on error. */
int string_append(String *str, const char *cstr);

/** Safely appends C-string with length limit. @return 0 on success, -1 on error. */
int string_append_n(String *str, const char *cstr, size_t max_len);

/** Appends another String. @return 0 on success, -1 on error. */
int string_concat(String *str, const String *other);

/** Inserts a character at position. @return 0 on success, -1 on error. */
int string_insert_char(String *str, size_t index, char ch);

/** Inserts C-string at position. @return 0 on success, -1 on error. */
int string_insert(String *str, size_t index, const char *cstr);

/** Safely inserts buffer with length limit. @return 0 on success, -1 on error. */
int string_insert_n(String *str, size_t index, const char *cstr, size_t max_len);

/** Clears string (length = 0, keeps capacity). */
void string_clear(String *str);

/** Gets character at position. @return 0 on success, -1 on error. */
int string_get(const String *str, size_t index, char *out_ch);

/** Sets character at position. @return 0 on success, -1 on error. */
int string_set(String *str, size_t index, char ch);

/** Returns internal C-string pointer (read-only). WARNING: invalid after modification. */
const char *string_cstr(const String *str);

/** Returns string length (excluding null terminator). */
size_t string_length(const String *str);

/** Returns total capacity. */
size_t string_capacity(const String *str);

/** Checks if string is empty. @return 1 if empty, 0 otherwise. */
int string_is_empty(const String *str);

/** Finds first occurrence of character. @return Index or -1. */
int string_find_char(const String *str, char ch);

/** Finds first occurrence of substring. @return Index or -1. */
int string_find(const String *str, const char *substr);

/** Safely finds substring with length limit. @return Index or -1. */
int string_find_n(const String *str, const char *substr, size_t max_len);

/** Compares strings lexicographically. @return <0, 0, or >0. Returns -2 on NULL. */
int string_compare(const String *str1, const char *str2);

/** Checks if strings are equal. @return 1 if equal, 0 otherwise. */
int string_equals(const String *str1, const char *str2);

/** Creates a substring. @return New string or NULL. */
String *string_substring(const String *str, size_t start, size_t length);

/** Creates a copy of the string. @return New string or NULL. */
String *string_copy(const String *str);

/** Prints string to stdout. */
void string_print(const String *str);

/** Prints string with metadata (length, capacity). */
void string_debug(const String *str);

#endif // DYN_STRING_H