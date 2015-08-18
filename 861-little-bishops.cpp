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

void setboard(int x, int y)
{
	if (board[x][y]==false) v.push_back(make_pair(x,y));
	board[x][y]=true;
}

void disablefields(int i, int j)
{
	v.clear();
	if (board[i][j]==false) v.push_back(make_pair(i,j));
	board[i][j]=true;
	int x,y;
	//Go to top-left
	x=i-1;
	y=j-1;
	while((x>=0) && (y>=0))
	{
		setboard(x,y);
		x--;
		y--;
	}
	//Go to top-right
	x=i+1;
	y=j-1;
	while((x<n) && (y>=0))
	{
		setboard(x,y);
		x++;
		y--;
	}
	//Go to bottom-left
	x=i-1;
	y=j+1;
	while((x>=0) && (y<n))
	{
		setboard(x,y);
		x--;
		y++;
	}
	//Go to bottom-right
	x=i+1;
	y=j+1;
	while((x<n) && (y<n))
	{
		setboard(x,y);
		x++;
		y++;
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

int position(int x, int y)
{
	return y*n+x;
}

bool issolution(int depth, int ipos, int jpos)
{
	if (depth==k) return true;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if ((position(i,j)>=position(ipos,jpos)) && (board[i][j]==false))
			{
				disablefields(i,j);
				vector<pair<int,int> > d(v);
				if (issolution(depth+1,i,j)) res++;
				enablefields(d);
			}
		}
	}
	return false;
}

long long solve()
{
	res=0;
	issolution(0,0,0);
	return res;
}

int main()
{
	while(1)
	{
		cin >> n >> k;
		if ((n==0) && (k==0)) break;
		memset(board,false,sizeof(board[0][0])*maxn);
		cout << solve() << endl;
	}
	return 0;
}