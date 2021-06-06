#include "char-vector.h"
#include <stdio.h>

static void _char_vector_expand(char_vector_t *char_vector);
static void _free(void *ptr);

struct char_vector {
	uint32_t n;
	uint32_t m;
	char *data;
};

char_vector_t *char_vector_constructor(void) {

	char_vector_t *char_vector = malloc(sizeof(*char_vector));
	if (!char_vector) return NULL;

	char_vector->data = NULL;
	char_vector->n    = char_vector->m = 0;

	return char_vector;
}

void char_vector_destructor(char_vector_t *char_vector) {
	if (!char_vector) return;

	if (char_vector->m)
		_free(char_vector->data);

	_free(char_vector);
}

void char_vector_add(char_vector_t *char_vector, char entry) {
	if (char_vector->n >= char_vector->m)
		_char_vector_expand(char_vector);

	char_vector->data[char_vector->n++] = entry;
}

char char_vector_get(char_vector_t *char_vector, uint32_t index) {
	if (index > char_vector->n)
		exit(EXIT_FAILURE);

	return char_vector->data[index];
}

char *char_vector_get_raw_array(char_vector_t *char_vector) {
	return char_vector->data;
}

static void _char_vector_expand(char_vector_t *char_vector) {
	if (!char_vector->m) {
		char_vector->m = 1;
		char_vector->data = malloc(char_vector->m * sizeof(char));
		if (!char_vector->data) exit(EXIT_FAILURE);
		return;
	}

	char_vector->m <<= 1;
	char_vector->data = realloc(char_vector->data, sizeof(char) * char_vector->m);
	if (!char_vector->data) exit(EXIT_FAILURE);
}

static void _free(void *ptr) {
	free(ptr);
	ptr = NULL;
}