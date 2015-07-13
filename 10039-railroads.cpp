#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#define maxcities 100
#define maxminutesinday 1440

using namespace std;

int scenarios,ncities,starti,endi,startt;
string cities[maxcities];
unordered_map<string,int> citymap;
vector<vector<pair<int,int> > > trains;
vector<vector<pair<int,int> > > graph;
vector<vector<int> > vtimes;

int dfs(int node, int maxt)
{
	if ((node==starti) && (maxt>=startt)) return vtimes[node][maxt]=maxt;
	if (node==starti) return -1;
	if (vtimes[node][maxt]!=-1) return vtimes[node][maxt];
	int train,stop,t,nextnode;
	for(unsigned int i=0;i<graph[node].size();i++)
	{
		train = graph[node][i].first;
		stop = graph[node][i].second;
		t = trains[train][stop].first;
		if (t>maxt) continue;
		for(int j=0;j<stop;j++)
		{
			nextnode = trains[train][j].second;
			vtimes[node][t] = max(vtimes[node][t],dfs(nextnode,trains[train][j].first));
		}
		vtimes[node][maxt] = max(vtimes[node][maxt],vtimes[node][t]);
	}
	return vtimes[node][maxt];
}

int main()
{
	cin >> scenarios;
	int ntrains,nstops,t,cityi,stime,etime;
	string cityname,startc,endc;
	for(int z=1;z<=scenarios;z++)
	{
		cin >> ncities;
		citymap.clear();
		trains.clear();
		graph.clear();
		vtimes.clear();
		graph = vector<vector<pair<int,int> > >(ncities);
		vtimes = vector<vector<int> >(ncities);
		for(int i=0;i<ncities;i++)
		{
			cin >> cities[i];
			citymap[cities[i]]=i;
			vtimes[i].clear();
			for(int j=0;j<maxminutesinday;j++) vtimes[i].push_back(-1);
		}
		cin >> ntrains;
		trains = vector<vector<pair<int,int> > >(ntrains);
		for(int i=0;i<ntrains;i++)
		{
			cin >> nstops;
			for(int j=0;j<nstops;j++)
			{
				cin >> t >> cityname;
				cityi = citymap[cityname];
				trains[i].push_back(pair<int,int>((t/100)*60+t%100,cityi));
				graph[cityi].push_back(pair<int,int>(i,j));
			}
		}
		cin >> startt;
		startt = (startt/100)*60+startt%100;
		cin >> startc;
		starti = citymap[startc];
		cin >> endc;
		endi = citymap[endc];
		dfs(endi,maxminutesinday-1);
		stime=-1;
		etime=1e9;
		int train,stop,t;
		for(unsigned int i=0;i<graph[endi].size();i++)
		{
			train = graph[endi][i].first;
			stop = graph[endi][i].second;
			t = trains[train][stop].first;
			if (vtimes[endi][t]!=-1)
			{
				if ((t<etime) || (etime - stime > t - vtimes[ endi ][ t ]))
				{
					etime = t;
					stime = vtimes[endi][t];
				}
			}
		}
		cout << "Scenario " << z << endl;
		if (etime==1e9) cout << "No connection" << endl;
		else
		{
			cout << "Departure " << stime/60*100+stime%60 << " " << startc << endl;
			cout << "Arrival " << etime/60*100+etime%60 << " " << endc << endl;
		}
		if (z!=scenarios) cout << endl;
	}
	return 0;
}
