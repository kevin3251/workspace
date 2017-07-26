#include <stdio.h>
#include <stdlib.h>
#include "fin.h"
void fin_initial() /*建數列的1,2項*/
{
    create_num=0;
    first=malloc(sizeof(node));
    first->num=0;
    node *temp;
    temp=malloc(sizeof(node));
    temp->num=1;
    first->next=temp;
    temp->next=first;
    cur=first;
}
void fin_create() /*當數列不足時,新增一個點*/
{
    node *temp;
    temp=malloc(sizeof(node));
    temp->num=(cur->num)+(cur->next->num);
    cur->next=temp;
    temp->next=cur;
}
void fin_exe(int n,int i) /*執行,當數列不夠時,輸出並建點,反之繼續輸出*/
{
    if(cur->next->num<cur->num&&n>1&&i!=2)
    {
        printf("%d,",cur->num);
        fin_create();
        create_num++;
        cur=cur->next;
    }
    else if(cur->next->num==cur->num&&n>1&&i==2)
    {
        printf("%d,",cur->num);
        fin_create();
        create_num++;
        cur=cur->next;
    }
    else if(n==1)
        printf("%d",cur->num);
    else
    {
        printf("%d,",cur->num);
        cur=cur->next;
    }
}
