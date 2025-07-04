#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <functional>
#include <stdexcept>
#include <cstddef>
#include <cstdlib>


namespace phone
{	
	class Numbers  // кнопки на клавиатуре
	{
	public:
		virtual bool
			operator== ( const char ch ) const = 0;	
		virtual bool
			operator!= ( const char ch ) const = 0;
		
		virtual
			~Numbers() {}
	};
	
	class N2 : public Numbers
	{
	public:
		bool operator== ( const char ch ) const
		{
			return ch == 'a' || ch == 'b' || ch == 'c';
		}
		bool operator!= ( const char ch ) const
		{
			return ! this->operator==(ch);
		}
	};
	
	class N3 : public Numbers
	{
	public:
		bool operator== ( const char ch ) const
		{
			return ch == 'd' || ch == 'e' || ch == 'f';
		}
		bool operator!= ( const char ch ) const
		{
			return ! this->operator==(ch);
		}
	};
	
	class N4 : public Numbers
	{
	public:
		bool operator== ( const char ch ) const
		{
			return ch == 'g' || ch == 'h' || ch == 'i';
		}
		bool operator!= ( const char ch ) const
		{
			return ! this->operator==(ch);
		}
	};
	
	class N5 : public Numbers
	{
	public:
		bool operator== ( const char ch ) const
		{
			return ch == 'j' || ch == 'k' || ch == 'l';
		}
		bool operator!= ( const char ch ) const
		{
			return ! this->operator==(ch);
		}
	};
	
	class N6 : public Numbers
	{
	public:
		bool operator== ( const char ch ) const
		{
			return ch == 'm' || ch == 'n' || ch == 'o';
		}
		bool operator!= ( const char ch ) const
		{
			return ! this->operator==(ch);
		}
	};
	
	class N7 : public Numbers
	{
	public:
		bool operator== ( const char ch ) const
		{
			return ch == 'p' || ch == 'q' || ch == 'r' || ch == 's';
		}
		bool operator!= ( const char ch ) const
		{
			return ! this->operator==(ch);
		}
	};
	
	class N8 : public Numbers
	{
	public:
		bool operator== ( const char ch ) const
		{
			return ch == 't' || ch == 'u' || ch == 'v';
		}
		bool operator!= ( const char ch ) const
		{
			return ! this->operator==(ch);
		}
	};
	
	class N9 : public Numbers
	{
	public:
		bool operator== ( const char ch ) const
		{
			return ch == 'w' || ch == 'x' || ch == 'y' || ch == 'z';
		}
		bool operator!= ( const char ch ) const
		{
			return ! this->operator==(ch);
		}
	};
	
	
	bool operator==( const char ch, const Numbers& n )
	{
		return n == ch;
	}
	
	bool operator!=( const char ch, const Numbers& n )
	{
		return n != ch;
	}
	
	
	
	/*******************************************************/
	
	
	
	class Words
	{	
	public:
		
		// __k_numbers - вектор кнопок, которым
		//соответствуют буквы на клавиатуре 
		
		typedef std::vector<Numbers*>							__k_numbers;
		typedef unsigned int	 								__int;
		typedef std::list<std::string>							__words; 		//  коллекция слов
		typedef std::map<__int, __words, std::greater<__int> >	__words_counter; // словарь (счетчик, слова)
		
		
		// добавить слово в словарь с счетчиком __int
		void
		insert ( __int, const std::string& );
		
		
		// получить первое подходящее слово
		/* вектор нажатых кнопок, кол-во звездочек, длина искомого слова */
		const std::string&	
		top ( const __k_numbers&, __int, unsigned char );
		
	private:
		
		// переместить слово в новый "счетчик"
		void
		rmv ( __int, const std::string& );
		
		// подходит ли слово к нажатым кнопкам?
		bool	
		equal	( const std::string&, const __k_numbers& ) const; // слово, список нажатых кнопок
		
	//MEMBERS
		mutable
		__words_counter w_; // счетчик слов
		
	}; // Words
	
	
	
	/*******************************************************/
	
	
	
	class T9
	{	
	public:
		
		typedef Words::__int			__int;
		typedef Words::__k_numbers		__k_numbers;
		typedef Words::__words			__words;
		typedef Words::__words_counter	__words_counter;	
		
		T9() : keys_(8) { numbers_init(); }
		~T9();
		
