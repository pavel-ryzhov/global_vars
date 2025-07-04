/**
 * \file mobi_dict.cpp
 * \brief Программа, имитирующая работу мобильного телефона со словарем T9
 * \author Кутуков Денис
 */


#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <map>
using namespace std;

//========== Объявдение класса Dictionary ====================================

typedef unsigned int uint;

typedef struct TDictionaryItem
{
    string word;
    uint freq;
} DictionaryItem;

typedef list<DictionaryItem> WordsQueue;
typedef map<string, WordsQueue> QueuesMap;

class Dictionary
{
public:
    Dictionary();
    virtual ~Dictionary();

    void addWord(string code, string word, uint freq);
    string selectWord(string code, uint order);

private:
     QueuesMap _queuesMap;
};

//============ Реализация класса Dictionary ==================================

Dictionary::Dictionary()
{
}

Dictionary::~Dictionary()
{
}

void Dictionary::addWord(string code, string word, uint freq)
{
    DictionaryItem newItem;
    newItem.word = word;
    newItem.freq = freq;

    QueuesMap::iterator mapIter = _queuesMap.lower_bound(code);
    if (mapIter != _queuesMap.end() && !_queuesMap.key_comp()(code, mapIter->first))
    {
        // очередь на данный код уже существует - добавляем в ее конец
        WordsQueue *queue = &mapIter->second;
        WordsQueue::iterator queueIter = queue->begin();
        while (true)
        {
            if (queueIter == queue->end() || queueIter->freq < freq)
            {
                queue->insert(queueIter, newItem);
                break;
            }
            queueIter++;
        }
    }
    else
    {
        // очередь на данный код отсутствует - создаем ее
        WordsQueue queue;
        queue.push_back(newItem);
        pair<string, WordsQueue> newPair(code, queue);
        _queuesMap.insert(mapIter, newPair);
    }
}

string Dictionary::selectWord(string code, uint order)
{
    try
    {
        QueuesMap::iterator mapIter = _queuesMap.find(code);
        WordsQueue *queue = &mapIter->second;
        WordsQueue::iterator iter = queue->begin();
        for (uint i = 0; i < order; i++)
        {
            iter++;
        }
        DictionaryItem item = *iter;
        queue->erase(iter);
        item.freq++;

        // перемещаем слово с учетом нового приоритета и факта выбора
        if (queue->empty())
        {
            queue->push_back(item);
        }
        else
        {
            bool inserted = false;
            for (iter = queue->begin(); iter != queue->end(); iter++)
            {
                if (iter->freq <= item.freq)
                {
                    queue->insert(iter, item);
                    inserted = true;
                    break;
                }
            }
            if (!inserted)
                queue->push_back(item);
        }
        return item.word;
    }
    catch (exception exc)
    {
        return "";
    }
}

//======== Объявление класса Phone ===========================================

class Phone
{
public:
    Phone(uint wordsCount);
    virtual ~Phone();

    void addDictWord(string word, uint freq);
    string defineMessage(string input);

private:
    void finishWord(ostringstream& stream, string& code, uint& starsPressed);
    string getWordCode(string word);
    char getSymbolCode(char symbol);

    char const static *const _punctSigns;
    uint _wordsCount;
    Dictionary *_dict;
};

//=========== Реализация класса Phone ========================================

char const *const Phone::_punctSigns = ".,?";

Phone::Phone(uint wordsCount) : _wordsCount(wordsCount)
{
    _dict = new Dictionary();
}

Phone::~Phone()
{
    delete _dict;
}

void Phone::addDictWord(string word, uint freq)
{
    string code = getWordCode(word);
    _dict->addWord(code, word, freq);
}

string Phone::defineMessage(string input)
{
    ostringstream result;
    string curCode;
    uint starsPressed = 0;
    for (string::iterator iter = input.begin(); iter != input.end(); iter++)
    {
        if (*iter == '*')
        {
            starsPressed++;
        }
        else if (*iter == ' ')
        {
            finishWord(result, curCode, starsPressed);
            result << ' ';
        }
        else if (*iter == '1')
        {
            finishWord(result, curCode, starsPressed);
            curCode.push_back(*iter);
        }
        else
        {
            if (curCode == "1")
            {
                finishWord(result, curCode, starsPressed);
            }
            curCode.push_back(*iter);
        }
    }
    finishWord(result, curCode, starsPressed);
    return result.str();
}

void Phone::finishWord(ostringstream& stream, string& code, uint& starsPressed)
{
    if (!code.empty())
    {
        if (code == "1")
        {
            char sign = _punctSigns[starsPressed];
            stream << sign;
        }
        else
        {
            string selectedWord = _dict->selectWord(code, starsPressed);
            stream << selectedWord;
        }
        starsPressed = 0;
        code.clear();
    }
}

string Phone::getWordCode(string word)
{
    string wordCode;
    for (uint i = 0; i < word.size(); i++)
    {
        char code = getSymbolCode(word[i]);
        wordCode.push_back(code);
    }
    return wordCode;
}

char Phone::getSymbolCode(char symbol)
{
    uint alphabetIndex = symbol - 'a';
    if (symbol >= 's')
        alphabetIndex--;
    if (symbol >= 'y')
        alphabetIndex--;
    uint code = alphabetIndex / 3;
    return code + 2 + '0';
}

//============= Главная функция программы ==================================

int main(int argc, char** argv)
{
    uint wordsCount = 0;
    cin >> wordsCount;

    Phone *phone = new Phone(wordsCount);
    for (uint i = 0; i < wordsCount; i++)
    {
        string word("");
        uint freq = 0;
        cin >> word >> freq;
        phone->addDictWord(word, freq);
    }
    cin.ignore(); // пропускаем символ перехода на новую строку

    string input;
    getline(cin, input);
    
    string message = phone->defineMessage(input);
    cout << message << endl;

    delete phone;
    return 0;
}

