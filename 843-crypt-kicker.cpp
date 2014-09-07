#include <iostream>
#include <string>
#include <sstream>
#include <string.h>
#include <algorithm>

using namespace std;

#define maxdict 1000
#define maxwords 80
#define alphalen 26

string dict[maxdict];
string owords[maxwords];
string words[maxwords];
char table[alphalen];
int ndict, nwords;


int ndistchar(string str)
{
	int res=0;
	int alpha[alphalen];
	memset(alpha,0,sizeof(int)*alphalen);
	for(unsigned i=0;i<str.size();i++) alpha[str[i]-'a']++;
	for(int i=0;i<alphalen;i++) if (alpha[i]>0) res++;
	return res;
}

void buildcandidates(int k, bool* candidates)
{
	memset(candidates,true,sizeof(bool)*ndict);
	for(int i=0;i<ndict;i++) if (dict[i].size()!=words[k].size()) candidates[i]=false;
	int ndistcharw = ndistchar(words[k]);
	for(int i=0;i<ndict;i++)
	{
		if (!candidates[i]) continue;
		if (ndistcharw!=ndistchar(dict[i])) candidates[i]=false;
	}
}

bool isvalid(int i, int k)
{
	string str = dict[i];
	string word = words[k];
	for(unsigned int j=0;j<word.size();j++)
	{
		if (table[word[j]-'a']==-1) continue;
		else if (str[j]!=table[word[j]-'a']) return false;
	}
	return true;
}

void setintable(int i, int k,int* index,int &cc)
{
	string str = dict[i];
	string word = words[k];
	cc=0;
	for(unsigned int j=0;j<word.size();j++)
	{
		if (table[word[j]-'a']!=-1) continue;
		table[word[j]-'a']=str[j];
		index[cc++]=word[j]-'a';
	}
}

void removefromtable(int* index, int cc)
{
	for(int i=0;i<cc;i++) table[index[i]]=-1;
}

bool inconsistent()
{
    int a[alphalen];
    memset(a,0,sizeof(int)*alphalen);
    for(int i=0;i<alphalen;i++) a[table[i]-'a']++;
    for(int i=0;i<alphalen;i++) if (a[i]>1) return true;
    return false;
}

bool backtrack(int k)
{
	int number;
	if (k==nwords) return true;
	else
	{
		bool* candidates = new bool[ndict];
		buildcandidates(k,candidates);
		for(int i=0;i<ndict;i++)
		{
			if (!candidates[i]) continue;
			if(isvalid(i,k))
			{
				int* index = new int[maxdict];
				setintable(i,k,index,number);
				if (!inconsistent())
				{
                    if (backtrack(k+1)) return true;
				}
				removefromtable(index,number);
			}
		}
		return false;
	}
}

string replace(string str,bool star)
{
	for(unsigned int i=0;i<str.size();i++) str[i] = (star) ? table[str[i]-'a'] : '*';
	return str;
}

void printwords(bool star)
{
	for(int i=0;i<nwords;i++)
	{
		cout << replace(owords[i],star);
		if (i!=nwords-1) cout << " ";
	}
}

bool cmp(string str1, string str2)
{
    if (str1.size()>=str2.size()) return true;
    else return false;
}

int main()
{
	int n,cc;
	cin >> n;
	cc=0;
	for(int i=0;i<n;i++) cin >> dict[cc++];
	ndict=cc;
	cin.ignore();
	string line, word;
	stringstream ss;
	while(getline(cin,line))
	{
		ss.str(line);
		cc=0;
		while(ss >> word)
        {
            words[cc++]=word;
            owords[cc-1]=word;
        }
		nwords=cc;
        sort(words,words+nwords,cmp);
		memset(table,-1,alphalen);
		printwords(backtrack(0));
		cout << endl;
		ss.clear();
	}
	return 0;
}
