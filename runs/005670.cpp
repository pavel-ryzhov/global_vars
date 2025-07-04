#include <iostream>
#include <set>
#include <string>
#include <deque>

using namespace std;

class TFrequenceData
{
public:
	deque<string*> words;
};

class TFrequence
{
public:
	int freq;
	TFrequenceData *pWords;
	TFrequence(int f)
	{
		freq = f;
		pWords = new TFrequenceData;
	}
	bool operator() (const TFrequence& lhs, const TFrequence& rhs) const
		{return lhs.freq<rhs.freq;}
	bool operator< (const TFrequence& rhs) const
		{return freq<rhs.freq;}
	bool operator> (const TFrequence& rhs) const
		{return freq>rhs.freq;}
	bool operator== (const TFrequence& rhs) const
		{return freq==rhs.freq;}
};

class TCodeData
{
public:
	set<TFrequence> Freqs;
	set<TFrequence>::iterator itrFreq;
	int numWords;
	void addFreq(string *word, int freq);
	string getWordByNum(int n);
};

class TCode
{
public:
	string code;
	TCodeData *data;
	TCode(string cd)
	{
		code = cd;
		data = new TCodeData;
		data->numWords = 1;
	}
	bool operator() (const TCode& lhs, const TCode& rhs) const
		{return lhs.code<rhs.code;}
	bool operator< (const TCode& rhs) const
		{return code<rhs.code;}
	bool operator> (const TCode& rhs) const
		{return code>rhs.code;}
	bool operator== (const TCode& rhs) const
		{return code==rhs.code;}
};

class TLength
{
public:
	set<TCode> Codes;
	set<TCode>::iterator itrCodes;
	void addCode(string code, string *word, int freq);
	string getWordByCode(string code, int n);
};

class TT9
{
public:
	TLength Lengths[20];
	string *word;
	void readDictionary();
	void printSMS();
	void printWord(string code, int n);
};

string makeCode(string str);

int main() {
	TT9 t9;
	t9.readDictionary();
	cin.ignore();
	t9.printSMS();
	return 0;
}

string makeCode(string str)
{
	string code;
	for (int i=0; str[i]; i++)
	{
		if (str[i] == 'a' || str[i] == 'b' || str[i] == 'c') code += '2';
		if (str[i] == 'd' || str[i] == 'e' || str[i] == 'f') code += '3';
		if (str[i] == 'g' || str[i] == 'h' || str[i] == 'i') code += '4';
		if (str[i] == 'j' || str[i] == 'k' || str[i] == 'l') code += '5';
		if (str[i] == 'm' || str[i] == 'n' || str[i] == 'o') code += '6';
		if (str[i] == 'p' || str[i] == 'q' || str[i] == 'r' || str[i] == 's') code += '7';
		if (str[i] == 't' || str[i] == 'u' || str[i] == 'v') code += '8';
		if (str[i] == 'w' || str[i] == 'x' || str[i] == 'y' || str[i] == 'z') code += '9';
	}
	return code;
}

void TT9::readDictionary ()
{
	int numWords;
	int freq;
	cin >> numWords;
	word = new string[numWords];
	for (int i=0; i<numWords; i++)
	{
		cin >> *word >> freq;
		Lengths[(*word).length()-1].addCode(makeCode(*word), word, freq);
		word++;
	}
}

void TLength::addCode(string code, string *word, int freq)
{
	if (Codes.empty())
	{
		itrCodes = Codes.insert(TCode(code)).first;
		itrCodes->data->addFreq(word, freq);
	}
	else if (itrCodes->code == code)
	{
		itrCodes->data->addFreq(word, freq);
		itrCodes->data->numWords++;
	}
	else
	{
		itrCodes = Codes.insert(itrCodes, TCode(code));
		itrCodes->data->addFreq(word, freq);
	}
}

void TCodeData::addFreq(string *word, int freq)
{
	itrFreq = Freqs.insert(TFrequence(freq)).first;
	itrFreq->pWords->words.push_back(word);
}

void TT9::printSMS()
{
	string s;
	int n=0;
	char c;
	while (cin.get(c))
	{
		if (c == '\n' || c =='\0' || c == EOF)
		{
			if (!s.empty()) printWord(s, n);
			break;
		}
		if (c == '1')
		{
			if (!s.empty())
			{
				printWord(s, 0);
				s.clear();
			}
			while (cin.peek() == '*')
			{
				cin.get(c);
				n++;
			}
			switch (n)
			{
			case 0:
				cout << ".";
				break;
			case 1:
				cout << ",";
				break;
			case 2:
				cout << "?";
			}
				n = 0;
		}
		else if (c == '*')
			{
				n = 1;
				while (cin.peek() == '*')
				{
					cin.get(c);
					n++;
				};
				if (!s.empty())
				{
					printWord(s, n);
					s.clear();
				}
				n = 0;
			}
		else if (c == ' ')
			{
				if (!s.empty())
				{
					printWord(s, 0);
					s.clear();
				}
				cout << " ";
			}
		else
			s+=c;
	}
}

void TT9::printWord(string code, int n)
{
	cout << Lengths[code.length()-1].getWordByCode(code, n);
}

string TLength::getWordByCode(string code, int n)
{
	itrCodes = Codes.find(TCode(code));
	return itrCodes->data->getWordByNum(n);
}

string TCodeData::getWordByNum(int n)
{
	string *word;
	int size;
	set<TFrequence>::iterator itrTmp;
	if (numWords/2 < n)
	{
		n = numWords - n - 1;
		itrFreq = Freqs.begin();
		while (1)
		{
			size = itrFreq->pWords->words.size();
			if (size > n)
			{
				word = itrFreq->pWords->words[size - n - 1];
				itrFreq->pWords->words.erase(itrFreq->pWords->words.end()-n-1);
				break;
			}
			else
			{
				n = n - size;
				itrFreq++;
			}
		}
	}
	else
	{
		itrFreq = Freqs.end();
		itrFreq--;
		while (1)
		{
			size = itrFreq->pWords->words.size();
			if (size > n)
			{
				word = itrFreq->pWords->words[n];
				itrFreq->pWords->words.erase(itrFreq->pWords->words.begin()+n);
				break;
			}
			else
			{
				n = n - size;
				itrFreq--;
			}
		}
	}
	itrTmp = itrFreq;
	itrFreq = Freqs.insert(itrFreq, TFrequence(itrFreq->freq+1));
	itrFreq->pWords->words.push_front(word);
	if (size == 1)
		Freqs.erase(itrTmp);
	return *word;
}
