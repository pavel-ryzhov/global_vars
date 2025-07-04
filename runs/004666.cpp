// T9.cpp : Defines the entry point for the console application.
//
#include "iostream"
#include "map"
#include "list"
#include <string>

struct Word
{
	std::string sWord;
	int iFreq;
	int iAddFreq;

	Word(std::string _sWord, int _iFreq, int _iAddFreq)
	{
		sWord = _sWord;
		iFreq = _iFreq;
		iAddFreq = _iAddFreq;
	}

	bool operator<(const Word& rhs) const
	{
		if(iFreq == rhs.iFreq)
		{
			//return (sWord.compare(rhs.sWord) > 0);
			return (iAddFreq > rhs.iAddFreq);
		}

		return (iFreq < rhs.iFreq);
	}
};

namespace TelephoneAlphabet
{
	const char alphabet[9][4]= {
		{'.', ',', '?'},
		{'a', 'b', 'c'},
		{'d', 'e', 'f'},
		{'g', 'h', 'i'},
		{'j', 'k', 'l'},
		{'m', 'n', 'o'},
		{'p', 'q', 'r', 's'},
		{'t', 'u', 'v'},
		{'w', 'x', 'y', 'z'}
	};

	const int alphabetSize[9] = {3, 3, 3, 3, 3, 3, 4, 3, 4};

	char GetIndexByLitera(char cLitera)
	{
		for(int i = 1; i < 9; i++)
		{
			for(int j = 0; j < alphabetSize[i]; j++)
			{
				if(alphabet[i][j] == cLitera)
				{
					char cBuffer[2];
					sprintf(cBuffer, "%d", i+1);
					//itoa(i+1, cBuffer, 10);
					return cBuffer[0];
				}
			}
		}

		return 'e';
	}

	std::string GetCodeByWord(std::string sWord)
	{
		for(int i = 0; i < (int)sWord.size(); i++)
		{
			sWord[i] = GetIndexByLitera(sWord[i]);
		}

		return sWord;
	}
}

struct CompStrings 
{
	bool operator() (const std::string& lhs, const std::string& rhs) const
	{
		return (lhs.compare(rhs) < 0);
	}
};

typedef std::list<Word> WordList;
typedef std::map<std::string, WordList, CompStrings> MapDictionary;

class Dictionary{
private:
	MapDictionary m_Dict;

public:
	Dictionary(){};
	~Dictionary(){};

	void AddNewWord(std::string sCode, std::string sWord, int iFrequency)
	{
		if(m_Dict.find(sCode) != m_Dict.end())
		{
			// This word code already exist
			m_Dict[sCode].push_back(Word(sWord, iFrequency, (int)m_Dict[sCode].size()));
		}
		else
		{
			// Add new word code in dictionary
			m_Dict[sCode].push_back(Word(sWord, iFrequency, 0));
		}
	}

	void PrintWordAndIncreaseFreq(std::string sWordCode, int iWordNumber)
	{
		WordList& lValidWords = m_Dict[sWordCode];
		lValidWords.sort();
		lValidWords.reverse();

		int i = 0;
		WordList::iterator it = lValidWords.begin();
		while(i != iWordNumber)
		{
			i++; 
			if(++it == lValidWords.end())
			{
				it = lValidWords.begin();
			}
		}

		// Print word
		std::cout<<it->sWord;

		// Increase frequently
		it->iFreq++;
		
		// And additional frequently
		for(WordList::iterator itVW = lValidWords.begin(); itVW != lValidWords.end(); itVW++)
		{
			itVW->iAddFreq++;
		}
		it->iAddFreq = 0;
	}

	void PrintDictionary()
	{
		MapDictionary::const_iterator it = m_Dict.begin();
		for(it; it != m_Dict.end(); it++)
		{
			std::cout<< it->first.c_str()<< ":" << std::endl;
			for(WordList::const_iterator itList = it->second.begin(); itList != it->second.end(); itList++)
			{
				std::cout<< itList->sWord.c_str()<< " : " << itList->iFreq << " : " << itList->iAddFreq << std::endl;
			}
		}
	}
};

namespace Analizator
{
	enum SymbolType
	{
		TEXT_LITERA = 0,
		SEPARATE,
		STAR_AFTER_LITERA,
		STAR_AFTER_SEPARATE,
		ANOTHER,
		NOTHING
	};

	class TextAnalizator
	{
		Dictionary* m_dict;
		std::string m_sInputData;

		SymbolType	m_stPreviousSymbol;
		
		std::string m_sWordCode;
		int					m_iCountStars;
		bool				m_bIsNewWord;

		void EndWord()
		{
			m_dict->PrintWordAndIncreaseFreq(m_sWordCode, m_iCountStars);
			m_sWordCode = "";
			m_iCountStars = 0;
			m_bIsNewWord = true;
		}

		void EndSeparate()
		{
			if(m_stPreviousSymbol == STAR_AFTER_SEPARATE)
			{
				// Set First Symbol
				if(m_iCountStars >= TelephoneAlphabet::alphabetSize[0])
				{				
					m_iCountStars %= TelephoneAlphabet::alphabetSize[0];
				}
				std::cout<<TelephoneAlphabet::alphabet[0][m_iCountStars];

				m_iCountStars = 0;
			}
			else if(m_stPreviousSymbol == SEPARATE)
			{
				std::cout<<TelephoneAlphabet::alphabet[0][0];
			}
		}

