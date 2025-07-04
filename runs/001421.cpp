#include <iostream>
#include <vector>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef	unsigned long int	UI32;

using namespace std;

class word
{
public:
	vector<char*> Words;
	vector<UI32> frequency;
	UI32 combination;
	vector<UI32> last;

	void add(char*, UI32);
	void setLast();

	word()
	{
		combination = 0;
	}

	~word(){}
};

class stringParse
{
public:
	char *buff;

	stringParse()
	{
		buff = new char[10000];
		memset(buff, '\0', sizeof(char)*10000);
	}

	~stringParse()
	{
		if( buff != 0 )
			delete [] buff;
	}

	 vector<pair<UI32,UI32> > Parse();
};

UI32 calc(char* );

int main()
{
	UI32 n;
	char wordCh[256];
	UI32 frequency;
	UI32 combination;
	vector<word> dictionary;
	vector<word>::iterator dicIter;
	vector<word>::iterator dicEnd;
	word newWord;
	stringParse str;

	dictionary.push_back(newWord);
	dictionary[0].combination = 1;
	dictionary[0].add(".", 1);
	dictionary[0].add(",", 1);
	dictionary[0].add("?", 1);
	dictionary.push_back(newWord);
	dictionary[1].combination = 0;
	dictionary[1].add(" ", 1);

	cin >> n;

	for(UI32 i = 0; i < n; ++i)
	{
		cin >> wordCh >> frequency;
		combination = calc(wordCh);

		dicIter = dictionary.begin();
		dicEnd = dictionary.end();
		while(dicIter != dicEnd)
		{
			if(dicIter->combination == combination)
			{
				dicIter->add(wordCh, frequency);
				break;
			}
			++dicIter;
		}
		if(dicIter == dicEnd)
		{
			dictionary.push_back(newWord);
			UI32 size = dictionary.size() - 1;
			dictionary[size].add(wordCh, frequency);
			dictionary[size].combination = combination;
		}
	}

	dicIter = dictionary.begin();
	while(dicIter != dictionary.end())
	{
		dicIter->setLast();
		++dicIter;
	}
	cin.getline(str.buff,10000);
	gets(str.buff);

	cout << str.buff << "\n";

	vector<pair<UI32,UI32> >::iterator vecIter;
	vector<pair<UI32,UI32> > vecPair(str.Parse());

	vecIter = vecPair.begin();

	for(vecIter = vecPair.begin(); vecIter != vecPair.end(); vecIter++)
	{
		for(dicIter = dictionary.begin(); dicIter != dictionary.end(); dicIter++)
		{
			if(dicIter->combination == vecIter->first)
				break;
		}
		vector<UI32>::iterator it = dicIter->last.begin();
		for(UI32 i = 0; i < vecIter->second; i++)
		{
			it++;
			if(it == dicIter->last.end())
				it = dicIter->last.begin();
		}
		cout << dicIter->Words[*it];
		vector<UI32>::iterator fr = dicIter->frequency.begin();
		for(UI32 i = 0; i < *it; i++)
			++fr;
		(*fr)++;
		dicIter->setLast();
	}

	return 0;
}

