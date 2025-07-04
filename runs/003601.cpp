#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector"

using namespace std;

struct WordInfo{
	WordInfo () : length (0), vs (0) {word = new char;}
	~WordInfo ();
	WordInfo (const WordInfo&);
	WordInfo& operator= (const WordInfo&);
	WordInfo& operator= (char *);
    void clear ();
	int wordLength ();
	char* word;
	int vs;
 	int length;
};

WordInfo::WordInfo (const WordInfo &rhs)
{
	vs = rhs.vs;
	length = strlen(rhs.word);
	word = new char[length];
	for (int i = 0; i < length; i++)
		word[i] = rhs.word[i];
	word[length] = '\0';
}

WordInfo::~WordInfo()
{
    if (word)
    delete[] word;
}

WordInfo& WordInfo::operator = (const WordInfo &rhs)
{
	if (this != &rhs)
	{
		int length = strlen(rhs.word);
		vs = rhs.vs;
		if (this->word)
			delete this->word;
		word = new char[length];
		for (int i = 0; i < length; i++)
		this->word[i] = rhs.word[i];
		word[length] = '\0';
	}
	return *this;
}

WordInfo& WordInfo::operator = (char* rhs)
{
	if (word)
		delete[] word;
    int l = strlen(rhs);
	word = new char[l];
	for (int i = 0; i < l; i++)
		word[i] = rhs[i];
	word[l] = '\0';
	return *this;
}

int WordInfo::wordLength ()
{
	length = strlen(word);
	return length;
}

void WordInfo::clear ()
{
    vs = 0;
    if (word)
    delete[] word;
    word = 0;
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
	void addWord (char*, int);
	void print ();
	int getSize () {return count;}
	void updateData (WordInfo &);
	void clear ();
	void swap (char*, char*);
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

void Dictionary::addWord (char *word, int seq)
{
	if (count < size)
	{
		p[count] = word;
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
		p[count] = word;
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
		if (strcmp(p[i].word, data.word) == 0)
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

void Dictionary::swap (char* a, char *b)
{
    WordInfo *s1 = NULL;
    WordInfo *s2 = NULL;
    WordInfo tmp;
    int c1(0);
    int c2(0);
    for (int i = 0; i < this->count; i++)
    {
        if (strcmp (a, p[i].word) == 0)
        {
            c1 = i;
           s1 = (&p[i]);
        }
        if (strcmp (b, p[i].word) == 0)
        {
            c2 = i;
            s2 = &(p[i]);
        }
    }
    if (strcmp (s1->word, s2->word) != 0)
    {
       tmp = s2->word;
       tmp.vs = s2->vs;
       for (int i = c2; i > c1; i--)
       {
           WordInfo q = p[i];
           WordInfo q1 = p[i - 1];
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
    Parser () : first(1), temp(1) {}
    ~Parser () {}
    void parseInput(char *input);
    Dictionary getString();
    void getWord (WordInfo&, Dictionary&);
    void getNextWord (WordInfo&, Dictionary&);
    void getDictionary (Dictionary& d) {first = d;};
    private:
    //int wordsCounter;
    Dictionary first;
    Dictionary temp;
    std::vector<int>numberSet;
    std::vector<int>::iterator itr;
    std::vector<char*>exeption;
    std::vector<char*>::iterator itrC;
};


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
    Dictionary first(1);
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
        first.addWord(word, atoi(str2.c_str()));
    }
    cin.getline (iinput, 100003);
    int x = strlen (iinput);
    iinput[x] = ' ';
    iinput[x+1] = '\0';
    parser.getDictionary(first);
	try
	{
		if (first.getSize() != 0)
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
	char *sequence = new char('\0');
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
		        localTemp = getString ();
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
			    if (ttemp.word != 0)
			    {
                    char *a = new char;
                    for (int i = 0; i < strlen(ttemp.word); i++)
                        a[i] = ttemp.word[i];
                    a[strlen(ttemp.word)] = '\0';
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
		    if (numberSet.size() != 0 && ttemp.word == 0)
		    {
		        localTemp = getString ();
		        temp.clear();
		        if (localTemp.getSize() > 0)
                getWord (ttemp, localTemp);
		    }
			if (ttemp.word != 0)
			{
			cout << ttemp.word;
			numberSet.clear();
			char *m = new char;
			first.swap (localTemp[0].word, ttemp.word);
			}
			exeption.clear();
			if (buffer[0] != '0')
			for(int i = 0; i < starCounter+1; i++)
				cout << buffer[i];
			sequence[0] = '\0';
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
			continue;
		}
		sequence[sequenceLength] = c[0];
		sequence[++sequenceLength] = '\0';
		numberSet.push_back(atoi(c));
		input++;
	}
}

Dictionary Parser::getString ()
{
		int count = strlen(set[numberSet.front()].letters);
		for (int i = 0; i < this->first.getSize(); i ++)
		{
			for (int j = 0; j < count; j++)
			{
				if (set[numberSet.front()].letters[j] == first[i].word[0])
				{
				    char *b = first[i].word;
					temp = first[i];
				}
			}
		}
		for (int i = 1; i < numberSet.size(); i++)
		{
			Dictionary tmp(1);
			for (int k = 0; k < temp.getSize(); k++)
			{
				for (int j = 0; j < strlen(set[numberSet.at(i)].letters); j++)
				{
					char letter = set[numberSet.at(i)].letters[j];
					char *b = temp[k].word;
					if (temp[k].word[i] == letter)
					{
						if (strlen(temp[k].word) <= numberSet.size())
						tmp = temp[k];
					}
				}
			}
			temp = tmp;
		}
		return temp;
}

void Parser::getNextWord(WordInfo &ttemp, Dictionary &localTemp)
{
	char *a = new char;
	bool flag = true;
	int x = exeption.size();
	ttemp.vs = 0;
	if ( x == localTemp.getSize())
	{
		exeption.clear();
			for (int i = 0; i < strlen(ttemp.word); i++)
				a[i] = ttemp.word[i];
			a[strlen(ttemp.word)] = '\0';
		exeption.push_back(a);
		flag = true;
	}
	for (int i = 0; i < localTemp.getSize(); i++)
	{
		for (itrC = exeption.begin(); itrC < exeption.end(); itrC++)
		{
			if (strcmp(localTemp[i].word, *itrC) == 0)
			{
				flag = false;
			}
		}
		if (flag)
		{
			WordInfo a;
			a = localTemp[i];
			if (ttemp.vs < localTemp[i].vs)
			ttemp = localTemp[i];
			flag = false;
		}
		flag = true;
	}
}

void Parser::getWord (WordInfo& ttemp, Dictionary& localTemp)
{
	ttemp = localTemp[0];
	for (int i = 0; i < localTemp.getSize(); i++)
	{
		if (localTemp[i].vs > ttemp.vs)
			{
				ttemp = localTemp[i];
			}
	}

}
