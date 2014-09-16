#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#define maxlines 100
#define maxwords 80
#define alphalen 26

string linewords[maxlines][maxwords];
char table[alphalen];
int fox[26][10];

void filltable(int i)
{
    if (i==-1) return;
    //
}

int solve(int rows)
{
    for(int i=0;i<rows;i++)
    {

    }
}

void replacelines(int knownrow)
{
    //
}

void buildfox()
{
    string str = "the quick brown fox jumps over the lazy dog";
    bool a[alphalen];
    memset(a,0,sizeof(bool)*alphalen);
    for(int i=0;i<str.length();i++)
    {

    }
}

int main()
{
    int cases;
    cin >> cases;
    cin.ignore();
    string line, word;
    stringstream ss;
    int row,col,knownrow;
    for(int z=1;z<=cases;z++)
    {
        getline(cin,line); //blank line
        row=0;
        col=0;
        while(getline(cin,line))
        {
            ss.str(line);
            while(ss >> word) linewords[row][col++] = word;
            row++;
            ss.clear();
        }
        knownrow = solve(row);
        filltable(knownrow);
        replacelines(knownrow);
    }
    return 0;
}
