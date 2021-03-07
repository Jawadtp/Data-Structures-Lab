#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int isPrime(int x)
{
    for(int i=2; i<=sqrt(x); i++)
    {
        if(!(x%i)) return 0;
    }
    return 1;
}

int getLargestPrime(int m)
{
    for(int i=m-1; i>=0; i--)
        if(isPrime(i)) return i;
    return -1;    
}

void insertIntoHashtable(int hashtable[], int m, int k, int c1, int c2, int P, int type)
{
    int h;
    for(int i=0; i<m; i++)
    {
        
        h = type?((k%m) + i*(P- (k%P)))%m:((k%m) + c1*i + c2*i*i)%m;
        if(hashtable[h]==INT_MAX)
        {
            hashtable[h]=k;
            return;
        }
    }
}

int searchHashtable(int hashtable[], int m, int k, int c1, int c2, int P, int type)
{
    int h;
    for(int i=0; i<m; i++)
    {
        
        h = type?((k%m) + i*(P- (k%P)))%m:((k%m) + c1*i + c2*i*i)%m;
        if(hashtable[h]==k) return 1;
    }
    return -1;
}

void deleteFromHashtable(int hashtable[], int m, int k, int c1, int c2, int P, int type)
{
    int h;
    for(int i=0; i<m; i++)
    {
        h = type?((k%m) + i*(P- (k%P)))%m:((k%m) + c1*i + c2*i*i)%m;
        if(hashtable[h]==k) 
        {
            hashtable[h]=INT_MAX;
            return;
        }    
    }
    
}

void printKeyValuePair(int hastable[], int m)
{
    for(int i=0; i<m; i++)
    {
        printf("%d ", i);
        hastable[i]==INT_MAX?printf("()\n"):printf("(%d)\n",hastable[i]);
    }    
}

int main()
{
    
    
    char c, l;
    int m, h, c1, c2, k, flag=1;
    int p;
    scanf("%c %d",&c,&m);
    if(c=='a') scanf("%d %d",&c1, &c2);
    else p=getLargestPrime(m);

    int hashtable[m];
    
    for(int i=0; i<m; i++)
        hashtable[i]=INT_MAX;
    
    
    while(flag)
    {
        scanf("%c",&l);
        switch(l)
        {
            case 'i':
            {
                scanf("%d",&k);
                insertIntoHashtable(hashtable, m, k, c1, c2, p, c=='a'?0:1);
                //else if(c=='b') 
                break;
            }
            case 's':
            {
                scanf("%d",&k);
                printf("%d\n",searchHashtable(hashtable, m, k, c1, c2, p, c=='a'?0:1));
                break;
            }
            case 'd':
            {
                scanf("%d",&k);
                deleteFromHashtable(hashtable, m, k, c1, c2, p, c=='a'?0:1);
                break;
            }
            case 'p':
            {
                printKeyValuePair(hashtable, m);
                break;
            }
            case 't':
            {
                flag=0;
                break;
            }
        }
    }

    
    return 0;
}