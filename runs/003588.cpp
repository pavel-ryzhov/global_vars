#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <string>

using namespace std;

class T9TreeItem;

typedef map< char, T9TreeItem * > itemsMap;
typedef list< std::pair< string, size_t > > wordsList;

class T9TreeItem
{
    public:
        T9TreeItem( const char n = 0 );
        ~T9TreeItem();

        void newWord( const string &str, const size_t pos, const size_t weight );

        T9TreeItem *findWord( const string &str, const size_t pos = 0 );

        std::string word();
        std::string nextWord();
        void selectionDone();

    private:
        void sortWords();
        const char m_key;
        itemsMap m_children;
        wordsList *m_words;
        wordsList::iterator m_curWord;
};

class T9
{
    public:
        T9();
        ~T9();

        void newWord( const string &str );

        std::string word( const string &str );
        std::string nextWord();
        void selectionDone();

    private:
        T9TreeItem *m_rootItem;
        T9TreeItem *m_curItem;

};

bool
wordsCompare( pair< string, size_t > one, pair< string, size_t > two )
{
    return ( one.second > two.second ) || ( one.second == two.second && one.first < two.first );
}
//-------------------------------T9TreeItem----------------------------------------------
T9TreeItem::T9TreeItem( const char n )
          : m_key( n )
          , m_words( 0 )
{
}

T9TreeItem::~T9TreeItem()
{
    for( itemsMap::iterator i = m_children.begin(); i != m_children.end(); i++ )
        delete i->second;

    if( m_words )
        delete m_words;
}

void
T9TreeItem::newWord( const string &str, const size_t pos, const size_t weight )
{
    if( pos != str.length() )
    {
        char key = str.at( pos );
        if( key == '.' || key == ',' || key == '?' )
            key = '1';
        if( key >= 'w' )
            key = '9';
        else if( key >= 't' )
            key = '8';
        else if( key >= 'p' )
            key = '7';
        else if( key >= 'm' )
            key = '6';
        else if( key >= 'j' )
            key = '5';
        else if( key >= 'g' )
            key = '4';
        else if( key >= 'd' )
            key = '3';
        else if( key >= 'a' )
            key = '2';

        if( m_children.count( key ) == 0 )
            m_children.insert( make_pair( key, new T9TreeItem( key ) ) );

        m_children.at( key )->newWord( str, pos + 1, weight );
    }
    else
    {
        if( !m_words )
            m_words = new wordsList;

        m_words->push_back( make_pair( str, weight ) );
        sortWords();
    }
}

T9TreeItem *
T9TreeItem::findWord( const string &str, const size_t pos )
{
    if( str.length() == pos )
        return this;

    if( m_children.count( str.at( pos ) ) )
        return m_children.at( str.at( pos ) )->findWord( str, pos + 1 );
    else
        return 0;
}

void
T9TreeItem::sortWords()
{
    if( m_key == '1' )
        return;

    m_words->sort( wordsCompare );
    m_curWord = m_words->end();
}

string
T9TreeItem::word()
{
    if( m_curWord != m_words->end() )
        selectionDone();

    m_curWord = m_words->begin();
    return m_curWord->first;
}

string
T9TreeItem::nextWord()
{
    if( ++m_curWord == m_words->end() )
        m_curWord = m_words->begin();
    return m_curWord->first;
}

void
T9TreeItem::selectionDone()
{
    if( m_curWord == m_words->end() || m_key == '1' )
        return;

    m_curWord->second++;
    for( wordsList::iterator i = m_words->begin(); i != m_curWord; i++ )
        if( i->second <= m_curWord->second )
        {
            m_words->insert( i, *m_curWord );
            m_words->erase( m_curWord );
            break;
        }

    m_curWord = m_words->end();
}

//-----------------------------------------T9--------------------------------------------
T9::T9()
  : m_rootItem( new T9TreeItem() )
  , m_curItem( 0 )
{
    m_rootItem->newWord( ".", 0, 1 );
    m_rootItem->newWord( ",", 0, 1 );
    m_rootItem->newWord( "?", 0, 1 );
}

T9::~T9()
{
    delete m_rootItem;
}

void
T9::newWord( const string &str )
{
    size_t offset;
    if( ( offset = str.find( ' ' ) ) == string::npos )
        m_rootItem->newWord( str, 0, 1 );
    else
        m_rootItem->newWord( str.substr( 0, offset ), 0, strtoul( str.c_str() + offset + 1, NULL, 0 ) );
}

string
T9::word( const string &str )
{
    if( ( m_curItem = m_rootItem->findWord( str ) ) )
        return m_curItem->word();
    else
        cerr << "Not such word in the dictionary: \"" << str << "\".\n";

    return string();
}

string
T9::nextWord()
{
    return m_curItem ? m_curItem->nextWord() : string();
}

void
T9::selectionDone()
{
    if( m_curItem )
    {
        m_curItem->selectionDone();
        m_curItem = 0;
    }
}

int
main()
{
    T9 *dict = new T9;
    string *str = new string;

    size_t n;
    getline( cin, *str );
    n = strtoul( str->c_str(), NULL, 0 );

    for( size_t i = 0; i < n; i++ )
    {
        getline( cin, *str );
        dict->newWord( *str );
    }
    getline( cin, *str );

    n = 0;
    string code, word;
    unsigned char state = 0;
    char c;
    while( n < str->length() )
    {
        c = str->at( n );
        if( isspace( c ) )
        {
            if( state == 3 )
            {
                cout << word;
                word.erase();
                dict->selectionDone();
            }
            else if( state )
            {
                cout << dict->word( code );
                dict->selectionDone();
                code.erase();
            }

            cout << c;
            state = 0;
        }
        else if( c == '*' )
        {
            if( state == 1 || state == 2 )
            {
                dict->word( code );
                code.erase();
            }
            word = dict->nextWord();
            state = 3;
        }
        else if( c == '1' )
        {
            if( state == 3 )
            {
                cout << word;
                dict->selectionDone();
            }
            else if( state )
            {
                cout << dict->word( code );
                dict->selectionDone();
                code.erase();
            }
            code = "1";
            state = 2;
        }
        else if( isdigit( c ) )
        {
            if( state == 2 )
            {
                cout << dict->word( code );
                dict->selectionDone();
                code.erase();
            }
            else if( state == 3 )
            {
                cout << word;
                word.erase();
                dict->selectionDone();
            }

            code += c;
            state = 1;
        }
        n++;
    }
    switch( state )
    {
        case 1:
        case 2:
            cout << dict->word( code );
            dict->selectionDone();
            code.erase();
            break;
        case 3:
            cout << word;
            dict->selectionDone();
            word.erase();
            break;
    }
    cout << endl;
    delete str;
    delete dict;
    return 0;
}
