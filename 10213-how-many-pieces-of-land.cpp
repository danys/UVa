#include <iostream>

using namespace std;

//Convert a given integer into a char array
char* convertToChar(int x)
{
	bool sign = true; //default to plus sign
	if (x<0)
	{
		sign = false;
		x = x*(-1);
	}
	char* res = new char[12]; //accommodates the 5'000'000'000 possible values, the sign and the '\0' character
	int index=11;
	res[index]='\0'; //store the terminating null character
	index--;
	while(x>0)
	{
		res[index]=(char)((x%10)+'0'); //extract bit after bit
		x /= 10;
		index--;
	}
	if (sign) res[index]='+';
	else res[index]='-';
	if (index==0) return res;
	char* shortRes = new char[12-index];
	for(int i=0;i<12-index;i++) shortRes[i]=res[index+i];
	delete res;
	return shortRes;
}

//Change the sign of the number x
char* neg(char* x)
{
	//find current sign
	if (x[0]=='-')	x[0]='+';
	else x[0]='-';
	return x;
}

//Computes f(x)=(x^4-6*x^3+23*x^2-18*x+24)/24
long long compute(int x)
{
	if (x<=30000)
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
	else
	{
		long long res = 24;
		long long x2 = x*x;
		res += (-18)*x;
		char* cx = convertToChar(x);
		char* cres = convertToChar(res);
		char* c23x2 = mult(convertToChar(x2),convertToChar(6));
		cres = add(cres,c23x2);
		char* cx3 = mult(convertToChar(x2),cx);
		char* c6x3 = neg(mult(mult(convertToChar(x2),convertToChar(x)),convertToChar(6)));
		cres = add(cres,c6x3);
		char* cx4 = mult(cx3,cx);
		cres = add(cres,cx4);
		return divideBy24(cres);
	}
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