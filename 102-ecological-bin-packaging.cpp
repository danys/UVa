#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>

using namespace std;

const int length = 9;

int convert(char x)
{
    if (x=='B') return 0;
    else if(x=='G') return 1;
    else if (x=='C') return 2;
    else return -1;
}

int bottlemoves(int* a,int colorb1,int colorb2,int colorb3)
{
    int ab1 = colorb1;
    int ab2 = colorb2+(length/3);
    int ab3 = colorb3+(length/3)*2;
    int nmoves = 0;
    for (int i=0;i<length;i++) if((i!=ab1)&&(i!=ab2)&&(i!=ab3)) nmoves += a[i];
    return nmoves;
}

int main()
{
    int a[length];
    for(int i=0;i<length;i++) a[i]=0;
    string line;
    int combination, maxmoves, temp;
    char combinations[6][4] = {"GCB","GBC","CGB","CBG","BGC","BCG"};
    while(getline(cin,line))
    {
        combination=0;
        stringstream s(line);
        for(int i=0;i<length;i++) s >> a[i];
        int maxmoves = bottlemoves(a,convert(combinations[0][0]),convert(combinations[0][1]),convert(combinations[0][2]));
        for (int i=1;i<6;i++)
        {
            temp = bottlemoves(a,convert(combinations[i][0]),convert(combinations[i][1]),convert(combinations[i][2]));
            if (temp<=maxmoves)
            {
                maxmoves = temp;
                combination=i;
            }
        }
        printf("%c%c%c %d\n",combinations[combination][0],combinations[combination][1],combinations[combination][2],maxmoves);
    }
    return 0;
}
