#include <map>
#include <string>
#include <list>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

typedef unsigned long ulong;
typedef unsigned int  uint;

typedef map<int,list<string*>,greater<int> > TPriorityMap;

//-----------------------------------------------------------------------------
// ���������: ��� ����� (� ������������) ��� ���������� ���������� ������

class WordsForDigitCollection
{
public:
	// ��������� ����� � ������ ����������
	void addWord(string *word, int priority)
    {
		_collection[priority].push_front(word);
		_wordsCount++;
	}

	// ������� ����� �� ���������� ������� '*'
	const string* getWordBySwitches(uint switches)
    {
		// ����� �� ������ �� �����
		switches %= _wordsCount ;

		uint passedWords = 0;
		uint wordListSize = 0;

		// � ������� �������� ����������� - ���� ������ ������:
		TPriorityMap::iterator findList = _collection.begin();
		while( findList != _collection.end() )
		{
			wordListSize = findList->second.size();
			if( (passedWords + wordListSize) > switches ) {
				// ����� � ������� ������
				break;
			}
			else {
				// ��������� � ���������� ������
				passedWords += wordListSize;
				++findList;
			}
		}

		int priority = findList->first;
		list<string*>* wordList = &findList->second;

        // ������� ������� ����� � ������ wordList
        int positionInList = switches - passedWords;

		list<string*>::iterator findWord = wordList->begin();
		while( positionInList > 0 )
		{
			++findWord;
			--positionInList;
		}
		string* result = *findWord;

		// ������ ��������� � �����
		_collection[ priority ].remove(result);
		_collection[priority+1].push_front(result);

		return result;
	}

	// ��������� ����� � ������� � ���������� �������
    void sortLists()
    {
		TPriorityMap::iterator i;
		for(i = _collection.begin(); i != _collection.end(); ++i) {
            i->second.sort();
		}
    }

private:
	// ���������� ���� ��� ���������� ������
	uint _wordsCount;

	// ������ ���� � ���������� ����������� (�� ��������)
	TPriorityMap _collection;
};

//-----------------------------------------------------------------------------
// �������: ��������� ���� ���� � ��������

class Dictionary
{
public:
	// ���������� ������ ����� � �������� �����������
	void addWord(string *word, int priority)
    {
		_dictionary[ ConvertWordToDigits(word) ].addWord(word, priority);
	}

	// ����� ����� �� ������������������ ��������� ������ � ���������� "*"
	const string* getWord(string *digits, uint switchCount)
    {
		return _dictionary[ (*digits) ].getWordBySwitches(switchCount);
	}

	// ������� ���� ���������� �� ���������� "1"
	char getPunctuationChar(int switchCount)
    {
		static const char *_punctuations = "?.,";
		return _punctuations[ switchCount % 3 ];
	}

	// ������������� ����� � �������� � ���������� �������
    void sortWords()
    {
        map<string,WordsForDigitCollection>::iterator i;
        for(i = _dictionary.begin(); i != _dictionary.end(); ++i) {
			i->second.sortLists();
		}
    }

	friend istream& operator>> (istream&, Dictionary&);

	// ������� �� �����
	~Dictionary()
	{
		delete[] _words;
	}

private:
	string* _words;
	uint    _size;

	// ����������� ��������� ���������� � ������ ����
	map<string,WordsForDigitCollection> _dictionary;

private:
	string ConvertWordToDigits(string *text)
    {
		// ����������� ����� � �����. ����� "abcdefghijklmnopqrstuvwxyz"
		static const char *charToDigitMap = "22233344455566677778889999";
		
		string result;
		result.reserve(text->length());
		for(string::iterator i = text->begin(); i != text->end(); ++i)
			result.push_back( charToDigitMap[ tolower(*i) - 'a' ] );

		return result;
	}
};


//-----------------------------------------------------------------------------
// �������� �����: �������������� ��������� ������������� ������

class Parser
{
public:

	class State;

	Parser();

	void InterpretText(istream*    input, 
		               ostream*    output, 
		               Dictionary* dictionary);

	void ChangeState(State *state)
    {
		_state = state;
	}
	void addSwitch()
    {
		if ( _currentWord.length() > 0 ) {
			addWordSwitch();
		}
		else if ( _punctuationCount > 0 ) {
			addPunctuationSwitch();
		}
	}
	void addSpace()
    {
        addToOutput(' ');
	}
	void addWordChar(char c)
    {
		_currentWord.push_back(c);
	}
	void addWordSwitch()
	{
		_switchCount++;
	}
	void addPunctuationSwitch()
    {
		_punctuationCount++;
	}
	void finalizeWord()
    {
		addToOutput( _dictionary->getWord(&_currentWord, _switchCount) );
		_currentWord.clear();
		_switchCount = 0;
	}
	void finalizePunctuation()
    {
		addToOutput( _dictionary->getPunctuationChar(_punctuationCount) );
		_punctuationCount = 0;
	}
    void finalize()
    {
		if ( _currentWord.length() > 0 ) {
            finalizeWord();
		}
		else if ( _punctuationCount > 0 ) {
            finalizePunctuation();
		}		
    }

protected:
	void addToOutput(char c)
	{
		(*_output) << c;
	}
	void addToOutput(const string* text)
	{
		(*_output) << (*text);
	}

private:
	string		_currentWord;       // ������� ������������������ [2-9]
	int			_switchCount;       // ������� ��� ������ ������ "*"
	int			_punctuationCount;  // ������� ��� ������ ������ "1"

