#include <map>
#include <list>
#include <iostream>
#include <string>

using namespace std;


class WordsForChoice
{
	map<int, list<string> > ListsOfWords;
public:
	void AddWord(string &, int);
	string GetWord(int);
	void AddFrontWord(string &Word, int Priority);
};
class Dictionary
{
public:
	map<string, WordsForChoice> Combinations;
public:
	void Initialize();
	void PutWord(string &Word, int Priority);
	string GetWordOfComb(string, int);
};

char LetterToNumber(const char);
int Analyse(const Dictionary &);
string AnalysePunct(string);

void WordsForChoice::AddWord(string &Word, int Priority)
{
	map<int, list<string> >::iterator LWIter;
	list<string> WordsOfPriority;
	LWIter = ListsOfWords.find(Priority);
	if (LWIter != ListsOfWords.end())
	{
		LWIter->second.push_back(Word);
	}
	else
	{
		WordsOfPriority.push_back(Word);
		ListsOfWords[Priority] = WordsOfPriority;
	}

}

void WordsForChoice::AddFrontWord(string &Word, int Priority)
{
	map<int, list<string> >::iterator LWIter;
	list<string> WordsOfPriority;
	LWIter = ListsOfWords.find(Priority);
	if (LWIter != ListsOfWords.end())
	{
	
		LWIter->second.push_front(Word);
	}
	else
	{
		WordsOfPriority.push_back(Word);
		this->ListsOfWords[Priority] = WordsOfPriority;
	}

}

string WordsForChoice::GetWord(int AmountOfAsterisks)
{
	string WordWanted;
	map<int, list<string> >::iterator SearchIter;
	list<string>::iterator ListIter;
	SearchIter = ListsOfWords.end();
	SearchIter--;
	while (SearchIter->second.size()<=AmountOfAsterisks)
	{
		AmountOfAsterisks -= SearchIter->second.size();
		SearchIter--;
	}
	ListIter = SearchIter->second.begin();
	int i;
	for (i = 0; i < AmountOfAsterisks; i++)
		ListIter++;
	WordWanted = *ListIter;
	this->AddFrontWord(WordWanted, (SearchIter->first) + 1);

	
	SearchIter->second.erase(ListIter);
	if (SearchIter->second.size() == 0)
		this->ListsOfWords.erase(SearchIter);
	return WordWanted;

}

void Dictionary::Initialize()
{
	unsigned int n;
	int Priority;
	string Word;
	cin>>n;
	for (unsigned int i = 0; i < n; i++)
	{
		cin>>Word>>Priority;
		PutWord(Word, Priority);
	}
}

void Dictionary::PutWord(string &Word, int Priority)
{
	string NumberCombination;
	map<string, WordsForChoice>::iterator CurCombIter;
	WordsForChoice WordsOfCombination;
	for (int i = 0; i < Word.size(); i++)
	{
		NumberCombination = NumberCombination + LetterToNumber(Word[i]);
	}

	CurCombIter = Combinations.find(NumberCombination);
	if (CurCombIter != Combinations.end())
	{
		CurCombIter->second.AddWord(Word, Priority);
	}
	else
	{
		WordsOfCombination.AddWord(Word, Priority);
		Combinations[NumberCombination] = WordsOfCombination;
	}
}

string Dictionary::GetWordOfComb(string Comb, int AmountOfAsterisks)
{
	return Combinations[Comb].GetWord(AmountOfAsterisks);
}

char LetterToNumber(const char Letter)
{
	if ((Letter == 'a')||(Letter == 'b')||(Letter == 'c'))
	{
		return '2';
	}
	else if ((Letter == 'd')||(Letter == 'e')||(Letter == 'f'))
	{
		return '3';
	}
    else if ((Letter == 'g')||(Letter == 'h')||(Letter == 'i'))
	{
		return '4';
	}
	else if ((Letter == 'j')||(Letter == 'k')||(Letter == 'l'))
	{
		return '5';
	}
	else if ((Letter == 'm')||(Letter == 'n')||(Letter == 'o'))
	{
		return '6';
	}
	else if ((Letter == 'q')||(Letter == 'r')||(Letter == 's'))
	{
		return '7';
	}
	else if ((Letter == 't')||(Letter == 'u')||(Letter == 'v'))
	{
		return '8';
	}
	else if ((Letter == 'w')||(Letter == 'x')||(Letter == 'y')||(Letter == 'z'))
	{
		return '9';
	}
	else
	{
		return '0';
	}
}

int Analyse(Dictionary & MyDictionary)
{
	string Word, Punctuation, WordOfComb;
	
	char c = 'e';
	cin.get();
	getline(cin, Word, ' ');
	while (true)
	{
		string::size_type PositionOf1, WordSize, FirstAsterisk;
		string::size_type AmountOfAsterisks, CombinationSize = 0;
		WordSize = Word.size();
		PositionOf1 = Word.find('1');
		FirstAsterisk = Word.find('*');
		if ((PositionOf1 != string::npos)&&(FirstAsterisk == string::npos))
		{
			AmountOfAsterisks = 0;	
			CombinationSize = PositionOf1;
		}
		if ((PositionOf1 != string::npos)&&(FirstAsterisk != string::npos))
		{
			if (PositionOf1 > FirstAsterisk)
			{
				AmountOfAsterisks = PositionOf1 - FirstAsterisk;
				CombinationSize = FirstAsterisk;
			}
			else
			{
				AmountOfAsterisks = 0;	
				CombinationSize = PositionOf1;
			}
		}

		if ((PositionOf1 == string::npos)&&(FirstAsterisk != string::npos))
		{
			AmountOfAsterisks = WordSize-FirstAsterisk;	
			CombinationSize = FirstAsterisk;
		}

		if ((PositionOf1 == string::npos)&&(FirstAsterisk == string::npos))
		{
			AmountOfAsterisks = 0;	
			CombinationSize = WordSize;
		}

		if (PositionOf1 != string::npos)
		{
			Punctuation = AnalysePunct(Word.substr(PositionOf1,WordSize-PositionOf1));
		}
		else
			Punctuation = "";
		if (CombinationSize == 0)
		{
			cout << Punctuation;
		}
		else
			cout << MyDictionary.GetWordOfComb(Word.substr(0,CombinationSize),AmountOfAsterisks) << Punctuation;
		if (cin.eof())
			return 0;
		else
			cout << ' ';
		c = cin.get();
		while ((c == ' ')&&!(cin.eof()))
		{
			cout << ' ';
			c = cin.get();
		}
		if (cin.eof())
			return 0;		

		getline(cin, Word, ' ');
		Word = c + Word;
	}
	return 0;
}

string AnalysePunct(string PunctWord)
{
	int i = 0;
	int PWordSize;
	string Punct = "";
	PWordSize = PunctWord.size();
	while (i < PWordSize)
	{
		if (i+1 >= PWordSize)
			return Punct + '.';
		if ((PunctWord[i+1] == '*')&&(i+2 >= PWordSize))
			return Punct + ',';
		if (PunctWord[i+1] == '1')
		{
			Punct = Punct + '.';
			i++;
		}
		else
		{
			if ((PunctWord[i+2] == '*')&&(i+3 >= PWordSize))
				return Punct + '?';
			if (PunctWord[i+2] == '1')
			{
				Punct = Punct + ',';
				i += 2;
			}
			else
			{
				Punct = Punct + '?';
				i += 3;
			}
		}
	}
}

int main ()
{
	Dictionary MyDictionary;
	MyDictionary.Initialize();

	Analyse(MyDictionary);
	
	return 0;
}