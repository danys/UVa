#include <iostream>
#include <string.h>

using namespace std;

int main()
{
    int ncoordinates = 100000;
    int* height = new int[ncoordinates];
    memset(height,0,ncoordinates*sizeof(int));
    int currentheight, left, right;
    while(cin >> left >> currentheight >> right)
    {
        for(int i=left;i<right;i++)
        {
            if (currentheight>height[i]) height[i]=currentheight;
        }
    }
    int currentlevel = 0;
    for (int i=0;i<ncoordinates;i++)
    {
        if (height[i] != currentlevel)
        {
            if (currentlevel!=0) cout << ' ';
            cout << i << ' ' << height[i];
            currentlevel = height[i];
        }
    }
    cout << endl;
    return 0;
}