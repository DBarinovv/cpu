#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>
#include <sys\stat.h>
#include <assert.h>

#include "enum.h"
#include "OneginLib.h"
#include "Help_functions.h"

//=============================================================================

#define DEF_CMD(name, num, code, arg)                                                      \
    else if (strncmp (strings_arr[line - 1].str, #name, strlen (#name)) == 0)              \
    {                                                                                      \
        res[pos++] = CMD_##name;                                                           \
        if (arg == 1)                                                                      \
        {                                                                                  \
            Case_Have_Arg (strings_arr[line - 1].len, &pos, res,                           \
                                strings_arr[line - 1].str + strlen (#name) + 1, labels);   \
        }                                                                                  \
    }

//=============================================================================

const int C_cnt_of_labels = 10;

//=============================================================================

bool Case_Have_Arg (const int len_of_string, int* pos, char *res, char *line, char *labels);

//=============================================================================

int main ()
{
    char *name_of_fin  = "input.txt";
    char *name_of_fout = "output.txt";
    char **strings_copy = nullptr;

    struct file_t text = Read_File_And_Make_Arrays (name_of_fin, name_of_fout);

    struct string_t *strings_arr = text.strings;
    strings_copy = text.copies;  assert (strings_copy);
    int n_lines = text.n_Lines;  assert (n_lines >= 1);
    int sz_file = text.sz_File;  assert (sz_file >= 0);
    FILE *file_out = text.fout;  assert (file_out);

    char *res = (char *) calloc (sz_file + 1, sizeof (char));

    char labels[C_cnt_of_labels];

    for (int i = 0; i < C_cnt_of_labels; i++)
        labels[i] = -1;

    int line =  1;
    int pos  =  0;
    int mark = -1;

    for (int i = 0; i < 2; i++)       // 2 pass
    {
        line =  1;
        pos  =  0;
        mark = -1;

        while (line < n_lines)
        {
            if (false);
            #include "Commands.h"
            else if (strings_arr[line - 1].str[0] == '$')
            {
                mark = atoi (strings_arr[line - 1].str + 1);
                labels[mark] = pos;
            }
            else
                printf ("ERROR in main in line [%d]\n", line);

            line++;
        }
    }

    fwrite (res, pos, sizeof (char), file_out);

    #undef DEF_CMD

    assert (strings_arr);
    assert (strings_copy);

    free (&strings_arr);
    strings_arr = nullptr;
    free (strings_copy);
    strings_copy = nullptr;

    return 0;
}

//=============================================================================

bool Case_Have_Arg (const int len_of_string, int* pos, char *res, char *line, char *labels)
{
    int if_reg = Check_If_Reg (line);

    if (if_reg != -1)
    {
        res[(*pos)++] = line[0];
        res[(*pos)++] = line[1];

        return true;
    }
    else if (line[0] == '$')
    {
        *(int*) (res + *pos) = labels[atoi (line + 1)];
        *pos += sizeof (int);

        return true;
    }


    *(int*) (res + *pos) = atoi (line);
    *pos += sizeof (int);

    return true;
}
