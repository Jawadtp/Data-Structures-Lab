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

void preorder(node *root)
{
    if(!root) return;
    printf("%d ",root->data);
    preorder(root->left);
    preorder(root->right);
}

int sumOfTree(node *root)
{
    if(!root) return 0;
    return root->data + sumOfTree(root->left) + sumOfTree(root->right);
}

int isBST(node *root, int min, int max)
{
    if(!root) return 1;
    if(root->left && root->left->data > root->data) return 0;
    if(root->right && root->right->data < root->data) return 0;
    if(root->data < min || root->data > max) return 0;
    int min1, max1;
    if(root->data > min) min1=root->data;
    int a = isBST(root->right, min1, max);
    if(root->data < max) max1=root->data;
    int b= isBST(root->left, min, max1);
    return a && b;
}

int CountSpecialBST(node *root, int k)
{
    if(!root) return 0;
    int count=0;
    if(sumOfTree(root) == k && isBST(root,INT_MIN, INT_MAX)) count++;
    count+=CountSpecialBST(root->left, k) + CountSpecialBST(root->right, k);
    return count;
}

void insert(node **root, node *x)
{
    if(!(*root))
    {
        *root=x;
        return;
    }
    if((*root)->data < x->data) return insert(&(*root)->right, x);
    else return insert(&(*root)->left, x);
}

int main()
{
 
    char s[1000];
    gets(s);
    node *root=constructTree(s);
    int k;
    scanf("%d",&k);
    int x=CountSpecialBST(root,k);
    printf("%d ",x==0?-1:x); 
    return 0;
}