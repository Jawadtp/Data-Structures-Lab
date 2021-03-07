#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
}typedef node;

node* createNode(int data)
{
    node *t = (node *)malloc(sizeof(node));
    t->data=data;
    t->left=NULL;
    t->right=NULL;
    return t;
}

int isNumber(char x) //b/w 48 & 57
{
    return x>=48 && x<=57;
}

node* getTree(char parRep[])
{
    if(!strcmp(parRep, "( )")) return NULL;
    char left[1000]="";
    char right[1000]="";
    int i=2;
    if(parRep[i]=='-') i++;
    int data=0;

    while(isNumber(parRep[i]))
        data=data*10+parRep[i++]-'0';

    data=parRep[2]=='-'?data*-1:data;
    i++;
    int count=0;
    do
    {
        strncat(left, parRep+i, 1);
        if(parRep[i]=='(') count++;
        if(parRep[i++]==')') count--;
    } while (count);

    i++;
    do
    {
        strncat(right, parRep+i, 1);
        if(parRep[i]=='(') count++;
        if(parRep[i++]==')') count--;
    } while (count);

    node *leftnode=getTree(left);
    node *rightnode=getTree(right);
    node *t=createNode(data);
    t->left=leftnode;
    t->right=rightnode;
   return t;
}

void inorder(node *root)
{
    if(!root) return;
    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}

int getMax(int a, int b)
{
    return a>b?a:b;
}

int getSuccessor(node *root, int k)
{
    int successor=INT_MAX;
    
   while(root && root->data!=k)
   {
       successor=root->data >= k && root->data < successor?root->data:successor;
       if(root->data < k) root=root->right;
       else root=root->left;
   }

   if(!root) return -1;

   if(root->right) 
   {
       root=root->right;
        while(root->left)
            root=root->left;
       return root->data;     
   }
    return successor==INT_MAX?root->data:successor;
}

int getPredecessor(node *root, int k)
{
    int predecessor=INT_MIN;

   while(root && root->data!=k)
   {
       predecessor=root->data <= k && root->data > predecessor?root->data:predecessor;
       if(root->data < k) root=root->right;
       else root=root->left;
   }

   if(!root) return -1;

   if(root->left) 
   {
       root=root->left;
        while(root->right)
            root=root->right;
       return root->data;     
   }

    return predecessor==INT_MIN?root->data:predecessor;
}

int kthLargest(node *root, int k)
{
    node *t=root;

    while (root->right)
        root=root->right;

    int x=root->data;


    while(k-- - 1)
    {
        if(getPredecessor(t,x)==x) return -1;
        x=getPredecessor(t,x);       
    }
    return x;    
}

int kthSmallest(node *root, int k)
{
    node *t=root;

    while (root->left)
        root=root->left;

    int x=root->data;

    while(k-- - 1)
    {
        if(getSuccessor(t,x)==x) return -1;
        x=getSuccessor(t,x);       
    }
    return x;    
}

int main()
{
    char s[1000];
    gets(s);
    node *t =getTree(s);
    char c;
    int flag = 1, x;

    while(flag)
    {
        scanf("%c",&c);
        switch(c)
        {
            case 'r':
            {
                scanf("%d",&x);
                printf("%d\n",getPredecessor(t, x));
                break;
            }
            case 'u':
            {
                scanf("%d",&x);
                printf("%d\n",getSuccessor(t, x));
                break;
            }
            case 'l':
            {
                scanf("%d",&x);
                printf("%d\n",kthLargest(t, x));
                break;
            }
            case 's':
            {
                scanf("%d",&x);
                printf("%d\n",kthSmallest(t,x));
                break;
            }
            case 'i':
            {
                inorder(t);
                printf("\n");
                break;
            }
            case 'e':
            {
                flag=0;
                break;
            }
        }
    }
    return 0;
}