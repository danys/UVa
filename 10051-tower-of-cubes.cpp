#include <iostream>
#include <string.h>

#define maxcubes 500
#define maxcolors 100
#define maxfaces 6

using namespace std;

int h[maxcubes][maxfaces];
int cubes[maxcubes][maxfaces];

string faces[] = {"front","back","left","right","top","bottom"};

struct box
{
    int pos;
    int face;
};

box boxes[maxcubes][maxfaces];

int tr(int i)
{
    if ((i>maxfaces-1) || (i<0)) return -1;
    if (i%2==0) return i+1;
    else return i-1;
}

int maxlength(int i, int j, int n)
{
    int res = h[i][j];
    if (res!=1) return res;
    for(int x=n-1;x>i;x--)
    {
        for(int y=0;y<maxfaces;y++)
        {
            if ((cubes[x][y]==cubes[i][tr(j)]) && (res<h[x][y]+1))
            {
                res = h[x][y]+1;
                boxes[i][j].pos=x;
                boxes[i][j].face=y;
            }
        }
    }
    h[i][j]=res;
    return res;
}

int solve(int n, box& b)
{
    int maxlen=0;
    for(int i=n-1;i>=0;i--)
    {
        for(int j=0;j<maxfaces;j++)
        {
            if (maxlength(i,j,n)>maxlen)
            {
                maxlen=h[i][j];
                b.pos=i;
                b.face=j;
            }
        }
    }
    return maxlen;
}

void arrayset(int val, int l1, int l2)
{
    for(int i=0;i<l1;i++)
        for(int j=0;j<l2;j++) h[i][j]=val;
}

int main()
{
    int n,cases;
    box b;
    cases=0;
    while((cin >> n) && (n!=0))
    {
        if (cases!=0) cout << endl;
        arrayset(1,maxcubes,maxfaces);
        memset(boxes,0,maxcubes*maxfaces*sizeof(box));
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<maxfaces;j++)
            {
                cin >> cubes[i][j];
            }
        }
        cases++;
        cout << "Case #" << cases << endl;
        cout <<  solve(n,b) << endl;
        while(h[b.pos][b.face] != 1)
        {
            cout << b.pos+1 << " " << faces[b.face] << endl;
            b = boxes[b.pos][b.face];
        }
        cout << b.pos+1 << " " << faces[b.face] << endl;
    }
}
