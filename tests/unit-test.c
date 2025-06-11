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
	str_append(str, expected_content);
	if (strcmp(str_data(str), expected_content) != 0)
		return 1;
	return 0;
	
}

int main(void) {
	ASSERT(test_new() == 0);
	ASSERT(test_append() == 0);
	ASSERT(test_data() == 0);

	print_results();
	return 0;
}
