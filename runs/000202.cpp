#include <map>
#include <iostream>
#include <string>
#include <set>

using std::map;
using std::set;
using std::string;
using std::cin;
using std::cout;

char buttons[] = "22233344455566677778889999";

struct Entry
{
	int freq;
	int use;
	string word;

	bool operator<(const Entry& s) const
	{
		if ( freq > s.freq ) return true;
		if ( freq < s.freq ) return false;
		if ( use > s.use ) return true;
		if ( use < s.use ) return false;
		return word < s.word;
	}

};

typedef map<string, set<Entry> > Dictionary;

void input_data(Dictionary& dict)
{
	int n;
	Entry ent;
	ent.use = 0;
	cin >> n;
	for ( int i=0; i<n; ++i )
	{
		char c;
		string key;
		cin >> c >> c; // read '\n' first, than first letter of the word
		ent.word = "";
		while ( c != ' ' )
		{
			ent.word += c;
			key += buttons[c-'a'];
			cin >> c;
		}
		cin >> ent.freq;
		dict[key].insert(ent);
	}
	ent.freq=2; ent.use=0; ent.word=".";
	dict["1"].insert(ent);
	ent.freq=1; ent.use=0; ent.word=",";
	dict["1"].insert(ent);
	ent.freq=0; ent.use=0; ent.word="?";
	dict["1"].insert(ent);
}

void write_word(Dictionary& dict, string& key, const set<Entry>::iterator& i, int& use)
{
	Entry tmp(*i);
	cout << i->word;
	dict[key].erase(i);
	++tmp.freq;
	tmp.use = ++use;
	dict[key].insert(tmp);
	key = "";
}

void write_punctuation(string& key, set<Entry>::iterator i)
{
	cout << i->word;
	key = "";
}

set<Entry>::iterator set_iterator(Dictionary& dict, const string& key, int& asterisk)
{
	set<Entry>::iterator res;
	res = dict[key].begin();
	while ( asterisk )
	{
		++res;
		--asterisk;
	}

	return res;
}

void write_string(Dictionary& dict) 
{
	enum state {BLANK, WORD, PUNCTUATION};

	string res, key;
	state prevstate=BLANK;
	char c;
	int asterisk=0;
	int use=0;
	set<Entry>::iterator i;
	cin >> c >> c; // read '\n' at first
	while ( !cin.eof() && (c != '\n') ) // '\n' is needed when cin is from file
	{
		if ( c == ' ' )
		{
			switch ( prevstate )
			{
				case WORD:
					i = set_iterator(dict, key, asterisk);
					write_word(dict, key, i, use);
					break;
				case PUNCTUATION:
					i = set_iterator(dict, key, asterisk);
					write_punctuation(key, i);
					break;
			}
			cout << ' ';
			prevstate = BLANK;
		}	
		else if ( c == '1' )
		{
			switch ( prevstate )
			{
				case WORD:
					i = set_iterator(dict, key, asterisk);
					write_word(dict, key, i, use);
					break;
				case PUNCTUATION:
					i = set_iterator(dict, key, asterisk);
					write_punctuation(key, i);
					break;
			}
			key = "1";
			prevstate = PUNCTUATION;
		}
		else if ( c == '*' )
		{
			++asterisk;	
		}
		else // mean c is a digit between 2 and 9
		{
			if ( prevstate == PUNCTUATION )
			{
				i = set_iterator(dict, key, asterisk);
				write_punctuation(key, i);
			}
			prevstate = WORD;
			key += c;
		}
		cin >> c;
	}
	switch ( prevstate )
	{
		case WORD:
			i = set_iterator(dict, key, asterisk);
			write_word(dict, key, i, use);
			break;
		case PUNCTUATION:
			i = set_iterator(dict, key, asterisk);
			write_punctuation(key, i);
			break;
	}
}

int main()
{
	cin >> std::noskipws;
	Dictionary dict;
	string res;
	input_data(dict);
	write_string(dict);
	return 0;
}

