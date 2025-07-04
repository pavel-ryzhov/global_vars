#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector"
#include <time.h>

using namespace std;

struct WordInfo{
	WordInfo () : length (0), vs (0) {}
	~WordInfo ();
	WordInfo (const WordInfo&);
	WordInfo& operator= (const WordInfo&);
	WordInfo& operator= (const string&);
    void clear ();
	int wordLength ();
	string word;
	int vs;
 	int length;
};

WordInfo::WordInfo (const WordInfo &rhs)
{
	vs = rhs.vs;
	word = rhs.word;
}

WordInfo::~WordInfo()
{

}

WordInfo& WordInfo::operator = (const WordInfo &rhs)
{
	if (this != &rhs)
	{
		vs = rhs.vs;
		word = rhs.word;
	}
	return *this;
}

WordInfo& WordInfo::operator = (const string& str)
{
	word = str;
	return *this;
}

void WordInfo::clear ()
{
    word = "";
}

class Dictionary
{
public:
	Dictionary ();
	Dictionary (int);
	Dictionary (const Dictionary &);
	~Dictionary ();
	Dictionary& operator= (const Dictionary &);
	Dictionary& operator= (WordInfo &);
	WordInfo& operator[] (int i);
	void addWord (const string&, const int);
	void print ();
	int getSize () {return count;}
	void updateData (WordInfo &);
	void clear ();
	void swap (string&, string&);
private:
	int size;
	int count;
	int sequence;
	WordInfo *p;
};

Dictionary::Dictionary () : p(0)
{
	count = 0;
}

Dictionary::Dictionary (int s) : size(s)
{
	p = new WordInfo[size];
	count = 0;
}

Dictionary::Dictionary (const Dictionary &rhs)
{
	size = rhs.size;
	count = rhs.count;
	p = new WordInfo[size];
	for (int i = 0; i < count; i ++)
		p[i] = rhs.p[i];
}

Dictionary::~Dictionary ()
{
    if (p)
    delete[] p;
}

Dictionary& Dictionary::operator= (const Dictionary & rhs)
{
	if (this != &rhs)
	{
		size = rhs.size;
		count = rhs.count;
		sequence = rhs.sequence;
		if (p) delete[] p;
		p = new WordInfo[size];
		for (int i = 0; i < count; i++)
			p[i] = rhs.p[i];
	}
	return *this;
}

Dictionary& Dictionary::operator= (WordInfo &rhs)
{
	if (count < size)
	{
		p[count] = rhs;
	}
	else
	{
		Dictionary tmp (*this);
		if (p) delete[] p;
		size++;
		p = new WordInfo[size];
		for (int i = 0; i < count; i++)
			p[i] = tmp.p[i];
		p[count] = rhs;
	}
	++count;
 	return *this;
}

WordInfo& Dictionary::operator [] (int i)
{
	if (i < size && i >= 0)
		return p[i];
	else
	throw "Out of index. Terminated...";
	return p[0];
}

void Dictionary::addWord (const string& str,const int seq)
{
	if (count < size)
	{
		p[count] = str;
		p[count].vs = seq;
	}
	else
	{
	    Dictionary tmp (*this);
		if (p) delete[] p;
		size++;
		p = new WordInfo[size];
		for (int i = 0; i < count; i++)
			p[i] = tmp.p[i];
		p[count] = str;
		p[count].vs = seq;
	}
	count++;
}

void Dictionary::print ()
{
	for (int i = 0; i < count; i++)
		cout << "Word: " << p[i].word << ", " << "Sequence: " << p[i].vs << '\n';
}

void Dictionary::updateData(WordInfo & data)
{
	for (int i = 0; i < count; i++)
		if (p[i].word.compare(data.word) == 0)
			p[i].vs++;
}

void Dictionary::clear()
{
	if (p)
	delete[] p;
	count = 0;
	size = 1;
	p = new WordInfo[1];
}

