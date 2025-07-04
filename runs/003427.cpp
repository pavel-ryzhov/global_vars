#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

struct freq
{
	string _word;
	int _frequency;
	int _prior;
	freq(){};
	freq(string word, int frequency, int prior) : _word(word),_frequency(frequency),_prior(prior){};
};

bool operator<(const freq &a, const freq& b)
{
	if (a._frequency < b._frequency) 
		return true;
	else if (a._frequency > b._frequency) 
		return false;
	else return a._prior < b._prior;
}

map<string, set<freq> > dictionary;
map<int, int> priorities;
string keys = "22233344455566677778889999";


string GetNumber(string word)
{
	string res = "";
	int size = word.length();
	for(int i = 0; i < size; ++i)
		res += keys[word[i] - 'a'];
	return res;
}

bool cmp(const char & a)
{
	return a == '*';
}

void input()
{
	int n;
	cin >> n;
	int prior = 50001, amount;
	string word;
	for(int i = 0; i < n; ++i)
	{
		cin >> word >> amount;
		string number = GetNumber(word);
		if (dictionary.find(number) != dictionary.end())
			dictionary.find(number)->second.insert(freq(word,amount,prior--));
		else
		{
			set<freq> cur;
			cur.insert(freq(word,amount,prior--));
			dictionary.insert(make_pair(number,cur));
			priorities.insert(make_pair(amount , prior + 1));
		}
	}

	string cur;
	bool isFirst = true;
	while(cin >> cur)
	{
		int onePos = cur.find_first_of("1");
		string trail = "";
		if (onePos != -1)
		{
			trail = cur.substr(onePos);
			cur = cur.substr(0,onePos);
		}

		if (cur!="")
		{
			int starsAmount = count_if(cur.begin(),cur.end(), cmp);
			string actualNumber = cur.substr(0, cur.length() - starsAmount);
			map<string,set<freq> >::iterator s = dictionary.find(actualNumber);
			set<freq>::iterator curSet = s->second.end();

			for(int i=0;i<starsAmount;++i)
				curSet--;
			curSet--;
			cout << (isFirst?"":" ") << curSet -> _word;
			isFirst = false;
			int prior = priorities[curSet->_frequency + 1] + 1;
			priorities[curSet->_frequency + 1] ++;
			freq toInsert(curSet->_word, curSet->_frequency+1, prior);
			s->second.erase(curSet);
			s->second.insert(toInsert);
		}
		if (trail != "")
		{
			int in = 0;
			for(int i=0;i<trail.size();i++)
			{
				if (trail[i] == '1')
				{
					if (!in) 
						in ++;
					else
					{
						if (in == 1) cout << ".";
						else if(in ==2) cout << ",";
						else cout << "?";
						in = 1;
					}
				}
				else if (trail[i] == '*')
					in ++;
			}
			if (in == 1) cout << ".";
			else if(in ==2) cout << ",";
			else cout << "?";
		}
	}
}

int main()
{
	input();
	return 0;
}