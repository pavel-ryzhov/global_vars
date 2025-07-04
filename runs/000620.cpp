#include <map>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

#define HT_SIZE 0x1000

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
    std::vector<std::string>   words[HT_SIZE];
    std::vector<list_word>     list_words[HT_SIZE];

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
    // ["86"] ("to", 1)
    // ["23"] ("ad", 2) ("be", 1)
    // ["67"] ("or", 5)
    hash_table words;

    static char char2digit(char ch);

public:
    dictionary();
    void get_words(std::istream &in=std::cin);
    static void word2number(const std::string &word, std::string *res);
    void translate();
    void print_word(const std::string &number, int aster_count);
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

list_word &hash_table::operator[](const std::string &str)
{
    int hsh = hash(str) % HT_SIZE;
    std::vector<list_word> *pllw = &list_words[hsh];
    const std::vector<std::string> *pwlist = &words[hsh];
    if (pllw->empty()) add(str);

    std::vector<list_word>::iterator res_iter = pllw->begin();
    std::vector<std::string>::const_iterator str_list_iter = pwlist->begin();

    while (str_list_iter != pwlist->end()  &&  *str_list_iter != str)
    {
        ++res_iter;
        ++str_list_iter;
    }

    if (str_list_iter == pwlist->end())
    {
        add(str);
        return pllw->back();
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

void dictionary::get_words(std::istream &in)
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
        std::string w2n;
        word2number(wd, &w2n);
        std::list<word> *plist = &words[w2n];

        std::list<word>::iterator place =
            std::find_if(plist->begin(),
                         plist->end(),
                         counters_less(wrd)
                         );
        plist->insert(place, wrd);
    }

    in.get();
}

void dictionary::word2number(const std::string &word, std::string *res)
{
    res->clear();
    res->reserve(word.size());

    for (size_t i = 0; i < word.size(); ++i)
    {
        *res += char2digit(word[i]);
    }
}

bool delim(char c)
{
    return (c == ' ') || (c == '*') ||
           (c == '1') || (c == '\n');
}

void dictionary::translate()
{
    register char ch = std::cin.get();

    while (ch != '\n')
    {
        register std::string str_number;
        str_number.reserve(20);

        while (!delim(ch))
        {
            str_number += ch;
            ch = std::cin.get();
        }

        if (str_number.empty())
        {
            str_number = "1";
            ch = std::cin.get();
        }

        int aster_count = 0; 

        while (ch == '*')
        {
            ch = std::cin.get();
            ++aster_count;
        }

        print_word(str_number, aster_count);

        while ( (ch != '\n') && (isspace(ch)) )
        {
            std::cout << ch;
            ch = std::cin.get();
        }
    }
}

void dictionary::print_word(const std::string &number, int aster_count)
{
    std::list<word> *plist = &words[number];
    std::list<word>::iterator it = plist->begin();

    while (aster_count-- != 0)
    {
        ++it;
        if (it == plist->end())
            it = plist->begin();
    }

    if (number == "1")
    {
        std::cout << it->str;
        return;
    }

    /////////////////////
    // 3 3 2 2 1 1     //
    //         ^       //
    //         it -> 2 //
    //                 //
    // 3 3 2 2 2 1     //
    //    ^____|       //
    /////////////////////

    const int cntr = ++it->counter;

    typedef  std::list<word>::iterator  iter;
    iter place;

    place = it;
    for (iter itf = it; ; --itf)
    {
        if (itf->counter > cntr)
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

    std::cout << place->str;
}


int main()
{
    dictionary dict;
    dict.get_words();
    dict.translate();
}

