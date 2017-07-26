#include "board.h"
#include <stdio.h>
#include <stdlib.h>
void board_initial()
{
    for(i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
            board[i][j]=0;
    }
}
void ktmove_initial()
{
    ktmove1[0]=-2;
    ktmove2[0]=1;
    ktmove1[1]=-1;
    ktmove2[1]=2;
    ktmove1[2]=1;
    ktmove2[2]=2;
    ktmove1[3]=2;
    ktmove2[3]=1;
    ktmove1[4]=2;
    ktmove2[4]=-1;
    ktmove1[5]=1;
    ktmove2[5]=-2;
    ktmove1[6]=-1;
    ktmove2[6]=-2;
    ktmove1[7]=-2;
    ktmove2[7]=-1;
}
void set_first()
{
    scanf("%d %d",&i,&j);
    board[i][j]=1;
}
void final_output()
{
    for(i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            if(j==7)
                printf("%3d\n",board[i][j]);
            else
                printf("%3d ",board[i][j]);
        }
    }
}
void find_exit()
{
    int k;
    int nexti[8]= {0};
    int nextj[8]= {0};
    for(m=2; m<=64; m++)
    {
        int npos_way=0;
        for(k=0; k<8; k++)
        {
            if((i+ktmove1[k])<0||(i+ktmove1[k])>7||(j+ktmove2[k])<0||(j+ktmove2[k])>7)
                continue;
            if(board[i+ktmove1[k]][j+ktmove2[k]]==0)
            {
                nexti[npos_way]=i+ktmove1[k];
                nextj[npos_way]=j+ktmove2[k];
                npos_way++;
            }
        }
        test_next(npos_way,nexti,nextj);
        for(k=0; k<8; k++)
        {
            nexti[k]=0;
            nextj[k]=0;
        }
    }
}
void test_next(int npos_way,int nexti[],int nextj[])
{
    if(npos_way==1)
    {
        i=nexti[0];
        j=nextj[0];
        board[i][j]=m;
    }
    if(npos_way>1)
    {
        int l,k,exits;
        int min,ture_exit;
        for(min=7; min>0; min--)
        {
            l=npos_way;
            while(l>0)
            {
                exits=0;
                l--;
                for(k=0; k<8; k++)
                {
                    if((nexti[l]+ktmove1[k])<0||(nexti[l]+ktmove1[k])>7||(nextj[l]+ktmove2[k])<0||(nextj[l]+ktmove2[k])>7)
                        continue;
                    if(board[nexti[l]+ktmove1[k]][nextj[l]+ktmove2[k]]==0)
                        exits++;
                }
                if(exits==min)
                    ture_exit=l;
            }
        }
        i=nexti[ture_exit];
        j=nextj[ture_exit];
        board[i][j]=m;
    }
}
