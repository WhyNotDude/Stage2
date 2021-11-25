#include "../inc/pathfinder.h"

void sort_arr(t_arr_p* array, char ** names)
{
    for (int i = 0; i < array->size; i++)
    {
        for (int j = i+1; j < array->size; j++)
        {int iter;
            for (iter=0;true;iter++)
            {
            if(mx_strcmp(array->arr[i]->islands[iter], 
            array->arr[j]->islands[iter])!= 0)
                {
                break;
                }
            }
            int frst = check_index(names,array->arr[i]->islands[iter]);
            int scnd = check_index(names,array->arr[j]->islands[iter]);
            if (frst > scnd)
            {
                t_path* var = array->arr[i];
                array->arr[i] = array->arr[j];
                array->arr[j] = var;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        mx_printerr("usage: ./pathfinder [filename]\n");
        return 1;
    }
    validator(argv[1]);
    int isl_count;

    t_island** islands = parse(argv[1], &isl_count);

    char **names = (char **) malloc (isl_count * sizeof(char*));
    
    for (int i = 0; islands[i] != NULL; i++)
    {
        names[i] = mx_strdup(islands[i]->isl_name);
    }

    for(int y = 0; y < isl_count - 1; y++)
    {
        for(int x = y+1; x < isl_count; x++)
        {
            t_path* path = path_init(islands[y]->isl_name);
            t_arr_p* paths = find_path(islands[y], islands[x], path, isl_count);
            sort_arr(paths, names);
            for(int i = 0; i < paths->size; i++)
            {
                print(paths->arr[i]);
            }
            clean_arr_p(paths);
            free(paths);
            path_del(&path);
        }
    }

    for (int i = 0; islands[i] != NULL; i++)
    {
        free(names[i]);
    }
    free(names);
    names = NULL;

    for (int i = 0; islands[i] != NULL; i++)
    {
        del_island(&islands[i]);
    }
    free(islands);
    islands = (t_island**) NULL;
    return 0;
}

