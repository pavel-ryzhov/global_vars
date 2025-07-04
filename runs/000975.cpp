#include <iostream>
#include <vector>
#include <string>

typedef unsigned short ushort;

using namespace std;

string out;

struct entry
{
	string chars;
	string nums;
};

void set_nums(entry &tempEntry)
{
	for (ushort i = 0; i < tempEntry.chars.size(); ++i)
	{
		if ( 'a' <= tempEntry.chars[i]  && tempEntry.chars[i] <= 'c')
		{
			tempEntry.nums.push_back('2');
			continue;
		}
		if ( 'd' <= tempEntry.chars[i]  && tempEntry.chars[i] <= 'f')
		{
			tempEntry.nums.push_back('3');
			continue;
		}
		if ( 'g' <= tempEntry.chars[i]  && tempEntry.chars[i] <= 'i')
		{
			tempEntry.nums.push_back('4');
			continue;
		}
		if ( 'j' <= tempEntry.chars[i]  && tempEntry.chars[i] <= 'l')
		{
			tempEntry.nums.push_back('5');
			continue;
		}
		if ( 'm' <= tempEntry.chars[i]  && tempEntry.chars[i] <= 'o')
		{
			tempEntry.nums.push_back('6');
			continue;
		}
		if ( 'p' <= tempEntry.chars[i]  && tempEntry.chars[i] <= 's')
		{
			tempEntry.nums.push_back('7');
			continue;
		}
		if ( 't' <= tempEntry.chars[i]  && tempEntry.chars[i] <= 'v')
		{
			tempEntry.nums.push_back('8');
			continue;
		}
		if ( 'w' <= tempEntry.chars[i]  && tempEntry.chars[i] <= 'z')
		{
			tempEntry.nums.push_back('9');
			continue;
		}
	}
}

void switch_punct(int shift)
{
	switch (shift)
	{
		case 1:	{out.push_back('.');break;}
		case 2:	{out.push_back(',');break;}
		case 3: {out.push_back('?');break;}
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


void print_word(string word, vector<vector<entry > > &dicts)
{
	string::iterator s = word.begin();
	while (*s != '*') 
	{
		++s;
		 if (s == word.end())
			 break;
	}
	string letters(word.begin(), s);
	ushort shift = word.end() - s;

	for (int i = 999; i > -1 ; --i)
	{
		for (int j = 0; j < dicts[i].size(); ++j)
		{
			if (dicts[i][j].nums == letters)
			{
				if (!shift)
				{
					out+=dicts[i][j].chars;
					if (i<999)
					{
						dicts[i+1].insert(dicts[i+1].begin(), dicts[i][j]);
						dicts[i].erase(dicts[i].begin()+j);
					}
					return;
				}
					else
						--shift;
			}
		}
	}
}


void print_word_or_puncts(string tempWord, vector<vector<entry > > &dicts)
{
	ushort last = tempWord.size() - 1;
	if (tempWord[last] == '\n') tempWord.erase(last);
	if (tempWord[0	 ] == '\n') tempWord.erase(0);
	
	string word;
	string puncts;
	for (ushort i = 0; i < tempWord.size(); ++i)
	{
		if (tempWord[i] == '*')
		{
			if (word.size())
				word.push_back('*');
			else
				puncts.push_back('*');
		}
		else
		{
			if (tempWord[i] == '1')
			{
				if (word.size())
				{
					print_word(word, dicts);
					word.clear();
				}
				puncts.push_back('1');
			}
			else
			{
				if (puncts.size())
				{
					print_puncts(puncts);
					puncts.clear();
				}
				word.push_back(tempWord[i]);
			}
		}
	}
	if (puncts.size())
		print_puncts(puncts);
	if (word.size())
		print_word(word, dicts);
}

int main()
{
	unsigned short	wordNum;	
	vector<vector<entry > > dicts;
	dicts.resize(1000);

	cin >> wordNum;
	
	entry tempEntry;
	ushort freq;
	for (ushort i = wordNum; i; --i)
	{
		
		tempEntry.nums.clear();
		cin >> tempEntry.chars >> freq;
		set_nums(tempEntry);
		dicts[freq-1].push_back(tempEntry);
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
				print_word_or_puncts(tempWord, dicts);
				tempWord.clear();
				isWord = false;
				if (c != '\n')
					out.push_back(c);
			}
			else
				if (c != '\n')
					out.push_back(c);
		}
	} 
	if (tempWord.size())
		print_word_or_puncts(tempWord, dicts);

	printf("%s", out.c_str());
	return 0;
}

