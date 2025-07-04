#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <istream>
#include <exception>
#include <algorithm>

const int buttons = 8;
const int filename_size = 1024;

class MyMap : public std::multimap<int,std::string>
{
public:
    MyMap();
    virtual ~MyMap();
    MyMap::iterator FindString(const std::string &word);
};

class Tree;

class Punctuation
{
    Tree *treePtr;
    MyMap words;
public:
    Punctuation();
    virtual ~Punctuation();
    void SetTreePtr(Tree *ptr);
    void WriteSince(const std::string &word, const int &level, const int &word_size);
    void WriteWord(int stars, int space = 0);
};

struct TreeItem
{
    TreeItem *pointers[buttons];
    // добавление в структуру указателя на объект дерева, которому принадлежит структура - плохое решение
    // лучше вариантов не придумал. хотя возможно что-то вроде шаблона проектирования singleton для класса Punctuation
    // тогда в этом классе хранился бы указатель на единственнй объект класса.
    // и доступ к объекту Tree.punc можно было бы получать через Punctuation.GetPointer();
    // вопрос остаётся открытым. как сделать грамотно - до сих пор не знаю.
    Tree *treePtr;
    MyMap words;
    TreeItem(Tree *ptr = 0);
    virtual ~TreeItem();
    void AddWord(const std::string &word, const int &value, const int &word_size, int level);
    void OfferAWord(const std::string &word, const int &word_size, int level);
    void WriteWord(int stars, int space = 0);
    void ShowAll();
    inline void ShowMe();
    void CreateNext(int num);

};

class Tree
{
    TreeItem node;
    char filename[filename_size];
    int out;
    std::ofstream fileoutstream;
public:
    Punctuation punc;
    Tree();
    virtual ~Tree();
    void SetCout();
    void SetFileOut(const char *s);
    void WriteOutstream(const std::string &s);
    void AddWord(const std::string &word, int);
    void OfferAWord(const std::string &word);
    void ShowTree();
};


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


using namespace std;

const int null = 0;
const int star = -1;
const int space = 1;

int charButton(const char &c);
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


//=========== Punctuation ============
Punctuation::Punctuation()
{
    //cerr << "Constr Punctuation" << endl;
    words.insert(std::pair<int,std::string>(1,"?"));
    words.insert(std::pair<int,std::string>(1,","));
    words.insert(std::pair<int,std::string>(1,"."));
}
Punctuation::~Punctuation()
{
    //cerr << "Destr Punctuation" << endl;
}
void Punctuation::SetTreePtr(Tree *ptr)
{
    treePtr = ptr;
}

// выводит знаки пунктуации для произвольной последовательности кнопок '1' и '*',
// которая начинается с '1'
void Punctuation::WriteSince(const string &word, const int &level, const int &word_size)
{
    int i = level;
    int stars  = 0;

    while (i < word_size)
    {
        int num_letter = codeButton(word[i]);
        if (num_letter == 1)
        {
            if (i == word_size - 1) // если это последний символ example: "come1"
            {
                WriteWord(stars, space);
            }
            else
            {
                int j;
                for (j = i + 1; (j < word_size)&&(codeButton(word[j]) == star) ; j++ )
                    stars++;
                if (j < word_size)
                    WriteWord(stars);
                else
                    WriteWord(stars, space);
                i = j - 1;
            }
        }
        else
        {
            if ((num_letter >= 2) && (num_letter <= 9))
            {
                treePtr->OfferAWord(word.substr(i,word.length()));
                break;
            }
        }
        i++;
    }
}
void Punctuation::WriteWord(int stars, int space)
{
    MyMap::iterator iter = words.end();
    iter--;
    for (int i = stars; (i > 0)&&(iter != words.begin()); i--)
    {
        iter--;
    }
    treePtr->WriteOutstream(iter->second);
    if (space != 0)
        treePtr->WriteOutstream(" ");
   // words.insert(std::pair<int,std::string>(iter->first + 1, iter->second));
   // words.erase(iter);
}
//=========== Punctuation =========end


