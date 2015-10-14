#include <iostream>
#include <gmp.h>
#include <stdio.h>
#include <vector>
#include <string>

#define maxFibs 1000

using namespace std;

mpz_t fibs[maxFibs];

void compute(char* maxNum)
{
	mpz_t maxNumber;
	mpz_init(maxNumber);
	mpz_set_str(maxNumber,maxNum,10);
	mpz_t fib1;
	mpz_init(fib1);
	mpz_set_si(fib1,1);
	mpz_out_str(stdout, 10, fib1);
  	putchar('\n');
	mpz_t fib2;
	mpz_init(fib2);
	mpz_set_si(fib2,2);
	mpz_set(fibs[0],fib1);
	int counter=1;
	mpz_t t;
	mpz_init(t);
	while(mpz_cmp(fib2,maxNumber)<=0)
	{
		mpz_set(fibs[counter],fib2);
		counter++;
		mpz_out_str(stdout, 10, fib2);
  		putchar('\n');
		mpz_add(t,fib1,fib2);
		mpz_set(fib1,fib2);
		mpz_set(fib2,t);
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

int findIndex(bool high, mpz_t x)
{
	int index=0;
	while((index<maxFibs) && (mpz_cmp(fibs[index],x)<0)) index++;
	if (high) return index;
	else
	{
		if (mpz_cmp(fibs[index],x)==0) return index;
		else return --index;
	}
}

int main()
{
	compute(createMaxNumStr(100));
	mpz_t a,b;
	mpz_init(a);
	mpz_init(b);
	string astr,bstr;
	while(1)
	{
		cin >> astr >> bstr;
		if ((astr.compare("0")==0) && (bstr.compare("0")==0)) break;
		mpz_set_str(a,astr.c_str(),10);
		mpz_set_str(b,bstr.c_str(),10);
		cout << findIndex(false,b)-findIndex(true,a)+1 << endl;
	}
}