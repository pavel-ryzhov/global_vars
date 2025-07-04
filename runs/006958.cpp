#include <iostream>
#include <vector>
#include <utility>
#include <stdexcept>

namespace gns
{
	class Graf
	{
		typedef unsigned int				__int;
		typedef std::pair<__int, __int>		__point; // индекс, вес
		typedef std::vector<__point>		__ways; 
		typedef std::vector<__ways>			__graf;
		
	public:
		Graf(__int n) : g_(n+1) {}
		
		void
		add ( __int, __int, __int );
		
		__int
		search_way	( __int, __int ) const;	// расстояние между 2 точками
		
	private:
		
		class Walker
		{
		public:
			Walker() { flag_ = false; summ_ = 0; }
			
			void	// graf, point, prev_point, end_point, summa 
			walk 	( const __graf&, __int, __int, __int, __int);
			
			__int
			result	( ) const
				{ return summ_; }
			
		private:
			bool 	flag_;
			__int	summ_;
		};
		
		__graf g_;
		
	};// Graf
	
} // gns
///////////////////

void
gns::Graf::add ( __int pA, __int pB, __int way )
{
	g_[pA].push_back( std::make_pair( pB, way ) );
	g_[pB].push_back( std::make_pair( pA, way ) );
}

gns::Graf::__int
gns::Graf::search_way( __int start_point, __int end_point ) const
{
	if( start_point == end_point ) return 0;
	
	Walker w;
	
	w.walk( g_, start_point, start_point, end_point, 0 );
	
	return w.result();
}

void
gns::Graf::Walker::walk
	( const __graf& graf, __int cur_point,
		__int prev_point, __int end_point, __int summ)
{
	if ( flag_ ) return;
	
	__int size = graf[cur_point].size();
	__int temp_point;
	
	for ( __int i = 0; i < size; ++i )
	{	
		temp_point = graf[cur_point][i].first; // соседняя вершина
		
		if ( temp_point == end_point )
		{
			flag_ = true;
			summ_ = graf[cur_point][i].second + summ;
/**/		return;
		}
		if ( temp_point != prev_point )
		{
			this->walk( graf, temp_point, cur_point, end_point, graf[cur_point][i].second + summ );
		}
	}
}

///////////
int main (int argc, char const *argv[])
{
	std::size_t num;
	std::cin >> num;
	
	if ( !num ) throw std::logic_error("у графа должна быть хотя бы одна точка");
	
	gns::Graf 	g(num);
	std::size_t a, b, c;
	
	if ( num > 1 )
	{
		for ( --num; num; --num )
		{
			std::cin >> a;
			std::cin >> b;
			std::cin >> c;

			g.add (a,b,c);
		}
	}
	
	std::cin >> num;
	
	for ( ; num; --num )
	{
		std::cin >> a;
		std::cin >> b;
		
		std::cout << g.search_way( a, b ) << '\n';
	}
	return 0;
}

