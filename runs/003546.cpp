#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

class T9TreeItem;

typedef map< char, T9TreeItem * > itemsMap;
typedef vector< pair< string, size_t > > wordsList;

map< char, char > *keyMap;

class T9TreeItem
{
    public:
        T9TreeItem( const char n = 0 );
        ~T9TreeItem();

        void newWord( const string &str, const size_t pos, const size_t weight );

        T9TreeItem *findWord( const string &str );

        string word();
        string nextWord();
        void selectionDone();

    private:
        void sortWords();
        const char m_key;
        itemsMap m_children;
        wordsList *m_words;
        long int m_curWord;
};

class T9
{
    public:
        T9();
        ~T9();

        void newWord( const string &str );

        string word( const string &str );
        string nextWord();
        void selectionDone();

    private:
        T9TreeItem *m_rootItem;
        T9TreeItem *m_curItem;

};

T9TreeItem::T9TreeItem( const char n )
          : m_key( n )
          , m_words( 0 )
          , m_curWord( -1 )
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
        char key = keyMap->at( str.at( pos ) );
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
T9TreeItem::findWord( const string &str )
{
    if( str.empty() )
        return this;

    if( m_children.count( str.at( 0 ) ) )
        return m_children.at( str.at( 0 ) )->findWord( str.substr( 1 ) );
    else
        return 0;
}

void
T9TreeItem::sortWords()
{
    if( m_key == '1' )
        return;

    for( size_t i = 0; i < m_words->size() - 1; i++ )
        for( size_t j = i + 1; j < m_words->size(); j++ )
            if( ( m_words->at( i ).second < m_words->at( j ).second ) ||
                ( m_words->at( i ).second == m_words->at( j ).second &&
                  m_words->at( i ).first > m_words->at( j ).first ) )
            {
                pair< string, size_t > buff = m_words->at( i );
                ( *m_words )[ i ] = ( *m_words )[ j ];
                ( *m_words )[ j ] = buff;
            }
}

string
T9TreeItem::word()
{
    if( m_curWord != -1 )
        selectionDone();

    m_curWord = 0;
    return m_words->at( m_curWord ).first;
}

string
T9TreeItem::nextWord()
{
    if( ++m_curWord == static_cast< long int >( m_words->size() ) )     //Warning clean.
        m_curWord = 0;
    return m_words->at( m_curWord ).first;
}

void
T9TreeItem::selectionDone()
{
    if( m_curWord == -1 || m_key == '1' )
        return;

    ( *m_words )[ m_curWord ].second++;
    for( long int i = 0; i <= m_curWord; i++ )
        if( m_words->at( i ).second <= m_words->at( m_curWord ).second )
        {
            pair< string, size_t > buff = m_words->at( i );
            ( *m_words )[ i ] = ( *m_words )[ m_curWord ];
            ( *m_words )[ m_curWord ] = buff;
        }
    m_curWord = -1;
}

T9::T9()
  : m_rootItem( new T9TreeItem() )
  , m_curItem( 0 )
{
    keyMap = new map< char, char >;
    {
        keyMap->insert( make_pair( '.', '1' ) );
        keyMap->insert( make_pair( ',', '1' ) );
        keyMap->insert( make_pair( '?', '1' ) );
        keyMap->insert( make_pair( 'a', '2' ) );
        keyMap->insert( make_pair( 'b', '2' ) );
        keyMap->insert( make_pair( 'c', '2' ) );
        keyMap->insert( make_pair( 'd', '3' ) );
        keyMap->insert( make_pair( 'e', '3' ) );
        keyMap->insert( make_pair( 'f', '3' ) );
        keyMap->insert( make_pair( 'g', '4' ) );
        keyMap->insert( make_pair( 'h', '4' ) );
        keyMap->insert( make_pair( 'i', '4' ) );
        keyMap->insert( make_pair( 'j', '5' ) );
        keyMap->insert( make_pair( 'k', '5' ) );
        keyMap->insert( make_pair( 'l', '5' ) );
        keyMap->insert( make_pair( 'm', '6' ) );
        keyMap->insert( make_pair( 'n', '6' ) );
        keyMap->insert( make_pair( 'o', '6' ) );
        keyMap->insert( make_pair( 'p', '7' ) );
        keyMap->insert( make_pair( 'q', '7' ) );
        keyMap->insert( make_pair( 'r', '7' ) );
        keyMap->insert( make_pair( 's', '7' ) );
        keyMap->insert( make_pair( 't', '8' ) );
        keyMap->insert( make_pair( 'u', '8' ) );
        keyMap->insert( make_pair( 'v', '8' ) );
        keyMap->insert( make_pair( 'w', '9' ) );
        keyMap->insert( make_pair( 'x', '9' ) );
        keyMap->insert( make_pair( 'y', '9' ) );
        keyMap->insert( make_pair( 'z', '9' ) );
    }
    m_rootItem->newWord( ".", 0, 1 );
    m_rootItem->newWord( ",", 0, 1 );
    m_rootItem->newWord( "?", 0, 1 );
}

T9::~T9()
{
    delete m_rootItem;
    delete keyMap;
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
        cerr << "Not such word in the dictionary.\n";

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
