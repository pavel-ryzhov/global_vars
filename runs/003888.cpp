#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using std::cin;
using std::cout;
using std::istream;
using std::ostream;
using std::list;
using std::vector;
using std::map;
using std::multimap;
using std::string;
using std::pair;

void read_input_data(istream& in, vector< pair<string, int> >* words_freq,
	string* message_code)
{
	int number_of_words;
	in >> number_of_words;
	
	words_freq->clear();
	words_freq->resize(number_of_words);
	
	for (int index = 0; index < number_of_words; ++index)
	{
		in >> (*words_freq)[index].first;
		in >> (*words_freq)[index].second;
	}
	in.get();
	
	getline(in, *message_code);
}

struct keyboard
{
	vector<string> buttons;

	keyboard(): buttons(9)
	{
        buttons[0] = ".,?";
        buttons[1] = "abc";
        buttons[2] = "def";
        buttons[3] = "ghi";
        buttons[4] = "jkl";
        buttons[5] = "mno";
        buttons[6] = "pqrs";
        buttons[7] = "tuv";
        buttons[8] = "wxyz";
	}
};

const keyboard KEYBOARD;

const string& get_button_inscription(int button_number)
{
	return KEYBOARD.buttons[button_number - 1];
}

const string& get_button_inscription(char button)
{
	return KEYBOARD.buttons[button - '0' - 1];
}

int button_number(char symbol)
{
	int button_number = 0;
	while (button_number < static_cast<int>(KEYBOARD.buttons.size()) &&
		find(KEYBOARD.buttons[button_number].begin(),
			KEYBOARD.buttons[button_number].end(), symbol) ==
				KEYBOARD.buttons[button_number].end())
   	{
		++button_number;
	}

	return button_number + 1;
}

string word_buttons_code(const string& word)
{
	string word_buttons_code;

	word_buttons_code.resize(word.size());

	for (int index = 0; index < static_cast<int>(word.size()); ++index)
	{
		word_buttons_code[index] =
			static_cast<char>('0' + button_number(word[index]));
	}

	return word_buttons_code;
}

//attempt = 0, 1, 2, ...
char get_mark(int attempt)
{
	return KEYBOARD.buttons[0][attempt];
}

class t9_dictionary
{
	map <string, multimap<int, string> > m_dictionary;

public:

 	t9_dictionary()
	{ }

	t9_dictionary(const vector< pair<string, int> >& words_freq)
 	{
		for (int index = static_cast<int>(words_freq.size()) - 1; index >= 0; --index)
		{
			m_dictionary[word_buttons_code(words_freq[index].first)].insert(
			    make_pair(words_freq[index].second, words_freq[index].first));
		}
 	}
	
	//attempt = 0, 1, 2, ...
    string get_word(const string& buttons_code, int attempt)
	{
		multimap<int, string>::iterator word_freq_iter =
			--m_dictionary[buttons_code].end();

		for (int current_attempt = 0; current_attempt < attempt; ++current_attempt)
		{
			--word_freq_iter;
		}

		string word_to_return = word_freq_iter->second;
		int current_freq = word_freq_iter->first;

		m_dictionary[buttons_code].erase(word_freq_iter);
        m_dictionary[buttons_code].insert(
			make_pair(current_freq + 1, word_to_return));

		return word_to_return;
	}
	
};

const char NEXT_ATTEMPT = '*';
const char MARK = '1';
const char SPACE = ' ';

struct block
{
    string word;
	int attempt;

	block()
	{ }
	
	block(const string& block_word, int word_attempt):
		word(block_word), attempt(word_attempt)
	{ }
};

bool is_mark(const block& current_block)
{
	return current_block.word[0] == MARK;
}

bool is_space(const block& current_block)
{
	return current_block.word[0] == SPACE;
}

void get_block(const string& message_code, int block_begin,
	block* current_block, int* next_block_begin)
{
 	if (message_code[block_begin] == SPACE)
	{
		int index = block_begin;
		
		while (index < static_cast<int>(message_code.size())
			&& message_code[index] == SPACE)
		{
			++index;
		}
		
		*next_block_begin = index;

		*current_block = block(
			message_code.substr(block_begin, *next_block_begin - block_begin), 0);
	}

	else if (message_code[block_begin] == MARK)
	{
		int index = block_begin + 1;
		while (index < message_code.size() && message_code[index] == NEXT_ATTEMPT)
		{
			++index;
		}
		*next_block_begin = index;

		*current_block = block(message_code.substr(block_begin, 1),
			*next_block_begin - block_begin - 1);
	}
	
	else
 	{
		int index = block_begin;
		while (
			index < static_cast<int>(message_code.size()) &&
			message_code[index] != NEXT_ATTEMPT &&
			message_code[index] != MARK && message_code[index] != SPACE)
		{
			++index;
		}

		string word = message_code.substr(block_begin, index - block_begin);

		int attempt = 0;
		while (index + attempt < static_cast<int>(message_code.size()) &&
			message_code[index + attempt] == NEXT_ATTEMPT)
		{
            ++attempt;
		}

		*current_block = block(word, attempt);
		
		*next_block_begin = index + attempt;
	}
			
}

void split_into_blocks(const string& message_code, list<block>* blocks)
{
	blocks->clear();

	int block_begin = 0;

	while (block_begin != static_cast<int>(message_code.size()))
	{
		int next_block_begin;

		block current_block;

		get_block(message_code, block_begin, &current_block, &next_block_begin);

        blocks->push_back(current_block);

		block_begin = next_block_begin;
	}
}

void decode_buttons_sequence(const string& message_code,
	t9_dictionary& dictionary, string* message)
{
	message->clear();

	list<block> blocks;
	
	split_into_blocks(message_code, &blocks);
	
	for (list<block>::const_iterator current_block = blocks.begin();
	    current_block != blocks.end(); ++current_block)
 	{
		if (is_mark(*current_block))
		{
			message->push_back(get_mark(current_block->attempt));
		}

		else if(is_space(*current_block))
		{
			message->append(current_block->word);
		}
		
		else
		{
			message->append(dictionary.get_word(current_block->word,
				current_block->attempt));
		}
	}

}

void write_message(ostream& out, const string& message)
{
	out << message;
}

int main()
{
 	vector< pair<string, int> > words_freq;
	string message_code;
	
	read_input_data(cin, &words_freq, &message_code);
	
	t9_dictionary dictionary(words_freq);
	
	string message;
	
	decode_buttons_sequence(message_code, dictionary, &message);
	
	write_message(cout, message);
	
	return 0;
}
