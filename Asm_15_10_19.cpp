#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>
#include <sys\stat.h>
#include <assert.h>

#include "enum.h"
#include "OneginLib.h"


//=============================================================================

#define DEF_CMD(name, num, code)                                                           \
    else if (strncmp (strings_arr[line - 1].str, #name, strlen (#name)) == 0)              \
    {                                                                                      \
        res [pos++] = CMD_##name;                                                          \
        if (num == 1 && !Case_Push (strings_arr[line - 1].len, strlen (#name), &pos, res,  \
                                    strings_arr[line - 1].str + strlen (#name) + 1))       \
        {                                                                                  \
            printf ("ERROR!");                                                             \
            break;                                                                         \
        }                                                                                  \
    }

//=============================================================================

char *Make_Char_From_Str (char* str);

bool Case_Push (const int len_of_string, const int len_of_name, int* pos, char *res, char *line);

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

    int line = 1;
    int pos = 0;

    while (line < n_lines)
    {
        if (false);
        #include "Commands.h"
        else
            printf ("ERROR in line [%d]\n", line);

        line++;
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

char *Make_Char_From_Str (char* str)
{
    int num = atoi (str);

    char res[5] = {'0', '0', '0', '0', '0'};

    if (num > 0)
        res[0] = '1';   // > 0
    else if (num < 0)
        res[0] = '2';   // < 0

    for (int i = 1; i < 5; i++)
    {
        res[i] = num % 256;

        num /= 256;
    }

    return res;
}

//=============================================================================

bool Case_Push (const int len_of_string, const int len_of_name, int* pos, char *res, char *line)
{
    if (len_of_string < len_of_name + 1)
    {
        return false;
    }

    char *helper = Make_Char_From_Str (line);

    for (int i = 0; i < 5; i++)
    {
        res[(*pos)++] = helper[i];
    }

    return true;
}
