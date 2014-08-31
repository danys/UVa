#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

#define maxarray 3001

bool isjolly(int* a,bool* table,int c)
{
    if (a[0]==1) return true;
    for(int i=1;i<c-1;i++) table[abs(a[i]-a[i+1])] = true;
    int cc = 0;
    for(int i=1;i<a[0];i++) if (table[i]) cc++;
    return (cc==a[0]-1) ? true : false;
}

int main()
{
    string line;
    string snum;
    stringstream ss;
    int a[maxarray];
    bool table[maxarray];
    int c;
    while(getline(cin,line))
    {
        c=0;
        ss.str(line);
        while(ss>>snum) a[c++] = atoi(snum.c_str());
        memset(table,false,maxarray*sizeof(bool));
        if (isjolly(a,table,c)) cout << "Jolly" << endl;
        else cout << "Not jolly" << endl;
        ss.clear();
    }
    return 0;
}
