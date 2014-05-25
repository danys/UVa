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
int ncandid;

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
    for(int i=0;i<ncandidates;i++) votes[i]=0.0;
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
            break;
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

double gethighestvalue()
{
    double maxvalue = 0.0;
    for(int i=0;i<ncandidates;i++)
    {
        if (!currentcandidates[i]) continue;
        if (votes[i]>maxvalue)
        {
            maxvalue = votes[i];
        }
    }
    return maxvalue;
}

void deleteentries(double value)
{
    for(int i=0;i<ncandidates;i++)
    {
        if (!currentcandidates[i]) continue;
        if (votes[i]==value)
        {
            currentcandidates[i]=false;
            ncandid--;
        }
    }
}

int getnexti(int i)
{
    int j=0;
    while(currentcandidates[ballot[i][j]-1]==false) j++;
    return j;
}

int computewinner()
{
    for(int i=0;i<ncandidates;i++) currentcandidates[i]=true;
    if (nlines==0) return -1;
    ncandid = ncandidates;
    double low, high;
    int winnerindex=-1;
    while(ncandid>0)
    {
        reset();
        for(int i=0;i<nlines;i++)
        {
            if (ballot[i][getnexti(i)]>0) votes[ballot[i][getnexti(i)]-1]++;
        }
        for(int i=0;i<ncandidates;i++)
        {
            votes[i]=(double)((double)votes[i]/(double)nlines)*100.0;
        }
        winnerindex = getwinnerindex();
        low = getlowestvalue();
        high = gethighestvalue();
        if ((winnerindex!=-1) || (low==high))
        {
            break;
        }
        else
        {
            //find lowest voted candidates and delete them
            deleteentries(low);
        }
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
    getline(cin,line); //blank line
    for(int t=1;t<=T;t++)
    {
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
        if (t!=T) cout << endl;
    }
    return 0;
}
