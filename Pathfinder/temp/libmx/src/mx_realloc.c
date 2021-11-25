#include "../inc/libmx.h"

void* mx_realloc(void* ptr, int size) {
    if (!ptr) return malloc(size);
    int cur_size = malloc_size(ptr);
    if (size <= cur_size) return ptr;
    void* new_ptr = malloc(size);
    mx_memcpy(new_ptr, ptr, cur_size);
    free(ptr);
    return new_ptr;
}
