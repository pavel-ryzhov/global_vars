#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <map>
#include <set>
#include <list>

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::pair;
using std::find;
using std::make_pair;
using std::endl;
using std::swap;
using std::set;
using std::map;
using std::list;
using std::sort;

struct word_with_frequency
{
	string word;
	int frequency;
	word_with_frequency ( string word_, int frequency_) :
	word(word_), frequency(frequency_ )
	{
	}
	
};

struct separated_word
{
	string word_in_numeric;
	int number_stars_after_word;
	bool is_1;
	int number_stars_after_1;
	int number_gap;
	separated_word (string word_in_numeric_, int number_stars_after_word_, bool is_1_,
	int number_stars_after_1_,int number_gap_ ):
	word_in_numeric(word_in_numeric_), number_stars_after_word(number_stars_after_word_),
	is_1(is_1_), number_stars_after_1(number_stars_after_1_), number_gap(number_gap_) 
	{
	}
};

bool Less (const word_with_frequency &first, const word_with_frequency &second)
{
	if (first.frequency > second.frequency)
	{
		return true;
	}
	if (first.frequency < second.frequency)
	{
		return false;
	}
	return (first.word < second.word);
}
vector <pair < vector <char>, char > > Transform_in_t9 ()
{
	vector <pair <vector <char>, char> > transform_in_t9;
	
	vector <char> symbols_of_2;
	symbols_of_2.push_back ('a');
	symbols_of_2.push_back ('b');
	symbols_of_2.push_back ('c');
	transform_in_t9.push_back (make_pair (symbols_of_2, '2'));
	
	vector <char> symbols_of_3;
	symbols_of_3.push_back ('d');
	symbols_of_3.push_back ('e');
	symbols_of_3.push_back ('f');
	transform_in_t9.push_back (make_pair (symbols_of_3, '3'));
	
	vector <char> symbols_of_4;
	symbols_of_4.push_back ('g');
	symbols_of_4.push_back ('h');
	symbols_of_4.push_back ('i');
	transform_in_t9.push_back (make_pair (symbols_of_4, '4'));
	
	vector <char> symbols_of_5;
	symbols_of_5.push_back ('j');
	symbols_of_5.push_back ('k');
	symbols_of_5.push_back ('l');
	transform_in_t9.push_back (make_pair (symbols_of_5, '5'));
	
	vector <char> symbols_of_6;
	symbols_of_6.push_back ('m');
	symbols_of_6.push_back ('n');
	symbols_of_6.push_back ('o');
	transform_in_t9.push_back (make_pair (symbols_of_6, '6'));
	
	vector <char> symbols_of_7;
	symbols_of_7.push_back ('p');
	symbols_of_7.push_back ('q');
	symbols_of_7.push_back ('r');
	symbols_of_7.push_back ('s');
	transform_in_t9.push_back (make_pair (symbols_of_7, '7'));
	
	vector <char> symbols_of_8;
	symbols_of_8.push_back ('t');
	symbols_of_8.push_back ('u');
	symbols_of_8.push_back ('v');
	transform_in_t9.push_back (make_pair (symbols_of_8, '8'));
	
	vector <char> symbols_of_9;
	symbols_of_9.push_back ('w');
	symbols_of_9.push_back ('x');
	symbols_of_9.push_back ('y');
	symbols_of_9.push_back ('z');
	transform_in_t9.push_back (make_pair (symbols_of_9, '9'));
	
	return transform_in_t9;
}

char Transform_symbol_to_symbol_in_numeric (char symbol)
{
	const vector <pair <vector <char>, char> > transform_in_t9 = Transform_in_t9 ();
	for (int i = 0; i < transform_in_t9.size(); ++i)
	{
		 vector <char>::const_iterator iterator = 
		 find( transform_in_t9[i].first.begin() , transform_in_t9[i].first.end(), symbol );
		 if (!(iterator == transform_in_t9[i].first.end()))
		 {
			 return transform_in_t9[i].second;
		 }
	}
}

char Bidlo (char s)
{
	if ((s == 'a') || (s == 'b') || (s == 'c'))
	{
		return '2';
	}
	if ((s == 'd') || (s == 'e') || (s == 'f'))
	{
		return '3';
	}
	if ((s == 'g') || (s == 'h') || (s == 'i'))
	{
		return '4';
	}
	if ((s == 'j') || (s == 'k') || (s == 'l'))
	{
		return '5';
	}
	if ((s == 'm') || (s == 'n') || (s == 'o'))
	{
		return '6';
	}
	if ((s == 't') || (s == 'u') || (s == 'v'))
	{
		return '8';
	}
	if ((s == 'p') || (s == 'q') || (s == 'r') || (s == 's'))
	{
		return '7';
	}
	if ((s == 'w') || (s == 'x') || (s == 'y') || (s == 'z'))
	{
		return '9';
	}						
			
		
}

string Transform_word_to_word_in_numerics (const string &word)
{
	string transform_word;
	for (int i = 0; i < word.length(); ++i)
	{
		transform_word += Bidlo(word[i]);
		//transform_word.push_back(Transform_symbol_to_symbol_in_numeric(word[i]) );
	}
	return transform_word;
}

void Read (vector <word_with_frequency> &dicionary, string &message_in_t9)
{
	int number_words;
	cin >> number_words;
	for (int i = 0; i < number_words; ++i)
	{
		string word;
		cin >> word;
		int frequency;
		cin >> frequency;
		dicionary.push_back( word_with_frequency (word, frequency) );
	}
	string empty_string;
	cin >> empty_string;
	getline(cin, message_in_t9);
	message_in_t9 = empty_string + message_in_t9;

}

