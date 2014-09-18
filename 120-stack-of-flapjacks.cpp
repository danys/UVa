#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

#define maxpancakes 30

int stack[maxpancakes];
int temp[maxpancakes];
int npancakes;

void flip(int i)
{
    reverse(stack,stack+npancakes-i+1);
}

int maxindex(int maxi)
{
    int max=0;
    int res=-1;
    for(int i=0;i<=maxi;i++)
    {
       if (stack[i]>max)
       {
           max=stack[i];
           res=i;
       }
    }
    return res;
}

void solve()
{
    int t;
    for(int k=npancakes-1;k>=0;k--)
    {
        t = maxindex(k);
        if (t!=k)
        {
            if (t!=0)
            {
                flip(npancakes-t);
                cout << npancakes-t << " ";
            }
            flip(npancakes-k);
            cout << npancakes-k << " ";
        }
    }
    cout << "0" << endl;
}

void prints()
{
    for(int i=0;i<npancakes;i++)
    {
        cout << stack[i];
        if (i!=npancakes-1) cout << " ";
    }
    cout << endl;
}

int main()
{
    string line;
    stringstream ss;
    int t;
    while(getline(cin,line))
    {
        ss.str(line);
        npancakes=0;
        while(ss >> t) stack[npancakes++] = t;
        prints();
        solve();
        ss.clear();
    }
}
