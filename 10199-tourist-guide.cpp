#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstring>

#define maxnamechars 30
#define maxlocations 110

using namespace std;

int N, R;
char names[maxlocations][maxnamechars];
unordered_map<string,int> namemap;
vector<int> graph[maxlocations];
vector<string> articulations;
bool visited[maxlocations], visited2[maxlocations];

void insert(int x,int y)
{
	graph[x].push_back(y);
	graph[y].push_back(x);
}

void dfs(int x, int forbidden, bool* v)
{
	v[x]=true;
	int next;
	for(int i=0;i<graph[x].size();i++)
	{
		next = graph[x][i];
		if ((!v[next]) && (next!=forbidden)) dfs(next,forbidden,v);
	}
}

void solve()
{
	bool loop = true;
	int counter=0;
	for(int i=0;i<N;i++)
	{
		memset(visited,false,sizeof(visited));
		dfs(i,-1,visited);
		memset(visited2,false,sizeof(visited2));
		loop = true;
		for(int j=0;j<N && loop;j++)
		{
			if ((visited[j]) && (i!=j))
			{
				dfs(j,i,visited2);
				loop = false;
			}
		}
		counter=0;
		for(int j=0;j<N;j++)
		{
			if (visited[j]!=visited2[j])
			{
					counter++;
					if (counter>1)
					{
						articulations.push_back(names[i]);
						break;
					}
			}
		}
	}
}

int main()
{
	char loc1[maxnamechars], loc2[maxnamechars];
	int index1,index2,cc;
	cc=0;
	while(1)
	{
		cc++;
		cin >> N;
		if (N==0) break;
		namemap.clear();
		for(int i=0;i<maxlocations;i++) graph[i].clear();
		articulations.clear();
		for(int i=0;i<N;i++)
		{
			cin >> names[i];
			namemap[names[i]]=i;
		}
		cin >> R;
		for(int i=0;i<R;i++)
		{
			cin >> loc1 >> loc2;
			index1 = namemap[loc1];
			index2 = namemap[loc2];
			insert(index1,index2);
		}
		solve();
		sort(articulations.begin(),articulations.end());
		if (cc>1) cout << "\n" << endl;
		cout << "City map #" << cc << ": " << articulations.size() << " camera(s) found";
		if (articulations.size()>0) cout << endl;
		for(int i=0;i<articulations.size();++i)
		{
				cout << articulations[i];
				if (i<articulations.size()-1) cout << endl;
		}
	}
	return 0;
}