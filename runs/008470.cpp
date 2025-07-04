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
    static long long n;
    long long number;
    std::string GiveWord(int stars);
    MyMap words;
    string code;
    void SetCode(const std::string &s);
    void NewNumber();
};
void VectorTreeItem::NewNumber()
{
    VectorTreeItem::n++;
    this->number = VectorTreeItem::n;
}

long long VectorTreeItem::n = 0;

class VectorTree : public vector<VectorTreeItem>
{
public:
    void SortByCodes();
    void ShowCodes();
    void ShowWords();
    void SortTrue();
    void CombineItems(VectorTree::iterator from, VectorTree::iterator to);
    bool FindInsert(const std::string &s, const std::string &word, int value);
};

bool VectorTree::FindInsert(const std::string &s, const std::string &word, int value)
{
    bool ret = false;
    VectorTree::iterator iter;
    for (iter = this->begin(); iter < this->end(); iter++)
    {
        if (iter->code == s)
        {

            std::pair<MyMap::iterator, MyMap::iterator> r;
            r = iter->words.equal_range(value);


            MyMap::iterator d;
            d = r.first;
            if (d != iter->words.begin())
                d--;

            iter->words.insert(d,std::pair<int, string>(value, word));


            ret = true;
            break;
        }
    }
    return ret;
}

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
void VectorWords::ShowAnswers()
{
    VectorWords::iterator iter;
    for (iter = this->begin(); iter < this->end(); iter++)
    {
        for (int i = 0; i < iter->spaces_before_word; i++)
            cout << " ";
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
    if ((s[0] >= '2') && (s[0] <= '9'))
    {
        i = 0;
        while (((s[i] >= '2') && (s[i] <= '9')) && (i < (int) s.length()))
        {
            s_new.insert(s_new.end(), s[i]);
            i++;
        }
        if (i < (int) s.length())
        {
            if (s[i] == '*')
            {
                int stars = 0;
                while ((s[i] == '*') && (i < (int) s.length()))
                {
                    stars++;
                    i++;
                }
                WordAnswer wa;
                wa.code = s_new;
                wa.spaces_before_word = spaces;
                wa.stars_after_word = stars;
                this->insert(end(),wa);
                if (i < (int) s.length())
                    AddDevideWord(s.substr(i,s.length()));
            }
            else
                if (s[i] == '1')
                {
                    WordAnswer wa;
                    wa.code = s_new;
                    wa.spaces_before_word = spaces;
                    this->insert(end(),wa);
                    AddDevideWord(s.substr(i,s.length()));
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
            this->insert(end(),wa);
            if (i < (int) s.length())
                AddDevideWord(s.substr(i, s.length()));
        }
    }

}




void VectorTreeItem::SetCode(const std::string &s)
{
    this->code.clear();
    for (int i = 0; i < (int) s.length(); i++)
    {
        this->code.insert(this->code.end(), (char) charButton(s[i]));
    }
}
std::string VectorTreeItem::GiveWord(int stars)
{


    string s;
    int v;
    MyMap::iterator map_iter, map_begin, map_end;

    map_end = this->words.end();
    map_begin = this->words.begin();
    map_iter = map_end;

    map_iter--;
    for (int i = 0; (i < stars) && (map_iter != map_begin); i++)
    {
        map_iter--;
    }

    s = map_iter->second;
    v = map_iter->first + 1;
    this->words.erase(map_iter);
    this->words.insert(pair<int, string>(v, s));
    return s;
}

bool sortVectorTreeByCodes(const VectorTreeItem &a, const VectorTreeItem &b)
{
    if (a.code != b.code)
        return (a.code < b.code);
    else
        return (a.number < b.number);
}
void VectorTree::CombineItems(VectorTree::iterator from, VectorTree::iterator to)
{
    if (from < to)
    {
        VectorTree::iterator iter, iter_to, iter_second;
        MyMap::iterator map;
        iter_to = to;
        iter_second = from;
        iter_second++;

        for (iter = from; iter < iter_to; iter_to--)
        {
            for (map = iter_second->words.begin(); map != iter_second->words.end(); map++)
            {
                std::pair<MyMap::iterator, MyMap::iterator> r;
                r = iter->words.equal_range(map->first);



                if (r.first->first == map->first)
                {

                    MyMap::iterator d;

                    d = r.second;
                    if (d != iter->words.end())
                        d++;

                    iter->words.insert(d,std::pair<int, string>(map->first, map->second));

                }
                else
                    iter->words.insert(iter->words.begin(),std::pair<int, string>(map->first, map->second));
                // вставить в правильно порядке!
            }
            this->erase(iter_second);
        }

    }
}

void VectorTree::SortTrue()
{
    if (this->size() > 1)
    {
        this->SortByCodes();
        VectorTree::iterator iter, iter_next;
        iter = this->begin();
        iter_next = iter;
        iter_next++;

        while (iter < this->end())
        {
            if (iter_next < this->end())
            {
                while ((iter->code == iter_next->code))
                {
                    iter_next++;
                    if (iter_next == this->end())
                        break;
                }
            }
            iter_next--;
            this->CombineItems(iter, iter_next);
            iter++;
            iter_next = iter;
        }
     }
}

void VectorTree::SortByCodes()
{
    std::sort(this->begin(), this->end(), sortVectorTreeByCodes);
}

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

void VectorTree::ShowCodes()
{
    VectorTree::iterator iter;
    for (iter = this->begin(); iter < this->end(); iter++)
    {
        cout  << iter->code <<"[";
        MyMap::iterator i;
        for (i = iter->words.begin(); i != iter->words.end(); i++)
        {
            cout <<"(" << i->second <<";"<<i->first <<";"<<iter->number <<")";
        }
        cout <<"] " << endl;
    }
}




void VectorWords::CreateAnswers(VectorTree &vtree)
{
    VectorTree::iterator tree_start, tree_end, tree_iter;
    tree_start = vtree.begin();
    tree_end = vtree.end();
    tree_iter = tree_start;

    VectorWords::iterator words_start, words_end, words_iter;
    words_start = this->begin();
    words_end = this->end();
    words_iter = words_start;



    while ((words_iter->code[0] == '1')&& (words_iter < words_end))
        words_iter++;
    while (words_iter < words_end)
    {
        if (words_iter->code == tree_iter->code)
        {
            words_iter->answer = tree_iter->GiveWord(words_iter->stars_after_word);
            words_iter++;
        }
        else
        {
            tree_iter++;
        }

    }
}



int main(int argc, char *argv[])
{
    try
    {
        VectorTreeItem vta;
        VectorTree *vtree = new VectorTree;

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
                vta.NewNumber();
                vta.words.clear();
                vta.words.insert(std::pair<int, string>(value, word));
                vtree->insert(vtree->end(), vta);
            }

        }

        getline(cin, word, '\n');




        // читаем строку, которую вбивает пользователь T9


        VectorWords *words = new VectorWords();
        int spaces = 0;
        while (!cin.eof())
        {
            getline(cin, word, ' ');
            if (word.empty())
                spaces++;
            else
            {
                std::string::iterator iter;
                iter = word.end();
                iter--;
                while (*iter == '\n')
                {
                    word.erase(iter);
                    iter--;
                }
                words->AddDevideWord(word, spaces);
                spaces = 1;
            }
        }

        // настраиваем словарь
       // vtree->SortByCodes();
        //vtree->ShowCodes();
        vtree->SortTrue();
       // vtree->ShowWords();
        // настраиваем строку

        words->SortByWords();

       // words->ShowWords();
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
