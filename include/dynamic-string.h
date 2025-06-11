#ifndef DYNAMIC_STRING_H
#define DYNAMIC_STRING_H

#include <stdbool.h>

#define str_auto\
	\
	/* Use as a prefix to ensure automatic freeing when variable goes out of scope.
	 * Gcc or clang required! */\
	\
	__attribute__((cleanup(str_destroy))) str_t*

/* String object opaque struct */
typedef struct str str_t;

/* Required for testing */
extern bool _is_exit_called;

/* Creates a new instance of str_t.
 * Exits program with status code '1' on failure. */
str_t *create_str();

/* Required for testing */
extern bool _is_str_destroyed;

/* Frees all memory allocated in 'str' */
void str_destroy(str_t **str);

#endif
