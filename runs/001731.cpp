/* עוסעמגûי פאיכ Dictionary.t9
16
act 1
ad 1
as 1
bat 1
be 1
cat 1
he 1
king 1
lalala 1
me 1
not 1
on 1
or 1
queen 1
to 1
you 1
*/


#include <string>
#include <exception>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <set>
//#include <conio.h>

const std::string DICTIONARY_DEFAULT = "Dictionary.t9";
const std::string ADDTODICTIONARY_DEFAULT = "add.t9";
const std::string BUTTONS = "23456789";
const std::string PUNCTUATION_MARKS = "?.,";
const char PUNCUATION_BUTTON = '1';
const char SPACE = ' ';
const char STAR = '*';
const std::string EXIT = "exit";
const int PUNCTUATION_MODULE[] = {2, 0, 1};
const std::string CURSOR_WAITING = ">>>>>>>>>>>>>>>>";


//class Word

namespace StCat
{
	class Word
	{
	public:
		Word(const std::string& word, int rating);
		const std::string& GetWord() const;
		int GetRating() const;
		static void SetWordPriority();
		static void IgnoreRating(bool ingoreIt = true);
		static bool IsRatingIgnored();
		static void SetRatingPriority();
		const std::string& GetKey() const;
		void IncreaseRating();

	public:
		bool LessThan(const Word& rhs);
		bool operator == (const Word& rhs) const;

	private:
		void MakeKey();

	private:
		std::string word_;
		int rating_;
		static bool wordPriority_;
		static bool ignoreRating_;
		std::string key_;
	};

	bool operator < (const Word& lhs, const Word& rhs);
}

//class MapException

namespace StCat
{
	class MapException : public std::exception
	{
	public:
        virtual ~MapException() throw();
		MapException(const std::string& errExplanation);
		virtual const char* what() const throw();

	private:
		std::string what_;
	};
}

//class Dictionary

namespace StCat
{
	class Dictionary
	{
		typedef std::set<Word> WordSet_t;
		typedef WordSet_t::iterator WordSetIterator_t;
		typedef WordSet_t::const_iterator WordSetConstIterator_t;

		typedef std::multimap<std::string, Word> StringWordMap_t;
		typedef StringWordMap_t::iterator StringWordIteratorMap_t;
		typedef StringWordMap_t::const_iterator StringWordConstIteratorMap_t;

		typedef std::vector<Word> WordVector_t;

		typedef std::set<int, std::greater<int> > IntSet_t;
		typedef IntSet_t::iterator IntIteratorSet_t;

	public:
		Dictionary(const std::string& dic);

		void AddWord(const Word& word);
		void NewDictionary(const std::string& dic);
		void AppendDictionary(const std::string& newDic);
		void ShowDictionary() const;
		void CheckExistance(const std::string& fileName);
		void SaveDictionary(const std::string& smsMsg = "", const std::string& sms = "");
		const std::string& GetWord(const std::string& key);
		const std::string& GetCurrentWord() const;
		void IncreaseRating();
		const std::string& GetNextWord();


	public:
		void Index();

	private:
		void Initialize();
		void CreateRoundedVector();

	private:
		std::string dictionaryFileName_;
		WordVector_t roundedVector_;
		int posInRoundedVector_;
		WordSet_t wordSet_;
		StringWordMap_t indexedMap_;
		bool indexed_;
		std::string currentWord_;
		std::string currentKey_;
		StringWordIteratorMap_t currentKeyIterator_;
		IntSet_t ratingsSet_;

	};
}


