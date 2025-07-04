#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector"

using namespace std;

struct Slovar{
	Slovar () : length (0), vs (0) {word = new char;}
	~Slovar ();
	Slovar (const Slovar&);
	Slovar& operator= (const Slovar&);
	Slovar& operator= (char *);
    void clear ();
	int wordLength ();
	char* word;
	int vs;
 	int length;
};

Slovar::Slovar (const Slovar &rhs)
{
	vs = rhs.vs;
	length = strlen(rhs.word);
	word = new char[length];
	for (int i = 0; i < length; i++)
		word[i] = rhs.word[i];
	word[length] = '\0';
}

Slovar::~Slovar()
{
    if (word)
    delete[] word;
}

Slovar& Slovar::operator = (const Slovar &rhs)
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

Slovar& Slovar::operator = (char* rhs)
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

int Slovar::wordLength ()
{
	length = strlen(word);
	return length;
}

void Slovar::clear ()
{
    vs = 0;
    if (word)
    delete[] word;
    word = 0;
}

class Slovarik
{
public:
	Slovarik ();
	Slovarik (int);
	Slovarik (const Slovarik &);
	~Slovarik ();
	Slovarik& operator= (const Slovarik &);
	Slovarik& operator= (Slovar &);
	Slovar& operator[] (int i);
	void addWord (char*, int);
	void print ();
	int getSize () {return count;}
	void updateData (Slovar &);
	void clear ();
	void swap (char*, char*);
private:
	int size;
	int count;
	int sequence;
	Slovar *p;
};

Slovarik::Slovarik () : p(0)
{
	count = 0;
}

Slovarik::Slovarik (int s) : size(s)
{
	p = new Slovar[size];
	count = 0;
}

Slovarik::Slovarik (const Slovarik &rhs)
{
	size = rhs.size;
	count = rhs.count;
	p = new Slovar[size];
	for (int i = 0; i < count; i ++)
		p[i] = rhs.p[i];
}

Slovarik::~Slovarik ()
{
    if (p)
    delete[] p;
}

Slovarik& Slovarik::operator= (const Slovarik & rhs)
{
	if (this != &rhs)
	{
		size = rhs.size;
		count = rhs.count;
		sequence = rhs.sequence;
		if (p) delete[] p;
		p = new Slovar[size];
		for (int i = 0; i < count; i++)
			p[i] = rhs.p[i];
	}
	return *this;
}

Slovarik& Slovarik::operator= (Slovar &rhs)
{
	if (count < size)
	{
		p[count] = rhs;
	}
	else
	{
		Slovarik tmp (*this);
		if (p) delete[] p;
		size++;
		p = new Slovar[size];
		for (int i = 0; i < count; i++)
			p[i] = tmp.p[i];
		p[count] = rhs;
	}
	++count;
 	return *this;
}

Slovar& Slovarik::operator [] (int i)
{
	if (i < size && i >= 0)
		return p[i];
	else
	throw "Out of index. Terminated...";
	return p[0];
}

void Slovarik::addWord (char *word, int seq)
{
	if (count < size)
	{
		p[count] = word;
		p[count].vs = seq;
	}
	else
	{
	    Slovarik tmp (*this);
		if (p) delete[] p;
		size++;
		p = new Slovar[size];
		for (int i = 0; i < count; i++)
			p[i] = tmp.p[i];
		p[count] = word;
		p[count].vs = seq;
	}
	count++;
}

void Slovarik::print ()
{
	for (int i = 0; i < count; i++)
		cout << "Word: " << p[i].word << ", " << "Sequence: " << p[i].vs << '\n';
}

void Slovarik::updateData(Slovar & data)
{
	for (int i = 0; i < count; i++)
		if (strcmp(p[i].word, data.word) == 0)
			p[i].vs++;
}

void Slovarik::clear()
{
	if (p)
	delete[] p;
	count = 0;
	size = 1;
	p = new Slovar[1];
}

void Slovarik::swap (char* a, char *b)
{
    Slovar *s1 = NULL;
    Slovar *s2 = NULL;
    Slovar tmp;
    int counter(0);
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
    counter = c2 - c1;
    if (strcmp (s1->word, s2->word) != 0)
    {
       tmp = *s2;
       for (int i = counter; i > 0; i--)
       {
           Slovar q = p[counter];
           Slovar q1 = p[counter - 1];
           p[i] = p[i - 1];
       }
       p[c1] = tmp;
       p[c1].vs++;
    }
    else
    {
        p[counter].vs++;
    }
}

class Parser
{
    public:
    Parser () {}
    ~Parser () {}
    void parseInput (char *input);
    Slovarik getString ();
    void getWord (Slovar&, Slovarik&);
    void getNextWord (Slovar&, Slovarik&);
    private:
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

void parseInput (char *input);
Slovarik getString ();
void getWord (Slovar&, Slovarik&);
void getNextWord (Slovar&, Slovarik&);
int wordsCounter(0);
Slovarik first(12);
Slovarik temp (1);
std::vector<int>numberSet;
std::vector<int>::iterator itr;
std::vector<char*>exeption;
std::vector<char*>::iterator itrC;

int main ()
{
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
	try
	{
		if (first.getSize() != 0)
		parseInput (iinput);
	}
	catch (const char &ex)
	{
		cout << ex << '\n';
	}
	return 0;
}

void parseInput (char *input)
{
	Slovarik localTemp;
		Slovar ttemp;
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
		if (c[0] == '0')
		{
		    input++;
		    continue;
		}
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

Slovarik getString ()
{
		int count = strlen(set[numberSet.front()].letters);
		for (int i = 0; i < wordsCounter; i ++)
		{
			for (int j = 0; j < count; j++)
			{
				if (set[numberSet.front()].letters[j] == first[i].word[0])
				{
					temp = first[i];
				}
			}
		}
		for (int i = 1; i < numberSet.size(); i++)
		{
			Slovarik tmp(1);
			for (int k = 0; k < temp.getSize(); k++)
			{
				for (int j = 0; j < strlen(set[numberSet.at(i)].letters); j++)
				{
					char letter = set[numberSet.at(i)].letters[j];
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

void getNextWord(Slovar &ttemp, Slovarik &localTemp)
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
			Slovar a;
			a = localTemp[i];
			if (ttemp.vs < localTemp[i].vs)
			ttemp = localTemp[i];
			flag = false;
		}
		flag = true;
	}
}

void getWord (Slovar& ttemp, Slovarik& localTemp)
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
