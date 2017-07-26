#include <stdio.h>
#include <stdlib.h>
#include "BST.h"
void initial() /*BST �𪺪�l��*/
{
    root=NULL;
    cur=root;
}
void BST_first_input(int num) /*�P�_�ڬO�_����NULL,�ÿ�ܤ覡���J*/
{
    if(root==NULL)
    {
        node* temp;
        temp=malloc(sizeof(node));
        temp->key=num;
        temp->left=NULL;
        temp->right=NULL;
        root=temp;
    }
    else
        BST_insert(root,num);
}
void BST_insert(node* a,int num)
{
    if(a!=NULL&&a->left==NULL&&num<a->key)
    {
        node* temp;
        temp=malloc(sizeof(node));
        temp->key=num;
        temp->left=NULL;
        temp->right=NULL;
        a->left=temp;
    }
    else if(a!=NULL&&a->right==NULL&&num>a->key)
    {
        node* temp;
        temp=malloc(sizeof(node));
        temp->key=num;
        temp->left=NULL;
        temp->right=NULL;
        a->right=temp;
    }
    else if(a!=NULL&&a->left!=NULL&&num<a->key)
        BST_insert(a->left,num);
    else if(a!=NULL&&a->right!=NULL&&num>a->key)
        BST_insert(a->right,num);
}
node* Search(int num) /*�j�M*/
{
    cur=root;
    while(cur)
    {
        if(num==cur->key)
            return cur;
        if(num<cur->key)
            cur=cur->left;
        else
            cur=cur->right;
    }
    return NULL;
}
node* DelNode(int num,node *cur,node *parent) /*�R���I; cur���n�R�����I,parent��cur��parent*/
{
    if(cur==NULL)
        return(parent);
    else
    {
        if(cur->key==num)
        {
            if(cur->left==NULL&&cur->right==NULL)
            {
                if(parent==NULL)
                {
                    free(cur);
                    return(NULL);
                }
                if(parent->left==cur)
                {
                    parent->left=NULL;
                }
                else
                {
                    parent->right=NULL;
                }
                free(cur);
                return(parent);
            }
            if(cur->left==NULL)
            {
                if(parent==NULL)
                {
                    node* temp=cur;
                    cur=cur->right;
                    free(temp);
                    return(cur);
                }
                if(parent->left==cur)
                {
                    parent->left=cur->right;
                }
                else
                {
                    parent->right=cur->right;
                }
                free(cur);
                return(parent);
            }
            if(cur->right==NULL)
            {
                if(parent==NULL)
                {
                    node* temp=cur;
                    cur=cur->left;
                    free(temp);
                    return(cur);
                }
                if(parent->left==cur)
                {
                    parent->left=cur->left;
                }
                else
                {
                    parent->right=cur->left;
                }
                free(cur);
                return(parent);
            }
            node* rchild=cur->right;
            node* rparent=cur;
            while(rchild->left!=NULL)
            {
                rparent=rchild;
                rchild=rchild->left;
            }
            cur->key=rchild->key;
            if(rparent==cur)
            {
                cur->right=rchild->right;
            }
            else
            {
                rparent->left=rchild->right;
            }
            free(rchild);
            if(parent==NULL)
            {
                return(cur);
            }
            return(parent);
        }
        else
        {
            if(num<cur->key)
            {
                DelNode(num,cur->left,cur);
                return(cur);
            }
            else
            {
                DelNode(num,cur->right,cur);
                return(cur);
            }
        }
    }
}
void BST_print(node* a)
{
    if(a!=NULL)
    {
        BST_print(a->left);
        printf("%d ",a->key);
        BST_print(a->right);
    }
}
