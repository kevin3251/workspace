#include <stdio.h>
#include <stdlib.h>
#include "fin.h"
void fin_initial() /*�ؼƦC��1,2��*/
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
void fin_create() /*��ƦC������,�s�W�@���I*/
{
    node *temp;
    temp=malloc(sizeof(node));
    temp->num=(cur->num)+(cur->next->num);
    cur->next=temp;
    temp->next=cur;
}
void fin_exe(int n,int i) /*����,��ƦC������,��X�ë��I,�Ϥ��~���X*/
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
