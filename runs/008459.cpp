#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <istream>
#include <exception>
#include <algorithm>
#include <vector>


const int buttons = 8;
const int filename_size = 1024;

using namespace std;

class MyException : public std::exception
{
private:
    std::string msg;
public :
    MyException() { msg = "Systax Error!"; }
    MyException(const std::string &s) { msg = s; }
    MyException(const MyException &rhs) { msg = rhs.msg;}
    virtual ~MyException() throw() {}
    std::string str() { return msg; }
};


class MyMap : public std::multimap<int,std::string>
{
public:
    MyMap();
    virtual ~MyMap();
    MyMap::iterator FindString(const std::string &word);
};



struct VectorTreeItem
{
    std::string GiveWord(const int &stars);
    MyMap words;
    string code;
    void SetCode(const std::string &s);
};


class VectorTree : public vector<VectorTreeItem>
{
public:
    void SortByCodes();
    void ShowCodes();
    void ShowWords();
    bool FindInsert(const std::string &s, const std::string &word,const int &value);
};


struct WordAnswer
{
    long long number;
    string code;
    int spaces_before_word;
    int stars_after_word;
    string answer;
    WordAnswer();
};



class VectorWords : public std::vector<WordAnswer>
{
public:
    void CreateAnswers(VectorTree &vtree);
    void ShowWords();
    void ShowAnswers();
    void SortByWords();
    void SortByNumbers();
    void AddDevideWord(const string &s, int spaces = 0);
};










using namespace std;

const int null = 0;
const int star = -1;
const int space = 1;

char charButton(const char &c);
int codeButton(const char &c);


void VectorTree::ShowWords()
{
    VectorTree::iterator iter;
    for (iter = this->begin(); iter < this->end(); iter++)
    {
        cout  << "CODE: " << iter->code <<";" << endl;
        MyMap::iterator i;
        for (i = iter->words.begin(); i != iter->words.end(); i++)
        {
            cout << i->second <<";"<<i->first<<endl;
        }
        cout <<"===================" << endl;
    }
}

void VectorWords::ShowWords()
{
    VectorWords::iterator iter;

    for (iter = this->begin(); iter < this->end(); iter++)
    {
        for (int i = 0; i < iter->spaces_before_word; i++)
            cout << " ";
        cout  << iter->code << "["<<iter->stars_after_word<<"]";
    }
    cout << endl;
}

void VectorTree::ShowCodes()
{
    VectorTree::iterator iter;
    for (iter = this->begin(); iter < this->end(); iter++)
    {
        cout  << iter->code <<"[";
        MyMap::iterator i;
        for (i = iter->words.begin(); i != iter->words.end(); i++)
        {
            cout <<"(" << i->second <<";"<<i->first <<")";
        }
        cout <<"] " << endl;
    }
}


//============= MyMap ================
MyMap::MyMap()
{
    //cerr << "Constr MyMap" << endl;
}
MyMap::~MyMap()
{
    //cerr << "Destr MyMap" << endl;
}
MyMap::iterator MyMap::FindString(const string &word)
{
    MyMap::iterator iter;
    for (iter = this->begin(); iter != this->end(); iter++)
    {
        if (iter->second == word)
            return iter;
    }
    return MyMap::end();
}
//============= MyMap =============end





//=============== Other ==============
char charButton(const char &c)
{
    if (((c >= 'A')&&(c <= 'C')) || ((c >= 'a')&&(c <= 'c')))
        return '2';
    if (((c >= 'D')&&(c <= 'F')) || ((c >= 'd')&&(c <= 'f')))
        return '3';
    if (((c >= 'G')&&(c <= 'I')) || ((c >= 'g')&&(c <= 'i')))
        return '4';
    if (((c >= 'J')&&(c <= 'L')) || ((c >= 'j')&&(c <= 'l')))
        return '5';
    if (((c >= 'M')&&(c <= 'O')) || ((c >= 'm')&&(c <= 'o')))
        return '6';
    if (((c >= 'P')&&(c <= 'S')) || ((c >= 'p')&&(c <= 's')))
        return '7';
    if (((c >= 'T')&&(c <= 'V')) || ((c >= 't')&&(c <= 'v')))
        return '8';
    if (((c >= 'W')&&(c <= 'Z')) || ((c >= 'w')&&(c <= 'z')))
        return '9';
    throw MyException();
}
int codeButton(const char &c)
{
    int r = c - '1' + 1;
    if ((c >= '1') && (c <= '9'))
        return r;
    if (c == '*')
        return star;
    throw MyException();
}
//=============== Other ===========end

