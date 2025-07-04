#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

typedef ::string TKey;
typedef ::string TWord;
typedef ::pair<TWord,int> TWrdfreq;

//string err;
const int puncts_num=3, min_dic_len=3, max_dic_len=50000, max_freg = 1000, max_word_len=20, max_sms_len=100000;
int N=0;
TWrdfreq* puncts;
map<char, char> keyboard;

map<TKey, vector<TWrdfreq> > dic;

// orders words in list, according to their preferences. 
// recursive. starts from 'list[n]'.
// assumes, that preferences can only increment.
void order(vector<TWrdfreq>& list, unsigned int n)
{
	if (n<list.size()-1)
	{
		if (! (list[n].second < list[n+1].second))
		{
			swap(list[n],list[n+1]);
			order(list, n+1);
		}
	}
}

// prints the word to cout (word='dic[key][pref]')
int print_word(TKey& key, int& pref)
{
	vector<TWrdfreq>& list = dic[key];
	int len = list.size(); //number of words with key 'key'
	if (len==0) return 1;
	if (key.length()) 
	{
		int pos = len - 1 - pref % len; //position of the required word in list='dic[key]'
		// the vector 'dic[key]' acts here as a circle
		TWrdfreq& output = list[pos];
		cout << output.first;
		// puncts ('dic["1"]') and lonely words shouldn't change preferences
		if (key!=TKey("1") && len>1) 
		{
			output.second++;
			order(list,pos);			
		}
		key=""; 
		pref = 0;
	}
	return 0;
}

// puts 'word' in 'list' according to it's preference.
void push_word(vector<TWrdfreq>& list, TWrdfreq word)
{
	if (list.size()!=0) 
	{
		int pref = word.second;
		vector< TWrdfreq >::iterator l_end = list.end();
		vector<TWrdfreq>::iterator pos = list.begin();
		for (; pos!=l_end && pref > (*pos).second; ++pos) ;
		list.insert(pos,word);
	}
	else {list.push_back(word);}
}


// gets key for the 'word' 
TKey get_key(TWord word)
{
	TKey key = "";
	int w_len = word.length();
	
	for (int i=0; i<w_len; i++)
	{
		key += keyboard[word[i]];
	}
	return key;
}

// adds puncts to dictionary with key "1"
int push_puncts()
{
	//if (puncts.length()<puncts_num) {err="invalid puncts";return 1;}
	for (int i=0; i<puncts_num; i++)
	{
		dic["1"].push_back(puncts[i]);
	}
	return 0;
}

// reads and composes dictionary and preferences ('dic', 'prefers') from 'cin'
int read_dic(istream& input)
{
	input >> N;
	//if (N<min_dic_len) {err = "bad N value"; return 1;}
	
	TWrdfreq wordbuf = TWrdfreq("",-1); //stores current processing word
	TKey key = "";
		
	push_puncts(); // adds 'puncts' to dictionary with key "1"
	
	for (int i=0; i<N; i++)
	{
		// gets a word
		input >> wordbuf.first;
		// gets key for the word
		key = get_key(wordbuf.first);
		// gets the word's frequency and pushes it to dictionary according to it
		input >> wordbuf.second;
		push_word(dic[key],wordbuf);
	}
	return 0;
}


int set_keyboard_and_puncts()
{
	puncts = new TWrdfreq[puncts_num];
	puncts[0] = TWrdfreq("?",0);
	puncts[1] = TWrdfreq(",",0); 
	puncts[2] = TWrdfreq(".",0);
	keyboard['a'] = '2'; keyboard['b'] = '2'; keyboard['c'] = '2';
	keyboard['d'] = '3'; keyboard['e'] = '3'; keyboard['f'] = '3';
	keyboard['g'] = '4'; keyboard['h'] = '4'; keyboard['i'] = '4';
	keyboard['j'] = '5'; keyboard['k'] = '5'; keyboard['l'] = '5';
	keyboard['m'] = '6'; keyboard['n'] = '6'; keyboard['o'] = '6';
	keyboard['p'] = '7'; keyboard['q'] = '7'; keyboard['r'] = '7'; keyboard['s'] = '7';
	keyboard['w'] = '9'; keyboard['x'] = '9'; keyboard['y'] = '9'; keyboard['z'] = '9';
	keyboard['t'] = '8'; keyboard['u'] = '8'; keyboard['v'] = '8';
	return 0;
}

int main(int argc, char* argv[])
{
	//if(set_keyboard()) {cout<<err; return 1;}
	set_keyboard_and_puncts();

	// reads and composes dictionary and preferences ('dic', 'prefers') from 'cin'
	//if(read_dic()) {cout<<err; return 1;}
	string tmp;
	std::istream* in = &cin;
	fstream fin;	
	if (argc > 1)
	{
		// sets, if it's test making mode
		//if (string(argv[1]) == tmp2) {maketest(); return 0;}
		tmp = string(argv[1]);
		std::cout << "file reading..." << std::endl;
		fin.open(tmp.c_str());
		in = &fin;
		std::cout << "file reading...OK" << std::endl;
	}
	
	read_dic(*in);

	TKey key="";
	int pref=0;
	char symbol;
	*in >> symbol;

	while(symbol != '\n')
	{
		switch (symbol)
		{
		default:
			if (key=="1") print_word(key,pref);
			key += symbol;
			break;
		case '*' :
			pref++;
			break;
		case ' ':
			print_word(key,pref);
			cout << ' '; 
			break;
		case '1':
			print_word(key,pref);
			key="1";
			break;
		}
	(*in).get(symbol);
	}
	print_word(key,pref);
	return 0;

	return 0;
}