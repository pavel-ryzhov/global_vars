#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;
//string err;
const int puncts_num=3, min_dic_len=3, max_dic_len=50000, max_freg = 1000, max_word_len=20, max_sms_len=100000;
int N=0;
char* puncts = new char[puncts_num];
map<char, int> keyboard;

map<int, vector<char*> > dic;
map<char*, int> prefers;
vector<char*> words;

// orders words in list, according to their preferences
// assumes, that preferences only increments 
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

// prints the word to cout (word='dic[key][pref]')
int print_word(int& key, int& pref)
{
	int len = dic[key].size(); //number of words with key 'key'
	int pos = dic[key].size() - pref; //position of the required word in list='dic[key]'
	// the vector='dic[key]' acts here as a circle
	while(pos < 0 || pos>len)
	{
		if (pos<0) pos=pos+len;
		if (pos>len) pos=pos-len;
	}
	char* output = dic[key].at(pos);
	if (key==1) {cout << output[0]; return 0;} // trash after puncts may uppear otherwise
	// puncts also shouldn't change preferences
	cout << output;
	prefers[dic[key].at(pos)]++;
	dic[key]=order(dic[key],pos);
	return 0;
}

// orders words in 'list', while reading them from 'cin'
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


// gets key for the word 
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

// adds puncts to dictionary with key 1
int push_puncts()
{
	dic[1].reserve(puncts_num);
	//if (strlen(puncts)<puncts_num) {err="invalid puncts";return 1;}
	for (int i=0; i<puncts_num; i++)
	{
		char* a=new char[1]; a[0] = puncts[i];
		words.push_back(new char[1]);
		strcpy(words.back(),a);
		dic[1].push_back(words.back());
	}
	return 0;
}

// reads and composes dictionary and preferences ('dic', 'prefers') from 'cin'
int read_dic()
{
	cin >> N;
	if (N<min_dic_len) {cout << "bad N value"; return 1;}
	
	char wordbuf[max_word_len]; //used for reading words from 'cin'
	char* l_word; //stores current processing word
	int key;
		
	words.reserve(N);
	push_puncts();
	
	for (int i=0; i<N; i++)
	{
		// gets a word
		cin.getline(wordbuf,max_word_len,' ');
		words.push_back(new char[strlen(wordbuf)-1]);
		l_word = words.back();
		strcpy(l_word, &wordbuf[1]);	
		// gets key for the word
		key = get_key(l_word);
		if (dic[key].size()==0) {dic[key].reserve(1);}
		// gets the word's frequency and pushes it to dictionary according to it
		cin >> prefers[l_word];
		dic[key].push_back(l_word);
		dic[key] = global_order(dic[key], dic[key].size()-1);
	}
	return 0;
}


int set_keyboard_and_puncts()
{
	puncts[0] = '?'; puncts[1] = ','; puncts[2] = '.';
	keyboard['a'] = 2; keyboard['b'] = 2; keyboard['c'] = 2;
	keyboard['d'] = 3; keyboard['e'] = 3; keyboard['f'] = 3;
	keyboard['g'] = 4; keyboard['h'] = 4; keyboard['i'] = 4;
	keyboard['j'] = 5; keyboard['k'] = 5; keyboard['l'] = 5;
	keyboard['m'] = 6; keyboard['n'] = 6; keyboard['o'] = 6;
	keyboard['p'] = 7; keyboard['q'] = 7; keyboard['r'] = 7; keyboard['s'] = 7;
	keyboard['w'] = 9; keyboard['x'] = 9; keyboard['y'] = 9; keyboard['z'] = 9;
	keyboard['t'] = 8; keyboard['u'] = 8; keyboard['v'] = 8;
	return 0;
}

int main()
{
	//if(set_keyboard()) {cout<<err; return 1;}
	set_keyboard_and_puncts();

	// reads and composes dictionary and preferences ('dic', 'prefers') from 'cin'
	//if(read_dic()) {cout<<err; return 1;}
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