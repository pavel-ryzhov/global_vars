#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <cctype>

using std::map;
using std::multimap;
using std::pair;
using std::string;
using std::cin;
using std::cout;
using std::stringstream;
using std::noskipws;
using std::endl;
using std::iscntrl;

string translate(string word)
{
    string result(word);
    for (int i = 0; i < word.length(); i++) {
        if (word [i] < 's') {
            result[i] = '2' + (word[i] - 'a') / 3;
        }
        else if (word[i] < 'z') {
            result[i] = '7' + (word[i] - 'q') / 3;
        }
        else {
            result[i] = '9';
        }
    }
    return result;
}

class T9
{
private:
    typedef map<string, multimap<int, string, std::greater<int> > > dictionary_t;
    dictionary_t dictionary_;
    bool punctuation_flag_;
    stringstream sequence_;
    int stars_;
    stringstream message_;
    string punctuation_;

    void ProcessWord();
public:
    T9();
    ~T9();
    void AddWord(string word, int priority);
    void Feed(char c);
    string Message();

    void Print();
};

T9::T9(): message_(stringstream::out), sequence_(stringstream::out), stars_(0), punctuation_flag_(false)
{
    punctuation_ = ".,?";
}

T9::~T9()
{}

void T9::AddWord(string word, int priority)
{
    dictionary_t::mapped_type &cell = dictionary_[translate(word)];
    cell.insert(cell.upper_bound(priority), pair<int, string>(priority, word));
}

void T9::ProcessWord()
{
    if (sequence_.str() == "1") {
        message_ << punctuation_[stars_];
    }
    else if (sequence_.str() == "") {
        return;
    }
    else {
        dictionary_t::mapped_type &cell = dictionary_[sequence_.str()];
        dictionary_t::mapped_type::iterator wi = cell.begin();
        for (int i = 0; i < stars_; i++) {
            wi++;
        }
        string &word = wi->second;
        int priority = wi->first + 1;
        cell.insert(cell.lower_bound(priority), pair<int, string>(priority, word));
        cell.erase(wi);
        message_ << word;
    }
    sequence_.str("");
    stars_ = 0;
}

void T9::Feed(char c)
{
    if (c == '*') {
        stars_++;
    }
    else if (c == ' ') {
        ProcessWord();
        message_ << c;
    }
    else if (c == '1') {
        ProcessWord();
        sequence_ << c;
        punctuation_flag_ = true;
    }
    else if (c == '\0') {
        ProcessWord();
    }
    else if ('2' <= c && c <= '9') {
        if (punctuation_flag_)
            ProcessWord();
        sequence_ << c;
        punctuation_flag_ = false;
    }
}

string T9::Message()
{
    return message_.str();
}

int main()
{
//  cout << translate("abcdefghijklmnopqrstuvwxyz") << endl;

    int n;
    cin >> n;

    T9 automaton;

    string word;
    int priority;
    for (int i = 0; i < n; i++) {
        cin >> word >> priority;
        automaton.AddWord(word, priority);
    }

    char c;
    cin >> noskipws >> c;
    do {
        automaton.Feed(c);
        cin >> noskipws >> c;
    } while (!cin.eof());

    automaton.Feed('\0');

    cout << automaton.Message() << endl;
}

