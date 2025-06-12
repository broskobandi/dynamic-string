#include "dynamic-string.h"
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

uint completed = 0;
uint failed = 0;
uint passed = 0;

#define ASSERT(expr)\
	if (!(expr)) {\
		printf("***[FAILED]: %s\n", #expr);\
		printf("\tLine: %d\n", __LINE__);\
		failed++;\
	} else {\
		printf("[PASSED]: %s\n", #expr);\
		passed++;\
	}\
	completed++;

void print_results() {
	printf("\nCompleted:\t%d\n", completed);
	if (!failed) {
		printf("All tests passed.\n");
	} else {
		printf("Passed:\t\t%d\n", passed);
		printf("Failed:\t\t%d\n", failed);
	}
}

int test_new() {
	{
		str_auto str = str_create();
		if (str == NULL) return 1;
		_is_str_destroyed = false;
	}
	if (_is_str_destroyed != true) return 2;
	return 0;
}

int test_append() {
	str_auto str = str_create();
	if (!str) return 1;
	const char *expected_content = "Hello, World!";
	if (strcmp(str_append(str, expected_content), expected_content) != 0)
		return 1;
	const char *new_content = " This is a kickass library.";
	expected_content = "Hello, World! This is a kickass library.";
	if (strcmp(str_append(str, new_content), expected_content) != 0)
		return 2;
	return 0;
}

int test_data() {
	str_auto str = str_create();
	if (!str) return 1;
	const char *expected_content = "Hello, World! This is a kickass library.";
	if (str_append(str, expected_content) == NULL) return 1;
	if (strcmp(str_data(str), expected_content) != 0)
		return 2;
	return 0;
}

int test_len() {
	str_auto str = str_create();
	if (!str) return 1;
	if (str_len(str) != 0) return 1;
	const char *new_text = "Hello, World!";
	if (str_append(str, new_text) == NULL) return 2;
	if (str_len(str) != strlen(new_text)) return 3;
	str_t *str_null = NULL;
	_is_exit_called = false;
	str_len(str_null);
	if (_is_exit_called == false) return 4;
	return 0;
}

int test_capacity() {
	str_auto str = str_create();
	if (!str) return 1;
	if (str_capacity(str) != 16) return 1;
	str_t *str_null = NULL;
	_is_exit_called = false;
	str_capacity(str_null);
	if (_is_exit_called == false) return 4;
	return 0;
}

int test_expand_with_append() {
	str_auto str = str_create();
	if (!str) return 1;
	ulong expected_capacity = str_capacity(str);
	while (str_capacity(str) < 10000000) {
		str_append(str, "c");
		if (str_len(str) + 1 > expected_capacity) expected_capacity *= 2;
		if (str_capacity(str) != expected_capacity) return 1;
	}
	return 0;
}

int test_push_back() {
	str_auto str = str_create();
	if (!str) return 1;
	if (str_append(str, "Hello, World") == NULL) return 1;
	if (str_push_back(str, '!') == 1) return 2;
	if (strcmp(str_data(str), "Hello, World!") != 0) return 3;
	return 0;
}

int test_expand_with_push_back() {
	str_auto str = str_create();
	if (!str) return 1;
	ulong expected_capacity = str_capacity(str);
	while (str_capacity(str) < 10000000) {
		if (str_push_back(str, 'c')) return 2;
		if (str_len(str) + 1 > expected_capacity) expected_capacity *= 2;
		if (str_capacity(str) != expected_capacity) return 3;
	}
	return 0;
}

int test_push_front() {
	str_auto str = str_create();
	if (!str) return 1;
	if (str_append(str, "ello, World!") == NULL) return 1;
	if (str_push_front(str, 'H') == 1) return 2;
	if (strcmp(str_data(str), "Hello, World!") != 0) return 3;
	return 0;
}

int test_expand_with_push_front() {
	str_auto str = str_create();
	if (!str) return 1;
	ulong expected_capacity = str_capacity(str);
	while (str_capacity(str) < 10000) {
		if (str_push_front(str, 'c')) return 2;
		if (str_len(str) + 1 > expected_capacity) expected_capacity *= 2;
		if (str_capacity(str) != expected_capacity) return 3;
	}
	return 0;
}

int test_pop() {
	str_auto str = str_create();
	if (!str) return 1;
	if (str_push_back(str, 'c')) return 2;
	if (str_pop(str) != 'c') return 3;
	return 0;
}

int test_pop_overflow() {
	str_auto str = str_create();
	if (!str) return 1;
	_is_exit_called = false;
	str_pop(str);
	if (_is_exit_called != true) return 2;
	return 0;
}

int test_shrink_with_pop() {
	str_auto str = str_create();
	if (!str) return 1;
	if (str_append(str, "aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa") == NULL) return 2;
	ulong len = str_len(str);
	ulong expected_capacity = str_capacity(str);
	for (ulong i = 0; i < len; i++) {
		__attribute__((unused)) char c = str_pop(str);
		if (str_len(str) + 1 < expected_capacity / 2 && expected_capacity / 2 >= 16)
			expected_capacity /= 2;
		if (str_capacity(str) != expected_capacity) return 1;
	}
	return 0;
}

int test_str_cmp() {
	str_auto str = str_create();
	if (!str) return 1;
	if (str_append(str, "Hello, World!") == NULL) return 1;
	if (str_cmp(str, "Hello, World!") != true) return 2;
	if (str_cmp(str, "carrot") != false) return 3;
	str_t *str_null = NULL;
	_is_exit_called = false;
	str_cmp(str_null, "anything");
	if (_is_exit_called != true) return 4;
	return 0;
}

int test_replace() {
	str_auto str = str_create();
	if (!str) return 1;
	if (str_append(str, "Hello, World!") == NULL) return 1;
	if (strcmp(str_replace(str, "Hello", "Yo"), "Yo, World!") != 0) return 2;
	for (int i = 0; i < 10; i++) {
		if (str_append(str, "Hello") == NULL) return 3;
	}
	const char *expected = "Yo, World!yoyoyoyoyoyoyoyoyoyo";
	if (strcmp(str_replace(str, "Hello", "yo"), expected) != 0) return 4;
	return 0;
}

int test_expand_with_replace() {
	str_auto str = str_create();
	if (!str) return 1;
	if (str_append(str, "a a a a a a a a a a") == NULL) return 2;
	const char *expected = "aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa";
	if (strcmp(str_replace(str, "a", "aaaaaaaaaaaaaaaaaaaa"), expected) != 0) return 3;
	return 0;
}

int test_shrink_with_replace() {
	str_auto str = str_create();
	if (!str) return 1;
	if (str_append(str, "aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaa") == NULL) return 2;
	const char *expected = "a a a a a a a a a a";
	if (strcmp(str_replace(str, "aaaaaaaaaaaaaaaaaaaa", "a"), expected) != 0) return 3;
	if (str_capacity(str) != 32) return 4;
	return 0;
}

int test_str_has() {
	str_auto str = str_create();
	if (!str) return 1;
	if (str_append(str, "Hello, World!") == NULL) return 2;
	if (str_has(str, "Hello") != true) return 3;
	if (str_has(str, "Yellow") != false) return 4;
	return 0;
}

int main(void) {
	ASSERT(test_new() == 0);
	ASSERT(test_append() == 0);
	ASSERT(test_data() == 0);
	ASSERT(test_len() == 0);
	ASSERT(test_capacity() == 0);
	ASSERT(test_expand_with_append() == 0);
	ASSERT(test_push_back() == 0);
	ASSERT(test_push_front() == 0);
	ASSERT(test_expand_with_push_back() == 0);
	ASSERT(test_expand_with_push_front() == 0);
	ASSERT(test_str_cmp() == 0);
	ASSERT(test_replace() == 0);
	ASSERT(test_expand_with_replace() == 0);
	ASSERT(test_shrink_with_replace() == 0);
	ASSERT(test_str_has() == 0);
	ASSERT(test_pop() == 0);
	ASSERT(test_pop_overflow() == 0);
	ASSERT(test_shrink_with_pop() == 0);

	print_results();
	return 0;
}