		// добавить слово и приоретет в словарь
		void
		add ( __int n, const std::string& s );
		
		// поиск слова
		const std::string
		find( const std::string& ) const;
		
		
	private:
		
		void
		numbers_init()
		{
			vnP_.push_back( new N2 );
			vnP_.push_back( new N3 );
			vnP_.push_back( new N4 );
			vnP_.push_back( new N5 );
			vnP_.push_back( new N6 );
			vnP_.push_back( new N7 );
			vnP_.push_back( new N8 );
			vnP_.push_back( new N9 );
		}
		
		//обрабатывает последовательности единиц и их звезд
		const std::string
		key_one( std::string::const_iterator&, std::string& ) const;
		
		// добавление знака препинания
		const char
		tchk( std::string::const_iterator& ) const;
		
		
	//Members
		
		mutable /* для top() */
		std::vector<Words> 	keys_;
		
		// объекты N2 - N9
		__k_numbers		 	vnP_;
		
	}; // T9
	
	
} // phone


///////////////////////////////////////////////////////////


void
phone::Words::insert ( __int num, const std::string& word )
{
	__words_counter::iterator iter = w_.find(num);
	
	if ( iter == w_.end() )
	{
		__words ws;
		
		ws.push_back(word);
		w_.insert( std::make_pair( num, ws ) );
	}
	else
	{
		iter->second.push_back(word);
	}
}


void
phone::Words::rmv ( __int num, const std::string& word )
{
	__words_counter::iterator iter = w_.find(num);
	
	if ( iter == w_.end() )
	{
		__words ws;
		
		ws.push_front(word);
		w_.insert( std::make_pair( num, ws ) );
	}
	else
	{
		iter->second.push_front(word);
	}
}


const std::string&
phone::Words::top ( const __k_numbers& vn, __int stars, unsigned char size )
{	
	__words_counter::iterator	w_c_beg	= w_.begin();
	__words_counter::iterator 	w_c_end	= w_.end();
	
	__words::iterator		beg;
	__words::iterator		end;
	
	std::pair<const __int, __words>* pair_ptr = 0;
	
	// начинаем обход всех вложенных словарей
	
	for ( ; w_c_beg != w_c_end; ++w_c_beg )
	{
		pair_ptr = &*w_c_beg; // текущая пара <кол-во использований, слова>
		
		beg = pair_ptr->second.begin();
		end = pair_ptr->second.end();
		
		for ( ; beg != end; ++beg )
		{	
			if ( beg->size() == size ) // если слово имеет нужную длину
			{	
				bool b = equal( *beg, vn ); // проверяем на совпадение
				
				if ( b && stars ) // если совпало по шаблону и есть звездочки
				{
					--stars;
				}	
				else
				if ( b ) // если совпало и звездочек нет
				{	
					__int counter = pair_ptr->first + 1; // увеличиваем счетчик слова на 1
					
					rmv( counter, *beg ); // добавляем слово в +1 счетчик
					
					pair_ptr->second.erase( beg ); // удаляем слово с текущего счетчика
					
					if ( pair_ptr->second.empty() ) // если счетчик пуст, удаляем его из map
					{ 
						w_.erase (w_c_beg);
					}
					
				 	return *w_.find( counter )->second.begin();
				}
			}
		}
	}
	
	// из расчета, что слово обязательно
	// присутствует в словаре. Иначе - 
	// рекурсия бесконечной глубины
	// -->
	
	return top( vn, stars, size ); // если пользователь любит нажимать много звездочек
}



bool
phone::Words::equal
	( const std::string& str, const __k_numbers& vn )
const
{
	__k_numbers::const_iterator beg = vn.begin();
	__k_numbers::const_iterator end = vn.end();
	
	for( __int i = 1; beg != end; ++i, ++beg ) // проверяем начиная со второго символа
	{
		if ( **beg != (str[i]) ) return false; // полиморфный operator!= объекта типа Numbers
	}
	return true;	
}


phone::T9::~T9()
{
	__k_numbers::iterator beg = vnP_.begin();
	__k_numbers::iterator end = vnP_.end();
	
	while ( beg != end )
	{
		delete *beg;
		++beg;
	}
}


void
phone::T9::add ( __int n, const std::string& s )
{
	for ( char i = 0; i < 8; ++i )
	{
		if ( *vnP_[i] == s[0] ) // полиморфный operator== объекта типа Numbers
		{
			keys_[i].insert( n, s );
			return;
		}
	}
}


