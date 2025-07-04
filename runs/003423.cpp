#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

/*
Описание программы:
    Словам в словаре сопоставляется их цифровой код (например, слову not -> 668),
и создается обратный словарь - цифровой код -> записи, содержащие слово и 
частоту встречаемости. 
    Считывается цифровой код и выбирается наиболее встречаемое слово.
*/

/*
Структура одной записи в словаре (слово и частота встречаемости)
*/
struct Record         
{
    string value;
    unsigned int freq;    
    Record(string v, unsigned int f):value(v), freq(f) {}
};

map< string, vector<Record> > dict;    // Сам словарь

void addFreq(string str, unsigned int k)
{
    Record tmp("",0);    
    dict[str][k].freq++;
    while ( (k>0) && (dict[str][k].freq >= dict[str][k-1].freq) )
    {
        tmp = dict[str][k];
        dict[str][k] = dict[str][k-1];
        dict[str][k-1] = tmp;        
        --k;
    }
}

// Функция сравнения записей, учитывает частоту,
// а так же алфавитный порядок, если частоты равны.
bool compare_records(Record r1, Record r2)
{
    if (r1.freq > r2.freq) return true;
    if (r1.freq < r2.freq) return false;
    else if (r1.value < r2.value) return true;
         else return false;
}


int main(int argc, char* argv[])
{
    unsigned int n, num;               
    unsigned int i,j;
    map <char, char> t9;                // Буква - цифра
    string s, st, word;
    
    // заполняем "словарь" буква-цифра.
    t9.insert( pair<char, char>('a', '2') );
    t9.insert( pair<char, char>('b', '2') );
    t9.insert( pair<char, char>('c', '2') );
    t9.insert( pair<char, char>('d', '3') );
    t9.insert( pair<char, char>('e', '3') );
    t9.insert( pair<char, char>('f', '3') );
    t9.insert( pair<char, char>('g', '4') );
    t9.insert( pair<char, char>('h', '4') );
    t9.insert( pair<char, char>('i', '4') );
    t9.insert( pair<char, char>('j', '5') );
    t9.insert( pair<char, char>('k', '5') );
    t9.insert( pair<char, char>('l', '5') );
    t9.insert( pair<char, char>('m', '6') );
    t9.insert( pair<char, char>('n', '6') );
    t9.insert( pair<char, char>('o', '6') );
    t9.insert( pair<char, char>('p', '7') );
    t9.insert( pair<char, char>('q', '7') );
    t9.insert( pair<char, char>('r', '7') );
    t9.insert( pair<char, char>('s', '7') );
    t9.insert( pair<char, char>('t', '8') );
    t9.insert( pair<char, char>('u', '8') );
    t9.insert( pair<char, char>('v', '8') );
    t9.insert( pair<char, char>('w', '9') );
    t9.insert( pair<char, char>('x', '9') );
    t9.insert( pair<char, char>('y', '9') );
    t9.insert( pair<char, char>('z', '9') );
    // Ух, все.
    
    cin >> n;
    cerr << "Got " << n << " words..." << endl;
    getline(cin, s);       // Пропустить строку с кол-вом слов
    for (i=0; (i<n); ++i)
    {
        getline(cin, st); 
        if (cin.fail()) { cerr << "Incorrect number of words" << endl; break;}
        s=st;
        st.clear();
        if (s.find(" ") == string::npos) {cerr << "No space" << endl; break;}
        for (j=0; j<s.find(" "); ++j)
        {
            st.push_back( t9[s[j]] );                // Переводим букву в цифру
        }
        word = s.substr(0, s.find(" "));
        istringstream buf( s.substr(s.find(" ")+1) );
        buf >> num;
        dict[st].push_back(Record(word, num));       // Добавляем слово
    }    
    // Словарь заполнен, теперь нужно его отсортировать по частоте.
    cerr << "Dictionary full. Sorting..." << endl;
    map< string, vector<Record> >::iterator it;
    for ( it=dict.begin(); it!=dict.end(); ++it )
        sort( (*it).second.begin(), (*it).second.end(), compare_records );
    // и добавить знаки препинания    
    dict["1"].push_back(Record(".", 0));    
    dict["1"].push_back(Record(",", 0)); 
    dict["1"].push_back(Record("?", 0)); 
    cerr << "Sort ok, sorted " << dict.size() << " entries" << endl;
    // Теперь все готово для обработки текста    
    i = 0;
    num = 0;
    st.clear();
    cerr << "Reading text" << endl;
    if (!cin.fail()) getline(cin, s);
    cerr << "Got " << s.length() << " symbols to process" << endl;
    while (i<s.length())
    {
        switch (s[i]) {
        case '1':
            if (!st.empty())
            {             
                cout << dict[st][num].value;
                if (st[0] != '1') addFreq(st, num);
                st.clear();
                num = 0;
            }
            st = "1";
            break;
        case ' ': 
            if (!st.empty())
            {             
                cout << dict[st][num].value;
                if (st[0] != '1') addFreq(st, num);
                st.clear();
                num = 0;
            }
            cout << ' ';
            break;
        case '*': 
            num++;
            break;
        default:
            if ( (s[i]>='2') && (s[i]<='9') )
                st += s[i];
            break;
        }   
        ++i;
    }
    if (!st.empty())
    {             
        cout << dict[st][num].value;
        //if (st[0] != '1') addFreq(st, num);
        //st.clear();
        //num = 0;
    }
    cout << endl;    
    return 0;
}
