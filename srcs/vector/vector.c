//
// Created by plouvel on 24/04/24.
//

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

typedef struct s_vector {
    size_t elem_size;
    size_t capacity;
    size_t size;
    void *begin;
} t_vector;

t_vector *vector_new(size_t capacity, size_t elem_size) {
    t_vector *vector = NULL;

    assert(capacity != 0);
    assert(elem_size != 0);
    if ((vector = malloc(sizeof *vector)) == NULL) {
        return (NULL);
    }
    if ((vector->begin = malloc(capacity * elem_size)) == NULL) {
        free(vector);
        return (NULL);
    }
    vector->capacity = capacity;
    vector->elem_size = elem_size;
    vector->size = 0;

    return (vector);
}

t_vector *vector_push_back(t_vector *vector, const void *elem) {
    assert(vector != NULL);
    if (vector->size == vector->capacity) {
        vector->capacity *= 2;
        if ((vector->begin = realloc(vector->begin, vector->capacity * vector->elem_size)) == NULL) {
            return (NULL);
        }
    }
    ft_memcpy((uint8_t *)vector->begin + (vector->size * vector->elem_size), elem, vector->elem_size);
    vector->size++;
    return (vector);
}

size_t vector_size(const t_vector *vector) {
    assert(vector != NULL);
    return vector->size;
}

const void *vector_data(const t_vector *vector) {
    assert(vector != NULL);
    return vector->begin;
}

void vector_sort(t_vector *vector, int (*cmp)(const void *, const void *)) {
    assert(vector != NULL);
    qsort(vector->begin, vector->size, vector->elem_size, cmp);
}

void vector_free(t_vector **vector) {
    assert(vector != NULL);
    if (*vector == NULL) {
        return;
    }
    free((*vector)->begin);
    free(*vector);
    *vector = NULL;
}
