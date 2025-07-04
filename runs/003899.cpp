#include <iostream>
#include <list>
#include <string>
#include <sstream>

using namespace std;

const int MAX_WORD_LEN = 21;
const int PUNCTUATION_MARKS_COUNT = 3;
const int DIGIT_COUNT = 8;
const int MAX_WORD_PLUS_FREQUENCY_LEN  = 26;
const int MAX_SMS_LEN = 100001;

class SharedString
{
	string *str;
public:
	SharedString(string str);
	void DeleteString();
	bool operator>(SharedString str2);
	char operator[](int i);
	string Copy();
	int Lenght();
};

class Coder
{
	char *code;
	static char selectPunctuationMark(int number);
public:
	Coder();
	void Code(SharedString word);
	static char EncodePunctuationMark(int numberOfChanges);
	const char *GetCode();
	~Coder();
};

class WordList
{
	int frequency;
	list<SharedString> words;
public:
	WordList(int frequency, SharedString word);
	int Lenght();
	int Frequency();
	void IncreaseFrequency();
	void Insert(SharedString word);
	void PushHead(SharedString word);
	SharedString UseWord(int index);
	~WordList();
};

class FrequencyList
{
	list<WordList *> frequencyList;
public:
	void Add(SharedString word, int frequency);
	SharedString SelectWord(int numberOfChanges);
	~FrequencyList();
};

class CodeTreeNode
{
	CodeTreeNode **nextSymbols;
	FrequencyList frequencyList;
public:
	CodeTreeNode();
	friend class Dictionary;
	void AddWord(string *word, int frequency);
	~CodeTreeNode();
};

class Dictionary
{
	Coder coder;
	CodeTreeNode *codeTree;
public:
	Dictionary();
	void Add(SharedString word, int frequency);
	SharedString SelectWord(const string &code, int numberOfChanges);
	~Dictionary();
};

class SmsTypingEngine
{
	Dictionary dictionary;
	string encodeAndWriteWord(const char *code, int wordLen, int numberOfChanges);
public:
	void AddWordToDictionary(SharedString word, int frequency);
	string EncodeMessage(char *messageCode);
};

SharedString::SharedString(string str)
{
	string *wordPointer = new string(str);
	this->str = wordPointer;
}
bool SharedString::operator>(SharedString str2)
{
	string string1 = *this->str;
	string string2 = *str2.str;
	bool isGreater = string1 > string2;
	return isGreater;
}
char SharedString::operator[](int i)
{
	string data = *this->str;
	return data[i];
}
string SharedString::Copy()
{
	string copy = string(*this->str);
	return copy;
}
void SharedString::DeleteString()
{
	delete this->str;
}
int SharedString::Lenght()
{
	return this->str->length();
}

Coder::Coder()
{
	this->code = new char[MAX_WORD_LEN];
}
Coder::~Coder()
{
	delete[] this->code;
}
const char *Coder::GetCode()
{
	const char *data = this->code;
	return data;
}
void Coder::Code(SharedString word)
{
	int codeLenght = word.Lenght();
	for (int i = 0; i < codeLenght; i++)
	{
		switch (word[i])
		{
		case 'a':
			code[i] = '2';
			break;
		case 'b':
			code[i] = '2';
			break;
		case 'c':
			code[i] = '2';
			break;
		case 'd':
			code[i] = '3';
			break;
		case 'e':
			code[i] = '3';
			break;
		case 'f':
			code[i] = '3';
			break;
		case 'g':
			code[i] = '4';
			break;
		case 'h':
			code[i] = '4';
			break;
		case 'i':
			code[i] = '4';
			break;
		case 'j':
			code[i] = '5';
			break;
		case 'k':
			code[i] = '5';
			break;
		case 'l':
			code[i] = '5';
			break;
		case 'm':
			code[i] = '6';
			break;
		case 'n':
			code[i] = '6';
			break;
		case 'o':
			code[i] = '6';
			break;
		case 'p':
			code[i] = '7';
			break;
		case 'q':
			code[i] = '7';
			break;
		case 'r':
			code[i] = '7';
			break;
		case 's':
			code[i] = '7';
			break;
		case 't':
			code[i] = '8';
			break;
		case 'u':
			code[i] = '8';
			break;
		case 'v':
			code[i] = '8';
			break;
		case 'w':
			code[i] = '9';
			break;
		case 'x':
			code[i] = '9';
			break;
		case 'y':
			code[i] = '9';
			break;
		case 'z':
			code[i] = '9';
		}
	}
}
char Coder::selectPunctuationMark(int number)
{
	switch (number)
	{
	case 0:
		return '.';
	case 1:
		return ',';
	case 2:
		return '?';
	}
}
char Coder::EncodePunctuationMark(int numberOfChanges)
{
	char punctuationMark;
	punctuationMark = selectPunctuationMark(numberOfChanges % PUNCTUATION_MARKS_COUNT);
	return punctuationMark;
}

