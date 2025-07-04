#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
using namespace std;

struct word_freq
{
    word_freq(string x, unsigned int y) : word(x), freq(y) {}
    bool operator< (const word_freq &other) const
    {
        if (freq > other.freq) return true; else return false;
    }
    string word;
    unsigned int freq;
};

typedef vector< word_freq > word_freqArray;
typedef map< string, word_freqArray > key_wordsDict;
typedef pair<string, word_freqArray> key_wordPair;

class T9Processor
{
public:
    //Загружает из входных данных словарь и входную строку
    void readInput();
    //Обрабатывает строку и выводит ответ
    void processInput();
private:
    //возвращает цифровую комбинацию слова
    static string keyOfWord(string word);
    //вовзвращает истину, если цифра из [2-9], то есть используется для букв
    static bool isTextNum(char x);
    //добавляет выбранное слово к ответу и увеличивает его частоту
    void useWord(string num, unsigned int asteriskCount, bool spaceAfter);
    //добавляет выбранный знак препинания
    void usePunct(unsigned int asteriskCount, bool spaceAfter);
    enum states {reading_num, reading_punct, reading_space};
    states state;
    key_wordsDict dictionary;
    string input;
    string output;
};

void T9Processor::readInput()
{
    unsigned int dictionarySize = 0;
    scanf("%u", &dictionarySize);
    string word;
    char wordString[21];
    unsigned int count;
    for (unsigned int i = 0; i < dictionarySize; i++)
    {
        scanf("%s%u", wordString, &count);
        word.assign(wordString);
        pair<key_wordsDict::iterator, bool> newRecord =
            dictionary.insert(key_wordPair(keyOfWord(word), word_freqArray()));
        newRecord.first->second.push_back(word_freq(word, count));
    }
    for (key_wordsDict::iterator i = dictionary.begin(); i != dictionary.end(); i++)
    {
        stable_sort(i->second.begin(), i->second.end());
    }
    char inputString[100001];
    getchar();
    gets(inputString);
    input.assign(inputString);
}

void T9Processor::useWord(string num, unsigned int asteriskCount, bool spaceAfter)
{
    word_freqArray& wordsOfNum = dictionary[num];
    string word = wordsOfNum[asteriskCount].word;
    unsigned int nextCountFirstIndex = asteriskCount;
    unsigned int nextCount = ++wordsOfNum[asteriskCount].freq;
    for (int i = asteriskCount - 1; i >= 0; i--)
    {
        if (wordsOfNum[i].freq <= nextCount) nextCountFirstIndex = i; else break;
    }
    if (asteriskCount != nextCountFirstIndex)
    {
        wordsOfNum.erase(wordsOfNum.begin() + asteriskCount);
        wordsOfNum.insert(wordsOfNum.begin() + nextCountFirstIndex, word_freq(word, nextCount));
    }
    output += word;
    if (spaceAfter) output += ' ';
}

void T9Processor::usePunct(unsigned int asteriskCount, bool spaceAfter)
{
    static string punct = ".,?";
    output += punct[asteriskCount];
    if (spaceAfter) output += ' ';
}

bool T9Processor::isTextNum(char x)
{
    if ((x != ' ') && (x != '*') && (x != '1')) return true; else return false;
}

string T9Processor::keyOfWord(string word)
{
    string num = "";
    for (unsigned int i = 0; i < word.size(); i++)
    {
        if ((word[i]=='a') || (word[i]=='b') || (word[i]=='c'))
        {
            num += "2";
        }
        else if ((word[i]=='d') || (word[i]=='e') || (word[i]=='f'))
        {
            num += "3";
        }
        else if ((word[i]=='g') || (word[i]=='h') || (word[i]=='i'))
        {
            num += "4";
        }
        else if ((word[i]=='j') || (word[i]=='k') || (word[i]=='l'))
        {
            num += "5";
        }
        else if ((word[i]=='m') || (word[i]=='n') || (word[i]=='o'))
        {
            num += "6";
        }
        else if ((word[i]=='p') || (word[i]=='q') || (word[i]=='r') || (word[i]=='s'))
        {
            num += "7";
        }
        else if ((word[i]=='t') || (word[i]=='u') || (word[i]=='v'))
        {
            num += "8";
        }
        else if ((word[i]=='w') || (word[i]=='x') || (word[i]=='y') || (word[i]=='z'))
        {
            num += "9";
        }
    }
    return num;
}

void T9Processor::processInput()
{
    state = reading_space;
    string num = "";
    int asteriskCount = 0;
    for (unsigned int i = 0; i < input.size(); i++)
    {
        char currentChar = input[i];
        switch (state)
        {
        case reading_space:
            {
                if (isTextNum(currentChar))
                {
                    num.push_back(currentChar);
                    state = reading_num;
                }
                else if (currentChar == '1')
                {
                    state = reading_punct;
                }
                else if (currentChar == ' ')
                {
                    output.push_back(' ');
                }
                break;
            }
        case reading_num:
            {
                if (isTextNum(currentChar))
                {
                    num.push_back(currentChar);
                }
                else if (currentChar == '1')
                {
                    useWord(num, asteriskCount, false);
                    num = "";
                    asteriskCount = 0;
                    state = reading_punct;
                }
                else if (currentChar == ' ')
                {
                    useWord(num, asteriskCount, true);
                    num = "";
                    asteriskCount = 0;
                    state = reading_space;
                }
                else if (currentChar == '*')
                {
                    asteriskCount++;
                }
                break;
            }
        case reading_punct:
            {
                if (isTextNum(currentChar))
                {
                    usePunct(asteriskCount, false);
                    asteriskCount = 0;
                    state = reading_num;
                    num.push_back(currentChar);
                }
                else if (currentChar == '*')
                {
                    asteriskCount++;
                }
                else if (currentChar == ' ')
                {
                    usePunct(asteriskCount, true);
                    asteriskCount = 0;
                    state = reading_space;
                }
                else if (currentChar == '1')
                {
                    usePunct(asteriskCount, false);
                    asteriskCount = 0;
                }
            }
        }
    }
    switch (state)
        {
        case reading_num:
            {
                useWord(num, asteriskCount, false);
                break;
            }
        case reading_punct:
            {
                usePunct(asteriskCount, false);
            }
        }
    printf("%s", output.c_str());
}

int main()
{
    T9Processor t9;
    t9.readInput();
    t9.processInput();

    return 0;
}