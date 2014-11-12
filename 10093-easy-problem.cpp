#include <iostream>
#include <string>

#define minbase 2
#define maxbase 62

using namespace std;

//Converts char into the range 0 to 61
int convertchar(char c)
{
   if ((c>='0') && (c<='9')) return c-'0';
   if ((c>='A') && (c<='Z')) return (c-'A')+10;
   if ((c>='a') && (c<='z')) return (c-'a')+36;
   return 0;
}

long convertnumber(string str)
{
   long res = 0;
   //N based number X is divisible by (N-1) if the sum of its digits is divisible by (N-1)
   for(int i = str.length()-1;i>=0;i--) res += (long)convertchar(str[i]);
   return res;
}

int minimum(string str)
{
   int mini=0;
   for(unsigned int i=0;i<str.length();i++) if (convertchar(str[i])>mini) mini = convertchar(str[i]);
   return mini+1;
}

void solve(string str)
{
   int mini = minimum(str);
   if (mini<2) mini = minbase;
   for(int i=mini;i<=maxbase;i++)
   {
      if (convertnumber(str)%(i-1)==0)
      {
         cout << i << endl;
         return;
      }
   }
   cout << "such number is impossible!" << endl;
}

int main()
{
   string line;
   while(getline(cin,line)) solve(line);
}