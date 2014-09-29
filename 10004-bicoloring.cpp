#include <iostream>
#include <vector>

#define maxnodes 200

using namespace std;

struct Node
{
    vector<int> nodes;
    int color;
    bool visited;
};

Node graph[maxnodes];

bool solve(int n, int nedges, int startnode, bool color)
{
    if (graph[startnode].visited) return true;
    graph[startnode].color = color;
    graph[startnode].visited = true;
    for(unsigned int i=0;i<graph[startnode].nodes.size();i++)
    {
        if ((graph[graph[startnode].nodes[i]].visited) && (graph[graph[startnode].nodes[i]].color != !color)) return false;
        if (!solve(n,nedges,graph[startnode].nodes[i],!color)) return false;
    }
    return true;
}

void init(int n)
{
    for(int i=0;i<n;i++) graph[i].nodes.clear();
}

int main()
{
    int n, nedges, e1, e2;
    while((cin >> n) && (n!=0))
    {
        cin >> nedges;
        init(n);
        for(int i=0;i<nedges;i++)
        {
            cin >> e1;
            cin >> e2;
            graph[e1].nodes.push_back(e2);
            graph[e2].nodes.push_back(e1);
            graph[e1].color = -1;
            graph[e2].color = -1;
            graph[e1].visited = false;
            graph[e2].visited = false;
        }
        if (solve(n,nedges,0,0)) cout << "BICOLORABLE." << endl;
        else cout << "NOT BICOLORABLE." << endl;
    }
}
