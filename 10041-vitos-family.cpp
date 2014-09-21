#include <iostream>
#include <algorithm>

using namespace std;

#define relatives 500

int dist[relatives];
int nrelatives;

int compute(int pos)
{
    int res=0;
    for(int i=0;i<nrelatives;i++) res=res+abs(pos-dist[i]);
    return res;
}

int main()
{
    int cases;
    cin >> cases;
    for(int z=1;z<=cases;z++)
    {
        cin >> nrelatives;
        for(int i=0;i<nrelatives;i++) cin >> dist[i];
        sort(dist,dist+nrelatives);
        cout << compute(dist[nrelatives/2]) << endl;
    }
    return 0;
}