WordAnswer::WordAnswer()
{
    static long long n = 0;
    n++;
    number = n;
    spaces_before_word = 0;
    stars_after_word = 0;
}

bool VectorTree::FindInsert(const std::string &s, const std::string &word, const int &value)
{
    bool ret = false;
    VectorTree::iterator iter;
    for (iter = this->begin(); iter < this->end(); iter++)
    {
        if (iter->code == s)
        {
            std::pair<MyMap::iterator, MyMap::iterator> iters;
            MyMap::iterator first;

            iters = iter->words.equal_range(value);
            first = iters.first;

            if (first != iter->words.begin())
                first--;

            iter->words.insert(first,std::pair<int, string>(value, word));

            ret = true;
            break;
        }
    }
    return ret;
}

bool sortWordAnswerByCodes(const WordAnswer &a, const WordAnswer &b)
{
    if (a.code != b.code)
        return (a.code < b.code);
    else
        return (a.number < b.number);
}

bool sortWordAnswerByNumbers(const WordAnswer &a, const WordAnswer &b)
{
    return (a.number < b.number);
}

void VectorWords::ShowAnswers()
{
    VectorWords::iterator iter;

    string sp;
    for (iter = this->begin(); iter < this->end(); iter++)
    {
        for (int i = 0; i < iter->spaces_before_word; i++)
            sp.append(" ");
        cout << sp;
        sp.clear();
        cout  << iter->answer;
    }
}

void VectorWords::SortByWords()
{
    std::sort(this->begin(), this->end(), sortWordAnswerByCodes);
}

void VectorWords::SortByNumbers()
{
    std::sort(this->begin(), this->end(), sortWordAnswerByNumbers);
}

void VectorWords::AddDevideWord(const string &s, int spaces)
{
    string s_new;
    int i = 0;
    int length_s = (int) s.length();
    if ((s[0] >= '2') && (s[0] <= '9'))
    {
        i = 0;
        while (((s[i] >= '2') && (s[i] <= '9')) && (i < length_s))
        {
            s_new.insert(s_new.end(), s[i]);
            i++;
        }
        if (i < length_s)
        {
            if (s[i] == '*')
            {
                int stars = 0;
                while ((s[i] == '*') && (i < length_s))
                {
                    stars++;
                    i++;
                }
                WordAnswer wa;
                wa.code = s_new;
                wa.spaces_before_word = spaces;
                wa.stars_after_word = stars;
                this->insert(end(), wa);
                if (i < length_s)
                    AddDevideWord(s.substr(i, length_s));
            }
            else
                if (s[i] == '1')
                {
                    WordAnswer wa;
                    wa.code = s_new;
                    wa.spaces_before_word = spaces;
                    this->insert(end(), wa);
                    AddDevideWord(s.substr(i, length_s));
                }
        }
        else
        {
            WordAnswer wa;
            wa.code = s_new;
            wa.spaces_before_word = spaces;
            this->insert(end(),wa);
        }

    }
    else
    {
        if (s[0] == '1')
        {
            string s_answer;
            i = 0;
            int stars = -1;

            while (((s[i] == '1')||(s[i] == '*'))&&(i < (int) s.length()))
            {
                if (s[i] == '1')
                {
                    switch (stars)
                    {
                    case -1:
                        break;
                    case 0:
                        s_answer.insert(s_answer.end(),'.');
                        break;
                    case 1:
                        s_answer.insert(s_answer.end(),',');
                        break;
                    default:
                        s_answer.insert(s_answer.end(),'?');
                        break;
                    }
                    stars = 0;
                }
                else
                    stars++;
                s_new.insert(s_new.end(), s[i]);
                i++;
            }
            switch (stars)
            {
            case -1:
                break;
            case 0:
                s_answer.insert(s_answer.end(),'.');
                break;
            case 1:
                s_answer.insert(s_answer.end(),',');
                break;
            default:
                s_answer.insert(s_answer.end(),'?');
                break;
            }
            WordAnswer wa;
            wa.code = s_new;
            wa.answer = s_answer;
            wa.spaces_before_word = spaces;
            this->insert(end(), wa);
            if (i < length_s)
                AddDevideWord(s.substr(i, length_s));
        }
    }

}

