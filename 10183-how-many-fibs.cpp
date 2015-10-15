#include <iostream>
#include <vector>

#define maxFibs 1000

using namespace std;

char* fibs[maxFibs];

int len(char* x)
{
	int i=0;
	while(x[i]!='\0') i++;
	return i;
}

void printNum(char* x)
{
	int lenx = len(x);
	for(int i=0;i<lenx;i++) cout << x[i];
	cout << endl;
}

char* add(char* x, char* y)
{
	//cout << "Adding " << endl;
	//printNum(x);
	//printNum(y);
	//cout << "OK" << endl;
	//DEBUG
	int lenx = len(x);
	int leny = len(y);
	int lenz = lenx>=leny ? lenx : leny;
	int minxy = lenx<=leny ? lenx : leny;
	//cout << "Lenx " << lenx << endl;
	//cout << "Leny " << leny << endl;
	//cout << "minxy " << minxy << endl;
	lenz++;
	//cout << "Lenz " << lenz << endl;
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
		//cout << "Digit " << (char)(digitz+'0') << endl;
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
			//cout << "X> Digit " << (char)(digitz+'0') << endl;
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
			//cout << "Y> Digit " << (char)(digitz+'0') << endl;
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
	//cout << "Add res " << endl;
	//printNum(z);
	//cout << "OK" << endl;
	return z;
}

int cmp(char* x, char* y)
{
	int lenx = len(x);
	int leny = len(y);
	if (lenx>leny) return 1;
	else if (lenx<leny) return -1;
	int i=0;
	while(x[i]==y[i]) i++;
	if (x[i]>y[i]) return 1;
	else if(x[i]<y[i]) return -1;
	else return 0;
}

void compute(char* maxNum)
{
	char* fib1;
	char* fib2;
	fib1 = new char[2];
	fib2 = new char[2];
	fib1[0] = '1';
	fib1[1] = '\0';
  	printNum(fib1);
	fib2[0] = '2';
	fib2[1] = '\0';
	fibs[0] = fib1;
	int counter=1;
	char* t;
	while(cmp(fib2,maxNum)<=0)
	{
		fibs[counter]=fib2;
		counter++;
		printNum(fib2);
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

int findIndex(bool high, char* x)
{
	int index=0;
	while((index<maxFibs) && (cmp(fibs[index],x)<0)) index++;
	if (high) return index;
	else
	{
		if (cmp(fibs[index],x)==0) return index;
		else return --index;
	}
}

int main()
{
	cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
	compute(createMaxNumStr(100));
	/*char* a;
	char* b;
	string astr,bstr;
	while(1)
	{
		cin >> astr >> bstr;
		if ((astr.compare("0")==0) && (bstr.compare("0")==0)) break;
		a = (char*)astr.c_str();
		b = (char*)bstr.c_str();
		cout << findIndex(false,b)-findIndex(true,a)+1 << endl;
	}*/
}