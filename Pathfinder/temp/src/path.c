#include "../inc/pathfinder.h"

t_path * path_init(char* name)
{
    t_path* answer = (t_path*) malloc(sizeof(t_path));
    answer->size = 0;
    answer->islands = (char**) malloc(sizeof(char*));
    answer->islands[0] = mx_strdup(name);
    answer->isl_count = 0;
    answer->comp = (int*) malloc (sizeof(int) * 0);
    return answer;
}

void add_p_point(t_path* path, char * name, int len)
{
    path->comp = (int*)mx_realloc(path->comp, (path->isl_count + 1) * sizeof(int));
    path->islands = (char**)mx_realloc(path->islands, (path->isl_count + 2) * sizeof(char*));
    path->comp[path->isl_count] = len;
    path->islands[path->isl_count + 1] = mx_strdup(name);
    path->isl_count++;
    path->size += len;
}

void path_del(t_path ** path)
{
    for (int i = 0; i <= (*path)->isl_count; i++)
    {
        mx_strdel(&(*path)->islands[i]);
    }
    free((*path)->islands);
    free((*path)->comp);
    free(*path);
}

void clean_arr_p (t_arr_p* arr)
{
    for (int i = 0; i < arr->size; i++)
    {
        path_del(&(arr->arr[i]));
    }
    free(arr->arr);
    arr->arr = NULL;
    arr->size = 0;
}

void add_path(t_arr_p* arr, t_path* path)
{
    arr->arr = (t_path**) mx_realloc (arr->arr, (arr->size+1) * sizeof(t_path*));
    arr->arr[arr->size] = path;
    arr->size ++;
}

t_arr_p* init_arr_p ()
{
    t_arr_p * answer = (t_arr_p*) malloc (sizeof(t_arr_p));
    answer->size = 0;
    answer->arr = (t_path**)malloc(sizeof(t_path*)*0);
    return answer;
}

bool is_here(char ** arr, int size, char * target)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == target)
        {
            return true;
        }
    }
    return false;
}

t_island * neighb_is(t_island * home, t_bridge * brid)
{
    if(mx_strcmp(home->isl_name, brid->island_1->isl_name) == 0)
    return brid->island_2;
    return brid->island_1;
}

int check_index(char **names, char* name)
{
    int i;
    for (i = 0; names[i]!= NULL; i++)
    {
        if (mx_strcmp(names[i], name) == 0)
        break;
    }
    return i;
}

t_bridge *get_act_bridge(int *index, t_island* isl, char **names)
{
    for (int i = *index; i < isl->brid_count; i++)
    {
        int frst = check_index(names, neighb_is(isl,isl->bridges[i])->isl_name);
        for (int j = i; j < isl->brid_count; j++)
        {
            int scnd = check_index(names, neighb_is(isl,isl->bridges[j])->isl_name);
            if (frst < scnd)
            {
                *index = j;
                return isl->bridges[j];
            }
        }
    }
    return isl->bridges[*index];
}

t_path* dupl_path(t_path* input)
{
    if(input == NULL) return NULL;
    t_path* answer = (t_path*) malloc (sizeof(t_path));
    answer->islands = (char **) malloc (sizeof(char*) * (input->isl_count + 1));
    answer->comp = (int*) malloc (sizeof(int*) * input->isl_count);
    answer->isl_count = input->isl_count;
    answer->size = input->size;
    for(int i = 0; i < answer->isl_count; i++)
    {
        answer->comp[i] = input->comp[i];
    }
    for(int i = 0; i <= answer->isl_count; i++)
    {
        if(input->islands[i] != NULL)
        answer->islands[i] = mx_strdup(input->islands[i]);
    }
    return answer;
}

t_arr_p* find_path(t_island* start, t_island* finish, t_path* first, int isl_count) 
{
    
    long min_len = 2147483647;
    t_arr_p* path_arr = init_arr_p();
    for (int i = 0; i < start->brid_count; i++) 
    {   
        t_bridge* var = start->bridges[i];

        if (is_here(first->islands, first->isl_count+1, neighb_is(start, var)->isl_name))
        {
            continue;
        }
        int len = first->size + var->length;
        if (len > min_len) continue;

        t_path* cur_path;

        if (mx_strcmp(neighb_is(start,var)->isl_name, finish->isl_name) == 0) 
        {
            if (len < min_len) 
            {
                min_len = len;
                clean_arr_p(path_arr);
            }
            if (len == min_len) 
            {
                cur_path = dupl_path(first);
                add_p_point(cur_path, neighb_is(start,var)->isl_name, var->length);
                add_path(path_arr, cur_path);
            }
            cur_path = NULL;
            continue;
        }

        if (first->isl_count >= isl_count) continue;
        cur_path = dupl_path(first);
        add_p_point(cur_path, neighb_is(start,var)->isl_name, var->length);
        t_arr_p* deep_path_arr = find_path(neighb_is(start,var), finish, cur_path, isl_count);
        for (int j = 0; j < deep_path_arr->size; j++) 
        {
            t_path* p = deep_path_arr->arr[j];
            if (p->size < min_len) 
            {
                min_len = p->size;
                clean_arr_p(path_arr);
            }
            if (p->size == min_len)
                add_path(path_arr, p);
            else
                path_del(&p);
        }
        free(deep_path_arr->arr);
        free(deep_path_arr);
        path_del(&cur_path);
    }
    return path_arr;
}

void print(t_path *path) {
    mx_printstr("========================================\nPath: ");
    mx_printstr(path->islands[0]);
    mx_printstr(" -> ");
    mx_printstr(path->islands[path->isl_count]);
    mx_printstr("\nRoute: ");
    for (int i = 0; i <= path->isl_count; i++) 
    {
        if (i) mx_printstr(" -> ");
        mx_printstr(path->islands[i]);
    }
    mx_printstr("\nDistance: ");
    if (path->isl_count > 1)
    {
        for (int i = 0; i < path->isl_count; i++) 
        {
            if (i) mx_printstr(" + ");
            mx_printint(path->comp[i]);
            if (i == path->isl_count - 1) mx_printstr(" = ");
        }
    }
    mx_printint(path->size);
    mx_printstr("\n========================================\n");
}


