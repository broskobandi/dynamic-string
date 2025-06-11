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
	if (!str) return NULL;

	ulong old_capacity = str->capacity;
	ulong old_len = str->len;
	ulong new_len = old_len + strlen(src);
	ulong new_capacity = old_capacity;

	while (new_len + 1 > new_capacity) {
		new_capacity *= 2;
	}

	if (new_capacity != old_capacity) {
		char *tmp = realloc(str->data, new_capacity * sizeof(char));
		if (!tmp) return NULL;
		str->data = tmp;
	}

	strcpy(&str->data[old_len], src);

	str->capacity = new_capacity;
	str->len = new_len;

	return str->data;
}


