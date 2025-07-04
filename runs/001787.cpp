#include <string.h>
#include <iostream>
#include <string>
#include <map>
#include <list>

using namespace std;

//////////////////////////////////////////////////////////////////////////////
//  Class `T9Mode` implemenation.
//
//  This class is supposed to conversion a text encoded in T9
//  to human-readable text. Contains alphabet of human-readable letters
//  and dictionary to store human-readable words. Each word is corresponded
//  with its frequency of popularity. The higher frequnency, the more the
//  chances this word is returned if corresponding T9-code is provided.
//  T9-dictionary is represnted as a map of T9-codes to lists of correponding
//  human-readable words. New word is added to dictionary so that the human
//  word list would be sorted in a frequncy descendant order.
//  Main methods:
//  `addWord`  - add a new word to dictionary,
//  `getWord`  - get a human-readable word
//  `parse`    - parse a T9-text to human-readable one
//
//  Copyright 2010, Dima Rodionov
//////////////////////////////////////////////////////////////////////////


//  Human-readable word in T9-dictionary
struct DictWord {
    //  functions are needed for STL-List
    explicit DictWord() {frequency = -1;}
    DictWord(const string &s, int frequency) {
        this->s = s;
        this->frequency = frequency;
    }
    bool operator==(const DictWord &b) { return this->s == b.s; }

    string s;       //  human-readable word
    int frequency;  //  frequency of word
};


class T9Mode
{
public:
    T9Mode();
    ~T9Mode();

    void addWord(const string &word, int frequency);
    string getWord(const string &t9Word, int astCount = 0);
    string parse(const string &t9String);
    void clearDictionary() { dictionary.clear(); }
//private:
    void initializeAlphabet();

    //  it needs less than 255 chars but lookup is easier and faster
    char alphabet[255];
    map <string, list<DictWord> > dictionary;
};


T9Mode::T9Mode()
{
    initializeAlphabet();
    //dictionary.
}

T9Mode::~T9Mode() {
    clearDictionary();
}

//  Initializes alphabet
void T9Mode::initializeAlphabet() {
    alphabet['a'] = '2'; alphabet['b'] = '2'; alphabet['c'] = '2';
    alphabet['d'] = '3'; alphabet['e'] = '3'; alphabet['f'] = '3';
    alphabet['g'] = '4'; alphabet['h'] = '4'; alphabet['i'] = '4';
    alphabet['j'] = '5'; alphabet['k'] = '5'; alphabet['l'] = '5';
    alphabet['m'] = '6'; alphabet['n'] = '6'; alphabet['o'] = '6';
    alphabet['p'] = '7'; alphabet['q'] = '7'; alphabet['r'] = '7';
        alphabet['s'] = '7';
    alphabet['t'] = '8'; alphabet['u'] = '8'; alphabet['v'] = '8';
    alphabet['w'] = '9'; alphabet['x'] = '9'; alphabet['y'] = '9';
        alphabet['z'] = '9';
    alphabet['.'] = '1'; alphabet[','] = '1'; alphabet['?'] = '1';
}

//  Adds new word `w` to T9-`dictionary`. Codes the word with T9-`alphabet`
//  and tries to find the code in `dictionary`. If it is found then appends
//  `w` to existing human word list, otherwise creates new one.
//  Sets frequency of new word to `frequency`.
//  `word`      - human-readable word to add,
//  `frequency` - frequency of new word.
void T9Mode::addWord(const string &word, int frequency)
{
    list<DictWord> newList;
    string::iterator j;
    string t9Word(word);

    //  Convert `w` with T9 `alphabet`.
    j = t9Word.begin();
    for (string::const_iterator i = word.begin(); i != word.end(); i++, j++)
        *j = alphabet[*i];

    map<string, list<DictWord > >::iterator i = dictionary.find(t9Word);

    //  `w` is a new word so expand `dictionary`.
    if (i == dictionary.end()) {
        newList.push_back(DictWord(word, frequency));
        dictionary[t9Word] = newList;

        return;
    }

    //  Search the appropriate place for `w`. All preceding words
    //  should have a larger frequency and be lexicographically less.
    list<DictWord>::iterator itr = (*i).second.begin();
    for ( ; itr != (*i).second.end() && itr->frequency > frequency; itr++);
        /* VOID */

    for ( ; itr != (*i).second.end() &&
          itr->s < word && frequency == itr->frequency; itr++);
        /* VOID */

    (*i).second.insert(itr, DictWord(word, frequency));
}