//============ TreeItem ==============
TreeItem::TreeItem(Tree *ptr)
{
//    cout << "Constr TreeItem" << endl;
    for (int i = 0; i < buttons; i++)
        pointers[i] = null;
    treePtr = ptr;
}
TreeItem::~TreeItem()
{
    for (int i = 0; i < buttons; i++)
        if (pointers[i] != null)
            delete pointers[i];
//    cout << "Destr TreeItem" << endl;
}
// level - индекс следующей для разбора литеры. добавляем слово в структуру, если word[level] не существует.
// если word[level] существует, то перекидываем её дальше.
void TreeItem::AddWord(const std::string &word, const int &value, const int &word_size, int level)
{
    if (level == word_size)
    {
        MyMap::iterator map_iter;
        map_iter = words.FindString(word);
        if (map_iter == words.end())
        {
            MyMap::iterator it;
            it = words.lower_bound(value);
            words.insert(it, pair<int,string>(value,word));
        }
        else
            throw MyException(); // в принципе здесь можно увеличить значение
    }
    else
    {
        int num_letter;
        num_letter = charButton(word[level]);
        num_letter -= 2; // button[2;9] => pointer[1;7]
        CreateNext(num_letter);
        this->pointers[num_letter]->AddWord(word, value, word_size, level + 1);
    }
}
// выводит слово (WriteWord), если:
// 1) слово просмотрено целиком
// 2) далее в слове идут только звездочки.
// 3) далее в слове подряд идут звездочки, а затем последовательность '1' и '*'
// кидает слово в следующую структуру, если слово просмотрено не всё и следуюущий символ - литера.
// если далее встречается знак препинания ('1'), то вызывается Punctuation::WriteSince
void TreeItem::OfferAWord(const std::string &word, const int &word_size, int level)
{
    int stars = 0;
    if (level == word_size)
    {
        // example: "feel"
        WriteWord(stars, space);
    }
    else
    {
        // examples: "feel***"; "feel**1*"; "feel*1"; "feel**1***1*1"
        int num_letter;
        num_letter = codeButton(word[level]);
        if (num_letter == star)
        {
            int current;
            for (current = level; (current < word_size) && (codeButton(word[current]) == star); current++)
                stars++;
            if (current < word_size )
            {
                // exmaples: "feel**1*"; "feel*1"; "feel**1***1*1"
                WriteWord(stars);
                if (codeButton(word[current]) == 1)
                    treePtr->punc.WriteSince(word, current, word_size);
                else
                    throw MyException();
            }
            else
            {
                // example: "feel****";
                WriteWord(stars, space);
            }
        }
        else
        if (num_letter == 1)
        {
            // examples: "feel1"; "feel1*"; "feel1*1**11*"
            WriteWord(0, 0);
            treePtr->punc.WriteSince(word, level, word_size);
        }
        else
        {
            // example: "feelings..."
            num_letter -= 2; // button[2;9] => pointer[1;7]
            if (pointers[num_letter] == null)
                throw MyException();
            pointers[num_letter]->OfferAWord(word, word.size(), level + 1);
        }
    }
}
// выводит слово, учитывая количество звездочек.
void TreeItem::WriteWord(int stars, int space)
{
    MyMap::iterator iter = words.end();
    iter--;
    for (int i = stars; (i > 0)&&(iter != words.begin()); i--)
        iter--;
    treePtr->WriteOutstream(iter->second);
    if (space != 0)
        treePtr->WriteOutstream(" ");
    words.insert(pair<int,std::string>(iter->first + 1, iter->second));
    words.erase(iter);
}
// вывод всех слов данной вершины и всех её подвершин
void TreeItem::ShowAll()
{
    this->ShowMe();
    for (int i = 0; i < buttons; i++)
        if (pointers[i] != null)
            pointers[i]->ShowAll();
}
// вывод всех слов данной вершины
void TreeItem::ShowMe()
{
    MyMap::iterator map_iter;
    for (map_iter = words.begin(); map_iter != words.end(); map_iter++)
        cerr << map_iter->second << " " << map_iter->first << endl;
}
// создаем новую структуру, если её не ещё не существует
void TreeItem::CreateNext(int num)
{
    if (pointers[num] == 0)
        pointers[num] = new TreeItem(treePtr);
}
//============ TreeItem ===========end


