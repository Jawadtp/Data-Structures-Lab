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
    node *head;
    node *tail;
}typedef queue;

queue createQueue()
{
    queue q;
    q.head=NULL;
    q.tail=NULL;
    return q;
}

node* createNode(int data)
{
    node *t = (node *)malloc(sizeof(node));
    t->data=data;
    t->left=NULL;
    t->right=NULL;
    t->next=NULL;
    return t;
}

void enqueue(queue *q, node *x)
{
    if(!q->head && !q->tail)
    {
        q->head=x;
        q->tail=x;
        return;
    }
    q->tail->next=x;
    q->tail=x;
}

node *dequeue(queue *q)
{
    if(!q->head && !q->tail) return NULL;
    node *t = q->head;
    if(q->head==q->tail)
    {
        q->head=NULL;
        q->tail=NULL;
        return t;
    }
    q->head=q->head->next;
    return t;
}

int isEmpty(queue q)
{
    return !q.head && !q.tail;
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

void HeightBalancedInsert(node **root, int arr[], int start, int end)
{
    if(start>end) return;
    int m = (start + end)/2;
    insertIntoBST(root, createNode(arr[m]));
    HeightBalancedInsert(root, arr, start, m-1);
    HeightBalancedInsert(root, arr, m+1, end);
}

void preorder(node *root)
{
    if(!root) return;
    printf("%d ",root->data);
    preorder(root->left);
    preorder(root->right);
}

char *getParanthesis(node *root)
{
    if(!root) return "( )";
    int data=root->data;
    char *left = getParanthesis(root->left);
    char *right = getParanthesis(root->right);
    char * result = (char *)malloc(100*sizeof(char));
    sprintf(result, "( %d %s %s )",data, left, right);
    return result;
}

void printLevelSums(node *root)
{
    queue q = createQueue();
    int sum=0;
    enqueue(&q, root);
    enqueue(&q, createNode(INT_MAX));
    while(1)
    {
        node *t = dequeue(&q);
        if(t->data==INT_MAX)
        {
            printf("%d ",sum);
            if(isEmpty(q)) break;
            enqueue(&q, createNode(INT_MAX));
            sum=0;
        }
        else
        {
            if(t->left) enqueue(&q, t->left);
            if(t->right) enqueue(&q, t->right);
            sum+=t->data;
           
        }    
    }
}

int main()
{
    node *root=NULL;
    int n;
    scanf("%d",&n);
    int arr[n];

    for(int i=0; i<n; i++)
        scanf("%d",&arr[i]);

    HeightBalancedInsert(&root, arr, 0, n-1);
    printf("%s\n",getParanthesis(root));
    printLevelSums(root);
       
    return 0;
}