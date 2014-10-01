#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>

#define maxwords 25000
#define alphalen 26
#define primelen 100003

using namespace std;

struct Node
{
    string val;
    vector<int> nodes;
};

Node graph[maxwords];
int table[alphalen];

vector<vector<pair<int,string>>> hashtable(primelen);

int hashcompute(string &s)
{
    long long res = 0;
    long long base = 1;
    for(unsigned int i=0;i<s.length();i++)
    {
        res = (res + base*(int)(s[i]-'a')) % primelen;
        base = (base * alphalen) % primelen;
    }
    return (int)res;
}

bool match(string& str1, string& str2)
{
    int count=0;
    for(unsigned int i=0;i<min(str1.length(),str2.length());i++) if (str1[i]!=str2[i]) count++;
    return (count==1);
}

int matchunequal(string& str1, string& str2)
{
    memset(table,0,sizeof(int)*alphalen);
    for(unsigned int i=0;i<min(str1.length(),str2.length());i++)
    {
        table[str1[i]-'a']+=1;
        table[str2[i]-'a']-=1;
    }
    if (str1.length()>str2.length()) table[str1[str1.length()-1]-'a']+=1;
    else table[str2[str2.length()-1]-'a']-=1;
    int count=0;
    int sum=0;
    for(int i=0;i<alphalen;i++)
    {
        if (table[i]==0) count++;
        sum += table[i];
    }
    if (count==alphalen-1) return sum;
    else return 0;
}

bool editstep(string& str1, string& str2)
{
    if (str1.compare(str2)==0) return false;
    int ldiff = str1.length()-str2.length();
    if (abs(ldiff)>1) return false;
    if (ldiff==0)
    {
        return match(str1,str2);
    }
    else return (matchunequal(str1,str2)==ldiff);
}

pair<int,string> findinhashtable(string &str)
{
    int index = hashcompute(str);
    for(unsigned int i=0;i<hashtable[index].size();i++)
    {
        if (hashtable[index][i].second.compare(str)==0) return hashtable[index][i];
    }
    return make_pair(-1,"");
}

void buildcandidates(string &str,vector<string> candidates)
{
    candidates.clear();
    string word = str;
    //Compute strings with same length where only one char is different.
    //That char must be lexicographically following the char to be replaced.
    for(unsigned int i=0;i<word.length();i++)
    {
        for(char c=word[i]+1;c<'z';c++)
        {
            word[i]=c;
            candidates.push_back(word);
        }
        word[i] = str[i];
    }
    //Compute all strings with one more char.
    for(unsigned int i=0;i<word.length();i++)
    {
        word.insert(word.begin()+i,'a');
        for(char c=word[i]+1;c<'z';c++)
        {
            word[i]=c;
            candidates.push_back(word);
        }
        word.erase(word.begin()+i);
    }
    //Same as above but appending last char
    word.insert(word.end(),'a');
    for (char c = 'a'; c <= 'z'; c++)
    {
        word[word.length()-1]=c;
        candidates.push_back(word);
    }
    word.erase(word.begin()+word.length()-1);
    //Compute all strings with one missing char
    for (unsigned int i = 0; i < str.length()-1; i++)
    {
        if (word[i] >= word[i+1]) continue;
        word.erase(word.begin()+i);
        candidates.push_back(word);
        word.insert(word.begin()+i, str[i]);
    }
}

void buildgraph(int n)
{
    for(int i=0;i<n;i++)
    {
        vector<string> candidates;
        pair<int,string> t;
        for (int i = 0; i < n; i++)
        {
            buildcandidates(graph[i].val, candidates);
            for (unsigned int j = 0; j < candidates.size(); j++)
            {
                t = findinhashtable(candidates[j]);
                if (t.first != -1) graph[i].nodes.push_back(t.first);
            }
        }
    }
}

int solve(int n,int startnode)
{
    if (graph[startnode].nodes.size()==0) return 1;
    int max=0;
    int cur;
    for(unsigned int i=0;i<graph[startnode].nodes.size();i++)
    {
        cur = solve(n,graph[startnode].nodes[i]);
        if (cur>max) max = cur;
    }
    return 1+max;
}

int allsolve(int n)
{
    int max, cur;
    max=0;
    for(int i=0;i<n;i++)
    {
        cur=solve(n,i);
        if (cur>max) max=cur;
        if (max>n-i) break;
    }
    return max;
}

void putinhashtable(int i,string &str)
{
    hashtable[hashcompute(str)].push_back(make_pair(i,str));
}

int main()
{
    string str;
    int n=0;
    while(getline(cin,str))
    {
        graph[n++].val = str;
        graph[n-1].nodes.clear();
        putinhashtable(n-1,str);
    }
    buildgraph(n);
    cout << allsolve(n) << endl;
}