int main(int argc, char* argv[])
{
	try
	{
		const int maxCommandSize = 100000;
		std::string sms;
		std::string smsMsg;
		char commandLine[maxCommandSize];
		std::string commandLineString;

//		std::cout << "T9 emulyaciya"  << std::endl;
//		std::cout << "programmist: Aleksandr Chulkin" << std::endl;
//		std::cout << "version 1.1" << std::endl;
//		std::cout << "Dlya vvoda slova naberite kombinaciyu cifr, sootvetstvuyushuyu emu v slovare T9,"; 
//		std::cout << " posle chego najmite klavishu vvoda. dlya smeny slova naberite simvol *";
//		std::cout << " i klavishu vvoda. Dlya probela najmite cifru 0, i klavishu vvoda. ";
//		std::cout << "Slovar' nahoditsya v faile Dictionary.t9.";
//		std::cout << " Dlya vyhoda iz programmy s sohraneniem reitinga v slovar ";
//		std::cout << "i vyvodom nabrannogo texta, naberite exit i najmite klavishu vvoda" << std::endl;

		std::string dictionaryFileNameT9;
		std::string addToDictionaryFileNameT9;

		dictionaryFileNameT9 = DICTIONARY_DEFAULT;
		StCat::Dictionary d(dictionaryFileNameT9);
		if (argc >= 2)
		{
			/*
			addToDictionaryFileNameT9 = argv[1];
			d.AppendDictionary(addToDictionaryFileNameT9);
			d.SaveDictionary();
			*/
			d.AddWord(StCat::Word("pnu" ,1));
			d.AddWord(StCat::Word("pot" ,3));
			d.AddWord(StCat::Word("pov" ,1));
			d.AddWord(StCat::Word("qnu" ,1));
			d.AddWord(StCat::Word("qot" ,1));
			d.AddWord(StCat::Word("qov" ,2));
			d.AddWord(StCat::Word("rnu" ,1));
			d.AddWord(StCat::Word("rot" ,2));
			d.AddWord(StCat::Word("rov" ,2));
			d.AddWord(StCat::Word("snu" ,1));
			d.AddWord(StCat::Word("sot" ,1));
			d.AddWord(StCat::Word("sov" ,2));

			d.ShowDictionary();
		} else 
		{
			int size;
			std::string word;
			int n;
			std::cin >> size;
			for (int i = 0; i < size; ++i)
			{
				std::cin >> word >> n;
				d.AddWord(StCat::Word(word, n));
			}
		}
		std::string tmp;
		char sym[2];
		sym[1] = 0;
		for (unsigned char i = 0; i < PUNCTUATION_MARKS.size(); ++i)
		{
			sym[0] = PUNCTUATION_MARKS[i];
			d.AddWord(StCat::Word(sym, 10000 - 2000*i));
		}
		d.Index();

//		d.ShowDictionary();
		std::cout.flush();
		std::cin.getline(commandLine, maxCommandSize);
		std::cin.getline(commandLine, maxCommandSize);
		commandLineString = commandLine;
		int pos = 0;
		while (pos < commandLineString.size())
		{
			tmp = "";
			smsMsg = "";
			for (int k = pos; k < commandLineString.size(); ++k, ++pos)
			{
				if (SPACE == commandLineString[k])
					break;
				tmp.push_back(commandLineString[k]);
			}

			for (int k = pos; k < commandLineString.size(); ++k, ++pos)
			{
				if (SPACE != commandLineString[k])
					break;
				smsMsg.push_back(SPACE);
					
			}
//			if (EXIT == tmp)
//				break;

			std::string command;
			command = "";
			unsigned int starsAfterNumber, starsAfter1 = 0, i, j = 0;
			starsAfterNumber = 0;
			starsAfter1 = 0;

			for (i = 0; i < tmp.size(); ++i)
			{
				if (std::string::npos == BUTTONS.find(tmp[i]))
					break;

				command.push_back(tmp[i]);
//				++pos;
			}
			if (!command.empty())
			{
				d.GetWord(command);
				for (j = i; j < tmp.size(); ++j)
				{
					if (STAR != tmp[j])
					{
						break;
					}
					d.GetNextWord();
				}
			}
			if (!command.empty())
			{
				sms += d.GetCurrentWord();
				d.IncreaseRating();
			}

			i = tmp.size() - j;
			if (i > 0)
			{
				int n = j + 1;
				starsAfter1 = 1;
				for (; n < tmp.size(); ++n)
				{
					if (PUNCUATION_BUTTON == tmp[n])
					{
						sms.push_back(PUNCTUATION_MARKS[starsAfter1 % PUNCTUATION_MARKS.size()]);
						starsAfter1 = 1;

						continue;
					}
					if (STAR == tmp[n])
						++starsAfter1;
				}
				
				sms.push_back(PUNCTUATION_MARKS[starsAfter1 % PUNCTUATION_MARKS.size()]);
//				i %= PUNCTUATION_MARKS.size();
//				sms.push_back(PUNCTUATION_MARKS[i]);
			}
			sms += smsMsg;
		}

			/*
			if (EXIT == tmp)
			{
				sms += d.GetCurrentWord();
				break;
			}

			if (SPACE == tmp[0]) 
			{
				smsMsg += " ";
				sms += d.GetCurrentWord() + " ";
				d.IncreaseRating();

				continue;
			}
			if (STAR == tmp[0])
			{
				smsMsg += "*";
				std::cout << CURSOR_WAITING << d.GetNextWord() << std::endl;

				continue;
			}
			if (PUNCUATION_BUTTON == tmp[0])
			{
				sms += d.GetCurrentWord();
				d.IncreaseRating();
			}

			if (std::string::npos != BUTTONS.find(tmp[0]))
			{
				smsMsg += tmp;
				std::cout << CURSOR_WAITING << d.GetWord(tmp) << std::endl;

				continue;
			}
			*/
//		d.ShowDictionary();
//		d.SaveDictionary(smsMsg, sms);
//		std::cout << CURSOR_WAITING << smsMsg << std::endl;
		std::cout << sms;
//		std::cin >> tmp;
//		_getch();

	} catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}

