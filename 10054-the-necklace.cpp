#include <iostream>
#include <string.h>

#define maxbeads 1000

using namespace std;

struct node
{
	int index;
	int color1;
	int color2;
	bool orientation;
	node* next; //adjacency list
};

node cycle[maxbeads]; //result chain of nodes

node* graph[maxbeads];
bool visited[maxbeads];

bool dfs(int n, int startnode, int k, bool orientation)
{
    cout << "DFS n= " << n << " k = " << k << " startnode = " << startnode << " orient = " << orientation << endl;
    node* currentnode = graph[startnode];
	visited[startnode]=true;
	if (orientation)
	{
		cycle[k].color1=currentnode->color1;
		cycle[k].color2=currentnode->color2;
	}
	else
	{
		cycle[k].color1=currentnode->color2;
		cycle[k].color2=currentnode->color1;
	}
	if (k==n-1)
	{
		if ((orientation) && (cycle[0].color1==cycle[k].color2)) return true;
		else if ((!orientation) && (cycle[0].color1==cycle[k].color1)) return true;
		else return false;
	}
	while(currentnode->next!=NULL)
	{
		if (visited[currentnode->next->index]) continue;
		if (graph[currentnode->next->index]->color1==currentnode->color2) dfs(n,currentnode->next->index,k+1,true);
		else dfs(n,currentnode->next->index,k+1,false);
		currentnode = currentnode->next;
		cout << "Hoi" << endl;
	}
	return false;
}

bool solve(int n, int startnode, int k, bool orientation)
{
	memset(visited,false,sizeof(bool)*maxbeads);
	return dfs(n,startnode,k,orientation);
}

void buildgraph(int n)
{
	node* fromnode;
	node* tonode;
	node* currentnode;
	for(int i=0;i<n;i++)
	{
		fromnode = graph[i];
		currentnode = fromnode;
		for(int j=0;j<n;j++)
		{
			if (i==j) continue;
			tonode = graph[j];
			if ((fromnode->color1==tonode->color1) || (fromnode->color1==tonode->color2) || (fromnode->color2==tonode->color1) || (fromnode->color2==tonode->color2))
			{
				currentnode->next = new node();
				currentnode->next->index=j;
				currentnode = currentnode->next;
				currentnode->next=NULL;
			}
		}
	}
}

void insertnode(int i, int c1,int c2)
{
	node* currentnode = graph[i];
	currentnode->color1 = c1;
	currentnode->color2 = c2;
	currentnode->orientation = true;
	currentnode->next = NULL;
}

void printresult(int n)
{
	for(int i=0;i<n;i++) cout << cycle[i].color1 << " " << cycle[i].color2 << endl;
}

void init(int n)
{
    for(int i=0;i<n;i++) graph[i] = new node();
}

void dealloc(int n)
{
    for(int i=0;i<n;i++) delete graph[i];
}

int main()
{
	int cases, n, color1, color2;
	cin >> cases;
	for(int z=1;z<=cases;z++)
	{
		cin >> n;
        init(n);
		for(int i=0;i<n;i++)
		{
			cin >> color1 >> color2;
			insertnode(i,color1,color2);
		}
		buildgraph(n);
		cout << "Case #" << z << endl;
		if ((solve(n,0,0,true)) || (solve(n,0,0,false))) printresult(n);
		else cout << "some beads may be lost" << endl;
		dealloc(n);
	}
}