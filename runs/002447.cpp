#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <string>

using std::string ;
using std::vector ;
using std::pair ;
using std::map ;
using std::list ;
using std::cin ;
using std::cout ;

const int GLOBALnButtons = 8 ;
const int GLOBALbuttonsByLetter[] = { 0 , 0 , 0 , 1 , 1 , 1 , 2 , 2 , 2 , 3 , 3 , 3 , 4 , 4 , 4 , 5 , 5 , 5 , 5 , 6 , 6 , 6 , 7 , 7 , 7 , 7 } ;
const int GLOBALnPunctuation = 3 ;
const char GLOBALpunctuation[] = { '.' , ',' , '?' } ; 

class Node ;
class Dictionary ;
class T9 ;

//a field in Node
class Dictionary{
public:
	Dictionary() ;
	// ( pos )
	int getIndexAndIncreaseFrequency( int pos ) ;
	// ( log( min( size , #frequencies ) ) )
	void addIndex( int indexToAdd , int frequency ) ;
private:
	//lists ARE to be nonempty
	map< int , list< int > > listsWithIndexes ;
	//sum of lists' sizes 
	int size ;
};

// each Node corresponds to a certain succession of letter-buttons pressed
class Node{
public:
	//when you press a letter-button , you pass over the corresponding link
	vector< Node * > linksByButton ;
	Dictionary nodeDictionary ;

	Node( int nButtons ) ;
};

//main class, node and string container
class T9{
public:
	T9() ;
	// ( N * min( log( F ) , log( N ) ) )
	void getDictionaryFromCin() ;
	// ( command length )
	void getTaskFromCoutAndParceAndPrint() ;
	

private:
	//to delete nodes in destructor
	list< Node > nodesToSupply ;
	
	//the root node having empty dictionary
	Node rootNode ;
	//to handle dictionary operating : only indexes are copied
	vector< string > allStrings ;

	//cout << parced string ; ( command length )
	void parceAndPrint( const string &sourceString ) ;
	// creates links on first use ( 1 )
	Node *getLinkByButton( Node *argNode , int button ) ;

};

//---------------------------------------------------------------------------------

Dictionary::Dictionary() : listsWithIndexes() {
	size = 0 ;
};

int Dictionary::getIndexAndIncreaseFrequency( int pos ){
	// get listIt and indexIt ( pos )
	if ( size == 0 ){
		return 0 ;
	};
	pos = pos % size ;
	map< int , list< int > >::iterator listIt = listsWithIndexes.end() ;
	while ( pos >= ( int )( --listIt)->second.size() ){
		pos -= ( int )listIt->second.size() ;
	};

	list< int >::iterator indexIt = listIt->second.begin() ;
	advance( indexIt , pos ) ;
	int answerToReturn = *indexIt ;

	//update frequency ( amm. 1 )
	bool newFrequencyExists = false ;
	map< int , list< int > >::iterator listItNext = listIt ;
	++listItNext ;
	if ( listItNext != listsWithIndexes.end() ){
		if ( listItNext->first == listIt->first + 1 ){
			newFrequencyExists = true ;
		};
	};
	
	if ( listIt->second.size() == 1 ){
		if ( newFrequencyExists ){
			//erase this list and stack string to next list ( amm. 1 )
			listItNext->second.push_front( *indexIt ) ;
			listsWithIndexes.erase( listIt ) ;
		}else{
			//increase key , bit risky but we have checked conditions ( 1 )
			*( const_cast< int * >(  &( listIt->first )  ) ) += 1 ;
		};
	}else{
		if ( newFrequencyExists ){
			//erase string and push string ( 1 )
			listItNext->second.push_front( *indexIt ) ;
			listIt->second.erase( indexIt ) ;
		}else{
			//insert new list ( 1 )
			listsWithIndexes.insert( listIt , pair< int , list< int > >( listIt->first + 1 , list< int >( 1 , *indexIt ) ) ) ;
			listIt->second.erase( indexIt ) ;
		};
	};

	return answerToReturn ;
};

void Dictionary::addIndex( int index , int frequency ){
	// ( < log( diff frequencies = F = 1000 ) )
	listsWithIndexes[ frequency ].push_back( index ) ;
	size += 1 ;
};

//---------------------------------------------------------------------------------

Node::Node( int nButtons ) : linksByButton( nButtons , ( Node * )0 ) {
};

//---------------------------------------------------------------------------------

