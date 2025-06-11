#include "dynamic-string.h"
#include <stdio.h>
#include <sys/types.h>

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

int main(void) {
	// test create_str()
	{
		_is_exit_called = false;
		str_t *str = str_create();
		ASSERT(_is_exit_called == true);
		ASSERT(str != NULL);
	}

	// test str_destroy()
	{
		str_t *str = str_create();
		_is_str_destroyed = false;
		str_destroy(&str);
		ASSERT(_is_str_destroyed == true);
	}

	// test str_auto
	{
		str_auto str = str_create();
		_is_str_destroyed = false;
	}
	ASSERT(_is_str_destroyed == true);

	print_results();
	return 0;
}
