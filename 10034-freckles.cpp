#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <math.h>

#define maxfreckles 100

using namespace std;

struct node
{
	int index;
	double x;
	double y;
	double weight;
	node* next;
};

struct graph
{
	int nnodes=0;
	int nedges=0;
	node* nodes[maxfreckles];
};

struct edge
{
	int node1;
	int node2;
	double weight;
};

struct unionfind
{
	int nsets;
	int parent[maxfreckles];
	int nnodessub[maxfreckles];
};

graph g;
vector<edge> edges;
unionfind uf;

int findroot(int i)
{
	while(uf.parent[i]!=i)	i=uf.parent[i];
	return i;
}

bool differentcomponents(int i,int j)
{
	return (findroot(i)!=findroot(j));
}

void merge(int i, int j)
{
	int rooti = findroot(i);
	int rootj = findroot(j);
	if (rooti==rootj) return;
	if (uf.nnodessub[rooti]>uf.nnodessub[rootj])
	{
		uf.parent[rooti] = rootj;
		uf.nnodessub[rootj] = uf.nnodessub[rootj]+uf.nnodessub[rooti];
	}
	else
	{
		uf.parent[rootj] = rooti;
		uf.nnodessub[rooti] = uf.nnodessub[rooti]+uf.nnodessub[rootj];
	}
}

bool compare(edge e1, edge e2)
{
	return (e1.weight<=e2.weight);
}

//Kruskal's algorithm for building minimum spanning trees
double solve(int n)
{
	sort(edges.begin(),edges.end(),compare);
	double result = 0;
	for(unsigned int i=0;i<edges.size();i++)
	{
		if (differentcomponents(edges[i].node1,edges[i].node2))
		{
			result = result + edges[i].weight;
			merge(edges[i].node1,edges[i].node2);
		}
	}
	return result;
}

//Computes the distance between two points in two dimensions
double distance(double x1,double y1, double x2, double y2)
{
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void insert(double x, double y)
{
	node* currentnode = g.nodes[g.nnodes];
	currentnode = new node();
	currentnode->x=x;
	currentnode->y=y;
	currentnode->weight=-1;
	currentnode->index=g.nnodes;
	currentnode->next=NULL;
	g.nodes[g.nnodes]=currentnode;
	g.nnodes++;
}

//Build a full mesh graph
void fullmesh(int n)
{
	node* startnode;
	node* endnode;
	double weight;
	edge e;
	for(int i=0;i<n;i++)
	{
		startnode = g.nodes[i];
		for(int j=0;j<n;j++)
		{
			endnode = g.nodes[j];
			if (i==j) continue;
			weight = distance(startnode->x,startnode->y,endnode->x,endnode->y);
			if (i<j)
			{
			    e.weight=weight;
				e.node1 = i;
				e.node2 = j;
				edges.push_back(e);
				g.nedges++;
            }
		}
	}
}

void init(int n)
{
	g.nnodes = 0;
	g.nedges = 0;
	for(int i=0;i<n;i++) g.nodes[i]=NULL;
	edges.clear();
	uf.nsets = n;
	for(int i=0;i<n;i++)
	{
		uf.parent[i]=i;
		uf.nnodessub[i]=1;
	}
}

void deallocate(int n)
{
    node* currentnode;
    for(int i=0;i<n;i++)
    {
        currentnode = g.nodes[i];
        delete currentnode;
        currentnode=0;
    }
}

int main()
{
	int cases, nfreckles=0;
	double x, y;
	cin >> cases;
	string line;
	for(int z=1;z<=cases;z++)
	{
		getline(cin,line);
		cin.ignore();
		cin >> nfreckles;
		init(nfreckles);
		for(int i=0;i<nfreckles;i++)
		{
			cin >> x >> y;
			insert(x,y);
		}
		fullmesh(nfreckles);
		cout << fixed;
        cout.precision(2);
		cout << solve(nfreckles) << endl;
		if (z!=cases) cout << endl;
		deallocate(nfreckles);
	}
}
