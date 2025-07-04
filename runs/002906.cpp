/* 
 * File:   taskc.cpp
 * Author: Sergey Nikishin
 *
 * Created on 2 Сентябрь 2010 г.
 */
#include <stdlib.h>
#include <iostream>
#include <string>
#include <iterator>
using std::string;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
#include <queue>
#include <map>
#include <vector>
#include <algorithm>
#include <time.h>
using std::pair;
using std::priority_queue;
using std::map;
using std::vector;


//#include <time.h>
//void wait ( int seconds )
//{
//  clock_t endwait;
//  endwait = clock () + seconds * CLOCKS_PER_SEC ;
//  while (clock() < endwait) {}
//}


/*
 * формат словаря:
 * [ код1 слова по нажатым клавишам ]
 *      | частота1  - { слово1, слово12, слово33 }
 *      | частота2  - { слово4, слово7, слово10 }
 *      ...
 * [ код2 ]
 *      ...
 * [ код3 ]
 *      ...
 */
typedef int Frequency;
typedef string WordCode;
typedef pair< Frequency, string > Word;
typedef vector<Word> WordsList;
typedef map<WordCode, WordsList> DictionaryData;

const char selectSymbol = '*';
const char spaceSymbol = ' ';
const char punctuationSymbol = '1';

namespace std {
bool operator < ( const Word & w1, const Word & w2 )
{
    return w1.first != w2.first ?
        w1.first < w2.first : w1.second > w2.second;
}
}

// конвертировать строку в число
int StrToInt( const string & s )
{
    return static_cast< int >( atoi( s.c_str() ) );
}

// удалить лишние пробелы
string LeftTrim( const string & str )
{
    string result = str;

    while ( isspace( *result.begin() ) ) {
        result.erase(0, 1);
    }

    return result;
}

// считать одиночное число в строке
int ReadIntFromStream()
{
    string text_value = "";
    std::getline ( cin, text_value );

    return StrToInt ( text_value );
}

// считать слово для словаря
Word ReadWordFromStream()
{
    string line = "";
    std::getline ( cin, line );
    
    line = LeftTrim ( line );
    
    string letter = "";
    Frequency frequency = 0;

    int pos = line.find ( ' ' );
    if( pos != -1 ) {
        letter = line.substr ( 0, pos );
        frequency = StrToInt ( line.erase ( 0, pos + 1 ) );
    }       
    
    return Word( frequency, letter );
}

// вычислить числовой код символа
inline char GetCharCode( char ch )
{
    static const int letters_count = 26;
    static char codes[ letters_count ] = { '2','2','2','3','3','3','4','4','4', '5','5','5','6','6','6','7','7','7','7','8','8','8','9','9','9','9' };

    // привести код к [0..26]
    int char_index = static_cast < int > ( ch ) - static_cast < int > ( 'a' );
    
    if( char_index >= 0 && char_index < letters_count )
    {
        return codes[ char_index ];
    }
    else
    {
        return '1';
    }
}

// вычислить числовой код слова
WordCode GetWordCode( const string & word )
{
    static WordCode result = "";
    result = "";

    for ( unsigned i = 0; i < word.length(); ++i )
    {
         char code = GetCharCode ( word[ i ] );
         result += code;
    }
    return result;
}

// символ - цифра от 2 до 9
inline bool IsDigit( char ch )
{
    return ch >= '2' && ch <= '9';
}


class Dictionary
{
public:
    explicit Dictionary() {}

    // внести слово в словарь
    void AddWord( const Word & word, const WordCode & wordCode = "" )
    {
        // если код указан вручную, то не вычислять его для данного слова
        WordCode word_code = wordCode == "" ? GetWordCode ( word.second ) : wordCode;

        // добавить в список Т9 для данного кода
//        WordsList & word_list = data[ word_code ];
        data[ word_code ].push_back ( word );

//        // найти список слов с такой же либо меньшей частотой
//        unsigned i = 0;
//        for ( i = 0; i < word_list.size (); ++i ) {
//            if( word_list[ i ].first > word.first ) {
//                break;
//            }
//        }
//
//        // если частота наименьшая из присутствующих
//        if( i == word_list.size () )
//        {
//            // добавить в конец списка
//            word_list.push_back ( word );
//        }
//
//        else
//        {
//            // добавить в нужную позицию
//            AddWordToWordList ( word_list, i, word );
//        }        
    }

