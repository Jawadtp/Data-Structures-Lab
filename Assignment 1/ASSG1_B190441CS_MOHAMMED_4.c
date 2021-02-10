#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
}typedef node;

node* createNode(int data)
{
    node *t=(node*)malloc(sizeof(node));
    t->data=data;
    t->parent=NULL;
    t->left=NULL;
    t->right=NULL;
    return t;
}

void insert(node **root, node *prev, node *t)
{
    if(!(*root)) 
    {
        *root=t;
        (*root)->parent=prev;
        return;
    }
    if((*root)->data < t->data) return insert(&(*root)->right, *root, t);
    else return insert(&(*root)->left, *root, t);
}

void preorder(node *root)
{
    if(!root) return;
    printf("%d ",root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(node *root)
{
    if(!root) return;
    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}

void postorder(node *root)
{
    if(!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ",root->data);
}
node *search(node *root, int k)
{
    if(!root) return NULL;
    if(root->data==k) return root;
    if(root->data < k) return search(root->right, k);
    else return search(root->left, k);
}

int level(node *root, int k)
{
    int level=1;
    while(root)
    {
        if(root->data==k) return level;
        level++;
        if(root->data < k) root=root->right;
        else root=root->left;
    }
    return -1;
}

int maxValue(node *root)
{
    if(!root) return -1;
    if(root->right) return maxValue(root->right);
    return root->data;
}

int minValue(node *root)
{
    if(!root) return -1;
    if(root->left) return minValue(root->left);
    return root->data;
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

node* predecessor(node *root, int k)
{
    node *t=search(root, k);
    if(!t) return NULL;
    if(!t->left)
    {
        while(t)
        {
            if(!t->parent) return NULL;
            if(t->parent->right==t) return t->parent;
            t=t->parent;
        }
    }
    t=t->left;
    while(t->right)
        t=t->right;
    return t;    
}

void delete(node **root, int k, int type)
{
    if(!(*root)) 
    {
        if(type) printf("-1\n");
        return;
    }
    node *t=search(*root, k);
    if(!t) 
    {
        printf("-1\n");
        return;
    }
    if(type) printf("%d\n",t->data);
    if(!t->left && !t->right)
    {
        
        if(!t->parent) 
        {
            *root=NULL;
            return;
        }    
        if(t->parent->left==t)
        {
            
            t->parent->left=NULL;
            return;
        }
        else
        {
            t->parent->right=NULL;
            return;
        }
    }
    if(!t->right)
    {
        if(!t->parent)
        {
            t->left->parent=NULL;
            *root=t->left;
            return;
        }
        if(t->parent->right==t)
        {
            t->parent->right=t->left;
            return;
        }
        else
        {
            t->parent->left=t->left;
            return;
        }
        
    }
    if(!t->left)
    {
        if(!t->parent)
        {
            t->right->parent=NULL;
            *root=t->right;
            return;
        }
        if(t->parent->left==t)
        {
            t->parent->left=t->right;
            return;
        }
        else
        {
            t->parent->right=t->right;
            return;
        }
    }
    node *s=successor(*root, t->data);
    int val=s->data;
    delete(root, val, 0);
    t->data=val;
}

int main()
{
    node *root=NULL;
    int x, flag=1;
    char c;
    while(flag)
    {
        scanf("%c",&c);
        switch(c)
        {
            case 'a':
            {
                scanf("%d",&x);
                insert(&root, NULL, createNode(x));
                break;
            }
            case 'd':
            {
                scanf("%d",&x);
                delete(&root, x, 1);
                break;
            }
            case 'l':
            {
                scanf("%d",&x);
                printf("%d\n",level(root, x));
                break;
            }
            case 'm':
            {
                printf("%d\n",minValue(root));
                break;
            }
            case 'x':
            {
                printf("%d\n",maxValue(root));
                break;
            }
            case 'r':
            {
                scanf("%d",&x);
                node *t=predecessor(root, x);
                printf("%d\n",!t?-1:t->data);
                break;
            }
            case 's':
            {
                scanf("%d",&x);
                printf("%d\n",!search(root, x)?-1:1);
                break;
            }
            case 'u':
            {
                scanf("%d",&x);
                node *t=successor(root, x);
                printf("%d\n",!t?-1:t->data);
                break;
            }
            case 'i':
            {
                inorder(root);
                printf("\n");
                break;
            }
            case 'p':
            {
                preorder(root);
                printf("\n");
                break;
            }
            case 't':
            {
                postorder(root);
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