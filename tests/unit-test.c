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
	const char *expected_content = "Hello, World! This is a kickass library.";
	if (str_append(str, expected_content) == NULL) return 1;
	if (strcmp(str_data(str), expected_content) != 0)
		return 2;
	return 0;
	
}

int test_len() {
	str_auto str = str_create();
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
	if (str_capacity(str) != 16) return 1;
	return 0;
}

int test_expand_with_append() {
	str_auto str = str_create();
	ulong expected_capacity = str_capacity(str);
	while (str_capacity(str) < 10000000) {
		str_append(str, "c");
		if (str_len(str) + 1 > expected_capacity) expected_capacity *= 2;
		if (str_capacity(str) != expected_capacity) return 1;
	}
	return 0;
}



int main(void) {
	ASSERT(test_new() == 0);
	ASSERT(test_append() == 0);
	ASSERT(test_data() == 0);
	ASSERT(test_len() == 0);
	ASSERT(test_capacity() == 0);
	ASSERT(test_expand_with_append() == 0);

	print_results();
	return 0;
}
