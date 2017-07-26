#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include <string.h>
static const unsigned int BYTE_WIDTH= 8;
// Number of bits in a byte
static const unsigned int CRC_HASH_SHIFT = 5;
// How much to shift hash by, per char hashed

static const unsigned int WORD_WIDTH = sizeof (int) * 8;
// Number of bits in a machine word (int), used
// ..by several algorithms.
unsigned int	hashStringCRC(const char *key);
// Hash a string using the fake-CRC XOR method
unsigned int hashStringCRC(		// Hash a string
    const char *key)		// Key to be hashed
{
    unsigned int hashValue = 0;
    int i = strlen(key);

    for (i=0; i<strlen(key); i++)
    {
        /*
         * The following expression could be done in one line, but it
         * would be really nasty, and a modern compiler ought to
         * generate the same code whether it's one line or several.
         * So we'll break it up to make it easier to read.
         *
         * First, we shift the value left to make room for bits from
         * the new key character.
         */
        unsigned int leftShiftedValue = hashValue << CRC_HASH_SHIFT;
        /*
         * Shifting left lost the top bits, so we have to extract and
         * position them separately with a right shift.  If we were
         * writing in assembly, we could do all of this in a single
         * rotate instruction, but C++ doesn't give us access to that
         * machine operation so we have to do it the hard way.
         */
        unsigned int rightShiftedValue =
            hashValue >> (WORD_WIDTH - CRC_HASH_SHIFT);
        /*
         * Put the shifted values together, and then XOR them with the
         * next key character (stepping past it in the process).
         */
        hashValue = (leftShiftedValue | rightShiftedValue) ^ (unsigned)*(key+i);
    }
    return hashValue;
}
void ht_initial(int num)
{
    int i;
    for(i=0;i<num;i++)
        t[i]=NULL;
}
void ht_insert(char *b)
{
    int num= hashStringCRC(b)%1024;
    ht *temp,*cur;
    if(t[num]!=NULL)
    {
        cur = t[num];
        while(cur->next!=NULL)
            cur=cur->next;
        temp=malloc(sizeof(*temp));
        strcpy(temp->data,b);
        temp->next=NULL;
        cur->next=temp;
    }
    else
    {
        temp=malloc(sizeof(*temp));
        strcpy(temp->data,b);
        temp->next=NULL;
        t[num]=temp;
    }
}
int is_exist(char *b)
{
    int i=1;
    int num =hashStringCRC(b)%1024;
    ht *cur=t[num];
    while(cur!=NULL)
    {
        if(i==0)
            break;
        i=strcmp(cur->data,b);
        cur=cur->next;
    }
    return i;
}
void find_eng(char *b)
{
    int i,j;
    char test[100];
    for(i=0;i<strlen(b);i++)
    {
        strcpy(test,b);
        for(j=97;j<=122;j++)
        {
            test[i]=j;
            if(is_exist(test)==0)
                printf("%s ",test);
        }
    }
}
