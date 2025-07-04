#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <string>
#include <cassert>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::string;
using std::stringstream;

class Word {
public:
    Word( 
        const string & word,
        int priority1,
        int priority2 ) 
    :
        word_( word ),
        priority1_( priority1 ),
        priority2_( priority2 )
    {}

    const string word() const {
        return word_;
    }

    const int priority1() const {
        return priority1_;
    }

    const int priority2() const {
        return priority2_;
    }

    void SetWord( const string & word ) {
        word_ = word;
    }

    void SetPriority1( const int priority1 ) {
        priority1_ = priority1;
    }

    void SetPriority2( const int priority2 ) {
        priority2_ = priority2;
    }

    bool operator == ( const Word & other_word ) const {
        return 
            word_ == other_word.word_ &&
            priority1_ == other_word.priority1_ &&
            priority2_ == other_word.priority2_;
    }

    bool operator < ( const Word & other_word ) const {
        if ( priority1_ == other_word.priority1_ ) {
            return priority2_ > other_word.priority2_;
        }
        return priority1_ < other_word.priority1_;
    }

private:
    string word_;
    int priority1_;
    int priority2_;
};

string FromWordToCode( const string & word ) {
    string result;
    for ( int index = 0; index < (int)word.size(); ++index ) {
        switch( word[ index ] ) {
            case 'a':
            case 'b':
            case 'c':
                result += '2';
                break;
            case 'd':
            case 'e':
            case 'f':
                result += '3';
                break;
            case 'g':
            case 'h':
            case 'i':
                result += '4';
                break;
            case 'j':
            case 'k':
            case 'l':
                result += '5';
                break;
            case 'm':
            case 'n':
            case 'o':
                result += '6';
                break;
            case 'p':
            case 'q':
            case 'r':
            case 's':
                result += '7';
                break;
            case 't':
            case 'u':
            case 'v':
                result += '8';
                break;
            case 'w':
            case 'x':
            case 'y':
            case 'z':
                result += '9';
                break;

            default:
                //there is an error over here
                assert( 0 );
        };
    }

    return result;
}

void InputWords( 
    vector<int> & second_priorities,
    map<string, vector<Word> > & code_words ) 
{
    int number_of_words;
    scanf( "%d", &number_of_words );

    for ( int word_index = 0; word_index < number_of_words; ++word_index ) {
        string word;
        int frequency;
        
        cin >> word >> frequency;

        //because alphabetic order, the further
        //he goes, the lower priority he gets
        int second_priority = ++second_priorities.at( frequency - 1 );

        code_words[ FromWordToCode( word ) ].push_back( 
            Word( word, frequency, second_priority ));
    }
}

//NEED SOMETHING TO DO_____________________________
void InputMessage( string * message ) {
    char buf[ 100000 ];
    gets( buf ); 
    gets( buf );
    *message = buf;
}

void Output( const string & word ) {
    cout << word;
}

bool IsToken( char c ) {
    return c >= '2' &&
        c <= '9';
}

bool IsPunctuation( char c ) {
    return c == '1';
}

bool IsStar( char c ) {
    return c == '*';
}

int NumberOfStarsGoingNext(
    int & position,
    const string & message ) 
{
    int number_of_stars = 0;
    while ( position < (int)message.size() &&
        IsStar( message.at( position ))) 
    {
        ++number_of_stars;
        ++position;
    }   

    return number_of_stars;
}

char GetPunctuation( int number_of_stars ) {
    const char * punctuation = ".,?";
    return punctuation[ number_of_stars % 3 ];
}

string GetWord(
    const string & code,
    const int number_of_stars,
    map<string, vector<Word> > & code_words,
    vector<int> & second_priorities )
{
    vector<Word> & words = code_words[ code ];

    assert( words.size() > 0 );

    sort( words.begin(), words.end());

    Word & my_word = words.at( words.size() - number_of_stars % words.size() - 1 );

    my_word.SetPriority1( my_word.priority1() + 1 );

    if ( second_priorities.at( my_word.priority1() - 1 ) >= 0 ) {
        second_priorities.at( my_word.priority1() - 1 ) = -1;
        my_word.SetPriority2( -1 );
    } else {
        my_word.SetPriority2( --second_priorities.at( my_word.priority1() - 1 ));
    }

    return my_word.word();
}

void ProcessMessage( 
    const string & message,
    map<string, vector<Word> > & code_words,
    vector<int> & second_priorities,
    string * real_message ) 
{
    for ( int pos = 0; pos < (int)message.size(); ++pos ) {
        if ( message.at( pos ) == ' ' ) {
            real_message->push_back( ' ' );
        } 
        else if ( IsToken( message.at( pos ))) {
            //getting code
            string code;
            while ( 
                pos < (int)message.size() &&
                IsToken( message.at( pos ))) 
            {
                code += message.at( pos++ );
            }

            int number_of_stars = NumberOfStarsGoingNext( pos, message );
            
            *real_message += GetWord( code, number_of_stars, 
                code_words, second_priorities );

            --pos;
        }
        else if ( IsPunctuation( message.at( pos ))) {
            int number_of_stars = NumberOfStarsGoingNext( ++pos, message );
            *real_message += GetPunctuation( number_of_stars );
            --pos;
        }
    }
}

int main() {
    const int max_frequency = 10000;
    vector<int> second_priorities( max_frequency, 0 );

    map<string, vector<Word> > code_words;
    InputWords( second_priorities, code_words );

    string message; 
    InputMessage( &message );

    string real_message;
    ProcessMessage( message, code_words, second_priorities, &real_message );

    Output( real_message );
 
	return 0;
}