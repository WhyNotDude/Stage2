#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "../inc/error.h"
#include "../inc/path.h"

#include "../libmx/inc/libmx.h"

t_island** parse (char * filename, int * counter);

int max_isl_count(char * str, bool* valid);

t_path * path_init(char* name);

t_arr_p* find_path(t_island* start, t_island* finish, t_path* first, int isl_count);

void print(t_path *path);

void path_del(t_path ** path);

void clean_arr_p (t_arr_p* arr);

void del_island(t_island** island);

t_island * neighb_is(t_island * home, t_bridge * brid);

void sort_arr(t_arr_p* array, char **names);

int check_index(char **names, char* name);
