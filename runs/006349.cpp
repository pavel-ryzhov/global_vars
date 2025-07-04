#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

// Пара слово-его частота
typedef pair<string, unsigned int> element;
// Нужно переопределить операции сравнения, иначе с порядком следования слов в словаре будут проблемы:
bool operator > (element a, element b) {
    if(a.second > b.second) return true;
    else if(a.second == b.second) return (a.first < b.first);
    else return false;
}
bool operator < (element a, element b) {
    if(a.second < b.second) return true;
    else if(a.second == b.second) return (a.first > b.first);
    else return false;
}

// Структура для хранения слов, с одинаковым цифровым эквивалентом
// (то есть результат функции convert для всех слов из этой структуры один и тот же);
struct wordbook { 
    vector<element> words;
    inline vector<element>::iterator begin() {
        return words.begin();
    }
    inline vector<element>::iterator end() {
        return words.end();
    }
    
    // Добавляем элементы так, что бы слова были всегда отсортированы
    void Add ( element el ) {
        if(words.empty() || words.back() > el) {
            words.push_back(el);
            return;
        }
        
        vector<element>::iterator i;
        for(i = words.begin(); (*i)>el; i++);
        words.insert(i, el);
    }
    
    // Выдаем слово с индексом num и перемещаем его туда, куда надо (в самый верх среди слов с той же частотой)
    string GetWord (unsigned int num) {
        if(num == 0) {
            words[0].second++;
            return words[0].first;
        }
        vector<element>::iterator i = begin();
        i += num;
        i->second++;
        
        element result = (*i);
        words.erase(i);
        
        while( (i-1)->second <= result.second && i!=begin() ) i--;
        words.insert(i, result);
        
        return result.first;
    }
};
char points[] = { '.', ',', '?' }; // Массив для определени знака препинания

// Сия карта будет использоваться для быстрого нахождения нужного набора слов (wordbook)
map<string, wordbook*> compliance;

// Функция convert преобразует слово (строку из букв) в числовой эквивалент
// (как оно бы набиралось на клавиатуре телефона)
string convert (string word) {
    char* result = new char[21];
    int i;
    for(i=0; word[i]; i++) {
        switch(word[i]) {
            case 'a': case 'b': case 'c':
                result[i] = '2';
                break;
            case 'd': case 'e': case 'f':
                result[i] = '3';
                break;
            case 'g': case 'h': case 'i':
                result[i] = '4';
                break;
            case 'j': case 'k': case 'l':
                result[i] = '5';
                break;
            case 'm': case 'n': case 'o':
                result[i] = '6';
                break;
            case 'p': case 'q': case 'r': case 's':
                result[i] = '7';
                break;
            case 't': case 'u': case 'v':
                result[i] = '8';
                break;
            case 'w': case 'x': case 'y': case 'z':
                result[i] = '9';
                break;
        }
    }
    
    result[i] = 0;
    return result;
}

// Обработка слова (печать того, что указано в word, начиная с i-го символа)
void parseAndWork(string word, unsigned char i = 0) {
    string cmd; unsigned int n;
    
    // Заполняем cmd (если 1 - то ничем не заполняем)
    if(word[i] == '1') i++; 
    else {
        for(; word[i]!='*' && word[i]!='1' && word[i]!=0; i++)
            cmd += word[i];
    }
    
    // Считаем количество звезд ('*')
    for(n=0; word[i] == '*'; i++, n++);
    
    // Выводим на экран то, что нужно (либо слово из словаря, либо знак препинания)
    if(cmd.empty()) cout<<points[n];
    else cout<<compliance[cmd]->GetWord(n);
    
    if(word[i] != 0) parseAndWork(word, i);
}

int main () {
    unsigned int N; cin>>N;
    
    // Создание словаря (создание и заполнение структур wordbook)
    string word; unsigned short v;
    for(unsigned int i=0; i<N; i++) {
        cin>>word>>v;
        if( compliance.empty() || 
                compliance.find(convert(word)) == compliance.end() )
            compliance.insert( make_pair( convert(word), (new wordbook) ) );
        compliance[convert(word)]->Add( make_pair(word, v) );
    }
    
    // Обработка запроса
    // Первый раз просто считываем в строку, потом же считывать будем посимвольно...
    cin>>word;
    parseAndWork( word );
    
    char s; cin.get(s);
    while(s != 10) {
        if(s == ' ') {
            cout<<" ";
            cin.get(s);
            continue;
        } else {
            word.clear();
            do {
                word += s;
                cin.get(s);
            } while (s != ' ' && s != 10);
            parseAndWork( word ); 
        }
    }
    
    for(map<string, wordbook*>::iterator i=compliance.begin(); i!=compliance.end(); i++)
        delete (i->second);
}