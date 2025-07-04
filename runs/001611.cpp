#include <iostream>
#include <algorithm>
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
	UI32 lastused;

	void add(char*, UI32);
	void setLast();
	void move(UI32);

	word()
	{
		combination = 0;
		lastused = 20000;
	}

	void print(int n)
	{
		UI32 f = n % last.size();
		cout << Words[last[f]];
		if(combination != 1 && combination != 0)
		{
			frequency[last[f]] = frequency[last[f]] + 1;
			lastused = last[f];
			move(f);
		}
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

	 vector< pair<UI32,UI32> > Parse();
};

UI32 calc(char* );
bool compVec(const word& d1, const word& d2);

int main()
{
	UI32 n;
	UI32 frequency;
	UI32 combination;
	vector<word> dictionary;
	vector<word>::iterator dicIter;
	vector<word>::iterator dicEnd;
	word newWord;
	stringParse str;

	dictionary.push_back(newWord);
	dictionary[0].combination = 0;
	dictionary[0].add(" ", 1);

	dictionary.push_back(newWord);
	dictionary[1].combination = 1;
	dictionary[1].add(".", 1);
	dictionary[1].add(",", 1);
	dictionary[1].add("?", 1);

	cin >> n;

	for(UI32 i = 0; i < n; ++i)
	{
		char *wordCh = new char[21];
		cin >> wordCh >> frequency;
		combination = calc(wordCh);

		int db;
		int de;
		int dc;

		db = 0;
		de = dictionary.size()-1;
		while(db <= de)
		{
			dc = db + (de - db)/2;
			if( combination > dictionary[dc].combination)
				db = dc + 1;
			else if(combination < dictionary[dc].combination)
				de = dc - 1;
			else
				break;
		}
		if(dictionary[dc].combination == combination)
			dictionary[dc].add(wordCh, frequency);
		else if(dictionary[dc].combination < combination)
		{
			dictionary.insert(dictionary.begin() + dc + 1, newWord);
			dictionary[dc+1].add(wordCh, frequency);
			dictionary[dc+1].combination = combination;
		}
		else if(dictionary[dc].combination > combination)
		{
			dictionary.insert(dictionary.begin() + dc, newWord);
			dictionary[dc].add(wordCh, frequency);
			dictionary[dc].combination = combination;
		}

/*		dicIter = dictionary.begin()+2;
		dicEnd = dictionary.end();

		for(; dicIter != dicEnd; dicIter++)
		{
			if(dicIter->combination == combination)
			{
				dicIter->add(wordCh, frequency);
				break;
			}
		}
		if(dicIter == dicEnd)
		{
			dictionary.push_back(newWord);
			UI32 size = dictionary.size()-1;

			dictionary[size].add(wordCh, frequency);
			dictionary[size].combination = combination;
		}*/
	}

	sort(dictionary.begin(), dictionary.end(), compVec);

	dicIter = dictionary.begin();
	dicEnd = dictionary.end();
	for(;dicIter != dictionary.end(); dicIter++)
	{
		dicIter->setLast();
	}
	cin.getline(str.buff,10000);
	gets(str.buff);

	vector<pair< UI32,UI32> >::iterator vecIter;
	vector<pair< UI32,UI32> > vecPair(str.Parse());

	vecIter = vecPair.begin();

	for(vecIter = vecPair.begin(); vecIter != vecPair.end(); vecIter++)
	{
		if(vecIter->first == 1 || vecIter->first == 0)
		{
			dictionary[vecIter->first].print(vecIter->second);
		}
		else
		{
			vector<word>::iterator dicEnd = dictionary.end();
			dicIter = dictionary.begin()+2;

			while (dicIter != dicEnd)
			{
				vector<word>::iterator mid = dicIter + (dicEnd - dicIter) / 2;

				if (mid->combination < vecIter->first)
					dicIter = mid;
				else if (mid->combination > vecIter->first)
					dicEnd = mid;
				else
				{
					mid->print(vecIter->second);
					break;
				}
			}
		}
	}

	return 0;
}

vector<pair< UI32,UI32> > stringParse::Parse()
{
	char buffs[60];
	memset(buffs, '\0', sizeof(char)*60);

	pair<UI32,UI32> newPair;
	vector< pair<UI32,UI32> > vecPair;

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
			++stars;
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
	UI32 *f = new UI32;
	f[0] = freq;
	char *bword = new char[21];
	for(int i = 0; i < 21; i ++)
		bword[i] = wordCh[i];
	Words.push_back(bword);
	frequency.push_back(f[0]);
}

int comp(const void *a1, const void *b1)
{
	return static_cast<int>( (-1) * ( *(UI32*)a1 - *(UI32*)b1 ) );
}

void word::setLast()
{
	if(frequency.size() > 1)
	{
		if(!last.empty())
			last.clear();
		vector<UI32>::iterator it;
		it = frequency.begin();

        bool set;

		if(lastused != 20000)
            set = false;
        else
            set = true;

		UI32 *posnew;
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
				if( set == false)
			    if( buff[i] == frequency[lastused])
			    {
			        posnew = new UI32;
					*posnew = lastused;
					last.push_back(*posnew);
					set = true;
					continue;
			    }
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
							posnew = new UI32;
							*posnew = poscurr;
							last.push_back(*posnew);
						}
					}
					else
					{
						posnew = new UI32;
						*posnew = poscurr;
						last.push_back(*posnew);
					}
				}
			}
		}
	}
	else
		last.push_back(0);
}

void word::move(UI32 index)
{
	UI32 lastfreq = frequency[last[0]];
	if(last.size() > 1)
	{
		UI32 wordIndex = last[index];
		last.erase(last.begin()+index);
		if(frequency[last[0]] <= frequency[wordIndex])
			last.insert(last.begin(), wordIndex);
		else
		{
			vector<UI32>::iterator it = last.begin() + 1;
			for(; it != last.end(); it++)
			{
				if(lastfreq > frequency[wordIndex] && frequency[wordIndex] >= frequency[*it])
				{
					last.insert(it, wordIndex);
					break;
				}
				else
				{
					lastfreq = frequency[*it];
				}
			}
			if( it == last.end())
				last.push_back(wordIndex);
		}
	}
}

bool compVec(const word& d1, const word& d2)
{
	return d1.combination < d2.combination;
}
