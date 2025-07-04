#include <set>
#include <string>
#include <vector>
#include <string>
#include <cctype>
#include <cassert>
#include <iostream>
#include <fstream>

using namespace std;

int t9_get_digit(char keypressed)
{
	static int keymap[26] = 
			{2, 2, 2,		// a, b, c
			 3, 3, 3,		// d, e, f
			 4, 4, 4,		// g, h, i
			 5, 5, 5,		// j, k, l
			 6, 6, 6,		// m, n, o
			 7, 7, 7, 7,	// p, q, r, s
			 8, 8, 8,		// t, u, v
			 9, 9, 9, 9};	// w, x, y, z

	return keymap[keypressed - 'a'];
};

struct T9_entry
{
	string str;
	int freq; 
	int time;

	T9_entry(string data, int frequency, int time_added) : str(data), freq(frequency), time(time_added) {};
	bool operator< (const T9_entry &another) const
	{
		/*this->print(cout);
		another.print(cout);*/

		bool res = (this->freq > another.freq) || (this->freq == another.freq && this->time > another.time);
		/*cout << "   " << res; 
		cout << endl;*/
		
		return res; 
	}
	ostream &print(ostream &stream) const
	{
		return stream << this->str << " " << this->freq << " " << this->time;
	}
};

ostream &operator <<(ostream &stream, const T9_entry &entry) 
{
	return entry.print(stream);
}

void t9_print(set<T9_entry>::iterator iter) // usefull for gdb debugging
{
	cerr << *iter;
}

struct Trie_node
{
	Trie_node() : links(10), term(false), entries() {};
	vector<int> links;
	bool term; // is it terminal
	set<T9_entry> entries; // entries that are present in this terminal node;
};

class Trie // prefix tree
{
	public:
		Trie() : count(1), trie_(1) {};
		set<T9_entry> &add(T9_entry entry);
		set<T9_entry> &lookup(string str); 
	private:
		int count; // number of nodes
		vector<Trie_node> trie_;
};

set<T9_entry> &Trie::add(T9_entry word)
{
	int node_num = 0;

	for (unsigned int i = 0; i < word.str.length(); i++)
	{
		int digit = t9_get_digit(word.str[i]);

		if (trie_[node_num].links[digit] == 0)
		{
			count++;
			trie_.resize(count);
			trie_[node_num].links[digit] = count - 1;
		}
		node_num = trie_[node_num].links[digit];
	}
	trie_[node_num].term = true;

	return trie_[node_num].entries;
}

set<T9_entry> &Trie::lookup(string str)
{
	int node_num = 0;

	for (unsigned int i = 0; i < str.length(); i++)
	{
		int digit = str[i] - '0';

		assert(trie_[node_num].links[digit] != 0); // we always have entry in dictionary during lookup
		node_num = trie_[node_num].links[digit];
	}
	assert(trie_[node_num].term); // same as above
	
	return trie_[node_num].entries;
}

int main()
{
	int n;
	int time = 0;
	Trie trie;

	cin >> n;

	for (int i = 0; i < n; i++)
	{
		string str;
		int freq;
		
		cin >> str >> freq;
		
		T9_entry word(str, freq, n - i); // such magic value of time is used to add words in correct order
		trie.add(word).insert(word); 
	}
	
	time = n + 1;
	char c;
	bool punct_mark = false;
	string str;
	int asterisk_num = 0;
//	while (cin.get(c))
	do // while (!cin.eof())
	{
		cin.get(c);
		if (isdigit(c) && c != '1') 
			str += c;
				
		if (c == '*') 
			asterisk_num++;

		if (isdigit(c) || c == '1' || c == ' ' || cin.eof()) // if character is from correct input set, i.e. not a newline, for example
			if (punct_mark) 
			{
				cout << ".,?"[asterisk_num % 3];
				punct_mark = false;
				asterisk_num = 0;
			}
		if (c == '1' || c == ' ' || cin.eof())
		{
			if (!str.empty()) // user was entering string
			{
				set<T9_entry> &wordlist = trie.lookup(str);
				set<T9_entry>::iterator iter = wordlist.begin();

				for (int i = 0; i < asterisk_num; i++)
					iter++;
				T9_entry selected = *iter;
				wordlist.erase(iter);
				
				selected.freq += 1;
				selected.time = time;
				wordlist.insert(selected);
				cout << selected.str;
				
				str = "";
				time++;
			}

			if (c == ' ') cout << ' ';
			asterisk_num = 0;
			punct_mark = c == '1';
		}
	}
	while (!cin.eof());
}
