#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

typedef unsigned short ushort;

using namespace std;

struct button
{
	string letters;
	button(char value);
};

button::button(char value)
{
	if (value == '2') letters = "abc";
	if (value == '3') letters	= "def";
	if (value == '4') letters	= "ghi";
	if (value == '5') letters = "jkl";
	if (value == '6') letters = "mno";
	if (value == '7') letters = "pqrs";
	if (value == '8') letters	= "tuv";
	if (value == '9') letters = "wxyz";
}

struct entry
{
	string word;
	ushort freq;
	bool recent;
};

bool moreFrequently(const entry& a, const entry& b)
{ 
	return a.freq > b.freq;
} 
bool moreRecently(const entry& a, const entry& b)
{ 
	return a.recent > b.recent;
} 

void switch_punct(int shift)
{
	switch (shift)
	{
		case 1:	{cout<<".";	break;}
		case 2:	{cout<<",";	break;}
		case 3: {cout<<"?";	break;}
	}
}

void print_puncts(string punctMarks)
{
	unsigned char shift = 0;
	string::iterator p = punctMarks.begin();
	while (p < punctMarks.end())
	{
		if (*p == '1' && !shift || *p  == '*')
			++shift;

		else 
		{
			switch_punct(shift);
			shift = 1;
		}

		++p;
		
		if (p == punctMarks.end())
			switch_punct(shift);
	}
}


void print_word(string word, vector<entry> &dictionary)
{
	string::iterator s = find(word.begin(), word.end(), '*');
	string letters(word.begin(), s);
	unsigned short shift = word.end() - s;
	vector<entry> variants;
	for (vector<entry>::iterator i = dictionary.begin(); i < dictionary.end(); ++i)
	{
		if (i->word.size() == letters.size())
		{
			int equalities = 0;
			for (string::iterator s = i->word.begin(); s < i->word.end(); ++s)
			{
				button tempButton(letters[s - i->word.begin()]);
				for (string::iterator b = tempButton.letters.begin(); b < tempButton.letters.end(); ++b)
					if (*b == *s)
						++equalities;
			}
			if (equalities == letters.size())
				variants.push_back(*i);
		}
	}

	sort(variants.begin(), variants.end(), moreFrequently);
	cout << variants[shift].word;

	for (unsigned short cur_entry = 0; cur_entry < dictionary.size(); ++cur_entry)
	{
		if (dictionary[cur_entry].word == variants[shift].word)
		{
			++dictionary[cur_entry].freq;
			dictionary[cur_entry].recent = true;
		}
		else
			if (dictionary[cur_entry].freq    == variants[shift].freq + 1)
				dictionary[cur_entry].recent  =  false;
	}	
}
void print_word_or_puncts(string tempWord, vector<entry> &dictionary)
{
	if (tempWord[tempWord.size()-1] == '\n') tempWord.erase(tempWord.size()-1);
	if (tempWord[0			      ] == '\n') tempWord.erase(0);
	string::iterator s = find(tempWord.begin(), tempWord.end(), '1');
	if (s != tempWord.begin())
	{
		string word(tempWord.begin(), s);
		if (word.size())
		{
			sort(dictionary.begin(), dictionary.end(), moreRecently);
			print_word(word, dictionary);
		}
	}
	if (s != tempWord.end())
	{
		string punctMarks(s, tempWord.end());
		if (punctMarks.size())
			print_puncts(punctMarks);
	}
}

int main()
{
	unsigned short	wordNum;	
	vector<entry>	dictionary; 

	cin >> wordNum;
	
	entry tempEntry;
	tempEntry.recent = false;
	for (ushort i = wordNum; i; --i)
	{
		cin >> tempEntry.word >> tempEntry.freq;
		dictionary.push_back(tempEntry);
	}
	
	string tempWord;
	bool isWord = false;
	char c;
	while(cin.get(c))
	{
		if (c == ' ' && !isWord)
			cout<<c;
		if (c != ' ')
		{
			isWord = true;
			tempWord.push_back(c);
		}
		if (c == ' ' && isWord || c == '\n' && isWord)
		{
			print_word_or_puncts(tempWord, dictionary);
			tempWord.clear();
			isWord = false;
			if (c != '\n')
				cout<<c;
		}
	} 
	if (tempWord.size())
		print_word_or_puncts(tempWord, dictionary);
	return 0;
}

