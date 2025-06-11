#include <dynamic-string.h>
#include <stdio.h>

int main(void) {
	// Create a new instance
	// This has to be explicitly freed with str_destroy()!
	str_t *str = str_create();

	{
		// To free the allocated memory automatically when the
		// object goes out of scope, declare the variable with str_auto
		str_auto str = str_create();
	}

	// Always double check if the allocation was successful
	if (!str) return 1;

	// Append new data at the end of 'str'
	// Returns the new data or NULL on failure
	if (!str_append(str, "New data")) return 1;

	// Get a pointer to the data stored. Returns NULL on failure.
	const char *data = str_data(str);
	if (!data) return 1;

	// Get the length of the string. Exits the program with status code '1'
	// on failure.
	printf("Length: %lu\n", str_len(str));

	// Get the capacity of the object. Exits the program with status code '1'
	// on failure.
	printf("Capacity: %lu\n", str_capacity(str));

	// Append a single character at the end of 'str'
	// returns '0' on success and '1' on failure.
	if (str_push(str, '!')) return 1;

	// Compares 'str' with

	// Don't forget to free the allocated memory.
	// This is not necessary if you declared the variable with str_auto
	str_destroy(&str);
}
