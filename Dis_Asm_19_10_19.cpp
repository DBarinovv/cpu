#include <sys\stat.h>
#include "TXLib.h"

#include "OneginLib.h"
#include "Stack.h"
#include "enum.h"

#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

//=============================================================================

bool Print_Int (FILE *fout, char *buf, int *pos);

//=============================================================================

int main ()
{
    char *name_of_fin  = "output.txt";
    char *name_of_fout = "output_test.txt";

    int sz_file = Find_Size_Of_File (name_of_fin);

    FILE* fin  = fopen (name_of_fin,  "r");
    FILE* fout = fopen (name_of_fout, "w");

    char *buf = (char *) calloc (sz_file + 1, sizeof(char));

    fread (buf, sizeof (char), sz_file + 1, fin);


    int pos = 0;

    #define DEF_CMD(name, num, code)                           \
        case CMD_##name:                                       \
            fprintf (fout, "%s", #name);                       \
            if (num == 1 && !Print_Int (fout, buf, &pos))      \
                printf ("ERROR, NOT INT!");                    \
                                                               \
            fprintf (fout, "\n");                              \
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

    return 0;
}

//=============================================================================

bool Print_Int (FILE *fout, char *buf, int *pos)
{
    int sign = 0;
    int sum  = 0;

    (*pos)++;

    if ((int) buf[*pos] == '1')         // > 0
        sign = 1;
    else if ((int) buf[*pos] == '2')    // < 0
        sign = -1;

    (*pos)++;

    for (int i = 0; i < 4; i++)
    {                                                               // buf || sign
        if ((int) buf[*pos] > 0 && sign > 0)                     //  >      <
        {
            sum += pow (256, i) * (int) buf[*pos];
        }
        else if ((int) buf[*pos] > 0 && sign < 0)                //  >      >
        {
            sum += pow (256, i) * ((int) buf[*pos] - 256);
        }
        else if ((int) buf[*pos] < 0 && sign < 0)                //  <      <
        {
            sum += pow (256, i) * (int) buf[*pos];
        }
        else if ((int) buf[*pos] < 0 && sign > 0)                //  <      >
        {
            sum += pow (256, i) * ((int) buf[*pos] + 256);
        }
        else
        {
            sum += pow (256, i) * (int) buf[*pos];
        }

        (*pos)++;
    }

    (*pos)--;

    fprintf (fout, " %d", sum);

    return true;
}
