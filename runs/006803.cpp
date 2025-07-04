#include <stdio.h>
#include <vector>
#include <string>
#include <ctype.h>
#include <algorithm>
#include <list>
using namespace std;
typedef list<string> words;
struct wlist
{
	vector<words> wordListsVector;
	string firstWord;
	int FirstWordFr;
};
typedef vector<wlist> HashTable;
struct WordNumber
{
	int word;
	int number;
};
typedef list<WordNumber> wn;
int HashFunc (string word);
HashTable FillDict ();
string recognize (HashTable &t, string s);
void RemoveDict (HashTable &t);
wn SeparateWords (string s);
int HashFunc (string word)
{
	int hashIndex = 0;
	for (int i = 0; i <= word.size() -1; i++)
	{
		switch (word[i])
		{
		case 'a':
		case 'b':
		case 'c':
			hashIndex=hashIndex*10+2;
			break;
		case 'd':
		case 'e':
		case 'f':
			hashIndex=hashIndex*10+3;
			break;
		case 'g':
		case 'h':
		case 'i':
			hashIndex=hashIndex*10+4;
			break;
		case 'j':
		case 'k':
		case 'l':
			hashIndex=hashIndex*10+5;
			break;
		case 'm':
		case 'n':
		case 'o':
			hashIndex=hashIndex*10+6;
			break;
		case 'p':
		case 'q':
		case 'r':
		case 's':
			hashIndex=hashIndex*10+7;
			break;
		case 't':
		case 'u':
		case 'v':
			hashIndex=hashIndex*10+8;
			break;
		case 'w':
		case 'x':
		case 'y':
		case 'z':
			hashIndex=hashIndex*10+9;
			break;
		}
	}
	return hashIndex;
}
HashTable FillDict ()
{
	int n;
	scanf ("%i", &n);
	HashTable t;
	char* st = new char [20];
	int fr;
	int hashIndex;
	for (int i = 0; i <= n-1; i++)
	{
		scanf ("%s", st);
		scanf ("%i", &fr);
		hashIndex = HashFunc ((string) st);
		if (t.size() < hashIndex)
			t.resize (hashIndex);
		if (t[hashIndex-1].wordListsVector.size() < fr)
			t[hashIndex-1].wordListsVector.resize (fr);
		t[hashIndex-1].wordListsVector[fr-1].push_back ((string) st);
	}
	for (int i = 0; i <= t.size() -1; i++)
		t[i].FirstWordFr = 0;
	return t;
}
wn SeparateWords (string s)
{
	wn w;
	WordNumber word;
	word.word = 0;
	word.number = 1;
	for (int i = 0; i <= s.size() -1; i++)
	{
		if (s[i] == '1' || s[i] == ' ')
		{
			w.push_back (word);
			word.word = 0;
			word.number = 1;
		}
		if (isdigit (s[i]) && ((int) s[i]-(int) '0') > 1)
			word.word = word.word * 10 + ((int) s[i]-(int) '0');
		else if (isdigit (s[i]) && ((int) s[i]-(int) '0') == 1)
		{
			word.word = 1;
			word.number = 1;
		}
		else if (s[i] == '*')
			word.number++;
		else if (s[i] == ' ')
		{
			word.word = 0;
			word.number = 1;
			w.push_back (word);
		}
		if (i == s.size()-1)
			w.push_back (word);
	}
	return w;
}
string recognize (HashTable &t, string s)
{
	string result;
	wn w = SeparateWords  (s);
	char sign[3]={'.', ',', '?'};
	for (wn::iterator itr = w.begin (); itr != w.end (); itr++)
	{
		if (itr->word == 1)
			result.push_back (sign[itr->number -1]);
		else if (itr->word == 0)
			result.push_back (' ');
		else
		{
			int k = itr->number;
			if (!t[itr->word -1].wordListsVector.empty() && t[itr->word -1].FirstWordFr)
			{
				k--;
				if (!k)
				{
					result += (t[itr->word -1].firstWord);
					t[itr->word -1].FirstWordFr++;
					continue;
				}
			}
			int iFr = t[itr->word -1].wordListsVector.size() -1;
			while (k)
			{
				if (t[itr->word -1].wordListsVector[iFr].empty())
				{
					iFr--;
					continue;
				}
				if (k > t[itr->word -1].wordListsVector[iFr].size())
				{
					k -= t[itr->word -1].wordListsVector[iFr].size();
					iFr--;
					continue;
				}
				for (words::iterator wItr = t[itr->word -1].wordListsVector[iFr].begin(); wItr != t[itr->word -1].wordListsVector[iFr].end(); wItr++)
				{
					k--;
					if (!k)
					{
						result += *wItr;
						if (t[itr->word -1].wordListsVector.size() < t[itr->word -1].FirstWordFr +1 && t[itr->word -1].FirstWordFr)
							t[itr->word -1].wordListsVector.resize (t[itr->word -1].FirstWordFr +1);
						if (t[itr->word -1].FirstWordFr)
						{
							t[itr->word -1].wordListsVector[t[itr->word -1].FirstWordFr].push_front (t[itr->word -1].firstWord);
						}
						t[itr->word -1].firstWord = *wItr;
						t[itr->word -1].FirstWordFr =iFr +1;
						t[itr->word -1].wordListsVector[iFr].erase (wItr);
						break;
					}
				}
			}
		}
	}
	return result;
}
void RemoveDict (HashTable &t)
{
	for (int i = 0; i <= t.size() -1; i++)
		if (!t[i].wordListsVector.empty())
		{
			for (int j = t[i].wordListsVector.size() -1; j >=0; j--)
				if (!t[i].wordListsVector[j].empty())
					for (list<string>::iterator itr = t[i].wordListsVector[j].begin(); itr != t[i].wordListsVector[j].end(); itr++)
						itr->~string();
			t[i].wordListsVector.clear();
			if (!t[i].firstWord.empty())
				t[i].firstWord.~string ();
		}
}
int main ()
{
	HashTable t =FillDict ();
	char* st = new char [100000];
	char a;
	scanf ("%c", &a);
	gets (st);
	char* result = new char [100000];
	string vsp=recognize (t, st).c_str();
	result = (char*) vsp.c_str();
	printf ("%s", result);
	RemoveDict (t);
	delete [] st;
	return 0;
}