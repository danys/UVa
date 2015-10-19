#include <iostream>

#define maxDigits 1050
#define maxFibs maxDigits*5

using namespace std;

char* fibs[maxFibs];

int len(char* x)
{
	int i=0;
	while(x[i]!='\0') i++;
	return i;
}

char* add(char* x, char* y)
{
	int lenx = len(x);
	int leny = len(y);
	int lenz = lenx>=leny ? lenx : leny;
	int minxy = lenx<=leny ? lenx : leny;
	lenz++;
	char* z = new char[lenz+1];//+1 for '\0' char
	int digitx, digity, carry, digitz;
	carry=0;
	z[lenz]='\0';
	for(int i=0;i<minxy;i++)
	{
		digitx = (int)(x[lenx-1-i]-'0');
		digity = (int)(y[leny-1-i]-'0');
		digitz = digitx+digity+carry;
		carry = digitz / 10;
		digitz %= 10;
		z[lenz-1-i] = (char)(digitz+'0'); 
	}
	if (lenx>leny)
	{
		for(int i=lenx-1-minxy;i>=0;i--)
		{
			digitx = (int)(x[i]-'0');
			digitz = carry+digitx;
			carry = digitz / 10;
			digitz %= 10;
			z[i+lenz-lenx] = (char)(digitz+'0'); 
		}
	}
	else if (lenx<leny)
	{
		for(int i=leny-1-minxy;i>=0;i--)
		{
			digity = (int)(y[i]-'0');
			digitz = carry+digity;
			carry = digitz / 10;
			digitz %= 10;
			z[i+lenz-leny] = (char)(digitz+'0'); 
		}
	} //else if lenx==leny => do nothing
	z[0]=(char)(carry+'0');
	//Remove leading zeros
	int first = 0;
	while((first<lenz) && (z[first]=='0')){first++;}
	if (first>0)
	{
		char* zz = new char[lenz+1-first];
		for(int i=first;i<=lenz;i++) zz[i-first]=z[i];
		z=zz;
	}
	return z;
}

int cmp(char* x, char* y)
{
	int lenx = len(x);
	int leny = len(y);
	if (lenx>leny) return 1;
	else if (lenx<leny) return -1;
	int i=0;
	while((i<lenx) && (x[i]==y[i])) i++;
	if (i==lenx) return 0;
	if (x[i]>y[i]) return 1;
	else return -1;
}

void compute(char* maxNum)
{
	char* fib1;
	char* fib2;
	fib1 = new char[2];
	fib2 = new char[2];
	fib1[0] = '0';
	fib1[1] = '\0';
	fib2[0] = '1';
	fib2[1] = '\0';
	fibs[0] = fib1;
	int counter=1;
	char* t;
	while(cmp(fib2,maxNum)<=0)
	{
		fibs[counter]=fib2;
		counter++;
		t = add(fib1,fib2);
		fib1 = fib2;
		fib2 = t;
	}
	delete maxNum;
	maxNum=0;	
}

char* createMaxNumStr(int nDigits)
{
	nDigits += 2;
	char* str = new char[nDigits];
	for(int i=0;i<nDigits-1;i++)
	{
		if (i==0) str[0]='1';
		else str[i]='0';
	}
	str[nDigits-1]='\0';
	return str;
}

int main(int argc, char** argv)
{
	int x;
	compute(createMaxNumStr(maxDigits));
	while(cin >> x) cout << "The Fibonacci number for " << x << " is " << fibs[x] << endl;
}