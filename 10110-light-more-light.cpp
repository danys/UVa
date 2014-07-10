#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    unsigned int n;
    while(true)
    {
        cin >> n;
        if (n==0) break;
        /* TIME LIMIT EXCEEDED APPROACH
        bool ison = false;
        for(unsigned int i=1;i<=n;i++) if (n%i==0) ison = !ison;
        if (ison) cout << "yes" << endl;
        else cout << "no" << endl;*/
        //Perfect squares apprach:
        unsigned int root = sqrt(n);
        if (root*root == n) cout << "yes" << endl;
        else cout << "no" << endl;
    }
    return 0;
}
