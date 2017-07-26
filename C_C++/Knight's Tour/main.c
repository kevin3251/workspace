#include "board.h"
#include <stdio.h>
#include <stdlib.h>
int main()
{
    board_initial();
    ktmove_initial();
    set_first();
    find_exit();
    final_output();
    return 0;
}
