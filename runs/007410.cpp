#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <stdexcept>


namespace nmbs
{	
	// вычисляет наименьшее расстояние по Хемингу
	class N_analizator
	{
	public:
		
		N_analizator() {}
		
		N_analizator( unsigned length )
		{
			length_ = length;
		}
		
		void
		new_type	( unsigned length )
		{
			length_ = length;
		}
		
		unsigned
		operator()	( const std::vector<char>& vch, const std::vector<std::string>& var ) const
		{
			unsigned result = length_;
			unsigned temp_length;
			
			for ( unsigned i = 0; i < var.size(); ++i )
			{
				temp_length = this->start_alg( vch, var[i] );
				if ( result > temp_length )
				{
					result = temp_length;
				}
			}
			
			return result;
		}

	private:
		
		// расстояние по Хемингу
		unsigned
		start_alg	( const std::vector<char>& vch, const std::string& str ) const
		{
			unsigned counter = 0;
			
			for ( unsigned i = 0; i < length_; ++i )
			{
				if( vch[i] != str[i] ) ++counter;
			}
			
			return counter;
		}
		
	//members
	
		unsigned length_; // длинна сравниваемых векторов
		
	};
	
	// база эталонов
	struct Etalons
	{
		typedef std::vector< std::vector<std::string> >		__etalons;
		
		Etalons() : etalons_(10)
		{
			etalons_[0].push_back("00011100011101100100001111000001100000011000001110000001100000011000000110000001100000011000000110000001100000010110001101111111");
			etalons_[0].push_back("00000000001111000111111001111111000000000000001111111111111010000000000000000000111000001110000011111000111110000000000000000000");
			etalons_[1].push_back("00001000000010000010100001001000000010000001000000001000000100000000100000010000000000000000000000000000000000000000000000000000");
			etalons_[1].push_back("00000001000000100000100100100001000000010000000100000001000000100000000100000000000000000000000000000000000000000000000000000000");
			etalons_[2].push_back("00011100001000110100000110000001100000010000000100000001000000100000010000011000000100000011000000100000001000011101101110111111");
			etalons_[3].push_back("00011000011001101100001011000001100000110000001100000111000011000000010000000010000000110000000100000001000000101100001000111000");
			etalons_[4].push_back("00001000000100100001000000001010000100000001001000100100001000100100000001000110100001101111110100000110000001100000001000000010");
			etalons_[5].push_back("00111111001111110010000010000000100000000100110010111100101001000000111100000101000110010001000111000011110000100100010001100110");
			etalons_[6].push_back("00010000001100000010000001100000110000001100000010011100111000101100000111000001110000011100000110000001100000011100001001111100");
			etalons_[7].push_back("11111111100000011000001100000010000001100000010000000100000010000000100000001000000100000001000000010000000100000001000000010000");
			etalons_[8].push_back("00011000001111100100000101000011110000110110000101100011011110000011010000110100110000101100000111000001100000010111000101101100");
			etalons_[9].push_back("00111000001001000100001010000001100000011000000110000001100000010100000100111001000000010000001000000010100000101000010000111000");
		}
		
		__etalons 		etalons_; // этоланы 8х16 (128 символов)
	};
	
	
	
	// распознаватель
	class A : Etalons
	{
	public:
		typedef unsigned short int							__int;
		typedef std::vector<std::vector<char> > 			__matrix;
		typedef std::vector<__matrix>						__objects;
		
		
		// принимаем картинку из потока
		void
		init 					( std::istream& );
		
		// отправляем результат в поток
		void
		result					( std::ostream& ) 						const;
		
	private:
		
		// проверяет вектор на наличие мусора ( мусор все, что не char )
		bool
		gorizontal_char_trash 	( std::vector<char>&, char ) 			const;
		
		// стирает символы # и % по вертикали, если в вертикали не встретился @
		void
		vertical_char_trash		( __matrix& ) 							const;
		
		// приводит изображаение к бинарному виду
		void
		binary_img				( __matrix& ) 							const;
		
		// помечает на бинарном изображении первый не помеченный объект маркером __int
		void
		wave 					( __matrix&, int, int, __int )			const;
		
		// маркирует все объекты на изображении, запуская wave
		__int
		marking					( __matrix& )							const;
		
		// сегментация изображения, захват всех помеченных объектов, удовл. условию
		void
		segmentation			( const __matrix&, __int );
		
		// захват из __matrix помеченного маркером __int объекта,
		// добавляя объект в __objects
		void
		catch_object			( __objects&, __int, const __matrix& ) 			const;
		
		// счетчик символа char в __matrix
		__int
		char_counter			( const __matrix&, char )						const;
		
		// ищет в const __matrix путоты по горизонтали и вертикали
		// матрица без пустот сохраняется в __matrix
		void
		cut_empty				( const __matrix&, __matrix& )					const;
		
		// анализирует матрицу с цифрой, возвращает результат
		// unsigned char для dev_line
		// char для pixel_analiz
		__int
		number_analiz			( const __matrix&, unsigned char, char )		const;
		
