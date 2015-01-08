#include <iostream>
#include <string>
#include <vector>

#define maxcities 100
#define maxtrains 1000
#define maxstops 100

using namespace std;

struct station{
string city;
int time;
};

string cities[maxcities];
station times[maxtrains][maxcities];
int arrivaltimes[maxstops][maxcities];

bool solve(int earliesttime, string startcity, string endcity)
{
    return true;
}

int main()
{
    int cases, ncities, ntrains, nstops, time, earliesttime;
    string cityname, startcity, endcity;
    station st;
    cin >> cases;
    for(int z=1;z<=cases;z++)
    {
        cin >> ncities;
        for(int c=1;c<=ncities;c++) cin >> cities[c-1];
        cin >> ntrains;
        for(int t=1;t<=ntrains;t++)
        {
            cin >> nstops;
            for(int s=1;s<=nstops;s++)
            {
                cin >> time >> cityname;
                st.city = cityname;
                st.time = time;
                times[t-1][s-1]=st;
            }
        }
        cin >> earliesttime;
        cin >> startcity;
        cin >> endcity;
        cout << "Scenario " << z << endl;
        if (!solve(earliesttime,startcity,endcity)) cout << "No connection" << endl;
    }
    return 0;
}
