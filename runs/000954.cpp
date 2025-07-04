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
	if (value == '2') letters = "abcc";
	if (value == '3') letters	= "deff";
	if (value == '4') letters	= "ghii";
	if (value == '5') letters = "jkll";
	if (value == '6') letters = "mnoo";
	if (value == '7') letters = "pqrs";
	if (value == '8') letters	= "tuvv";
	if (value == '9') letters = "wxyz";
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
	ushort p = 0;
	while (p < punctMarks.size())
	{
		if (punctMarks[p] == '1' && !shift || punctMarks[p]  == '*')
			++shift;

		else 
		{
			switch_punct(shift);
			shift = 1;
		}

		++p;
		
		if (p == punctMarks.size())
			switch_punct(shift);
	}
}


void print_word(string word, vector< vector <string> > &dicts)
{
	string::iterator s = find(word.begin(), word.end(), '*');
	string letters(word.begin(), s);
	ushort shift = word.end() - s;
	ushort len   = letters.size();
	bool valid;

	for (int i = 999; i > -1 ; --i)
	{
		for (int j = 0; j < dicts[i].size(); ++j)
		{
			if (dicts[i][j].size() == len)
			{
				valid = true;
				for (ushort cur_sym = 0; valid, cur_sym < len; ++cur_sym)
				{	
					button but(letters[cur_sym]);
					if (dicts[i][j][cur_sym] < but.letters[0] || dicts[i][j][cur_sym]  > but.letters[3])//but.letters.size()-1])
						valid = false; 
				}
				if (valid)
				{
					if (!shift)
					{
						cout << dicts[i][j];
						if (i<999)
							dicts[i+1].insert(dicts[i+1].begin(), dicts[i][j]);

						dicts[i][j].erase();
						return;
					}
					else
						--shift;
				}
			}
		}
	}
}


void print_word_or_puncts(string tempWord, vector< vector <string> > &dicts)
{
	ushort last = tempWord.size() - 1;
	if (tempWord[last] == '\n') tempWord.erase(last);
	if (tempWord[0			      ] == '\n') tempWord.erase(0);
	string::iterator s = find(tempWord.begin(), tempWord.end(), '1');
	if (s != tempWord.begin())
	{
		string word(tempWord.begin(), s);
		print_word(word, dicts);
	}
	if (s != tempWord.end())
	{
		string punctMarks(s, tempWord.end());
		print_puncts(punctMarks);
	}
}

int main()
{
	unsigned short	wordNum;	
	vector< vector <string> > dictionary;
	dictionary.resize(1000);

	cin >> wordNum;
	
	string tempEntry;
	ushort freq;
	for (ushort i = wordNum; i; --i)
	{
		cin >> tempEntry >> freq;
		dictionary[freq-1].push_back(tempEntry);
	}

	string tempWord;
	bool isWord = false;
	char c;
	while(cin.get(c))
	{
		if (c != ' ' && c != '\n')
		{
			isWord = true;
			tempWord.push_back(c);
		}
		else 
		{
			if (isWord)
			{
				print_word_or_puncts(tempWord, dictionary);
				tempWord.clear();
				isWord = false;
				if (c != '\n')
					cout<<c;
			}
			else
				cout<<c;
		}
	} 
	if (tempWord.size())
		print_word_or_puncts(tempWord, dictionary);

	return 0;
}

