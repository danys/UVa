#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#define maxlines 1000
#define maxcandidates 20

int ncandidates, nlines;
string candidates[maxcandidates];
int ballot[maxlines][maxcandidates];
double votes[maxcandidates];
vector maxindex;

void init()
{
    for(int i=0;i<maxlines;i++)
    {
        for(int j=0;j<maxcandidates;j++)
        {
            ballot[i][j]=0;
        }
    }
}

void reset()
{
    for(int i=0;i<ncandidates;i++) votes[i]=0;
}

int getwinnerindex()
{
    int winnerindex=-1;
    int nwinners=0;
    for(int i=0;i<ncandidates;i++)
    {
        if (votes[i]>50.0)
        {
            winnerindex = i;
            nwinners++;
        }
    }
    return (nwinners==1)? winnerindex : -1;
}



int computewinner()
{
    bool found = false;
    int round = 0;
    while((found==false) && (round<ncandidates))
    {
        reset();
        for(int i=0;i<nlines;i++)
        {
            votes[ballot[i][0]-1]++;
        }
        for(int i=0;i<ncandidates;i++)
        {
            votes[i]=(double)(votes[i]/(double)nlines)*100.0;
        }
        getwinnerindex()
        round++;
    }
}

int main()
{
    int T;
    string line;
    getline(cin,line);
    stringstream sstr(line);
    sstr >> T;
    for(int t=1;t<=T;t++)
    {
        getline(cin,line); //blank line
        getline(cin,line); //number of candidates
        stringstream nstr(line);
        nstr >> ncandidates;
        for(int z=1;z<=ncandidates);z++)
        {
            getline(cin,line);
            candidates[z-1] = line;
        }
        init();
        getline(cin,line); //first ballot
        stringstream ballotstr(line);
        int linecounter = 0;
        while(line.compare("")!=0) //do as long as line not empty
        {
            for(int z=1;z<=ncandidates;z++) line >> ballot[linecounter][z-1];
            linecounter++;
            getline(cin,line); //next ballot
            stringstream bstr(line);
        }
        nlines = linecounter;
    }
    return 0;
}
