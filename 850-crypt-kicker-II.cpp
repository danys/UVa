#include <iostream>
#include <string>
#include <sstream>
#include <string.h>

using namespace std;

#define maxlines 100
#define maxwords 80
#define alphalen 26


char table[alphalen];

string lines[maxlines];
string linewords[maxlines][maxwords];
int linewordsnwords[maxlines];
int linewordswordlen[maxlines][maxwords];

string foxstr = "the quick brown fox jumps over the lazy dog";
int fox[maxwords][maxwords]; //stores char information about the known sentence
int foxlen[maxwords]; //stores length of second dimension of fox
int foxlen1; //stores length of first dimension of fox
int foxnwords;
int foxwordlen[maxwords];

bool filltable(int i)
{
    if (i==-1) return false;
    memset(table,-1,sizeof(char)*alphalen);
    for(unsigned int j=0;j<lines[i].length();j++)
    {
        if (foxstr[j]==' ') continue;
        if ((table[lines[i][j]-'a']!=-1) && (table[lines[i][j]-'a']!=foxstr[j])) return false;
        table[lines[i][j]-'a']=foxstr[j];
    }
    int t[alphalen];
    memset(t,0,sizeof(int)*alphalen);
    for(int j=0;j<alphalen;j++)
    {
        t[table[j]-'a']++;
        if (t[table[j]-'a']>1) return false;
    }
    return true;
}

bool ismatch(int i)
{
    if (linewordsnwords[i]!=foxnwords) return false;
    for(int j=0;j<foxnwords;j++) if (foxwordlen[j]!=linewordswordlen[i][j]) return false;
    char c;
    for(int d1=0;d1<foxlen1;d1++)
    {
        c = 0;
        if (foxlen[d1]<=1) continue;
        for(int d2=0;d2<foxlen[d1];d2++)
        {
            if (d2==0) c = lines[i][fox[d1][0]];
            else if (lines[i][fox[d1][d2]]!=c) return false;
        }
    }
    return filltable(i);
}

string replacestr(int i)
{
    string s = lines[i];
    for(unsigned int j=0;j<s.length();j++) if(s[j]!=' ') s[j]=table[s[j]-'a'];
    return s;
}

int solve(int rows)
{
    for(int i=0;i<rows;i++) if (ismatch(i)) return i;
    return -1;
}

void replacelines(int rows,int r)
{
    if (r==-1) cout << "No solution." << endl;
    else
    {
        for(int i=0;i<rows;i++)
        {
          if (i==r) cout << "the quick brown fox jumps over the lazy dog" << endl;
          else cout << replacestr(i) << endl;
        }
    }
}

void buildfox()
{
    string str = foxstr;
    int a[maxwords][maxwords];
    int len[maxwords];
    int currentlen=0;
    bool used[alphalen];
    memset(a,-1,sizeof(bool)*maxwords*maxwords);
    memset(len,0,sizeof(int)*maxwords);
    memset(used,0,sizeof(bool)*alphalen);
    memset(foxlen,0,sizeof(int)*maxwords);
    for(unsigned int i=0;i<foxstr.length();i++) if (foxstr[i]!=' ') a[foxstr[i]-'a'][len[foxstr[i]-'a']++]=i;
    foxlen1=0;
    foxnwords=0;
    for(unsigned int i=0;i<foxstr.length();i++)
    {
        if (used[foxstr[i]-'a']) {currentlen++;continue;}
        if (foxstr[i]==' ')
        {
            foxwordlen[foxnwords]=currentlen;
            foxnwords++;
            currentlen=0;
        }
        else
        {
            currentlen++;
            for(int j=0;j<len[foxstr[i]-'a'];j++)
            {
                if (a[foxstr[i]-'a'][j]==-1) break;
                fox[i][j]=a[foxstr[i]-'a'][j];
            }
            used[foxstr[i]-'a']=true;
            foxlen[i]=len[foxstr[i]-'a'];
        }
    }
    foxwordlen[foxnwords]=currentlen;
    foxlen1 = foxstr.length();
    foxnwords++;
}

int main()
{
    int cases;
    cin >> cases;
    cin.ignore();
    string line, word;
    stringstream ss;
    int row,col;
    buildfox();
    getline(cin,line); //blank line
    for(int z=1;z<=cases;z++)
    {
        row=0;
        while(getline(cin,line))
        {
            if (line.empty()) break;
            ss.str(line);
            lines[row] = line;
            col=0;
            while(ss >> word)
            {
                linewords[row][col++] = word;
                linewordswordlen[row][col-1] = word.length();
            }
            linewordsnwords[row]=col;
            row++;
            ss.clear();
        }
        replacelines(row,solve(row));
        if (z!=cases) cout << endl;
    }
    return 0;
}

