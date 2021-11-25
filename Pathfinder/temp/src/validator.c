#include "../inc/error.h"

void mx_throw_line_err(size_t index) {
    char* error = mx_replace_substr(DATA_LINE_ERR, ERR_LINE, mx_itoa(index));
    mx_printerr(error);
    mx_strdel(&error);
    exit(0);
}

void validator(char* filename)
{
    char* error = NULL;
    char* file = mx_file_to_str(filename);

    if(file == NULL)
    {
        error = mx_replace_substr(FILE_NOT_EXIST_ERR, IN_FILE, filename);
    }
    else
    if(mx_strcmp(file, "") == 0)
    {
        error = mx_replace_substr(FILE_EMPTY_ERR,IN_FILE,filename);
    }

    if(error != NULL)
    {
    mx_printerr(error);
    mx_strdel(&error);
    exit (0);
    }

    frst_line_check(file);
}

void frst_line_check(char* file)
{
    int i = 0;
    if(file[0] == '\n')
    {
        mx_throw_line_err(1);
    }
    while(file[i] != '\n')
    {
        if(mx_isdigit(file[i]) != true)
        {
            mx_throw_line_err(1);
        }
        i++;
    }
    all_other_line_check(file);
}

void all_other_line_check(char * file)
{
    int line = 1;
    int symbol = 1;
    while (file[symbol-1] != '\n') symbol++;
    line++;

bool is_coma_ok;
bool is_minus_ok;
bool is_digit_ok;

int index = mx_strlen(file);

    while(symbol < index)
    {
        char b1[256] = {0};
        char b2[256] = {0};
        int iter = 0;
        is_digit_ok = is_minus_ok = is_coma_ok = false;
        while(mx_isalpha(file[symbol]) == true || file[symbol] == '-')
        {
            if(file[symbol] == '-')
            {
                is_minus_ok = true;
                symbol++;
                break;
            }
            b1[iter] = file[symbol];
            iter++;
            symbol++;
        }
        if(is_minus_ok == false)
        {
            mx_throw_line_err(line);
        }
        iter = 0;
        while(mx_isalpha(file[symbol]) == true || file[symbol] == ',')
        {
            if(file[symbol] == ',')
            {
                is_coma_ok = true;
                symbol++;
                break;
            }
            b2[iter] = file[symbol];
            iter++;
            symbol++;
        }
        if(is_coma_ok == false || mx_strcmp(b1,b2) == 0)
        {
            mx_throw_line_err(line);
        }
        while(mx_isdigit(file[symbol]) == true)
        {   
            is_digit_ok = true;
            if(file[symbol+1] == '\n')
            {
                line++;
                symbol++;
                break;
            }else if (file[symbol+1] == '\0')
            {
                symbol++;
                break;
            }
            symbol++;
        }
        if (is_digit_ok == false || (file[symbol] == '\n' && file[symbol+1] == '\n'))
        {
            mx_throw_line_err(line);
        }
        symbol++;
    }
    free(file);
}