WordList::WordList(int frequency, SharedString word)
{
	this->frequency = frequency;
	this->words.push_front(word);
}
WordList::~WordList()
{
	int wordsCount = this->words.size();
	if (wordsCount != 0)
	{
		list<SharedString>::iterator iterator = this->words.begin();
		while (iterator != this->words.end())
		{
			iterator->DeleteString();
			iterator++;
		}
	}
}
int WordList::Frequency()
{
	return this->frequency;
}
void WordList::IncreaseFrequency()
{
	this->frequency++;
}
void WordList::PushHead(SharedString word)
{
	this->words.push_front(word);
}
void WordList::Insert(SharedString word)
{
	if (!this->words.empty())
	{
		list<SharedString>::iterator iterator = this->words.begin();
		while (iterator != this->words.end())
		{
			if (word > *iterator)
				iterator++;
			else
				break;
		}

		if (iterator != this->words.end())
			this->words.insert(iterator,word);
		else
			this->words.push_back(word);
	}
	else
		this->words.push_front(word);
}
int WordList::Lenght()
{
	int lenght = this->words.size();
	return lenght;
}
SharedString WordList::UseWord(int index)
{
	list<SharedString>::iterator iterator;
	int listSize = this->words.size();
	if (index < listSize / 2)
	{
		iterator = this->words.begin();
		for (int i = 0; i < index; i++)
			iterator++;
	}
	else
	{
		iterator = this->words.end();
		for (int i = listSize; i > index; i--)
			iterator--;
	}
	SharedString word = *iterator;
	this->words.erase(iterator);
	return word;
}

FrequencyList::~FrequencyList()
{
	int lenght = this->frequencyList.size();
	if (lenght != 0)
	{
		list<WordList *>::iterator iterator = this->frequencyList.begin();
		for (int i = 0; i < lenght; i++)
		{
			delete *iterator;
			iterator++;
		}
	}
}
void FrequencyList::Add(SharedString word, int frequency)
{
	if (!this->frequencyList.empty())
	{
		list<WordList *>::iterator iterator = this->frequencyList.begin();
		int curFrequency;
		while (iterator != frequencyList.end())
		{
			curFrequency = (*iterator)->Frequency();
			if (frequency > curFrequency)
				iterator++;
			else
				break;
		}

		if (iterator != this->frequencyList.end())
		{
			if (frequency == curFrequency)
			{
				(*iterator)->Insert(word);
			}
			else
			{
				WordList *newWordList = new WordList(frequency, word);
				this->frequencyList.insert(iterator, newWordList);
			}
		}
		else
		{
			WordList *newWordList = new WordList(frequency, word);
			this->frequencyList.push_back(newWordList);
		}
	}
	else
	{
		WordList *wordList = new WordList(frequency, word);
		this->frequencyList.push_back(wordList);
	}
}
SharedString FrequencyList::SelectWord(int numberOfChanges)
{
	list<WordList *>::iterator iterator = this->frequencyList.end();
	iterator--;

	while (numberOfChanges > (*iterator)->Lenght() - 1) // = maxIndex
	{
		numberOfChanges -= (*iterator)->Lenght();
		if (iterator != this->frequencyList.begin())
		{
			iterator--;
		}
		else 
		{
			iterator = this->frequencyList.end();
			iterator--;
		}
	}
	//теперь итератор указывает на нужный нам список. Ќадо использовать оттуда элемент на позиции
	//numberOfChanges и толкнуть его в список с частотой на 1 больше

	SharedString word = (*iterator)->UseWord(numberOfChanges);
	int currentFrequency = (*iterator)->Frequency();

	//теперь необходимо добавить в список частоты на 1 больше новое слово и удалить тот список, если он пуст
	list<WordList *>::iterator currentIterator = iterator;
	iterator++;

	if ((*currentIterator)->Lenght() == 0)
	{
		if (iterator == this->frequencyList.end())
		{
			(*currentIterator)->IncreaseFrequency();
			(*currentIterator)->PushHead(word);
		}
		else
		{
			if ((*iterator)->Frequency() > currentFrequency + 1)
			{
				(*currentIterator)->IncreaseFrequency();
				(*currentIterator)->PushHead(word);
			}
			else //(iterator->Frequency() == currentFrequency + 1)
			{
				(*iterator)->PushHead(word);
			}
		}
	}
	else
	{
		if (iterator == this->frequencyList.end())
		{
			WordList *newWordList = new WordList(currentFrequency+1, word);
			this->frequencyList.push_back(newWordList);
		}
		else
		{
			if ((*iterator)->Frequency() == currentFrequency + 1)
			{
				(*iterator)->PushHead(word);
			}
			else
			{
				WordList *newWordList = new WordList(currentFrequency+1, word);
				this->frequencyList.insert(iterator, newWordList);
			}
		}
	}	
	return word;
}

