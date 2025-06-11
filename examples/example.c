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

	/* Appends new data at the end of 'str'.
	 * Returns a pointer to the data or NULL on failure. */
	if (str_append(str, "Some text") == NULL) return 1;

	/* Returns a pointer to the data stored in 'str' or NULL on failure.
	 * This is a reference and not a copy, changes made to 
	 * 'str' will be reflected through this. */
	const char *data = str_data(str);
	if (!data) return 1;

	/* Returns the length of 'str'.
	 * Exits the program with status code '1' if 'str' is NULL. */
	printf("Length: %lu\n", str_len(str));

	/* Returns the capacity of 'str'.
	 * Exits the program with status code '1' if 'str' is NULL. */
	printf("Capacity: %lu\n", str_capacity(str));

	/* Appends a single character at the end of 'str'.
	 * Returns '0' on success and '1' on failure. */
	if (str_push(str, 'c')) return 1;

	/* Removes and returns the last character of 'str'.
	 * Exits the program with status code '1' on failure. */
	printf("Last character: %c\n", str_pop(str));

	/* Returns 'true' if 'str' and 'src' are the same, otherwise returns 'false'.
	 * Exits the program with status code '1' on failure. */
	bool str_cmp(const str_t *str, const char *src);
	if (str_cmp(str, "Some text")) {
		printf("String is \"Some text\"\n");
	} else {
		printf("String is NOT \"Some text\"\n");
	}

	/* Replaces all occurrences of 'text' to the desired value in 'str'.
	 * Returns a pointer to the data or NULL on failure. */
	const char *data2 = str_replace(str, "text", "awesome text");
	if (!data2) return 1;

	/* Returns 'true' if 'str' has 'Some' in it, otherwise returns 'false'.
	 * Exits the program with status code '1' if 'str' is NULL */
	if (str_has(str, "Some")) {
		printf("String has \"Some\"\n");
	} else {
		printf("String does NOT have \"Some\"\n");
	}

	// Don't forget to free the allocated memory.
	// This is not necessary if you declared the variable with str_auto
	str_destroy(&str);
}
