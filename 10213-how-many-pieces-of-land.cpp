#include <iostream>

using namespace std;

//Computes f(x)=(x^4-6*x^3+23*x^2-18*x+24)/24
long long compute(int x)
{
	long long res = 24;
	long long x2 = x*x;
	long long x3 = x2*x;
	long long x4 = x3*x;
	res += x4;
	res += (-6)*x3;
	res += 23*x2;
	res += (-18)*x;
	return res/24;
}

int main(int argc, char** argv)
{
	int ncases,x;
	cin >> ncases;
	for(int z=1;z<=ncases;z++)
	{
		cin >> x;
		cout << compute(x) << endl;
	}
	return 0;
}