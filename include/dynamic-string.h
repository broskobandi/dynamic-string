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

/* Returns a new instance of str_t or NULL on failure. */
str_t *str_create();

/* Required for testing */
extern bool _is_str_destroyed;

/* Frees all memory allocated in 'str' */
void str_destroy(str_t **str);

/* Appends 'src' at the end of 'str'.
 * Returns a pointer to the data or NULL on failure. */
const char *str_append(str_t *str, const char *src);

/* Returns a pointer to the data stored in 'str' or NULL on failure.
 * This is a reference and not a copy, changes made to 
 * 'str' will be reflected through this. */
const char *str_data(const str_t *str);

#endif