// class Word definition

namespace StCat
{
	const std::string BUTTON1 = ".,?";
	const std::string BUTTON2 = "abc";
	const std::string BUTTON3 = "def";
	const std::string BUTTON4 = "ghi";
	const std::string BUTTON5 = "jkl";
	const std::string BUTTON6 = "mno";
	const std::string BUTTON7 = "pqrs";
	const std::string BUTTON8 = "tuv";
	const std::string BUTTON9 = "wxyz";
	const std::string BUTTONSPACE = " ";
	bool Word::wordPriority_ = true;
	bool Word::ignoreRating_ = false;
	
	
	bool operator < (const Word& lhs, const Word& rhs)
	{
		
		if (lhs.GetRating() < 0 || rhs.GetRating() < 0 || Word::IsRatingIgnored())
			return lhs.GetWord() < rhs.GetWord();

		if (lhs.GetRating() == rhs.GetRating())
			return lhs.GetWord() < rhs.GetWord();

		return lhs.GetWord() < rhs.GetWord();

//		return lhs.LessThan(rhs);
	}
	
	void Word::IgnoreRating(bool ignoreIt)
	{
         ignoreRating_ = ignoreIt;
    }
    
    bool Word::IsRatingIgnored()
    {
         return ignoreRating_;
    }
	
	Word::Word(const std::string &word, int rating): word_(word), rating_(rating)
	{
		MakeKey();
	}

	const std::string& Word::GetWord() const
	{
		return word_;
	}

	int Word::GetRating() const
	{
		return rating_;
	}

	void Word::SetWordPriority()
	{
		wordPriority_ = true;
	}

	void Word::SetRatingPriority()
	{
		wordPriority_ = false;
	}

	bool Word::LessThan(const Word &rhs)
	{
		if (wordPriority_)
		{
			if (rating_ < 0 || rhs.rating_ < 0)
				return word_ < rhs.word_;

			if (rating_ == rhs.rating_)
				return word_ < rhs.word_;

			return rating_ < rhs.rating_;
		}

		return rating_ < rhs.rating_;
	}

	bool Word::operator ==(const Word& rhs) const
	{
		return word_ == rhs.word_;
	}

	const std::string& Word::GetKey() const
	{
		return key_;
	}