		void EndWordWithoutStarsOrSeparate()
		{
			if(m_stPreviousSymbol == STAR_AFTER_LITERA)
			{
				EndWord();
			}
			else 
			{
				EndSeparate();
			}
		}

		void EndWordOrSeparate()
		{
			if(m_stPreviousSymbol == TEXT_LITERA)
			{
				EndWord();
			}
			else 
			{
				EndWordWithoutStarsOrSeparate();
			}
		}

	public:
		TextAnalizator(Dictionary* dict, std::string sInputData)
			:m_dict(dict), m_sInputData(sInputData)
		{
			m_stPreviousSymbol = NOTHING;
			m_sWordCode = "";
			m_iCountStars = 0;
			m_bIsNewWord = true;
		};
		
		~TextAnalizator()
		{
			delete m_dict;
		};

		void StartProcess()
		{
			for(std::string::const_iterator it = m_sInputData.begin(); it != m_sInputData.end(); it++)
			{
				char chCurrent = *it;
				if(chCurrent >= '2' && chCurrent <= '9')
				{
					EndWordWithoutStarsOrSeparate();

					int iNumb = chCurrent - '0' - 1; 

					if(m_bIsNewWord)
					{
						m_sWordCode = chCurrent;
						m_bIsNewWord = false;
					}
					else
					{
						m_sWordCode += chCurrent;
					}

					m_stPreviousSymbol = TEXT_LITERA;
				}
				else if(chCurrent == '*')
				{
					if(m_stPreviousSymbol == TEXT_LITERA)
					{
						m_iCountStars = 1;
						m_stPreviousSymbol = STAR_AFTER_LITERA;
					}
					else if(m_stPreviousSymbol == SEPARATE)
					{
						m_iCountStars = 1;
						m_stPreviousSymbol = STAR_AFTER_SEPARATE;
					}
					else if(m_stPreviousSymbol == STAR_AFTER_LITERA ||
									m_stPreviousSymbol == STAR_AFTER_SEPARATE)
					{
						m_iCountStars++;
					}
					else
					{
						m_stPreviousSymbol = ANOTHER;
					}
				}
				else if(chCurrent == '1')
				{
					EndWordOrSeparate();
					m_stPreviousSymbol = SEPARATE;
				}
				else
				{
					EndWordOrSeparate();
					std::cout<<chCurrent;
					m_stPreviousSymbol = ANOTHER;
				}
			}

			EndWordOrSeparate();
		}
	};
}

int main(int argc, char* argv[])
{
	Dictionary* dict = new Dictionary();

	//dict->AddNewWord(TelephoneAlphabet::GetCodeByWord("act"),"act", 1);
	//dict->AddNewWord(TelephoneAlphabet::GetCodeByWord("bat"),"bat", 1);
	//dict->AddNewWord(TelephoneAlphabet::GetCodeByWord("cat"),"cat", 1);
/*
	dict->AddNewWord(TelephoneAlphabet::GetCodeByWord("and"), "and", 1);
	dict->AddNewWord(TelephoneAlphabet::GetCodeByWord("bat"), "bat", 1);
	dict->AddNewWord(TelephoneAlphabet::GetCodeByWord("bats"), "bats", 1);
	dict->AddNewWord(TelephoneAlphabet::GetCodeByWord("black"), "black", 1);
	dict->AddNewWord(TelephoneAlphabet::GetCodeByWord("cat"), "cat", 1);
	dict->AddNewWord(TelephoneAlphabet::GetCodeByWord("cats"), "cats", 1);
	dict->AddNewWord(TelephoneAlphabet::GetCodeByWord("eat"), "eat", 1);
	dict->AddNewWord(TelephoneAlphabet::GetCodeByWord("fat"), "fat", 1);
	dict->AddNewWord(TelephoneAlphabet::GetCodeByWord("grey"), "grey", 1);
	dict->AddNewWord(TelephoneAlphabet::GetCodeByWord("is"), "is", 1);
	dict->AddNewWord(TelephoneAlphabet::GetCodeByWord("likes"), "likes", 1);
	dict->AddNewWord(TelephoneAlphabet::GetCodeByWord("my"), "my", 1);
	dict->AddNewWord(TelephoneAlphabet::GetCodeByWord("rats"), "rats", 1);
*/
	//dict->PrintDictionary();

	//dict->PrintWordAndIncreaseFreq("228", 1);
	//std::cout<<" ";

	//std::string sWordCode = TelephoneAlphabet::GetCodeByWord("cat");

	
	unsigned int iDictionarySize = 0;
	std::cin >> iDictionarySize;
	std::string sWord;
	int iFreq;
	for(unsigned int i = 0; i < iDictionarySize; ++i)
	{
		std::cin >> sWord;
		std::cin >> iFreq;

		dict->AddNewWord(TelephoneAlphabet::GetCodeByWord(sWord), sWord, iFreq);
	}
	std::cin.ignore();
	

	std::string sInputData;
	std::getline(std::cin, sInputData);

	Analizator::TextAnalizator *tAnalizator = new Analizator::TextAnalizator(dict, sInputData);
	tAnalizator->StartProcess();
	delete tAnalizator;

//	int i = 0;
//	std::cin>>i;
}