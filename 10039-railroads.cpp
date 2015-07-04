#include <iostream>
#include <vector>
#include <utility>
#include <string>

using namespace std;

struct conn
{
	int startt;
	int endt;
};

vector<vector<pair<int,conn> > > graph;
vector<string> cities;
int scenarios,ncities,solstartt,solendt,solstarti,solendi;
vector<int> traint;
vector<int> traini;

void createNode()
{
	vector<pair<int,conn> > v;
	graph.push_back(v);
}

void insertEdge(int x, int y, int startt, int endt)
{
	vector<pair<int,conn> > v = graph[x];
	conn c;
	c.startt = startt;
	c.endt = endt;
	pair<int,conn> p(y,c);
	v.push_back(p);
	graph[x] = v;
}

void insertTrain()
{
	int startindex,endindex,starttime,endtime;
	for(int i=0;i<traint.size();i++)
	{
		for(int j=i+1;j<traint.size();j++)
		{
			startindex = traini[i];
			endindex = traini[j];
			starttime = traint[i];
			endtime = traint[j];
			insertEdge(endindex,startindex,starttime,endtime);
		}
	}
}

//O(N) city ID search
int getCityID(string citystr)
{
	for(int i=0;i<cities.size();i++)
		if (cities[i]==citystr) return i;
	return -1;
}

bool dfs(int x,int goal,int minstartt,int k,int currentendt,int currentstartt)
{
	if (k>100) return false; //avoid cycles in the graph
	if (x==goal)
	{
		if (solendt!=-1)
		{
			if (currentendt<solendt)
			{
				solstartt = currentstartt;
				solendt = currentendt;
			}
			else if (currentendt==solendt)
			{
				if (currentstartt>solstartt) solstartt = currentstartt;
			}
		}
		else
		{
			solstartt = currentstartt;
			solendt = currentendt;
		}
		return true;
	}
	bool b,ret;
	ret=false;
	vector<pair<int,conn> > v = graph[x];
	int nextnode;
	pair<int,conn> p;
	conn c;
	for(int i=0;i<v.size();i++)
	{
		p = v[i];
		nextnode = p.first;
		c = p.second;
		if ((nextnode==goal) && (c.startt<minstartt)) continue; //in case the train starts too early
		if (currentstartt<c.endt) continue;//TODO
		if (k==0) b = dfs(nextnode,goal,minstartt,k+1,c.endt,c.startt);
		else b = dfs(nextnode,goal,minstartt,k+1,currentendt,c.startt);
		if (!ret) ret = b;
	}
	//if no solution found so far => false
	return ret;
}

bool solve(int startt, int starti, int endi)
{
	return dfs(endi,starti,startt,0,-1,-1);
}

string tostrtime(int time)
{
	string s = to_string(time);
	if (time>=1000) return s;
	else return '0'+s;
}

int main()
{
	cin >> scenarios;
	int T,n,time,startt,cid,starti,endi;
	string startc,destc;
	bool unreachable;
	for(int z=1;z<=scenarios;z++)
	{
		graph.clear();
		cin >> ncities;
		cities.clear();
		string citystr;
		for(int c=1;c<=ncities;c++)
		{
			cin >> citystr;
			cities.push_back(citystr);
			createNode();
		}
		cin >> T;
		for(int t=1;t<=T;t++)
		{
			cin >> n;
			traint.clear();
			traini.clear();
			for(int i=0;i<n;i++)
			{
				cin >> time >> citystr;
				cid = getCityID(citystr);
				traini.push_back(cid);
				traint.push_back(time);
				insertTrain();
			}
		}
		cin >> startt;
		cin >> startc;
		cin >> destc;
		starti = getCityID(startc);
		endi = getCityID(destc);
		unreachable = false;
		if ((starti==-1) || (endi==-1)) unreachable=true;
		cout << "Scenario " << z << endl;
		solstartt = -1;
		solendt = -1;
		if ((!unreachable) && (solve(startt,starti,endi)))
		{
			cout << "Departure " << tostrtime(solstartt) << " " << /*cities[solstarti]*/startc << endl;
			cout << "Arrival " << tostrtime(solendt) << " " << /*cities[solendi]*/destc << endl;
		}
		else cout << "No connection" << endl;
		if (z!=scenarios) cout << endl;
	}
	return 0;
}