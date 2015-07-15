#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>

#define maxnamechars 30
#define maxlocations 100

using namespace std;

struct vertex
{
	int id;
	int num;
	int low;
	bool visited;
	int parentid;
	vector<int> adjid;
	vertex(int x)
	{
		id = x;
		num = 0;
		low = 0;
		visited = false;
		parentid = -1;
		adjid = vector<int>(0);
	}
};

int N, R, counter;
char names[maxlocations][maxnamechars];
unordered_map<string,int> namemap;
vector<vertex> graph;

bool cmp(int x,int y)
{
	return (strcmp(names[x],names[y])<0);
}


set<int,bool (*)(int, int)> articulations(cmp);

void labelGraph(int x)
{
	vertex &v = graph[x];
	v.num = counter++;
	v.visited = true;
	vector<int> &vect = v.adjid;
	for(int i=0;i<vect.size();i++)
	{
		vertex &next = graph[vect[i]];
		if (!next.visited)
		{
			next.parentid = x;
			labelGraph(next.id);
		}
	}
}

void computeLows(int x)
{
	vertex &v = graph[x];
	if ((v.parentid==-1) && (v.adjid.size()>1)) articulations.insert(x);
	v.low = v.num;
	vector<int> &vect = v.adjid;
	for(int i=0;i<vect.size();i++)
	{
		vertex &next = graph[vect[i]];
		if (next.num>v.num) //forward edge
		{
			computeLows(next.id);
			if ((next.low>=v.num) && (v.adjid.size()>1)) articulations.insert(x);
			v.low = min(v.low,next.low);
		}
		else //backward edge
		{
			if (v.parentid!=next.id) v.low = min(v.low,next.num);
		}
	}
}

void insert(int x,int y)
{
	graph[x].adjid.push_back(y);
	graph[y].adjid.push_back(x);
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
		graph.clear();
		articulations.clear();
		graph = vector<vertex>();
		for(int i=0;i<N;i++)
		{
			cin >> names[i];
			namemap[names[i]]=i;
			vertex v(i);
			graph.push_back(v);
		}
		cin >> R;
		for(int i=0;i<R;i++)
		{
			cin >> loc1 >> loc2;
			index1 = namemap[loc1];
			index2 = namemap[loc2];
			insert(index1,index2);
		}
		counter=0;
		labelGraph(0);
		computeLows(0);
		cout << "City map #" << cc << ": " << articulations.size() << " camera(s) found" << endl;
		for(set<int>::iterator i=articulations.begin();i!=articulations.end();++i)	cout << names[*i] << endl;
		cout << endl;
	}
	return 0;
}