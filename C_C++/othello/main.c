#include <stdio.h>
#include <stdlib.h>
#include "othello.h"


int main()
{

    char compcolor = 'W', c[10];
    int column_input, row_input ;
    int rx, ry, m=0, n;
    FILE *fp;

    Init();
    printf("Computer take?(B/W/All/File play as first/file play as Second/Load and play): ");
    scanf("%c", &compcolor);
    Show_Board_and_Set_Legal_Moves();

    if (compcolor == 'L' || compcolor == 'l')
        compcolor = Load_File();

    if ( compcolor == 'B' || compcolor == 'b')
    {
        Computer_Think( &rx, &ry );
        printf("Computer played %c%d\n", rx+97, ry+1);
        Play_a_Move( rx, ry );

        Show_Board_and_Set_Legal_Moves();
    }

    if ( compcolor == 'A' || compcolor == 'a')
        while ( m++ < 64 )
        {
            Computer_Think( &rx, &ry );
            if ( !Play_a_Move( rx, ry ))
            {
                printf("Wrong Computer moves %c%d\n", rx+97, ry+1);
                scanf("%d", &n);
                break;
            }
            if ( rx == -1 )
                printf("Computer Pass\n");
            else
                printf("Computer played %c%d\n", rx+97, ry+1);

            if ( Check_EndGame() )
                return 0;
            Show_Board_and_Set_Legal_Moves();
        }

    if ( compcolor == 'F')
    {
        Computer_Think( &rx, &ry );
        Play_a_Move( rx, ry );
    }

    while ( m++ < 64 )
    {
        while (1)
        {
            if ( compcolor == 'F' || compcolor == 'S' )
            {
                fp = fopen( "of.txt", "r" );
                fscanf( fp, "%d", &n );
                fclose( fp );

                if (compcolor == 'F' )
                {
                    if ( n % 2 == 0 )
                        Read_File( c );
                    else
                    {
                        Delay(100);
                        continue;
                    }
                }
                else
                {
                    if ( n % 2 == 1 )
                        Read_File( c );
                    else
                    {
                        Delay(100);
                        continue;
                    }
                }
             }


            if ( compcolor == 'B' )
            {
                printf("input White move:(a-h 1-8), or PASS\n");
                scanf("%s", c);
            }
            else if ( compcolor == 'W' )
            {
                printf("input Black move:(a-h 1-8), or PASS\n");
                scanf("%s", c);
            }

            if ( c[0] == 'P' || c[0] == 'p')
                row_input = column_input = -1;
            else if ( c[0] == 'M' || c[0] == 'm' )
            {
                Computer_Think( &rx, &ry );
                if ( !Play_a_Move( rx, ry ))
                {
                    printf("Wrong Computer moves %c%d\n", rx+97, ry+1);
                    scanf("%d", &n);
                    break;
                }
                if ( rx == -1 )
                    printf("Computer Pass");
                else
                    printf("Computer played %c%d\n", rx+97, ry+1);
                if ( Check_EndGame() )
                    break;
                Show_Board_and_Set_Legal_Moves();
            }
            else
            {
                row_input = c[0] - 97;
                column_input = c[1] - 49;
            }
//            printf("%d, %d\n", row_input, column_input);

            if ( !Play_a_Move(row_input, column_input) )
                printf("%c%d is a Wrong move\n", c[0], column_input+1);
            else
                break;
        }
        if ( Check_EndGame() )
            return 0;;
        Show_Board_and_Set_Legal_Moves();

        Computer_Think( &rx, &ry );
        printf("Computer played %c%d\n", rx+97, ry+1);
        Play_a_Move( rx, ry );
        if ( Check_EndGame() )
            return 0;;
        Show_Board_and_Set_Legal_Moves();

    }

    printf("Game is over");
    scanf("%d", &n);

    return 0;
}
