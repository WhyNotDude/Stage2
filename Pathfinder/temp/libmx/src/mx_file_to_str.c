#include "../inc/libmx.h"

char *mx_file_to_str(const char *filename) {
    if (filename == NULL) {
        return NULL;
    }

    int file = open(filename, O_RDONLY);
    if (file < 0) {
        return NULL;
    }

    char buffer;
    int length = 0; 

    while (read(file, &buffer, 1)) {
        length++;
    }

    if (close(file) < 0) {
        return NULL;
    }

    if (length == 0) {
        return mx_strdup("");
    }

    file = open(filename, O_RDONLY);
    if (file < 0) {
        return NULL;
    }
    
    char *arr = mx_strnew(length);

    read(file, arr, length);

    if (close(file) < 0) {
        return NULL;
    }
    return arr;
}

