#define othllo_c

#include "othello.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <assert.h>


//othello data value
#define Board_Size 8
#define TRUE 1
#define FALSE 0
#define	EMPTY_BOARD	0ULL
#define A1 0x0000000000000001ULL
#define B1 0x0000000000000002ULL
#define C1 0x0000000000000004ULL
#define D1 0x0000000000000008ULL
#define E1 0x0000000000000010ULL
#define F1 0x0000000000000020ULL
#define G1 0x0000000000000040ULL
#define H1 0x0000000000000080ULL
#define A2 0x0000000000000100ULL
#define B2 0x0000000000000200ULL
#define C2 0x0000000000000400ULL
#define D2 0x0000000000000800ULL
#define E2 0x0000000000001000ULL
#define F2 0x0000000000002000ULL
#define G2 0x0000000000004000ULL
#define H2 0x0000000000008000ULL
#define A3 0x0000000000010000ULL
#define B3 0x0000000000020000ULL
#define C3 0x0000000000040000ULL
#define D3 0x0000000000080000ULL
#define E3 0x0000000000100000ULL
#define F3 0x0000000000200000ULL
#define G3 0x0000000000400000ULL
#define H3 0x0000000000800000ULL
#define A4 0x0000000001000000ULL
#define B4 0x0000000002000000ULL
#define C4 0x0000000004000000ULL
#define D4 0x0000000008000000ULL
#define E4 0x0000000010000000ULL
#define F4 0x0000000020000000ULL
#define G4 0x0000000040000000ULL
#define H4 0x0000000080000000ULL
#define A5 0x0000000100000000ULL
#define B5 0x0000000200000000ULL
#define C5 0x0000000400000000ULL
#define D5 0x0000000800000000ULL
#define E5 0x0000001000000000ULL
#define F5 0x0000002000000000ULL
#define G5 0x0000004000000000ULL
#define H5 0x0000008000000000ULL
#define A6 0x0000010000000000ULL
#define B6 0x0000020000000000ULL
#define C6 0x0000040000000000ULL
#define D6 0x0000080000000000ULL
#define E6 0x0000100000000000ULL
#define F6 0x0000200000000000ULL
#define G6 0x0000400000000000ULL
#define H6 0x0000800000000000ULL
#define A7 0x0001000000000000ULL
#define B7 0x0002000000000000ULL
#define C7 0x0004000000000000ULL
#define D7 0x0008000000000000ULL
#define E7 0x0010000000000000ULL
#define F7 0x0020000000000000ULL
#define G7 0x0040000000000000ULL
#define H7 0x0080000000000000ULL
#define A8 0x0100000000000000ULL
#define B8 0x0200000000000000ULL
#define C8 0x0400000000000000ULL
#define D8 0x0800000000000000ULL
#define E8 0x1000000000000000ULL
#define F8 0x2000000000000000ULL
#define G8 0x4000000000000000ULL
#define H8 0x8000000000000000ULL
bitboard black, white, Legal_Moves, Now_Board;
int Search_Counter;
int Computer_Take;
int Winner;
int HandNumber;
int sequence[100];
int Black_Count, White_Count;
int Turn;// 0 is black or 1 is white

int LastX, LastY;
//int Auto_Check_Dead;
int search_deep;

