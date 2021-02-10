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

int findLevel(node *root, int k, int level)
{
    if(root->data==k) return level;
    int x=-1;
    if(root->left) x = findLevel(root->left, k, level+1);
    if(root->right && x<0) x = findLevel(root->right, k, level+1);
    return x;
}

int printCousins(node *root, int k, int level)
{
    if(level==-1) return 0;
    if(level==0)
    {
        if((root->parent->left && root->parent->left->data==k) || (root->parent->right && root->parent->right->data==k)) return 0;
        printf("%d ",root->data);
        return 1;        
    }
    int x,y;
    if(root->left) x=printCousins(root->left, k, level-1);
    if(root->right) y=printCousins(root->right, k, level-1);
    return x==0 && y==0?0:1;
}
int main()
{
    char str[2000];
    int k;
    gets(str);
    scanf("%d",&k);
    //scanf("%[^\n]%*c %d",str,&k);
    node *root = constructTree(str);
    int x = printCousins(root, k, findLevel(root, k, 0));
    if(x==0) printf("-1");
    return 0; 
}