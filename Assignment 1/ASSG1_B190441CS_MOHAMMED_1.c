#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    struct Node *next;
}typedef node;


struct Queue
{
    struct Node *front;
    struct Node *back;
}typedef queue;

void enqueue(struct Queue *q, node *t)
{
    if(!q->front)
    {
        q->front=t;
        q->back=t;
        return;
    }
    q->back->next=t;
    q->back=t;
    return;
}

node *dequeue(struct Queue *q)
{
    if(!q->front) return NULL;

    node *t = q->front;
    if(q->front==q->back)
    {
        q->front=NULL;
        q->back=NULL;
        return t;
    }
    q->front=q->front->next;
    return t;
}

int isEmpty(queue *q)
{
    return !q->front?1:0;
}
node *createNode(int x)
{
    node *t=(node *)malloc(sizeof(node));
    t->data=x;
    t->left=NULL;
    t->right=NULL;
    t->next=NULL;
    return t;
}


void insert(node **root, node *t)
{
    if(!(*root))
    {
        *root=t;
        return;
    }
   queue q;
   q.front=NULL, q.back=NULL;
   node *x = *root;
   enqueue(&q, x);
   while(!isEmpty(&q))
   {
       node *temp = dequeue(&q);
       if(!temp->left) 
       {
           temp->left=t;
           return;
       }
       else
       {
           enqueue(&q, temp->left);
       }
        if(!temp->right) 
       {
           temp->right=t;
           return;
       }
       else
       {
           enqueue(&q, temp->right);
       }        
   }
}

char * getParanthesis(node *root)
{
    if(!root)
    {
        return "( )";
    }
    int data = root->data;
    char *left= getParanthesis(root->left);
    char *right=getParanthesis(root->right);
    char *str=(char *)malloc(1000*sizeof(char));
    sprintf(str,"( %d %s %s )",data,left,right);
    return str;
}

void preorder(node *root)
{
    if(!root) return;
    printf("%d ",root->data);
    preorder(root->left);
    preorder(root->right);
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
            case 'i':
            {
                scanf("%d",&x);
                insert(&root,createNode(x));
                break;
            }
            case 'p':
            {
                printf("%s\n",getParanthesis(root));
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