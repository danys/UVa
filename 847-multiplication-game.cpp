#include <iostream>

using namespace std;

bool winner(unsigned int x)
{
	if (x<=9) return true;
	unsigned int val = 9;
	unsigned int counter = 1;
	while(val<x)
    {
        val *= (counter%2==1) ? 2 : 9;
        counter++;
    }
	return (counter%2==1) ? true : false;
}

int main()
{
	unsigned int n;
	while(cin >> n)
	{
		if (winner(n)) cout << "Stan wins." << endl;
		else cout << "Ollie wins." << endl;
	}
}
