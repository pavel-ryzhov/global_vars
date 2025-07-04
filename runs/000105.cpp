#include <map>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <ctime>

#define HT_SIZE 0x1000
clock_t start;

unsigned hash(const std::string &str)
{
    if (str == "1") return 0;

    unsigned res = 0;
    for (size_t i = 1; i < str.size(); ++i)
        res += (res<<1)^str[i];

    if (res == 0) return str[0];
    return res;
}

struct word
{
    std::string str;
    int counter;

    word()
        : counter(0)
        {
        }

    word(const std::string &str, int counter)
        : str(str), counter(counter)
        {
        }
};

typedef std::list<word> list_word;

class hash_table
{
    std::list<std::string>   words[HT_SIZE];
    std::list<list_word>     list_words[HT_SIZE];

    void add(std::string str)
        {
            int hsh = hash(str) % HT_SIZE;
            words[hsh].push_back(str);
            list_words[hsh].push_back(list_word());
        }
public:
    list_word &operator[](const std::string &str);
};

class dictionary
{
    std::string str;

    // ["86"] ("to", 1)
    // ["23"] ("ad", 2) ("be", 1)
    // ["67"] ("or", 5)
    hash_table words;

    static char char2digit(char ch);

public:
    dictionary();
    void get(std::istream &in=std::cin);
    static std::string word2number(const std::string &word);
    void print();
    const std::string *get_word(std::string number, int aster_count);
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

struct counters_greater
{
    int counter;

    counters_greater(const word &wrd1)
        : counter(wrd1.counter)
        {
        }

    bool operator()(const word &wrd2) const
        {
            return wrd2.counter > counter;
        }
};

list_word &hash_table::operator[](const std::string &str)
{
    int hsh = hash(str) % HT_SIZE;
    std::list<list_word> *pllw = &list_words[hsh];
    const std::list<std::string> *pwlist = &words[hsh];
    if (pllw->empty()) add(str);

    std::list<list_word>::iterator res_iter = pllw->begin();
    std::list<std::string>::const_iterator str_list_iter = pwlist->begin();

    while (str_list_iter != pwlist->end()  &&  *str_list_iter != str)
    {
        ++res_iter;
        ++str_list_iter;
    }

    if (str_list_iter == pwlist->end())
    {
        add(str);
        return *--pllw->end();
    }

    return *res_iter;
}

dictionary::dictionary()
{
    words["1"].push_back(word(".", 2));
    words["1"].push_back(word(",", 1));
    words["1"].push_back(word("?", 0));
}

char dictionary::char2digit(char ch)
{
    if (ispunct(ch)) return '1';
    if (ch <= 'r')   return '0' + (ch - 'a') / 3 + 2;
    if (ch == 's')   return '7';
    if (ch <= 'v')   return '8';
    return '9';
}

void dictionary::get(std::istream &in)
{
    int words_count;
    in >> words_count;

    bool mm = words_count > 90000;

    std::string wd;
    int ct;

    for (int i = 0; i < words_count; ++i)
    {
        in >> wd;
        in >> ct;

        if (mm && i%10000==0)
        {
            if (i == 30000) break;
            std::cout << i/10000 << " ";
        }

        word wrd = word(wd, ct);
        std::list<word> *plist = &words[word2number(wd)];

        std::list<word>::iterator place =
            std::find_if(plist->begin(),
                         plist->end(),
                         counters_less(wrd)
                         );
        plist->insert(place, wrd);
    }

    if (mm)
        exit(1);

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

        std::cout << *get_word(str_number, aster_count);

        while ( (begin != str.end()) && (isspace(*begin)) )
        {
            std::cout << *begin++;
        }
    }
}

const std::string *dictionary::get_word(std::string number, int aster_count)
{
    std::list<word> *plist = &words[number];
    std::list<word>::iterator it = plist->begin();

    while (aster_count-- != 0)
    {
        ++it;
        if (it == plist->end())
            it = plist->begin();
    }

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

        typedef  std::list<word>::iterator  iter;
        iter place;
        counters_greater cge(*it);

        for (iter itf = it; ; --itf)
        {
            if (cge(*itf))
            {
                place = ++itf;
                break;
            }

            if (itf == plist->begin())
            {
                place = plist->begin();
                break;
            }
        }

        if (it != place)
        {
            place = plist->insert(place, word());
            std::iter_swap(it, place);
            plist->erase(it);
        }

        return &place->str;
    }

    return &it->str;
}


int main()
{
    start = clock();
    dictionary dict;
    dict.get();
    dict.print();
}

