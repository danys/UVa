#include <iostream>
#include <string>
#include <sstream>
#include <string.h>

using namespace std;

double a[20][20][20];
int b[20][20][20];
int sequence[21];

//sets the whole array to all 0 or -1
void initialize()
{
    memset(a,0.0,sizeof a);
    memset(b,-1,sizeof b);
    memset(sequence,0,sizeof sequence);
}

void traverse(int i,int j, int length)
{
    if (length<=0) return;
    int temp = b[length][i][j];
    traverse(i,temp,length-1);
    cout << " " << b[length][i][j]+1;
}

int main()
{
    string line;
    int n;
    double temp;
    while(getline(cin,line))
    {
        stringstream s(line);
        s >> n;
        initialize();
        for(int i=0;i<n;i++)
        {
            getline(cin,line);
            stringstream ss(line);
            for(int j=0;j<n-1;j++)
            {
                if (j==i)
                {
                    a[0][i][j] = 1;
                    ss >> a[0][i][j+1];
                }
                else if (j<i) ss >> a[0][i][j];
                else ss >> a[0][i][j+1];
                b[0][i][j] = i;
            }
        }
        a[0][n-1][n-1] = 1;
        for(int l=1;l<n;l++)
            for(int k=0;k<n;k++)
                for(int i=0;i<n;i++)
                    for(int j=0;j<n;j++)
                    {
                        temp = a[l-1][i][k]*a[0][k][j];
                        if (temp>a[l][i][j])
                        {
                            a[l][i][j] = temp;
                            b[l][i][j] = k;
                        }
                    }
        //we have the array
        bool found = false;
        int length = -1;
        int index = -1;
        for(int l=0;l<n && !found;l++)
            for(int i=0;i<n && !found;i++)
                if (a[l][i][i]>1.01)
                {
                    index = i;
                    length = l;
                    found=true;
                    break;
                }
        if (index==-1) cout << "no arbitrage sequence exists" << endl;
        else
        {
            //we have a profiting sequence
            cout << index+1;
            traverse(index,index,length);
            cout << " " << index+1 << endl;
        }
    }
    return 0;
}
