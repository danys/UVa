#include <iostream>
#include <string.h>

#define maxcolors 50

using namespace std;

int graph[maxcolors+1][maxcolors+1];
int degree[maxcolors+1];

void dfs(int start)
{
    for(int i=1;i<=maxcolors;i++)
    {
        if (graph[start][i]>0)
        {
            graph[start][i]--;
            graph[i][start]--;
            dfs(i);
            cout << i << " " << start << endl;
        }
    }
}

bool checkdegree()
{
    for(int i=0;i<=maxcolors;i++) if (degree[i]%2==1) return false;
    return true;
}

int main()
{
    int cases, n, color1, color2, temp;
    cin >> cases;
    for(int z=1;z<=cases;z++)
    {
        cin >> n;
        memset(degree,0,sizeof(degree));
        memset(graph,0,sizeof(graph));
        temp=-1;
        for(int i=0;i<n;i++)
        {
            cin >> color1 >> color2;
            graph[color1][color2]++;
            graph[color2][color1]++;
            degree[color1]++;
            degree[color2]++;
            if (temp==-1) temp = color1;
        }
        cout << "Case #" << z << endl;
        if (!checkdegree()) cout << "some beads may be lost" << endl;
        else dfs(temp);
        if (z!=cases) cout << endl;
    }
    return 0;
}
