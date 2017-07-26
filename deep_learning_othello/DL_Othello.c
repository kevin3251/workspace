#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <assert.h>

#include "hdf5.h"

#define TRUE 1
#define FALSE 0

int globalcount = 0;

int Input[1000000][2][8][8];
int Output[1000000];

void Delay(unsigned int mseconds);
void Read_File( char *c );//open a file and get the next move, for play by file
char Load_File( void );//load a file and start a game

void Init();
void Play_a_Move( int p );
void Make_Board( int move, int *t);
void Print_Input( int move);
void Write_HDF5( char *HDF5FILE );

int  Check_Cross( int p, int update );
int  Check_Straight_Army( int p, int d, int update );
int  Find_Legal_Moves(int color);

int Now_Board[ 100 ];
int Legal_Moves[ 100 ];
int HandNumber;

int Turn = 0;// 0 is black or 1 is white
int Stones[2]= {1,2}; // 1: black, 2: white
int Dir[8] = { 1, -9, -10, -11, -1, 9, 10, 11};

int board_range[100] =
{
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1,  20,  -3,  11,  8,  8,  11,  -3,  20, -1,
  -1,  -3,  -7,  -4,  1,  1,  -4,  -7,  -3, -1,
  -1,  11,  -4,  2,  2,  2,  2,  -4,  11, -1,
  -1,  8,  1,  2,  -3,  -3,  2,  1,  8, -1,
  -1,  8,  1,  2,  -3,  -3,  2,  1,  8, -1,
  -1,  11,  -4,  2,  2,  2,  2,  -4,  11, -1,
  -1,  -3,  -7,  -4,  1,  1,  -4,  -7,  -3, -1,
  -1,  20,  -3,  11,  8,  8,  11,  -3,  20, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
};


//     a,  b,  c,  d,  e,  f,  g,  h
/* 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 1 // c4 = 43
  20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 2
  30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 3
  40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 4
  50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 5
  60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 6
  70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 7
  80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 8
  90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
}*/
/*
 a,  b,  c,  d,  e,  f,  g,  h   c4=26
 0,  1,  2,  3,  4,  5,  6,  7,
 8,  9, 10, 11, 12, 13, 14, 15,
16, 17, 18, 19, 20, 21, 22, 23,
24, 25, 26, 27, 28, 29, 30, 31,
*/
//---------------------------------------------------------------------------
// FILE example
//-18 61 f5 f4 d3 c4 g3 d2 e3 e6 c2 f6 c1 g5 c5 c6 d6 f3 g4 h4 c3 h3 b5 b4 d7 e2 a3 a5 b6
//e7 f1 a6 g6 c7 f2 h6 g7 d1 e1 f7 d8 a4 a7 e8 g8 c8 b3 b2 f8 h8 b8 a8 b7 b1 h7 a2 a1 g1 h1 ps h5 g2 h2
//---------------------------------------------------------------------------
int main()
{
    int now_move, i, j, nc=0, total_move;
    FILE *fp, *fdata;
    char tc[10+20], fname[30];
    char *fn = fname;
    int row_input, column_input, n, s, think_time;
    time_t timeBegin, timeEnd;

    timeBegin = time(NULL);

    fp = fopen( "train_games.txt", "r" );
    fdata = fopen( "train_set.txt", "w");
    assert( fp != NULL );
    for ( j = 1; j < 4; j++ )
    {
        globalcount = nc = total_move = 0 ;
        while ( nc < 2500 )
        {
            Init();
            fscanf( fp, "%s", tc );
            fscanf( fp, "%d", &n );
            ///printf("%d\n", n);
            for ( i=1; i <= n; i++ )
            {
                total_move++;
                fscanf( fp, "%s", tc );
                column_input = 1 + tc[0] - 97;// pass = ps,'p'=112, 15, ex. c4=34 <<>> 43
                row_input = 1 + tc[1] - 49;// 's'=115, 66
                now_move = row_input + column_input * 10;//ps = 675
//           printf("Play #%d: %c%c = %d%d %d\n", i, tc[0], tc[1], row_input, column_input, Turn);
                if ( now_move> 10 && now_move < 89 && Find_Legal_Moves( Stones[Turn] ))
                    Print_Input( now_move);

                Play_a_Move( now_move );
                //scanf("%d", &s );
            }

            nc++;
            if ( nc % 1000 == 0)
            {
                timeEnd = time(NULL);
                think_time = timeEnd - timeBegin ;
                printf("#%dth train set, Finished #%d, time= %d min. %d sec.\n", j, nc, think_time/60, think_time);
            }
        }
        sprintf( fn, "./data/train%d.h5", j );
        printf("#Total train boards = %d, #Total moves = %d\n", globalcount, total_move);
        Write_HDF5( fn );
        fprintf( fdata, "%s\n", fn );
    }


    fclose(fp);
    fclose(fdata);
//

    fp = fopen( "test_games.txt", "r" );
    assert( fp != NULL );
    globalcount = nc = total_move = 0 ;
    while ( nc < 250 )
    {
        Init();
        fscanf( fp, "%s", tc );
        fscanf( fp, "%d", &n );
        ///printf("%d\n", n);
        for ( i=1; i <= n; i++ )
        {

            fscanf( fp, "%s", tc );
            column_input = 1 + tc[0] - 97;// pass = ps,'p'=112, 15, ex. c4=34 <<>> 43
            row_input = 1 + tc[1] - 49;// 's'=115, 66
            now_move = row_input + column_input * 10;//ps = 675
//           printf("Play #%d: %c%c = %d%d %d\n", i, tc[0], tc[1], row_input, column_input, Turn);
            if ( now_move> 10 && now_move < 89 && Find_Legal_Moves( Stones[Turn] ))
                Print_Input( now_move);

            Play_a_Move( now_move );
            //scanf("%d", &s );
        }

        nc++;
        if ( nc % 100 == 0)
        {
            timeEnd = time(NULL);
            think_time = timeEnd - timeBegin ;
            printf("Finished #%d, time= %d min. %d sec.\n", nc, think_time/60, think_time);
        }
    }
    printf("#Total train boards = %d, #Total moves = %d\n", globalcount, total_move);
    Write_HDF5( "./data/test_set.h5");

    fclose(fp);

    printf("End parsing, #Total data = %d\n", nc);
    //scanf("%d", &s );

    return 0;
}

