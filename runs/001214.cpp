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
// Коллекция: все слова (с приоритетами) для одинаковой комбинации клавиш

class WordsForDigitCollection
{
public:
	// Добавляем слово с учетом приоритета
	void addWord(string *word, int priority)
    {
		_collection[priority].push_front(word);
		_wordsCount++;
	}

	// Находим слово по количеству нажатий '*'
	const string* getWordBySwitches(uint switches)
    {
		// чтобы не бегать по кругу
		switches %= _wordsCount ;

		uint passedWords = 0;
		uint wordListSize = 0;

		// в порядке убывания приоритетов - ищем нужный список:
		TPriorityMap::iterator findList = _collection.begin();
		while( findList != _collection.end() )
		{
			wordListSize = findList->second.size();
			if( (passedWords + wordListSize) > switches ) {
				// слово в текущем списке
				break;
			}
			else {
				// переходим к следующему списку
				passedWords += wordListSize;
				++findList;
			}
		}

		int priority = findList->first;
		list<string*>* wordList = &findList->second;

        // позиция нужного слова в списке wordList
        int positionInList = switches - passedWords;

		list<string*>::iterator findWord = wordList->begin();
		while( positionInList > 0 )
		{
			++findWord;
			--positionInList;
		}
		string* result = *findWord;

		// меняем приоритет у слова
		_collection[ priority ].remove(result);
		_collection[priority+1].push_front(result);

		return result;
	}

	// Сортируем слова в списках в алфавитном порядке
    void sortLists()
    {
		TPriorityMap::iterator i;
		for(i = _collection.begin(); i != _collection.end(); ++i) {
            i->second.sort();
		}
    }

private:
	// Количество слов для комбинации клавиш
	uint _wordsCount;

	// Списки слов с одинаковым приоритетом (по убыванию)
	TPriorityMap _collection;
};

//-----------------------------------------------------------------------------
// Словарь: коллекция всех слов в телефоне

class Dictionary
{
public:
	// Добавление нового слова с заданным приоритетом
	void addWord(string *word, int priority)
    {
		_dictionary[ ConvertWordToDigits(word) ].addWord(word, priority);
	}

	// Найти слово по последовательности введенных клавиш и количеству "*"
	const string* getWord(string *digits, uint switchCount)
    {
		return _dictionary[ (*digits) ].getWordBySwitches(switchCount);
	}

	// Выбрать знак препинания по количеству "1"
	char getPunctuationChar(int switchCount)
    {
		static const char *_punctuations = "?.,";
		return _punctuations[ switchCount % 3 ];
	}

	// Отсортировать слова в цепочках в алфавитном порядке
    void sortWords()
    {
        map<string,WordsForDigitCollection>::iterator i;
        for(i = _dictionary.begin(); i != _dictionary.end(); ++i) {
			i->second.sortLists();
		}
    }

	friend istream& operator>> (istream&, Dictionary&);

	// Убираем за собой
	~Dictionary()
	{
		delete[] _words;
	}

private:
	string* _words;
	uint    _size;

	// Отображение клавишной комбинации в список слов
	map<string,WordsForDigitCollection> _dictionary;

private:
	string ConvertWordToDigits(string *text)
    {
		// отображение буквы в соотв. цифру "abcdefghijklmnopqrstuvwxyz"
		static const char *charToDigitMap = "22233344455566677778889999";
		
		string result;
		result.reserve(text->length());
		for(string::iterator i = text->begin(); i != text->end(); ++i)
			result.push_back( charToDigitMap[ tolower(*i) - 'a' ] );

		return result;
	}
};


//-----------------------------------------------------------------------------
// Основной класс: интерпретирует введенную пользователем строку

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
	string		_currentWord;       // текущая последовательность [2-9]
	int			_switchCount;       // сколько раз подряд нажата "*"
	int			_punctuationCount;  // сколько раз подряд нажата "1"

	State*		_state;				// pattern State
	Dictionary* _dictionary;

	istream*    _input;
	ostream*    _output;
};

class Parser::State
{
public:
	// Обработка 1 символа входной строки
	void ProcessCharacter(char, Parser*);

protected:
	// Реакция состояния на варианты входного символа
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

	// Смена состояния (реализация по умолчанию)
	void ChangeState(Parser* parser, State* state) {
		parser->ChangeState(state);
	}
};

// Состояние: после считывания символа " "
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
		// ничего не делаем, т.к. ввод '*' после пробела
		// ни к чему не приводит по условию задачи
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

// Состояние: после считывания символа выбора варианта "*"
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

// Состояние: после обработки символа [.,?]
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

// Состояние: после считывания цифры "[2-9]"
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

// Сброс состояния
Parser::Parser() 
{
	_state = ParseStateSpace::Instance();
	_switchCount = 0;
	_punctuationCount = 0;
}

// Pattern State: посимвольная обработка
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

// Обработка и переход в др. состояние в зависимости от считанного символа
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