#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <cstddef>

namespace gns
{
	class Graf
	{	
		typedef std::map<std::size_t, std::size_t> 	__ways; // pair<соседняя точка, расстояние>
		typedef std::map<std::size_t, __ways>		__graf; // pair<точка, связные точки>

		friend class Walker;
		
	public:
		
		void
		add_point ( std::size_t );
		
		void
		add_way ( std::size_t, std::size_t, std::size_t );
		
		std::size_t
		search_way	( std::size_t, std::size_t ) const;		  // расстояние между 2 точками
		
		
	private:
		
		// рассчитывает расстояние между 2 точками 
		class Walker
		{		
		public:
			
			Walker() { flag_ = false; summ_ = 0; }
			
			void 	// graf, point, prev_point, end_point, summa 
			walk 	( const Graf* const, std::size_t, std::size_t, std::size_t, std::size_t);
			
			std::size_t
			result	( ) const
				{ return summ_; }
			
		private:
			bool		flag_;
			std::size_t summ_;
		};
		
	//MEMBERS
		__graf g_;
		
	}; /* Graf */
	
} /* gns */ 
//*********************************************

void gns::Graf::add_point ( std::size_t pA )
{
	g_.insert( std::make_pair(pA, __ways()) );
}

void gns::Graf::add_way ( std::size_t pA, std::size_t pB, std::size_t way )
{
	__graf::iterator iterA = g_.find(pA);
	
	if ( iterA == g_.end() )
	{
		add_point(pA);
	}
	
	__graf::iterator iterB = g_.find(pB);
	
	if ( iterB == g_.end() )
	{
		add_point(pB);
	}
	
	iterA->second.insert( std::make_pair(pB,way) );
	iterB->second.insert( std::make_pair(pA,way) );
}


std::size_t	gns::Graf::search_way ( std::size_t pA, std::size_t pB ) const
{
	__graf::const_iterator end	= g_.end();
	
	// на всякий случай (:
	if ( g_.find(pA) == end )
	{
		std::stringstream report;
		
		report << "точки " << pA;
		
		if ( g_.find(pB) == end )
			report << " и точки " << pB;
			
		report  << " нет на графе";
		
		throw std::logic_error	(report.str().c_str());
	}
	if ( g_.find(pB) == end )
	{
		std::stringstream report;
		report << "точки " << pB << " нет на графе";
		throw std::logic_error(report.str().c_str());
	}
	
/**/if( pA == pB ) return 0;
	
	Walker w;
	
	w.walk( this, pA, pA, pB, 0 ); // считаем расстояние от pA до pB

	return w.result();
}


void gns::Graf::Walker::walk
	( const Graf* const g_ptr, std::size_t point, std::size_t prev_p, std::size_t end_p, std::size_t summ )
{
	if ( flag_ ) return; // если расстояние уже просчитано, прекращаем обход дерева остальными рекурсиями
	
	__graf::const_iterator	cur		= g_ptr->g_.find(point); // ищем точку, с которой работаем
	
	__ways::const_iterator	finish	= cur->second.find(end_p); // искомая точка
	__ways::const_iterator	end		= cur->second.end();
	
	if ( finish != end ) // если искомая точка найдена
	{
		flag_ = true; 					// поиск окончен
		summ_ = summ + finish->second;
/**/	return;
	}
	
	__ways::const_iterator	beg 	= cur->second.begin();
	__ways::const_iterator	prev	= cur->second.find(prev_p); // точка, из которой пришли
	
	while ( beg != end ) // создаем рекурсию для каждой связной точки
	{
		if ( beg != prev ) // пропускаем точку, из которой пришли
		{
			this->walk( g_ptr, beg->first, point, end_p, summ + beg->second );
		}
		++beg;
	}
	
}
//**********

int main (int argc, char const *argv[])
{
	std::size_t num;
	std::cin >> num;
	
	if ( !num ) throw std::logic_error("у графа должна быть хотя бы одна точка");
	
	gns::Graf 	g;
	std::size_t a, b, c;
	
	if ( num > 1 )
	{
		for ( --num; num; --num )
		{
			std::cin >> a;
			std::cin >> b;
			std::cin >> c;

			g.add_point	(a);
			g.add_point	(b);
			g.add_way	(a,b,c);
		}
	}
	else
	{
		g.add_point(1);
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