//  Gets word in T9-encoding and returns the correponding
//  human-readable word with the highest frequency. Increases
//  frequency of found word and change the order of a human word list
//  that corresponds `t9Word`.
//  `t9Word`   - T9-encoded word
//  `askCOunt` - count of asterisks to select the word
string T9Mode::getWord(const string &t9Word, int astCount)
{
    string humanWord;

    if (astCount < 0)

        return string("");

    //  Find the human word list of the `t9Word` in `dictionary`.
    map<string, list<DictWord> >::iterator itr = dictionary.find(t9Word);
    if (itr == dictionary.end())

        return string("");

    //  Pick the word offseted by `astCount` in the list.
    list<DictWord>::iterator i = (*itr).second.begin(), j;
    for (;i != (*itr).second.end() && astCount > 0; astCount--, i++);
        /* VOID */

    //  No such word found.
    if (i == (*itr).second.end())

        return string("");

    humanWord = i->s;
    i->frequency++;

    //  Find the first word in the list with the same frequency.
    for(j = i; j != (*itr).second.begin() &&
            i->frequency >= j->frequency; j--);
        /* VOID */

    //  Change the order of words in the list
    if (i != j) {
        if (j == (*itr).second.begin() && i->frequency >= j->frequency)
            (*itr).second.insert(j, *i);
        else {
            j++;
            (*itr).second.insert(j, *i);
        }
        (*itr).second.erase(i);
    }

    return humanWord;
}


//  Parses `t9String` which consists of digits, asterisks and whitespaces
//  and returns human-readable string
string T9Mode::parse(const string &t9String)
{
    char *t9str = new char[t9String.length()],    //  raw copy of input string
         *humstr = new char[t9String.length()],   //  raw string for output
         *word = new char[21];                    //  container for tokens
    char *wordBase = word,
         *humstrBase = humstr,
         *t9strBase = t9str;
    int acount;             //  asterisk count
    string humanString;     //  wrapper to return `humstr`

    strcpy(t9str, t9String.c_str());
    memset(humstr, '\0', t9String.length());

    while (*t9str != '\0') {
        switch (*t9str) {

        //  Stop sign
        case '1' : {

            t9str++;
            for (acount = 0; *t9str == '*'; t9str++, acount++) ;
                /* VOID */
            switch(acount % 3) {
            case 0: *humstr = '.'; break;
            case 1: *humstr = ','; break;
            case 2: *humstr = '?'; break;
            }
            humstr++;
            break;
        }

        //  Whitespace
        case ' ' : { *humstr++ = *t9str++; break; }

        //  Char digit from range ('2'..'9')
        default: {

            for (word = wordBase; *t9str >= '2' && *t9str <= '9';
                 word++, t9str++)
            {
                *word = *t9str;
            }

            *word = '\0';

            for (acount = 0; *t9str == '*'; t9str++, acount++) ;
                /* VOID */
            strcat(humstr, getWord(string(wordBase), acount).c_str());
            humstr += strlen(wordBase);
        }
        }
    }

    humanString = humstrBase;

    delete wordBase, humstrBase, t9strBase;
    return humanString;
}
////////////////////////////////////////////////////////////////


int main(int argc, char *argv[])
{
    T9Mode t9;
    int n;                          //  word count
    int f;                          //  frequency of word
    char w[21];                     //  word
    string t9str;                   //  T9 string

    //  read word count
    cin >> n;

    //  read words
    while (n--) {
        cin >> w >> f;
        t9.addWord(string(w), f);
    }

    //  read T9-string (the whole line till '\n' is encountered)
    cin.get();
    getline(cin, t9str);

    cout << t9.parse(t9str) << endl;

    return 0;
}
