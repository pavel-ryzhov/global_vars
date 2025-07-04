#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <map>


#define MINMA 256
#define MWL 20

#define MAX_WORD_ON_DIGITS 200

#define MAX(a,b) a>=b? a : b
#define MIN(a,b) a<=b? a : b


template <class T> class Array
{
private:
	T* elements_;

	int limit_;
	int count_;
	bool memoryCopy_;

	void push_part();
public:

	Array<T>();
	Array<T>(const int &s);
	Array<T>( const Array &other );
	~Array();

	int size();
	void push(const T t);
	void push();
	void setMemoryCopy(const bool memoryCopy);
	void rotate(const int &from, const int &to);
	void insert(const int &index, const T t);
	void moveToFirstPlace(const int &index);


	const T& pop();

	const Array<T>& operator = (const Array<T>& other);
	const T& operator [] (int i) const;
	T& operator [] (int i);

	void out();
};


template<class T> Array<T>::Array():
elements_( NULL ),
limit_ (MINMA),
count_ (0),
memoryCopy_ (true)
{
	if ( limit_ > 0 )
	{
		elements_ = new T[limit_];
	}
}
template<class T> Array<T>::Array( const int & s):
limit_ (s),
count_ (s),
memoryCopy_ (true)
{
	if (limit_ > 0)
	{
		elements_ = new T[limit_];
	}
}

template<class T> Array<T>::Array( const Array& other ):
limit_ (other.limit_),
count_ (other.count_),
memoryCopy_ (other.memoryCopy_)
{
	if (limit_ > 0)
	{
		elements_ = new T[other.limit_];

		if (count_ > 0)
		{

			if (memoryCopy_)
			{
				memcpy(elements_, other.elements_, sizeof(T)*count_);
			}
			else
			{
				for(int i = 0; i < count_; ++i)
				{
					elements_[i] = other.elements_[i];
				}
			}
		}
	}
}

template<class T> Array<T>::~Array()
{
	if (elements_)
		delete [] elements_;
}

template<class T> int Array<T>::size()
{
	return count_;
}

template<class T> void Array<T>::push(const T t)
{
	push_part();
	elements_[count_ - 1] = t;
	return;
}
template<class T> void Array<T>::setMemoryCopy(const bool memoryCopy)
{
	memoryCopy_ = memoryCopy;
	return;
}
template<class T> void Array<T>::push()
{
	push_part();
	return;
}

template<class T> void Array<T>::push_part()
{
	if ( limit_ == 0 )
	{
		limit_ = 512;
		elements_ = new T[limit_];
	}
	else if ( count_ >= limit_ )
	{
		T* oldElements = elements_;

		limit_ = 2 * limit_;

		elements_ = new T[limit_];


		if (memoryCopy_)
		{
			memcpy( elements_, oldElements, sizeof(T) * count_ );
		}
		else
		{
			for(int i = 0; i < count_; ++i)
			{
				elements_[i] = oldElements[i];
			}
		}
		delete [] oldElements;
	}

	++ count_;
	return;
}

template<class T> void Array<T>::rotate(const int &from, const int &to) // from > to
{
	T *buffer= new T[from - to];
	T elementToCopy = elements_[from];

	if(memoryCopy_)
	{
		memcpy( buffer, elements_ + to, sizeof(T) * (from - to));
		memcpy( elements_ + to + 1, buffer, sizeof(T) * (from - to));
	}
	else
	{
		for(int i = to; i < from - 1; ++i)
		{
			elements_[i + 1] = elements_[i];
		}
	}

	delete [] buffer;

	elements_[to] = elementToCopy;
	return;
}

template<class T> void Array<T>::insert(const int &index, const T t)
{
	this->push();

	T *buffer= new T[count_ - index - 1];

	if(memoryCopy_)
	{
		memcpy( buffer, elements_ + index, sizeof(T) * (count_ - index));
		memcpy( elements_ + index + 1, buffer, sizeof(T) * (count_ - index));
	}
	else
	{
		for(int i = index; i < count_ - 1; ++i)
		{
			elements_[i + 1] = elements_[i];
		}
	}

	delete [] buffer;
	elements_[index] = t;
	return;
}

template<class T> void Array<T>::moveToFirstPlace(const int &index)
{
	T *buffer = new T[index];
	T t = elements_[index];

	if(memoryCopy_)
	{
		memcpy( buffer, elements_, sizeof(T) * (index));
		memcpy( elements_ + 1, buffer, sizeof(T) * (index));
	}
	else
	{
		for(int i = 0; i < index; ++i)
		{
			elements_[i + 1] = elements_[i];
		}
	}

	delete [] buffer;
	elements_[0] = t;
	return;
}



template<class T> const T& Array<T>::pop()
{
	-- count_;
	return elements_[count_];
}

