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
#include <list>
#include <map>
using std::pair;
using std::priority_queue;
using std::map;
using std::list;

typedef pair< int, string > Word;
typedef list<Word> AssociatedWords;
typedef map<string, AssociatedWords> Dictionary;

namespace std{
bool operator < ( const Word & a, const Word & b )
{
    return ( a.first != b.first )
           ? ( a.first > b.first )
           : ( a.second < b.second );
}
}

const char selectSymbol = '*';
const char spaceSymbol = ' ';
const char punctuationSymbol = '1';

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
    int freq = 0;

    int pos = line.find ( ' ' );
    if( pos != -1 )
    {
        letter = line.substr ( 0, pos );
        freq = StrToInt ( line.erase ( 0, pos + 1 ) );
    }       
    
    return Word( freq, letter );
}

// вычислить числовой код символа
inline char GetCharCode( char ch )
{
    const int letters_count = 26;
    static char codes[ letters_count ] = { '2','2','2','3','3','3','4','4','4', '5','5','5','6','6','6','7','7','7','7','8','8','8','9','9','9','9' };

    // привести код к [0..26]
    int char_index = static_cast < int > ( ch ) - static_cast < int > ( 'a' );
    char_index = std::max( char_index, 0 );
    char_index = std::min( char_index, letters_count - 1 );

    return codes[ char_index ];
}

// вычислить числовой код слова
string GetWordCode( const string & word )
{
    static string result = "";
    result = "";

    for ( unsigned i = 0; i < word.length(); ++i )
    {
         char code = GetCharCode ( word[ i ] );
         result += code;
    }
    return result;
}

// вывести на экран все элементы словаря
void PrintDictionary( const Dictionary & dictionary )
{
    Dictionary::const_iterator it = dictionary.begin ();
    for( ; it != dictionary.end (); ++it )
    {
        cout << "\t" << it->first << endl;
        AssociatedWords::const_iterator it2 =  it->second.begin ();
        for ( ; it2 != it->second.end(); ++it2 )
        {
            cout << "\t    " << it2->second << " : " << it2->first << endl;
        }

    }
}

// увеличить частоту использования данного слова
// и переместить слово вперед, если это необходимо
void IncreaseWordFrequency( AssociatedWords & awords, const AssociatedWords::iterator & it )
{
    // исключить знаки препинания
    if ( it->first <= 0 ) {
        return;
    }

    ++it->first;

    // найти в предыдущих тот, на место которого надо вставить элемент
    AssociatedWords::iterator it_current = it;

    AssociatedWords::iterator lbound = awords.begin ();
    for ( ; lbound != awords.end() && lbound != it ; ++lbound ) {
        if ( lbound->first <= it->first ) {
            break;
        }
    }
    if ( lbound != awords.end () && lbound != it )
    {
        Word w = *it;
        awords.erase ( it );
        awords.insert ( lbound, w );
    }

}

/*
 * ввести словарь
 * для знаков препинания частота отрицательная,
 * т.к. их популярность не учитывается.
 */
void FillDictionary( Dictionary * dictionary, std::istream & stream, int wordsCount )
{
    if( !dictionary ) {
        cerr << "FillDictionary: bad arguments" << endl;
        return;
    }
    
    for ( int i = 0; i < wordsCount; i++ )
    {
        // внести по очереди все слова
        Word word = ReadWordFromStream();
        string word_code = GetWordCode ( word.second );

        // добавить в список Т9 для данного кода
        // с учетом порядка
        AssociatedWords & awords = ( *dictionary )[ word_code ];
        awords.push_back ( word );
    }

    string punctuationCode = "";
    punctuationCode = punctuationSymbol;
    ( *dictionary )[ punctuationCode ].push_back ( Word(-1, ".") );
    ( *dictionary )[ punctuationCode ].push_back ( Word(-2, ",") );
    ( *dictionary )[ punctuationCode ].push_back ( Word(-3, "?") );

    // упорядочить словарь
    Dictionary::iterator it = dictionary->begin ();
    for( ; it != dictionary->end (); ++it ) {
        it->second.sort ();
    }
    it = dictionary->begin ();
    for( ; it != dictionary->end (); ++it ) {
        it->second.sort ();
    }
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
    FillDictionary ( dictionary, cin, wordsCount );

    //
    cerr << "info... words: " << wordsCount << endl;
    cerr << "info... dictionary size: " << dictionary->size () << endl;

    // ввести последнюю строку (нажатые клавиши)
    std::getline( cin, *keysPressed );

    cerr << "info... keysPressed size: " << keysPressed->length () << endl;
}

// символ - цифра от 2 до 9
inline bool IsDigit( char ch )
{
    return ch >= '2' && ch <= '9';
}

// декодировать слово
string DecodeWord( Dictionary * dictionary, const string & code, const int t9_offset )
{
    if( code.empty () || (*dictionary)[ code ].size () <= t9_offset ) {
        return "";
    }

    string result = "";

    AssociatedWords & awords = (*dictionary)[ code ];

    // перейти к слову по смещению
    AssociatedWords::iterator it = awords.begin();
    std::advance ( it, t9_offset );
    result = it->second;
    
    IncreaseWordFrequency( awords, it );
    
    return result;
}

/*
 * обработать нажатия кнопок
 */
string ProcessKeysPressed( Dictionary * dictionary, const string & keysPressed )
{
    string result = "";
    string word_accumulator = "";
    int t9_offset = 0;
    char prev_character = '\0';
    char ch = '\0';

    for( int position = 0; position < keysPressed.length (); ++position )
    {
        ch = keysPressed[ position ];
        // если символ - цифра 2..9, то записать его в аккумулятор
        // сбросить, если до этого был другой символ
        if( IsDigit ( ch ) )
        {
            if( !IsDigit( prev_character ) )
            {
                result += DecodeWord ( dictionary, word_accumulator, t9_offset );
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
            result += DecodeWord ( dictionary, word_accumulator, t9_offset );
            word_accumulator = punctuationSymbol;
            t9_offset = 0;
        }
        // если пробел, сбросить слово и дописать пробел
        else if ( ch == spaceSymbol )
        {
            result += DecodeWord ( dictionary, word_accumulator, t9_offset );
            result += spaceSymbol;
            word_accumulator = "";
            t9_offset = 0;
        }

        prev_character = ch;
    }

    result += DecodeWord ( dictionary, word_accumulator, t9_offset );

    return result;
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

    // обработать нажатия кнопок
    string result = ProcessKeysPressed ( &dictionary, keysPressed );

    // вывести результат
    cout << result << endl;

    return 0;
}