#include <map>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

struct word
{
    std::string str;
    int counter;

    word(const std::string &str, int counter)
        : str(str), counter(counter)
        {
        }
};

class dictionary
{
    std::string str;

    // [86] (to,1)
    // [23] (ad,2) (be,1)
    // [67] (or,5)
    std::map<int, std::list<word> > words;

    static int char2digit(char ch);

public:
    dictionary();
    void get(std::istream &in=std::cin);
    static int word2number(const std::string &word);
    void print();
    std::string get_word(int number, int aster_count);
};

struct counters_less
{
    int counter;

    counters_less(const word &wrd1)
        : counter(wrd1.counter)
        {
        }

    bool operator()(const word &wrd2) const
        {
            return wrd2.counter < counter;
        }
};

struct counters_less_equal
{
    int counter;

    counters_less_equal(const word &wrd1)
        : counter(wrd1.counter)
        {
        }

    bool operator()(const word &wrd2) const
        {
            return wrd2.counter <= counter;
        }
};

dictionary::dictionary()
{
    words[1].push_back(word(".", 2));
    words[1].push_back(word(",", 1));
    words[1].push_back(word("?", 0));
}

int dictionary::char2digit(char ch)
{
    if (ispunct(ch)) return 1;
    if (ch <= 'r') return (ch - 'a') / 3 + 2;
    if (ch == 's') return 7;
    if (ch <= 'v') return 8;
    return 9;
}

void dictionary::get(std::istream &in)
{
    int words_count;
    in >> words_count;

    std::string wd;
    int ct;

    for (int i = 0; i < words_count; ++i)
    {
        in >> wd;
        in >> ct;

        word wrd = word(wd, ct);
        std::list<word> *plist = &words[word2number(wd)];


        if (plist->empty())
        {
            plist->push_back(wrd);
        }
        else
        {
            std::list<word>::iterator place =
                std::find_if(plist->begin(),
                             plist->end(),
                             counters_less(wrd)
                             );
            plist->insert(place, wrd);
        }
    }

    in.get();
    str.clear();

    for (;;)
    {
        char ch = in.get();
        if ( ch == '\n' || in.eof() ) break;
        str += ch;
    }
}

int dictionary::word2number(const std::string &word)
{
    int result = 0;
    int multiplier = 1;
    size_t i = word.size();

    while (i > 0)
    {
        result += ( char2digit(word[--i]) * multiplier );
        multiplier *= 10;
    }

    return result;
}

bool delim(char c)
{
    return (c == ' ') || (c == '*') ||
           (c == '1') || (c == '\0');
}

void dictionary::print()
{
    std::string::iterator begin = str.begin(), end;
    while (begin != str.end())
    {
        end = std::find_if(begin, str.end(), delim);
        if (*begin == '1') ++end;

        std::string str_number(begin, end);
        int aster_count = 0; 

        begin = end;
        while ( (begin != str.end()) && (*begin == '*') )
        {
            ++begin;
            ++aster_count;
        }

        std::cout << get_word(atoi(str_number.c_str()), aster_count);

        while ( (begin != str.end()) && (isspace(*begin)) )
        {
            std::cout << *begin++;
        }
    }
}

std::string dictionary::get_word(int number, int aster_count)
{
    std::list<word> *plist = &words[number];
    std::list<word>::iterator it = plist->begin();

    while (aster_count-- != 0)
    {
        ++it;
        if (it == plist->end())
            it = plist->begin();
    }

    std::string result = it->str;

    if (number != 1)
    {
        /////////////////////
        // 3 3 2 2 1 1     //
        //         ^       //
        //         it -> 2 //
        //                 //
        // 3 3 2 2 2 1     //
        //    ^____|       //
        /////////////////////

        ++it->counter;

        std::list<word>::iterator place =
            std::find_if(plist->begin(),
                         plist->end(),
                         counters_less_equal(*it)
                         );

        plist->insert(place, *it);
        plist->erase(it);
    }

    return result;
}


int main()
{
    dictionary dict;
    dict.get();
    dict.print();
}

