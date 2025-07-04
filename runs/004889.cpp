#include <stdio.h>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <strstream>
#include <cmath>

using namespace std;
const int min_dic_len=3, max_dic_len=50000, max_freg = 1000, max_word_len=20;
int N=0;
char puncts[3]={'?',',','.'};
map<char, int> keyboard;

typedef vector<char> str;

map<int, vector<str*> > dic;
map<str*, int> prefers;
vector<str> words;


vector<str*> order(vector<str*> list, unsigned int n)
{
	if (n<list.size()-1)
	{
		if (prefers[list[n]] > prefers[list[n+1]])
		{
			str* a;
			a = list[n+1];
			list[n+1] = list[n];
			list[n] = a;
		}
	}
	return list;
}

int print_word(int kod, int pref)
{
	int pos = dic[kod].size()-pref;
	str output = *(dic[kod].at(pos));
	for (unsigned int i=0; i<output.size(); i++) cout << output[i];
	prefers[dic[kod].at(pos)]++;
	order(dic[kod],pos);
	return 0;
}

vector<str*> global_order(vector<str*> list, int n)
{
	if (n>0)
	{
		if (prefers[list[n]] < prefers[list[n-1]])
		{
			str* a;
			a = list[n-1];
			list[n-1] = list[n];
			list[n] = a;
			list = global_order(list,n-1);
		}
	}
	return list;
}

int get_kod(str word)
{
	int w_kod=0, word_len=word.size()-1;
	for (int i=word_len; i>=0; i--)
	{
		int l_kod = keyboard[word[i]];
		w_kod = l_kod*(int)pow(10.0,word_len-i) + w_kod;	
	}
	return w_kod;
}

void read_dic()
{
	int freq=0;
	words.reserve(N);
	char wordbuf[max_word_len];
	
	for (int i=0; i<N; i++)
	{
		cin.getline(wordbuf,max_word_len,' ');
		str word; word.reserve(1);
		for (int j=1; j<cin.gcount()-1; j++)	word.push_back(wordbuf[j]);
		words.push_back(word);
		int kod = get_kod(words.back());
		cin >> freq;
		if (dic[kod].size()==0) {dic[kod].reserve(1);}
		prefers[&words.back()] = freq;
		dic[kod].push_back(&words.back());
		dic[kod] = global_order(dic[kod], dic[kod].size()-1);
	}
}


void set_keyboard()
{
	keyboard['a'] = 2; keyboard['b'] = 2; keyboard['c'] = 2;
	keyboard['d'] = 3; keyboard['e'] = 3; keyboard['f'] = 3;
	keyboard['g'] = 4; keyboard['h'] = 4; keyboard['i'] = 4;
	keyboard['j'] = 5; keyboard['k'] = 5; keyboard['l'] = 5;
	keyboard['m'] = 6; keyboard['n'] = 6; keyboard['o'] = 6;
	keyboard['p'] = 7; keyboard['q'] = 7; keyboard['r'] = 7; keyboard['s'] = 7;
	keyboard['w'] = 9; keyboard['x'] = 9; keyboard['y'] = 9; keyboard['z'] = 9;
	keyboard['t'] = 8; keyboard['u'] = 8; keyboard['v'] = 8;
}

int main()
{
	set_keyboard();
	cin >> N;
	if (N<min_dic_len) {cout << "bad N value"; return 1;}
	read_dic();

	int kod, pref;
	char delim='*';
	
	while(delim!='\n')
	{
		kod=-1;
		cin >> kod;
		if (kod!=-1)
		{
			if ((kod-1)%10==0) {print_word(kod/10,1); kod=-1;}
			pref=1;
			delim = '*';
			while(delim!=' ' && delim!='\n')
			{	cin.get(delim);
				switch(delim)
				{
				case '*': pref++; break;
				case '1': print_word(kod,pref); kod=-1; pref=1; break;
				case ' ': break;
				}
			}
			if (kod!=-1) print_word(kod,pref);
			else cout << puncts[3-pref];
			cout << delim;
		}
	}
	return 0;
}