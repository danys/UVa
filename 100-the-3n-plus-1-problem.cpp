#include <stdio.h>

using namespace std;

int ncycles(int i)
{
    int counter=1;
    while (i!=1)
    {
        if (i%2==1) i=3*i+1;
        else i=i/2;
        counter++;
    }
    return counter;
}

int main()
{
    int i=0;
    int j=0;
    int nmax=0;
    int itemp=0;
    int jtemp=0;
    int temp=0;
    while(scanf("%d %d \n",&i,&j)==2)
    {
        if (i>j)
        {
            itemp=j;
            jtemp=i;
        }
        else
        {
            itemp=i;
            jtemp=j;
        }
        nmax = 0;
        for(int k=itemp;k<=jtemp;k++)
        {
            temp=ncycles(k);
            if (temp>nmax) nmax=temp;
        }
        printf("%d %d %d\n",i,j,nmax);
    }
    return 0;
}
