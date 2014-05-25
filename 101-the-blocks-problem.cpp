#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

int** a;
int* alength;
int nblocks;

int findx(int x)
{
    for(int i=0;i<nblocks;i++)
    {
        for(int j=0;j<alength[i];j++)
        {
            if (a[i][j] == x)
            {
                return i*nblocks+j; //to separate i and j use div (i) and % (j)
            }
        }
    }
    return -1;
}

void returnupperblocks(int x)
{
    int position = findx(x);
    int i = position / nblocks;
    int j = position % nblocks;
    int t;
    for (int k=j+1;k<alength[i];k++)
    {
        t = a[i][k];
        a[i][k] = 0; //reset upper elements
        a[t][alength[t]] = t;
        alength[t]++;
    }
    alength[i]=j+1;
}

void removeblock(int x)
{
    int position = findx(x);
    int i = position / nblocks;
    int j = position % nblocks;
    a[i][j] = 0;
    alength[i]--;
}

void addblock(int x, int y) //adds block x on top of y
{
    int position = findx(y);
    int i = position / nblocks;
    a[i][alength[i]] = x;
    alength[i]++;
}

void addpile(int x, int y, bool b)
{
    int position = findx(x);
    int position2 = findx(y);
    int i = position / nblocks;
    int j = position % nblocks;
    int i2 = position2 / nblocks;
    if (i!=i2)
    {
     if (b) returnupperblocks(y);
     for(int k=j;k<alength[i];k++)
     {
        a[i2][alength[i2]] = a[i][k];
        alength[i2]++;
        a[i][k] = 0;
     }
     alength[i] = j;
    }
}

int main()
{

    if (scanf("%d\n",&nblocks)!=1) return 0;
    string line;
    string word;
    int number1, number2;
    a = new int*[nblocks];
    for(int i=0;i<nblocks;i++)
    {
        a[i] = new int[nblocks];
        for(int k=0;k<nblocks;k++) a[i][k] = 0;
        a[i][0] = i; //initialization
    }
    alength = new int[nblocks];
    for(int i=0;i<nblocks;i++) alength[i]=1;
    while(true)
    {
            cin >> word;
            if (word.compare("quit")==0)
            {
                break;
            }
            else if (word.compare("move")==0) //we do a move
            {
                cin >> number1;//word;
                cin >> word;
                if (word.compare("onto")==0) //we do a move onto
                {
                    cin >> number2;//word;
                    //Move number1 onto number 2
                    if ((number1!=number2) && ((findx(number1)/nblocks)!=(findx(number2)/nblocks)))
                    {
                        //return number1 and number2
                        returnupperblocks(number1);
                        returnupperblocks(number2);
                        removeblock(number1);
                        addblock(number1,number2);
                    }
                }
                else//we do a move over
                {
                    cin >> number2;//word;
                    //Move number2 over number2
                    if ((number1!=number2) && ((findx(number1)/nblocks)!=(findx(number2)/nblocks)))
                    {
                        returnupperblocks(number1);
                        removeblock(number1);
                        addblock(number1,number2);
                    }
                }
            }
            else if (word.compare("pile")==0)//we do a pile
            {
                cin >> number1;//word;
                cin >> word;
                if (word.compare("onto")==0) //we do a pile onto
                {
                    cin >> number2;//word;
                    //Move number1 onto number 2
                    if (number1!=number2)
                    {
                        addpile(number1, number2,true);
                    }
                }
                else//we do a pile over
                {
                    cin >> number2;//word;
                    if (number1!=number2)
                    {
                        addpile(number1, number2,false);
                    }
                }
            }
    }
    //print output
    for(int i=0;i<nblocks;i++)
    {
        cout << i << ":";
        if (alength[i]>=1)
        {
            for(int k=0;k<alength[i];k++) cout << " " << a[i][k];
        }
        cout << endl;
    }
    //clean: delete array
    for(int i=0;i<nblocks;i++)
    {
        delete[] a[i];
    }
    delete[] a;
    return 0;
}
