#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

typedef unsigned char  uchar;
typedef unsigned int   uint;
typedef unsigned short ushort;

using namespace std;

struct entry
{
	string word;
	ushort frequently;
	bool	 recent;
};


bool moreFrequently(const entry& a, const entry& b)
{ 
	return a.frequently > b.frequently;
} 
bool moreRecently(const entry& a, const entry& b)
{ 
	return a.recent > b.recent;
} 

uchar howManyLetters(string s)
{
	uchar letters = 0;
	while (s[letters] != '*' && s[letters] != '1')
	{
		letters++;
		if (letters == s.size())
			break;
	}
	return letters;
}

void punctuate(string word, uint pos, string &out)
{
	for (uint i = pos; i < word.size(); i++)
	{
		if (word[i] == '1')
		{
			if (i+1 == word.size())
				out.push_back('.');
			else
			{
				if (word[i+1] == '1') 
					out.push_back('.');
				else
				{
					if (i+2 == word.size())
						out.push_back(',');
					else
					{
						if (word[i+2] == '1') 
							out.push_back(',');
						else
							out.push_back('?');
					}
				}
			}
		}
	}
}
void setButtons(vector<string> &buttons)
{
	buttons.push_back("2abc");
	buttons.push_back("3def");
	buttons.push_back("4ghi");
	buttons.push_back("5jkl");
	buttons.push_back("6mno");
	buttons.push_back("7pqrs");
	buttons.push_back("8tuv");
	buttons.push_back("9wxyz");
}

int main()
{
	vector<string>	buttons;
	ushort			wordNum;	
	vector<entry>	dictionary; 
	vector<string>	sms;	
	vector<uint>    spaces;
	vector<string>  out;

	setButtons(buttons);

	cin >> wordNum;
	
	entry tempEntry;
	tempEntry.recent = false;
	for (ushort i = wordNum; i; --i)
	{
		cin >> tempEntry.word >> tempEntry.frequently;
		dictionary.push_back(tempEntry);
	}

	
	string smsString;
	char c;
	cin.get(c);
	while (cin.get(c))
		smsString.push_back(c);

	bool startBySpace = false;
	if (smsString[0] == ' ')
		startBySpace = true;

	string tempWord;
	uint   numSpaces = 0;
	for (uint cur_symbol = 0; cur_symbol < smsString.size(); ++cur_symbol)
	{
		if (smsString[cur_symbol] != ' ')
		{
			tempWord.push_back(smsString[cur_symbol]);
			if (cur_symbol+1 < smsString.size())
			{
				if (smsString[cur_symbol+1] == ' ')
				{
					sms.push_back(tempWord);
					tempWord.clear();
				}
			}
			else
			{
				sms.push_back(tempWord);
				tempWord.clear();
			}
		}
		else
		{
			++numSpaces;
			if (cur_symbol+1 < smsString.size())
			{
				if (smsString[cur_symbol+1] != ' ')
				{
					spaces.push_back(numSpaces);
					numSpaces = 0;
				}
			}
			else
			{
				spaces.push_back(numSpaces);
				numSpaces = 0;
			}
		}

	}

	for (uint cur_word=0; cur_word < sms.size(); ++cur_word)
	{
		sort(dictionary.begin(), dictionary.end(), moreRecently);

		vector<entry>	   variants;
		tempWord	     = sms[cur_word];
		uchar lettersNum = howManyLetters(tempWord);
		for (ushort cur_entry = 0; cur_entry < dictionary.size(); ++cur_entry)
		{
			if (dictionary[cur_entry].word.size() == lettersNum)
			{
				uchar equalities = 0;
				for (uchar cur_letter = 0; cur_letter < lettersNum; ++cur_letter)
				{
					string tempButton;
					for (uchar cur_button = 0; cur_button < buttons.size(); ++cur_button)
						if (tempWord[cur_letter] == buttons[cur_button][0])
							tempButton = buttons[cur_button];

					for (uchar cur_symbol = 1; cur_symbol < tempButton.size(); ++cur_symbol)
						if (dictionary[cur_entry].word[cur_letter] == tempButton[cur_symbol])
							++equalities;	
				}
				if (equalities == lettersNum && lettersNum != 0)
					variants.push_back(dictionary[cur_entry]);
			}
		}

		sort(variants.begin(), variants.end(), moreFrequently);

		ushort shift    = 0;
		uint cur_symbol = lettersNum;
		if (lettersNum)
		{
			if (lettersNum < sms[cur_word].size())
				if (sms[cur_word][lettersNum] != '1')
					while (sms[cur_word][cur_symbol] == '*')
					{
						++shift;
						++cur_symbol;
						if (cur_symbol == sms[cur_word].size())
							break;
					}
	
			for (ushort cur_entry = 0; cur_entry < dictionary.size(); ++cur_entry)
			{
				if (dictionary[cur_entry].word == variants[shift].word)
				{
					++dictionary[cur_entry].frequently;
					dictionary[cur_entry].recent = true;
				}
				else
					if (dictionary[cur_entry].frequently == variants[shift].frequently + 1)
						dictionary[cur_entry].recent  =  false;
			}	
		}
		if (variants.size())
		{
			punctuate(sms[cur_word], cur_symbol, variants[shift].word);
			out.push_back(variants[shift].word);
		}
		else
		{
			string emptyString;
			punctuate(sms[cur_word], cur_symbol, emptyString);
			out.push_back(emptyString);
		}
	}
	for (ushort cur_word = 0; cur_word < out.size(); ++cur_word)
		cout << out[cur_word] << " ";
	return 0;
}

