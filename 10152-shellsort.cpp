#include <iostream>
#include <string>

using namespace std;

#define maxturtles 200

string turtles[maxturtles];
string fturtles[maxturtles];
string temp[maxturtles];

bool hasallbelow(int opos,int fpos,int n)
{
    if (opos==0) return true;
    if (opos>fpos) return false;
    for(int i=opos;i<=n-1;i++)
    {
        if (turtles[i].compare(fturtles[fpos])==0)
        {
           fpos++;
           if (fpos>n-1) return true;
        }
    }
    return false;
}

int findt(string str,int n)
{
    for(int i=n-1;i>=0;i--) if (turtles[i].compare(str)==0) return i;
    return -1;
}

void move(int index,int n)
{
    cout << turtles[index] << endl;
    int cc=1;
    temp[0]=turtles[index];
    for(int i=0;i<n;i++) if (i!=index) temp[cc++] = turtles[i];
    for(int i=0;i<n;i++) turtles[i]=temp[i];
}

void solve(int n)
{
    int index;
    for(int i=n-1;i>=0;i--)
    {
        index = findt(fturtles[i],n);
        if (!hasallbelow(index,i,n)) move(index,n);
    }
}

void readt(int n, string* t)
{
    int counter=0;
    string line;
    for(int i=0;i<n;i++)
    {
        getline(cin,line);
        t[counter++] = line;
    }
}

int main()
{
    int k,n;
    cin >> k;
    for(int z=1;z<=k;z++)
    {
        cin >> n;
        cin.ignore();
        readt(n,turtles);
        readt(n,fturtles);
        solve(n);
        cout << endl;
    }
}