const std::string
phone::T9::find( const std::string& str )
const
{
	std::string::const_iterator 	beg = str.begin();
	std::string::const_iterator 	end = str.end();
	std::string 					the_word;
	
	// если работаем с единицами
	if ( *beg == '1' )
/**/	return key_one( beg, the_word );
	
	
	__k_numbers 			vn; 					// нажатые пользователем клавиши
	unsigned short			n;		 				// буфер для разлиных целей
	char					ch[2] = { '\0', '\0' }; // для преобразования строки в число
	
	ch[0]	 = *beg++;
	char num = std::atoi( ch ); // № словаря
	
	// собираем информацию о нажатых кнопках
	
	while ( ch[0] = *beg,
		beg != end && ch[0] != '*' && ch[0] != '1' )
	{
		n = std::atoi( ch );
		
		switch(n)
		{
			case 2: vn.push_back( vnP_[n-2] );break;
			case 3: vn.push_back( vnP_[n-2] );break;
			case 4: vn.push_back( vnP_[n-2] );break;
			case 5: vn.push_back( vnP_[n-2] );break;
			case 6: vn.push_back( vnP_[n-2] );break;
			case 7: vn.push_back( vnP_[n-2] );break;
			case 8: vn.push_back( vnP_[n-2] );break;
			case 9: vn.push_back( vnP_[n-2] );break;
		}
		++beg;
	}
	
	n = 0; // для подсчета звездочек
	
	while ( *beg == '*' )
	{
		++n;
		++beg;
	}
	
 	the_word = keys_[num-2].top( vn, n, vn.size() + 1 ); // получаем слово

	if ( beg == end )
	{
/**/	return the_word;
	}
	
	// тут единица
	
	key_one( beg, the_word );
	
	// ecли после единиц есть еще цифры
	
	if ( beg != end )
	{
		the_word += find( std::string( beg, end ) );
	}
	
	return the_word;
}


const std::string
phone::T9::key_one( std::string::const_iterator& beg, std::string& str ) 
const
{
	while ( *beg == '1' )
	{
		str += tchk(beg);
		//++beg -> внутри функции tchk
	}
	return str;
}


const char
phone::T9::tchk
	( std::string::const_iterator& beg )
const
{
	__int n = 0; // для посчета звездочек
	
	++beg;
	
	while ( *beg == '*' )
	{
		++n;
		++beg;
	}
	
	while ( n > 2 )
	{
		n -= 3;
	}
	
	switch(n)
	{
		case 0: return '.';
		case 1: return ',';
		case 2: return '?';
	}
	throw std::logic_error("какая-то ошибка в подсчете звездочек в функции tchk...");
}



/***************************************/

#include <iomanip>

int main (int argc, char const *argv[])
{
	unsigned 			words, num;
	char				buf; // буфер для потока
	phone::T9 			t9;
	
	std::string 		temp_str;	// строковый буфер
	std::string 		num_str;	// числовой буфер
	std::size_t 		i;			// for char iterator
	
	
	while( (buf = std::cin.get()) != '\n' )
	{
		num_str += buf;	
	}
	
	words = std::atoi ( num_str.c_str() );

	num_str.clear();

	// добавляем слова в словарь
	for ( ; words; --words, temp_str.clear(), num_str.clear() )
	{	
		while ( (buf = std::cin.get()) != ' ' )
		{
			temp_str += buf;
		}
		
		while ( (buf = std::cin.get()) != '\n' )
		{
			num_str += buf;
		}
		
		num = std::atoi( num_str.c_str() );
		
		t9.add( num, temp_str );
	}
	
	
	// SMS
	std::string sms;
	
	std::getline (std::cin, sms);

	for ( i = 0 ; sms[i] != '\0'; temp_str.clear() )
	{	
		// обрабатываем набор последовательных символов
		for ( ; sms[i] != ' ' && sms[i] != '\0'; ++i )
		{
			temp_str += sms[i];
		}
		
		std::cout << t9.find( temp_str );
		
		// обрабатываем хвостовые пробулы
		for ( ; sms[i] == ' '; ++i)
		{
			std::cout << ' ';
		}
	}
	
	std::cout << '\n';
	
	return 0;
}