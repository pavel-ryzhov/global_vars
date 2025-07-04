// T9.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
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
}


struct CompStrings 
{
	bool operator() (const std::string& lhs, const std::string& rhs) const
	{
		return (lhs.compare(rhs) < 0);
	}
};

struct Frequently
{
	int iFreq;
	int iAddFreq;

	Frequently()
	{
		iFreq = iAddFreq = 0;
	}

	Frequently(int _iFreq, int _iAddFreq)
	{
		iFreq = _iFreq;
		iAddFreq = _iAddFreq;
	}
};

typedef std::map<std::string, Frequently, CompStrings> MapDictionary;

class Dictionary{
private:
	MapDictionary m_Dict;

public:
	Dictionary(){};
	~Dictionary(){};

	void AddNewWord(std::string sWord, int iFrequency, int iAddFrequency)
	{
		m_Dict[sWord] = Frequently(iFrequency, iAddFrequency);
	}

	void IncreaseFrequency(std::string sWord, int iAddVal = 1)
	{
		m_Dict[sWord].iFreq += iAddVal;

		int iBuffVal = m_Dict[sWord].iAddFreq;
		for(MapDictionary::iterator it = m_Dict.begin(); it != m_Dict.end(); it++)
		{
			if(it->second.iAddFreq < iBuffVal)
				it->second.iAddFreq++;
		}
	
		m_Dict[sWord].iAddFreq = 0;
	}

	std::list<Word> SearchWordsByFirstLiterDiapazone(char cFirst, char cEnd)
	{
		cEnd++;
		MapDictionary::const_iterator itFirst = m_Dict.lower_bound(std::string(&cFirst, 0, 1));
		MapDictionary::const_iterator itEnd = m_Dict.lower_bound(std::string(&cEnd, 0, 1));
		
		std::list<Word> SearchedList;
		for(itFirst; itFirst != itEnd; itFirst++)
		{
			SearchedList.push_back(Word(itFirst->first, itFirst->second.iFreq, itFirst->second.iAddFreq));
		}
	
		return SearchedList;
	}

	void PrintDictionary()
	{
		MapDictionary::const_iterator it = m_Dict.begin();
		for(it; it != m_Dict.end(); it++)
		{
			std::cout<< it->first.c_str()<< "(" << it->second.iFreq << ")" << std::endl;
		}
	}
};

///
class SearchWords
{
	int m_iNLiters;
	std::list<Word> m_lFitWords;
	SearchWords(){};
public:
	

	SearchWords(int iFirstNumber, Dictionary& Dict)
	{
		m_lFitWords.clear();
		
		m_lFitWords = Dict.SearchWordsByFirstLiterDiapazone(
			TelephoneAlphabet::alphabet[iFirstNumber][0], 
			TelephoneAlphabet::alphabet[iFirstNumber][TelephoneAlphabet::alphabetSize[iFirstNumber] - 1]);

		m_iNLiters = 1;
	};

	void AddNextLiteraIndex(int index)
	{
		std::list<Word>::iterator it = m_lFitWords.begin();
		for(it; it != m_lFitWords.end(); )
		{
			bool bIsFitWord = false;
			const char cCurrentLitera = it->sWord[m_iNLiters];
			for(int i = 0; i < TelephoneAlphabet::alphabetSize[index]; i++)
			{
				if(cCurrentLitera == TelephoneAlphabet::alphabet[index][i])
				{
					bIsFitWord = true;
					break;
				}
			}	
			
			if(!bIsFitWord) 
			{
				it = m_lFitWords.erase(it);
			}
			else
			{
				it++;
			}
		}

		m_iNLiters++;
	}

	std::list<Word> GetList()
	{
		return m_lFitWords;
	}

	void SortList()
	{
		m_lFitWords.sort();
		m_lFitWords.reverse();
	}

