#pragma once
#include "../inc/error.h"
#include "../libmx/inc/libmx.h"

#define string_t char*

#define SH_NAME "u$h> "

typedef struct s_flags
{
    int i; //env
    int P; //env
    int u; //env
    int p; //cd pwd
    int s; //cd which
    int minus; //cd
    int L; //pwd
    int a; //which
    int n; //echo
    int e; //echo
    int E; //echo
} t_flags;

void print_sh();
