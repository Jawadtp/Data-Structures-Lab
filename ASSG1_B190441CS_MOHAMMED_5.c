#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
}typedef node;

node* createNode(int data)
{
    node *t=(node *)malloc(sizeof(node));
    t->left=NULL;
    t->right=NULL;
    t->parent=NULL;
    t->data=data;
    return t;
}

int isNumber(char x) // b/w 48 and 57
{
    return x>=48 && x<=57?1:0;
}

node *constructTree(char s[])
{
    if(!strcmp(s,"( )")) return NULL;
    
    int data=0;
     int i=2;
    if(s[i]=='-') i++;
    while(isNumber(s[i]))
        data=data*10+s[i++]-'0';
    if(s[2]=='-') data=data*-1;
     

     
    int count = 0;
    i++;
    char sleft[2000]="", sright[2000]="";
    do
    {
        strncat(sleft, s+i, 1); 
        if(s[i]=='(') count++;
        else if(s[i]==')') count--;
        i++;
    } while (count);
    
    i++;
    do
    {
        strncat(sright, s+i, 1); 
        if(s[i]=='(') count++;
        else if(s[i]==')') count--;
        i++;
    } while (count);

    node *t=createNode(data);
    t->left=constructTree(sleft);
    if(t->left) t->left->parent=t;
    t->right=constructTree(sright);
    if(t->right) t->right->parent=t;
    return t;
}

node *search(node *root, int k)
{
    if(!root) return NULL;
    if(root->data==k) return root;
    if(root->data < k) return search(root->right, k);
    else return search(root->left, k);
}


node* successor(node *root, int k)
{
    node *t=search(root, k);
    if(!t) return NULL;
    if(!t->right)
    {
        while(t)
        {
            if(!t->parent) NULL;
            if(t->parent->left==t) return t->parent;
            t=t->parent;
        }    
    }
    t=t->right;
    while(t->left)
        t=t->left;
    
    return t;
}

void preorder(node *t)
{
    if(!t) return;
    printf("%d ",t->data);
    preorder(t->left);
    preorder(t->right);
}

int minValue(node *root)
{
    if(!root) return -1;
    if(root->left) return minValue(root->left);
    return root->data;
}

int kthMin(node *root, int k)
{
    if(k==1) return minValue(root);
    int x=minValue(root);
    while(k-- - 1)
    {
        node *t=successor(root, x);
        if(!t) return -1;
        x=t->data;
    }
    return x;
}
int main()
{
    char *s=(char *)malloc(2000*sizeof(char));
    gets(s);
    
    node *root=constructTree(s);
    int k;
    scanf("%d",&k);
    printf("%d\n",kthMin(root,k));
    return 0;
}
