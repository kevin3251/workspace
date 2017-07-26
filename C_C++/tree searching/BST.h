#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED
typedef struct node
{
    int key;
    struct node* left;
    struct node* right;
}node;
node* root;
node* cur;
void initial();
node* DelNode(int num,node *cur,node *parent);
void BST_first_input(int num);
void BST_insert(node* a,int num);
node* Search(int num);
void BST_print(node* a);
#endif // BST_H_INCLUDED
