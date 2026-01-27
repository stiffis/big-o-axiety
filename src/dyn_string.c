#include "../include/dyn_string.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_CAPACITY 32
#define GROWTH_FACTOR 2

struct String {
    char *data;
    size_t length;   // Number of characters (excluding null terminator)
    size_t capacity; // Total space including null terminator
};

static int _string_resize(struct String *str, size_t new_capacity) {
    if (!str || new_capacity <= str->length) {
        return -1;
    }
    
    char *new_data = realloc(str->data, new_capacity);
    if (!new_data) {
        return -1;
    }
    
    str->data = new_data;
    str->capacity = new_capacity;
    return 0;
}

static int _string_ensure_capacity(struct String *str, size_t required) {
    if (str->capacity > required) {
        return 0;
    }
    
    size_t new_capacity = str->capacity * GROWTH_FACTOR;
    while (new_capacity <= required) {
        new_capacity *= GROWTH_FACTOR;
    }
    
    return _string_resize(str, new_capacity);
}

String* string_create(void) {
    return string_create_with_capacity(DEFAULT_CAPACITY);
}

String* string_create_from(const char *cstr) {
    if (!cstr) {
        return NULL;
    }
    
    size_t len = strlen(cstr);
    size_t capacity = len + 1;
    if (capacity < DEFAULT_CAPACITY) {
        capacity = DEFAULT_CAPACITY;
    }
    
    struct String *str = string_create_with_capacity(capacity);
    if (!str) {
        return NULL;
    }
    
    memcpy(str->data, cstr, len);
    str->data[len] = '\0';
    str->length = len;
    
    return str;
}

String* string_create_from_n(const char *cstr, size_t max_len) {
    if (!cstr) {
        return NULL;
    }
    
    size_t len = 0;
    while (len < max_len && cstr[len] != '\0') {
        len++;
    }
    
    if (len == max_len && cstr[len] != '\0') {
        return NULL;
    }
    
    size_t capacity = len + 1;
    if (capacity < DEFAULT_CAPACITY) {
        capacity = DEFAULT_CAPACITY;
    }
    
    struct String *str = string_create_with_capacity(capacity);
    if (!str) {
        return NULL;
    }
    
    memcpy(str->data, cstr, len);
    str->data[len] = '\0';
    str->length = len;
    
    return str;
}

String* string_create_with_capacity(size_t capacity) {
    if (capacity < 2) {
        capacity = DEFAULT_CAPACITY;
    }
    
    struct String *str = malloc(sizeof(struct String));
    if (!str) {
        return NULL;
    }
    
    str->data = malloc(capacity);
    if (!str->data) {
        free(str);
        return NULL;
    }
    
    str->data[0] = '\0';
    str->length = 0;
    str->capacity = capacity;
    
    return str;
}

void string_destroy(String *str) {
    if (!str) {
        return;
    }
    
    free(str->data);
    free(str);
}

int string_push(String *str, char ch) {
    if (!str) {
        return -1;
    }
    
    // Need space for character + null terminator
    if (_string_ensure_capacity(str, str->length + 1) != 0) {
        return -1;
    }
    
    str->data[str->length] = ch;
    str->length++;
    str->data[str->length] = '\0';
    
    return 0;
}

int string_pop(String *str, char *out_ch) {
    if (!str || !out_ch || str->length == 0) {
        return -1;
    }
    
    str->length--;
    *out_ch = str->data[str->length];
    str->data[str->length] = '\0';
    
    return 0;
}

int string_append(String *str, const char *cstr) {
    if (!str || !cstr) {
        return -1;
    }
    
    size_t cstr_len = strlen(cstr);
    if (cstr_len == 0) {
        return 0;
    }
    
    if (_string_ensure_capacity(str, str->length + cstr_len) != 0) {
        return -1;
    }
    
    memcpy(str->data + str->length, cstr, cstr_len);
    str->length += cstr_len;
    str->data[str->length] = '\0';
    
    return 0;
}

int string_append_n(String *str, const char *cstr, size_t max_len) {
    if (!str || !cstr) {
        return -1;
    }
    
    size_t len = 0;
    while (len < max_len && cstr[len] != '\0') {
        len++;
    }
    
    if (len == max_len && cstr[len] != '\0') {
        return -1;
    }
    
    if (len == 0) {
        return 0;
    }
    
    if (_string_ensure_capacity(str, str->length + len) != 0) {
        return -1;
    }
    
    memcpy(str->data + str->length, cstr, len);
    str->length += len;
    str->data[str->length] = '\0';
    
    return 0;
}

int string_concat(String *str, const String *other) {
    if (!str || !other) {
        return -1;
    }
    
    return string_append(str, other->data);
}

int string_insert_char(String *str, size_t index, char ch) {
    if (!str || index > str->length) {
        return -1;
    }
    
    if (_string_ensure_capacity(str, str->length + 1) != 0) {
        return -1;
    }
    
    memmove(str->data + index + 1, str->data + index, str->length - index);
    str->data[index] = ch;
    str->length++;
    str->data[str->length] = '\0';
    
    return 0;
}

