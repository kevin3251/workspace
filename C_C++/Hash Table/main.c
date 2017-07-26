#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include <string.h>
#include <ctype.h>
int main()
{
    ht_initial(1024);
    int i;
    char a[100],spell[100]="\0";
    FILE *cfPtr;
    if((cfPtr=fopen("ispell.words","r"))==NULL)
        printf("File could not be opened\n");
    else
    {
        while(!feof(cfPtr))
        {
            fscanf(cfPtr,"%s",a);
            ht_insert(a);
        }
        fclose(cfPtr);
    }
    while(gets(spell))
    {
        for(i=0; i<strlen(spell);i++)
            spell[i]=tolower(spell[i]);
        spell[i+1]='\0';
        if(is_exist(spell)!=0)
        {
            printf("%s:",spell);
            find_eng(spell);
            printf("\n");
        }
        else
            printf("沒有錯誤\n");
        memset(spell, '\0',100);
    }
    return 0;
}