//============== Tree ================
Tree::Tree()
{
    punc.SetTreePtr(this);
    out = 0;
    filename[0] = '\0';
//    cout << "Constr Tree" << endl;
}
Tree::~Tree()
{
    if (fileoutstream.is_open())
        fileoutstream.close();
//    cout << "Destr Tree" << endl;
}
void Tree::SetCout()
{
    out = 0;
}
// делал вывод в файл, потом перечитал задание, понял, что он не требуется
// тем не менее, вывод у меня сделан очень убого. надеюсь, есть какой-нибудь нормальный метод.
void Tree::SetFileOut(const char *s)
{
    if (fileoutstream.is_open())
        fileoutstream.close();
    int i;
    for (i = 0; (s[i] != '\0')&&(i < filename_size); i++)
        filename[i] = s[i];
    if (i < filename_size)
    {
        filename[i] = '\0';
        out = 1;
        fileoutstream.open(filename);
    }
    else
        throw MyException();
}
void Tree::WriteOutstream(const string &s)
{
    if (out == 0)
        cout << s;
    else
        fileoutstream << s;
}

// переводим первую литеру в номер кнопки и перекидываем слово структуре, у которой этот же номер
void Tree::AddWord(const string &word, int value = 1)
{
    int num_letter;
    num_letter = charButton(word[0]);
    num_letter -= 2; // button[2;9] => pointer[1;7]
    if (node.pointers[num_letter] == null)
        node.pointers[num_letter] = new TreeItem(this);
    node.pointers[num_letter]->AddWord(word, value, word.size(), 1);
}
// если слово начинается со '*', то ошибка
// если слово начинается с '1', то управление передается WriteSince
// в остальных случаях управление передаётся структуре, соответств. первой литере слова.
void Tree::OfferAWord(const string &word)
{
    int num_letter = codeButton(word[0]);

    if (num_letter == star)
        throw MyException();
    else
    if (num_letter == 1)
        punc.WriteSince(word, 0, word.length());
    else
    {
        num_letter -= 2; // button[2;9] => pointer[1;7]
        if (node.pointers[num_letter] == null)
            throw MyException("There is no word in the dictionary!");
        node.pointers[num_letter]->OfferAWord(word, word.size(), 1);
    }
}
// отображение дерева
void Tree::ShowTree()
{
    //cerr << "=========TREE========" << endl;
    node.ShowAll();
    //cerr << "=====================" << endl;
}
//============== Tree =============end


//=============== Other ==============
int charButton(const char &c)
{
    if (((c >= 'A')&&(c <= 'C')) || ((c >= 'a')&&(c <= 'c')))
        return 2;
    if (((c >= 'D')&&(c <= 'F')) || ((c >= 'd')&&(c <= 'f')))
        return 3;
    if (((c >= 'G')&&(c <= 'I')) || ((c >= 'g')&&(c <= 'i')))
        return 4;
    if (((c >= 'J')&&(c <= 'L')) || ((c >= 'j')&&(c <= 'l')))
        return 5;
    if (((c >= 'M')&&(c <= 'O')) || ((c >= 'm')&&(c <= 'o')))
        return 6;
    if (((c >= 'P')&&(c <= 'S')) || ((c >= 'p')&&(c <= 's')))
        return 7;
    if (((c >= 'T')&&(c <= 'V')) || ((c >= 't')&&(c <= 'v')))
        return 8;
    if (((c >= 'W')&&(c <= 'Z')) || ((c >= 'w')&&(c <= 'z')))
        return 9;
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



// TODO
// проверка на дурака при вводе отстутствует

const char* in_file = "C:\\yaT9\\in.txt";
const char* out_file = "C:\\yaT9\\out.txt";

int main(int argc, char *argv[])
{
    try
    {
        Tree tree;
       // ifstream in;
       // in.open(in_file);
       // if (!in.is_open())
         //   throw MyException("There is no file in.txt!");
        int number_words;
        int value;
        string word;

        // читаем список слов
        cin >> number_words;
        for (; number_words > 0; number_words--)
        {
            cin >> word;
            cin >> value;
            tree.AddWord(word, value);
        }

        // читаем строку, которую вбивает пользователь T9

        getline(cin, word, '\n');


        int spaces = 0;
        void *run;
        while (!cin.eof())
        {
            run = getline(cin, word, ' ');
            if (word.empty())
            {
                spaces++;
            }
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
                for (int i = 0; i < spaces; i++)
                {
                    cout << " ";
                }
                tree.OfferAWord(word);
                spaces = 0;
            }
        }


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
