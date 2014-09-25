#include <iostream>

using namespace std;

#define maxlines 1000

int a[maxlines][3];

bool smaller(int x1, int x2, int y)
{
    return (((double)((double)x1/(double)x2))<((double)((double)a[y][0]/(double)a[y][1])));
}

void sort(int n)
{
    int j;
    int temp[3];
    for(int i=1;i<n;i++)
    {
        temp[0]=a[i][0];
        temp[1]=a[i][1];
        temp[2]=a[i][2];
        j=i-1;
        while(smaller(temp[0],temp[1],j))
        {
            a[j+1][0]=a[j][0];
            a[j+1][1]=a[j][1];
            a[j+1][2]=a[j][2];
            j--;
        }
        a[j+1][0]=temp[0];
        a[j+1][1]=temp[1];
        a[j+1][2]=temp[2];
    }
}

void print(int n)
{
    for(int i=0;i<n;i++)
    {
        cout << a[i][2];
        if (i!=n-1) cout << " ";
    }
    cout << endl;
}

int main()
{
    int cases,n;
    string str;
    cin >> cases;
    for(int z=1;z<=cases;z++)
    {
         cin.ignore();
         getline(cin,str);
         cin >> n;
         for(int i=0;i<n;i++)
         {
             cin >> a[i][0] >> a[i][1];
             a[i][2]=i+1;
         }
         sort(n);
         print(n);
         if (z!=cases) cout << endl;
    }
}
