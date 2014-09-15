#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

#define maxlen 50
#define maxwords 20

int m,n,k,cases;
string matrix[maxlen];
string words[maxwords];

bool onpath(int i, int j, int x, int y, unsigned int s, string w)
{
    if ((i<0) || (i>=m) || (j<0) || (j>=n)) return false;
    if (matrix[i][j]!=w[s]) return false;
    if (s==w.length()-1) return true;
    return onpath(i+x,j+y,x,y,s+1,w);
}

bool findstr(int i, int j, string w)
{
    return (onpath(i,j,-1,-1,0,w) || onpath(i,j,-1,0,0,w) || onpath(i,j,-1,1,0,w) || onpath(i,j,0,-1,0,w) || onpath(i,j,0,1,0,w) || onpath(i,j,1,-1,0,w) || onpath(i,j,1,0,0,w) || onpath(i,j,1,1,0,w));
}

void findwords()
{
    string w;
    bool found=false;
    for(int z=0;z<k;z++)
    {
        w = words[z];
        found = false;
        for(int i=0;(i<m) && (!found);i++)
        {
            for(int j=0;(j<n) && (!found);j++)
            {
                if (findstr(i,j,w))
                {
                    cout << i+1 << " " << j+1 << endl;
                    found=true;
                }
            }
        }
    }
}

int main()
{
    cin >> cases;
    cin.ignore();
    string line;
    stringstream ss;
    for(int z=1;z<=cases;z++)
    {
        getline(cin,line); //blank line
        getline(cin,line); //line containing m and n
        ss.str(line);
        ss >> m >> n;
        ss.clear();
        for(int i=0;i<m;i++)
        {
            getline(cin,line);
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            matrix[i]=line;
        }
        getline(cin,line);
        ss.str(line);
        ss >> k;
        ss.clear();
        for(int i=0;i<k;i++)
        {
            getline(cin,line);
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            words[i]=line;
        }
        findwords();
        if (z!=cases) cout << endl;
    }
    return 0;
}
