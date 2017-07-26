#ifndef OTHELLO_H
#define OTHELLO_H

// bitboard structure
typedef unsigned long long int bitboard;
//othello data structure

typedef struct location
{
    int i;
    int j;
    int g;
} Location;
//my othello function
void Reset_Weight_Board(int color);
void Reset_Move_Order(int color);
void Swap_Order(int p1,int p2);

//othello standard function
void Delay(unsigned int mseconds);
void Read_File( char *c );//open a file and get the next move, for play by file
char Load_File( void );//load a file and start a game

void Init();
int Play_a_Move( int x, int y);
void  Show_Board_and_Set_Legal_Moves( void );
int  Put_a_Stone( int x, int y );

int  In_Board( int x, int y );
int  Check_Cross( int x, int y, int update);
int  Check_Straight_Army( int x, int y, int d, int update , int army);

int  Find_Legal_Moves(int color);
int  Check_EndGame( void );
int  Compute_Grades(int flag);

void Computer_Think( int *x, int *y);
int Search(int myturn, int mylevel);
int search_next(int x, int y, int myturn, int mylevel, int alpha, int beta);

#endif // OTHELLO_H
