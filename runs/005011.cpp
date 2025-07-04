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
TWrdfreq puncts[puncts_num]={TWrdfreq("?",0), TWrdfreq(",",0), TWrdfreq(".",0)};
const char keyboard[26]={'2','2','2','3','3','3','4','4','4','5','5','5','6','6','6','7','7','7','7','8','8','8','9','9','9','9'};

map<TKey, vector<TWrdfreq> > dic;

// orders words in list, according to their preferences. 
// assumes, that preferences can only increment.
inline void order(vector<TWrdfreq>& list, int& pos, const int& len)
{
	int pref = list[pos].second;
    for (; pos!=len-1 && pref >= list[pos+1].second; ++pos) {
        swap (list[pos],list[pos+1]);
    }
}

// prints the word to cout (word='dic[key][pref]')
inline void print_word(const TKey& key, const int& pref)
{
	if (key.length()==0) return; //empty key shouldn't be processed.
	vector<TWrdfreq>& list = dic[key];
	int len = list.size(); //number of words with key 'key'
	if (len==0) return; //no words by this key in dictionary, should be an error. 
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
}

// puts 'word' in 'list' according to it's preference.
inline void push_word(vector<TWrdfreq>& list, const TWrdfreq& word)
{
	int len = list.size();
	int pref = word.second;
    if (len && pref <= list[len-1].second) {
        int pos = 0;
        if (pref > list[0].second) {
            pos = len/2;
            while (len != pos) {
                if (pref > list[(pos+len)/2].second) {
                    pos++;
                }
                else {
                    len = (pos+len)/2;
                }
            }
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
	
	for (int i=0; i<w_len; ++i) {
		key += keyboard[word[i] - 'a'];
	}
	return key;
}

// adds puncts to dictionary with key "1"
inline void push_puncts()
{
	//if (puncts.length()<puncts_num) {err="invalid puncts";return 1;}
	for (int i=0; i<puncts_num; ++i) {
		dic["1"].push_back(puncts[i]);
	}
}

// reads and composes dictionary ('dic') from '*in'
inline void read_dic(istream& input)
{
	push_puncts(); // adds 'puncts' to dictionary with key "1"
	
    input >> N;
	
	TWrdfreq wordbuf = TWrdfreq("",-1); //stores current processing word
	
	for (int i=0; i<N; i++)
	{
		// gets a word
		input >> wordbuf.first;
		// gets the word's frequency and pushes it to dictionary according to it
		input >> wordbuf.second;
		push_word(dic[get_key(wordbuf.first)], wordbuf);
	}
}

int main(int argc, char* argv[])
{
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
            if (key=="1") {
                print_word(key,pref);
                key="";
                pref=0;
            }
			key += symbol;
			break;
		case '*' :
			++pref;
			break;
		case ' ':
            print_word(key,pref);
            key="";
            pref=0;
            cout << ' '; 
			break;
		case '1':
			print_word(key,pref);
            pref=0;
            key="1";
			break;
		}
	(*in).get(symbol);
	}
	print_word(key,pref);
	return 0;

}