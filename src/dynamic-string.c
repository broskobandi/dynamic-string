/*
MIT License

Copyright (c) 2025 broskobandi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

// Implementation for dynamic-string.h

#include "dynamic-string.h"
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

struct str {
	char *data;
	ulong capacity;
	ulong len;
};

bool _is_exit_called = false;

// Constructor
#define DEFAULT_CAPACITY 16
str_t *str_create() {
	str_t *str = calloc(1, sizeof(str_t));
	if (!str) return NULL;
	str->data = calloc(1, sizeof(char));
	if (!str->data) return NULL;
	str->capacity = DEFAULT_CAPACITY;
	str->len = 0;
	return str;
}

// Destructor
bool _is_str_destroyed = false;
void str_destroy(str_t **str) {
	if (*str && str) {
		if ((*str)->data)
			free((*str)->data);
		free(*str);
		*str = NULL;
		_is_str_destroyed = true;
	}
}

// str_append
const char *str_append(str_t *str, const char *src) {
	if (!str || !src) return NULL;

	ulong old_capacity = str->capacity;
	ulong old_len = str->len;
	ulong new_len = old_len + strlen(src);
	ulong new_capacity = old_capacity;

	while (new_len + 1 > new_capacity) {
		new_capacity *= 2;
	}

	if (new_capacity != old_capacity) {
		char *tmp = realloc(str->data, new_capacity);
		if (!tmp) return NULL;
		str->data = tmp;
	}

	if (!strcpy(&str->data[old_len], src)) return NULL;

	str->capacity = new_capacity;
	str->len = new_len;

	return str->data;
}

// str_prepend
const char *str_prepend(str_t *str, const char *src) {
	if (!str || !src) return NULL;

	ulong old_capacity = str->capacity;
	ulong old_len = str->len;
	ulong new_len = old_len + strlen(src);
	ulong new_capacity = old_capacity;

	while (new_len + 1 > new_capacity) {
		new_capacity *= 2;
	}

	if (new_capacity != old_capacity) {
		char *tmp = realloc(str->data, new_capacity);
		if (!tmp) return NULL;
		str->data = tmp;
	}

	memmove(&str->data[strlen(src)], str->data, old_len + 1);

	memcpy(&str->data[0], src, strlen(src));

	str->capacity = new_capacity;
	str->len = new_len;

	printf("%s\n", str->data);

	return str->data;
}

// str_data
const char *str_data(const str_t *str) {
	if (!str) return NULL;
	return str->data;
}

// str_len
ulong str_len(const str_t *str) {
	if (!str) {
#ifndef NDEBUG
		fprintf(stderr, "NULL ptr passed to str_len().\n");
#endif
#ifndef TESTING
		exit(1);
#endif
		_is_exit_called = true;
	} else {
		return str->len;
	}
	return (ulong)-1;
}

// str_capacity
ulong str_capacity(const str_t *str) {
	if (!str) {
#ifndef NDEBUG
		fprintf(stderr, "NULL ptr passed to str_capacity().\n");
#endif
#ifndef TESTING
		exit(1);
#endif
		_is_exit_called = true;
	} else {
		return str->capacity;
	}
	return (ulong)-1;
}

// str_push_back
int str_push_back(str_t *str, char c) {
	if (!str) return 1;

	ulong old_capacity = str->capacity;
	ulong old_len = str->len;
	ulong new_capacity = old_capacity;
	ulong new_len = old_len + 1;

	while (new_len + 1 > new_capacity) {
		new_capacity *= 2;
	}

	if (new_capacity != old_capacity) {
		char *tmp = realloc(str->data, new_capacity);
		if (!tmp) return 1;
		str->data = tmp;
	}

	str->data[old_len] = c;
	str->data[new_len] = '\0';

	str->capacity = new_capacity;
	str->len = new_len;

	return 0;
}

int str_push_front(str_t *str, char c) {
	if (!str) return 1;

	ulong old_capacity = str->capacity;
	ulong old_len = str->len;
	ulong new_capacity = old_capacity;
	ulong new_len = old_len + 1;

	while (new_len + 1 > new_capacity) {
		new_capacity *= 2;
	}

	if (new_capacity != old_capacity) {
		char *tmp = realloc(str->data, new_capacity);
		if (!tmp) return 1;
		str->data = tmp;
	}

	memmove(&str->data[1], str->data, str->len + 1);

	str->data[0] = c;

	str->capacity = new_capacity;
	str->len = new_len;

	return 0;
}

// str_pop
char str_pop(str_t *str) {
	if (!str || !str->len) {
exit:
#ifndef NDEBUG
		fprintf(stderr, "NULL ptr passed to str_capacity(), or string length is is zero.\n");
#endif
#ifndef TESTING
		exit(1);
#endif
		_is_exit_called = true;
	} else {
		ulong old_len = str->len;
		ulong old_capacity = str->capacity;
		ulong new_len = old_len - 1;
		ulong new_capacity = old_capacity;

		while (new_len + 1 < new_capacity / 2 && new_capacity / 2 >= DEFAULT_CAPACITY) {
			new_capacity /= 2;
		}

		char c = str->data[old_len - 1];

		memset(&str->data[old_len - 1], 0, sizeof(char));

		if (new_capacity != old_capacity) {
			char *tmp = realloc(str->data, new_capacity);
			if (!tmp) goto exit;
			str->data = tmp;
		}

		str->data[new_len] = '\0';

		str->capacity = new_capacity;
		str->len = new_len;

		return c;
	}
	return '\0';
}

// str_cmp
bool str_cmp(const str_t *str, const char *src) {
	if (!str || !src) {
#ifndef NDEBUG
		fprintf(stderr, "NULL ptr passed to str_capacity().\n");
#endif
#ifndef TESTING
		exit(1);
#endif
		_is_exit_called = true;
	} else {
		if (strcmp(str_data(str), src) == 0) {
			return true;
		} else {
			return false;
		}
	}
	return false;
}

// str_replace
const char *str_replace(str_t *str, const char *old_str, const char *new_str) {
	if (!str || !old_str || !new_str || !strlen(old_str)) return NULL;

	ulong old_capacity = str->capacity;
	ulong old_len = str->len;
	ulong new_capacity = old_capacity;
	ulong num_old_str = 0;
	for (ulong i = 0; i < old_len; i++) {
		if (strstr(&str->data[i], old_str) == &str->data[i]) {
			num_old_str++;
			i += strlen(old_str) - 1;
		}
	}
	ulong new_len =
		old_len - (num_old_str * strlen(old_str)) + (num_old_str * strlen(new_str));

	char *result = malloc(new_len + 1);
	ulong data_i = 0;
	ulong result_i = 0;

	while (data_i < old_len) {
		if (strstr(&str->data[data_i], old_str) == &str->data[data_i]) {
			for (ulong i = 0; i < strlen(new_str); i++) {
				result[result_i] = new_str[i];
				result_i++;
			}
			data_i += strlen(old_str);
		} else {
			result[result_i] = str->data[data_i];
			result_i++;
			data_i++;
		}
	}
	if (new_len != result_i) return NULL;
	result[new_len] = '\0';

	if (new_len > old_len) {
		while (new_len + 1 > new_capacity) {
			new_capacity *= 2;
		}
	} else if (new_len < old_len) {
		while (new_len + 1 < new_capacity / 2 && new_capacity / 2 >= DEFAULT_CAPACITY) {
			new_capacity /= 2;
		}
	}

	if (new_capacity != old_capacity) {
		char *tmp = realloc(str->data, new_capacity);
		if (!tmp) return NULL;
		str->data = tmp;
	}

	if (strcpy(str->data, result) == NULL) return NULL;

	str->len = new_len;
	str->capacity = new_capacity;
	free(result);
	return str->data;
}

// str_has
bool str_has(const str_t *str, const char *src) {
	if (!str || !src) {
#ifndef NDEBUG
		fprintf(stderr, "NULL ptr passed to str_has().\n");
#endif
#ifndef TESTING
		exit(1);
#endif
		_is_exit_called = true;
	} else {
		if (strstr(str->data, src)) {
			return true;
		} else {
			return false;
		}
	}
	return false;
}
