#include <iostream>
#include <string>
#include <list>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::list;

typedef struct
{
	string word;
	int freq;
} record;

typedef struct Node
{
	int length;
	list<record> words;
	struct Node *next[10];
} node;

void insert_word_record(node *tree, string s, int freq);
int button(char c);
string useT9(node *tree, string T9code);
void delete_tree(node *tree);
inline int ctoi(char c);

void show(node *tree);

int main(void)
{
	int N;
	
	cin >> N;

	node *dictionary = new node;
	dictionary->length = 0;
	
	string new_word;
	int new_freq;
	for (int i = 0; i < N; ++i)
	{
		cin >> new_word;
		cin >> new_freq;
		insert_word_record(dictionary, new_word, new_freq);
	}
		
	insert_word_record(dictionary, ".", 3);
	insert_word_record(dictionary, ",", 2);
	insert_word_record(dictionary, "?", 1);

/*
	for (int i = 0; i < 9; ++i)
	{
		if (dictionary->next[i] != 0)
			show(dictionary->next[i]);
	}
*/

	char c;
	string T9code, decoded_word;
	cin.unsetf(std::ios::skipws);
	cout.unsetf(std::ios::skipws);
	
	cin.get(c);
	while ((c == '\r') || (c == '\n'))
		cin.get(c);
	cin.putback(c);
	
	while (!cin.eof())
	{
		cin.get(c);

		while ((c == ' ') || (c == '\t'))
		{
			cout.put(c);
			if (cin.eof())
				break;
			cin.get(c);
		}
		if ((c == '\n') || (c == '\r'))
			break;

		if (cin.eof())
			break;

		cin.putback(c);

		cin >> T9code;

		decoded_word = useT9(dictionary, T9code);

		if (!cin.eof()) // your gcc is bad : (
			cout << decoded_word;
	};
	
	cout << endl;
	
	delete_tree(dictionary);
	
	return 0;
}

void insert_word_record(node *tree, string s, int freq)
{
	if (tree->length == s.length())
	{
		list<record>::iterator it = tree->words.begin();
		while (it != tree->words.end() && it->freq >= freq)
			++it;
		
		record new_word;
		new_word.word = s;
		new_word.freq = freq;
		
		tree->words.insert(it, new_word);
	}
	else
	{
		if (tree->next[button(s[tree->length])] == 0)
		{
			tree->next[button(s[tree->length])] = new node;
			tree->next[button(s[tree->length])]->length = tree->length + 1;
		}
		
		insert_word_record(tree->next[button(s[tree->length])], s, freq);
	}
}

int button(char c)
{
	switch(c)
	{
		case '.': case ',': case '?': 			return 1;
		case 'a': case 'b': case 'c': 			return 2;
		case 'd': case 'e': case 'f': 			return 3;
		case 'g': case 'h': case 'i': 			return 4;
		case 'j': case 'k': case 'l': 			return 5;
		case 'm': case 'n': case 'o': 			return 6;
		case 'p': case 'q': case 'r': case 's': return 7;
		case 't': case 'u': case 'v': 			return 8;
		case 'w': case 'x': case 'y': case 'z': return 9;		
	}
	return -1;
}

void delete_tree(node *tree)
{
	for (int i = 0; i < 10; ++i)
		if (tree->next[i] != 0)
			delete_tree(tree->next[i]);
	
	delete tree;
}

string useT9(node *tree, string T9code)
{
	bool there_were_no_subwords = true;
	bool need_to_skeep_stars = false;
	
	string word;
	node *subtree = tree;
	list<record>::iterator currentWord = subtree->words.begin();
	word = "";
	char code;
	bool after_punctuation_mark = false;
	string subword = "", subcode;

	for (int i = 0; i < T9code.length(); ++i)
	{		
		code = T9code[i];
		
		if (i == 0 && code == '*')
			need_to_skeep_stars = true;
		if (code == '*') // skipping word in the list
		{
			if (need_to_skeep_stars)
				continue; // treat '*' at start of the word like nothing :)

			++currentWord;
			if (currentWord == subtree->words.end())
				currentWord = subtree->words.begin();
				
			continue;
		}

		if (after_punctuation_mark) // word after punctuation mark - treat it as new subword
		{
			subcode = T9code.substr(i);
			subword = useT9(tree, subcode);
			word = currentWord->word + subword;
			there_were_no_subwords = false;
			break; // no need to proceed cycle - already recursivly did it
		}
		else if (ctoi(code) == 1) // we face punctuation mark ('.', '.' or '?')
			if (i != 0) // punctuation mark inside word - treat as new subword
			{
				subcode = T9code.substr(i);
				subword = useT9(tree, subcode);
				if (need_to_skeep_stars)
					word = subword;
				else
					word = currentWord->word + subword;
				there_were_no_subwords = false;
				break; // no need to proceed cycle - already recursivly did it
			}
			else // word starts with punctuation mark - enable flag
			{
				need_to_skeep_stars = false;
				after_punctuation_mark = true;
				subtree = subtree->next[ctoi(code)];
				currentWord = subtree->words.begin();
			}
		else // normally proceed to next symbol for decoding T9
		{
			need_to_skeep_stars = false;
			subtree = subtree->next[ctoi(code)];
			currentWord = subtree->words.begin();
		}
	}

	if (subtree->length == 0) // currentWord consists of '*'
		if (there_were_no_subwords)
			return "";
		else
			return subword;
	
	if ( there_were_no_subwords )
		word = currentWord->word;

	// increasing frequencies for each part separately
	//      (currentWord->word, currentWord->freq)
	// but then return full word for output
	//      (word = currentWord->word + subword)

	if ( (currentWord->word == ".") || (currentWord->word == ",") || (currentWord->word == "?") )
		return word; // no need to increase frequncies

	currentWord->freq++;
	
	if (subtree->words.size() <= 1 || currentWord == subtree->words.begin())
		return word;
	
	list<record>::iterator it = currentWord;

	while ( (it->freq <= currentWord->freq) && (it != subtree->words.begin()) )
		--it;

	record buf;

	buf.word = currentWord->word;
	buf.freq = currentWord->freq;

	if (it->freq > currentWord->freq)
		++it;

	if (it == currentWord)
		return word; // word is already where we want

	subtree->words.erase(currentWord);
	subtree->words.insert(it, buf);

	return word;
}

inline int ctoi(char c)
{
	return c - 48;
}

void show(node *tree)
{
	list<record>::iterator it;

	for (it = tree->words.begin(); it != tree->words.end(); ++it)
		cout << it->word << " " << it->freq << endl;
		
	for (int i = 1; i < 10; ++i)
	{
		if (tree->next[i] != 0)
			show(tree->next[i]);
	}
}