void VectorTreeItem::SetCode(const std::string &s)
{
    this->code.clear();
    for (int i = 0; i < (int) s.length(); i++)
        this->code.insert(this->code.end(), (char) charButton(s[i]));
}

std::string VectorTreeItem::GiveWord(const int &stars)
{
    string s;
    int v;
    MyMap::iterator map_iter;

    map_iter = this->words.end();
    map_iter--;

    for (int i = 0; (i < stars) && (map_iter != this->words.begin()); i++)
        map_iter--;

    s = map_iter->second;
    v = map_iter->first + 1;
    this->words.erase(map_iter);
    this->words.insert(pair<int, string>(v, s));
    return s;
}

bool sortVectorTreeByCodes(const VectorTreeItem &a, const VectorTreeItem &b)
{
    return (a.code < b.code);
}

void VectorTree::SortByCodes()
{
    std::sort(this->begin(), this->end(), sortVectorTreeByCodes);
}

void VectorWords::CreateAnswers(VectorTree &vtree)
{
    VectorTree::iterator tree_iter;


    tree_iter =  vtree.begin();

    VectorWords::iterator words_start, words_iter;
    words_start = this->begin();

    words_iter = words_start;

    while ((words_iter->code[0] == '1')&&(words_iter < this->end()))
        words_iter++;
    while (words_iter != this->end())
    {
        if (words_iter->code == tree_iter->code)
        {
            words_iter->answer = tree_iter->GiveWord(words_iter->stars_after_word);
            words_iter++;
        }
        else
            tree_iter++;
    }
}



int main(int argc, char *argv[])
{
    try
    {

        VectorTreeItem vta;
        VectorTree *vtree = new VectorTree;
        VectorWords *words = new VectorWords();
        int spaces = 0;
        int number_words;
        int value;
        string word;
        bool isfind;

        // читаем список слов
        cin >> number_words;
        for (; number_words > 0; number_words--)
        {
            cin >> word;
            cin >> value;
            vta.SetCode(word);
            isfind = vtree->FindInsert(vta.code, word, value);
            if (!isfind)
            {
                vta.words.clear();
                vta.words.insert(std::pair<int, string>(value, word));
                vtree->insert(vtree->end(), vta);
            }
        }
        getline(cin, word, '\n');



        // читаем строку, которую вбивает пользователь T9
        while (!cin.eof())
        {
            getline(cin, word, ' ');
            if (word.empty())
                spaces++;
            else
            {
                words->AddDevideWord(word, spaces);
                spaces = 1;
            }
        }

        // настраиваем словарь
        if (vtree->size() > 1)
            vtree->SortByCodes();
        // vtree->ShowWords();
        // настраиваем строку
        words->SortByWords();
        words->CreateAnswers(*vtree);
        words->SortByNumbers();
        words->ShowAnswers();


    }
    catch (MyException ex)
    {
        cerr << ex.str() << endl;
    }
    catch (...)
    {
        cerr << "Unknown Error!" << endl;
    }
    return 0;
}
