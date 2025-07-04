#include <map>
#include <list>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <iostream>

#define HT_SIZE 0x1000

unsigned hash(const char *s_beg, const char *s_end)
{
    if (*s_beg == '1') return 0;

    unsigned res = 0;
    while (s_beg != s_end)
        res += (res<<1)^(*s_beg++);

    if (res == 0) return *s_beg;
    return res;
}

unsigned hash(const char *str)
{
    return hash(str, str+strlen(str));
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

    void add(const char *str)
        {
            int hsh = hash(str) % HT_SIZE;
            words[hsh].push_back(str);
            list_words[hsh].push_back(list_word());
        }
public:
    list_word &operator[](const char *str);
    list_word &operator()(const char *s_beg, const char *s_end);
};

class dictionary
{
    char str[0x20000];

    // ["86"] ("to", 1)
    // ["23"] ("ad", 2) ("be", 1)
    // ["67"] ("or", 5)
    hash_table words;

    static char char2digit(char ch);

public:
    dictionary();
    void get(std::istream &in=std::cin);
    static void word2number(const std::string &word, std::string *number);
    void print();
    const std::string *get_word(const char *s_beg, const char *s_end, int aster_count);
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

list_word &hash_table::operator[](const char *str)
{
    return operator()(str, str+strlen(str));
}

list_word &hash_table::operator()(const char *s_beg, const char *s_end)
{
    int hsh = hash(s_beg, s_end) % HT_SIZE;
    std::list<list_word> *pllw = &list_words[hsh];
    const std::list<std::string> *pwlist = &words[hsh];
    if (pllw->empty()) add(std::string(s_beg, s_end).c_str());

    std::list<list_word>::iterator res_iter = pllw->begin();
    std::list<std::string>::const_iterator str_list_iter = pwlist->begin();

    std::list<std::string>::const_iterator rend = pwlist->end(); 
    while (str_list_iter != rend  &&  /**str_list_iter != str*/ !std::equal(s_beg, s_end, str_list_iter->begin()))
    {
        ++res_iter;
        ++str_list_iter;
    }

    if (str_list_iter == pwlist->end())
    {
        add(std::string(s_beg, s_end).c_str());
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

    std::string wd;
    int ct;

    for (int i = 0; i < words_count; ++i)
    {
        in >> wd;
        in >> ct;

        word wrd = word(wd, ct);
        std::string number;
        word2number(wd, &number);
        std::list<word> *plist = &words[number.c_str()];

        std::list<word>::iterator place =
            std::find_if(plist->begin(),
                         plist->end(),
                         counters_less(wrd)
                         );
        plist->insert(place, wrd);
    }

    in.get();
    in.getline(str, 0x20000);
}

void dictionary::word2number(const std::string &word, std::string *number)
{
    number->clear();
    number->reserve(word.size());

    for (size_t i = 0; i < word.size(); ++i)
    {
        *number += char2digit(word[i]);
    }
}

bool delim(char c)
{
    return (c == ' ') || (c == '*') ||
           (c == '1') || (c == '\0');
}

void dictionary::print()
{
    const char *beg = str;
    const char *end;
    const char *str_end = (str + strlen(str) + 1);
    const char *p;

    while (*beg)
    {
        end = std::find_if(beg, str_end, delim);
        if (*beg == '1') ++end;

        int aster_count = 0; 

        p = end;
        while (*p && *p == '*')
        {
            ++p;
            ++aster_count;
        }

        std::cout << *get_word(beg, end, aster_count);

        while (*p && isspace(*p))
        {
            std::cout << *p++;
        }

        beg = p;
    }
}

const std::string *dictionary::get_word(const char *s_beg, const char *s_end, int aster_count)
{
    int x = hash(s_beg, s_end);
    std::list<word> *plist = &words(s_beg, s_end);
    std::list<word>::iterator it = plist->begin();

    while (aster_count-- != 0)
    {
        ++it;
        if (it == plist->end())
            it = plist->begin();
    }

    if (*s_beg != '1')
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

        place = it;
        for (iter itf = it; ; --itf)
        {
            if (it->counter < itf->counter)
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
    dictionary dict;
    dict.get();
    dict.print();
} 

