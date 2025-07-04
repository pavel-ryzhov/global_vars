#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

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
	Array<T>( const Array& other );
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

template<class T> void Array<T>::rotate(const int &from, const int &to)
{
	T *buffer= new T[from - to];
	T elementToCopy = elements_[from];

	if(memoryCopy_)
	{
		memcpy( buffer, elements_ + from + 1, sizeof(T) * (to - from));
		memcpy( elements_ + from, buffer, sizeof(T) * (to - from));
	}
	else
	{
		for(int i = from; i < to - 1; ++i)
		{
			elements_[i] = elements_[i + 1];
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

class Digits
{
public:
	unsigned int digits1_;
	unsigned int digits2_;
	int position_;
	int lenght_;
	int rank_;

	Digits()
	{
	}
	~Digits(){};
};

class Dictionary{
private:
	Array<Digits> *hashes_;
	Array<Digits *> *hashesPtr_;

	static int hashFromDigits(const char *digits,const int &length);
	static void getDigitsAndHash(const char *str,const int &strLen,unsigned int &digits1,unsigned int &digits2, int &hash);
public:
	std::string fileString_;
	int begin_;
	int fileSize_;

	void readFile(FILE *file);
	void readScreen();

	Dictionary()
	{
		hashes_ = new Array<Digits>[MAXHASH + 1];
		hashesPtr_ = new Array<Digits *>[MAXHASH + 1];
		begin_ = 0;
		fileString_ = "";
	}
	~Dictionary()
	{
		if (hashes_)
		{
			delete [] hashes_;
		}
		if (hashesPtr_)
		{
			delete [] hashesPtr_;
		}

	}

	int addWord(const int &index);
	int readTask(FILE *file);
};

void Dictionary::readScreen()
{
	char buffer[100000];
	fileString_ = "";
	begin_ = 0;

	std::cin >> buffer;
	fileString_ += buffer;
	fileString_ += 10;

	int numStr = atoi(fileString_.c_str());
	for(int i = 0; i < numStr; ++i)
	{
		std::cin >> buffer;
		fileString_ += buffer;
		fileString_ += ' ';

		std::cin >> buffer;
		fileString_ += buffer;
		fileString_ += 10;
	}
	std::cin >> buffer;
	fileString_ += buffer;
	std::cin.getline(buffer, 1000000, '\n');
	fileString_ += buffer;
	fileString_ += 33;

	fileSize_ = fileString_.length();
	return;
}

void Dictionary::readFile(FILE *file)
{
	fseek(file, 0, SEEK_END);
	int fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	char *buffer = new char[fileSize];

	begin_ = 0;


	fileSize_ = fread(buffer, sizeof(char), fileSize, file);

	std::cout << fileSize_ << "\n";


	fileString_ = buffer;
	fileString_[fileSize_] = 33;

	if (buffer)
	{
		delete [] buffer;
	}
	return;
}



void Dictionary::getDigitsAndHash(const char *str,const int &strLen,unsigned int &digits1,unsigned int &digits2, int &hash)
{
	int hashes[]={S2,S2,S2,S3,S3,S3,S4,S4,S4,S5,S5,S5,S6,S6,S6,S7,S7,S7,S7,S8,S8,S8,S9,S9,S9,S9};
	hash = SPACE * (MWL - strLen);
	int d []= {1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,6,7,7,7,8,8,8,8};
	unsigned int numerator1 [] = {387420489,43046721,4782969,531441,59049,6561,729,81,9,1,0,0,0,0,0,0,0,0,0,0};
	unsigned int numerator2 [] = {0,0,0,0,0,0,0,0,0,0,387420489,43046721,4782969,531441,59049,6561,729,81,9,1};

	digits1 = 0;
	digits2 = 0;
	for(int i = 0; i < strLen; ++i)
	{
		hash += hashes[str[i]-'a'];
		digits1 += numerator1[i] * d[str[i]-'a'];
		digits2 += numerator2[i] * d[str[i]-'a'];
	}

	return;
}
int Dictionary::addWord(const int &index)
{
	Digits d;
	while(fileString_[begin_] == ' ')
	{
		begin_ ++;
	}
	d.position_ = begin_;
	d.lenght_ = fileString_.find_first_of(' ', begin_) - begin_;
	begin_ = fileString_.find_first_of(' ',begin_) + 1;
	int hash;
	getDigitsAndHash(&fileString_[d.position_], d.lenght_, d.digits1_, d.digits2_, hash);

	while(fileString_[begin_] == ' ')
	{
		begin_++;
	}
	d.rank_ = atoi(fileString_.c_str() + begin_);
	begin_ = fileString_.find_first_of(10, begin_) + 1;

	hashes_[hash].push(d);
	Digits *dPtr = &hashes_[hash][hashes_[hash].size() - 1];
	hashesPtr_[hash].push(dPtr);
	return 0;
}

struct DigitsAndIndex
{
	Digits *d;
	int index;
};


int Dictionary::readTask(FILE *file)
{
	DigitsAndIndex di[MAX_WORD_ON_DIGITS];

	int diCount = 0;

	int space = 0;
	int flag = 0;
	int hash = 0;
	int star = 0;
	int one = 0;
	int digitsLength = 0;
	unsigned int digits1 = 0;
	unsigned int digits2 = 0;

	int hashes[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,S2,S3,S4,S5,S6,S7,S8,S9};
	int d []= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8};
	int isds []= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1};
	unsigned int numerator1 [] = {387420489,43046721,4782969,531441,59049,6561,729,81,9,1,0,0,0,0,0,0,0,0,0,0};
	unsigned int numerator2 [] = {0,0,0,0,0,0,0,0,0,0,387420489,43046721,4782969,531441,59049,6561,729,81,9,1};
	char spaces [] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	char stars [] = {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	char ones [] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0};
	char eofs [] = {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	char punct[]={'.',',','?'};

	while(!flag)
	{
		space += spaces[fileString_[begin_] - ' '];
		star += stars[fileString_[begin_] - ' '];

		one += ones[fileString_[begin_] - ' '];
		flag = space + one + eofs[fileString_[begin_] - ' '];

		hash += hashes[fileString_[begin_] - ' '];

		digits1 += numerator1[digitsLength] * d[fileString_[begin_] - ' '];
		digits2 += numerator2[digitsLength] * d[fileString_[begin_] - ' '];

		digitsLength += isds[fileString_[begin_] - ' '] ;
		begin_++;
	}
	hash += SPACE * (MWL - digitsLength);

	if(digits1)
	{
		for(int i = 0; i < hashesPtr_[hash].size(); ++i)
		{
			if(hashesPtr_[hash][i]->digits1_ == digits1 && hashesPtr_[hash][i]->digits2_ == digits2)
			{
				di[diCount].d = hashesPtr_[hash][i];
				di[diCount].index = i;
				diCount++;
			}
		}

		if(diCount)
		{
			DigitsAndIndex diBuf;
			int rank = star % diCount;
//			if(rank <= diCount/2)
			{
				for (int i = 0; i < rank + 1; ++i)
				{
					for (int n = diCount - 1; n > i ; --n)
					{
						if(di[i].d->rank_ < di[n].d->rank_)
						{
							diBuf = di[i];
							di[i] = di[n];
							di[n] = diBuf;
						}
					}
				}
			}
/*			else
			{
				rank = diCount - rank - 1;
				for (int i = 0; i < rank + 1; ++i)
				{
					for (int n = i + 1; n < diCount; ++n)
					{
						if(di[i].d->rank_ >= di[n].d->rank_)
						{
							diBuf = di[i];
							di[i] = di[n];
							di[n] = diBuf;
						}
					}
				}

			}*/
//			fwrite(&fileString_[di[rank].d->position_], sizeof(char),di[rank].d->lenght_, file);
			std::string wordOut;
			wordOut =  fileString_.substr(di[rank].d->position_ , di[rank].d->lenght_);
			std::cout << wordOut.c_str();

			hashesPtr_[hash][di[rank].index]->rank_ ++;
			hashesPtr_[hash].moveToFirstPlace(di[rank].index);
		}
	}
	if (space)
	{
		char s = ' ';
		//		fwrite(&s, sizeof(char), 1, file);
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
			space += spaces[fileString_[begin_] - ' '];
			star += stars[fileString_[begin_] - ' '];
			one += ones[fileString_[begin_] - ' '];
			isd += isds[fileString_[begin_] - ' '];
			flag = space + one +  isd + eofs[fileString_[begin_] - ' '];

			begin_++;
		}
		begin_ -= one + isd + space;
		//		fwrite(&punct[star % 3], sizeof(char), 1, file);
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
	dict.readScreen();
	//	char *buffer = new char [12];
	FILE *file = NULL;
	//	bool isOpen = false;

	//	while (!isOpen)
	//	{
	//		std::cout << "Enter input file name: ";
	//		std::cin >> buffer ;
	//		std::string fileName = buffer;
	//		isOpen = file = fopen(fileName.c_str(), "r");
	//	}
	//////////////////////////////////////

	//	dict.readFile(file);
	//	fclose(file);

	int quantity = readNumber(dict.fileString_, dict.begin_);

	for (int i = 0; i < quantity; ++i)
	{
		dict.addWord(i);
	}

	//	isOpen = false;
	//	while (!isOpen)
	//	{
	//		std::cout << "Enter output file name: ";
	//		std::cin >> buffer ;
	//		std::string fileName = buffer;
	//		isOpen = file = fopen(fileName.c_str(), "w");
	//	}
	while(dict.begin_ < dict.fileSize_)
	{
		dict.readTask(file);
	}
	//	fclose(file);
	//	if (buffer)
	//	{
	//		delete [] buffer;
	//	}
	return 0;
}


int T9::readNumber(const std::string &str, int &begin)
{
	int number = 0;

	while(str[begin] == ' ')
	{
		begin++;
	}
	number = atoi(str.c_str() + begin);

	begin = str.find_first_of(10, begin) + 1;
	return number;
}


int main()
{
	T9 t9;
	t9.run();


	return 0;
}
