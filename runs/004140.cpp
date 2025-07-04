#include <cstdlib>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

struct way {
	unsigned int node1;
	unsigned int node2;
	unsigned int d;
};

int main(int argc, char** argv) {
	unsigned int i, j, k, temp;

	unsigned int num_of_nodes;
	cin >> num_of_nodes;

	bool **conn;
	conn=(bool**)malloc(num_of_nodes*sizeof(bool*));
	unsigned int **d;
	d=(unsigned int**)malloc(num_of_nodes*sizeof(unsigned int*));
	for( i = 0; i < num_of_nodes; i++) {
		d[i]=(unsigned int*)malloc(num_of_nodes*sizeof(unsigned int));
		conn[i]=(bool*)malloc(num_of_nodes*sizeof(bool));
			for( j = 0; j < num_of_nodes; j++) {
				conn[i][j]=false;
				d[i][j]=0;
			}
		conn[i][i]=true;
	}
	vector< vector<unsigned int> > already_mesured;
	already_mesured.resize(num_of_nodes);
	vector< vector< way > > lay;
	lay.resize(2);
	way temp_way;
	for( k = 0; k < num_of_nodes-1; k++) {
		cin >> i >> j >> temp;
		i=i--;
		j=j--;
		d[i][j]=temp;
		d[j][i]=temp;
		conn[i][j]=true;
		conn[j][i]=true;
		already_mesured.at(i).push_back(j);
		already_mesured.at(j).push_back(i);
		if( i < j ) {
			temp_way.node1=i;
			temp_way.node2=j;
		}
		else {
			temp_way.node1=j;
			temp_way.node2=i;
		}
		temp_way.d=temp;
		lay.at(0).push_back(temp_way);
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
	while( total_mesuared<(num_of_nodes*(num_of_nodes-1))/2 ) {
		lay_num=lay_num%2;
		for( vector< way >::iterator it=lay.at(lay_num).begin(); it!=lay.at(lay_num).end(); ++it ) {
			for( vector<unsigned int>::iterator jt=already_mesured.at(it->node1).begin(); jt!=already_mesured.at(it->node1).end(); ++jt ) {
				if( conn[it->node2][*jt]==false ) {
					temp_way.d=d[*jt][it->node1]+d[it->node1][it->node2];
					if( it->node2 < *jt ) {
						temp_way.node1=it->node2;
						temp_way.node2=*jt;
					}
					if( it->node2 > *jt ) {
						temp_way.node1=*jt;
						temp_way.node2=it->node2;
					}
					lay.at((lay_num+1)%2).push_back(temp_way);
					d[it->node2][*jt]=temp_way.d;
					d[*jt][it->node2]=temp_way.d;
					conn[it->node2][*jt]=true;
					conn[*jt][it->node2]=true;
					total_mesuared++;
				}
			}
			for( vector<unsigned int>::iterator jt=already_mesured.at(it->node2).begin(); jt!=already_mesured.at(it->node2).end(); ++jt ) {
				if( conn[it->node1][*jt] == false ) {
					temp_way.d=d[*jt][it->node2]+d[it->node2][it->node1];
					if( it->node1 < *jt ) {
						temp_way.node1=it->node1;
						temp_way.node2=*jt;
					}
					if( it->node1 > *jt ) {
						temp_way.node1=*jt;
						temp_way.node2=it->node1;
					}
					lay.at((lay_num+1)%2).push_back(temp_way);
					d[it->node1][*jt]=temp_way.d;
					d[*jt][it->node1]=temp_way.d;
					conn[it->node1][*jt]=true;
					conn[*jt][it->node1]=true;
					total_mesuared++;
				}
			}
		}
		for( vector< way >::iterator it=lay.at((lay_num+1)%2).begin(); it!=lay.at((lay_num+1)%2).end(); ++it ) {
			already_mesured.at(it->node2).push_back(it->node1);
			already_mesured.at(it->node1).push_back(it->node2);
		}
		lay.at(lay_num).clear();
		lay_num++;
	}

	for( i = 0; i < num_of_pairs; i++) {
		cout << d[from[i]][to[i]] << endl;
	}
	return 0;
}