// task3.cpp: определяет точку входа для консольного приложения.
//
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;


int N;

typedef string big;

class words 
{
public:
	string word;
	big klavishi;
	int chastota;
	words() {}
	~words() {}
	void wordToInt();
};

typedef vector<words*> collect;
collect c;
char keyboard[9][4] = {
	{'.',',','?'},
	{'a','b','c'},
	{'d','e','f'},
	{'g','h','i'},
	{'j','k','l'},
	{'m','n','o'},
	{'p','q','r','s'},
	{'t','u','v'},
	{'w','x','y','z'}};
int sizes[9]={3,3,3,3,3,3,4,3,4};

char find(char c)
{
	for (char i=0;i<9;i++)
	{
		for (int j=0;j<sizes[i];j++)
		{
			if (c==keyboard[i][j]) return i+1;
		}
	}
	return 0;
}
void words::wordToInt()
{
	for (unsigned i=0; i<word.length();i++)
	{
		klavishi+=find(word[i]);
		
	}
}
void findWord(big rez, unsigned z)
{
	vector<words*> dub;
	int first=-1;
	for (unsigned i=0; i<c.size(); i++)
	{
		if (c[i]->klavishi==rez)
		{
			first=i;
			break;
		}
	}
	unsigned p=first;
	while ((p<c.size())&&(c[p]->klavishi==rez))
	{
		dub.push_back(c[p]);
		p++;
	}
	if (z>dub.size()) z=z%dub.size();
	cout<<dub[z]->word;
	dub[z]->chastota++;
	while ((z>0)&& (dub[z]->chastota>=dub[z-1]->chastota))
	{
		words* dub2=dub[z-1];
		dub[z-1]=dub[z];
		dub[z]=dub2;
		z--;
	}
	copy(dub.begin(), dub.end(),c.begin()+first); 
}
void analiz(string s)
{
	big rez="";
	unsigned zvezd=0;
	for (unsigned i=0;i<s.length(); i++)
	{
		if (s[i]=='*')
		{
			zvezd++;
			while ((i<s.length()-1)&&(s[i+1]=='*'))
			{
				i++;
				zvezd++;
			}
			
			findWord(rez,zvezd);
			zvezd=0;
			rez="";
		} else if (s[i]=='1')
		{
			if (rez.length()!=0) findWord(rez,zvezd);
			zvezd=0;
			rez="";
			while ((i<s.length()-1)&&(s[i+1]=='*'))
			{
				i++;
				zvezd++;
			}
			cout<<keyboard[0][zvezd%sizes[0]];
		} else {
			
			rez+=s[i]- '0';
			
		}
	}
	if (rez.length()!=0) findWord(rez,zvezd);	
	cout<<" ";
}

bool mypred(words* w2, words* w1)
{
	if (w1->klavishi>w2->klavishi)
	{ 
		return true;
	} else if (w1->klavishi==w2->klavishi)
	{
		if ((w1->chastota)<(w2->chastota))
		{
			return true;
		} 
	}
	return false;
}
int main()
{
	ifstream in("in");
	cin>>N;
	for (int i=0; i<N; i++)
	{
		words * w = new words();
		cin>>w->word;
		cin>>w->chastota;
		w->wordToInt();
		c.push_back(w);
	}
	stable_sort(c.begin(), c.end(),mypred);
	string str;
	cin.get();
	getline(cin,str);
	int i;
	do 
	{
		i=str.find(' ');
		string str2=str.substr(0,i);
		if (str2!="") analiz(str2);
		else cout<<" ";
		str=str.substr(i+1, str.length()-i);
	} while (i!=-1);
	while(c.size()!=0)
	{
		words* p=c.back();
		c.pop_back();
		delete p;
	}
	//in.close();
	return 0;
}

