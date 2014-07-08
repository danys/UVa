#include <iostream>

using namespace std;

int intlen(int x)
{
    if (x==0) return 1;
    int res=0;
    while(x>0)
    {
        x /= 10;
        res++;
    }
    return res;
}

int* inttoarray(int x,int len)
{
    int* res = new int[len];
    if (x==0)
    {
        res[0]=0;
        return res;
    }
    int counter=0;
    while(x>0)
    {
        res[counter]=x%10;
        x/=10;
        counter++;
    }
    return res;
}

int main()
{
    int x1, x2;
    while(true)
    {
        cin >> x1 >> x2;
        if ((x1 == 0) && (x2 == 0)) break;
        int lenx1 = intlen(x1);
        int lenx2 = intlen(x2);
        int minlen = (lenx1<lenx2)? lenx1:lenx2;
        int maxlen = (lenx1>lenx2)? lenx1:lenx2;
        int ncarries = 0;
        int* ax1 = inttoarray(x1,lenx1);
        int* ax2 = inttoarray(x2,lenx2);
        int carry = 0;
        int currentsum = 0;
        for(int i=0;i<minlen;i++)
        {
            currentsum = ax1[i]+ax2[i]+carry;
            if (currentsum>9) ncarries++;
            carry=currentsum/10;
        }
        if ((carry>0) && (minlen!=maxlen))
        {
            if (lenx1>minlen)
            {
                for(int i=minlen;i<lenx1;i++)
                {
                    currentsum = ax1[i]+carry;
                    if (currentsum>9) ncarries++;
                    carry=currentsum/10;
                }
            }
            else
            {
                for(int i=minlen;i<lenx2;i++)
                {
                    currentsum = ax2[i]+carry;
                    if (currentsum>9) ncarries++;
                    carry=currentsum/10;
                }
            }
        }
        if (ncarries==0) cout << "No carry operation." << endl;
        else if (ncarries==1) cout << "1 carry operation." << endl;
        else cout << ncarries << " carry operations." << endl;
    }
    return 0;
}
