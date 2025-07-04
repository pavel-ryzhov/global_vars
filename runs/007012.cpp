#include <stdio.h>
#include <vector>
#include <string>
#include <ctype.h>
#include <algorithm>
#include <list>
using namespace std;
struct words
{
	list<string> l;
	long Fr;
};
struct wlist
{
	list<words> wordListsL;
	long WordCount;
	wlist () : WordCount(0) {};
};
typedef vector<wlist> HashTable;
struct WordNumber
{
	long word;
	long number;
};
typedef list<WordNumber> wn;
long HashFunc (string word);
HashTable FillDict ();
string recognize (HashTable &t, string s);
wn SeparateWords (string s);
long HashFunc (string word)
{
	long hashIndex = 0;
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
	long n;
	scanf ("%d", &n);
	HashTable t;
	char* st = new char [20];
	long fr;
	long hashIndex;
	for (int i = 0; i <= n-1; i++)
	{
		scanf ("%s", st);
		scanf ("%d", &fr);
		hashIndex = HashFunc ((string) st);
		if (t.size() < hashIndex)
			t.resize (hashIndex);
		if (t[hashIndex -1].wordListsL.empty())
		{
				words Words;
				Words.Fr = fr;
				t[hashIndex -1].wordListsL.push_front (Words);
				t[hashIndex -1].wordListsL.begin()->l.push_back (st);
				t[hashIndex -1].WordCount++;
		}
		else if (fr > t[hashIndex -1].wordListsL.back().Fr)
		{
				words Words;
				Words.Fr = fr;
				list<words>::iterator vsp = t[hashIndex -1].wordListsL.insert (t[hashIndex -1].wordListsL.end(), Words);
				vsp->l.push_back(st);
				t[hashIndex -1].WordCount++;
 		}
		else if (fr < t[hashIndex -1].wordListsL.front().Fr)
		{
				words Words;
				Words.Fr = fr;
				t[hashIndex -1].wordListsL.push_front (Words);
				t[hashIndex -1].wordListsL.begin()->l.push_back (st);
				t[hashIndex -1].WordCount++;
		}
		else
		{
			for (list<words>::iterator itr = t[hashIndex -1].wordListsL.begin(); itr != t[hashIndex -1].wordListsL.end(); itr ++)
			{
				if (itr->Fr == fr)
				{
					itr->l.push_back (st);
					t[hashIndex -1].WordCount++;
					break;
				}
				else if (fr < itr->Fr)
				{
					words Words;
					Words.Fr = fr;
					list<words>::iterator vsp = t[hashIndex -1].wordListsL.insert (itr, Words);
					vsp->l.push_back (st);
					t[hashIndex -1].WordCount++;
					break;
				}
			}
		}
	}
	return t;
}
wn SeparateWords (string s)
{
	wn w;
	WordNumber word;
	word.word = 0;
	word.number = 1;
	for (long i = 0; i <= s.size() -1; i++)
	{
		if (s[i] == '1' || s[i] == ' ')
		{
			if (word.word != 0)
			{
				w.push_back (word);
				word.word = 0;
				word.number = 1;
			}
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
			continue;
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
			long k = itr->number;
			if (k > t[itr->word -1].WordCount)
				k -= t[itr->word -1].WordCount;
			list<words>::iterator iFr = t[itr->word -1].wordListsL.end();
			iFr--;
			while (k)
			{
				if (iFr->l.empty())
				{
					iFr--;
					continue;
				}
				if (k > iFr->l.size())
				{
					k -= iFr->l.size();
					iFr--;
					continue;
				}
				for (list<string>::iterator wItr = iFr->l.begin(); wItr != iFr->l.end(); wItr++)
				{
					k--;
					if (!k)
					{
						result += *wItr;
						string vsp = *wItr;
						iFr->l.erase (wItr);
						if (iFr->Fr != t[itr->word -1].wordListsL.back().Fr)
						{
							list<words>::iterator vsp1 = iFr;
							vsp1++;
							if (iFr->Fr +1 == vsp1->Fr)
								vsp1->l.push_front (vsp);
							else
							{
								words Words;
								Words.Fr = iFr->Fr +1;
								Words.l.push_front (vsp);
								list<words>::iterator vsp1 = iFr;
								vsp1++;
								t[itr->word -1].wordListsL.insert (vsp1, Words);
							}
						}
						else
						{
							words Words;
							Words.Fr = iFr->Fr +1;
							Words.l.push_front (vsp);
							t[itr->word -1].wordListsL.push_back (Words);
						}
						break;
					}
				}
			}
		}
	}
	return result;
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
	delete [] st;
	return 0;
}