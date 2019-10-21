#include <sys\stat.h>
#include "TXLib.h"

#include "OneginLib.h"
#include "Stack.h"
#include "enum.h"
#include "Help_functions.h"

#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

//=============================================================================

bool Un_Fold_If_Have_Arg (FILE *fout, char *buf, int *pos);

//=============================================================================

int main ()
{
    char *name_of_fin  = "output.txt";
    char *name_of_fout = "output_test.txt";

    int sz_file = Find_Size_Of_File (name_of_fin);

    FILE* fin  = fopen (name_of_fin,  "r");
    FILE* fout = fopen (name_of_fout, "w");

    char *buf = (char *) calloc (sz_file + 1, sizeof (char));

    fread (buf, sizeof (char), sz_file + 1, fin);


    int pos = 0;

    #define DEF_CMD(name, num, code, arg)                                                      \
        case CMD_##name:                                                                       \
            fprintf (fout, "%s", #name);                                                       \
            if (arg == 1)                                                                      \
            {                                                                                  \
                Un_Fold_If_Have_Arg (fout, buf, &pos);                                         \
            }                                                                                  \
                                                                                               \
            fprintf (fout, "\n");                                                              \
            break;

    while (pos < sz_file)
    {
        switch (buf[pos])
        {
        #include "Commands.h"
        default:
            break;
        }

        pos++;
    }

    #undef DEF_CMD

    return 0;
}

//=============================================================================

bool Un_Fold_If_Have_Arg (FILE *fout, char *buf, int *pos)
{
    int sum = 0;

    (*pos)++;

    int if_reg = Check_If_Reg (buf + *pos);

    if (if_reg != -1)
    {
        fprintf (fout, " %c", buf[(*pos)++]);
        fprintf (fout, "%c",  buf[(*pos)]);
        return true;
    }

    sum = *(int*) (buf + *pos);
    *pos += sizeof (int) - 1;

    fprintf (fout, " %d", sum);

    return true;
}
