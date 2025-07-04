#include <iostream>
#include <string>
#include <list>
#include <cstdlib>

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
	struct Node *next[9];
} node;

void insert(node *T, string s, int freq);
int button(char c);
string useT9(node *T, string T9code);
void delete_tree(node *T);

//void show(node *T);

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
		insert(dictionary, new_word, new_freq);
	}
		
	insert(dictionary, ".", 3);
	insert(dictionary, ",", 2);
	insert(dictionary, "?", 1);
	
/*
	for (int i = 0; i < 9; ++i)
	{
		if (dictionary->next[i] != 0)
			show(dictionary->next[i]);
	}
*/
	//return 0;
	
	char c;
	string T9text, res_word;
	while (!cin.eof())
	{	
		cin >> T9text;
		
		res_word = useT9(dictionary, T9text);
		
		cout << res_word << " ";
	};
	
	cout << endl;
	
	delete_tree(dictionary);
	
	return 0;
}

void insert(node *T, string s, int freq)
{
	if (T->length == s.length())
	{
		list<record>::iterator it = T->words.begin();
		while (it->freq >= freq)
			++it;
		
		record *new_word = new record;
		new_word->word = s;
		new_word->freq = freq;
		
		T->words.insert(it, *new_word);
	}
	else
	{
		if (T->next[button(s[T->length])] == 0)
		{
			T->next[button(s[T->length])] = new node;
			T->next[button(s[T->length])]->length = T->length + 1;
		}
		
		insert(T->next[button(s[T->length])], s, freq);
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
}

void delete_tree(node *T)
{
	for (int i = 0; i < 9; ++i)
		if (T->next[i] != 0)
			delete_tree(T->next[i]);
	
	delete T;
}

string useT9(node *T, string T9code)
{
	string word;
	node *TT = T;
	list<record>::iterator currentWord = TT->words.begin();
	char num[1];
	for (int i = 0; i < T9code.length(); ++i)
	{
		num[0] = T9code[i];
		if (T9code[i] == '*')
			++currentWord;
		else if ( (atoi(num) == 1) && (i != 0) )
		{
			string mark = useT9(T, T9code.substr(i));
			word = currentWord->word + mark;
			return word;
		}
		else
		{
			TT = TT->next[atoi(num)];
			currentWord = TT->words.begin();
		}
	}
	word = currentWord->word;
	
	if ( (word == ".") || (word == ",") || (word == "?") )
		return word;
		
	currentWord->freq++;
	list<record>::iterator it = currentWord;

	while ( (it->freq <= currentWord->freq) && (it != TT->words.begin()) )
		--it;
		
	record *buf = new record;

	buf->word = currentWord->word;

	buf->freq = currentWord->freq;

	if (TT->words.size() <= 1)
		return word;
	
	TT->words.erase(currentWord);

	if (it == TT->words.end() || it == TT->words.begin())
		TT->words.insert(it, *buf);
	else
		TT->words.insert(++it, *buf);

	return word;
}
//
/*
void show(node *T)
{
	list<record>::iterator it;

	for (it = T->words.begin(); it != T->words.end(); ++it)
		cout << it->word << " " << it->freq << endl;
		
	for (int i = 0; i < 9; ++i)
	{
		if (T->next[i] != 0)
			show(T->next[i]);
	}
}
*/