CodeTreeNode::CodeTreeNode()
{
	this->nextSymbols = new CodeTreeNode* [DIGIT_COUNT];
	for (int i = 0; i < DIGIT_COUNT; i++)
	{
		this->nextSymbols[i] = 0;
	}
}
CodeTreeNode::~CodeTreeNode(void)
{
	for (int i = 0; i < DIGIT_COUNT; i++)
	{
		if (this->nextSymbols[i] != 0)
			delete this->nextSymbols[i];
	}
	delete[] this->nextSymbols;
}

Dictionary::Dictionary()
{
	this->codeTree = new CodeTreeNode();
}
Dictionary::~Dictionary()
{
	delete this->codeTree;
}
void Dictionary::Add(SharedString word, int frequency)
{
	this->coder.Code(word);
	string code = coder.GetCode();
	CodeTreeNode *currentNode = this->codeTree;
	int wordLenght = word.Lenght();
	for (int digitPosition = 0; digitPosition < wordLenght; digitPosition++)
	{
		int symbolNumber = code[digitPosition] - '2';
		if (currentNode->nextSymbols[symbolNumber] == 0)
		{
			currentNode->nextSymbols[symbolNumber] = new CodeTreeNode();
		}
		currentNode = currentNode->nextSymbols[symbolNumber];
	}
	currentNode->frequencyList.Add(word, frequency);
}
SharedString Dictionary::SelectWord(const string &code, int numberOfChanges)
{
	CodeTreeNode *currentNode = this->codeTree;
	int wordLenght = code.length();
	for (int digitPosition = 0; digitPosition < wordLenght; digitPosition++)
	{
		int symbolNumber = code[digitPosition] - '2';
		currentNode = currentNode->nextSymbols[symbolNumber];
	}
	SharedString word = currentNode->frequencyList.SelectWord(numberOfChanges);
	return word;
}

string SmsTypingEngine::encodeAndWriteWord(const char *code, int wordLen, int numberOfChanges)
{
	string message = "";
	if (code[0] == '1')
	{
		message+= Coder::EncodePunctuationMark(numberOfChanges);
	}
	else
	{
		string codeString = string(code, wordLen);
		string word = this->dictionary.SelectWord(codeString, numberOfChanges).Copy();
		message += word;
	}
	return message;
}
void SmsTypingEngine::AddWordToDictionary(SharedString word, int frequency)
{
	this->dictionary.Add(word, frequency);
}
string SmsTypingEngine::EncodeMessage(char *messageCode)
{
	string message = "";
	char code[MAX_WORD_LEN] = {0};
	int currentWordLen = 0;
	int numberOfChanges = 0;

	while (*messageCode != '\0')
	{
		switch (*messageCode)
		{
		case ' ':
			if (currentWordLen != 0)
			{
				message += this->encodeAndWriteWord(code, currentWordLen, numberOfChanges);
				numberOfChanges = 0;
			}
			message += ' ';
			currentWordLen = 0;
			break;
		case '1':
			if (currentWordLen != 0)
			{
				message += this->encodeAndWriteWord(code, currentWordLen, numberOfChanges);
				numberOfChanges = 0;
			}
			code[0] = '1';
			currentWordLen = 1;
			break;
		case '*':
			numberOfChanges++;
			break;
		default: //цифра от 2 до 9
			if (currentWordLen != 0 && code[0] == '1')
			{
				message += Coder::EncodePunctuationMark(numberOfChanges);
				numberOfChanges = 0;
				currentWordLen = 0;
			}
			code[currentWordLen] = *messageCode;
			currentWordLen++;
		}
		messageCode++;
	}

	if (currentWordLen != 0)
	{
		message += this->encodeAndWriteWord(code, currentWordLen, numberOfChanges);
	}

	return message;
}

int main()
{
	SmsTypingEngine engine;

	int wordCount;
	cin >> wordCount;
	cin.get();

	char wordPlusFrequency[MAX_WORD_PLUS_FREQUENCY_LEN];
	for (int i = 0; i < wordCount; i++)
	{
		cin.getline(wordPlusFrequency, MAX_WORD_PLUS_FREQUENCY_LEN);			
		string word;
		int frequency;
		istringstream stream(wordPlusFrequency);	
		stream >> word;
		stream >> frequency;
		SharedString sharedStr(word);
		engine.AddWordToDictionary(sharedStr, frequency);
	}

	char message[MAX_SMS_LEN];
	cin.getline(message, MAX_SMS_LEN);
	string result = engine.EncodeMessage(message);
	cout << result << endl;	
    return 0;
}
