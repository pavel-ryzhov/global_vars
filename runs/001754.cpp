#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class WordWithFrequencyAndPhoneForm
{
	string GetWordInPhoneDigitsFromString(string word)
	{
		string outputword = "";

		for(int i = 0; i < word.size(); i++)
		{
			switch(word[i])
			{
			case 'a': case 'A': case 'b': case 'B': case 'c': case 'C': outputword += '2'; break;
			case 'd': case 'D': case 'e': case 'E': case 'f': case 'F': outputword += '3'; break;
			case 'g': case 'G': case 'h': case 'H': case 'i': case 'I': outputword += '4'; break;
			case 'j': case 'J': case 'k': case 'K': case 'l': case 'L': outputword += '5'; break;
			case 'm': case 'M': case 'n': case 'N': case 'o': case 'O': outputword += '6'; break;
			case 'p': case 'P': case 'q': case 'Q': case 'r': case 'R': case 's': case 'S': outputword += '7'; break;
			case 't': case 'T': case 'u': case 'U': case 'v': case 'V': outputword += '8'; break;
			case 'w': case 'W': case 'x': case 'X': case 'y': case 'Y': case 'z': case 'Z': outputword += '9'; break;
			}
		}
		
		return outputword;
	}

public:
	string Word;
	string WordInPhoneDigits;
	unsigned int Frequency;
	bool SignOfLastUse;

	WordWithFrequencyAndPhoneForm(string word, unsigned int frequency)
	{
		Word = word;
		Frequency = frequency;
		WordInPhoneDigits = GetWordInPhoneDigitsFromString(Word);
		SignOfLastUse = false;
	};
};

bool SortFunction (WordWithFrequencyAndPhoneForm i, WordWithFrequencyAndPhoneForm j) 
{ 
	if(i.Frequency != j.Frequency)
		return i.Frequency > j.Frequency;

	if(i.SignOfLastUse)
		return true;
	if(j.SignOfLastUse)
		return false;
	
	return i.Word < j.Word;
}

class T9
{
	string GetWordFromStringWithAsterisks(string str)
	{
		int NumberOfAsterisk = 0;
		string Word = str.substr(0, str.find("*"));
		
		if(str.find("*") != -1)
		{
			NumberOfAsterisk = str.length() - str.find("*");
		}
		
		long Position;
		Position = GetPositionInVocabularyByWordInPhoneDigits(Word);

		Word = Dictionary[Position][NumberOfAsterisk].Word;
		
		for(unsigned int i = 0; i < Dictionary[Position].size(); i++)
		{
			if(Dictionary[Position][i].Word == Word)
			{
				Dictionary[Position][i].SignOfLastUse = true;
				Dictionary[Position][i].Frequency++;
			}
			else
			{
				Dictionary[Position][i].SignOfLastUse = false;
			}
		}

		// "Продвигаем" использованное слово в словаре
		while(NumberOfAsterisk > 0 && Dictionary[Position][NumberOfAsterisk].Frequency >= Dictionary[Position][NumberOfAsterisk-1].Frequency)
		{
			WordWithFrequencyAndPhoneForm temp = Dictionary[Position][NumberOfAsterisk];
			Dictionary[Position][NumberOfAsterisk] = Dictionary[Position][NumberOfAsterisk-1];
			Dictionary[Position][NumberOfAsterisk-1] = temp;

			NumberOfAsterisk--;
		};
	
		return Word;
	};

	string GetPunctuationFromString(string str)
	{
		string outputstr = "";
		while(str.find("1") != -1)
		{
			str = str.substr(1);
			int NumberOfPunctuationAsterisk = str.substr(0, str.find("1")).size();
			str = str.substr(NumberOfPunctuationAsterisk);
			switch(NumberOfPunctuationAsterisk)
			{
			case 0: outputstr += '.'; break;
			case 1: outputstr += ','; break;
			case 2: outputstr += '?'; break;
			};
		};

		return outputstr;
	};

	string GetWordFromT9String(string T9String)
	{
		string MainPart;
		string outputWord = "";

		if(T9String[0] != '1')
		{
			MainPart = T9String.substr(0, T9String.find("1")); // Всё что относится к слову
			
			if(T9String.find("1") != -1)
			{
				outputWord += GetWordFromStringWithAsterisks(MainPart) + GetPunctuationFromString(T9String.substr(T9String.find("1")));
			}
			else
				outputWord = GetWordFromStringWithAsterisks(MainPart);		
		}
		else
		{
			outputWord = GetPunctuationFromString(T9String);
		}

		return outputWord;

	};

public:
	vector< vector<WordWithFrequencyAndPhoneForm> > Dictionary;
	
	void ReadDictionary()
	{	
		try
		{
			string Word;
			unsigned int Frequency;
			unsigned int WordCount;
			long Position;
			
			cin >> WordCount;	
						
			for(unsigned int i = 0; i < WordCount; i++)
			{
				cin >> Word;
				cin >> Frequency;
				
				WordWithFrequencyAndPhoneForm wordWithFrequencyAndPhoneForm(Word, Frequency);

				Position = GetPositionInVocabularyByWordInPhoneDigits(wordWithFrequencyAndPhoneForm.WordInPhoneDigits);
				if(Position == -1)
				{
					vector<WordWithFrequencyAndPhoneForm> newword;
					newword.push_back(wordWithFrequencyAndPhoneForm);
					Dictionary.push_back(newword);
				}
				else
				{
					Dictionary[Position].push_back(wordWithFrequencyAndPhoneForm);
				}
			}
		}
		catch(char *str)
		{
			cerr << "Ошибка: " << str << "\n";
		}

		for(unsigned int i=0; i < Dictionary.size(); i++)
		{
			sort(Dictionary[i].begin(),Dictionary[i].end(), SortFunction);		
		}
	};



	// Функция поиска по словарю (можно оптимизировать)
	unsigned int GetPositionInVocabularyByWordInPhoneDigits(string str)
	{
		// TODO: Поиск можно оптимизировать
		for(unsigned int i = 0; i < Dictionary.size(); i++)
		{
			if(Dictionary[i][0].WordInPhoneDigits == str)
				return i;
		}

		return -1;
	};

	void ParseInputText()
	{
		string outputstring = "";
		string questionWord = "";
		string inputstring;	
		
		getline(cin, inputstring);
		getline(cin, inputstring);

		for(int i = 0; i < inputstring.size(); i++)
		{
			if(inputstring[i] == ' ')
			{
				if(questionWord != "") 
				{
					cout << GetWordFromT9String(questionWord) + " ";
					questionWord = "";
				}
				else
					cout << ' ';	
			}
			else
			{
				questionWord += inputstring[i];
			}
		}
		if(questionWord != "")
			cout << GetWordFromT9String(questionWord);

	};
};

int main()
{
	T9 t9;

	//freopen("C:\\Yandex\\3.txt","r",stdin); 
	//freopen("C:\\Yandex\\Answer3.txt","w",stdout);
	
	t9.ReadDictionary();

	t9.ParseInputText();

	

	return 0;
};
