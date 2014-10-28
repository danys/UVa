#include <iostream>
#include <string.h>
#include <algorithm>

#define maxncities 100

using namespace std;

int n,r;
int cap[maxncities][maxncities];

void computemaxcaps()
{
   for(int k=0;k<n;k++)
   {
      for(int i=0;i<n;i++)
      {
         for(int j=0;j<n;j++)
         {
            cap[i][j]=max(cap[i][j],min(cap[i][k],cap[k][j]));
         }
      }
   }
}

int computeres(int start,int dest, int npers)
{
   computemaxcaps();
   int ncapacity = cap[start-1][dest-1]-1;
   if (npers % ncapacity==0) return npers/ncapacity;
   return (npers/ncapacity)+1;
}

int main()
{
   int city1, city2, capacity, start, destination, ntourists, ncases;
   ncases=0;
   while(true)
   {
      cin >> n >> r;
      if ((n==0) && (r==0)) break;
      ncases++;
      memset(cap,-1,sizeof(int)*maxncities*maxncities);
      for(int i=0;i<r;i++)
      {
         cin >> city1 >> city2 >> capacity;
         cap[city1-1][city2-1] = capacity;
         cap[city2-1][city1-1] = capacity;
      }
      cin >> start >> destination >> ntourists;
      cout << "Scenario #" << ncases << endl;
      cout << "Minimum Number of Trips = " << computeres(start,destination,ntourists) << endl;
      cout << endl;
   }
   return 0;
}