	void Word::MakeKey()
	{
		char symbol;
		key_ = "";
		for (unsigned char i = 0; i < word_.size(); ++i)
		{
			symbol = word_[i];
			if (std::string::npos != BUTTON1.find(symbol))
			{
				key_ += "1";
				continue;
			}
			if (std::string::npos != BUTTON2.find(symbol))
			{
				key_ += "2";
				continue;
			}
			if (std::string::npos != BUTTON3.find(symbol))
			{
				key_ += "3";
				continue;
			}
			if (std::string::npos != BUTTON4.find(symbol))
			{
				key_ += "4";
				continue;
			}
			if (std::string::npos != BUTTON5.find(symbol))
			{
				key_ += "5";
				continue;
			}
			if (std::string::npos != BUTTON6.find(symbol))
			{
				key_ += "6";
				continue;
			}
			if (std::string::npos != BUTTON7.find(symbol))
			{
				key_ += "7";
				continue;
			}
			if (std::string::npos != BUTTON8.find(symbol))
			{
				key_ += "8";
				continue;
			}
			if (std::string::npos != BUTTON9.find(symbol))
			{
				key_ += "9";
				continue;
			}
		}
	}

	void Word::IncreaseRating()
	{
		++rating_;
	}
}


//class MapException definition

namespace StCat
{
    MapException::~MapException() throw()
    {
    }                        
	MapException::MapException(const std::string& errExplanation)
	{
		what_ = errExplanation;
	}

	const char* MapException::what() const throw()
	{
		return what_.c_str();
	}
}


//class Dictionary definition

namespace StCat
{
	Dictionary::Dictionary(const std::string& dic)
	{
//		CheckExistance(dic);
//		Initialize();
	}

	void Dictionary::NewDictionary(const std::string& dic)
	{
		CheckExistance(dic);
		wordSet_.clear();
		Initialize();
	}

	void Dictionary::CheckExistance(const std::string& fileName)
	{
		if (fileName.empty())
			throw MapException("dic: empty file name");
		dictionaryFileName_ = fileName;

		std::ifstream ifile(fileName.c_str());
		if (ifile)
			return;

		std::ofstream file(fileName.c_str());
		if (!file)
			throw MapException("Dic: some kind of error with opening dictionary file");	
		file << 0;
	}

	void Dictionary::Initialize()
	{
		std::ifstream file(dictionaryFileName_.c_str());
		if (!file)
			throw MapException("Dic: some kind of error with opening dictionary file");	
		int dictionarySize;
		file >> dictionarySize;
		if (!dictionarySize)
			return;
		for (int i = 0; i < dictionarySize; ++i)
		{
			int rating;
			std::string word;
			file >> word >> rating;
			AddWord(Word(word, rating));
		}
	}

	void Dictionary::AddWord(const Word& word)
	{
		if (wordSet_.count(word))
			wordSet_.erase(word);

		wordSet_.insert(word);
	}

	void Dictionary::ShowDictionary() const
	{
		for (WordSetConstIterator_t pos = wordSet_.begin(); pos != wordSet_.end(); ++pos)
		{
			if (std::string::npos != PUNCTUATION_MARKS.find(pos->GetWord()))
			{
				continue;
			}
			std::cout << pos->GetWord() << "\t" << pos->GetRating() << std::endl;
		}
	}

	void Dictionary::AppendDictionary(const std::string& newDic)
	{
		std::ifstream file(newDic.c_str());
		if (!file)
			throw MapException("Dic: can't find file to append");
		int dictionarySize;
		file >> dictionarySize;
		if (!dictionarySize)
			return;
		for (int i = 0; i < dictionarySize; ++i)
		{
			int rating;
			std::string word;
			file >> word >> rating;
			AddWord(Word(word, rating));
		}
		SaveDictionary();
	}

	void Dictionary::SaveDictionary(const std::string& smsMsg, const std::string& sms)
	{
		std::ofstream file(dictionaryFileName_.c_str(), std::ios::out | std::ios::trunc);
		if (!file)
			throw MapException("Dic: some kind of error with opening dictionary file");	
		
		bool ratingIgnoredOld = Word::IsRatingIgnored();
		Word::IgnoreRating();
		WordSet_t wordSet = wordSet_;
		int dictionarySize = wordSet.size();
		file << dictionarySize - PUNCTUATION_MARKS.size() << std::endl;
		for (WordSetIterator_t pos = wordSet.begin(); pos != wordSet.end(); ++pos)
		{
			if (std::string::npos != PUNCTUATION_MARKS.find(pos->GetWord()))
			{
				continue;
			}
			file << pos->GetWord() << " " << pos->GetRating() << std::endl;
		}
		Word::IgnoreRating(ratingIgnoredOld);
		
		if (sms.empty())
			return;
		file << smsMsg << std::endl << sms << std::endl;
	}