    // упорядочить словарь
    void Finalize()
    {
        DictionaryData::iterator it = data.begin ();
        for ( ; it != data.end(); ++it ) {
            std::sort ( it->second.begin (), it->second.end () );
        }
    }

    // вывести на экран все элементы словаря
    void Print() const
    {
        DictionaryData::const_iterator it = data.begin ();
        for( ; it != data.end (); ++it )
        {
            // код слова
            cout << "\t word code: " << it->first << endl;
            // списки T9

            const WordsList & word_list = it->second;
            WordsList::const_iterator it_word = word_list.begin ();
            for ( ; it_word != word_list.end (); ++it_word )
            {
                cout << ", " << it_word->second << " (" << it_word->first << ")";
            }
            cout << endl;
        }
    }

    // декодировать слово
    string DecodeWordInT9( const WordCode & code, const int t9_offset )
    {
        if( code.empty () ) {
            return "";
        }

        static string result = "";
        static Word word( 0, "" );

        result = "";

        // найти списки слов, соответствующие данному коду
        WordsList & word_list = data[ code ];

        // найти позицию слово в словаре

        size_t word_list_size = word_list.size ();
        
        int index = word_list_size - ( t9_offset + 1 );

        // не перемещать знаки препинания
        if ( word_list[ index ].first < 0 ) {
            return word_list[ index ].second;
        }

        // увеличить частоту
        ++word_list[ index ].first;

        // запомнить слово
        word = word_list[ index ];
        result = word.second;

        // если элемент уже 1й, то смещать ничего не нужно
        if( !t9_offset ) {
            return result;
        }

        // найти с большей частотой
        int i = index + 1;
        for( ; i < word_list_size ; ++i )
        {
            if( word_list[ i ].first > word.first ) {
                break;
            }
        }

        if( i != word_list_size )
        {
            if( i != index + 1 )
            {
                word_list.erase ( word_list.begin () + index );
                word_list.insert ( word_list.begin () + i - 1, word );
            }
        }
        else
        {
            word_list.erase ( word_list.begin () + index );
            word_list.push_back ( word );
        }

        return result;
    }

    // размер словаря
    int Size() const
    {
        return data.size ();
    }
private:

    Dictionary& operator= ( const Dictionary&);
    Dictionary( const Dictionary& );

    // внести слово в список слов (в алфавитном порядке)
    void AddWordToWordList( WordsList & words_list, const int start_index, const Word & word )
    {
        // найти слово, < данного
        // и вставить перед ним
        WordsList::iterator it = words_list.begin () + start_index;
        WordsList::iterator it_end = words_list.end ();
        for ( ; it != it_end && it->first >= word.first; ++it )
        {
            if( *it >= word ) {
                break;
            }
        }

        // если достигнут конец списка, то вставить в конец
        // иначе вставить перед
        words_list.insert ( it, word );
    }

    // увеличить частоту использования данного слова
    // и переместить слово вперед, если это необходимо
    void IncreaseWordFrequency(  )
    {
        // исключить знаки препинания
    }

    DictionaryData data;

};

/*
 * ввести словарь
 * для знаков препинания частота отрицательная,
 * т.к. их популярность не учитывается.
 */
void FillDictionary( Dictionary * dictionary, int wordsCount )
{
    if( !dictionary ) {
        cerr << "FillDictionary: bad arguments" << endl;
        return;
    }
    
    for ( int i = 0; i < wordsCount; ++i )
    {
        // внести по очереди все слова
        Word word = ReadWordFromStream();

        // добавить слово в словарь
        dictionary->AddWord ( word );
    }

    dictionary->AddWord ( Word(-1, ".") );
    dictionary->AddWord ( Word(-2, ",") );
    dictionary->AddWord ( Word(-3, "?") );

    dictionary->Finalize ();

    // добавить знаки препинания в словарь
//    string punctuationCode = "";
//    punctuationCode = punctuationSymbol;
//
//    // упорядочить словарь
//    Dictionary::iterator it = dictionary->begin ();
//    for( ; it != dictionary->end (); ++it ) {
//        it->second.sort ();
//    }
}

