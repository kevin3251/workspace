#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED
typedef struct ht
{
    char data[100];
    struct ht *next;
}ht;
ht *t[1024];
void ht_initial(int num);
void ht_insert(char *b);
int is_exist(char *b);
void find_eng(char *b);
extern unsigned int	hashStringCRC(const char *key);

#endif // HASH_H_INCLUDED
