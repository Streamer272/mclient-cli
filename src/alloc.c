#include "alloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

void *alloc(size_t size) {
    void *pointer = malloc(size);
    if (pointer == NULL) {
        perror("couldn't allocate memory");
        exit(EXIT_FAILURE);
    }
    memset(pointer, 0, size);
    return pointer;
}
