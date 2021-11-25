#pragma once


typedef struct s_island t_island;


typedef struct s_bridge
{
    int length;
    t_island* island_1;
    t_island* island_2;
}t_bridge;

struct s_island
{
    int brid_count;
    t_bridge** bridges;
    char* isl_name;
};

typedef struct s_path
{
    char** islands;
    int isl_count;
    int *comp;
    int size;
} t_path;

typedef struct s_arr_p 
{
    t_path** arr;
    int size;
}
t_arr_p;
