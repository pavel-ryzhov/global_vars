// Author: Govorov Igor, 2010
// Task C (T9)

#include <cstdlib>   // for EXIT_SUCCESS
#include <cstring>   // for strlen
#include <cassert>
#include <algorithm> // for stable_sort
#include <iostream>
#include <vector>
#include <map>
#include <string>


struct Entry
{
    int frequency;
    char *text;
};

struct descendingEntrySorter
{
    bool operator()(const Entry& lhs, const Entry& rhs)
    {
        return lhs.frequency > rhs.frequency;
    }
};

typedef std::vector<Entry> WordList;
typedef std::map<std::string, WordList> Dictionary;


std::string wordToKey(const char* word)
{
    std::string retVal;
    for(int i = 0, len = strlen(word); i < len; ++i)
    {
        // Можно конечно и через map или через заранее определённый массив.
        // Но и так работает быстро и понятно.
        switch(word[i])
        {
        case 'a': case 'b': case 'c': retVal += '2'; break;
        case 'd': case 'e': case 'f': retVal += '3'; break;
        case 'g': case 'h': case 'i': retVal += '4'; break;
        case 'j': case 'k': case 'l': retVal += '5'; break;
        case 'm': case 'n': case 'o': retVal += '6'; break;
        case 'p': case 'q': case 'r': case 's': retVal += '7'; break;
        case 't': case 'u': case 'v': retVal += '8'; break;
        case 'w': case 'x': case 'y': case 'z': retVal += '9'; break;
        default: assert(false);
        }
    }
    return retVal;
}

void buildDictionaryFromInput(Dictionary& d, std::istream& in)
{
    int N = 0;
    in >> N;
    assert(N >= 3);
    assert(N <= 50000);

    Entry e;
    for(int i = 0; i < N; ++i)
    {
        e.text = new char[20+1];
        in >> e.text >> e.frequency;
        const std::string key = wordToKey(e.text);
        Dictionary::iterator iter = d.find(key);
        if(iter == d.end())
        {
            // Не такого - создадим
            WordList words;
            words.push_back(e);
            d[key] = words;
        }
        else
        {
            // Старый список - добавляем
            (*iter).second.push_back(e);
        }
    }
    // Добавили элементы - теперь отсортируем их в каждом списке
    for(Dictionary::iterator i = d.begin(); i != d.end(); ++i)
    {
        std::stable_sort(i->second.begin(), i->second.end(), descendingEntrySorter());
    }
}

void cleanDictionary(Dictionary& d)
{
    for(Dictionary::iterator i = d.begin(); i != d.end(); ++i)
    {
        for(WordList::iterator w = i->second.begin(); w < i->second.end(); ++w)
        {
            delete [] w->text;
        }
    }
    d.clear();
}

#if 0
void printDictionary(Dictionary & dictionary)
{
    for(Dictionary::iterator i = dictionary.begin(); i != dictionary.end(); ++i)
    {
        std::cout << (*i).first << ":";
        for(WordList::iterator w = i->second.begin(); w < i->second.end(); ++w)
        {
            std::cout << " " << w->text << '(' << w->frequency << ')';
        }
        std::cout << std::endl;
    }
}
#endif

enum State
{
    Whitespace,
    Word,
    Punctuation
};

enum CharacterType
{
    Character,
    Delimiter,
    Space,
    Asteriks,
    Finish
};

CharacterType classifyCharacter(char c)
{
    if(c == static_cast<char>(1)) return Finish;
    if(c == '1') return Delimiter;
    if(c == ' ') return Space;
    if(c == '*') return Asteriks;
    if(c >= '2' && c <= '9') return Character;
    assert(false);
}

void t9(std::istream& in, std::ostream& out)
{
    Dictionary dictionary;
    buildDictionaryFromInput(dictionary, in);

    std::string task;
    std::getline(in, task);
    if(task.empty())
    {
        // Не съели перевод строки с прошлого раза? Не беда, повторим.
        std::getline(in, task);
    }
    // Граничный финишный элемент
    task += static_cast<char>(1);

    State state = Whitespace;
    std::string currentWord;
    int shift = 0;
    const int numPunctuationTypes = 3;
    const char punctuationCharacters[numPunctuationTypes] = {'.',',','?'};

    for(size_t iChar = 0; iChar < task.size(); ++iChar)
    {
        switch(state)
        {
        case Whitespace:
            {
                switch(classifyCharacter(task[iChar]))
                {
                case Character:
                    {
                        state = Word;
                        currentWord = task[iChar];
                        break;
                    }
                case Delimiter:
                    {
                        state = Punctuation;
                        break;
                    }
                case Space:
                    {
                        out << task[iChar];
                        break;
                    }
                case Asteriks:
                    {
                        assert(false);
                    }
                case Finish: ;
                }
                break;
            }
        case Word:
            {
                switch(classifyCharacter(task[iChar]))
                {
                case Character:
                    {
                        currentWord += task[iChar];
                        break;
                    }
                case Delimiter:
                case Finish:
                case Space:
                    {
                        WordList &wl = dictionary[currentWord];
                        size_t idx = shift % wl.size();
                        out << wl.at(idx).text << std::flush;
                        wl[idx].frequency++;
                        if(wl.size() != 0)
                        {
                            // Двигаем в нужную позицию
                            for(int iPos = idx-1; iPos >= 0; iPos--)
                            {
                                if(wl.at(iPos).frequency <= wl.at(idx).frequency)
                                {
                                    std::swap(wl.at(iPos), wl.at(idx));
                                    idx = iPos;
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }

                        shift = 0;
                        if(classifyCharacter(task[iChar]) == Finish)
                        {
                            break;
                        }
                        if(classifyCharacter(task[iChar]) == Delimiter)
                        {
                            state = Punctuation;
                        }
                        else
                        {
                            state = Whitespace;
                            out << task[iChar];
                        }
                        break;
                    }
                case Asteriks:
                    {
                        ++shift;
                        break;
                    }
                }
                break;
            }
        case Punctuation:
            {
                switch(classifyCharacter(task[iChar]))
                {
                case Character:
                    {
                        out << punctuationCharacters[shift % numPunctuationTypes];
                        shift = 0;
                        currentWord = task[iChar];
                        state = Word;
                        break;
                    }
                case Finish:
                case Delimiter:
                    {
                        out << punctuationCharacters[shift % numPunctuationTypes];
                        shift = 0;
                        break;
                    }
                case Space:
                    {
                        out << punctuationCharacters[shift % numPunctuationTypes];
                        shift = 0;
                        state = Whitespace;
                        out << task[iChar];
                        break;
                    }
                case Asteriks:
                    {
                        ++shift;
                        break;
                    }
                }
                break;
            }
        default: assert(false);
        }
    }
    cleanDictionary(dictionary);
}

int main(int /*argc*/, char * /*argv*/ [])
{
    t9(std::cin, std::cout);
    return EXIT_SUCCESS;
}