template<class T> void Array<T>::out()
{
	int i;

	for(i = 0; i < count_; ++i)
	{
		elements_[i].out();
	}
	return;
}

template<class T> const Array<T>& Array<T>::operator = (const Array<T>& other)
{
	limit_ = other.limit_;
	count_ = other.count_;
	memoryCopy_ = other.memoryCopy_;

	if (elements_)
	{
		delete [] elements_;
	}

	elements_ = new T[limit_];

	if (count_ > 0)
	{
		if (memoryCopy_)
		{
			memcpy( elements_, other.elements_, sizeof(T) * count_);
		}
		else
		{
			for(int i = 0; i < count_; ++i)
			{
				elements_[i] = other.elements_[i];
			}
		}
	}

	return *this;
}

template<class T> const T& Array<T>::operator [] (int i) const
{
	return elements_[i];
}


template<class T> T& Array<T>::operator [] (int i)
{
	return elements_[i];
}

/////////////////////////////////////

/////////////////////////////////////

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
};

class WordKey
{
public:
	int digits1_;
	int digits2_;

	WordKey(const unsigned int d1, const unsigned int d2);
	WordKey(const std::string &str);
	~WordKey(){}

	void getWordKey(const std::string word);
//	bool operator <(const WordKey wk1, const WordKey wk2);
};

WordKey::WordKey(const unsigned int d1, const unsigned int d2):
	digits1_ (d1),
	digits2_ (d2)
{}

WordKey::WordKey(const std::string &str)
{
	int d []= {1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,6,7,7,7,8,8,8,8};
	unsigned int numerator1 [] = {387420489,43046721,4782969,531441,59049,6561,729,81,9,1,0,0,0,0,0,0,0,0,0,0};
	unsigned int numerator2 [] = {0,0,0,0,0,0,0,0,0,0,387420489,43046721,4782969,531441,59049,6561,729,81,9,1};
	digits1_ = 0;
	digits2_ = 0;


	for(int i = 0; i < str.length() ; ++i)
	{
		digits1_ += numerator1[i] * d[str[i]-'a'];
		digits2_ += numerator2[i] * d[str[i]-'a'];
	}
}
bool operator <(const WordKey wk1, const WordKey wk2)
{
	if (wk1.digits1_ < wk2.digits1_ && wk1.digits2_ <= wk2.digits2_)
		return true;
	else
		return false;
}

typedef std::map< WordKey, Array<Word *> > WordList;

class Dictionary{
public:
	Word *words_;
	WordList wordsList_;
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
	char buffer[MWL];
	std::cin >> buffer;

	words_[index].value_ = buffer;
	std::cin >> words_[index].rank_;

	WordKey wordKey(words_[index].value_);
	Word *w = &words_[index];

	wordsList_[wordKey].push(w);
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


int Dictionary::readTask()
{
	int diCount = 0;

	int space = 0;
	int flag = 0;
	int star = 0;
	int one = 0;
	int digitsLength = 0;
	unsigned int digits1 = 0;
	unsigned int digits2 = 0;

	int d []= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8};
	int isds []= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1};
	unsigned int numerator1 [] = {387420489,43046721,4782969,531441,59049,6561,729,81,9,1,0,0,0,0,0,0,0,0,0,0};
	unsigned int numerator2 [] = {0,0,0,0,0,0,0,0,0,0,387420489,43046721,4782969,531441,59049,6561,729,81,9,1};
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

		one += ones[taskString_[begin_] - ' '];
		flag = space + one + eofs[taskString_[begin_] - ' '];

		digits1 += numerator1[digitsLength] * d[taskString_[begin_] - ' '];
		digits2 += numerator2[digitsLength] * d[taskString_[begin_] - ' '];

		digitsLength += isds[taskString_[begin_] - ' '] ;
		begin_++;
	}

	if(digits1)
	{

		WordKey wKey(digits1, digits2);
		Array<Word *> *w= &wordsList_[wKey];
		Array<WordAndIndex> wi(w->size());
		for(int i = 0; i < w->size(); ++i)
		{
			wi[i].index_= i;
			wi[i].wordPtr_ = (*w)[i];
		}
		if(w->size())
		{
			int index = star % wi.size();
			{
				for (int i = 0; i < index + 1; ++i)
				{
					int nMax = -1;
					int rankMax = 0;
					for (int n = i ; n < wi.size() ; ++n)
					{
						if(rankMax < wi[n].wordPtr_->rank_)
						{
							rankMax = wi[n].wordPtr_->rank_;
							nMax = n;
						}
					}
					if(nMax != -1)
					{
						wi.rotate(nMax, i);
					}
				}
			}
			std::cout << wi[index].wordPtr_->value_.c_str();

			(*w)[wi[index].index_]->rank_ ++;
			(*w).moveToFirstPlace(wi[index].index_);
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
