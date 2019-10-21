// Commands.h

DEF_CMD(PUSH, 1,
                {
                counter++;

                int what_reg = -1;

                if ('a' <= buf[counter] && buf[counter] <= 'z')
                {
                    what_reg = Check_If_Reg (&buf[counter]);

                    if (what_reg == -1)
                    {
                        printf ("ERROR in DEF_CMD Push in Commands.h\n");
                    }
                    else
                    {
                        Stack_Push (stk, reg[what_reg]);
                    }

                    counter += 2;

                    break;
                }

                int sum = * (int*) (buf + counter);
                counter += sizeof (int);

                Stack_Push (stk, sum);

                break;
                })

DEF_CMD(POP, 2,
                {
                int what_reg = -1;

                if ('a' <= buf[counter + 1] && buf[counter + 1] <= 'z')
                {
                    what_reg = Check_If_Reg (&buf[counter + 1]);

                    if (what_reg == -1)
                    {
                        printf ("ERROR in DEF_CMD Pop in Commands.h\n");
                    }
                    else
                    {
                        Stack_Pop (stk, &reg[what_reg]);
                    }

                    counter += 3;

                    break;
                }

                Stack_Pop (stk, &helper_1);
                counter++;
                break;
                })

DEF_CMD(ADD, 3,
                {
                Stack_Pop (stk, &helper_1);
                Stack_Pop (stk, &helper_2);

                Stack_Push (stk, (helper_1 + helper_2));
                counter++;
                break;
                })

DEF_CMD(SUB, 4,
                {
                Stack_Pop (stk, &helper_1);
                Stack_Pop (stk, &helper_2);

                Stack_Push (stk, (helper_1 - helper_2));
                counter++;
                break;
                })

DEF_CMD(MUL, 5,
                {
                Stack_Pop (stk, &helper_1);
                Stack_Pop (stk, &helper_2);

                Stack_Push (stk, (helper_1 * helper_2));
                counter++;
                break;
                })

DEF_CMD(DIV, 6,
                {
                Stack_Pop (stk, &helper_1);
                Stack_Pop (stk, &helper_2);

                Stack_Push (stk, (helper_1 / helper_2));
                counter++;
                break;
                })

DEF_CMD(SQRT, 7,
                {
                (Stack_Pop (stk, &helper_1));

                Stack_Push (stk, sqrt (helper_1));
                counter++;
                break;
                })

DEF_CMD(JMP, 8,
                {
                counter = buf[counter + 1];
                break;
                })

DEF_CMD(END, 0,
                {
                printf ("END?\n");
                counter = sz_file + 1;
                })
