#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Node
{
    char *word;
    struct Node *next;
}typedef node;

struct List
{
    node *head;
    node *tail;
}typedef list;


node *createNode(char *word)
{
    node *t=(node *)malloc(sizeof(node));
    t->word=(char *)malloc(1000*sizeof(char));
    t->word=word;
    t->next=NULL;
    return t;
}

list *createList(node *x)
{
    list *l=(list *)malloc(sizeof(list));
    l->head=x;
    l->tail=x;
    return l;
}


void insertIntoHashtable(list* hashtable[], char *word, int index)
{
 
  if(hashtable[index]==NULL)
  {
      hashtable[index]=createList(createNode(word));
      return;
  }
    else
    {
        node *t=hashtable[index]->head;
        while(t)
        {
            if(!strcmp(t->word, word)) return;
            t=t->next;
        }
        hashtable[index]->tail->next=createNode(word);
        hashtable[index]->tail=hashtable[index]->tail->next;
        return;
    }
}

void printList(list *l)
{
    if(!l) {printf("null\n"); return;}
    while(l->head)
    {
        printf("%s", l->head->word);
        if(l->head->next) printf("-");
        l->head=l->head->next;
    }
    printf("\n");
}

int main()
{
       
    int k;
    scanf("%d\n",&k);
    
    list* hashtable[k];
    for(int i=0; i<k; i++)
        hashtable[i]=NULL;

   char s[501], word[501]="";
  
    gets(s);
    int l = strlen(s);

    for(int i=0; i<=l; i++)
    {
        if(s[i]!=' '&& i!=l)
            strncat(word,s+i,1);
        else
        {
            char *x=(char *)malloc(10*sizeof(char));
            //char x[10];
            strcpy(x, word);
             insertIntoHashtable(hashtable, x, (strlen(x)*strlen(x))%k);
             
            strcpy(word,"");
            
            
        }    
    }
    for(int i=0; i<k; i++)
    {
        printf("%d:",i);
        printList(hashtable[i]);
    }    
    return 0;
}