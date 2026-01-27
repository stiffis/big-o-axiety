#ifndef DYN_STRING_H
#define DYN_STRING_H

#include <stddef.h>

/**
 * Dynamic String - Self-growing character array with null terminator
 *
 * Key concepts:
 * - length: current number of characters (excluding null terminator)
 * - capacity: total available space (including null terminator)
 * - data: always null-terminated for C compatibility
 * - When length + 1 >= capacity, resize happens (typically 2x)
 */

// Opaque pointer - hides internal implementation
typedef struct String String;

/* ========== CONSTRUCTORS AND DESTRUCTORS ========== */

/**
 * Creates an empty string
 * @return Pointer to string, or NULL if malloc fails
 */
String *string_create(void);

/**
 * Creates a string from a C-string literal
 * @param cstr C-string to copy from (must be null-terminated)
 * @return Pointer to string, or NULL if malloc fails or cstr is NULL
 */
String *string_create_from(const char *cstr);

/**
 * Safely creates a string from a buffer with length limit
 * @param cstr Buffer to copy from (may not be null-terminated)
 * @param max_len Maximum length to read from cstr
 * @return Pointer to string, or NULL if malloc fails or unterminated
 */
String *string_create_from_n(const char *cstr, size_t max_len);

/**
 * Creates a string with specific initial capacity
 * @param capacity Initial capacity
 * @return Pointer to string, or NULL if malloc fails
 */
String *string_create_with_capacity(size_t capacity);

/**
 * Frees all string memory
 * @param str String to destroy (can be NULL)
 */
void string_destroy(String *str);

/* ========== MODIFIERS ========== */

/**
 * Appends a single character
 * @param str Target string
 * @param ch Character to append
 * @return 0 on success, -1 on error
 *
 * Complexity: O(1) amortized
 */
int string_push(String *str, char ch);

/**
 * Removes and returns the last character
 * @param str Target string
 * @param out_ch Pointer to store removed character
 * @return 0 on success, -1 on error (empty string)
 *
 * Complexity: O(1)
 */
int string_pop(String *str, char *out_ch);

/**
 * Appends a C-string to the end
 * @param str Target string
 * @param cstr C-string to append
 * @return 0 on success, -1 on error
 *
 * Complexity: O(n) where n is length of cstr
 */
int string_append(String *str, const char *cstr);

/**
 * Safely appends a C-string with length limit
 * @param str Target string
 * @param cstr C-string to append (may not be null-terminated)
 * @param max_len Maximum length to read from cstr
 * @return 0 on success, -1 on error (including unterminated string)
 *
 * Complexity: O(n) where n is min(strlen(cstr), max_len)
 */
int string_append_n(String *str, const char *cstr, size_t max_len);

/**
 * Appends another String to the end
 * @param str Target string
 * @param other String to append
 * @return 0 on success, -1 on error
 *
 * Complexity: O(n) where n is length of other
 */
int string_concat(String *str, const String *other);

/**
 * Inserts a character at a specific position
 * @param str Target string
 * @param index Position to insert (0 <= index <= length)
 * @param ch Character to insert
 * @return 0 on success, -1 on error
 *
 * Complexity: O(n)
 */
int string_insert_char(String *str, size_t index, char ch);

/**
 * Inserts a C-string at a specific position
 * @param str Target string
 * @param index Position to insert
 * @param cstr C-string to insert
 * @return 0 on success, -1 on error
 *
 * Complexity: O(n + m) where m is length of cstr
 */
int string_insert(String *str, size_t index, const char *cstr);

/**
 * Safely inserts a buffer with length limit
 * @param str Target string
 * @param index Position to insert
 * @param cstr Buffer to insert (may not be null-terminated)
 * @param max_len Maximum length to read from cstr
 * @return 0 on success, -1 on error (including unterminated string)
 *
 * Complexity: O(n + m) where m is min(strlen(cstr), max_len)
 */
int string_insert_n(String *str, size_t index, const char *cstr, size_t max_len);

/**
 * Removes all characters (length = 0, but keeps capacity)
 * @param str Target string
 */
void string_clear(String *str);

/* ========== ACCESSORS (QUERY) ========== */

/**
 * Gets character at a specific position
 * @param str Target string
 * @param index Position to query
 * @param out_ch Pointer to store character
 * @return 0 on success, -1 on error
 *
 * Complexity: O(1)
 */
int string_get(const String *str, size_t index, char *out_ch);

/**
 * Sets character at a specific position
 * @param str Target string
 * @param index Position to modify
 * @param ch New character
 * @return 0 on success, -1 on error
 *
 * Complexity: O(1)
 */
int string_set(String *str, size_t index, char ch);

/**
 * Returns internal C-string pointer (read-only)
 * @param str Target string
 * @return Pointer to internal data, or NULL if str is NULL
 *
 * WARNING: Pointer becomes invalid after any modification
 */
const char *string_cstr(const String *str);

/**
 * Number of characters (excluding null terminator)
 * @param str Target string
 * @return Length (0 if str is NULL)
 */
size_t string_length(const String *str);

/**
 * Total capacity
 * @param str Target string
 * @return Capacity (0 if str is NULL)
 */
size_t string_capacity(const String *str);

/**
 * Checks if string is empty
 * @param str Target string
 * @return 1 if empty, 0 otherwise
 */
int string_is_empty(const String *str);

/* ========== SEARCH AND COMPARISON ========== */

/**
 * Finds first occurrence of character
 * @param str Target string
 * @param ch Character to find
 * @return Index of character, or -1 if not found
 *
 * Complexity: O(n)
 */
int string_find_char(const String *str, char ch);

/**
 * Finds first occurrence of substring
 * @param str Target string
 * @param substr Substring to find
 * @return Index of first match, or -1 if not found
 *
 * Complexity: O(n*m) naive search
 */
int string_find(const String *str, const char *substr);

/**
 * Safely finds substring with length limit
 * @param str Target string
 * @param substr Buffer to find (may not be null-terminated)
 * @param max_len Maximum length to read from substr
 * @return Index of first match, or -1 if not found or unterminated
 *
 * Complexity: O(n*m) naive search
 */
int string_find_n(const String *str, const char *substr, size_t max_len);

/**
 * Compares two strings lexicographically
 * @param str1 First string
 * @param str2 Second string (C-string)
 * @return <0 if str1 < str2, 0 if equal, >0 if str1 > str2
 *
 * Returns -2 on NULL input
 */
int string_compare(const String *str1, const char *str2);

/**
 * Checks if two strings are equal
 * @param str1 First string
 * @param str2 Second string (C-string)
 * @return 1 if equal, 0 otherwise
 */
int string_equals(const String *str1, const char *str2);

/* ========== SUBSTRINGS ========== */

/**
 * Creates a substring
 * @param str Source string
 * @param start Start index (inclusive)
 * @param length Number of characters
 * @return New string with substring, or NULL on error
 *
 * Complexity: O(length)
 */
String *string_substring(const String *str, size_t start, size_t length);

/**
 * Creates a copy of the string
 * @param str Source string
 * @return New string copy, or NULL on error
 *
 * Complexity: O(n)
 */
String *string_copy(const String *str);

/* ========== UTILITIES ========== */

/**
 * Prints the string to stdout
 * @param str Target string
 */
void string_print(const String *str);

/**
 * Prints the string with metadata (length, capacity)
 * @param str Target string
 */
void string_debug(const String *str);

#endif // DYN_STRING_H
