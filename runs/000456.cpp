#include <string>
#include <map>
#include <vector>
#include <list>
#include <iostream>

namespace T9
{
	using std::string;
	using std::map;
	using std::vector;
	using std::list;
	using std::istream;
	using std::ostream;

	typedef size_t Rating;
	class T9Word
	{
	public:
		T9Word( const string &str, Rating r ): word(str), rate(r) {}

		inline void   inc()          { ++rate; }
		inline Rating rating() const { return rate; }	
		inline const char * c_str() const { return word.c_str(); }

	private:
		string word;
		Rating rate;
	};

	/**********************************************************************
	/ T9Code обеспечивает несколько операций над кодами.
	**********************************************************************/
	class T9Code
	{
	public:
		T9Code( const string &str );

		inline size_t len() const { return code.size(); }

		bool operator==( const T9Code &other ) const ;
		bool operator< ( const T9Code &other ) const ;
		inline char & operator[]( size_t idx ) { return code[idx]; }

	private:
		vector<char> code;
	};

	/**********************************************************************
	/ T9WordList содержит список слов с кодами codeOfWords.
	**********************************************************************/
	class T9WordList
	{
	public:		
		T9WordList() {}

		void addWord( const T9Word &wrd );
		const T9Word & word( size_t skip );

	private:
		typedef list< T9Word > WordList;
		WordList words;
	};

	template< size_t MaxWordLen >
	class T9Dictionary
	{
	public:
		T9Dictionary() {}

		void addWord( const string &str, Rating rate );

		const T9Word & word( const string &str );

		void parse( istream &in, ostream &out );

	private:
		typedef map< T9Code, T9WordList > Map;
		Map codes [MaxWordLen] [8];
		// codes[idx1][idx2]
		// idx1 - максимальная длина слова в словаре
		// idx2 - начало кода слова, idx2==0 если код начинается с '2'
	};

	template< size_t MaxWordLen >
	void T9Dictionary<MaxWordLen>::addWord( const string &str, Rating rate )
	{
		T9Word word( str, rate );
		const size_t len = str.length();
		T9Code code( str );
		T9WordList list;
		
		std::pair< Map::iterator, bool > ret = codes[ len-1 ][ code[0]-1 ].insert( std::make_pair( code, list ) );
		ret.first->second.addWord( word );
	}

	template< size_t MaxWordLen >
	const T9Word & T9Dictionary<MaxWordLen>::word( const string &str )
	{
		T9Code code( str );
		const size_t len = code.len();
		size_t skip = str.length() - len;

		return codes[ len-1 ][ code[0]-1 ][ code ].word( skip );
	}

	template< size_t MaxWordLen >
	void T9Dictionary<MaxWordLen>::parse( istream &in, ostream &out )
	{
		const size_t punctuationMarkCount = 3;
		const char punctuationMark[punctuationMarkCount] = { '.', ',', '?' };
		string w;
		while( in )
		{
			char ch = in.get();
			if( ch == '1' ) // ch == '1'
			{
				if( !w.empty() )
				{
					out << word( w ).c_str();
					w.clear();
				}
				size_t count = 0;
				while( in && ( ch = in.get() )=='*' ) ++count;
				out << punctuationMark[count%punctuationMarkCount];
			}
			if( '2'<=ch && ch<='9' || ch=='*' )
				w.push_back(ch);
			else if( ch == ' ' )
			{
				if( !w.empty() )
				{
					out << word( w ).c_str();
					w.clear();
				}
				out << ' ';
			}
		}
		if( !w.empty() )
			out << word( w ).c_str();
	}

	T9Code::T9Code( const string &str )
	{
		const size_t len = str.length();
		code.reserve(len);
		for( size_t i = 0; i < len; ++i )
		{
			if( str[i]=='a' || str[i]=='b' || str[i]=='c' )
				code.push_back(2);
			else if( str[i]=='d' || str[i]=='e' || str[i]=='f' )
				code.push_back(3);
			else if( str[i]=='g' || str[i]=='h' || str[i]=='i' )
				code.push_back(4);
			else if( str[i]=='j' || str[i]=='k' || str[i]=='l' )
				code.push_back(5);
			else if( str[i]=='m' || str[i]=='n' || str[i]=='o' )
				code.push_back(6);
			else if( str[i]=='p' || str[i]=='q' || str[i]=='r' || str[i]=='s' )
				code.push_back(7);
			else if( str[i]=='t' || str[i]=='u' || str[i]=='v' )
				code.push_back(8);
			else if( str[i]=='w' || str[i]=='x' || str[i]=='y' || str[i]=='z' )
				code.push_back(9);
			else if( '2'<=str[i] && str[i]<='9' )
				code.push_back( str[i]-'2'+2 );
			else
				break;
		}
	}

	bool T9Code::operator==( const T9Code &other ) const
	{
		const size_t len = other.code.size();
		if( len != code.size() )
			return false;

		for( size_t i = 0; i < len; ++i )
			if( code[i] != other.code[i] )
				return false;

		return true;
	}

	bool T9Code::operator<( const T9Code &other ) const
	{
		const size_t len = other.code.size();
		if( len < code.size() )
			return false;

		for( size_t i = 0; i < len; ++i )
		{
			if( code[i] < other.code[i] )
				return true;
			else if( code[i] > other.code[i] )
				return false;
		}

		return false;
	}

	void T9WordList::addWord( const T9Word &wrd )
	{
		WordList::iterator it = words.begin();
		for( WordList::iterator end = words.end(); (it != end); ++it )
		{
			if( it->rating() < wrd.rating() )
				break;
		}	
		words.insert(it, wrd);
	}

	const T9Word & T9WordList::word( size_t skip )
	{
		WordList::iterator begin = words.begin(), it = begin;
		for( WordList::iterator end = words.end(); skip; ++it, --skip );

		T9Word &w = *it;
		w.inc();

		WordList::iterator jt = it, tt = jt;
		for( ;; )
		{
			if( jt != begin )
			{
				tt = jt--;
				if( jt->rating() > w.rating() )
					break;
			}
			else
			{
				if( jt->rating() <= w.rating() )
					tt = jt;
				break;
			}
		}

		tt = words.insert(tt, w);
		words.erase(it);

		return *tt;
	}

}

int main(int argc, char *argv[])
{
	using std::cin;
	T9::T9Dictionary<20> dic;
	size_t wordCount, rate;
	std::string str;
	
	cin >> wordCount;
	for( size_t i = 0; i < wordCount; ++i )
	{
		cin >> str >> rate;
		dic.addWord( str, rate );
	}
	dic.parse( cin, std::cout ); 
}
