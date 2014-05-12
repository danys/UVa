#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <limits>
#include <stack>

using namespace std;

struct node{
    int key;
    int height;
};

int** a;
int n,k;
bool** matrix;
stack<node> vertexstack;

//Allocate space for a two dimensional array
void buildarray()
{
    a = new int*[k];
    for(int i=0;i<k;i++) *(a+i) = new int[n];
}

//clean up two dimensional array
void cleanuparray()
{
    for(int i=0;i<k;i++)
    {
        delete [] a[i];
    }
    delete [] a;
}

//selection sort - O(N^2) complexity
void sortarray(int* a, int length)
{
    int minindex;
    int temp;
    for(int i=0;i<length-1;i++)
    {
        minindex = i;
        for(int j=i+1;j<length;j++)
        {
            if (a[j]<a[minindex]) minindex = j;
        }
        temp = a[minindex];
        a[minindex] = a[i];
        a[i] = temp;
    }
}

bool box1fitsin2(int box1, int box2)
{
    if (box1==box2) return false;
    int i=0;
    while((a[box1][i]<a[box2][i]) && (i<n)) i++;
    if (i==n) return true;
    else return false;

}

void buildmatrix()
{
    matrix = new bool*[k];
    for(int i=0;i<k;i++) *(matrix+i)=new bool[k];
    for(int i=0;i<k;i++)
    {
        for(int j=0;j<k;j++)
        {
            if (box1fitsin2(i,j)) matrix[i][j]=true;
            else matrix[i][j]=false;
        }
    }
}

//Returns an array a with the sequence of nodes that form the maximum path
//Function returns the number of nodes on the maximum path
//Key x from 0 to k-1
int dfscount(int x, int* a)
{
    node n;
    n.key=x;
    n.height=1;
    node popelement;
    node pushelement;
    int maxheight=0;
    vertexstack.push(n);
    bool nextfound;
    int* temparray = new int[k];
    while(!vertexstack.empty())
    {
        popelement = vertexstack.top();
        vertexstack.pop();
        temparray[popelement.height-1]=popelement.key;
        nextfound=false;
        for(int i=0;i<k;i++)
        {
            if (matrix[popelement.key][i]==true)
            {
                pushelement.key=i;
                pushelement.height=popelement.height+1;
                vertexstack.push(pushelement);
                nextfound=true;
            }
        }
        if ((!nextfound) && (popelement.height>maxheight)) //we reached the end of the path and have a new longest path
        {
            maxheight = popelement.height;
            for(int i=0;i<maxheight;i++) a[i]=temparray[i];
        }
    }
    delete[] temparray;
    return maxheight;
}

void destroymatrix()
{
    for(int i=0;i<k;i++)
    {
        delete [] matrix[i];
    }
    delete [] matrix;
}

int main()
{
    k=0;
    n=0;
    string line;
    while(getline(cin,line))
    {
        stringstream s(line);
        s >> k >> n;
        buildarray();
        for(int i=0;i<k;i++)
        {
            getline(cin,line);
            stringstream ss(line);
            for(int j=0;j<n;j++)
            {
                ss >> a[i][j];
            }
        }
        //sort the boxes
        for(int i=0;i<k;i++) sortarray(*(a+i),n);
        //build adjacency matrix
        buildmatrix();
        int* solutionarray = new int[k];
        int* temparray=new int[k];
        int counter=0;
        int maxcounter=-1;
        for(int i=0;i<k;i++)
        {
            counter = dfscount(i,temparray);
            if (counter>maxcounter)
            {
                for(int j=0;j<counter;j++) solutionarray[j]=temparray[j]+1;
                maxcounter = counter;
            }
        }
        cout << maxcounter << endl;
        for(int i=0;i<maxcounter;i++)
        {
            if (i==maxcounter-1) cout << solutionarray[i];
            else cout << solutionarray[i] << " ";
        }
        cout << endl;
        destroymatrix();
        cleanuparray();
        delete [] solutionarray;
        delete [] temparray;
    }
    return 0;
}