	std::string GetFirstWord(int iLitersInWord)
	{
		SortList();

		std::list<Word>::iterator it = m_lFitWords.begin();
		while(it != m_lFitWords.end())
		{
			if( (int)it->sWord.size() == iLitersInWord )
			{
				return it->sWord;
			}
			it++;
		}

		return "ERROR2";
		//Word wFirst = m_lFitWords.front();
		//return wFirst.sWord;
	}

	std::string GetWordByIndex(int index, int iLitersInWord)
	{
		SortList();

		int iListSize = (int)m_lFitWords.size();
		if(!iListSize) return "ERROR1";

		if( index >= iListSize)
		{
			index %= iListSize;
		}

		int i = 0;
		std::list<Word>::iterator it = m_lFitWords.begin();
		while(it != m_lFitWords.end())
		{
			if( (int)it->sWord.size() == iLitersInWord )
			{
				i++;
			}
			it++;

			if(i == index && (int)it->sWord.size() == iLitersInWord)
			{
				return it->sWord;
			}
		}

		return it->sWord;
	}

	void PrintList()
	{
		std::list<Word>::const_iterator it = m_lFitWords.begin();
		for(it; it != m_lFitWords.end(); it++)
		{
			std::cout << it->sWord.c_str() << " : " << it->iFreq << std::endl;
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

		SearchWords* sw;
		SymbolType m_stPreviousSymbol;
		int m_iLitersInWord;
		int m_iCountStars;


		void EndWordWithoutStars()
		{
			// Print first word and increase his frequently
			std::string sWord = sw->GetFirstWord(m_iLitersInWord);
			m_dict->IncreaseFrequency(sWord);
			std::cout<<sWord;
			delete sw;
			sw = NULL;
		}

		void EndWordWithStars()
		{
			std::string sWord = sw->GetWordByIndex(m_iCountStars, m_iLitersInWord);
			m_iCountStars = 0;

			m_dict->IncreaseFrequency(sWord);
			std::cout<<sWord;
			delete sw;
			sw = NULL;
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
				EndWordWithStars();
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
				EndWordWithoutStars();
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
			sw = NULL;
			m_iCountStars = 0;
		};
		
		~TextAnalizator()
		{
			delete m_dict;
			
			if(sw)
			{
				delete sw;
				sw = NULL;
			}
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

					if(sw == NULL)
					{
						sw = new SearchWords(iNumb, *m_dict);
						m_iLitersInWord = 1;
					}
					else
					{
						sw->AddNextLiteraIndex(iNumb);
						m_iLitersInWord++;
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

	//dict->AddNewWord("ad", 2);
	//dict->AddNewWord("be", 1);
	//dict->AddNewWord("not", 10);
	//dict->AddNewWord("or", 5);
	//dict->AddNewWord("to", 50);

	//dict->AddNewWord("act", 1);
	//dict->AddNewWord("bat", 1);
	//dict->AddNewWord("cat", 1);

/*	dict->AddNewWord("and", 1, 0);
	dict->AddNewWord("bat", 1, 1);
	dict->AddNewWord("bats", 1, 2);
	dict->AddNewWord("black", 1, 3);
	dict->AddNewWord("cat", 1, 4);
	dict->AddNewWord("cats", 1, 5);
	dict->AddNewWord("eat", 1, 6);
	dict->AddNewWord("fat", 1, 7);
	dict->AddNewWord("grey", 1, 8);
	dict->AddNewWord("is", 1, 9);
	dict->AddNewWord("likes", 1, 10);
	dict->AddNewWord("my", 1, 11);
	dict->AddNewWord("rats", 1, 12);
*/

	//dict->PrintDictionary();

	unsigned int iDictionarySize = 0;
	std::cin >> iDictionarySize;
	std::string sWord;
	int iFreq;
	for(unsigned int i = 0; i < iDictionarySize; ++i)
	{
		std::cin >> sWord;
		std::cin >> iFreq;

		dict->AddNewWord(sWord, iFreq, i);
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

