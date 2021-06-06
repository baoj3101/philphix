#ifndef CHAR_VECTOR_H
#define CHAR_VECTOR_H

#include <stdint.h>
#include <stdlib.h>
// #include <string.h>

typedef struct char_vector char_vector_t;

extern char_vector_t *char_vector_constructor(void);

extern void char_vector_destructor(char_vector_t *char_vector);

extern void char_vector_add(char_vector_t *char_vector, char entry);

extern char char_vector_get(char_vector_t *char_vector, uint32_t index);

extern char *char_vector_get_raw_array(char_vector_t *char_vector);

#endif