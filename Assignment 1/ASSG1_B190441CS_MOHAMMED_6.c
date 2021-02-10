#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
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

void preorder(node *root)
{
    if(!root) return;
    printf("%d ",root->data);
    preorder(root->left);
    preorder(root->right);
}

void specialInsert(int a[], int start, int end, node **root)
{
    if(start>end) return;
    int mid = (start+end)/2;
    insert(root, createNode(a[mid]));
    specialInsert(a, start, mid-1, root);
    specialInsert(a, mid+1, end, root);
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

void displayLevelsum(node *root)
{
    if(!root) return;
    queue q;
    q.front=root;
    q.back=root;
    enqueue(&q, createNode(-99999));
    int sum=0;
   
   
    while(1)
    {
        node *t=dequeue(&q);
        if(t->data==-99999)
        {
            printf("%d ", sum);
            sum=0;
            if(isEmpty(&q)) return;
            enqueue(&q, createNode(-99999));
        }
        else
        {
            sum+=t->data;
            if(t->left) enqueue(&q, t->left);
            if(t->right) enqueue(&q, t->right);
        }
    }
}
int main()
{
    /*
    int a[]={18,20,24,30,36,50,51};
    node *root=NULL;
    insert(&root, createNode(10));
    insert(&root, createNode(15));
    insert(&root, createNode(5));

    node *root2=NULL;
    specialInsert(a,0,6,&root2);
    //printf("%s\n",getParanthesis(root2));
    displayLevelsum(root2);
*/

    int n;
    scanf("%d",&n);
    int a[n];
    for(int i=0; i<n; i++)
        scanf("%d", &a[i]);

    node *root=NULL;
    specialInsert(a,0,n-1,&root);
    printf("%s\n",getParanthesis(root));
    displayLevelsum(root);    
    //preorder(root2);
/*
    queue q;
    node *t=createNode(1);
    q.front=t;
    q.back=t;
    //enqueue(&q, createNode(1));
    enqueue(&q, createNode(2));
    enqueue(&q, NULL);
    printf("Hey");
    enqueue(&q, createNode(3));
    printf("%d ",dequeue(&q)->data);
    //printf("%d ",dequeue(&q)->data);
    //dequeue(&q);
    //printf("%d ",dequeue(&q)->data); */
    return 0;
}