	State*		_state;				// pattern State
	Dictionary* _dictionary;

	istream*    _input;
	ostream*    _output;
};

class Parser::State
{
public:
	// ��������� 1 ������� ������� ������
	void ProcessCharacter(char, Parser*);

protected:
	// ������� ��������� �� �������� �������� �������
	virtual void OnSpace(Parser* parser)
	{
		parser->finalize();
		parser->addSpace();
	}
	virtual void OnSwitch(Parser* parser)
	{
		parser->addSwitch();
	}
	virtual void OnPunctuation(Parser* parser)
	{
		parser->finalize();
		parser->addPunctuationSwitch();
	}
	virtual void OnDigit(char, Parser*) = 0;

	// ����� ��������� (���������� �� ���������)
	void ChangeState(Parser* parser, State* state) {
		parser->ChangeState(state);
	}
};

// ���������: ����� ���������� ������� " "
class ParseStateSpace : public Parser::State
{
public:
	static ParseStateSpace* Instance(){
		static ParseStateSpace _instance;
		return &_instance;
	}
	
    void OnSpace(Parser *parser) {
		parser->addSpace();
	}
	
    void OnSwitch(Parser *parser) {
		// ������ �� ������, �.�. ���� '*' ����� �������
		// �� � ���� �� �������� �� ������� ������
	}
	
    void OnPunctuation(Parser *parser) {
		parser->addPunctuationSwitch();
	}
	
    void OnDigit(char c, Parser *parser) {
		parser->addWordChar(c);
	}

private:
	ParseStateSpace(){}
};

// ���������: ����� ���������� ������� ������ �������� "*"
class ParseStateSwitch : public Parser::State
{
public:
	static ParseStateSwitch* Instance(){
		static ParseStateSwitch _instance;
		return &_instance;
	}
	
	// default: OnSpace, OnSwitch, OnPunctuation

	void OnDigit(char c, Parser *parser)
	{
		parser->finalize();
		parser->addWordChar(c);
	}
private:
	ParseStateSwitch(){}
};

// ���������: ����� ��������� ������� [.,?]
class ParseStatePunctuation : public Parser::State
{
public:
	static ParseStatePunctuation* Instance()
	{
		static ParseStatePunctuation _instance;
		return &_instance;
	}

	// default: OnSpace, OnSwitch, OnPunctuation

	void OnDigit(char c, Parser *parser)
	{
		parser->finalizePunctuation();
		parser->addWordChar(c);
	}

private:
	ParseStatePunctuation(){}
};

// ���������: ����� ���������� ����� "[2-9]"
class ParseStateDigit : public Parser::State
{
public:
	static ParseStateDigit* Instance()
	{
		static ParseStateDigit _instance;
		return &_instance;
	}

	// default: OnSpace, OnSwitch, OnPunctuation

	void OnDigit(char c, Parser *parser) {
		parser->addWordChar(c);
	}

private:
	ParseStateDigit(){}
};

// ����� ���������
Parser::Parser() 
{
	_state = ParseStateSpace::Instance();
	_switchCount = 0;
	_punctuationCount = 0;
}

// Pattern State: ������������ ���������
void Parser::InterpretText(istream*    input, 
		                   ostream*    output, 
		                   Dictionary* dictionary)
{
	_input      = input;
	_output     = output;
	_dictionary = dictionary;

    for(;;)
	{
		char c = input->get();
		if( input->eof() ) break;
    	_state->ProcessCharacter(c, this);
    } 

    finalize();
}

// ��������� � ������� � ��. ��������� � ����������� �� ���������� �������
void Parser::State::ProcessCharacter(char c, Parser *parser)
{
	switch(c)
	{
	case ' ': 
		OnSpace(parser);       
		ChangeState(parser, ParseStateSpace::Instance());
		break;
	
	case '*':
		OnSwitch(parser);
		ChangeState(parser, ParseStateSwitch::Instance());
		break;
	
	case '1':
		OnPunctuation(parser);
		ChangeState(parser, ParseStatePunctuation::Instance());
		break;
	
	default:
		if (c >= '2' && c <= '9')
		{
			OnDigit(c, parser);
			ChangeState(parser, ParseStateDigit::Instance());
		}
	}
}

istream& operator>> (istream& input, Dictionary& dictionary)
{
	uint dictionarySize = 0;
	int wordPriority = 0;

	input >> dictionary._size;
    dictionary._words = new string[ dictionary._size ];

	for(uint i = 0; i < dictionary._size; i++)
	{
        input >> dictionary._words[i] >> wordPriority;
		dictionary.addWord( &(dictionary._words[i]), wordPriority );
	}
    dictionary.sortWords();

	return input;
}

//-----------------------------------------------------------------------------
// Entry point:
int main()
{
	// ifstream input("input.txt");
	// ofstream output("output.txt");

    Parser     parser;
	Dictionary dictionary;

	cin >> dictionary;
	
    string  text;
	getline(cin,text);

    parser.InterpretText(&cin, &cout, &dictionary);

	// input.close();
	// output.close();

	return 0;
}