int string_insert(String *str, size_t index, const char *cstr) {
    if (!str || !cstr || index > str->length) {
        return -1;
    }
    
    size_t cstr_len = strlen(cstr);
    if (cstr_len == 0) {
        return 0;
    }
    
    if (_string_ensure_capacity(str, str->length + cstr_len) != 0) {
        return -1;
    }
    
    memmove(str->data + index + cstr_len, str->data + index, 
            str->length - index);
    memcpy(str->data + index, cstr, cstr_len);
    str->length += cstr_len;
    str->data[str->length] = '\0';
    
    return 0;
}

int string_insert_n(String *str, size_t index, const char *cstr, size_t max_len) {
    if (!str || !cstr || index > str->length) {
        return -1;
    }
    
    size_t len = 0;
    while (len < max_len && cstr[len] != '\0') {
        len++;
    }
    
    if (len == max_len && cstr[len] != '\0') {
        return -1;
    }
    
    if (len == 0) {
        return 0;
    }
    
    if (_string_ensure_capacity(str, str->length + len) != 0) {
        return -1;
    }
    
    memmove(str->data + index + len, str->data + index, 
            str->length - index);
    memcpy(str->data + index, cstr, len);
    str->length += len;
    str->data[str->length] = '\0';
    
    return 0;
}

void string_clear(String *str) {
    if (!str) {
        return;
    }
    
    str->length = 0;
    str->data[0] = '\0';
}

int string_get(const String *str, size_t index, char *out_ch) {
    if (!str || !out_ch || index >= str->length) {
        return -1;
    }
    
    *out_ch = str->data[index];
    return 0;
}

int string_set(String *str, size_t index, char ch) {
    if (!str || index >= str->length) {
        return -1;
    }
    
    str->data[index] = ch;
    return 0;
}

const char* string_cstr(const String *str) {
    if (!str) {
        return NULL;
    }
    
    return str->data;
}

size_t string_length(const String *str) {
    if (!str) {
        return 0;
    }
    
    return str->length;
}

size_t string_capacity(const String *str) {
    if (!str) {
        return 0;
    }
    
    return str->capacity;
}

int string_is_empty(const String *str) {
    if (!str) {
        return 1;
    }
    
    return str->length == 0;
}

int string_find_char(const String *str, char ch) {
    if (!str) {
        return -1;
    }
    
    for (size_t i = 0; i < str->length; i++) {
        if (str->data[i] == ch) {
            return (int)i;
        }
    }
    
    return -1;
}

int string_find(const String *str, const char *substr) {
    if (!str || !substr) {
        return -1;
    }
    
    size_t substr_len = strlen(substr);
    if (substr_len == 0) {
        return 0;
    }
    
    if (substr_len > str->length) {
        return -1;
    }
    
    for (size_t i = 0; i <= str->length - substr_len; i++) {
        if (memcmp(str->data + i, substr, substr_len) == 0) {
            return (int)i;
        }
    }
    
    return -1;
}

int string_find_n(const String *str, const char *substr, size_t max_len) {
    if (!str || !substr) {
        return -1;
    }
    
    size_t len = 0;
    while (len < max_len && substr[len] != '\0') {
        len++;
    }
    
    if (len == max_len && substr[len] != '\0') {
        return -1;
    }
    
    if (len == 0) {
        return 0;
    }
    
    if (len > str->length) {
        return -1;
    }
    
    for (size_t i = 0; i <= str->length - len; i++) {
        if (memcmp(str->data + i, substr, len) == 0) {
            return (int)i;
        }
    }
    
    return -1;
}

int string_compare(const String *str1, const char *str2) {
    if (!str1 || !str2) {
        return -2;
    }
    
    return strcmp(str1->data, str2);
}

int string_equals(const String *str1, const char *str2) {
    return string_compare(str1, str2) == 0;
}

String* string_substring(const String *str, size_t start, size_t length) {
    if (!str || start >= str->length) {
        return NULL;
    }
    
    if (start + length > str->length) {
        length = str->length - start;
    }
    
    struct String *substr = string_create_with_capacity(length + 1);
    if (!substr) {
        return NULL;
    }
    
    memcpy(substr->data, str->data + start, length);
    substr->data[length] = '\0';
    substr->length = length;
    
    return substr;
}

String* string_copy(const String *str) {
    if (!str) {
        return NULL;
    }
    
    return string_substring(str, 0, str->length);
}

void string_print(const String *str) {
    if (!str) {
        printf("(null)");
        return;
    }
    
    printf("%s", str->data);
}

void string_debug(const String *str) {
    if (!str) {
        printf("String(NULL)\n");
        return;
    }
    
    printf("String(\"%s\", length: %zu, capacity: %zu)\n", 
           str->data, str->length, str->capacity);
}
