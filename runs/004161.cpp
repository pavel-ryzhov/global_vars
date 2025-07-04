#include <cstdlib>
#include <vector>
#include <deque>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {

	unsigned int i, j, k, temp;

	unsigned int num_of_nodes;
	cin >> num_of_nodes;

	unsigned int **dist;
	dist=(unsigned int**)malloc(num_of_nodes*sizeof(unsigned int*));
	vector<bool> used;
	used.resize(num_of_nodes);
	for( i = 0; i < num_of_nodes; i++) {
		dist[i]=(unsigned int*)malloc(num_of_nodes*sizeof(unsigned int));
		used[i]=false;
			for( j = 0; j < num_of_nodes; j++)
				dist[i][j]=0;
	}

	vector< vector<unsigned int> > edges;
	edges.resize(num_of_nodes);
	for( k = 0; k < num_of_nodes-1; k++) {
		cin >> i >> j >> temp;
		i--;
		j--;
		dist[i][j]=temp;
		dist[j][i]=temp;
		edges.at(i).push_back(j);
		edges.at(j).push_back(i);
	}

	unsigned int num_of_pairs;
	cin >> num_of_pairs;
	unsigned int *from, *to;
	from=(unsigned int*)malloc(num_of_pairs*sizeof(unsigned int));
	to=(unsigned int*)malloc(num_of_pairs*sizeof(unsigned int));
	for( i = 0; i < num_of_pairs; i++) {
		cin >> from[i] >> to[i];
		from[i]--;
		to[i]--;
	}

	unsigned int start_node=0, ignited_node, current_node;
	deque<unsigned int> current;	
	vector<unsigned int> visited;
	current.clear();
	visited.clear();
	current.push_back(start_node);
	visited.push_back(start_node);
	used.at(start_node)=true;	
	while( !current.empty() ) {
		current_node=current.front();
		current.pop_front();
		for ( vector<unsigned int>::iterator it=edges.at(current_node).begin(); it!=edges.at(current_node).end(); ++it ) {
			ignited_node=*it;
			if ( !used.at(ignited_node) ) {
				for( vector<unsigned int>::iterator jt=visited.begin(); jt!=visited.end(); ++jt ) {
					temp=dist[*jt][current_node]+dist[ignited_node][current_node];
					dist[*jt][ignited_node]=temp;
					dist[ignited_node][*jt]=temp;
				}				
				used.at(ignited_node)=true;
				current.push_back(ignited_node);
				visited.push_back(ignited_node);
			}
		}
	}

	for( i = 0; i < num_of_pairs; i++)
		cout << dist[from[i]][to[i]] << endl;
	return 0;
}