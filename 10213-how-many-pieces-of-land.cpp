#include <iostream>

using namespace std;

char* cresult;
long long result;

int len(char* x)
{
	int i=0;
	while(x[i]!='\0') i++;
	return i;
}

//Convert a given integer into a char array
char* convertToChar(long long x)
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
char* neg(char* &x)
{
	//find current sign
	if (x[0]=='-')	x[0]='+';
	else x[0]='-';
	return x;
}

//Change the sign of the number x (call by value of reference)
char* pneg(char* x)
{
	//find current sign
	if (x[0]=='-')	x[0]='+';
	else x[0]='-';
	return x;
}

int compare(char* x, char* y)
{
	if ((x[0]=='-') && (y[0]=='+')) return -1;
	else if ((x[0]=='+') && (y[0]=='-')) return 1;
	int i=0;
	int lenx = len(x);
	int leny = len(y);
	if (x[0]=='+')
	{
		if (lenx>leny) return 1;
		else if (lenx<leny) return -1;
	}
	else
	{
		if (lenx>leny) return -1;
		else if (lenx<leny) return 1;
	}
	while((x[i]==y[i]) && (x[i]!='\0')){i++;}
	if (x[i]=='\0') return 0;
	if (x[i]<y[i])
	{
		if (x[0]=='+') return -1;
		else return 1;
	}
	else
	{
		if (x[0]=='+') return 1;
		else return -1;
	}
}

int compareABS(char* x, char* y)
{
	int i=1;
	int lenx = len(x);
	int leny = len(y);
	if (lenx>leny) return 1;
	else if (lenx<leny) return -1;
	while((x[i]==y[i]) && (x[i]!='\0')){i++;}
	if (x[i]=='\0') return 0;
	if (x[i]<y[i]) return -1;
	else return 1;
}

//Swap the given arguments
void swap(char* &x, char* &y)
{
	char* t;
	t = x;
	x = y;
	y = t;
}

void printNum(char* str)
{
	int i = 0;
	while(str[i]!='\0')
	{
		cout << str[i];
		i++;
	}
	cout << endl;
}

char* add(char* &x, char* &y)
{
	int xlen = len(x);
	int ylen = len(y);
	bool xsign = (x[0]=='+') ? true : false;
	bool ysign = (y[0]=='+') ? true : false;
	bool zsign = true;
	if ((xsign) && (ysign))
	{
		//plus operation
		zsign = true;
	}
	else if ((!xsign) && (!ysign))
	{
		//minus
		x = neg(x);
		y = neg(y);
		zsign = false;
	}
	else if ((!xsign) && (ysign))
	{
		swap(x,y);
		//now we have x with plus sign and y with minus sign
		if (compareABS(x,y)>=0)
		{
			zsign = true;
		}
		else
		{
			zsign = false;
			x = neg(x);
			y = neg(y);
			swap(x,y);
		}
	}
	else if ((xsign) && (!ysign))
	{
		if (compareABS(x,y)>=0)
		{
			zsign = true;
		}
		else
		{
			zsign = false;
			x = neg(x);
			y = neg(y);
			swap(x,y);
		}
	}
	char* z;
	char* zz;
	int reslen = (xlen>=ylen) ? xlen : ylen;
	int carry=0;
	int minxy = (xlen<=ylen) ? xlen : ylen;
	int digitx, digity, digitz;
	if (y[0]=='+')
	{
		//plus operation
		z = new char[reslen+2]; //null terminating char plus one more
		z[reslen+1]='\0';
		for(int i=0;i<minxy-1;i++)
		{
			digitx = x[xlen-1-i]-'0';
			digity = y[ylen-1-i]-'0';
			digitz = digitx + digity + carry;
			carry = digitz / 10;
			digitz %= 10;
			z[reslen-i] = (char)(digitz+'0');
		}
		if (xlen>ylen)
		{
			for(int i=xlen-minxy;i>=1;i--)
			{
				digitx = x[i]-'0';
				digitz = digitx + carry;
				carry = digitz / 10;
				digitz %= 10;
				z[i+1] = (char)(digitz+'0');
			}
		}
		else if (xlen<ylen)
		{
			for(int i=ylen-minxy;i>=1;i--)
			{
				digity = y[i]-'0';
				digitz = digity + carry;
				carry = digitz / 10;
				digitz %= 10;
				z[i+1] = (char)(digitz+'0');
			}
		}
		if (carry>0)
		{
			z[1]=(char)(carry+'0');
			z[0]=(zsign)?'+':'-';
		}
		else
		{
			zz = new char[reslen+1];
			for(int i=1;i<reslen+1;i++) zz[i]=z[i+1];
			z = zz;
			z[0]=(zsign)?'+':'-';
		}
	}
	else
	{
		//minus operation
		z = new char[reslen+1]; //null terminating char plus one more
		z[reslen]='\0';
		xlen = len(x);
		ylen = len(y);
		for(int i=0;i<minxy-1;i++)
		{
			digitx = x[xlen-1-i]-'0';
			digity = y[ylen-1-i]-'0';
			if (digitx>=digity+carry)
			{
				digitz = digitx-digity-carry;
				carry=0;
			}
			else
			{
				digitz = 10+digitx-digity-carry;
				carry=1;
			}
			digitz %= 10;
			z[reslen-i-1] = (char)(digitz+'0');
		}
		if (xlen>ylen)
		{
			for(int i=xlen-minxy;i>=1;i--)
			{
				digitx = x[i]-'0';
				if (digitx>=carry)
				{
					digitz = digitx-carry;
					carry=0;
				}
				else
				{
					digitz = 10+digitx-carry;
					carry=1;
				}
				digitz %= 10;
				z[i] = (char)(digitz+'0');
			}
		}
		else if (xlen<ylen)
		{
			for(int i=ylen-minxy;i>=1;i--)
			{
				digity = y[i]-'0';
				if (digity>=carry)
				{
					digitz = digity-carry;
					carry=0;
				}
				else
				{
					digitz = 10+digity-carry;
					carry=1;
				}
				digitz %= 10;
				z[i] = (char)(digitz+'0');
			}
		}
		if (z[1]==0)
		{
			int pos = 1;
			while(z[pos]=='0') pos++;
			zz = new char[reslen+1-pos];
			for(int i=pos;i<reslen+1;i++) zz[i-pos+1]=z[i];
			z = zz;
			z[0]=(zsign)?'+':'-';
		}
		else z[0]=(zsign)?'+':'-';
	}

	return z;
}