void Dictionary::swap (string& a, string& b)
{
    WordInfo *s1 = NULL;
    WordInfo *s2 = NULL;
    WordInfo tmp;
    int c1(0);
    int c2(0);
    for (int i = 0; i < this->count; i++)
    {
        if (a.compare(p[i].word) == 0)
        {
            c1 = i;
           s1 = (&p[i]);
        }
        if (b.compare(p[i].word) == 0)
        {
            c2 = i;
            s2 = &(p[i]);
        }
    }
    if (s1->word.compare(s2->word) != 0)
    {
       tmp = s2->word;
       tmp.vs = s2->vs;
       for (int i = c2; i > c1; i--)
       {
           p[i] = p[i-1];
       }
       p[c1] = tmp;
       p[c1].vs++;
    }
    else
    {
        p[c1].vs++;
    }
}

class Parser
{
    public:
		Parser () : temp(1), stop(false), position1(0), position2(0) {}
		~Parser () {}
		void parseInput(char *input);
		void getString(Dictionary&);
		void getWord (WordInfo&, Dictionary&);
		void getNextWord (WordInfo&, Dictionary&);
		void getDictionary (vector<WordInfo> *d) {first = d;};
		void swap(string &, string &);
	void print ();
    private:
		int position1;
		int position2;
		bool stop;
		vector<WordInfo> *first;
		vector<WordInfo>::iterator wItr;
		vector<WordInfo> temp;
		std::vector<int>numberSet;
		std::vector<int>::iterator itr;
		std::vector<string>exeption;
		std::vector<string>::iterator itrC;
};

void Parser::print()
{
	for (wItr = first->begin(); wItr < first->end(); wItr++)
	{
		cout << wItr->word << ' ';
		cout << wItr->vs << '\n';
	}
}

void Parser::swap(string &a, string &b)
{
	WordInfo *s1 = NULL;
    WordInfo *s2 = NULL;
    WordInfo tmp;
    int c1(0);
    int c2(0);
	int i;
	for (wItr = first->begin(), i = 0; wItr < first->end(); i++, wItr++)
    {
        if (a.compare(wItr->word) == 0)
        {
           c1 = i;
           s1 = &(*wItr);
        }
        if (b.compare(wItr->word) == 0)
        {
            c2 = i;
            s2 = &(*wItr);
        }
    }
		wItr = first->begin();
		tmp = s2->word;
		tmp.vs = s2->vs;
		first->erase(first->begin()+c2);
		first->insert(wItr+c1,tmp); 
		wItr[c1].vs++;	
}


struct Numbers{
	char letters[5];
}set[10] = {"",
			".,?",
			"abc",
			"def",
			"ghi",
			"jkl",
			"mno",
			"pqrs",
			"tuv",
			"wxyz"};

int main ()
{
    int wordsCounter(0);
    Parser parser;
	vector <WordInfo> first;
	WordInfo wi;
    char iinput[100003];
    char buffer[30];
    char word[21];
    string str1, str2;
    int pos(0);
    cin >> wordsCounter;
    cin.ignore(1, '\n');
    for (int i = 0; i < wordsCounter; i++)
    {
        cin.getline(buffer, 30);
        str1 = buffer;
        pos = str1.find(' ');
        str2 = str1.substr(pos);
        str1 = str1.substr(0, pos);
        strcpy (word, str1.c_str());
        int x = atoi(str2.c_str());
		wi.word = word;
		wi.vs = atoi(str2.c_str());
		first.push_back(wi);
    }
    cin.getline (iinput, 100003);
    int x = strlen(iinput);
    iinput[x] = ' ';
    iinput[x+1] = '\0';
    parser.getDictionary(&first);
	try
	{
		if (first.size() != 0)
		parser.parseInput (iinput);
	}
	catch (const char &ex)
	{
		cout << ex << '\n';
	}	

	return 0;
}

