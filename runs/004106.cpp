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

void insert_word_record(node *T, string s, int freq);
int button(char c);
string useT9(node *T, string T9code);
void delete_tree(node *T);
inline int ctoi(char c);

void show(node *T);

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

		cin.putback(c);//T9text = c + T9text;

		cin >> T9code;

		decoded_word = useT9(dictionary, T9code);

		if (!cin.eof()) // your gcc is bad : (
			cout << decoded_word;
	};
	
	cout << endl;
	
	delete_tree(dictionary);
	
	return 0;
}

void insert_word_record(node *T, string s, int freq)
{
	if (T->length == s.length())
	{
		list<record>::iterator it = T->words.begin();
		while (it->freq >= freq && it != T->words.end())
			++it;
		
		record new_word;
		new_word.word = s;
		new_word.freq = freq;
		
		T->words.insert(it, new_word);
	}
	else
	{
		if (T->next[button(s[T->length])] == 0)
		{
			T->next[button(s[T->length])] = new node;
			T->next[button(s[T->length])]->length = T->length + 1;
		}
		
		insert_word_record(T->next[button(s[T->length])], s, freq);
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

void delete_tree(node *T)
{
	for (int i = 0; i < 10; ++i)
		if (T->next[i] != 0)
			delete_tree(T->next[i]);
	
	delete T;
}

string useT9(node *T, string T9code)
{
	bool there_were_no_subwords = true;

	string word;
	node *TT = T;
	list<record>::iterator currentWord = TT->words.begin();
	char code;
	bool after_punctuation_mark = false;
	string subword, subcode;
	
	for (int i = 0; i < T9code.length(); ++i)
	{
		code = T9code[i];
	
		if (code == '*') // skipping word in the list
		{
			++currentWord;
			continue;
		}

		if (after_punctuation_mark) // word after punctuation mark - treat it as new subword
		{
			subcode = T9code.substr(i);
			subword = useT9(T, subcode);
			word = currentWord->word + subword;
			there_were_no_subwords = false;
			break; // no need to proceed cycle - already recursivly did it
		}
		else if (ctoi(code) == 1) // we face punctuation mark ('.', '.' or '?')
			if (i != 0) // punctuation mark inside word - treat as new subword
			{
				subcode = T9code.substr(i);
				subword = useT9(T, subcode);
				word = currentWord->word + subword;
				there_were_no_subwords = false;
				break; // no need to proceed cycle - already recursivly did it
			}
			else // word starts with punctuation mark - enable flag
			{
				after_punctuation_mark = true;
				TT = TT->next[ctoi(code)];
				currentWord = TT->words.begin();
			}
		else // normally proceed to next symbol for decoding T9
		{
			TT = TT->next[ctoi(code)];
			currentWord = TT->words.begin();
		}
	}

	if ( there_were_no_subwords )
		word = currentWord->word;

	// increasing frequencies for each part separately
	//      (currentWord->word, currentWord->freq)
	// but then return full word for output
	//      (word = currentWord->word + subword)

	if ( (currentWord->word == ".") || (currentWord->word == ",") || (currentWord->word == "?") )
		return word; // no need to increase frequncies

	currentWord->freq++;
	list<record>::iterator it = currentWord;

	while ( (it->freq <= currentWord->freq) && (it != TT->words.begin()) )
		--it;

	record buf;

	buf.word = currentWord->word;

	buf.freq = currentWord->freq;

	if (TT->words.size() <= 1)
		return word;

	if (currentWord == TT->words.begin())
		return word; // word is already the head of the list

	if (it->freq > currentWord->freq)
		++it;

	if (it == currentWord)
		return word; // word is already where we want

	TT->words.erase(currentWord);
	TT->words.insert(it, buf);

	return word;
}

inline int ctoi(char c)
{
	return c - 48;
}

void show(node *T)
{
	list<record>::iterator it;

	for (it = T->words.begin(); it != T->words.end(); ++it)
		cout << it->word << " " << it->freq << endl;
		
	for (int i = 1; i < 10; ++i)
	{
		if (T->next[i] != 0)
			show(T->next[i]);
	}
}
