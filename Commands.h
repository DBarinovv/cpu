// Commands.h

DEF_CMD(PUSH, 1,
                {
                int sum  = 0;
                int sign = 0;

                counter++;

                if ((int) buf[counter] == '1')         // > 0
                    sign = 1;
                else if ((int) buf[counter] == '2')    // < 0
                    sign = -1;

                counter++;

                for (int i = 0; i < 4; i++)
                {                                                               // buf || sign
                    if ((int) buf[counter] > 0 && sign > 0)                     //  >      <
                    {
                        sum += pow (256, i) * (int) buf[counter];
                    }
                    else if ((int) buf[counter] > 0 && sign < 0)                //  >      >
                    {
                        sum += pow (256, i) * ((int) buf[counter] - 256);
                    }
                    else if ((int) buf[counter] < 0 && sign < 0)                //  <      <
                    {
                        sum += pow (256, i) * (int) buf[counter];
                    }
                    else if ((int) buf[counter] < 0 && sign > 0)                //  <      >
                    {
                        sum += pow (256, i) * ((int) buf[counter] + 256);
                    }
                    else
                    {
                        sum += pow (256, i) * (int) buf[counter];
                    }

                    counter++;
                }

                Stack_Push (stk, sum);

                break;
                })

DEF_CMD(POP, 2,
                {
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

DEF_CMD(END, 0,
                {
                printf ("END?\n");
                counter = sz_file + 1;
                })
