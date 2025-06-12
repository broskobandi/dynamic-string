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

/* dynamic-string
 * Dynamic string written in C. */

#ifndef DYNAMIC_STRING_H
#define DYNAMIC_STRING_H

#include <stdbool.h>
#include <sys/types.h>

#define str_auto\
	\
	/* Use as a prefix to ensure automatic freeing when variable goes out of scope.
	 * Gcc or clang required! */\
	\
	__attribute__((cleanup(str_destroy))) str_t*

/* This is required for testing. */
extern bool _is_exit_called;

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

/* Prepends 'src' at the beginning of 'str'.
 * Returns a pointer to the data or NULL on failure. */
const char *str_prepend(str_t *str, const char *src);

/* Returns a pointer to the data stored in 'str' or NULL on failure.
 * This is a reference and not a copy, changes made to 
 * 'str' will be reflected through this. */
const char *str_data(const str_t *str);

/* Returns the length of 'str'.
 * Exits the program with status code '1' if 'str' is NULL. */
ulong str_len(const str_t *str);

/* Returns the capacity of 'str'.
 * Exits the program with status code '1' if 'str' is NULL. */
ulong str_capacity(const str_t *str);

/* Appends 'c' at the end of 'str'.
 * Returns '0' on success and '1' on failure. */
int str_push_back(str_t *str, char c);

/* Prepends 'c' at the front of 'str'.
 * Returns '0' on success and '1' on failure. */
int str_push_front(str_t *str, char c);

/* Removes and returns the last character of 'str'.
 * Exits the program with status code '1' on failure. */
char str_pop(str_t *str);

/* Returns 'true' if 'str' and 'src' are the same, otherwise returns 'false'.
 * Exits the program with status code '1' if 'str' or 'src' is NULL */
bool str_cmp(const str_t *str, const char *src);

/* Replaces all occurrences of 'old_str' to 'new_str' in 'str'.
 * Returns a pointer to the data or NULL on failure. */
const char *str_replace(str_t *str, const char *old_str, const char *new_str);

/* Returns 'true' if 'str' has 'src' in it, otherwise returns 'false'.
 * Exits the program with status code '1' if 'str' or 'src' is NULL */
bool str_has(const str_t *str, const char *src);

#endif
