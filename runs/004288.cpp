#include <cstdlib>
#include <vector>
#include <deque>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

unsigned int num_of_nodes;
vector< vector<unsigned int> > graph;
vector< vector<unsigned int> > edges_dist;
vector< vector< pair<unsigned int, unsigned int> > > q;
vector<unsigned int> dist;
vector<bool> used;
vector<unsigned int> dsu, current_ancestor;

unsigned int num_of_pairs;
vector<unsigned int> from;
vector<unsigned int> to;
vector<unsigned int> ancestor;

unsigned int dsu_get(unsigned int node);

void dsu_unite(unsigned int node1, unsigned int node2, unsigned int new_ancestor);

void dfs(unsigned int current_node);

int main(int argc, char** argv) {

	unsigned int i, j, k, temp;

	scanf("%ld", &num_of_nodes);

	graph.resize(num_of_nodes);
	edges_dist.resize(num_of_nodes);
	q.resize(num_of_nodes);
	dist.resize(num_of_nodes);
	used.resize(num_of_nodes);
	dsu.resize(num_of_nodes);
	current_ancestor.resize(num_of_nodes);

	for( k = 0; k < num_of_nodes-1; k++) {
		scanf("%ld %ld %ld", &i, &j, &temp);
		i--;
		j--;
		graph.at(i).push_back(j);
		edges_dist.at(i).push_back(temp);
		graph.at(j).push_back(i);
		edges_dist.at(j).push_back(temp);
	}

	scanf("%ld", &num_of_pairs);

	from.resize(num_of_pairs);
	to.resize(num_of_pairs);
	ancestor.resize(num_of_pairs);

	pair<unsigned int, unsigned int> temp_pair;
	for( k = 0; k < num_of_pairs; k++) {
		scanf("%ld %ld", &i, &j);
		i--;
		j--;
		from.at(k)=i;
		to.at(k)=j;
		temp_pair.first=j;
		temp_pair.second=k;
		q.at(i).push_back(temp_pair);
		temp_pair.first=i;
		q.at(j).push_back(temp_pair);
	}

	unsigned int start_node;
	start_node=0;
	dfs(start_node);

	for( k = 0; k < num_of_pairs; k++) {
		temp=dist.at(from.at(k))+dist.at(to.at(k))-2*dist.at(ancestor.at(k));
		printf("%ld\n", temp);
	}

	graph.clear();
	edges_dist.clear();
	q.clear();
	ancestor.clear();
	dist.clear();
	used.clear();
	dsu.clear();
	current_ancestor.clear();

	from.clear();
	to.clear();

	return 0;
}

unsigned int dsu_get(unsigned int node) {
	if( dsu.at(node) == node )
		return node;
	else
		dsu.at(node)=dsu_get(dsu.at(node));
	return dsu.at(node);
}

void dsu_unite(unsigned int node1, unsigned int node2, unsigned int new_ancestor) {
	node1=dsu_get(node1);
	node2=dsu_get(node2);
	if( rand() & 1 )
		swap(node1, node2);
	dsu.at(node1)=node2;
	current_ancestor.at(node2)=new_ancestor;
}

void dfs(unsigned int current_node) {
	unsigned int ignited_node;
	dsu.at(current_node)=current_node;
	current_ancestor.at(current_node)=current_node;
	used.at(current_node)=true;
	for( int k = 0; k < graph.at(current_node).size(); k++ ) {
		ignited_node=graph.at(current_node).at(k);
		if( !used.at(ignited_node) ) {
			dist.at(ignited_node)=dist.at(current_node)+edges_dist.at(current_node).at(k);
			dfs(ignited_node);
			dsu_unite(current_node, ignited_node, current_node);
		}
	}
	
	for( vector< pair<unsigned int, unsigned int> >::iterator it = q.at(current_node).begin(); it != q.at(current_node).end(); ++it )
		if( used.at(it->first) ) {
			ancestor.at(it->second)=current_ancestor.at(dsu_get(it->first));
		}
}