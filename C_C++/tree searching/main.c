#include <stdio.h>
#include <stdlib.h>
#include "BST.h"
int main()
{
    int num;
    initial();
    while(scanf("%d",&num)!=EOF)
    {
        if(Search(num)!=NULL)  /*�j�M;����ۦP���Ʀr,�R�����I;�Ϥ�,���J�I */
        {
           root=DelNode(num,root,NULL);
        }
        else
            BST_first_input(num);
    }
    BST_print(root);
    return 0;
}
