#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
}typedef node;

node *createNode(int x)
{
    node *t=(node *)malloc(sizeof(node));
    t->data=x;
    t->left=NULL;
    t->right=NULL;
    return t;
}

void insertIntoBST(node **root, node *x)
{
    if(!(*root))
    {
        *root=x;
        return;
    }
    node *t=*root;
    if(t->data < x->data)
    {
        if(t->right) insertIntoBST(&(t->right), x);
        else t->right=x;
        return;
    }
    else
    {
        if(t->left) insertIntoBST(&(t->left), x);
        else t->left=x;
        return;
    }
}

void preorder(node *root)
{
    if(!root) return;
    printf("%d ",root->data);
    preorder(root->left);
    preorder(root->right);
}

int getPath(node *root, int x, int arr[])
{
    int i=0;
    while(1)
    {
        arr[i++]=root->data;
        if(root->data==x) return i;
        if(x<root->data) 
            root=root->left;
        else root=root->right;
               
    }
}

int maxInPath(node *root, int a, int b)
{
    int Ap[100], Bp[100];
    for(int i=0; i<100; i++)
    {
        Bp[i]=-99999;
        Ap[i]=-99999;
    }

    int check=0;
    if(a==root->data || b==root->data) check=1;
    
    int n1=getPath(root, a, Ap);
    int n2=getPath(root, b, Bp);
 

    int i=0;
    
    int commonAnscestor;
    while(1)
    {
        if(Ap[i]!=Bp[i]) break;
        i++;
    }
    commonAnscestor=Ap[i-1];
    if(Ap[i]==-99999|| Bp[i]==-99999) check=1;

    int maxvalue=-99999;
    if(Ap[i]>Bp[i])
    {
        for(int j=i; j<n1-1; j++)
            maxvalue=maxvalue>Ap[j]?maxvalue:Ap[j];
    }
    else
    {
        for(int j=i; j<n2-1; j++)
            maxvalue=maxvalue>Bp[j]?maxvalue:Bp[j];
    }
    if(check) return maxvalue;
    return maxvalue>commonAnscestor?maxvalue:commonAnscestor;
}

int main()
{
    node *root=NULL;
    
   char c;
   int x;
   for(int i=0; c!='\n'; i++)
   {
       scanf("%d%c", &x, &c);
       insertIntoBST(&root, createNode(x));
   } 
   int a, b;
   scanf("%d %d",&a, &b);
   printf("%d",maxInPath(root, a, b));
    return 0;
}