int alpha_beta_option;
int resultX, resultY;
const int DirX[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const int DirY[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int mid_board_weight[8][8] =
//a, b, c, d, e, f, g,  h
{
    {20, 1, 1, 1, 1, 1, 1, 20},//1
    {1, 1, 1, 1, 1, 1, 1, 1},//2
    {1, 1, 1, 1, 1, 1, 1, 1},//3
    {1, 1, 1, 1, 1, 1, 1, 1},//4
    {1, 1, 1, 1, 1, 1, 1, 1},//5
    {1, 1, 1, 1, 1, 1, 1, 1},//6
    {1, 1, 1, 1, 1, 1, 1, 1},//7
    {20, 1, 1, 1, 1, 1, 1, 20}
};//8

int board_weight[8][8] =
//a, b, c, d, e, f, g,  h
{
    {20, -4, 5, 5, 5, 5, -4, 20},//1
    {-4, -6, 2, 2, 2, 2, -6, -4},//2
    {5, 2, 2, 2, 2, 2, 2, 5},//3
    {5, 2, 2, 2, 2, 2, 2, 5},//4
    {5, 2, 2, 2, 2, 2, 2, 5},//5
    {5, 2, 2, 2, 2, 2, 2, 5},//6
    {-4, -6, 2, 2, 2, 2, -6, -4},//7
    {20, -4, 5, 5, 5, 5, -4, 20}
};//8
bitboard site[8][8] =
{
    {A1,B1,C1,D1,E1,F1,G1,H1},
    {A2,B2,C2,D2,E2,F2,G2,H2},
    {A3,B3,C3,D3,E3,F3,G3,H3},
    {A4,B4,C4,D4,E4,F4,G4,H4},
    {A5,B5,C5,D5,E5,F5,G5,H5},
    {A6,B6,C6,D6,E6,F6,G6,H6},
    {A7,B7,C7,D7,E7,F7,G7,H7},
    {A8,B8,C8,D8,E8,F8,G8,H8}
};
bitboard moveOrder[64] =
{
    A1,H1,H8,A8,C1,A3,F1,H3,
    H6,F8,C8,A6,D1,A4,E1,H4,
    H5,E8,D8,A5,C2,B3,F2,G3,
    G6,F7,C7,B6,B4,D2,E2,G4,
    G5,E7,D7,B5,C3,F3,F6,C6,
    C4,D3,E3,F4,F5,E6,D6,C5,
    D4,E4,E5,D5,A2,B1,G1,H2,
    H7,G8,B8,A7,B2,G2,G7,B7
};
//int search_level_now;

int moveOrderX[64] =
{
    0,0,7,7,0,2,0,2,
    5,7,7,5,0,3,0,3,
    4,7,7,4,1,2,1,2,
    5,6,6,5,3,1,1,3,
    4,6,6,4,2,2,5,5,
    3,2,2,3,4,5,5,4,
    3,3,4,4,1,0,0,1,
    6,7,7,6,1,1,6,6
};
int moveOrderY[64] =
{
    0,7,7,0,2,0,5,7,
    7,5,2,0,3,0,4,7,
    7,4,3,0,2,1,5,6,
    6,5,2,1,1,3,4,6,
    6,4,3,1,2,5,5,2,
    2,3,4,5,5,4,3,2,
    3,4,4,3,0,1,6,7,
    7,6,1,0,1,6,6,1
};
void Reset_Weight_Board(int mycolor)
{
    bitboard nboard = (black|white);
    bitboard temp;
    if(mycolor == 0)
        temp = black;
    else
        temp = white;
    if( A1 & temp & nboard)
    {
        board_weight[0][1] = board_weight[1][0]= 15 ;
        board_weight[0][2] = board_weight[2][0]= -4 ;
        board_weight[1][1] = 10;
    }
    else
    {
        board_weight[0][1] = board_weight[1][0]= -4 ;
        board_weight[0][2] = board_weight[2][0]= 5 ;
        board_weight[1][1] = -6;
    }
    if( A8 & temp & nboard)
    {
        board_weight[6][0] = board_weight[7][1]= 15 ;
        board_weight[5][0] = board_weight[7][2]= -4 ;
        board_weight[6][1] = 10;
    }
    else
    {
        board_weight[6][0] = board_weight[7][1]= -4 ;
        board_weight[5][0] = board_weight[7][2]= 5 ;
        board_weight[6][1] = -6;
    }
    if( H1 & temp & nboard)
    {
        board_weight[0][6] = board_weight[1][7]= 15 ;
        board_weight[0][5] = board_weight[2][7]= -4 ;
        board_weight[6][1] = 10;
    }
    else
    {
        board_weight[0][6] = board_weight[1][7]= -4 ;
        board_weight[0][5] = board_weight[2][7]= 5 ;
        board_weight[6][1] = -6;
    }
    if( H8 & temp & nboard)
    {
        board_weight[7][6] = board_weight[6][7]= 15 ;
        board_weight[7][5] = board_weight[5][7]= -4 ;
        board_weight[6][6] = 10;
    }
    else
    {
        board_weight[7][6] = board_weight[6][7]= -4 ;
        board_weight[7][5] = board_weight[5][7]= 5 ;
        board_weight[6][6] = -6;
    }
}
void Swap_Order(int p1,int p2)
{
    bitboard Order;
    int x,y;
    Order = moveOrder[p1];
    moveOrder[p1] = moveOrder[p2];
    moveOrder[p2] = Order;
    x = moveOrderX[p1];
    moveOrderX[p1] = moveOrderX[p2];
    moveOrderX[p2] = x;
    y = moveOrderY[p1];
    moveOrderY[p1] = moveOrderY[p2];
    moveOrderY[p2] = y;
}
void Reset_Move_Order(int mycolor)
{
    bitboard nboard = (black|white);
    bitboard temp;
    if(mycolor == 0)
        temp = black;
    else
        temp = white;
    if( A1 & temp & nboard)
    {
        Swap_Order(0,9);
        Swap_Order(8,16);
        Swap_Order(1,2);
    }
    if( A8 & temp & nboard)
    {
        Swap_Order(56,49);
        Swap_Order(48,40);
        Swap_Order(57,58);
    }
    if( H1 & temp & nboard)
    {
        Swap_Order(7,14);
        Swap_Order(6,5);
        Swap_Order(15,23);
    }
    if( H8 & temp & nboard)
    {
        Swap_Order(63,54);
        Swap_Order(55,47);
        Swap_Order(62,61);
    }
    if(board_weight[moveOrderX[0]][moveOrderY[0]] < 0)
    {
        Swap_Order(0,9);
        Swap_Order(8,16);
        Swap_Order(1,2);
    }
    if(board_weight[moveOrderX[7]][moveOrderY[7]] < 0)
    {
        Swap_Order(7,14);
        Swap_Order(6,5);
        Swap_Order(15,23);
    }
    if(board_weight[moveOrderX[56]][moveOrderY[56]] < 0)
    {
        Swap_Order(56,49);
        Swap_Order(48,40);
        Swap_Order(57,58);
    }
    if(board_weight[moveOrderX[63]][moveOrderY[63]] < 0)
    {
        Swap_Order(63,54);
        Swap_Order(55,47);
        Swap_Order(62,61);
    }
}

void Delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
//---------------------------------------------------------------------------

void Read_File( char *c )
{
    FILE *fp;
    char tc[10];

    fp = fopen( "of.txt", "r" );
    while ( (fscanf( fp, "%s", tc ) ) != EOF )
    {
        c[0] = tc[0];
        c[1] = tc[1];
    }
}
//---------------------------------------------------------------------------

char Load_File( void )
{
    FILE *fp;
    char tc[10];
    int row_input, column_input, n;

    fp = fopen( "of.txt", "r" );
    assert( fp != NULL );

    fscanf( fp, "%d", &n );

    while ( (fscanf( fp, "%s", tc ) ) != EOF )
    {
        row_input= tc[0] - 97;
        column_input = tc[1] - 49;
        if ( !Play_a_Move(row_input, column_input) )
            printf("%c%d is a Wrong move\n", tc[0], column_input+1);

        Show_Board_and_Set_Legal_Moves();
    }
    return ( n%2 == 1 )? 'B' : 'W';
}
//---------------------------------------------------------------------------

void Init()
{
    alpha_beta_option = TRUE;
    search_deep = 8;
    Computer_Take = 0;
    black &= EMPTY_BOARD;
    white &= EMPTY_BOARD;
    //printf("%llu , %llu \n",black , white);

    white = D4 ^ E5;//white, dark
    black = E4 ^ D5;//black, light
   // printf("%llu , %llu \n",black , white);

    HandNumber = 0;
    memset(sequence, -1, sizeof(int) * 100);
    Turn = 0;

    LastX = LastY = -1;
    Black_Count = White_Count = 0;

//  Computer_Thinking = FALSE;
    //debug_value = 0;
    Search_Counter = 0;

    //Computer_Take = 0;
    Winner = 0;
}
//---------------------------------------------------------------------------

int Play_a_Move( int x, int y)
{
    FILE *fp;

    if ( x == -1 && y == -1)
    {
        fp = fopen( "of.txt", "r+" );

        fprintf( fp, "%2d\n", HandNumber+1 );
        fclose(fp);

        fp = fopen("of.txt", "a");
        fprintf( fp, "p9\n" );
        fclose( fp );

        sequence[HandNumber] = -1;
        HandNumber ++;
        Turn = 1 - Turn;
        return 1;
    }

    if ( !In_Board(x,y))
        return 0;
    Find_Legal_Moves(Turn);
    //if( Legal_Moves[x][y] == FALSE )
    //& site[x][y]
    if( !(Legal_Moves & (A1 << ( x << 3 )<< y)))
        return 0;

    if( Put_a_Stone(x,y) )
    {
        Check_Cross(x,y,1);

        Compute_Grades( TRUE );
//        Show_Board_and_Set_Legal_Moves();

//        printf("Play %c%d\n", x+97, y+1);
        return 1;
    }
    else
        return 0;
    return 1;
}

//---------------------------------------------------------------------------

int Put_a_Stone(int x, int y)
{
    FILE *fp;
    bitboard temp;
    temp = A1 << ( x << 3 )<< y;

    if( (( black | white ) & temp) == EMPTY_BOARD)
    {
        sequence[HandNumber] = Turn;
        if (HandNumber == 0)
            fp = fopen( "of.txt", "w" );
        else
            fp = fopen( "of.txt", "r+" );
        fprintf( fp, "%2d\n", HandNumber+1 );
        HandNumber ++;
        fclose(fp);

        //Now_Board[x][y] = Stones[Turn];
        if(Turn == 0)
            black ^= temp;
        else
            white ^= temp;

        fp = fopen("of.txt", "a");
        fprintf( fp, "%c%d\n", x+97, y+1 );;
        fclose( fp );

        LastX = x;
        LastY = y;

        Turn = 1 - Turn;

        return TRUE;
    }
    return FALSE;
}
//---------------------------------------------------------------------------

void Show_Board_and_Set_Legal_Moves( void )
{
    int i,j;
    //printf("%llu\n",Now_Board);
    Now_Board = black | white;
    //printf("%llu\n",Now_Board);
    Find_Legal_Moves(Turn);

    printf("a b c d e f g h\n");
    for(i=0 ; i<Board_Size ; i++)
    {
        for(j=0 ; j<Board_Size ; j++)
        {
            bitboard temp = A1 << ( j << 3 ) << i;
            if( Now_Board & temp )
            {
                if ( white & temp)
                    printf("O ");//white
                else
                    printf("X ");//black
            }
            else
            {
                if ( Legal_Moves & temp)
                    printf("? ");
                else printf(". ");
            }
        }
        printf(" %d\n", i+1);
    }
    printf("\n");
}
//---------------------------------------------------------------------------

int Find_Legal_Moves( int color )
{
    int i,j;
    int legal_count = 0;
    bitboard temp;

    Legal_Moves &= EMPTY_BOARD;
    Now_Board = black | white;

    for(i = 0; i < Board_Size; i++)
        for(j = 0; j <Board_Size; j++)
        {
            temp = A1 << ( i << 3 )<< j;
            if((Now_Board & temp) == EMPTY_BOARD)
            {
                if(color == 0)
                    black ^= temp;
                else
                    white ^= temp;


                if(Check_Cross(i,j,FALSE)==TRUE)
                {
                    Legal_Moves ^= temp;
                    legal_count++;
                }

                if(color == 0)
                    black ^= temp;
                else
                    white ^= temp;

            }
        }

    return legal_count;
}
//----------------------------------------------------------------------------
int Check_Cross(int x, int y, int update)
{
    int k;
    int dx, dy;
    bitboard temp;
    temp = A1 << ( x << 3 )<< y;
    temp &= (black | white);
    if( ! In_Board(x,y) || temp == EMPTY_BOARD)
        return FALSE;

    temp = A1 << ( x << 3 )<< y;
    int army;
    int army_count = 0;
    if(black & temp)
        army = 1;
    else
        army = 0;

//   printf("%d, %d, %d, %d\n", x, y, Now_Board[x][y], army);
    for( k=0 ; k<8 ; k++ )
    {

        dx = DirX[k];
        dy = DirY[k];
        temp = A1 << ( x << 3 )<< y;
        if(dx == 1)
            temp <<= 8;
        else if(dx == -1)
            temp >>= 8;
        if(dy == 1)
            temp <<= 1;
        else if(dy == -1)
            temp >>= 1;
        if(!(temp == EMPTY_BOARD))
        {
            if(army == 0 && (black & temp))
                army_count += Check_Straight_Army( x, y, k, update , army) ;
            if(army == 1 && (white & temp))
                army_count += Check_Straight_Army( x, y, k, update , army) ;
        }
    }

    if(army_count >0)
        return TRUE;
    else
        return FALSE;
}
//---------------------------------------------------------------------------

int Check_Straight_Army(int x, int y, int d, int update, int army)
{
    int me = 1 - army;
    int army_count=0;
    int found_flag=FALSE;
    //int flag[ Board_Size ][ Board_Size ] = {{0}};
    bitboard temp = A1 << ( x << 3 )<< y;
    bitboard flag = EMPTY_BOARD;
    int i;
    int tx, ty;

    tx = x;
    ty = y;
    for(i=0 ; i<Board_Size ; i++)
    {
        tx += DirX[d];
        ty += DirY[d];

        if(In_Board(tx,ty) )
        {
            //temp = A1 << ( tx << 3 )<< ty;
            if(DirX[d] == 1)
                temp <<= 8;
            else if(DirX[d] == -1)
                temp >>= 8;

            if(DirY[d] == 1)
                temp <<= 1;
            else if(DirY[d] == -1)
                temp >>= 1;

            if(me == 0)
            {
                if( white & temp )
                {
                    army_count ++;
                    flag ^= temp;
                }
                else if( black & temp )
                {
                    found_flag =TRUE;
                    break;
                }
                else
                    break;
            }
            else
            {
                if( black & temp )
                {
                    army_count ++;
                    flag ^= temp;
                }
                else if( white & temp )
                {
                    found_flag =TRUE;
                    break;
                }
                else
                    break;
            }
             /*
            if( Now_Board[tx][ty] == army )
            {
                army_count ++;
                flag[tx][ty] = TRUE;
            }
            else if( Now_Board[tx][ty] == me)
            {
                found_flag = TRUE;
                break;
            }
            else
                break;
            */
        }
        else
            break;

    }

    if( (found_flag == TRUE) && (army_count > 0) && update)
    {
        /*
        for(i=0 ; i<Board_Size ; i++)
            for(j=0; j<Board_Size ; j++)
                if(flag[i][j]==TRUE)
                {
                    //Dead_Stone[i][j] = TRUE;
                    if(Now_Board[i][j] != 0)
                        Now_Board[i][j]= 3 - Now_Board[i][j];
                }
        */
        for(i = 0; i < 64; i++)
        {
            temp = A1 << i;
            if((flag & temp)&&(( black|white)& temp ))
            {
                black ^= temp;
                white ^= temp;
            }
        }
    }
    if( (found_flag == TRUE) && (army_count > 0))
        return army_count;
    else return 0;
}
//---------------------------------------------------------------------------

int In_Board(int x, int y)
{
    if( x >= 0 && x < Board_Size && y >= 0 && y < Board_Size )
        return TRUE;
    else
        return FALSE;
}
//---------------------------------------------------------------------------

int Compute_Grades(int flag)
{
    int i,j;
    int B,W, BW, WW;
    bitboard temp;
    B = BW = W = WW = 0;

    for(i=0 ; i<Board_Size ; i++)
        for(j=0 ; j<Board_Size ; j++)
        {
            /*
            if( Now_Board[i][j]==1 )
            {
                B++;
                BW = BW + board_weight[i][j] ;
            }
            else if( Now_Board[i][j]==2 )
            {
                W++;
                WW = WW + board_weight[i][j] ;
            }
            */
            temp =  A1 << ( i << 3 )<< j;
            if(black & temp)
            {
                B++;
                BW = BW + board_weight[i][j];
            }
            else if(white & temp)
            {
                W++;
                WW = WW + board_weight[i][j];
            }
        }

    if(flag)
    {
        Black_Count = B;
        White_Count = W;
        printf("Grade: Black %d, White %d\n", B, W);
    }

    return ( BW - WW );
}
//---------------------------------------------------------------------------

int Check_EndGame( void )
{
    int lc1, lc2;

    lc2 = Find_Legal_Moves( 1 - Turn );
    lc1 = Find_Legal_Moves( Turn );

    if ( lc1==0 && lc2==0 )
    {
        if(Black_Count > White_Count)
        {
            printf("Black Win!\n");
            if(Winner == 0)
                Winner = 1;
        }
        else if(Black_Count < White_Count)
        {
            printf("White Win!\n");
            if(Winner == 0)
                Winner = 2;
        }
        else
        {
            printf("Draw\n");
            Winner = 0;
        }
        Show_Board_and_Set_Legal_Moves();
        printf("Game is over");
        scanf("%d", &lc1);
        return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------

void Computer_Think( int *x, int *y )
{
    time_t clockBegin, clockEnd;
    static int think_time=0;
    int flag;

    clockBegin = clock();

    resultX = resultY = -1;
    Search_Counter = HandNumber;
    if(HandNumber < 32)
        search_deep = 8;
    else if(HandNumber == 32)
        search_deep = 10;
    else if(HandNumber == 48)
        search_deep = 12;

    flag = Search( Turn, 0);

    clockEnd = clock();
    think_time += clockEnd - clockBegin ;
    printf("used thinking time= %d min. %d.%d sec.\n", think_time/60000, (think_time%60000)/1000,  (think_time%60000)%1000);

    if( flag )
    {
        *x = resultX;
        *y = resultY;
    }
    else
    {
        *x = *y = -1;
        return;
    }

}

//---------------------------------------------------------------------------

//MinMax search
int Search(int myturn, int mylevel)
{
    int i;
    //int j;
    Reset_Weight_Board(myturn);
    Location min, max;

    min.i = min.j = -1;
    min.g = 99999;

    max.i = max.j = -1;
    max.g = -99999;

    //int B[ Board_Size ][ Board_Size ];
    //int L[ Board_Size ][ Board_Size ];
    bitboard B,L,tempBlack,tempWhite;
    B = L = tempBlack = tempWhite = EMPTY_BOARD;
    tempBlack = black;
    tempWhite = white;
    B = Now_Board;
    //search_level_now = 0;

    int c = Find_Legal_Moves( myturn );
    if(c <= 0) return FALSE;

    L = Legal_Moves;

    int alpha = -99999;
    int beta = 99999;
    int g = -1;

     for( i = 0; i < 64; i++ )
        {
            bitboard temp =  moveOrder[i];
            if(L & temp)//you could add move ordering
            {
                Now_Board = B;
                black = tempBlack;
                white = tempWhite;
                //Now_Board[i][j] = Stones[myturn];
                if(myturn == 0)
                    black ^= temp;
                else
                    white ^= temp;
                Now_Board ^= temp;

                Check_Cross(moveOrderX[i],moveOrderY[i],TRUE);

                g = search_next(moveOrderX[i],moveOrderY[i], 1-myturn, mylevel+1, alpha, beta);

                if( myturn == 0 )  // max level
                    if( g > max.g )
                    {
                        max.g = g;
                        max.i = moveOrderX[i];
                        max.j = moveOrderY[i];
                    }

                if( myturn == 1 )
                    if( g < min.g )
                    {
                        min.g = g;
                        min.i = moveOrderX[i];
                        min.j = moveOrderY[i];
                    }
            }
        }
    Now_Board = B;
    black = tempBlack;
    white = tempWhite;

    if( myturn == 0 )
    {
        resultX = max.i;
        resultY = max.j;
        return TRUE;
    }

    else if( myturn == 1 )
    {
        resultX = min.i;
        resultY = min.j;
        return TRUE;
    }
    return FALSE;
}
//---------------------------------------------------------------------------

int search_next( int x, int y, int myturn, int mylevel, int alpha, int beta )
{
    int g;
    Search_Counter ++;


    if(HandNumber >= 50){
        memcpy(board_weight, mid_board_weight,sizeof(int)*Board_Size *Board_Size);
        Reset_Weight_Board(myturn);
    }
    else
        Reset_Weight_Board(myturn);

    if( mylevel >= search_deep )
    {
        g = Compute_Grades( FALSE );
        return g;
    }
    else
    {
        int i;
        //int j;
        ///int my_alpha = alpha; int my_beta = beta;

        //Location min; min.i = -1; min.j = -1; min.g = 99999;
        //Location max; max.i = -1; max.i = -1; max.g = -99999;

        //int B[ Board_Size ][ Board_Size ];
        //int L[ Board_Size ][ Board_Size ];
        int xOrder[64],yOrder[64];
        bitboard Order[64];
        bitboard B,L,tempBlack,tempWhite;
        B = L = EMPTY_BOARD;

        int c = Find_Legal_Moves( myturn );
        if(c <= 0)
        {
            g = Compute_Grades( FALSE );
            return g;
        }

        memcpy(xOrder, moveOrderX, sizeof(int)*64);
        memcpy(yOrder, moveOrderY, sizeof(int)*64);
        memcpy(Order, moveOrder, sizeof(bitboard)*64);
        B = Now_Board;
        L = Legal_Moves;
        tempBlack = black;
        tempWhite = white;
        Reset_Move_Order(myturn);
        for(i=0 ; i < 64 ; i++)
        {
            bitboard temp =  moveOrder[i];
            if(L & temp)//you could add move ordering
            {
                black = tempBlack;
                white = tempWhite;
                Now_Board = B;
                //Now_Board[i][j] = Stones[myturn];
                if(myturn == 0)
                    black ^= temp;
                else
                    white ^= temp;
                Now_Board ^= temp;

                Check_Cross(moveOrderX[i],moveOrderY[i],TRUE);

                g = search_next(moveOrderX[i],moveOrderY[i], 1-myturn, mylevel+1, alpha, beta);// could use transposition table

                //Memo1->Lines->Add("lv=" + IntToStr(mylevel) + ",g=" + IntToStr(g) );
                if(c < 4)
                    g -= 1;


                if(myturn==0)  // max ply
                {
                    if(g > alpha)
                        alpha = g;
                }
                if(myturn==1)// min ply
                {
                    if(g < beta)
                        beta = g;
                }

                if( alpha_beta_option == TRUE)
                    if( alpha >= beta )// cutoff
                    {
                        i = 64;
                        break;
                    }
            }
        }
        Now_Board = B;
        black = tempBlack;
        white = tempWhite;
        memcpy(moveOrderX, xOrder, sizeof(int)*64);
        memcpy(moveOrderY, yOrder, sizeof(int)*64);
        memcpy(moveOrder, Order, sizeof(bitboard)*64);

        if(myturn == 0) // max level
            return alpha; //max.g;
        else
            return beta; //min.g;
    }
}
//---------------------------------------------------------------------------
