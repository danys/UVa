#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool hasNext(string s, int len)
{
	if (len==1) return false;
	int counter=0;
	for(int i=0;i<len-1;i++) if (s[i]>=s[i+1]) counter++;
	return !(counter==len-1);
}

void printNextPermutation(string s)
{
	int len=s.length();
	if (hasNext(s,len))
	{
		char c;
		int index;
		for(int i=len-1;i>=0;i--)
		{
			index=-1;
			for(int j=i+1;j<=len-1;j++)
			{
				if (s[i]<s[j])
				{
					if (index==-1) index=j;
					else if (s[j]<s[index]) index=j;
				}
			}
			if (index!=-1)
			{
				c = s[index];
				s[index]=s[i];
				s[i]=c;
				sort(s.begin()+i+1,s.end());
				cout << s << endl;
				return;
			}
		}
	}
	else cout << "No Successor" << endl;
}

int main()
{
	string s;
	while(true)
	{
		cin >> s;
		if (s=="#") break;
		printNextPermutation(s);
	}
	return 0;
}