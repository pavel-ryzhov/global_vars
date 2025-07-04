#include <stdio.h>
#include <vector>
#include <string>
#include <string.h>
#include <map>

long long getHashFromWord(const char* str);
long long getHashFromNumber(const char* str);


class WordGroup
{
	public:
		WordGroup();
		std::string* getWord(std::string* tempString,short s);
		bool setHash(long long n);
		void addWord(char* s, short f);
		long long getHash() { return hash; };
	private:
		std::multimap<int,std::string> words;
		long long hash;
		unsigned short size;
};

WordGroup::WordGroup()
{
	hash = -1;
	size = 0;
};

bool WordGroup::setHash(long long n)
{
	if (hash == -1)
	{
		hash = n;
		return true;
	}
	else
		return false;
};

long long getHashFromWord(const char* str)
{
	//Let's take numbers instead of letters
	char tempStringNumber[21];
	tempStringNumber[strlen(str)] = '\0';
	for (int i = strlen(str) - 1; i >= 0; i--)
	{
		switch (str[i])
		{
		case 'a':
		case 'b':
		case 'c':
			tempStringNumber[i] = '2';
			break;
		case 'd':
		case 'e':
		case 'f':
			tempStringNumber[i] = '3';
			break;
		case 'g':
		case 'h':
		case 'i':
			tempStringNumber[i] = '4';
			break;
		case 'j':
		case 'k':
		case 'l':
			tempStringNumber[i] = '5';
			break;
		case 'm':
		case 'n':
		case 'o':
			tempStringNumber[i] = '6';
			break;
		case 'p':
		case 'q':
		case 'r':
		case 's':
			tempStringNumber[i] = '7';
			break;
		case 't':
		case 'u':
		case 'v':
			tempStringNumber[i] = '8';
			break;
		case 'w':
		case 'x':
		case 'y':
		case 'z':
			tempStringNumber[i] = '9';
			break;
		}
	}
	return getHashFromNumber(tempStringNumber);
};

long long getHashFromNumber(const char* str)
{
	//Some kind of hash function
	long long number = 0;
	long long length = strlen(str);
	long long delimiter = 8;
	//Limit words of one lenght from others
	for (int l = 0; l < length; l++) delimiter *= 8;
	delimiter *= 2;
	for (int k = 0; k < 20 - length; k++)
	{
		number += delimiter;
		delimiter *= 8;
	}
	//Convert from 2..9 numbers to octal representation
	long long position = 1;
	for (int i = strlen(str) - 1; i >= 0; i--)
	{
		long long character;
		switch (str[i])
		{
		case '2':
			character = 0;
			break;
		case '3':
			character = 1;
			break;
		case '4':
			character = 2;
			break;
		case '5':
			character = 3;
			break;
		case '6':
			character = 4;
			break;
		case '7':
			character = 5;
			break;
		case '8':
			character = 6;
			break;
		case '9':
			character = 7;
			break;
		}
		number += character * position;
		position *= 8;
	}
	return number;
};

std::string* WordGroup::getWord(std::string* tempString, short s)
{

	if (s >= words.size())
		s = s%words.size();
	if (size == 0)
		return tempString;
	std::multimap<int, std::string >::iterator it = words.end();
	for (int i = 0; i <= s; i++) it--;
	int	tempFrequency = (*it).first + 1;
	*tempString = (*it).second;
	words.erase(it);
	std::multimap<int, std::string >::iterator it2 = words.upper_bound(tempFrequency);
	words.insert(it2,std::make_pair<int,std::string> (tempFrequency,*tempString));
	return tempString;
};

void WordGroup::addWord(char* s, short f)
{
	//Add word to list
	std::string tempString = s;
	words.insert(words.lower_bound(f),std::make_pair<int, std::string> (f,tempString));
	size = words.size();
}


int main()
{
	std::vector<std::string> words;
	std::vector<short> frequencies;
	int N;
	std::map<long long,WordGroup> Dictionary;
	//Read dictionary from stdin
	scanf("%d\n",&N);
	for (int i = 0; i < N; i++)
	{
		char word[21] = "";
		int frequency = 0;
		long long hash;
		scanf("%s %d\n",word,&frequency);
		hash = getHashFromWord(word);
		Dictionary[hash].addWord(word,frequency);
		Dictionary[hash].setHash(hash);
	}
	char line[100001];
	gets(line);
	//Let's parse long line
	int length = strlen(line);
	std::string output;
	output.reserve(length);
	char word[21];
	short iteratorWord = 0;
	short iteratorStar = 0;
	char punctuation[3] = {'.',',','?'};
	bool needPunctuation = false;
	std::string tempString = "";
	for (int j = 0; j < length; j++)
	{
		switch (line[j])
		{
		case '*':
			iteratorStar++;
			break;
		case ' ':
			if (needPunctuation == true)
			{
				iteratorStar = iteratorStar%3;
				output += punctuation[iteratorStar];
				needPunctuation = false;
			}
			if (iteratorWord != 0)
                        {
                                word[iteratorWord] = '\0';
                                Dictionary[getHashFromNumber(word)].getWord(&tempString,iteratorStar);
                                output += tempString;
                        }
			output += ' ';
			iteratorWord = 0;
			iteratorStar = 0;
			break;
		case '1':
			if (needPunctuation == true)
			{
				iteratorStar = iteratorStar%3;
				output += punctuation[iteratorStar];
				iteratorStar = 0;
			}
			needPunctuation = true;
			if (iteratorWord != 0)
			{
				word[iteratorWord] = '\0';
				Dictionary[getHashFromNumber(word)].getWord(&tempString,iteratorStar);
				output += tempString;
			}
			iteratorWord = 0;
			iteratorStar = 0;
			break;
		default:
			word[iteratorWord] = line[j];
			iteratorWord++;
		}
		if (j == length - 1) 
		{
			if (needPunctuation == true)
			{
				iteratorStar = iteratorStar%3;
				output += punctuation[iteratorStar];
			}
			if (iteratorWord != 0)
			{
				word[iteratorWord] = '\0';
				Dictionary[getHashFromNumber(word)].getWord(&tempString,iteratorStar);
				output += tempString;
			}
		}
	}
	puts(output.data());
	return 0;
}

