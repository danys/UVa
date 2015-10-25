#include <iostream>

using namespace std;

//Returns the length +1
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

//OK works also for numbers without a sign
int cmp(char* x, char* y)
{
	int lenx = len(x);
	int leny = len(y);
	if ((x[0]=='-') && (y[0]=='+')) return -1;
	else if ((x[0]=='+') && (y[0]=='-')) return 1;
	int sign = 1;
	if ((x[0]=='-') && (y[0]=='-')) sign = -1;
	if (lenx>leny) return sign;
	else if (lenx<leny) return (-1)*sign;
	int i=1;
	while((i<lenx) && (x[i]==y[i])) i++;
	if (i==lenx) return 0;
	if (x[i]>y[i]) return sign;
	else return (-1)*sign;
}

int cmpABS(char* x, char* y)
{
	return cmp(x+1,y+1);
}

char* add(char* x, char* y)
{
	int lenx = len(x);
	int leny = len(y);
	int lenz = lenx>=leny ? lenx : leny;
	int minxy = lenx<=leny ? lenx : leny;
	lenz++;
	bool sign = true;
	char* temp;
	if ((x[0]=='-') && (y[0]=='-'))
	{
		sign = false;
		x[0]='+';
		y[0]='+';
	}
	else if ((x[0]=='-') && (y[0]=='+'))
	{
		temp = x;
		x = y;
		y = temp;
		sign = cmpABS(x,y)<0 ? false : true;
	}
	else if ((x[0]=='+') && (y[0]=='-'))
	{
		sign = cmpABS(x,y)<0 ? false : true;
	}
	//We either have two plus signs or a plus and a minus sign (in that order)
	char* z = new char[lenz+1];//+1 for '\0' char
	int digitx, digity, carry, digitz;
	carry=0;
	z[lenz]='\0'; //set the null terminating character
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
	}
	z[0]=(char)(carry+'0');
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

/*char* mult(char* x,char* y)
{
	//
}

char* divideBy24(char* x)
{
	//
}*/

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

/*char* compute(int x)
{
	char* cx = convertToChar(x);
	char* cx2 = mult(cx,cx);
	char* cx3 = mult(cx2,cx);
	//The 5 terms of the sum
	char* cx4 = mult(cx3,cx);
	char* cx3t6 = neg(mult(cx3,convertToChar(6)));
	char* cx2t23 = mult(cx2,convertToChar(23));
	char* cxt18 = neg(mult(cx,convertToChar(18)));
	char* c24 = convertToChar(24);
	return divideBy24(add(add(add(add(cx4,cx3t6),cx2t23),cxt18),c24));
}*/

int main(int argc, char** argv)
{
	char* str = convertToChar(-999997691);
	printNum(str);
	cout << "Len = " << len(str) << endl;
	/*int ncases,x;
	cin >> ncases;
	for(int z=1;z<=ncases;z++)
	{
		cin >> x;
		cout << printNum(compute(x));
	}*/
	return 0;
}