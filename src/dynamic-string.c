#include "dynamic-string.h"
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>

struct str {
	char *data;
	ulong capacity;
	ulong len;
};

// Constructor
#define DEFAULT_CAPACITY 16
bool _is_exit_called = false;
str_t *create_str() {
	str_t *str = calloc(1, sizeof(str_t));
	if (!str) goto exit;
	str->data = calloc(1, sizeof(char));
	if (!str->data) goto exit;
	str->capacity = DEFAULT_CAPACITY;
	str->len = 0;
exit:
#ifndef NDEBUG
		fprintf(stderr, "calloc() failed in create_str().\n");
#endif
#ifndef TESTING
		exit(1);
#else
		_is_exit_called = true;
#endif
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
