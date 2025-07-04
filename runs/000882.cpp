

#include <iostream>
#include <vector>
#include <algorithm>

/*
solving using this http://e-maxx.ru/algo/lca_simpler algorithm
(advise from task)
for finding least common parent along with cost of path to it
algoritm was chosen for speed of implementaion and becuse ln40000 ~=15 
*/

typedef struct _node{
	bool visited;
	int visit_in,visit_out,number,cost_to_root;//number is not needed
	std::vector<std::pair<int,int> > edges;//stores numbers of vertices to which you can get from there
										   //as (id,cost) pair
	_node(){//default constructor for resizin vector
		visit_in = 0;
		visit_out = 0;
		visited = false;
		cost_to_root = 0;
	}

	int get_cost(int to){
		for(int i = 0;i < edges.size();++i)
			if(edges[i].first == to)return edges[i].second;
	}

} node;



class graph{
	std::vector<std::vector< int>  > parents; 
	std::vector<node> _graph;
	int logarithmic_height;

	void depth_search(int node,int parent = 0,int cost = 0){//parent of root is zero
		static int time = 0;
		_graph[node].visited = true;
		_graph[node].visit_in = ++time;
		_graph[node].cost_to_root =  _graph[parent].cost_to_root + ( 1 == node ? 0 : _graph[node].get_cost(parent) );//check for root
		parents[node][0] = parent;
		for(int i = 1; i < logarithmic_height;++i){
			parents[node][i]= parents[parents[node][i-1]][i-1];
		}
		for(int i = 0;i < _graph[node].edges.size();++i){
			if( ! _graph[ _graph[node].edges[i].first ].visited ){//not visited
				depth_search(_graph[node].edges[i].first,node,_graph[node].edges[i].second);
				}
		}
		_graph[node].visit_out = ++time;
	}

	bool isparent(int parent,int child){
		return _graph[parent].visit_in < _graph[child].visit_in &&
			_graph[parent].visit_out > _graph[child].visit_out;
	}

	int least_common_ancestor(int from,int to){
		if(isparent(from,to)) return from;
		if(isparent(to,from)) return to;
		for(int i = logarithmic_height;i >=0 ;--i)
			if( ! isparent(parents[from][i] ,to) 
				&& parents[from][i] != 0)
				from = parents[from][i];
		return parents[from][0];
	}

	int cheapest_path(int from,int to){
		if(isparent(from,to)) return _graph[to].cost_to_root - _graph[from].cost_to_root;
		else if(isparent(to,from)) return _graph[from].cost_to_root - _graph[to].cost_to_root;
		else {
			int ancestor = least_common_ancestor(to,from);
			return (_graph[from].cost_to_root - _graph[ancestor].cost_to_root)
				 + (_graph[to].cost_to_root - _graph[ancestor].cost_to_root);
		}
	}




public:
	graph(){
		int size;
		std::cin >> size;
		_graph.resize(size + 1);
		_graph[0].number = -1;
		for(int i = 1; i < _graph.size();++i)_graph[i].number = i;
		for(int i = 0;i < size - 1 ;++i){
			int from,to,cost;
			std::cin >> from >> to >> cost;
			_graph[from].edges.push_back(std::pair<int,int>(to,cost));
			_graph[to].edges.push_back(std::pair<int,int>(from,cost));
		}
	    logarithmic_height = 1;//preparing parents vector
		while ((1<<logarithmic_height) <= size)  ++logarithmic_height;//same as *=2
		parents.resize(size + 1);
		for(int i = 0;i < size + 1;++i)parents[i].resize(logarithmic_height + 1 );
	}

	void solve(){
		depth_search(1);//root is first
		int num_problems;
		std::cin >> num_problems;
		for(int i = 0;i < num_problems;++i){
			int a,b;
			std::cin >> a >> b;
			std::cout << cheapest_path(a,b) << std::endl;
		}
	}

};

int main(int argc,char* argv[])
{
	graph input;
	input.solve();
	return 0;
}

