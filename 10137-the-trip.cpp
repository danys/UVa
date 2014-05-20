#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

double student[1000];

int main()
{
    int n;
    double avg, pres, nres, res;
    while(true)
    {
        cin >> n;
        if (n==0) break;
        for(int z=1;z<=n;z++) cin >> student[z-1];
        avg=0.0;
        for(int i=0;i<n;i++) avg += student[i];
        avg=avg/(double)n;
        pres=0.0;
        nres=0.0;
        for(int i=0;i<n;i++)
        {
            res = (double)(long)((student[i]-avg)*100.0)/100.0;
            if (res>0) pres += res;
            else nres +=res;
        }
        nres = -nres;
        cout << fixed << setprecision(2);
        if (pres>=nres) cout << "$" << pres << endl;
        else cout << "$" << nres << endl;
    }
    return 0;
}
