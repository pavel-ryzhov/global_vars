#include <stdio.h>
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>

#define REST 29997

char* getNumberFromWord(char* str);
int getHashFromNumber(const char* str);


class WordGroup
{
	public:
		WordGroup(std::vector<std::string>* w,std::vector<unsigned short>* f);
		WordGroup();
		std::string* getWord(std::string* tempString,short s);
		void addWord(char* s, short f);
		char* getNumber(char* str);
		bool setNumber(char* str);
	private:
		std::vector<std::string> words;
		std::vector<unsigned short> frequencies;
		unsigned short size;
		char number[21];
};

WordGroup::WordGroup(std::vector<std::string>* w,std::vector<unsigned short>* f)
{
	words = *w;
	frequencies = *f;
	size = words.size();
};

WordGroup::WordGroup()
{
	strcpy(number,"");
	size = 0;
}

char* WordGroup::getNumber(char *str)
{
	strcpy(str,number);
	return str;
}

bool WordGroup::setNumber(char* str)
{
	if (strlen(number) == 0)
	{
		strcpy(number,str);
		return true;
	}
	else
		return false;
}

char* getNumberFromWord(char* str)
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
	strcpy(str,tempStringNumber);
	return str;
};

int getHashFromNumber(const char* str)
{
	//Some kind of hash function
	int number = 0;
	int length = strlen(str);
	int tempNumber = 0;
	char tempString[8];
	tempString[7] = '\0';
	int i;
	for (i = 0; i < length / 7; i++)
	{
		strncpy(tempString,str + i * 7, 7);
		tempNumber = atoi(tempString);
		number += tempNumber % REST;
	}
	strcpy(tempString,str + i * 7);
	tempString[strlen(tempString)] = '\0';
	tempNumber = atoi(tempString);
	number += tempNumber % REST;
	return number;
};

std::string* WordGroup::getWord(std::string* tempString, short s)
{

	if (s >= words.size())
		s = s%words.size();
	if (size == 0)
		return tempString;
	if (size == 1)
	{
		frequencies[0] += 1;
		*tempString = words[0];
		return tempString;
	}
	*tempString = words[s];
	unsigned short tempFrequency = frequencies[s] + 1;
	int tempSize = size - 1;
	words.erase(words.begin() + s);
	frequencies.erase(frequencies.begin() + s);
	//Readd word with new frequency
	for (int i = 0; i < tempSize; i++)
		{	
			if (frequencies[i] <= tempFrequency)
			{
				words.insert(words.begin() + i,*tempString);
				frequencies.insert(frequencies.begin() + i,tempFrequency);
				break;
			} else if (i != tempSize - 1)
			{
				continue;
			} else
			{
				words.push_back(*tempString);
				frequencies.push_back(tempFrequency);
			}
		}
	return tempString;
};

void WordGroup::addWord(char* s, short f)
{
	//Add word to list
	std::string tempString = s;
	if (size == 0)
	{
		words.push_back(tempString);
		frequencies.push_back(f);
	} else
	{
		for (int i = 0; i < size; i++)
		{	
			if (frequencies[i] < f)
			{
				words.insert(words.begin() + i,tempString);
				frequencies.insert(frequencies.begin() + i,f);
				break;
			} else if (i != size - 1)
			{
				continue;
			} else
			{
				words.push_back(tempString);
				frequencies.push_back(f);
			}
		}
	}
	size = words.size();
}


int main()
{
	std::vector<std::string> words;
	std::vector<short> frequencies;
	int N;
	std::vector<WordGroup> Dictionary[REST];
	//Read dictionary from stdin
	scanf("%d\n",&N);
	for (int i = 0; i < N; i++)
	{
		char word[21] = "";
		char number[21] = "";
		int frequency = 0;
		int hash;
		scanf("%s %d\n",number,&frequency);
		strcpy(word,number);
		getNumberFromWord(number);
		hash = getHashFromNumber(number);
		if (Dictionary[hash].size() == 0)
		{
			Dictionary[hash].push_back(*(new WordGroup()));
			Dictionary[hash][0].addWord(word,frequency);
			Dictionary[hash][0].setNumber(number);
			continue;
		}
		for (int j = 0; j < Dictionary[hash].size(); j++)
		{
			char tempNumber[21];
			if (strcmp(Dictionary[hash][j].getNumber(tempNumber),number) == 0)
			{
				Dictionary[hash][j].addWord(word,frequency);
				break;
			} 
			if (j == Dictionary[hash].size() - 1)
			{
				Dictionary[hash].push_back(*(new WordGroup()));
				Dictionary[hash][Dictionary[hash].size() - 1].addWord(word,frequency);
				Dictionary[hash][Dictionary[hash].size() - 1].setNumber(number);
			}
		}
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
			if (iteratorWord != 0)
			{
				word[iteratorWord] = '\0';
				int hash = getHashFromNumber(word);
				if (Dictionary[hash].size() > 0)
				{
					for (int i = 0; i < Dictionary[hash].size(); i++)
					{
						char tempNumber[21];
						if (strcmp(Dictionary[hash][i].getNumber(tempNumber),word) == 0)
						{
							Dictionary[hash][i].getWord(&tempString,iteratorStar);
						}
					}
				}
				else
					tempString = "";
				output += tempString;
			}
			if (needPunctuation == true)
			{
				iteratorStar = iteratorStar%3;
				output += punctuation[iteratorStar];
				needPunctuation = false;
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
				int hash = getHashFromNumber(word);
				if (Dictionary[hash].size() > 0)
				{
					for (int i = 0; i < Dictionary[hash].size(); i++)
					{
						char tempNumber[21];
						if (strcmp(Dictionary[hash][i].getNumber(tempNumber),word) == 0)
						{
							Dictionary[hash][i].getWord(&tempString,iteratorStar);
						}
					}
				}
				else
					tempString = "";
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
				int hash = getHashFromNumber(word);
				if (Dictionary[hash].size() > 0)
				{
					for (int i = 0; i < Dictionary[hash].size(); i++)
					{
						char tempNumber[21];
						if (strcmp(Dictionary[hash][i].getNumber(tempNumber),word) == 0)
						{
							Dictionary[hash][i].getWord(&tempString,iteratorStar);
						}
					}
				}
				else
					tempString = "";
				output += tempString;
			}
		}
	}
	puts(output.data());
	return 0;
}