//---------------------------------------------------------------------------

void Init()
{
    memset(Now_Board, 0, sizeof(int) * 100);

    Now_Board[44] = Now_Board[55] = 2;//white, dark
    Now_Board[45] = Now_Board[54] = 1;//black, light
    HandNumber = 0;
    Turn = 0;
}
//---------------------------------------------------------------------------

void Play_a_Move( int p )
{
    if ( p == 675)// is a pass move
        return;
    Now_Board[p] = Stones[Turn];
    Check_Cross( p, TRUE );
	Turn = 1 - Turn;
    return;
}
//---------------------------------------------------------------------------

void Make_Board( int move, int *t)

{
    int b[64]={0}, w[64]={0};//Black/White stones
    int om[64] = {0};
    int tms[100] = {0};
    int i, m88;

    int x,y;

//    static char a1[64]={1}, a0[64] = {0};

    tms[move]=1;
    for ( i = 0; i < 64; i++ )
    {
        if ( Now_Board[t[i]] == 1)
            b[i] = 1;
        else if ( Now_Board[t[i]] == 2)
            w[i] = 1;
         if ( tms[t[i]] == 1 )
        {
            om[i] = 1;
            m88 = i;
//            printf("%d\n", m88);
        }

    }

    for( i = 0; i < 64; i++ )
    {
        ///fprintf( fip, "%d ", b[i] );
        x = i / 8;
        y = i % 8;
        Input[globalcount][0][x][y] = b[i];
    }

    for ( i = 0; i < 64; i++ )
    {
        ///fprintf( fip, "%d ", w[i] );
        x = i / 8;
        y = i % 8;
        Input[globalcount][1][x][y] = w[i];
    }


    Output[globalcount] = m88;
    globalcount += 1;
// check if all planes are ok
/*        int j, k, tb[8][8]={{0}};
        printf("a b c d e f g h\n");

        for( i = 0 ; i < 8 ; i++)
            for( j = 0 ; j < 8 ; j++)
            {
                k = i + j * 8;
                if ( b[k]  == 1)
                    tb[i][j] = 1;
                else if ( w[k]  == 1)
                    tb[i][j] = 2;
                else if ( ms[k]  == 1)
                    tb[i][j] = 3;
                if ( om[k]  == 1)
                    tb[i][j] = 4;
            }

        for( i=0 ; i<8 ; i++)
        {
            for(j=0 ; j<8 ; j++)
            {
                    if ( tb[i][j] == 2 )
                        printf("O ");//white
                    else if ( tb[i][j] == 1 )
                        printf("X ");//black
                    else if ( tb[i][j] == 3 )
                        printf("? ");
                    else if ( tb[i][j] == 4 )
                        printf("M ");
                    else printf(". ");
            }
            printf(" %d\n", i+1);
        }
        printf("#%d, %d\n", move, m88);
        scanf("%d", &move);*/
}
//---------------------------------------------------------------------------

