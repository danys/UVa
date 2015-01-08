#include <iostream>
#include <string>
#include <vector>

#define maxcities 100
#define maxtrains 1000
#define maxstops 100

using namespace std;

int ncities, ntrains;
string cities[maxcities];
int times[maxtrains][maxcities];
int arrivaltimes[maxstops][maxcities];


int main()
{
    int cases, ncities;
    cin >> cases;
    for(int z=1;z<=cases;z++)
    {
        cin >> ncities;
    }
    return 0;
}