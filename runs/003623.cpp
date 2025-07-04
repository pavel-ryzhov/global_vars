#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>

using namespace std;

class Word
{
	public:
		string s;
		int freq;
		int pos;
		Word(string s, int freq):s(s),freq(freq),pos(0){};
		friend bool operator<(const Word &a, const Word &b);
};

bool operator<(const Word &a, const Word &b)
{
	if (b.freq < a.freq) return true;
	if (b.freq > a.freq) return false;
	if (b.pos < a.pos) return true;
	if (b.pos > a.pos) return false;
	return a.s<b.s;
}
int tableConvert[26] = {2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};
string SToCode(const string &w)
{
	string res = "";
	for (int i=0;i<w.length();i++)
		res += '0'+tableConvert[w[i]-'a'];
	return res;
}

void moveWord(vector<Word> &v, int index)
{
	Word t = v[index];
	int i = index-1;
	while ((i>=0) && (t<v[i]))
	{
		v[i+1] = v[i];
		i--;
	}
	v[i+1] = t;
}

int main()
{
	map<string, vector<Word> > dict;
	int n;
	cin>>n;
	string s;
	int f;
	for (int i=0;i<n;i++)
	{
		cin>>s>>f;
		dict[SToCode(s)].push_back(Word(s, f));
	}

	map<string, vector<Word> >::iterator p;
	for (p = dict.begin(); p!=dict.end();p++)
		sort((*p).second.begin(), (*p).second.end());
	
	string text = "";
	string cur_s = "";
	char c;
	char zn[4] = ".,?";
	int pos = 0;
	int k = 0;
	int kzn =0;
	int state = 0;
	cin.unsetf(ios::skipws);
	while (cin>>c)
	{
		if (!( ((c>='1')&&(c<='9')) || (c==' ') || (c=='*') )) continue;
		
		if (c == '*')
		{
			k++;
			continue;
		}

		switch(state)
		{
			case 0:
				if ((c>='2') && (c<='9'))
				{
					cur_s = c;
					state = 1;
				}
				if (c == ' ') text += ' ';
				if (c == '1') state = 2;
				break;

			case 1:
				if ((c>='2') && (c<='9'))
					cur_s += c;
				else
				{
					text += dict[cur_s][k].s;
					if (c == ' ')
					{
						text += ' ';
						state = 0;
					}
					else state = 2;
					dict[cur_s][k].freq++;
					dict[cur_s][k].pos = pos;
					moveWord(dict[cur_s], k);
					k = 0;
				}
				break;

			case 2:
				text += zn[k%3];
				k = 0;
				if (c == ' ')
				{
					text += ' ';
					state = 0;
				}
				else
				if (c == '1' ) state = 2;
				else
				if ((c >= '2') && (c <= '9'))
				{
					state = 1;
					cur_s = c;
				}
				break;
		}
		pos++;
	}

	if (state == 1) text += dict[cur_s][k].s;
	if (state == 2) text += zn[k%3];
	cout.unsetf(ios::skipws);
	cout<<text<<endl;
	return 0;
}
