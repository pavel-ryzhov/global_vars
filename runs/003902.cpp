//problem C: T9
//Mikhail Zhirnoff, 2011
//m-a-zhirnoff@yandex.ru

#include <iostream>
#include <string>
#include <map>

using std::string;
using std::multimap;

//dictionary class, B-tree-based
//nodes represent digits of digital sequences corresponding to words
class Cdict
{
public:
	Cdict () { zero_node = new node; node_p = zero_node; }
	~Cdict () { delete zero_node; }

	//word adding method
	//adds word into dictionary
	//takes std::string with word and unsigned int with initial usage frequency
	//returns TRUE if new digital sequence has been registered, FALSE if word matches existing sequence
	bool add_word (const string& word_str, const unsigned int& initial_frequency);

	//word finding methods
	//one step of search for words of given digital sequence through the tree
	void input_digit (const char& digit);
	//returns std::string with word, alters one word_opts_t according to change of usage frequency 
	string retrieve_word (const unsigned int& ast_count);

private:
	//multimap-based class storing words with same T9 digital sequence sorted by usage frequency and in alphabetical order
	class word_opts_t : private multimap<unsigned int, string, std::greater<unsigned int> >
	{
	public:
		void add_word (const string& word_str, const unsigned int& freq);
		string retrieve_word (const unsigned int& ast_count);
	};

	struct node
	{
		word_opts_t* word_opts;
		//index+2 means digit
		node* branch[8];

		node();
		~node();
	};

	node* zero_node;
	node* node_p;

	//convert letter to T9 digit
	inline unsigned int to_digit (const char);

};

bool Cdict::add_word (const string& word_str, const unsigned int& init_freq)
{
	bool new_ds = false; //returning value
	int d_index;
	for (string::const_iterator it = word_str.begin(), end = word_str.end(); it != end; ++it)
	{
		d_index = to_digit(*it) - 2;
		if (node_p->branch[d_index] == NULL)
			node_p->branch[d_index] = new node;
		node_p = node_p->branch[d_index];
	}

	if (node_p->word_opts == NULL)
	{
		node_p->word_opts = new word_opts_t;
		new_ds = true;
	}
	node_p->word_opts->add_word(word_str, init_freq);

	node_p = zero_node;
	return new_ds;
}

void Cdict::input_digit (const char& digit)
{
	node_p = node_p->branch[digit - '2'];
}

string Cdict::retrieve_word (const unsigned int& ast_count)
{
	node* ret_node = node_p;
	node_p = zero_node;
	return ret_node->word_opts->retrieve_word(ast_count);
}

unsigned int Cdict::to_digit (const char ch)
{
	switch (ch)
	{
	case'a':
	case'b':
	case'c':
		return 2;
	case'd':
	case'e':
	case'f':
		return 3;
	case'g':
	case'h':
	case'i':
		return 4;
	case'j':
	case'k':
	case'l':
		return 5;
	case'm':
	case'n':
	case'o':
		return 6;
	case'p':
	case'q':
	case'r':
	case's':
		return 7;
	case't':
	case'u':
	case'v':
		return 8;
	case'w':
	case'x':
	case'y':
	case'z':
		return 9;
	default:
		throw 0;
		return 0;
	}
}

void Cdict::word_opts_t::add_word (const string& word_str, const unsigned int& freq)
{
	insert(std::make_pair(freq, word_str));
}

string Cdict::word_opts_t::retrieve_word (const unsigned int& ast_count)
{
	string word_str;
	unsigned int freq;

	iterator it;
	if (ast_count <= size()/2)
	{
		it = begin();
		for (unsigned int i = 0; i < ast_count; ++i)
			++it;
	}
	else
	{
		it = end();
		for (unsigned int i = size(); i > ast_count; --i)
			--it;
	}

	word_str = it->second;
	freq = it->first + 1;

	erase(it);

	insert(equal_range(freq).first, std::make_pair(freq, word_str));

	return word_str;
}

Cdict::node::node()
{
	word_opts = NULL;
	for (int i = 0; i < 8; ++i) branch[i] = NULL;
}
		
Cdict::node::~node()
{
	if (word_opts != NULL)
		delete word_opts;
	for (int i = 0; i < 8; ++i)
		if (branch[i] != NULL)
			delete branch[i];
}

int main()
{
	using std::cin;
	using std::cout;

	
	//declarations
	unsigned int dict_size;
	Cdict dict;
	//buffers
	char ch;
	string str;
	unsigned int x;

	//dictionary building
	cin >> dict_size;
	for (unsigned int i = 0; i < dict_size; ++i)
	{
		cin >> str >> x;
		dict.add_word(str, x);
	}

	//message text decoding
	cin >> std::noskipws;
	cin >> std::ws;

	//markov model: (input character, mode) -> (output string, mode)
	enum { new_lexem, punct_0, punct_1,	word } mode = new_lexem;
	int asterisks = 0;
	for (cin >> ch; !(cin.eof()); cin >> ch)
	{
		switch (mode)
		{
		case new_lexem:
			switch (ch)
			{
			case' ':
				cout << ' ';
				break;
			case'*':
				throw 0;
				break;
			case'1':
				mode = punct_0;
				break;
			default: //digits 2 to 9
				mode = word;
				dict.input_digit(ch);
			}
			break;
		case punct_0:
			switch (ch)
			{
			case' ':
				cout << '.' << ' ';
				mode = new_lexem;
				break;
			case'*':
				mode = punct_1;
				break;
			case'1':
				cout << '.';
				break;
			default:
				cout << '.';
				mode = word;
				dict.input_digit(ch);
			}
			break;
		case punct_1:
			switch (ch)
			{
			case' ':
				cout << ',' << ' ';
				mode = new_lexem;
				break;
			case'*':
				cout << '?';
				mode = new_lexem;
				break;
			case'1':
				cout << ',';
				mode = punct_0;
				break;
			default:
				cout << ',';
				mode = word;
				dict.input_digit(ch);
			}
			break;
		case word:
			switch (ch)
			{
			case' ':
				cout << dict.retrieve_word(asterisks) << ' ';
				asterisks = 0;
				mode = new_lexem;
				break;
			case'*':
				++asterisks;
				break;
			case'1':
				cout << dict.retrieve_word(asterisks);
				asterisks = 0;
				mode = punct_0;
				break;
			default:
				dict.input_digit(ch);
			}
		}
	}

	switch (mode)
	{
	case punct_0:
		cout << '.';
		break;
	case punct_1:
		cout << ',';
		break;
	case word:
		cout << dict.retrieve_word(asterisks);
	}

	return 0;
}