#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iterator>
#include <stdexcept>

namespace gns
{
	class Graph
	{
		typedef unsigned int							__int;
		
		typedef std::pair<__int, __int>					__point; // индекс, вес
		typedef std::vector<__point>					__ways; 
		typedef std::vector<__ways>						__graph;
		
		typedef std::pair<std::vector<__int>, __int>	__path; // путь от корня, вес
		typedef std::vector<__path>						__paths;
		
	public:
		Graph(__int n) : graph_(n+1), paths_(n+1) { root_ = false; }
		
		void
		add ( __int, __int, __int ); // добавить точки
		
		__int
		search_way	( __int, __int ) const;	// расстояние между 2 точками
		
	void root_roads()
	{
		if ( root_ ) return;
		
		walk( 1, 1, paths_[1], 0 );
		
		root_ = true;
	}
		
	private:
		
		void
		walk 	( __int, __int, __path&, __int ); // гуляет, изучает
		
	//Members
	
		bool		root_; // изучен ли граф?
		__graph 	graph_;
		__paths 	paths_;
		
	}; // Graph
	
} // gns
///////////////////

void
gns::Graph::add ( __int pA, __int pB, __int way )
{
	if( root_ ) return; // если граф оптимизирован для поиска - точки добавлять нельзя
	
	graph_[pA].push_back( std::make_pair( pB, way ) );
	graph_[pB].push_back( std::make_pair( pA, way ) );
}


gns::Graph::__int
gns::Graph::search_way( __int start_point, __int end_point ) const
{	
	if ( ! root_ ) throw std::logic_error("ошибка поиска маршрута");
	
	if( start_point == end_point ) return 0;
	
	
	// если одна из точек равна 1 - просто возвращаем путь
	if ( start_point == 1 )
	{
		return paths_[end_point].second;
	}
	
	if ( end_point == 1 )
	{
		return paths_[start_point].second;
	}
	
	__int pathA = paths_[start_point].second;
	__int pathB = paths_[end_point].second;

	
	__int size 		= std::min( paths_[start_point].first.size(), paths_[end_point].first.size() );
	__int parent 	= 0;
	
	// ищем наименьшего предка
	for ( __int i = 0; i < size ; ++i )
	{			
		if ( paths_[start_point].first[i] == paths_[end_point].first[i] )
			parent = paths_[start_point].first[i];
	}

	__int parent_path = paths_[parent].second; // путь от корня до предка

	return pathA + pathB - parent_path*2;
}


void
gns::Graph::walk ( __int cur_point, __int prev_point, __path& path,  __int summ)
{
	__int size = graph_[cur_point].size();

	__int point = 0;
	
	for ( __int i = 0; i < size; ++i )
	{	
		point = graph_[cur_point][i].first; // соседняя вершина
		
		if ( point != prev_point )
		{
			// копируем путь от предка
			std::copy( path.first.begin(), path.first.end(), std::back_inserter(paths_[point].first) );
			
			// добавляем к пути текущую вершину
			paths_[point].first.push_back(point);
			
			// длина до текущей вершины от корня
			paths_[point].second = graph_[cur_point][i].second + summ;
			
			walk( point, cur_point, paths_[point], graph_[cur_point][i].second + summ );
		}
	}
}

///////////
int main (int argc, char const *argv[])
{
	std::size_t num;
	std::cin >> num;
	
	if ( !num ) throw std::logic_error("у графа должна быть хотя бы одна точка");
	
	gns::Graph 	g(num);
	std::size_t a, b, c;
	

	for ( --num; num; --num )
	{
		std::cin >> a;
		std::cin >> b;
		std::cin >> c;

		g.add (a,b,c);
	}
	
	g.root_roads();
	
	
	std::cin >> num;
	
	for ( ; num; --num )
	{
		std::cin >> a;
		std::cin >> b;
		
		std::cout << g.search_way( a, b ) << '\n';
	}
	
	
	return 0;
}