	void Dictionary::Index()
	{
		indexedMap_.clear();
		currentWord_ = "";
		currentKey_ = "";
		for (WordSetIterator_t pos = wordSet_.begin(); pos != wordSet_.end(); ++pos)
		{
			indexedMap_.insert(make_pair(pos->GetKey(), *pos));
		}
	}

	const std::string& Dictionary::GetCurrentWord() const
	{
		return currentWord_;
	}

	void Dictionary::CreateRoundedVector()
	{
		roundedVector_.clear();
		IntIteratorSet_t posRanks = ratingsSet_.begin();
		while (posRanks != ratingsSet_.end())
		{
			int maxRank = *posRanks;
			for (StringWordIteratorMap_t pos = indexedMap_.lower_bound(currentKey_); pos != indexedMap_.upper_bound(currentKey_); ++pos)
			{
				if (pos->second.GetRating() == maxRank)
					roundedVector_.push_back(Word(pos->second.GetWord(), maxRank));
			}
			++posRanks;
		}
		posInRoundedVector_ = 0;
		for (WordVector_t::iterator i = roundedVector_.begin(); i != roundedVector_.end(); ++i, ++posInRoundedVector_)
		{
			if (i->GetWord() == currentWord_)
				break;
		}			
	}

	const std::string& Dictionary::GetWord(const std::string& key)
	{
		if (indexedMap_.find(key) == indexedMap_.end())
		{
			return currentWord_ = "Not found";
		}

		int maxRank = 0;
		ratingsSet_.clear();
		for (StringWordIteratorMap_t pos = indexedMap_.lower_bound(key); pos != indexedMap_.upper_bound(key); ++pos)
		{
			ratingsSet_.insert(pos->second.GetRating());
			if (pos->second.GetRating() > maxRank)
			{
				maxRank = pos->second.GetRating();
				currentWord_ = pos->second.GetWord();
				currentKeyIterator_ = pos;
			}
		}
		currentKey_ = key;
		CreateRoundedVector();

		return currentWord_;
	}

	void Dictionary::IncreaseRating()
	{
		if (currentWord_.empty())
			return;
		WordSetIterator_t pos = wordSet_.find(Word(currentWord_, -1));
		Word word(Word(pos->GetWord(), pos->GetRating()));
		wordSet_.erase(pos);
		word.IncreaseRating();
		wordSet_.insert(word);
//		pos->IncreaseRating();

		currentKeyIterator_->second.IncreaseRating();
		Word tmpWord(currentKeyIterator_->second);
		StringWordIteratorMap_t prevPos = currentKeyIterator_;
		--prevPos;
		for (StringWordIteratorMap_t pos = currentKeyIterator_; pos != indexedMap_.lower_bound(currentKey_); --pos, --prevPos)
		{
			pos->second = (prevPos)->second;
		}
		indexedMap_.lower_bound(currentKey_)->second = tmpWord;

		currentWord_ = "";
		currentKey_ = "";
	}

	const std::string& Dictionary::GetNextWord()
	{
		if (currentKey_.empty())
			return currentWord_ = "";

		if (1 == indexedMap_.count(currentKey_))
			return currentWord_;

		if (++posInRoundedVector_ > roundedVector_.size())
			posInRoundedVector_ = 0;
		Word nextWord(roundedVector_[posInRoundedVector_]);
		currentWord_ = nextWord.GetWord();

		for (StringWordIteratorMap_t pos = indexedMap_.lower_bound(currentKey_); pos != indexedMap_.upper_bound(currentKey_); ++pos)
		{
			if (pos->second == nextWord)
			{
				currentKeyIterator_ = pos;

				break;
			}
		}
/*
		int maxRank = 0;
		

//		++tmp;
		++currentKeyIterator_;
		if (currentKeyIterator_ == indexedMap_.upper_bound(currentKey_))
			currentKeyIterator_ = indexedMap_.lower_bound(currentKey_);
		currentWord_ = currentKeyIterator_->second.GetWord();


*/
		return currentWord_;
	}
}
