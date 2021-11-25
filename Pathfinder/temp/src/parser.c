#include "../inc/pathfinder.h"

t_island* find_island(t_island** iss, const char * name) 
{
    for (int i = 0; iss[i]; i++)
        if (!mx_strcmp(iss[i]->isl_name, name)) return iss[i];
    return NULL;
}

t_island* create_isl (char *name)
{
    t_island* answer = (t_island*)malloc(sizeof(t_island));
    answer->bridges = (t_bridge**) malloc (sizeof(t_bridge*));
    answer->brid_count = 0;
    answer->isl_name = mx_strdup(name);
    return answer;
}

void del_island(t_island** island) 
{
    mx_strdel(&(*island)->isl_name);
    for(int i = 0; i < (*island)->brid_count; i++)
    {
        if(malloc_size((*island)->bridges[i])!= 0)
        {
        free((*island)->bridges[i]);
        (*island)->bridges[i]= NULL;
        }
    }
    free((*island)->bridges);
    free(*island);
}

t_bridge* create_brid(int len, t_island* a, t_island* b)
{
    t_bridge* brid = (t_bridge*) malloc(sizeof(t_bridge));
    brid->length = len;
    brid->island_1 = a;
    brid->island_2 = b;
    return brid;
}


void add_bridge(t_island* is1, t_island* is2, t_bridge *br)
{
    is1->brid_count++;
    is1->bridges = (t_bridge**) mx_realloc(is1->bridges, is1->brid_count * sizeof(t_bridge*));
    is1->bridges[is1->brid_count-1] = br;

    is2->brid_count++;
    is2->bridges = (t_bridge**) mx_realloc(is2->bridges, is2->brid_count * sizeof(t_bridge*));
    is2->bridges[is2->brid_count-1] = br;
}

void connect_isl(t_island *is1, int len, t_island *is2)
{
    for (int i = 0; i < is1->brid_count; i ++)
    {
        if(mx_strcmp(is2->isl_name, neighb_is(is1,is1->bridges[i])->isl_name) == 0)
            {
            mx_printerr(DATA_DUPLICATE_BRIDGES_ERR);
            exit (0);
            }
    }
    for (int i = 0; i < is2->brid_count; i ++)
    {
        if(mx_strcmp(is1->isl_name, neighb_is(is2,is2->bridges[i])->isl_name) == 0)
            {
            mx_printerr(DATA_DUPLICATE_BRIDGES_ERR);
            exit (0);
            }
    }
    add_bridge(is1, is2, create_brid(len, is1, is2));
}

int max_isl_count (char * str, bool *valid)
{
    int len = mx_strlen(str);
    *valid = true;
    for (int i = 0; i < len; i++)
        if (!mx_isdigit(str[i])) 
        {
            *valid = false;
            return 0;
        }
    while (*str == '0') 
    {
        str++;
        len--;
    };
    if (!len) return 0;
    int ans = *str++ - '0';
    while (*str) 
    {
        ans *= 10;
        ans += *str++ - '0';
    }
    return ans;
}

void parse_line(t_island **isl, char *line ,int max_isl, int *inc) 
{
    int len_sum = 0;
    char **args = mx_strsplit(line, ',');
    char **cur_isl_names = mx_strsplit(args[0], '-');
    
    t_island **cur_isl = (t_island **)malloc(sizeof(t_island *) * 2);

    for (int i = 0; i < 2; i++) {
        cur_isl[i] = find_island(isl, cur_isl_names[i]);

        if (cur_isl[i] == NULL) {
            if (max_isl < (*inc) + 1) 
            {
                mx_printerr(DATA_INVALID_ISLANDS_COUNT_ERR);
                exit(0);
            }
            isl[*inc] = cur_isl[i] = create_isl(cur_isl_names[i]);
            (*inc)++;
        }
    }
    
    bool is_valid_sz;
    int len = max_isl_count(args[1], &is_valid_sz);
    len_sum += len;
    if (len_sum > 2147483647)
    {
        mx_printerr(DATA_TOO_BIG_BRIDGES_LEN_ERR);
        exit(0);
    }
    connect_isl(cur_isl[0], len, cur_isl[1]);
    
    free(cur_isl);
    mx_del_strarr(&cur_isl_names);
    mx_del_strarr(&args);
}

t_island** parse (char * filename, int *counter)
{
    t_island ** islands;
    char * file = mx_file_to_str(filename);
    char **lines = mx_strsplit(file, '\n');
    int i;
    bool is_frst_ok;
    int max_island = max_isl_count(*lines, &is_frst_ok);
    if(is_frst_ok == false)
    {
        mx_throw_line_err(1);
    }

    islands = (t_island**) malloc(sizeof(t_island*) * (max_island + 1));
    for(i = 0; i < max_island+1; i ++)
    {
        islands[i] = NULL;
    }
    int isl_count = 0;
    
    for (i = 1; lines[i]!= 0; i++)
    {
        parse_line(islands, lines[i], max_island, &isl_count);
    }
    
    if(max_island != isl_count)
    {
        mx_printerr (DATA_INVALID_ISLANDS_COUNT_ERR);
        exit(0);
    }
    *counter = max_island;
    mx_del_strarr(&lines);
    free(file);
    return (islands);
}