void Print_Input( int move)
{
    /*static int t1[64] =
    {
// a,  b,  c,  d,  e,  f,  g,  h
  11, 12, 13, 14, 15, 16, 17, 18, //1
  21, 22, 23, 24, 25, 26, 27, 28, //2
  31, 32, 33, 34, 35, 36, 37, 38, //3
  41, 42, 43, 44, 45, 46, 47, 48, //4
  51, 52, 53, 54, 55, 56, 57, 58, //5
  61, 62, 63, 64, 65, 66, 67, 68, //6
  71, 72, 73, 74, 75, 76, 77, 78, //7
  81, 82, 83, 84, 85, 86, 87, 88, //8
    };
    static int t2[64] =
    {
// a,  b,  c,  d,  e,  f,  g,  h
  11, 21, 31, 41, 51, 61, 71, 81, //1
  12, 22, 32, 42, 52, 62, 72, 82, //2
  13, 23, 33, 43, 53, 63, 73, 83, //3
  14, 24, 34, 44, 55, 64, 74, 84, //4
  15, 25, 35, 45, 54, 65, 75, 85, //5
  16, 26, 36, 46, 56, 66, 76, 86, //6
  17, 27, 37, 47, 57, 67, 77, 87, //7
  18, 28, 38, 48, 58, 68, 78, 88, //8
    };
    static int t3[64] =
    {
// a,  b,  c,  d,  e,  f,  g,  h
  88, 87, 86, 85, 84, 83, 82, 81, //1
  78, 77, 76, 75, 74, 73, 72, 71, //2
  68, 67, 66, 65, 64, 63, 62, 61, //3
  58, 57, 56, 55, 54, 53, 52, 51, //4
  48, 47, 46, 45, 44, 43, 42, 41, //5
  38, 37, 36, 35, 34, 33, 32, 31, //6
  28, 27, 26, 25, 24, 23, 22, 21, //7
  18, 17, 16, 15, 14, 13, 12, 11, //8
    };
    static int t4[64] =
    {
// a,  b,  c,  d,  e,  f,  g,  h
  88, 78, 68, 58, 48, 38, 28, 18, //1
  87, 77, 67, 57, 47, 37, 27, 17, //2
  86, 76, 66, 56, 46, 36, 26, 16, //3
  85, 75, 65, 55, 45, 35, 25, 15, //4
  84, 74, 64, 54, 44, 34, 24, 14, //5
  83, 73, 63, 53, 43, 33, 23, 13, //6
  82, 72, 62, 52, 42, 32, 22, 12, //7
  81, 71, 61, 51, 41, 31, 21, 11, //8
    };
	
    static int t5[64] =
    {
// a,  b,  c,  d,  e,  f,  g,  h
  88, 62, 57, 31, 56, 58, 55, 71, //1
  81, 46, 43, 45, 42, 44, 47, 63, //2
  87, 33, 17, 16, 23, 41, 52, 67, //3
  82, 31, 18, 14, 11, 21, 48, 64, //4
  86, 32, 15, 13, 12, 22, 53, 66, //5
  83, 28, 25, 27, 24, 26, 51, 65, //6
  85, 38, 35, 37, 34, 36, 54, 68, //7
  84, 75, 72, 76, 73, 77, 74, 78, //8
    };
*/	
/*
	static int t5[64] =
    {
// a,  b,  c,  d,  e,  f,  g,  h
  11, 18, 88, 81, 12, 17, 28, 78, //1
  87, 82, 71, 21, 31, 13, 16, 38, //2
  68, 86, 83, 61, 22, 27, 77, 72, //3
  41, 14, 15, 48, 58, 85, 84, 51, //4
  32, 23, 26, 37, 67, 76, 73, 62, //5
  42, 52, 24, 25, 47, 57, 75, 74, //6
  33, 36, 66, 63, 43, 34, 35, 46, //7
  56, 65, 64, 53, 44, 45, 55, 54, //8
    };
	*/
    static int t2[64] =
    {
// a,  b,  c,  d,  e,  f,  g,  h
  11, 13, 15, 17, 31, 51, 71, 33, //1
  55, 77, 81, 61, 41, 21, 83, 85, //2
  87, 63, 45, 27, 88, 86, 84, 82, //3
  68, 48, 28, 66, 44, 22, 18, 16, //4
  14, 12, 38, 58, 78, 36, 54, 72, //5
  42, 24, 25, 47, 57, 75, 74, 52, //6
  73, 62, 32, 23, 26, 37, 67, 76, //7
  43, 34, 53, 35, 65, 56, 64, 46, //8
    };
    static int t3[64] =
    {
// a,  b,  c,  d,  e,  f,  g,  h
  18, 16, 14, 12, 38, 58, 78, 36, //1
  54, 72, 88, 68, 48, 28, 86, 84, //2
  82, 66, 44, 22, 81, 83, 85, 87, //3
  61, 41, 21, 63, 45, 27, 11, 13, //4
  15, 17, 31, 51, 71, 33, 55, 77, //5
  25, 47, 57, 75, 74, 52, 42, 24, //6
  32, 23, 26, 37, 67, 76, 73, 62, //7
  43, 34, 35, 46, 56, 65, 64, 53, //8
    };
    static int t4[64] =
    {
// a,  b,  c,  d,  e,  f,  g,  h
  88, 68, 48, 28, 86, 84, 82, 66, //1
  44, 22, 81, 83, 85, 87, 61, 41, //2
  21, 63, 45, 27, 11, 31, 51, 71, //3
  13, 15, 17, 33, 55, 77, 18, 16, //4
  14, 12, 38, 58, 78, 36, 54, 72, //5
  42, 24, 25, 47, 57, 75, 74, 52, //6
  32, 23, 26, 37, 67, 76, 73, 62, //7
  43, 34, 35, 46, 56, 65, 64, 53, //8
    };
	
    static int t1[64] =
    {
// a,  b,  c,  d,  e,  f,  g,  h
  81, 61, 41, 21, 83, 85, 87, 63, //1
  45, 27, 11, 31, 51, 71, 13, 15, //2
  17, 33, 55, 77, 18, 16, 14, 12, //3
  38, 58, 78, 36, 54, 72, 88, 68, //4
  48, 28, 86, 84, 82, 66, 44, 22, //5
  57, 75, 74, 52, 42, 24, 25, 47, //6
  26, 38, 67, 76, 73, 62, 32, 23, //7
  35, 46, 56, 65, 64, 53, 43, 34, //8
    };
    Make_Board( move, t1);
    Make_Board( move, t2);
    Make_Board( move, t3);
    Make_Board( move, t4);
//	Make_Board( move, t5);
//    int i; scanf("%d", &i);
}
//---------------------------------------------------------------------------
void Write_HDF5( char *HDF5FILE )
{
	    hid_t       file_id, dataset_id, dataspace_id;  // identifiers
	    herr_t      status;
	    hsize_t     dims[4];


	    // Create a new file using default properties.
	    file_id = H5Fcreate(HDF5FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

	    // Create the data space for the dataset.
	    dims[0] = globalcount;
	    dims[1] = 2;//#plane number;
	    dims[2] = 8;
	    dims[3] = 8;
	    dataspace_id = H5Screate_simple(4, dims, NULL);

	    // Create the dataset.
	    dataset_id = H5Dcreate2(file_id, "/input", H5T_STD_I8BE, dataspace_id,
				    H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

	    // Create the data space for the dataset.
	    dims[0] = globalcount;
	    dims[1] = 1;
	    dims[2] = 1;
	    dims[3] = 1;
      dataspace_id = H5Screate_simple(1, dims, NULL);
//	    dataspace_id = H5Screate_simple(4, dims, NULL);

	    // Create the dataset.
	    dataset_id = H5Dcreate2(file_id, "/label", H5T_STD_I8BE, dataspace_id,
				    H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

	    // End access to the dataset and release resources used by it.
	    status = H5Dclose(dataset_id);

	    // Terminate access to the data space.
	    status = H5Sclose(dataspace_id);

	    // Close the file.
	    status = H5Fclose(file_id);

	    //----------------------------------------------------------------------------------------

	    // Open an existing file.
	    file_id = H5Fopen(HDF5FILE, H5F_ACC_RDWR, H5P_DEFAULT);

	    // Open an existing dataset.
	    dataset_id = H5Dopen2(file_id, "/input", H5P_DEFAULT);

	    // Write the dataset.
	    status = H5Dwrite(dataset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT,
			      Input);

	    // Close the dataset.
	    status = H5Dclose(dataset_id);

	    // Open an existing dataset.
	    dataset_id = H5Dopen2(file_id, "/label", H5P_DEFAULT);

	    // Write the dataset.
	    status = H5Dwrite(dataset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT,
			      Output);

	    // Close the dataset.
	    status = H5Dclose(dataset_id);

	    // Close the file.
	    status = H5Fclose(file_id);
}

int Find_Legal_Moves( int color )
{
    int i;
    int me = color;
    int legal_count = 0;

    memset(Legal_Moves, 0, sizeof(int) * 100);

    for( i = 11; i < 89; i++ )
        if( Now_Board[i] == 0 && board_range[i] != -1)
        {
            Now_Board[i] = me;
            if( Check_Cross( i, 0 ) == TRUE )
            {
                Legal_Moves[i] = TRUE;
                legal_count ++;
            }
            Now_Board[i] = 0;
        }

    return legal_count;
}
//---------------------------------------------------------------------------

int Check_Cross(int p, int update)
{
    int k;
    int dx;

    int army = 3 - Now_Board[p];
    int army_count = 0;

   //if(p == 62) printf("%d, %d, %d\n", p, Now_Board[p], army);
    for( k=0 ; k<8 ; k++ )
    {
        dx = p + Dir[k];
        if( board_range[dx] != -1 && Now_Board[dx] == army )
        {
            army_count += Check_Straight_Army( dx, k, update ) ;
   //if(p == 62) printf("%d, %d, %d, %d\n", p, dx, Now_Board[p], army_count);
            //printf("%d, ", army_count);
        }
    }
   //if(p == 62) printf("%d, %d, %d\n", p, Now_Board[p], army_count);
    if(army_count >0)
        return TRUE;
    else
        return FALSE;
}
//---------------------------------------------------------------------------

int Check_Straight_Army(int p, int d, int update)
{
    int army = Now_Board[p];
    int me = 3 - army;
    int army_count=0;
    int found_flag=FALSE;
    //int flag[ 100 ] = {0};
    int temp[7] = {0};

    int i, j;
    int tp = p;

    //flag[tp] = TRUE;
    temp[0] = tp;
    army_count ++;
//printf("Check_Straight_Army %d\n", tp);
    for(i=1 ; i<8 && !found_flag ; i++)
    {
        tp += Dir[d];
//printf("%d, %d, %d, %d\n", d, tp, Now_Board[tp], me);
        if( board_range[tp] != -1 )
        {
            if( Now_Board[tp] == army )
            {
                army_count ++;
               // flag[tp] = TRUE;
                temp[i] = tp;
            }
            else if( Now_Board[tp] == me)
            {
                //printf("%d\n", tp);
                found_flag = TRUE;
                break;
            }
            else
                break;
        }
        else
            break;
    }

    if( (found_flag == TRUE) && (army_count > 0) )
    {
        if ( update == 0 ) return army_count;

        for ( j = 0; j < i; j++ )
        {
           Now_Board[temp[j]] = me;
           //printf("%d %d\n", i, temp[i]);
        }

        return army_count;
    }
    else return 0;
}

//---------------------------------------------------------------------------
