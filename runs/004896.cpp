#include <stdio.h>
#include <map>
#include <vector>
#include <iostream>
#include <strstream>
#include <cmath>

using namespace std;
const int min_dic_len=3, max_dic_len=50000, max_freg = 1000, max_word_len=20, max_sms_len=100000;
int N=0;
char puncts[3]={'?',',','.'};
map<char, char> keyboard;

typedef vector<char> str;

map<str, vector<str*> > dic;
map<str*, int> prefers;
vector<str> words;

vector<str*> order(vector<str*> list, unsigned int n)
{
	if (n<list.size()-1)
	{
		if (! (prefers[list[n]] < prefers[list[n+1]]))
		{
			str* a;
			a = list[n+1];
			list[n+1] = list[n];
			list[n] = a;
			list = order(list, n+1);
		}
	}
	return list;
}

int print_word(str& key, int pref)
{
	int pos = dic[key].size()-pref;
	str output = *(dic[key].at(pos));
	for (unsigned int i=0; i<output.size(); i++) cout << output[i];
	if (key.back()!='1')
	{
		prefers[dic[key].at(pos)]++;
		dic[key]=order(dic[key],pos);
	}
	return 0;
}

vector<str*> global_order(vector<str*> list, int n)
{
	if (n>0)
	{
		if (prefers[list[n]] <= prefers[list[n-1]])
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

str get_key(str& word)
{
	str key;
	int word_len=word.size();
	key.reserve(word_len);

	for (int i=0; i<word_len; i++)
	{
		key.push_back(keyboard[word[i]]);
	}
	return key;
}

void read_dic()
{
	char wordbuf[max_word_len];
	int freq=0;
	
	words.reserve(N+3);
	str puncts_key;
	puncts_key.assign(1,'1');
	dic[puncts_key].reserve(3); 
	for (int i=0; i<3; i++) 
	{
		str punct;
		punct.assign(1,puncts[i]);
		words.push_back(punct);
		dic[puncts_key].push_back(&words.back());
	}

	for (int i=0; i<N; i++)
	{
		cin.getline(wordbuf,max_word_len,' ');
		str word;
		word.reserve(1);
		for (int j=1; j<cin.gcount()-1; j++)	word.push_back(wordbuf[j]);
		words.push_back(word);
		str key;
		key.reserve(1);
		key = get_key(word);
		cin >> freq;
		if (dic[key].size()==0) {dic[key].reserve(1);}
		prefers[&words.back()] = freq;
		dic[key].push_back(&words.back());
		dic[key] = global_order(dic[key], dic[key].size()-1);
	}
}


void set_keyboard()
{
	keyboard['a'] = '2'; keyboard['b'] = '2'; keyboard['c'] = '2';
	keyboard['d'] = '3'; keyboard['e'] = '3'; keyboard['f'] = '3';
	keyboard['g'] = '4'; keyboard['h'] = '4'; keyboard['i'] = '4';
	keyboard['j'] = '5'; keyboard['k'] = '5'; keyboard['l'] = '5';
	keyboard['m'] = '6'; keyboard['n'] = '6'; keyboard['o'] = '6';
	keyboard['p'] = '7'; keyboard['q'] = '7'; keyboard['r'] = '7'; keyboard['s'] = '7';
	keyboard['w'] = '9'; keyboard['x'] = '9'; keyboard['y'] = '9'; keyboard['z'] = '9';
	keyboard['t'] = '8'; keyboard['u'] = '8'; keyboard['v'] = '8';
}

int main()
{
	set_keyboard();
	cin >> N;
	if (N<min_dic_len) {cout << "bad N value"; return 1;}
	read_dic();

	char sms[max_sms_len];
	cin.getline(sms,max_word_len+1,' ');
	int j=cin.gcount();
	sms[j-1] = ' ';
	cin.get(&sms[j],max_sms_len-j+1);
	j = j+cin.gcount();
	int i=1, sms_len = j;
	str key;
	key.reserve(1);
	int pref=1;
		
	while(i<sms_len)
	{
		char symbol=sms[i];
		switch (symbol)
		{
		default :
			if (key.size()==0) key.reserve(1);
			key.push_back(symbol);
			break;
		case '*' :
			pref++;
			break;
		case ' ':
			if (key.size()!=0) {print_word(key,pref); key.clear(); pref = 1;}
			cout << ' '; 
			break;
		case '1':
			if (key.size()!=0) {print_word(key,pref); key.clear(); pref = 1;}
			key.reserve(1);
			key.push_back('1');
			break;
		}
		i++;
	}
	if (key.size()!=0) {print_word(key,pref); key.clear(); pref = 1;}
	return 0;
}