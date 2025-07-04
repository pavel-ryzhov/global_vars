#include <cstdlib>
#include <vector>
#include <deque>
#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

	unsigned int i, j, k, temp;
	
	unsigned int num_of_nodes;
	scanf("%ld", &num_of_nodes);
	
	vector< vector<unsigned int> > dist;
	dist.resize(num_of_nodes);
	vector<bool> used;
	used.resize(num_of_nodes);
	for( i = 0; i < num_of_nodes; i++) {
		dist.at(i).resize(num_of_nodes);
		used.at(i)=false;
 			for( j = 0; j < num_of_nodes; j++)
 				dist.at(i).at(j)=0;
	}

	vector< vector<unsigned int> > edges;
	edges.resize(num_of_nodes);
	for( k = 0; k < num_of_nodes-1; k++) {
		scanf("%ld %ld %ld", &i, &j, &temp);
		i--;
		j--;
		dist.at(i).at(j)=temp;
		dist.at(j).at(i)=temp;
		edges.at(i).push_back(j);
		edges.at(j).push_back(i);
	}

	unsigned int num_of_pairs;
	scanf("%ld", &num_of_pairs);
	vector<unsigned int> from, to;
	from.resize(num_of_pairs);
	to.resize(num_of_pairs);
	for( i = 0; i < num_of_pairs; i++) {
		scanf("%ld %ld", &from.at(i), &to.at(i));
		from.at(i)--;
		to.at(i)--;
	}

	unsigned int start_node=0, ignited_node, current_node;
	deque<unsigned int> current;
	vector<unsigned int> visited;
	current.clear();
	visited.clear();
	current.push_back(start_node);
	visited.push_back(start_node);
	used.at(start_node)=true;
	int temp2;
	while( !current.empty() ) {
		current_node=current.front();
		current.pop_front();
		for ( vector<unsigned int>::iterator it=edges.at(current_node).begin(); it!=edges.at(current_node).end(); ++it ) {
			ignited_node=*it;
			if ( !used.at(ignited_node) ) {
				temp2=dist.at(current_node).at(ignited_node);
				for( vector<unsigned int>::iterator jt=visited.begin(); jt!=visited.end(); ++jt ) {
					temp=dist.at(*jt).at(current_node)+temp2;
					dist.at(*jt).at(ignited_node)=temp;
					dist.at(ignited_node).at(*jt)=temp;
				}
				used.at(ignited_node)=true;
				current.push_back(ignited_node);
				visited.push_back(ignited_node);
			}
		}
	}
	visited.clear();
	current.clear();
	used.clear();

	for( i = 0; i < num_of_pairs; i++)
		printf("%ld\n",dist.at(from.at(i)).at(to.at(i)));
	return 0;
}