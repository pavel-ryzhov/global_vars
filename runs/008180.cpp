#include <vector>
#include <iostream>
#include <map>

using namespace std;

//попытка є 3

typedef vector < vector<int> > graph;
typedef vector<int>::const_iterator const_graph_iter;

vector<bool> lca_dfs_used;
vector<int> way;

map<pair<int, int>, int> ribs; //кешируем все результаты

bool build_way(const graph & g, int v1, int v2)
{
	//как и в поиске в глубину проходимс€ по всему графу
	// но в этот раз в массиве way сохран€ет путь, как мы шли от v1 к v2
	lca_dfs_used[v1] = true;
	way.push_back(v1);
	for (const_graph_iter i = g[v1].begin(); i != g[v1].end(); ++i)
		if(v1 != v2) //если дошли до необходимой вершины, возвращаемс€
		{
			if (!lca_dfs_used[*i])
			{
				bool f = build_way(g, *i, v2);
				if(!f && way[way.size()-2] == v1)
					way.pop_back();
				if(f)
					return true;
			}			
		}
		else
				return true;
	return false;
}

int way_size(const graph & g, int v1, int v2)
{
	lca_dfs_used.assign (g.size(), 0); 
	way.clear();
	build_way(g, v1, v2);
	
	//зна€ какой путь надо пройти (way)
	//идем по нему и складываем длины ребер

	int nResult = 0;	
	map<pair<int, int>, int>::iterator it;
	for(vector<int>::iterator i = way.begin(); i != way.end()-1; i++)
	{

		if(*i < *(i+1))
			it = ribs.find(make_pair(*i, *(i+1)));
		else
			it = ribs.find(make_pair(*(i+1), *i));
		nResult += (*it).second;
	}
	return nResult;
}


int main()
{
	graph g;
	
	//строим граф
	unsigned nSize;

	cin >> nSize;
	g.reserve(nSize); 

	vector<int> t;
	for(unsigned i=0; i<nSize; i++)
	{
		g.push_back(t);
	}

	for(unsigned i=0; i<nSize-1; i++)
	{
		unsigned nT0, nT1, nT2;
		cin >> nT0 >> nT1 >> nT2;

		g[--nT0].push_back(--nT1);
		g[nT1].push_back(nT0);
		if(nT0 < nT1)
			ribs.insert(make_pair(make_pair(nT0, nT1),nT2));
		else
			ribs.insert(make_pair(make_pair(nT1, nT0),nT2));
	}

	//вычисл€ем рассто€ни€
	cin >> nSize;

	for (unsigned i=0; i<nSize; i++)
	{
		int v1, v2, v; // поступил запрос
		cin >> v1 >> v2;
		v = way_size(g, --v1, --v2);		
		cout << v << endl;
	}
	return 0;
}