T9::T9() : nodesToSupply() , rootNode( GLOBALnButtons ) , allStrings( 1 , "<EMPTY NODE>" ) {
};

void T9::parceAndPrint( const string &sourceString ){
	enum { SPACE , WORD , WORD_STAR , PUNCT , PUNCT_STAR } state = SPACE ;
	Node *currentNode ;
	int nStars ;

	for( int charIndex = 0 ; charIndex < ( int )sourceString.size() ; ++charIndex ){
		char newChar = sourceString[ charIndex ] ;
		switch ( newChar ){
			case ' ' :
				if ( state == WORD || state == WORD_STAR ){
					cout << allStrings[ currentNode->nodeDictionary.getIndexAndIncreaseFrequency( nStars ) ] ;
				};
				if ( state == PUNCT || state == PUNCT_STAR ){
					cout << GLOBALpunctuation[ nStars % GLOBALnPunctuation ] ;
				};
				cout << ' ' ;
				state = SPACE ;
				break ;
			case '*' : 
				if ( state == WORD || state == WORD_STAR ){
					nStars += 1 ;
					state = WORD_STAR ;
					break ;
				};
				if ( state == PUNCT || state == PUNCT_STAR ){
					nStars += 1 ;
					state = PUNCT_STAR ;
					break ;
				};
				cout << "<STAR AFTER SPACE>" ;
				break ;
			case '1' :
				if ( state == WORD || state == WORD_STAR ){
					cout << allStrings[ currentNode->nodeDictionary.getIndexAndIncreaseFrequency( nStars ) ] ;
				};
				if ( state == PUNCT || state == PUNCT_STAR ){
					cout << GLOBALpunctuation[ nStars % GLOBALnPunctuation ] ;
				};
				state = PUNCT ;
				nStars = 0 ;
				break ;
			default :
				if ( state == WORD_STAR ){
					cout << allStrings[ currentNode->nodeDictionary.getIndexAndIncreaseFrequency( nStars ) ] ;
					cout << "<WORD RIGHT AFTER WORD>" ;
				};
				if ( state == PUNCT || state == PUNCT_STAR ){
					cout << GLOBALpunctuation[ nStars % GLOBALnPunctuation ] ;
				};

				if ( state != WORD ){
					currentNode = &rootNode ;
					nStars = 0 ;
				};
				state = WORD ;
				currentNode = getLinkByButton( currentNode , newChar - '2' ) ;
		};
	};
	if ( state == WORD || state == WORD_STAR ){
		cout << allStrings[ currentNode->nodeDictionary.getIndexAndIncreaseFrequency( nStars ) ] ;
	};
	if ( state == PUNCT || state == PUNCT_STAR ){
		cout << GLOBALpunctuation[ nStars % GLOBALnPunctuation ] ;
	};		
};

Node *T9::getLinkByButton( Node *argNode , int button ){
	if ( argNode->linksByButton[ button ] == 0 ){
		nodesToSupply.push_back( Node( GLOBALnButtons ) ) ;
		argNode->linksByButton[ button ] = &( nodesToSupply.back() ) ;
	};

	return argNode->linksByButton[ button ] ;
};

void T9::getDictionaryFromCin(){
	int nEntries ;
	cin >> nEntries ;
	int timesUsed ;
	for( int entriesRead = 0 ; entriesRead < nEntries ; ++entriesRead ){
		allStrings.push_back( string() ) ;
		cin >> allStrings.back() >> timesUsed ;
		string &lastString = allStrings.back() ;

		Node *destinationNode = &rootNode ;
		for( int charIndex = 0 ; charIndex < ( int )( lastString.size() ) ; ++charIndex ){
			destinationNode = getLinkByButton( destinationNode , GLOBALbuttonsByLetter[ lastString[ charIndex ] - 'a' ] ) ;
		};

		destinationNode->nodeDictionary.addIndex( ( int )allStrings.size() - 1 , timesUsed ) ;
	};
};

void T9::getTaskFromCoutAndParceAndPrint(){
	string task ;
	//2x to handle excess '\n'
	std::getline( cin , task ) ;
	std::getline( cin , task ) ;
	parceAndPrint( task ) ;
};

//---------------------------------------------------------------------------------

int main(){
	T9 t9 ;
	t9.getDictionaryFromCin() ;
	t9.getTaskFromCoutAndParceAndPrint() ;
	return 0 ;
};


