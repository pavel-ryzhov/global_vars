#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef ::string TKey;
typedef ::string TWord;

//string err;
const int puncts_num=3, min_dic_len=3, max_dic_len=50000, max_freg = 1000, max_word_len=20, max_sms_len=100000;
int N=0;
TWord* puncts;
map<char, char> keyboard;


map<TKey, vector<TWord> > dic;
map<TWord, int> prefers;

// orders words in list, according to their preferences. 
// recursive. starts from 'list[n]'.
// assumes, that preferences can only increment.
vector<TWord> order(vector<TWord> list, unsigned int n)
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
int print_word(TKey& key, int& pref)
{
	if (key.length()) 
	{
		vector<TWord> list = dic[key];
		int len = list.size(); //number of words with key 'key'
		int pos;
		pos = len - 1 - pref % len; //position of the required word in list='dic[key]'
		// the vector 'dic[key]' acts here as a circle
		TWord output = list.at(pos);
		cout << output;
		// puncts ('dic["1"]') shouldn't change preferences
		if (key!=TKey("1")) 
		{
			prefers[output]++;
			dic[key]=order(list,pos);			
		}
		key=""; 
		pref = 0;
	}
	return 0;
}

// orders words in 'list' according to their preferences.
// recursive. starts from 'list[n]'.
// used while first reading from 'cin'
vector<TWord> global_order(vector<TWord>& list, int n)
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
	dic["1"].reserve(puncts_num);
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
	
	TWord wordbuf = ""; //stores current processing word
	vector<TWord> list; //stores current processing 'dic' part
	TKey key = "";
		
	push_puncts(); // adds 'puncts' to dictionary with key "1"
	
	for (int i=0; i<N; i++)
	{
		// gets a word
		input >> wordbuf;
		// gets key for the word
		key = get_key(wordbuf);
		// gets the word's frequency and pushes it to dictionary according to it
		input >> prefers[wordbuf];
		list = dic[key];
		list.push_back(wordbuf);
		dic[key] = global_order(list, list.size()-1);
	}
	return 0;
}


int set_keyboard_and_puncts()
{
	puncts = new TWord[puncts_num];
	puncts[0] = '?';
	puncts[1] = ','; 
	puncts[2] = '.';
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
	string tmp = "test";
	std::istream* in = &cin;
	fstream fin;
	
	if (argc > 1)
	{
	if (string(argv[1]) == tmp)
	{
		std::cout << "file reading..." << std::endl;
		fin.open(tmp.c_str());
		in = &fin;
		std::cout << "file reading...OK" << std::endl;
	}}
	
	read_dic(*in);

	TKey key="";
	int i=0, pref=0;
	char* sms=new char[max_sms_len+1];
	*in >> sms[0];
	(*in).getline(sms+1,max_sms_len);
	int sms_len=(*in).gcount();

	while(i<sms_len)
	{
		char symb = sms[i];
		switch (symb)
		{
		default:
			key += symb;
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
	i++;
	}
	print_word(key,pref);
	return 0;
}