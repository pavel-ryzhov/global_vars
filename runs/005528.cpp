#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Word
{
public:
	string str;
	int freq;
};

class dictionaryTree
{
public:
	string code;
	vector<Word> words;
	dictionaryTree *right;
	dictionaryTree *left;
};

dictionaryTree *add(dictionaryTree *dTr, Word *word);
void makeCode(string str, string &code);
void printWord(dictionaryTree *dTr, string code, int n);
void printSMS(dictionaryTree *dTr);

int main()
{
	int numWords;
	dictionaryTree *dTr = NULL;
	Word *word;
	cin >> numWords;
	for (int i = 0; i < numWords; i++)
	{
		word = new Word;
		cin >> word->str >> word->freq;
		dTr = add(dTr, word);
		delete word;
	}
	cin.ignore();
	printSMS(dTr);
	return 0;
}

void makeCode(string str, string &code)
{
	for (int i=0; str[i]; i++)
	{
		if (str[i] == 'a' || str[i] == 'b' || str[i] == 'c') code += '2';
		if (str[i] == 'd' || str[i] == 'e' || str[i] == 'f') code += '3';
		if (str[i] == 'g' || str[i] == 'h' || str[i] == 'i') code += '4';
		if (str[i] == 'j' || str[i] == 'k' || str[i] == 'l') code += '5';
		if (str[i] == 'm' || str[i] == 'n' || str[i] == 'o') code += '6';
		if (str[i] == 'p' || str[i] == 'q' || str[i] == 'r' || str[i] == 's') code += '7';
		if (str[i] == 't' || str[i] == 'u' || str[i] == 'v') code += '8';
		if (str[i] == 'w' || str[i] == 'x' || str[i] == 'y' || str[i] == 'z') code += '9';
	}
}

dictionaryTree *add(dictionaryTree *dTr, Word *word)
{
	string code;
	makeCode(word->str, code);
	if (dTr == NULL) 
	{
		dTr = new dictionaryTree;
		dTr->code = code;
		dTr->words.push_back(*word);
		dTr->left = dTr->right = NULL;
	}
	else if (dTr->code == code)
	{
		dTr->words.push_back(*word);
		Word word;
		for (int i = dTr->words.size()-1; i > 0; i--)
			if (dTr->words[i].freq > dTr->words[i-1].freq)
			{
				word = dTr->words[i];
				dTr->words[i] = dTr->words[i-1];
				dTr->words[i-1] = word;
			}
			else
				break;
	}
	else if (dTr->code < code)
		dTr->left = add(dTr->left, word);
	else if (dTr->code > code)
		dTr->right = add(dTr->right, word);
	return dTr;
}

void printWord(dictionaryTree *dTr, string code, int n)
{
	if (dTr->code == code)
	{
		Word word;
		cout << dTr->words[n].str;
		dTr->words[n].freq++;
		for (int i = n; i > 0; i--)
			if (dTr->words[i].freq >= dTr->words[i-1].freq)
			{
				word = dTr->words[i];
				dTr->words[i] = dTr->words[i-1];
				dTr->words[i-1] = word;
			}
			else
				break;
	}
	else if (dTr->code < code)
		printWord(dTr->left, code, n);
	else if (dTr->code > code)
		printWord(dTr->right, code, n);
}

void printSMS(dictionaryTree *dTr)
{
	string s;
	int n=0;
	char c;
	while (cin.get(c))
	{
		if (c == '\n' || c =='\0' || c == EOF) 
		{
			if (!s.empty()) printWord(dTr, s, n);
			break;
		}
		if (c == '1')
		{
			if (!s.empty())
			{
				printWord(dTr, s, 0);
				s.clear();
			}
			while (cin.peek() == '*')
			{
				cin.get(c);
				n++;
			}
			switch (n)
			{
			case 0:
				cout << ".";
				break;
			case 1:
				cout << ",";
				break;
			case 2:
				cout << "?";
			}
				n = 0;
		}
		else if (c == '*')
			{
				n = 1;
				while (cin.peek() == '*')
				{
					cin.get(c);
					n++;
				};
				if (!s.empty())
				{
					printWord(dTr, s, n);
					s.clear();
				}
				n = 0;
			}
		else if (c == ' ')
			{
				if (!s.empty())
				{
					printWord(dTr, s, 0);
					s.clear();
				}
				cout << " ";
			}
		else
			{
				s+=c;
			}
	}
}