//Multiplies the char array number by a single digit number
char* simpleMult(char* x, int factor)
{
	if (factor>=10) factor %= 10; //ensure proper input
	int lenx = len(x);
	char* z = new char[lenx+2]; //+2 for new char and '\0' character
	z[lenx+1]='\0';
	int digitx,digitz,carry;
	int xsign = (x[0]=='+') ? 1 : -1;
	int fsign = (factor>=0) ? 1 : -1;
	if (factor<0) factor*=-1;
	bool zsign = (xsign*fsign==1) ? true : false;
	carry = 0;
	for(int i=lenx-1;i>=1;i--)
	{
		digitx = x[i]-'0';
		digitz = digitx*factor+carry;
		carry = digitz/10;
		digitz %= 10;
		z[i+1] = (char)(digitz+'0');
	}
	if (carry>0)
	{
		z[1] = (char)(carry+'0');
		z[0] = (zsign) ? '+' : '-';
	}
	else
	{
		char* zz = new char[lenx+1];
		for(int i=1;i<lenx+1;i++) zz[i]=z[i+1];
		zz[0] = (zsign) ? '+' : '-';
		z = zz;
	}
	return z;
}

char* leftShift(char* x, int c)
{
	int lenx = len(x);
	int lenz = lenx+c+1;//+1 for the '\0' char
	char* z = new char[lenz];
	for(int i=0;i<lenx;i++) z[i]=x[i];
	for(int i=1;i<=c;i++) z[lenx-1+i]='0';
	z[lenx+c]='\0';
    return z;
}

char* mult(char* &x, char* &y)
{
	int xlen = len(x);
	int ylen = len(y);
	int xsign = (x[0]=='+') ? 1 : -1;
	int ysign = (y[0]=='+') ? 1 : -1;
	bool zsign = (xsign*ysign==1) ? true : false;
	if (x[0]=='-') x[0]='+';
	if (y[0]=='-') y[0]='+';
	char* z = new char[xlen+ylen+1];
	for(int i=1;i<xlen+ylen;i++) z[i]='0';
	z[0]='+';
	z[xlen+ylen]='\0';
	char* t;
	int shift=0;
	for(int i=ylen-1;i>=1;i--)
	{
		t = leftShift(simpleMult(x,y[i]-'0'),shift);
		z = add(z,t);
		shift++;
	}
	if (z[1]!='0') z[0]=(zsign)?'+':'-';
	else
	{
		char* zz = new char[xlen+ylen+1];
		for(int i=1;i<xlen+ylen;i++) zz[i]=z[i+1];
		zz[0] = (zsign) ? '+' : '-';
		z = zz;
	}
	return z;
}

