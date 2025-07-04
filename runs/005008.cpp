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
typedef ::pair<TWord, int> TWrdfreq;

//string err;
const int puncts_num=3, min_dic_len=3, max_dic_len=50000, max_freg = 1000, max_word_len=20, max_sms_len=100000;
int N=0;
TWrdfreq* puncts;
const char keyboard[26]={'2','2','2','3','3','3','4','4','4','5','5','5','6','6','6','7','7','7','7','8','8','8','9','9','9','9'};

map<TKey, vector<TWrdfreq> > dic;

// orders words in list, according to their preferences. 
// assumes, that preferences can only increment.
inline void order(vector<TWrdfreq>& list, const int& pos, const int& len)
{
	int w_pos = pos;
	TWrdfreq word = list[pos];
	int pref = word.second;
	for (; w_pos!=len-1 && pref >= list[w_pos+1].second; ++w_pos) ;
	if(pos!=w_pos) 
	{
		list.erase(list.begin()+pos);
		list.insert(list.begin()+w_pos,word);
	}
}

// prints the word to cout (word='dic[key][pref]')
inline int print_word(TKey& key, int& pref)
{
	if (key.length()==0) return 0; //empty key shouldn't be processed.
	vector<TWrdfreq>& list = dic[key];
	int len = list.size(); //number of words with key 'key'
	if (len==0) return 1; //no words by this key in dictionary, should be an error. 
	int pos = len - 1 - pref % len; //position of the required word in list='dic[key]'
	// the vector 'dic[key]' acts here as a circle
	TWrdfreq& output = list[pos];
	cout << output.first;
	// puncts ('dic["1"]') and lonely words shouldn't change preferences
	if (key!=TKey("1") && len>1) 
	{
		output.second++;
		order(list,pos,len);			
	}
	key=""; 
	pref = 0;
	return 0;
}

// puts 'word' in 'list' according to it's preference.
inline void push_word(vector<TWrdfreq>& list, const TWrdfreq& word)
{
	int len = list.size();
	if (len) 
	{
		int pref = word.second;
		int pos = len-1;
		int pos0 = 0;
		bool condi1 = pos==0 || pref > list[pos-1].second;
		bool condi2 = pref <= list[pos].second;
		while(!condi1 || !condi2)
		{
			if (!condi2) pos0=pos+1;
			if (!condi1) len=pos;
			pos = (pos0 + len)/2;
			if (pos0==len) break;
			condi1 = pos==0 || pref > list[pos-1].second;
			condi2 = pref <= list[pos].second;
		
		}
		list.insert(list.begin()+pos,word);
	}
	else {list.push_back(word);}
}


// gets key for the 'word' 
inline TKey get_key(const TWord& word)
{
	TKey key = "";
	int w_len = word.length();
	
	for (int i=0; i<w_len; ++i)
	{
		key += keyboard[word[i] - 'a'];
	}
	return key;
}

// adds puncts to dictionary with key "1"
inline int push_puncts()
{
	//if (puncts.length()<puncts_num) {err="invalid puncts";return 1;}
	for (int i=0; i<puncts_num; ++i)
	{
		dic["1"].push_back(puncts[i]);
	}
	return 0;
}

// reads and composes dictionary and preferences ('dic', 'prefers') from 'cin'
inline int read_dic(istream& input)
{
	input >> N;
	//if (N<min_dic_len) {err = "bad N value"; return 1;}
	
	TWrdfreq wordbuf = TWrdfreq("",-1); //stores current processing word
	
    push_puncts(); // adds 'puncts' to dictionary with key "1"
	
	for (int i=0; i<N; i++)
	{
		// gets a word
		input >> wordbuf.first;
		// gets the word's frequency and pushes it to dictionary according to it
		input >> wordbuf.second;
		push_word(dic[get_key(wordbuf.first)], wordbuf);
	}
	return 0;
}


int set_puncts()
{
	puncts = new TWrdfreq[puncts_num];
	puncts[0] = TWrdfreq("?",0);
	puncts[1] = TWrdfreq(",",0); 
	puncts[2] = TWrdfreq(".",0);
	return 0;
}

int main(int argc, char* argv[])
{
	//if(set_keyboard()) {cout<<err; return 1;}
	set_puncts();

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
			++pref;
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