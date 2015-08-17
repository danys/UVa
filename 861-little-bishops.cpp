#include <iostream>
#include <string.h>
#include <vector>
#include <utility>

#define maxn 8
#define maxk 64

using namespace std;

int n,k;
bool board[maxn][maxn];
long long res;
vector<pair<int,int> > v;

void disablefields(int i, int j)
{
	v.clear();
	//if ((i<0) || (i>=n)) return;
	//if ((j<0) || (j>=n)) return;
	if (board[i][j]==false) v.push_back(make_pair(i,j));
	board[i][j]=true;
	//Go to top-left
	for(int x=i-1;x>=0;x--)
	{
		for(int y=j-1;y>=0;y--)
		{
			if (board[x][y]==false) v.push_back(make_pair(x,y));
			board[x][y]=true;
		}
	}
	//Go to top-right
	for(int x=i+1;x<n;x++)
	{
		for(int y=j-1;y>=0;y--)
		{
			if (board[x][y]==false) v.push_back(make_pair(x,y));
			board[x][y]=true;
		}
	}
	//Go to bottom-left
	for(int x=i-1;x>=0;x--)
	{
		for(int y=j+1;y<n;y++)
		{
			if (board[x][y]==false) v.push_back(make_pair(x,y));
			board[x][y]=true;
		}
	}
	//Go to bottom-right
	for(int x=i+1;x<n;x++)
	{
		for(int y=j+1;y<n;y++)
		{
			if (board[x][y]==false) v.push_back(make_pair(x,y));
			board[x][y]=true;
		}
	}
}

void enablefields(vector<pair<int,int> > &vect)
{
	for(int i=0;i<vect.size();i++)
	{
		pair<int,int> p = vect[i];
		board[p.first][p.second]=false;
	}
}

bool issolution(int depth)
{
	if (depth==k) return true;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if (!board[i][j])
			{
				disablefields(i,j);
				vector<pair<int,int> > d(v);
				if (issolution(depth+1)) res++;
				enablefields(d);
			}
		}
	}
	return false;
}

long long solve()
{
	res=0;
	issolution(0);
	return res;
}

int main()
{
	while(1)
	{
		cin >> n >> k;
		if ((n==0) && (k==0)) break;
		memset(board,false,sizeof(board));
		cout << solve() << endl;
	}
	return 0;
}