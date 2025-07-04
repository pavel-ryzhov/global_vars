#include <cstdlib>
#include <vector>
#include <deque>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
	unsigned int i, j, p, q, k, temp;

	unsigned int num_of_nodes;
	cin >> num_of_nodes;

	unsigned int **dist;
	dist=(unsigned int**)malloc(num_of_nodes*sizeof(unsigned int*));
	vector<int> color;
	color.resize(num_of_nodes);
	for( i = 0; i < num_of_nodes; i++) {
		dist[i]=(unsigned int*)malloc(num_of_nodes*sizeof(unsigned int));
		color[i]=-1;
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
	vector< deque<unsigned int> > current;	
	vector< vector<unsigned int> > visited;
	vector<unsigned int> start_node;
	vector<unsigned int> ignited_node, current_node;	
	vector<unsigned int> connect;
	unsigned int parallel=1+num_of_nodes/400;
	current.resize(parallel);
	visited.resize(parallel);
	start_node.resize(parallel);
	ignited_node.resize(parallel);
	current_node.resize(parallel);
	connect.resize(parallel);
	for( i = 0; i < parallel; i++ ) {
		current.at(i).clear();
		visited.at(i).clear();
		start_node.at(i)=num_of_nodes/parallel*i;
		current.at(i).push_back(start_node.at(i));
		visited.at(i).push_back(start_node.at(i));
		color.at(start_node.at(i))=i;
		connect.at(i)=i;
	}
	bool all_empty=false;
	while( !all_empty ) {
		all_empty=true;
		for( i = 0; i < parallel; i++ ) {
			if( !current.at(i).empty() ) {
				current_node.at(i)=current.at(i).front();
				current.at(i).pop_front();
				for ( vector<unsigned int>::iterator it=edges.at(current_node.at(i)).begin(); it!=edges.at(current_node.at(i)).end(); ++it ) {
					ignited_node.at(i)=*it;
					if( color.at(ignited_node.at(i))==-1 ) {
						for( vector<unsigned int>::iterator jt=visited.at(i).begin(); jt!=visited.at(i).end(); ++jt ) {
							temp=dist[*jt][current_node.at(i)]+dist[ignited_node.at(i)][current_node.at(i)];
							dist[*jt][ignited_node.at(i)]=temp;
							dist[ignited_node.at(i)][*jt]=temp;
						}
						color.at(ignited_node.at(i))=i;
						current.at(i).push_back(ignited_node.at(i));
						visited.at(i).push_back(ignited_node.at(i));
					}
					else if( color.at(ignited_node.at(i))!=i ) {
						//CONNECTION!
						connect.at(i)=color.at(ignited_node.at(i));
					}
					if( connect.at(i)!=i )
						it=edges.at(current_node.at(i)).end()-1;
				}
				if( connect.at(i)!=i ) {
					j=connect.at(i);
					p=current_node.at(i);
					q=ignited_node.at(i);
					for( vector<unsigned int>::iterator it=visited.at(i).begin(); it!=visited.at(i).end(); ++it )
						for( vector<unsigned int>::iterator jt=visited.at(j).begin(); jt!=visited.at(j).end(); ++jt ) {
							temp=dist[*jt][q]+dist[q][p]+dist[p][*it];
							dist[*jt][*it]=temp;
							dist[*it][*jt]=temp;
						}
					for( vector<unsigned int>::iterator it=visited.at(i).begin(); it!=visited.at(i).end(); ++it ) {
						visited.at(j).push_back(*it);
						color.at(*it)=j;
					}
					for( deque<unsigned int>::iterator it=current.at(i).begin(); it!=current.at(i).end(); ++it )
						current.at(j).push_back(*it);
					current.at(j).push_back(p);
					current.at(i).clear();
				}
			}
			if( !current.at(i).empty() )
				all_empty=false;
		}
	}

	for( i = 0; i < num_of_pairs; i++)
		cout << dist[from[i]][to[i]] << endl;
	return 0;
}