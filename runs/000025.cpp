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

    // ["86"] ("to", 1)
    // ["23"] ("ad", 2) ("be", 1)
    // ["67"] ("or", 5)
    std::map<std::string, std::list<word> > words;

    static char char2digit(char ch);

public:
    dictionary();
    void get(std::istream &in=std::cin);
    static std::string word2number(const std::string &word);
    void print();
    std::string get_word(std::string number, int aster_count);
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
    words["1"].push_back(word(".", 2));
    words["1"].push_back(word(",", 1));
    words["1"].push_back(word("?", 0));
}

char dictionary::char2digit(char ch)
{
    if (ispunct(ch)) return '0' + 1;
    if (ch <= 'r')   return '0' + (ch - 'a') / 3 + 2;
    if (ch == 's')   return '0' + 7;
    if (ch <= 'v')   return '0' + 8;
    return '0' + 9;
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

        std::list<word>::iterator place =
            std::find_if(plist->begin(),
                         plist->end(),
                         counters_less(wrd)
                         );
        plist->insert(place, wrd);
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

std::string dictionary::word2number(const std::string &word)
{
    std::string result;
    result.reserve(word.size());

    for (size_t i = 0; i < word.size(); ++i)
    {
        result += char2digit(word[i]);
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

        std::cout << get_word(str_number, aster_count);

        while ( (begin != str.end()) && (isspace(*begin)) )
        {
            std::cout << *begin++;
        }
    }
}

std::string dictionary::get_word(std::string number, int aster_count)
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

    if (number != "1")
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

