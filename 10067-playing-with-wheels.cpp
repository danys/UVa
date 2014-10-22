#include <iostream>
#include <string>
#include <string.h>
#include <queue>

#define maxnumbers 10000

using namespace std;

int start,target;
bool visited[maxnumbers];
int len[maxnumbers];
queue<int> q;

int power10(int x)
{
   if (x==1) return 10;
   if (x==2) return 100;
   if (x==3) return 1000;
   return 1;
}

int tonumber(int a[4])
{
   int res=0;
   for(int i=3;i>=0;i--) res += a[3-i]*power10(i);
   return res;
}

void toarray(int n, int (&a)[4])
{
   for(int i=0;i<4;i++)
   {
      a[3-i]=n%10;
      n /= 10;
   }
}

int readnumber()
{
   int a[4];
   for(int i=0;i<4;i++) cin >> a[i];
   return tonumber(a);
}

int extractdigit(int n,int index)
{
   for(int i=0;i<3-index;i++) n=n/10;
   return n%10;
}

int nextnumber(int n, int index, bool up)
{
   int t=extractdigit(n,index);
   if (up)
   {
      t += 1;
      t %= 10;
   }
   else
   {
      t -= 1;
      if (t==-1) t=9;
   }
   int a[4];
   toarray(n,a);
   a[index]=t;
   return tonumber(a);
}

void clearq(queue<int> &q)
{
    queue<int> newq;
    swap(q,newq);
}

bool bfs()
{
   int current=start;
   int next;
   memset(len,0,sizeof(int)*maxnumbers);
   if (current==target) return true;
   clearq(q);
   q.push(start);
   while(!q.empty())
   {
      current = q.front();
      q.pop();
      if (visited[current]) continue;
      if (current==target) return true;
      visited[current]=true;
      for(int u=0;u<2;u++)
      {
         for(int i=0;i<4;i++)
         {
            next = (u==0) ? nextnumber(current,i,true) : nextnumber(current,i,false);
            if (visited[next]) continue;
            len[next]=len[current]+1;
            q.push(next);
         }
      }
   }
   return false;
}

int main()
{
   int cases;
   cin >> cases;
   string line;
   int n;
   for(int z=0;z<cases;z++)
   {
      start = readnumber();
      target = readnumber();
      memset(visited,false,sizeof(bool)*maxnumbers);
      cin >> n;
      for(int i=0;i<n;i++) visited[readnumber()]=true;
      if (bfs()) cout << len[target] << endl;
      else cout << "-1" << endl;
      getline(cin,line);
      cin.ignore();
   }
   return 0;
}