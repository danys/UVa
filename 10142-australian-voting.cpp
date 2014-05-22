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
bool currentcandidates[maxcandidates];
int winners[maxcandidates];

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

double getlowestvalue()
{
    double minvalue = 100.0;
    for(int i=0;i<ncandidates;i++)
    {
        if (!currentcandidates[i]) continue;
        if (votes[i]<minvalue)
        {
            minvalue = votes[i];
        }
    }
    return minvalue;
}

void deleteentries(double value, int round)
{
    for(int i=0;i<ncandidates;i++)
    {
        if (votes[i]==value)
        {
            currentcandidates[i]=false;
            //delete ballot entry with index = i+1
            for(int l=0;l<nlines;l++)
            {
                bool f = false;
                for(int col=0;col<ncandidates-round;col++)
                {
                    if (ballot[l][col]==i+1) f=true;
                    if ((f) && (col+1<ncandidates-round)) ballot[l][col]=ballot[l][col+1];
                    else if((f) && (col+1==ncandidates-round)) ballot[l][col]=0;
                }
            }
        }
    }
}

int computewinner()
{
    bool found = false;
    int round = 0;
    int winnerindex=-1;
    for(int i=0;i<ncandidates;i++) currentcandidates[i]=true;
    while((found==false) && (round<ncandidates))
    {
        reset();
        for(int i=0;i<nlines;i++)
        {
            if (ballot[i][0]>0) votes[ballot[i][0]-1]++;
        }
        for(int i=0;i<ncandidates;i++)
        {
            votes[i]=(double)(votes[i]/(double)nlines)*100.0;
        }
        winnerindex = getwinnerindex();
        if (winnerindex!=-1) found = true;
        else
        {
            //find lowest voted candidate
            //delete that candidate
            deleteentries(getlowestvalue(),round);
        }
        round++;
    }
    return winnerindex;
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
        for(int z=1;z<=ncandidates;z++)
        {
            getline(cin,line);
            candidates[z-1] = line;
        }
        init();
        getline(cin,line); //first ballot
        int linecounter = 0;
        while(line.compare("")!=0) //do as long as line not empty
        {
            stringstream ballotstr(line);
            for(int z=1;z<=ncandidates;z++) ballotstr >> ballot[linecounter][z-1];
            linecounter++;
            getline(cin,line); //next ballot
        }
        nlines = linecounter;
        int winner = computewinner();
        if (winner!=-1) cout << candidates[winner] << endl;
        else
        {
            for(int i=0;i<ncandidates;i++)
                if (currentcandidates[i]==true) cout << candidates[i] << endl;
        }
        cout << endl;
    }
    return 0;
}
