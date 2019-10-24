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

void Pr_Reg (elem_t *reg);

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

    stack_t* stk_for_func = nullptr;
    STACK_CONSTRUCTOR(stk_for_func)

    int counter  = 0;
    int helper_1 = 0;
    int helper_2 = 0;

    #define DEF_CMD(name, num, code, arg)    \
        case CMD_##name:                     \
            code

    int i = 0;

    while (counter <= sz_file && ++i < 500)
    {
        switch (buf[counter])
        {
        #include "Commands.h"
        default:
            break;
        }

        Dump (stk, 100, i, "Prosto");
        Pr_Reg (reg);
        getchar();
    }

//    Dump (stk, 100, 5, "Prosto");

    #undef DEF_CMD

    fclose (fin);

    return 0;
}

//=============================================================================

void Pr_Reg (elem_t *reg)
{
    printf ("[");
    CH(White)
    for (int i = 0; i < 4; i++)
    {
        printf (" %d,", reg[i]);
    }
    CH_S
    printf ("]");
}
