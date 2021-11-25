#pragma once

#include "pathfinder.h"

#define USAGE_ERR "usage: ./pathfinder [filename]\n"

#define IN_FILE "[filename]"
#define ERR_LINE "[line_number]"

#define FILE_NOT_EXIST_ERR "error: file [filename] does not exist\n"
#define FILE_EMPTY_ERR "error: file [filename] is empty\n"

#define DATA_LINE_ERR "error: line [line_number] is not valid\n"
#define DATA_INVALID_ISLANDS_COUNT_ERR "error: invalid number of islands\n"
#define DATA_DUPLICATE_BRIDGES_ERR "error: duplicate bridges\n"
#define DATA_TOO_BIG_BRIDGES_LEN_ERR "error: sum of bridges lengths is too big\n"

void mx_throw_line_err(size_t index);

void validator(char* filename);

void frst_line_check(char* file);

void all_other_line_check(char * file);
