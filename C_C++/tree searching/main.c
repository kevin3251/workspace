#include <stdio.h>
#include <stdlib.h>
#include "BST.h"
int main()
{
    int num;
    initial();
    while(scanf("%d",&num)!=EOF)
    {
        if(Search(num)!=NULL)  /*搜尋;當找到相同的數字,刪除該點;反之,插入點 */
        {
           root=DelNode(num,root,NULL);
        }
        else
            BST_first_input(num);
    }
    BST_print(root);
    return 0;
}
