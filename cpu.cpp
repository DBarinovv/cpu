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

int main ()
{
    char *name_of_fin = "output.txt";
    int sz_file = Find_Size_Of_File (name_of_fin);

    FILE* fin = fopen (name_of_fin, "r");

    char *buf = (char *) calloc (sz_file + 1, sizeof(char));

    fread (buf, sizeof (char), sz_file + 1, fin);


    elem_t reg[4] = {'\0', '\0', '\0', '\0'};

    stack_t* stk = nullptr;
    STACK_CONSTRUCTOR(stk)


    int counter  = 0;
    int helper_1 = 0;
    int helper_2 = 0;

    #define DEF_CMD(name, num, code, arg)    \
        case CMD_##name:                     \
            code

    int i = 0;

    while (counter <= sz_file && ++i < 50)
    {
        switch (buf[counter])
        {
        #include "Commands.h"
        default:
            break;
        }

        Dump (stk, 100, i, "Prosto");
        getchar();
    }

    Dump (stk, 100, 5, "Prosto");

    #undef DEF_CMD

    fclose (fin);

    return 0;
}