/*
 * ввести входные данные
 */
void ReadStream ( Dictionary * dictionary, string * keysPressed )
{
    if( !dictionary || !keysPressed ) {
        cerr << "ReadStream: bad arguments" << endl;
        return;
    }

    // cчитать количество слов в словаре
    int wordsCount = ReadIntFromStream();

    // составить словарь
    FillDictionary ( dictionary, wordsCount );

    //
    cerr << "info... words: " << wordsCount << endl;
    cerr << "info... dictionary size: " << dictionary->Size () << endl;

    // ввести последнюю строку (нажатые клавиши)
    std::getline( cin, *keysPressed );

    cerr << "info... keysPressed size: " << keysPressed->length () << endl;
}


/*
 * обработать нажатия кнопок
 */
string ProcessKeysPressed( Dictionary * dictionary, const string & keysPressed )
{
    string result = "";
    WordCode word_accumulator = "";
    int t9_offset = 0;
    char prev_character = '\0';
    char ch = '\0';

    unsigned keysPressed_length = keysPressed.length ();
    for( unsigned position = 0; position < keysPressed_length; ++position )
    {
        ch = keysPressed[ position ];
        // если символ - цифра 2..9, то записать его в аккумулятор
        // сбросить, если до этого был другой символ
        if( IsDigit ( ch ) )
        {
            if( !IsDigit( prev_character ) )
            {
                result += dictionary->DecodeWordInT9 ( word_accumulator, t9_offset );
                word_accumulator = "";
                t9_offset = 0;
            }
            word_accumulator += ch;
        }
        // если звездочка, то увеличивать смещение в словаре
        else if( ch == selectSymbol )
        {
            ++t9_offset;
        }
        // если 1 (знаки препинания), то сбросить слово и записать
        // в аккумулятор код знаков препинания
        else if ( ch == punctuationSymbol )
        {
            result += dictionary->DecodeWordInT9 ( word_accumulator, t9_offset );
            word_accumulator = punctuationSymbol;
            t9_offset = 0;
        }
        // если пробел, сбросить слово и дописать пробел
        else if ( ch == spaceSymbol )
        {
            result += dictionary->DecodeWordInT9 ( word_accumulator, t9_offset );
            result += spaceSymbol;
            word_accumulator = "";
            t9_offset = 0;
        }

        prev_character = ch;
    }

    result += dictionary->DecodeWordInT9 ( word_accumulator, t9_offset );

    return result;
}


// сгенерировать свой словарь и строку-запрос
void GenerateDictionary( Dictionary * dictionary, string * keysPressed )
{
    // сгенерировать словарь на 50000 слов
    // в 3 группах
    
    // 1 группа "abc" из 10 символов
    for ( int i = 0; i < 25000; ++i )
    {
        Word w ( rand ()%30, "aaabbbccc" );
        dictionary->AddWord ( w );
    }

    for ( int i = 0; i < 25000; ++i )
    {
        Word w ( rand ()%30, "wegfwagccc" );
        dictionary->AddWord ( w );
    }

    WordCode code1 = GetWordCode ( "aaabbbccc" );
    WordCode code2 = GetWordCode ( "wegfwagccc");

    dictionary->Finalize();
}

/*
 * 
 */
int main ( int argc, char** argv )
{
    // ввести входные данные
    string keysPressed = "";
    Dictionary dictionary;

    ReadStream ( &dictionary, &keysPressed );
//    GenerateDictionary ( &dictionary, &keysPressed );
    cerr << "info... load time: " << clock() << endl;

//    keysPressed = "";

//    clock_t time0 = clock();

//    WordCode code = GetWordCode ( "aaabbbccc" );

    // сгенерировать
//    int j = 0;
//    for ( int i = 0; i < 100000; ++i )
//    {
//        keysPressed += " " + code;
//        for ( j = 0; j < rand()%100; ++j )
//        {
//           keysPressed += "*";
//        }
//    }

    // обработать нажатия кнопок
    string result = ProcessKeysPressed ( &dictionary, string(keysPressed) );
    cerr << "info... total time: " << clock() << endl;

    // вывести результат
    cout << result << endl;

    return 0;
}