vector <char> No_letter_symbols ()
{
	vector <char> no_letter_symbols;
	no_letter_symbols.push_back('*');
	no_letter_symbols.push_back('1');
	no_letter_symbols.push_back(' ');
	return no_letter_symbols;
}

bool Is_letter_symbol (char symbol)
{
	vector <char> no_letter_symbols = No_letter_symbols (); 
	vector <char>::const_iterator iterator = 
	find( no_letter_symbols.begin(), no_letter_symbols.end(), symbol );
	return (iterator == no_letter_symbols.end());
}

vector <char> Punctuation_mark_in_t9()
{
	vector <char> punctuation_mark_in_t9;
	punctuation_mark_in_t9.push_back('.');
	punctuation_mark_in_t9.push_back(',');
	punctuation_mark_in_t9.push_back('?');
	return punctuation_mark_in_t9;
}

char Restore_punctuation_mark (int number_stars_after_1)
{
	vector <char> punctuation_mark_in_t9 = Punctuation_mark_in_t9();
	return punctuation_mark_in_t9[number_stars_after_1];
}

string Restore_gaps (int number_gap)
{
	string restore_gaps;
	for (int i = 0; i < number_gap; ++i)
	{
		restore_gaps += ' ';
	}
	return restore_gaps;
}

vector <separated_word> Make_separated_message (const string &message_in_t9)
{
	const vector <char> no_letter_symbols = No_letter_symbols();
	vector <separated_word> separated_message;
	int i_letter = 0;
	while (i_letter < message_in_t9.length())
	{
		string word = "";
		int number_stars_after_word = 0;
		bool is_1 = false;
		int number_stars_after_1 = 0;
		int number_gap = 0;
		separated_message.push_back ( separated_word (word, number_stars_after_word,is_1,
		number_stars_after_1, number_gap));

		bool out = false;

		while (Is_letter_symbol (message_in_t9[i_letter]) && (!out))
		{

			separated_message[static_cast<int> (separated_message.size()) - 1].word_in_numeric += message_in_t9[i_letter];
			++i_letter;
			if (i_letter == message_in_t9.length())
			{
				out = true;
			}
		}

		while (message_in_t9[i_letter] == '*')
		{
			++separated_message[static_cast<int> (separated_message.size()) - 1].number_stars_after_word;
			++i_letter;
		}

		if (message_in_t9[i_letter] == '1')
		{
			separated_message[static_cast<int> (separated_message.size()) - 1].is_1 = true;
			++i_letter;
			while (message_in_t9[i_letter] == '*')
			{
				++separated_message[static_cast<int> (separated_message.size()) - 1].number_stars_after_1;
				++i_letter;
			}
		}

		while (message_in_t9[i_letter] == ' ')
		{
			++separated_message[static_cast<int> (separated_message.size()) - 1].number_gap;
			++i_letter;
		}
	}
	return separated_message;
}

string Restore_word (int number_stars, const string &word_in_numeric, map <string, list<word_with_frequency> > &sort_words)
{	

	list<word_with_frequency> ::iterator iter = sort_words[word_in_numeric].begin();

	for (int i = 0; i < number_stars; ++i)
	{

		++iter;
	}

	++(iter->frequency);
	
	word_with_frequency restore_word_with_frequency = *iter;
	
	string restore_word = restore_word_with_frequency.word;
	
	sort_words[word_in_numeric].erase(iter);
	if  ( (--sort_words[word_in_numeric].end())->frequency > restore_word_with_frequency.frequency )
	{
		sort_words[word_in_numeric].push_back(restore_word_with_frequency);
	}
	else
	{
		list<word_with_frequency> ::iterator it = sort_words[word_in_numeric].begin();
		while (restore_word_with_frequency.frequency < it->frequency) 
		{
			++it;
		}
		sort_words[word_in_numeric].insert(it, restore_word_with_frequency);
	}
	return restore_word; 
}

void Make_sort_words (map <string, list <word_with_frequency> > &sort_words, 
					           const vector <word_with_frequency> &dictionary,const string &message_in_t9)
{
	map <string, vector <word_with_frequency> > words;
	for (int i = 0; i < dictionary.size(); ++i)
	{
		words[Transform_word_to_word_in_numerics(dictionary[i].word)].push_back(word_with_frequency (dictionary[i].word, dictionary[i].frequency));
	}
	typedef map <string, vector <word_with_frequency> >::const_iterator cl;

	for (cl it = words.begin(); it != words.end(); ++it)
	{
		vector <word_with_frequency> vector_words = it->second;
		sort(vector_words.begin(), vector_words.end(), Less);
		for (int i = 0; i < vector_words.size(); ++i)
		{
			sort_words[it->first].push_back(vector_words[i]);
		}
	}
}

void Output_answer (const string &real_message)
{
	cout << real_message;
}

void Restore_message (string &real_message, const string &message_in_t9, const vector <word_with_frequency> &dictionary)
{

	vector <separated_word> separated_message = Make_separated_message(message_in_t9);
	map <string, list<word_with_frequency> > sort_words;
	Make_sort_words (sort_words, dictionary, message_in_t9);

	for (int i = 0; i < separated_message.size(); ++i)
	{
		if (separated_message[i].word_in_numeric != "")
		{
			real_message += Restore_word(separated_message[i].number_stars_after_word,
			separated_message[i].word_in_numeric, sort_words);
        }
    
		if (separated_message[i].is_1)
		{
			real_message += Restore_punctuation_mark(separated_message[i].number_stars_after_1);
		}
	
		real_message += Restore_gaps(separated_message[i].number_gap);
	
	}

}
int main(void)
{
	vector <word_with_frequency> dictionary;
	string message_in_t9;
	Read(dictionary, message_in_t9);
	string real_message;
	Restore_message (real_message, message_in_t9, dictionary);
	Output_answer(real_message);
	return 0;
}

