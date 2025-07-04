#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

struct word
{
    std::string str;
    int counter;
    int counter2;

    word(const std::string &str, int counter, int counter2=0)
        : str(str), counter(counter), counter2(counter2)
        {
        }

    bool operator>(const word &w)
        {
            return counter > w.counter;
        }

    bool operator>=(const word &w)
        {
            return counter >= w.counter;
        }
};

bool greater_with_counter2(const word &w1, const word &w2)
{
    if (w1.counter == w2.counter)
        return w1.counter2 > w2.counter2;
    return w1.counter > w2.counter;
}

class dictionary
{
    std::string str;

    // ["86"] ("to", 1)
    // ["23"] ("ad", 2) ("be", 1)
    // ["67"] ("or", 5)
    std::map<std::string, std::vector<word> > words;

    static char char2digit(char ch);

public:
    dictionary();
    void get(std::istream &in=std::cin);
    static std::string word2number(const std::string &word);
    void print();
    std::string get_word(const std::string &number, int aster_count);
};

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
    int ct, c2 = 0;

    for (int i = 0; i < words_count; ++i)
    {
        in >> wd;
        in >> ct;
        words[word2number(wd)].push_back(word(wd, ct, c2--));
    }

    typedef std::map<std::string, std::vector<word> >::iterator iter;
    for (iter it = words.begin(); it != words.end(); ++it)
    {
        std::sort(it->second.begin(), it->second.end(), greater_with_counter2);
    }

    in.get();
    str.clear();
    str.reserve(0x20000);

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

std::string dictionary::get_word(const std::string &number, int aster_count)
{
    std::vector<word> *pvect = &words[number];

    if (number == "1")
    {
        return (*pvect)[aster_count].str;
    }

    (*pvect)[aster_count].counter++;
    std::string result = (*pvect)[aster_count].str;

    for (int i = aster_count; i > 0; --i)
    {
        if ( (*pvect)[i] >= (*pvect)[i-1] )
        {
            std::swap( (*pvect)[i], (*pvect)[i-1] );
        }
        else
        {
            break;
        }
    }

    return result;
}

int main()
{
    dictionary dict;
    dict.get();
    dict.print();
}
