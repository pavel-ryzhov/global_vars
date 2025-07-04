#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
	unsigned int i, j, k, temp;

	unsigned int num_of_nodes;
	cin >> num_of_nodes;

	bool **used;
	used=(bool**)malloc(num_of_nodes*sizeof(bool*));
	unsigned int **dist;
	dist=(unsigned int**)malloc(num_of_nodes*sizeof(unsigned int*));
	for( i = 0; i < num_of_nodes; i++) {
		dist[i]=(unsigned int*)malloc(num_of_nodes*sizeof(unsigned int));
		used[i]=(bool*)malloc(num_of_nodes*sizeof(bool));
			for( j = 0; j < num_of_nodes; j++) {
				used[i][j]=false;
				dist[i][j]=0;
			}
		used[i][i]=true;
	}
	vector< vector<unsigned int> > edges;
	edges.resize(num_of_nodes);
	vector< vector< pair<unsigned int, unsigned int> > > lay;
	lay.resize(2);
	pair<unsigned int, unsigned int> temp_pair;
	for( k = 0; k < num_of_nodes-1; k++) {
		cin >> i >> j >> temp;
		i--;
		j--;
		dist[i][j]=temp;
		dist[j][i]=temp;
		used[i][j]=true;
		used[j][i]=true;
		edges.at(i).push_back(j);
		edges.at(j).push_back(i);
		if( i < j ) {
			temp_pair.first=i;
			temp_pair.second=j;
		}
		else {
			temp_pair.first=j;
			temp_pair.second=i;
		}
		lay.at(0).push_back(temp_pair);
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

	long unsigned int total_mesuared=(num_of_nodes-1);
	int lay_num=0;
	while( total_mesuared < (num_of_nodes*(num_of_nodes-1))/2 ) {
		for( vector< pair<unsigned int, unsigned int> >::iterator it=lay.at(lay_num%2).begin(); it!=lay.at(lay_num%2).end(); ++it ) {
			for( vector<unsigned int>::iterator jt=edges.at(it->first).begin(); jt!=edges.at(it->first).end(); ++jt ) {
				i=it->second;
				j=*jt;
				k=it->first;
				if( used[i][j] == false ) {
					temp=dist[j][k]+dist[k][i];
					dist[i][j]=temp;
					dist[j][i]=temp;
					used[i][j]=true;
					used[j][i]=true;
					total_mesuared++;
					if( i < j ) {
						temp_pair.first=i;
						temp_pair.second=j;
					}
					if( i > j ) {
						temp_pair.first=j;
						temp_pair.second=i;
					}
					lay.at((lay_num+1)%2).push_back(temp_pair);
				}
			}
			for( vector<unsigned int>::iterator jt=edges.at(it->second).begin(); jt!=edges.at(it->second).end(); ++jt ) {				
				i=it->first;
				j=*jt;
				k=it->second;
				if( used[i][j] == false ) {
					temp=dist[j][k]+dist[k][i];
					dist[i][j]=temp;
					dist[j][i]=temp;
					used[i][j]=true;
					used[j][i]=true;
					total_mesuared++;
					if( i < j ) {
						temp_pair.first=i;
						temp_pair.second=j;
					}
					if( i > j ) {
						temp_pair.first=j;
						temp_pair.second=i;
					}
					lay.at((lay_num+1)%2).push_back(temp_pair);
				}
			}
		}
		lay.at(lay_num%2).clear();
		lay_num++;
	}

	for( i = 0; i < num_of_pairs; i++)
		cout << dist[from[i]][to[i]] << endl;
	return 0;
}