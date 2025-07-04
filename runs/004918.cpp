#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;
const int min_dic_len=3, max_dic_len=50000, max_freg = 1000, max_word_len=20, max_sms_len=100000;
int N=0;
char* puncts;
map<char, int> keyboard;

map<int, vector<char*> > dic;
map<char*, int> prefers;
vector<char*> words;

vector<char*> order(vector<char*> list, unsigned int n)
{
	if (n<list.size()-1)
	{
		if (! (prefers[list[n]] < prefers[list[n+1]]))
		{
			swap(list[n],list[n+1]);
			list = order(list, n+1);
		}
	}
	return list;
}

int print_word(int& key, int& pref)
{
	int pos = dic[key].size()-pref;
	char* output = dic[key].at(pos);
	if (key==1) {cout << output[0]; return 0;} 
	cout << output;
	prefers[dic[key].at(pos)]++;
	dic[key]=order(dic[key],pos);
	return 0;
}

vector<char*> global_order(vector<char*> list, int n)
{
	if (n>0)
	{
		if (prefers[list[n]] <= prefers[list[n-1]]) 
		{
			swap(list[n],list[n-1]);
			list = global_order(list, n-1);
		}
	}
	return list;
}

int get_key(char* word)
{
	int key=0;
	int w_len = strlen(word);
	
	for (int i=0; i<w_len; i++)
	{
		key = key*10 + keyboard[word[i]];
	}
	return key;
}

void read_dic()
{
	char wordbuf[max_word_len];
	int freq=0;
	
	words.reserve(N+3);
	dic[1].reserve(3); 
	for (int i=0; i<3; i++) 
	{
		char* a=new char[1]; a[0] = puncts[i];
		words.push_back(new char[1]);
		strcpy(words.back(),a);
		dic[1].push_back(words[i]);
	}

	for (int i=0; i<N; i++)
	{
		cin.getline(wordbuf,max_word_len,' ');
		words.push_back(new char[strlen(wordbuf)-1]);
		strcpy(words.back(), &wordbuf[1]);
		int key;
		key= get_key(words.back());
		cin >> freq;
		if (dic[key].size()==0) {dic[key].reserve(1);}
		prefers[words.back()] = freq;
		dic[key].push_back(words.back());
		dic[key] = global_order(dic[key], dic[key].size()-1);
	}
}


void set_keyboard()
{
	puncts = new char[3];
	puncts[0] = '?'; puncts[1] = ','; puncts[2] = '.';
	keyboard['a'] = 2; keyboard['b'] = 2; keyboard['c'] = 2;
	keyboard['d'] = 3; keyboard['e'] = 3; keyboard['f'] = 3;
	keyboard['g'] = 4; keyboard['h'] = 4; keyboard['i'] = 4;
	keyboard['j'] = 4; keyboard['k'] = 4; keyboard['l'] = 4;
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

	int key=0;
	int pref=1;
	char symbol;
	cin >> symbol;

	while(symbol!='\n')
	{
		switch (symbol)
		{
		default:
			key = key*10 + atoi(&symbol);
			break;
		case '*' :
			pref++;
			break;
		case ' ':
			if (key > 0) {print_word(key,pref); key=0; pref = 1;}
			cout << ' '; 
			break;
		case '1':
			if (key > 0) {print_word(key,pref); key=0; pref = 1;}
			key=1;
			break;
		}
	cin.get(symbol);
	}
	if (key > 0) print_word(key,pref);
	return 0;
}