void Parser::parseInput (char *input)
{
	Dictionary localTemp;
    WordInfo ttemp;
    ttemp.clear();
	bool flag = false;
	bool one = false;
	bool star = false;
	int counter(0);
	int starCounter(0);
	char buffer[255];
	buffer[0] = '0';
	buffer[1] = '\0';
	int bufferCount(0);
	int sequenceLength(0);
	while (*input != '\0')
	{
		char c[2];
		c[0] = *input;
		c[1] = '\0';
		if (c[0] == '*')
		{
		    if (numberSet.size() != 0 && !star)
		    {
		        getString(localTemp);
		        temp.clear();
		        if (localTemp.getSize() > 0)
                getWord (ttemp, localTemp);
                star = true;
		    }

			if (one)
			{
				buffer[starCounter] = set[1].letters[++counter];
				if (counter == 3)
					counter = 0;
			}
			else
			{
			    if (ttemp.word != "")
			    {
                    string a;
                    a = ttemp.word;
                    exeption.push_back(a);
                    getNextWord (ttemp, localTemp);
			    }
			}
			input++;
			continue;
		}
		if (c[0] == '1')
		{
			one = true;
			if (buffer[0] != '0')
			{
                starCounter++;
                counter = 0;
			}
			buffer[starCounter] = set[1].letters[counter];
			input++;
			continue;
		}
		if (c[0] == ' ')
		{
		    if (numberSet.size() != 0 && ttemp.word == "")
		    {
		        getString(localTemp);
		        temp.clear();
		        if (localTemp.getSize() > 0)
                getWord (ttemp, localTemp);
		    }
			if (ttemp.word != "")
			{
			cout << ttemp.word;
			numberSet.clear();	
			position2 = position1 + position2;
			swap(localTemp[0].word, ttemp.word);
			}
			exeption.clear();
			if (buffer[0] != '0')
			for(short int i = 0; i < starCounter+1; i++)
				cout << buffer[i];
			sequenceLength = 0;
            one = false;
            star = false;
			buffer[0] = '0';
			counter = 0;
			starCounter = 0;
			cout << ' ';
			input++;
			ttemp.clear();
			localTemp.clear();
			numberSet.clear();
			//cout << "\n";
			//print();
			continue;
		}
		numberSet.push_back(atoi(c));
		input++;
	}
}

void Parser::getString (Dictionary &localTemp)
{
	int counter(0);
		int count = strlen(set[numberSet.front()].letters);
		for(wItr = first->begin(); wItr < first->end(); wItr++)
		{
			for (int j = 0; j < count; j++)
			{
				if (set[numberSet.front()].letters[j] == wItr->word[0])
				{
					temp.push_back(*wItr);					
					if (!stop)
					{
						position1 = counter;
						stop = true;
					}
				}
			}
			counter++;
		}
		stop = false;
		counter = position1;
		for (int i = 1; i < numberSet.size(); i++)
		{
			Dictionary tmp(1);
			for (int k = 0; k < temp.size(); k++)
			{
				for (int j = 0; j < strlen(set[numberSet.at(i)].letters); j++)
				{
					char letter = set[numberSet.at(i)].letters[j];
					if (temp[k].word[i] == letter)
					{
						if (temp[k].word.length() <= numberSet.size())
							{
								if (!stop)
								{
									position1 = counter;
									stop = true;
								}
								tmp = temp[k];
							}
					}
				}
				counter++;
			}
			localTemp = tmp;
			stop = false;
		}
}

void Parser::getNextWord(WordInfo &ttemp, Dictionary &localTemp)
{
    string a;
	int counter(0);
	bool flag = true;
	int x = exeption.size();
	ttemp.vs = 0;
	if ( x == localTemp.getSize())
	{
		exeption.clear();
        a = ttemp.word;
		exeption.push_back(a);
		flag = true;
	}
	for (int i = 0; i < localTemp.getSize(); i++)
	{
		for (itrC = exeption.begin(); itrC < exeption.end(); itrC++)
		{
			if (localTemp[i].word.compare(*itrC) == 0)
			{
				flag = false;
			}
		}
		if (flag)
		{
			if (ttemp.vs < localTemp[i].vs)
			ttemp = localTemp[i];
			flag = false;
			counter = i;
		}
		flag = true;
	}
	position2 = counter;
}

void Parser::getWord (WordInfo& ttemp, Dictionary& localTemp)
{
	int counter(0);
	ttemp = localTemp[0];
	for (int i = 0; i < localTemp.getSize(); i++)
	{
		if (localTemp[i].vs > ttemp.vs)
			{				
				ttemp = localTemp[i];
				counter = i;
			}
	}
	position2 = counter;
}