		// рекурсивная функция деления отрезка int-int на 2 ^ unsigned char частей
		// все точки сохраняются в std::set<int>
		void
		dev_line				( int, int, unsigned char, std::set<int>& )		const;
		
		
		// анализирует кол-во пустот в квадраде int, int, int, int
		// в матрице const __matrix. Возвращает '0' или '1',
		//  в зависимости от заполнености. При совпадении кол-ва
		// пустот и не пустот, возвращает char, который принимает '0' или '1'
		char
		pixel_analiz			( int, int, int, int, const __matrix&, char )	const;
		
	//members	
		
		__matrix 		m_; 	// изображение, с которым работам
		__objects		objs_; //  сегментированные объекты (цифры)
		
	};
}
/////////////////////////

void
nmbs::A::init ( std::istream& strm )
{
	std::string 		str;
	std::vector<char> 	vch;
	
	for ( ; strm.good(); vch.clear() )
	{
		std::getline( strm, str );
		
		for ( __int i = 0; i < str.size(); ++i )
		{
			if ( str[i] == '.' || str[i] == '@' || str[i] == '#' || str[i] == '%') 
			
				vch.push_back(str[i]);
		}
		
		if ( vch.empty() ) 						continue;
		if ( gorizontal_char_trash(vch, '@') )  continue;
		
		m_.push_back(vch);
	}
	
	vertical_char_trash		(m_);
	binary_img				(m_);
	
	__int limit = marking 	(m_);

	segmentation			(m_, limit);
}



void
nmbs::A::result	( std::ostream& strm ) const
{
	for ( __int i = 0; i < objs_.size(); ++i )
	{
		
		if( objs_[i][0].size() < 8 && objs_[i].size() > 15 )
		{
			strm << '1';
			continue;
		}
		
		
		if( objs_[i][0].size() < 25 )
		{
			strm << number_analiz( objs_[i], 3, '1' );
			continue;
		}
	
		strm << number_analiz( objs_[i], 3, '0' );
		
	}
}



////////////// private

bool
nmbs::A::gorizontal_char_trash ( std::vector<char>& v, char ch ) const
{
	__int 	size 		= v.size();
	double 	counter 	= 0;
	
	for ( __int i = 0; i < size; ++i )
	{
		if ( v[i] != ch ) ++counter;
	}
	
	// если строка заполнена одним типом символов
	if ( counter > (size * 0.95) || counter < 2 )
	
		return true;
		
	return false;
}


void
nmbs::A::vertical_char_trash ( __matrix& m ) const
{
	__int H 	= m.size();
	__int W		= m[0].size();
	
	std::vector<__int>					buf;
	std::vector<__int>::const_iterator	iter, end;
	
	for ( __int i = 0; i < W; ++i, buf.clear() )
	{
		bool flag = false;
		
		for ( __int j = 0; j < H; ++j )
		{
			if ( m[j][i] == '@' )
			{ 
				flag = true; break;
			}
			if ( m[j][i] == '%' || m[j][i] == '#')
			{
				buf.push_back(j);
			}
		}
		
		if ( ! flag && ! buf.empty() )
		{
			for ( iter = buf.begin(), end = buf.end(); iter != end; ++iter )
			{
				m[*iter][i] = '.';
			}
		}
	}
}



void
nmbs::A::binary_img	( __matrix& m ) const
{
	__int H 	= m.size();
	__int W		= m[0].size();
	
	for ( __int i = 0; i < H; ++i )
		for ( __int j = 0; j < W; ++j )
		{
			if ( m[i][j] == '.' )										m[i][j] = 0;
			if ( m[i][j] == '@' || m[i][j] == '#' || m[i][j] == '%' ) 	m[i][j] = 1;
		}
}



void
nmbs::A::wave ( __matrix& m, int x, int y, __int flag ) const
{
	int ILimit = m.size();
	int JLimit = m[0].size();
	
	for ( int i = x-1; i <= x+1; ++i )
		for ( int j = y-1; j <= y+1; ++j )
		{
			if ( i < 0 || j < 0 || i >= ILimit || j >= JLimit ) continue;
			
			if( m[i][j] == 1 )
			{
				m[i][j] = flag;
				this->wave ( m, i, j, flag );
			}
		}
}


nmbs::A::__int
nmbs::A::marking( __matrix& m ) const
{
	__int sgm 		= 1;
	__int middle 	= m.size()/2;
	__int final		= m[0].size();
	
	
	for ( __int i = 0; i < final; ++i )
	{	
		if ( m[middle][i] == 1 )
		{	
			wave( m, middle, i, ++sgm );
		}
	}	
	
	if ( sgm > 1 )
		return sgm;
	throw std::logic_error("изображение должно быть не пустое");
}


void
nmbs::A::segmentation ( const __matrix& matrix, __int limit )
{
	for ( __int index = 2; index <= limit; ++index )
	{
		if ( char_counter(matrix, index) < 16 ) continue;
		
		catch_object( objs_, index, matrix );
	}
}



