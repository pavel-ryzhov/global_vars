#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::string;
using std::map;
using std::getline;

typedef vector< pair<int, string> > Words;

class T9Vocabulary
{
	class WordsComparer
	{
	public:
		bool operator () (const pair<int, string> &word1, const pair<int, string> &word2)
		{
			if (word1.first > word2.first)
				return true;
			if (word1.first == word2.first && word1.second < word2.second)
				return true;
			return false;
		}
	};
	map<string, Words> MappedVocabulary;
	char CharToDigit(char c)
	{
		char digit = (c - 'a')/3;
		if (c == 's' || c == 'v' || c == 'y' || c == 'z')
			--digit;
		return digit + '2';
	}
	string TextTot9_word(const string &text)
	{
		string t9_word;
		for (unsigned int i = 0; i < text.length(); ++i)
			t9_word.push_back(CharToDigit(text.at(i)));
		return t9_word;
	}
public:
	T9Vocabulary(const Words &all_words);
	string FindWord(const string &t9_word, int mismatches);
};

T9Vocabulary::T9Vocabulary(const Words &all_words)
{
	for (Words::const_iterator word = all_words.begin(); word != all_words.end(); ++word)
	{
		string t9_word(TextTot9_word(word->second));
		map<string, Words>::iterator target_words = MappedVocabulary.find(t9_word);
		if (target_words == MappedVocabulary.end())
		{
			Words new_words_array;
			new_words_array.push_back(*word);
			MappedVocabulary.insert(pair<string, Words>(t9_word, new_words_array));
		}
		else
		{
			(target_words->second).push_back(*word);
		}
	}
	for (map<string, Words>::iterator words_array = MappedVocabulary.begin(); words_array != MappedVocabulary.end(); ++words_array)
	{
		sort((words_array->second).begin(), (words_array->second).end(), WordsComparer());
	}
}

string T9Vocabulary::FindWord(const string &t9_word, int mismatches)
{
	map<string, Words>::iterator target_words = MappedVocabulary.find(t9_word);
	mismatches = mismatches % (target_words->second).size(); //cycling search
	string result_word((target_words->second)[mismatches].second);
	++(target_words->second)[mismatches].first;
	for (int i = mismatches; i > 0; --i)
	{
		if ((target_words->second)[i].first >= (target_words->second)[i - 1].first)
			swap((target_words->second)[i], (target_words->second)[i - 1]);
		else
			break;
	}
	return result_word;
}

void ReadVocabulary(Words *input_vocabulary)
{
	int vocabulary_size;
	cin >> vocabulary_size;
	for (int i = 0; i < vocabulary_size; ++i)
	{
		string input_word;
		cin >> input_word;
		int word_frequency;
		cin >> word_frequency;
		input_vocabulary->push_back(pair<int, string>(word_frequency, input_word));
	}
}

void ReadInput(Words *input_vocabulary, string *t9_message)
{
	ReadVocabulary(input_vocabulary);
	getline(cin, *t9_message);
	while (t9_message->length() == 0)
		getline(cin, *t9_message);
}

const char one_key_symbols[3] = {'.', ',', '?'};
void ProcessMessages(const string &t9_message, T9Vocabulary &my_vocabulary, string *text_message)
{
	for (string::const_iterator input_char = t9_message.begin(); input_char != t9_message.end(); )
	{
		if (*input_char == ' ')
		{
			*text_message += ' ';
			++input_char;
			continue;
		}
		if (*input_char == '1')
		{
			int mismatches = 0;
			for (string::const_iterator input_stars = input_char + 1; input_stars != t9_message.end() && *input_stars == '*'; ++input_stars)
				++mismatches;
			*text_message += one_key_symbols[mismatches % 3];
			input_char += mismatches;
			++input_char;
			continue;
		}
		//else
		string t9_word;
		for (string::const_iterator word_char = input_char; word_char != t9_message.end() && (*word_char > '1' && *word_char <= '9'); ++word_char)
			t9_word.push_back(*word_char);
		input_char += t9_word.length();
		int mismatches = 0;
		for (string::const_iterator input_stars = input_char; input_stars != t9_message.end() && *input_stars == '*'; ++input_stars)
			++mismatches;
		*text_message += my_vocabulary.FindWord(t9_word, mismatches);
		input_char += mismatches;
	}
}

int main()
{
	string t9_message;
	Words input_vocabulary;
	ReadInput(&input_vocabulary, &t9_message);
	T9Vocabulary my_vocabulary(input_vocabulary);

	string text_message;
	ProcessMessages(t9_message, my_vocabulary, &text_message);
	cout << text_message << endl;
	return 0;
}