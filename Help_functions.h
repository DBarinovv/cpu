//=============================================================================
// For cpu and Asm
// Check if argument is register (ax, bx, cx, dx)
//=============================================================================

int Check_If_Reg (char *elem)
{
    if (*elem == 'a' && *(elem + 1) == 'x')         // ax
    {
        return 0;
    }
    else if (*elem == 'b' && *(elem + 1) == 'x')    // bx
    {
        return 1;
    }
    else if (*elem == 'c' && *(elem + 1) == 'x')    // cx
    {
        return 2;
    }
    else if (*elem == 'd' && *(elem + 1) == 'x')    // dx
    {
        return 3;
    }

    return -1;
}
