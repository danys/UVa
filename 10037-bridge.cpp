#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> people;
vector<int> solution;
int totaltime;

void solve(int n)
{
    if (n<1) return;
    else if (n==1)
    {
        solution.push_back(people[0]);
        solution.push_back(-1);
        totaltime += people[0];
    }
    else if (n==2)
    {
        solution.push_back(min(people[0],people[1]));
        solution.push_back(max(people[0],people[1]));
        solution.push_back(-1);
        totaltime += max(people[0],people[1]);
    }
    else if (n==3)
    {
        solution.push_back(people[0]);
        solution.push_back(people[2]);
        solution.push_back(-1);
        solution.push_back(people[0]);
        solution.push_back(-1);
        solution.push_back(people[0]);
        solution.push_back(people[1]);
        solution.push_back(-1);
        totaltime += people[0]+people[1]+people[2];
    }
    else
    {
        int x1,x2,x3,x4;
        x1=people[0];
        x2=people[1];
        x3=people[n-2];
        x4=people[n-1];
        if (x1+x3<2*x2)
        {
            solution.push_back(x1);
            solution.push_back(x4);
            solution.push_back(-1);
            solution.push_back(x1);
            solution.push_back(-1);
            solution.push_back(x1);
            solution.push_back(x3);
            solution.push_back(-1);
            solution.push_back(x1);
            solution.push_back(-1);
            totaltime += x4+x1+x3+x1;
        }
        else
        {
            solution.push_back(x1);
            solution.push_back(x2);
            solution.push_back(-1);
            solution.push_back(x1);
            solution.push_back(-1);
            solution.push_back(x3);
            solution.push_back(x4);
            solution.push_back(-1);
            solution.push_back(x2);
            solution.push_back(-1);
            totaltime += x2+x1+x4+x2;
        }
        people.pop_back();
        people.pop_back();
        solve(n-2);
    }
}

void print()
{
    cout << totaltime << endl;
    for(vector<int>::iterator i=solution.begin();i!=solution.end(); ++i)
    {
        if (*i==-1) cout << endl;
        else
        {
            if (*(i+1)==-1) cout << *i;
            else cout << *i << " ";
        }
    }
}

void init()
{
    people.clear();
    solution.clear();
    totaltime = 0;
}

int main()
{
    int cases,n,t;
    string str;
    cin >> cases;
    for(int z=1;z<=cases;z++)
    {
        cin.ignore();
        getline(cin,str);
        cin >> n;
        init();
        for(int i=0;i<n;i++)
        {
            cin >> t;
            people.push_back(t);
        }
        sort(people.begin(),people.end());
        solve(n);
        print();
        if (z!=cases) cout << endl;
    }
}
