#ifndef FIN_H_INCLUDED
#define FIN_H_INCLUDED
typedef struct node
{
    int num;
    struct node* next;
}node;
node* first;
node* cur;
int create_num;
void fin_initial();
void fin_create();
void fin_exe(int n,int i);
#endif // FIN_H_INCLUDED
