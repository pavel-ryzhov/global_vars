#include <map>
#include <string>
#include <list>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

typedef unsigned long ulong;
typedef unsigned int  uint;

// объединяет приоритеты и списки слов
typedef map<int,list<string*>,greater<uint> > TPriorityMap;

//-------------------------------------------------------------------------
// Коллекция: все слова (с приоритетами) для одинаковой комбинации клавиш

class WordsForDigitCollection
{
public:
	// Добавляем слово с учетом приоритета
	void Add(string *word, uint priority)
    {
		_collection[priority].push_front(word);
		_wordsCount++;
	}

	// Находим слово по количеству нажатий '*'
	const string* GetWord(uint switches)
    {
		// чтобы не бегать по кругу
		switches %= _wordsCount ;

		uint passedWords  = 0;
		uint wordListSize = 0;

		// в порядке убывания приоритетов ищем нужный список:
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

		uint priority = findList->first;
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

		_collection[ priority ].remove(result);
		_collection[priority+1].push_front(result);

		return result;
	}

	// Сортируем слова в списках в алфавитном порядке
    void SortLists()
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
	const string* GetWord(string *digits, uint switchCount)
    {
		return _dictionary[ (*digits) ].GetWord(switchCount);
	}

	char GetPunctuation(int switchCount)
    {
		static const char *_punctuations = "?.,";
		return _punctuations[ switchCount % 3 ];
	}

    friend istream& operator>>(istream&, Dictionary&);

private:
    static string WordToDigits(string &text)
    {
        // отображает буквы в цифры
        static const char *charToDigitMap = "22233344455566677778889999";

        string result;
        result.reserve(text.length());
        for(string::const_iterator i = text.begin(); i != text.end(); ++i)
            result.push_back( charToDigitMap[ tolower(*i) - 'a' ] );

        return result;
    }

	// преобразует комбинацию клавиш в слово
	map<string,WordsForDigitCollection> _dictionary;

    // все слова словаря
    vector<string> _words;
};

// ввод данных в словарь
istream& operator>> (istream& input, Dictionary& d)
{
    uint dictionarySize = 0;
    uint priority = 0;
    uint i = 0;

    input >> dictionarySize;
    d._words.assign(dictionarySize,"");

    while (dictionarySize--)
    {
        input >> d._words[i] >> priority;
        d._dictionary[Dictionary::WordToDigits( d._words[i]) ].\
            Add(&(d._words[i]), priority);
        i++;
    }

    map<string,WordsForDigitCollection>::iterator j;
    for(j = d._dictionary.begin(); j != d._dictionary.end(); ++j) {
        j->second.SortLists();
    }

    string rn;
    getline(input, rn);   // skip \r\n
    return input;
}


//---------------------------------
// Здесь происходит вся работа
class Parser
{
public:
    // внутреннее состояние класса, реализовано как паттерн State
	class State;
	
    Parser();

	void ProcessStream(istream*    input, 
		               ostream*    output, 
		               Dictionary* dictionary);

	void ChangeState(State *state)
    {
		_state = state;
	}
	void AddSwitch()
    {
		if ( _currentWord.length() > 0 )
			AddWordSwitch();
		else if ( _punctuationCount > 0 )
			AddPunctuationSwitch();
	}
	void AddSpace()
    {
        (*_output) << ' ';
	}
	void AddWordChar(char c)
    {
		_currentWord.push_back(c);
	}
	void AddWordSwitch()
	{
		_switchCount++;
	}
	void AddPunctuationSwitch()
    {
		_punctuationCount++;
	}
    void FinalizeWord()
    {
        (*_output) << (*_dictionary->GetWord(&_currentWord, _switchCount));
        _currentWord.clear();
        _switchCount = 0;
    }
    void FinalizePunctuation()
    {
        (*_output) << _dictionary->GetPunctuation(_punctuationCount);
        _punctuationCount = 0;
    }
    void Finalize()
    {
		if ( _currentWord.length() > 0 ) {
            FinalizeWord();
		}
		else if ( _punctuationCount > 0 ) {
            FinalizePunctuation();
		}		
    }

private:
	string		_currentWord;       // текущая последовательность (2-9)
	int			_switchCount;       // сколько раз подряд нажата '*'
	int			_punctuationCount;  // сколько раз подряд нажата '1'

	State*		_state;				// pattern State
	Dictionary* _dictionary;		// Dictionary for parsing

	// хранение потоков нужно для доступа State-у
    istream*    _input;
	ostream*    _output;
};

// абстрактный класс-состояние
// определяет основную логику поведения
class Parser::State
{
public:
	// Обработка 1 символа входной строки
	void ProcessCharacter(char, Parser*);

protected:
	// Реакция состояния на варианты входного символа
	virtual void OnSpace(Parser* parser)
	{
		parser->Finalize();
		parser->AddSpace();
	}
	virtual void OnSwitch(Parser* parser)
	{
		parser->AddSwitch();
	}
	virtual void OnPunctuation(Parser* parser)
	{
		parser->Finalize();
		parser->AddPunctuationSwitch();
	}
	virtual void OnDigit(char, Parser*) = 0;

	void ChangeState(Parser* parser, State* state) {
		parser->ChangeState(state);
	}
};

class ParseStateSpace : public Parser::State
{
public:
	static ParseStateSpace* Instance(){
		static ParseStateSpace _instance;
		return &_instance;
	}
	
    void OnSpace(Parser *parser) {
		parser->AddSpace();
	}
	
    void OnSwitch(Parser *parser) {
		// ничего не делаем, т.к. ввод '*' после пробела
		// ни к чему не приводит по условию задачи
	}
	
    void OnPunctuation(Parser *parser) {
		parser->AddPunctuationSwitch();
	}
	
    void OnDigit(char c, Parser *parser) {
		parser->AddWordChar(c);
	}

private:
	ParseStateSpace(){}
};

class ParseStateSwitch : public Parser::State
{
public:
	static ParseStateSwitch* Instance(){
		static ParseStateSwitch _instance;
		return &_instance;
	}
	
	void OnDigit(char c, Parser *parser)
	{
		parser->Finalize();
		parser->AddWordChar(c);
	}
private:
	ParseStateSwitch(){}
};

// Состояние: после обработки символа ".,?"
class ParseStatePunctuation : public Parser::State
{
public:
	static ParseStatePunctuation* Instance()
	{
		static ParseStatePunctuation _instance;
		return &_instance;
	}

	void OnDigit(char c, Parser *parser)
	{
		parser->FinalizePunctuation();
		parser->AddWordChar(c);
	}

private:
	ParseStatePunctuation(){}
};

class ParseStateDigit : public Parser::State
{
public:
	static ParseStateDigit* Instance()
	{
		static ParseStateDigit _instance;
		return &_instance;
	}

	void OnDigit(char c, Parser *parser) {
		parser->AddWordChar(c);
	}

private:
	ParseStateDigit(){}
};

Parser::Parser() 
{
	_state = ParseStateSpace::Instance();
	_switchCount = 0;
	_punctuationCount = 0;
}

void Parser::ProcessStream(istream*    input, 
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

    Finalize();
}

// простая FSM
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

int main()
{
    Parser parser;
	Dictionary dictionary;

    cin >> dictionary;
    parser.ProcessStream(&cin, &cout, &dictionary);

    return 0;
}