char* appendChar(char* x, int a)
{
	int lenx = len(x);
	a%=10;
	char* res = new char[lenx+2];
	for(int i=1;i<lenx;i++) res[i]=x[i];
	res[lenx]=(char)('0'+a);
	res[lenx+1]='\0';
	res[0]='+';
	return res;
}

char* divideBy24(char* x)
{
	char* c24 = convertToChar(24);
	char* nc24 = convertToChar(-24);
	cout << "C24 and nc24" << endl;
	printNum(c24);
	printNum(nc24);
	int xlen = len(x);
	char* z = new char[xlen+1];
	z[0]='\0';
	int p=1;
	int i=1;
	char* acc = new char[2];
	acc[0]='+';
	acc[1]='\0';
	printNum(acc);
	bool foundBeg = false;
	int digitz=0;
	char* m;
	char* nm;
	int fact=1;
	while(i<xlen)
	{
		acc = appendChar(acc,x[i]-'0');
		cout << "Acc = " << endl;
		printNum(acc);
		if (compare(acc,c24)<0)
		{
			if (!foundBeg)
			{
				while((i<xlen) && (compare(acc,c24)<0))
				{
					i++;
					acc = appendChar(acc,x[i]-'0');
				}
				if (i==xlen) return 0;
				foundBeg=true;
			}
			else
			{
				while((i<xlen) && (compare(acc,c24)<0))
				{
					i++;
					z[p]='0';
					p++;
					acc = appendChar(acc,x[i]-'0');
				}
				if (i==xlen) return 0;
			}
		}
		fact=1;
		c24[0]='+';
		m = simpleMult(c24,fact);
		cout << "m " << m  << endl;
		while(compare(m,acc)<=0)
		{
			fact++;
			m = simpleMult(c24,fact);
			cout << "m" << endl;
			printNum(m);
			cout << "Acc" << endl;
			printNum(acc);
			cout << "Fact = " << fact << endl;
		}
		m = add(m,nc24);
		fact--;
		z[p]=(char)(fact+'0');
		cout << "Setting res char = " << (char)(fact+'0') << endl;
		nm=pneg(m);
		acc = add(acc,nm);
		cout << "New acc = " << endl;
		printNum(acc);		
		/*int pos=1;
		while(acc[pos]=='0') pos++;
		int acclen = len(acc);
		char* zz = new char[acclen-pos];
		for(int j=pos;j<acclen+1;j++) zz[j-pos]=acc[j];
		acc = zz;*/
		p++;
		i++;
	}
	return z;
}

//Computes f(x)=(x^4-6*x^3+23*x^2-18*x+24)/24
void compute(int x)
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
		result = res/24;
	}
	else
	{
		char* cres = convertToChar(24);
		char* cx = convertToChar(x);
		char* ncx18 = simpleMult(cx,-18);
		cres = add(cres,ncx18);
		char* cx2 = mult(cx,cx);
		char* cx3 = mult(cx2,cx);
		char* cx4 = mult(cx3,cx);
		char* c23 = convertToChar(23);
		char* c6 = convertToChar(6);
		char* c23x2 = mult(cx2,c23);
		char* c6x3 = mult(cx3,c6);
		char* nc6x3 = neg(c6x3);
		cres = add(cres,c23x2);
		cres = add(cres,nc6x3);
		cres = add(cres,cx4);
		cresult = cres;
		
		/*int pos=1;
		while(cres[pos]=='0') pos++;
		int creslen = len(cres);
		char* zz = new char[creslen-pos];
		for(int i=pos;i<creslen+1;i++) zz[i-pos]=cres[i];
		cresult = zz;*/
		cresult = divideBy24(cresult);
	}
}

int main(int argc, char** argv)
{
	char* x = convertToChar(86400);
	//char* y = convertToChar(24);
	char* z = divideBy24(x);
	printNum(z);
	/*int ncases,x;
	cin >> ncases;
	for(int z=1;z<=ncases;z++)
	{
		cin >> x;
		compute(x);
		if (x<=30000) cout << result << endl;
		else printNum(cresult);
	}*/
	return 0;
}