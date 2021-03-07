#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Node
{
    char *word;
    struct Node *next;
}typedef node;

node *createNode(char *word)
{
    node *t=(node *)malloc(sizeof(node));
    t->word=word;
    t->next=NULL;
    return t;
}

int getPower(char *word)
{
    int p=0;
    int arr[8]={0};
    
    for(int i=0; i<strlen(word); i++)
    {
        if(!arr[word[i]-'a'])
        {
            p+=pow(2,word[i]-'a');
            arr[word[i]-'a']=1;
        }
    }
    return p;    
}

int compareWordsLexicographically(char *word0, char *word1)
{
    int i=0;
    int l0 =strlen(word0), l1=strlen(word1);

    while(1)
    {
        if(i>=l0) return 0;
        if(i>=l1) return 1;
        if(word0[i]<word1[i])
            return 0;
        else if(word0[i]>word1[i]) return 1;
        i++;    
    }

    return -1;
}

void insertIntoHashtable(node *list[], char *word)
{
    int index=getPower(word);

    if(!list[index])
    {
        list[index]=createNode(word);
        return;
    }

    else
    {
        node *head=list[index];
        node *t=createNode(word);

        if(compareWordsLexicographically(word, list[index]->word)==0)
        {
            t->next=list[index];
            list[index]=t;
            return;
        }
        
        while(head && head->next)
        {
            if(compareWordsLexicographically(word, head->word) && !compareWordsLexicographically(word, head->next->word))
            {
                t->next=head->next;
                head->next=t;
                return;
            }
            head=head->next;
        }
        head->next=t;
    }
}

void printList(node *head)
{
    if(!head) return;
    while(head)
    {
        printf("%s ",head->word);
        head=head->next;
    }
    printf("\n");
}

int main()
{
    node *list[255];
    for(int i=0; i<255; i++)
        list[i]=NULL;
      
    int n;
    scanf("%d",&n); 

    for(int i=0; i<n; i++) 
    {
        char *word = (char *)malloc(51*sizeof(char));
        scanf("%s",word);
        insertIntoHashtable(list, word);
    }    

    for(int i=0; i<=255; i++)
        printList(list[i]);

    return 0;
}

