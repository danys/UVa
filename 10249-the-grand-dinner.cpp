#include <iostream>
#include <vector>
#include <string.h>

#define maxmembers 100

using namespace std;

unsigned int M, N; //number of teams and number of tables
vector<int> team;
vector<int> table;
vector<vector<int> > sol;
bool available[maxmembers];
int maxteamsize;

//O(N) table search
int maxtindex()
{
    int index=-1;
    for(unsigned int i=0;i<table.size();i++)
    {
        if (available[i])
        {
            index=i;
            break;
        }
    }
    if (index==-1) return -1;
    for(unsigned int i=0;i<table.size();i++) if ((table[i]>table[index]) && (available[i])) index=i;
    return index;
}

bool solve()
{
    int maxt;
    unsigned int i=0;
    if (maxteamsize>N) return false;
    memset(available,true,sizeof(available));
    while((i<M) && (team[i]>0))
    {
        maxt = maxtindex();
        if (maxt==-1) return false;
        if (table[maxt]<1) return false;
        available[maxt]=false;
        team[i]--;
        table[maxt]--;
        if (i<sol.size())
        {
            vector<int> v=sol[i];
            v.push_back(maxt+1);
            sol[i]=v;
        }
        else
        {
            vector<int> v;
            v.push_back(maxt+1);
            sol.push_back(v);
        }
        if (team[i]==0)
        {
            i++;
            memset(available,true,sizeof(available));
        }
    }
    return true;
}

void printsol()
{
    cout << "1" << endl;
    for(unsigned int i=0;i<sol.size();i++)
    {
        vector<int> v = sol[i];
        for(unsigned int j=0;j<v.size();j++)
        {
            cout << v[j];
            if (j!=v.size()-1) cout << " ";
        }
        cout << endl;
    }
}

int main()
{
    int in;
    while(1)
    {
        cin >> M >> N;
        if ((M==0) && (N==0)) break;
        team.clear();
        table.clear();
        sol.clear();
        maxteamsize=-1;
        for(unsigned int z=1;z<=M;z++)
        {
            cin >> in;
            if (in>maxteamsize) maxteamsize=in;
            team.push_back(in);
        }
        for(unsigned int z=1;z<=N;z++)
        {
            cin >> in;
            table.push_back(in);
        }
        if (solve()) printsol();
        else cout << "0" << endl;
    }
    return 0;
}