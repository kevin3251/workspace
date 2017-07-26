#include <stdio.h>
#include <stdlib.h>
#include "fin.h"
int main()
{
    char c[30];
    int num;
    fin_initial();
    while(gets(c))
    {
        sscanf(c,"take(fib,%d)",&num);
        printf("[");
        int i=0;
        while(num>0)
        {
            fin_exe(num,i);
            i++;
            num--;
        }
        printf("]create %d nodes\n",create_num);
        cur=first;
        for(num=29;num>=0;num--)
            c[num]='\0';
        create_num=0;
    }
    return 0;
}