vector<pair<UI32,UI32> > stringParse::Parse()
{
	char buffs[60];
	memset(buffs, '\0', sizeof(char)*60);

	pair<UI32,UI32> newPair;
	vector<pair<UI32,UI32> > vecPair;

	UI32 i = 0;
	UI32 stars = 0;
	UI32 comb = 65535;
	UI32 in = 0;
	if(buff[0] == '1')
		comb = 1;
	else if(buff[0] == ' ')
		comb = 0;
	else if(buff[0] != '\0')
	{
		buffs[0] = buff[0];
		++in;
	}

	for(i = 1; buff[i] != '\0'; i++)
	{
		if(buff[i] >= '2' && buff[i] <= '9')
		{
			if(comb == 1 || comb == 0)
			{
				newPair.first = comb;
				newPair.second = stars;
				vecPair.push_back(newPair);
				comb = 65535;
				stars = 0;
			}
			buffs[in] = buff[i];
			++in;
		}
		else if(buff[i] == '1')
		{
			if( buffs[0] == '\0' && (comb == 1 || comb == 0))
			{
				newPair.first = comb;
				newPair.second = stars;
				vecPair.push_back(newPair);
			}
			else
			{
				comb = atoi(buffs);
				newPair.first = comb;
				newPair.second = stars;
				vecPair.push_back(newPair);
				memset(buffs, '\0', sizeof(char)*60);
			}
			stars = 0;
			comb = 1;
			in = 0;
		}
		else if(buff[i] == '*')
		{
			stars++;
		}
		else if(buff[i] == ' ')
		{
			if(buffs[0] == '\0' && (comb == 1 || comb == 0))
			{
				newPair.first = comb;
				newPair.second = stars;
				vecPair.push_back(newPair);
			}
			else
			{
				comb = atoi(buffs);
				newPair.first = comb;
				newPair.second = stars;
				vecPair.push_back(newPair);
				memset(buffs, '\0', sizeof(char)*60);
			}
			stars = 0;
			comb = 0;
			in = 0;
		}
	}

	if(buffs[0] == '\0')
	{
		newPair.first = comb;
		newPair.second = stars;
		vecPair.push_back(newPair);
	}
	else
	{
		comb = atoi(buffs);
		newPair.first = comb;
		newPair.second = stars;
		vecPair.push_back(newPair);
	}

	return vecPair;
}

UI32 calc(char* wordCh)
{
	UI32 i = 0;
	UI32 combination = 0;
	while( wordCh[i] != '\0' )
	{
		switch (wordCh[i])
		{
			case 'a':
			case 'b':
			case 'c':
				combination *= 10;
				combination += 2;
				i++;
				break;
			case 'd':
			case 'e':
			case 'f':
				combination *= 10;
				combination += 3;
				i++;
				break;
			case 'g':
			case 'h':
			case 'i':
				combination *= 10;
				combination += 4;
				i++;
				break;
			case 'j':
			case 'k':
			case 'l':
				combination *= 10;
				combination += 5;
				i++;
				break;
			case 'm':
			case 'n':
			case 'o':
				combination *= 10;
				combination += 6;
				i++;
				break;
			case 'p':
			case 'q':
			case 'r':
			case 's':
				combination *= 10;
				combination += 7;
				i++;
				break;
			case 't':
			case 'u':
			case 'v':
				combination *= 10;
				combination += 8;
				i++;
				break;
			case 'w':
			case 'x':
			case 'y':
			case 'z':
				combination *= 10;
				combination += 9;
				i++;
				break;
			case '\0':
			default:
				i++;
				break;
		}
	}
	return combination;
}

void word::add(char* wordCh, UI32 freq)
{
	Words.push_back(wordCh);
	frequency.push_back(freq);
}

int comp(const void *a1, const void *b1)
{
	UI32 a = (UI32)a1;
	UI32 b = (UI32)b1;
	if(a>b)
		return -1;
	else if (a<b)
		return 1;
	else
		return -1;
}

void word::setLast()
{
	if(frequency.size() > 1)
	{
		if(!last.empty())
			last.clear();
		vector<UI32>::iterator it;
		it = frequency.begin();

		UI32 poscurr = 0;

		UI32 num = frequency.size();
		UI32 *buff = new UI32[num];

		for(UI32 i = 0; i < num; i++)
		{
			buff[i] = *it;
			it++;
		}

		qsort(buff, num, sizeof(UI32), *comp);

		vector<UI32>::iterator ln;

		for( UI32 i = 0; i < num; i++)
		{
			for(it = frequency.begin(), poscurr = 0;it != frequency.end(); it++, poscurr++)
			{
				if( *it == buff[i])
				{
					if(last.begin() != last.end())
					{
						for(ln = last.begin(); ln != last.end(); ln++)
						{
							if(*ln == poscurr)
							{
								break;
							}
						}
						if(ln == last.end())
						{
							last.push_back(poscurr);
							break;
						}
					}
					else
					{
						last.push_back(poscurr);
						break;
					}
				}
			}
		}
	}
	else
		last.push_back(0);
}
