#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <set>


#define MINMA 256
#define MWL 20
#define S2 1
#define S3 127
#define S4 251
#define S5 369
#define S6 631
#define S7 751
#define S8 877
#define S9 997
#define SPACE 499
#define MAXHASH S9*MWL

#define MINMA 256
#define RANK_STEP 100000

/////////////////////////////////////

/////////////////////////////////////
class WordKey
{
public:
	unsigned long long digits_;
	WordKey(const unsigned long long &d);
	WordKey();
	~WordKey(){}
};

WordKey::WordKey(const unsigned long long &d):
digits_ (d)
{}
WordKey::WordKey(){}
bool operator <(const WordKey wk1, const WordKey wk2)
{
	return wk1.digits_ < wk2.digits_;
}


class Word
{
public:
	std::string value_;
	int rank_;

	Word()
	{
		value_ = "";
		rank_ = 0;
	}
	~Word(){}
	void getHashAndKey(int &hash, WordKey &wk);
};

class WordPtr
{
public:
	Word *value_;
	int rank_;

	WordPtr(Word *wP)
	{
		value_ = wP;
		rank_ = wP->rank_ * RANK_STEP;
	};
	~WordPtr(){}
};

bool operator <(const WordPtr wP1, const WordPtr wP2)
{
	return wP1.rank_ > wP2.rank_;
}

void Word::getHashAndKey(int &hash, WordKey &wk)
{
	int hashes[]={S2,S2,S2,S3,S3,S3,S4,S4,S4,S5,S5,S5,S6,S6,S6,S7,S7,S7,S7,S8,S8,S8,S9,S9,S9,S9};
	hash = SPACE * (MWL - value_.length());
	int d []= {1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,6,7,7,7,8,8,8,8};
	unsigned long long numerator = 1;
	wk.digits_ = 0;

	for(int i = 0; i < value_.length() ; ++i)
	{
		hash += hashes[value_[i]-'a'];
		wk.digits_ += numerator * d[value_[i]-'a'];
		numerator *= 9;
	}
}


typedef std::map< WordKey, std::multiset<WordPtr> > WordList;

class Dictionary{
public:
	Word *words_;
	WordList hashes_[MAXHASH + 1];

	std::string taskString_;
	int begin_;
	int taskSize_;

	Dictionary()
	{
		words_ = NULL;
	}
	~Dictionary()
	{
		if (words_)
		{
			delete [] words_;
		}
	}

	int addWord(const int &index);
	int readTask();
	void readScreen();

};

void Dictionary::readScreen()
{
	char buffer[100000];
	begin_ = 0;

	std::cin >> buffer;
	taskString_ += buffer;
	std::cin.getline(buffer, 1000000, '\n');
	taskString_ += buffer;
	taskString_ += 33;

	taskSize_ = taskString_.length();
	return;
}


int Dictionary::addWord(const int &index)
{
	char buffer[20];
	std::cin >> buffer;
	int hash;

	words_[index].value_ = buffer;
	std::cin >> words_[index].rank_;

	WordKey wordKey(0);
	words_[index].getHashAndKey(hash, wordKey);
	WordPtr w(&words_[index]);

	hashes_[hash][wordKey].insert(w);

	return 0;
}
class WordAndIndex
{
public:
	Word *wordPtr_;
	int index_;

	WordAndIndex():
	wordPtr_ (NULL),
		index_ (0)
	{}
	~WordAndIndex(){}
};

int it = 0;
int Dictionary::readTask()
{
	int diCount = 0;
	int hash = 0;
	int space = 0;
	int flag = 0;
	int star = 0;
	int one = 0;
	int digitsLength = 0;
	unsigned long long digits = 0;
	int hashes[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,S2,S3,S4,S5,S6,S7,S8,S9};
	int d []= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8};
	int isds []= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1};
	unsigned long long numerator = 1;
	char spaces [] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	char stars [] = {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	char ones [] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0};
	char eofs [] = {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	char punct[]={'.',',','?'};
	std::string dig="";

	while(!flag)
	{
		space += spaces[taskString_[begin_] - ' '];
		star += stars[taskString_[begin_] - ' '];
		hash += hashes[taskString_[begin_] - ' '];

		one += ones[taskString_[begin_] - ' '];
		flag = space + one + eofs[taskString_[begin_] - ' '];

		digits += numerator * d[taskString_[begin_] - ' '];
		digitsLength += isds[taskString_[begin_] - ' '];
		numerator *= 1 + 8 * isds[taskString_[begin_] - ' '];
		begin_++;
	}
	hash += SPACE * (MWL - digitsLength);

	if(digits)
	{
		WordKey wk(digits);
		std::multiset<WordPtr> *w = &hashes_[hash][wk];
		if((*w).size() > 0)
		{
			it++;
			std::multiset<WordPtr>::iterator f = (*w).begin();
			for (int i = 0; i < star % (*w).size(); ++i)
				f++;
			std::cout << (*f).value_->value_.c_str();
			WordPtr e = (*f);
			e.value_->rank_++;
			e.rank_ = e.value_->rank_* RANK_STEP + it;

			(*w).erase(f);
			(*w).insert(e);
		}
	}
	if (space)
	{
		char s = ' ';
		std::cout << s;
	}
	if (one)
	{
		flag = 0;
		star = 0;
		space = 0;
		one = 0;
		int isd = 0;
		while(!flag)
		{
			space += spaces[taskString_[begin_] - ' '];
			star += stars[taskString_[begin_] - ' '];
			one += ones[taskString_[begin_] - ' '];
			isd += isds[taskString_[begin_] - ' '];
			flag = space + one +  isd + eofs[taskString_[begin_] - ' '];

			begin_++;
		}
		begin_ -= one + isd + space;
		std::cout << punct[star % 3];
	}
	return 0;
}

class T9{
private:
	int readNumber(const std::string &str, int &begin);
public:
	T9(){};
	~T9(){};

	int run();
};


int T9::run()
{
	Dictionary dict;

	int quantity;
	std::cin >> quantity;
	dict.words_ = new Word[quantity];

	for (int i = 0; i < quantity; ++i)
	{
		dict.addWord(i);
	}

	dict.readScreen();
	while(dict.begin_ < dict.taskSize_)
	{
		dict.readTask();
	}
	return 0;
}

int main()
{
	T9 t9;
	t9.run();

	return 0;
}