void
nmbs::A::catch_object( __objects& objs, __int type, const __matrix& m ) const
{	
	__int H 		= m.size();
	__int W			= m[0].size();
	
	__matrix temp_m( H );
	
	for ( __int i = 0; i < H; ++i )
		for ( __int j = 0; j < W; ++j )
		{
			if ( m[i][j] == 0 || m[i][j] == type )	temp_m[i].push_back( m[i][j]  );
			else									temp_m[i].push_back( 0 );
		}
	
	objs.push_back( __matrix() );
	
	cut_empty( temp_m, objs.back() );
}



nmbs::A::__int
nmbs::A::char_counter ( const __matrix& m, char type ) const
{
	__int H 		= m.size();
	__int W			= m[0].size();
	__int counter 	= 0;	
	
	for ( __int i = 0; i < H; ++i )
		for ( __int j = 0; j < W; ++j )
		{
			if ( m[i][j] == type ) ++counter;
		}
		
	return counter;
}



void
nmbs::A::cut_empty ( const __matrix& m, __matrix& temp ) const
{
	__int H 	= m.size();
	__int W		= m[0].size();
	
	bool		flag = false;
	
	int left, right;
	
		
	for ( left = 0; left < W; ++left )
	{
		for ( __int j = 0; j < H; ++j )
		{
			if ( m[j][left] != 0 ) { flag = true; break; }
		}
		if(flag) break;
	}
	
	flag = false;
	
	for ( right = W-1; right >= 0; --right )
	{
		for ( __int j = 0; j < H; ++j )
		{
			if ( m[j][right] != 0 ) { flag = true; break; }
		}
		if(flag) break;
	}
	
		
	flag = false;
	
	
	for ( __int i = 0; i < H; ++i )
	{
		flag = false;
		
		for ( __int j = left; j <= right; ++j )
		{
			if ( m[i][j] != 0 ) { flag = true; break; }
		}
		if ( flag )
		{
			temp.push_back( std::vector<char>() );
			
			std::vector<char>* v_ptr = &temp.back();
			
			for ( __int j = left; j <= right; ++j )
			{
				v_ptr->push_back( m[i][j] );
			}
		}
	}
}



nmbs::A::__int
nmbs::A::number_analiz( const __matrix& m, unsigned char bin_div, char ch ) const
{
	std::set<int> v; // vertical 
	
	v.insert( 0 );
	v.insert( m.size() );
	
	dev_line( 0, m.size(), 4, v );
	
	
	std::set<int> g; // gorizontal
	
	g.insert( 0 );
	g.insert( m[0].size() );
	
	dev_line( 0, m[0].size(), bin_div, g );
	
	
	std::vector<char> input_vector;
	
	std::set<int>::const_iterator v_iter = v.begin();
	std::set<int>::const_iterator v_end = v.end();
	
	std::set<int>::const_iterator g_beg = g.begin();
	
	std::set<int>::const_iterator g_iter = g_beg;
	std::set<int>::const_iterator g_end = g.end();
	
	std::set<int>::const_iterator v_iter_prev;
	std::set<int>::const_iterator g_iter_prev;
	
	++v_iter;
	
	while( v_iter != v_end )
	{
		v_iter_prev = --v_iter;
		++v_iter;
		
		g_iter = g_beg;
		++g_iter;
		
		while( g_iter != g_end )
		{
			g_iter_prev = --g_iter;
			++g_iter;
			
			input_vector.push_back( pixel_analiz( *v_iter_prev, *v_iter, *g_iter_prev, *g_iter, m, ch ) );
			
			++g_iter;
		}
		++v_iter;
	}
	
	
	N_analizator 			nlz		(128);
	__int 					min 	= 128;
	__int 					index 	= 0;
	__int					temp	= 0;
	
	for ( __int i = 0; i < 10; ++i )
	{
		temp = nlz( input_vector, etalons_[i] );
		
		if( temp < min )
		{
			min = temp;
			index = i;
		}
	}
	
	return index;
}


void
nmbs::A::dev_line( int a, int b, unsigned char count, std::set<int>& set ) const
{
	if ( !count ) return;
	
	int val = (b-a)/2;
	
	set.insert( a + val);
	
	dev_line( a, a + val, count-1, set );
	dev_line( a + val, b, count-1, set );
}



char
nmbs::A::pixel_analiz ( int i, int i_max, int j, int j_max, const __matrix& m, char ch ) const
{
	if ( ch != '0' && ch != '1' ) throw std::logic_error("ch != 0 && ch != 1");
	
	__int counter1 = 0;
	__int counter0 = 0;
	
	for ( ; i <= i_max; ++i )
		for ( ; j <= j_max; ++j )
		{
			if ( m[i][j] == 0 ) ++counter0;
			if ( m[i][j] != 0 ) ++counter1;
		}

	if ( counter0 == counter1 ) return ch;
	if ( counter0 > counter1 )	return '0';
	
	return '1';
}
///////////////////

int main (int argc, char const *argv[])
{	
	nmbs::A ta;
	
	ta.init		( std::cin );
	ta.result	( std::cout );
	
	std::cout << '\n';
	
	
	return 0;
}