#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
int board[8][8],i,j,ktmove1[8],ktmove2[8],m;
void board_initial();
void set_first();
void find_exit();
void test_next(int npos_way,int nexti[],int nextj[]);
void final_output();
void ktmove_initial();

#endif // BOARD_H_INCLUDED
