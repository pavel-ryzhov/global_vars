// T9.cpp : Defines the entry point for the console application.
//
#include "iostream"
#include "map"
#include "list"
#include <string>
//#include <Windows.h>

struct Word
{
	std::string sWord;
	int iFreq;
	unsigned long iAddFreq;

	Word()
	{
		sWord = "";
		iFreq = 0;
		iAddFreq = 0;
	}

	Word(std::string _sWord, int _iFreq, unsigned long _iAddFreq)
	{
		sWord = _sWord;
		iFreq = _iFreq;
		iAddFreq = _iAddFreq;
	}

	bool operator<(const Word& rhs) const
	{
		if(iFreq == rhs.iFreq)
		{
			return (iAddFreq <= rhs.iAddFreq);
		}

		return (iFreq > rhs.iFreq);
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

	inline int GetIndexByLitera(const char cLitera)
	{
		for(int i = 1; i < 9; i++)
		{
			for(int j = 0; j < alphabetSize[i]; j++)
			{
				if(alphabet[i][j] == cLitera)
				{
					return i + 1;
				}
			}
		}

		return -1;
	}

	std::string GetCodeByWord(std::string sWord)
	{
		int iWordSize = (int)sWord.size();
		for(int i = 0; i < iWordSize; i++)
		{
			sWord[i] = '0' + GetIndexByLitera(sWord[i]);
		}

		return sWord;
	}

	void CodeFromWord(std::string& sWord)
	{
		int iWordSize = (int)sWord.size();
		for(int i = 0; i < iWordSize; i++)
		{
			sWord[i] = '0' + GetIndexByLitera(sWord[i]);
		}
	}
}

struct CompStrings 
{
	bool operator() (const std::string& lhs, const std::string& rhs) const
	{
		return (lhs.compare(rhs) < 0);
	}
};

static unsigned long iAdditionalFrequetly = 0;
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
		m_Dict[sCode].push_front(Word(sWord, iFrequency, iAdditionalFrequetly++));
	}

	void PrintWordAndIncreaseFreq(std::string sWordCode, int iWordNumber)
	{
		WordList& lValidWords = m_Dict[sWordCode];
		lValidWords.sort();

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

/*	DWORD timeStart = GetTickCount();
	for(int i = 0; i < 26; i++)
		for(int j = 0; j < 26; j++)
			for(int k = 0; k < 26; k++)
				for(int l = 0; l < 26; l++)
				{
					char aWord[5];
					aWord[0] = 'a' + l;
					aWord[1] = 'a' + k;
					aWord[2] = 'a' + j;
					aWord[3] = 'a' + i;
					aWord[4] = '\0';
					std::string sWord = std::string(aWord);

					dict->AddNewWord(TelephoneAlphabet::GetCodeByWord(aWord), sWord, 1);
				}
	DWORD timeEnd = GetTickCount();
	std::cout<<timeEnd - timeStart << " ms";*/
	//dict->PrintDictionary();

	//std::string sWordCode = TelephoneAlphabet::GetCodeByWord("cat");

	
	unsigned int iDictionarySize = 0;
	std::cin >> iDictionarySize;
	std::string sWord;
	int iFreq;
	for(unsigned int i = 0; i < iDictionarySize; ++i)
	{
		std::cin >> sWord;
		std::cin >> iFreq;

		std::string sCode = sWord;
		TelephoneAlphabet::CodeFromWord(sCode);
		dict->AddNewWord(sCode, sWord, iFreq);
	}
	std::cin.ignore();

	std::string sInputData;
	std::getline(std::cin, sInputData);

	Analizator::TextAnalizator *tAnalizator = new Analizator::TextAnalizator(dict, sInputData);
	tAnalizator->StartProcess();
	delete tAnalizator;

	//int i = 0;
	//std::cin>>i;
}