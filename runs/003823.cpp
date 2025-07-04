//This program uses Tarjan's algorithm http://e-maxx.ru/algo/lca_linear_offline

#include<iostream>
#include<vector>
#include <queue>
#include<fstream>
#include<string>
#include <algorithm>

using namespace std;

const int N=40000;
typedef unsigned short vertex; //type for vertices

vector< vector<vertex> > graph, query;
vertex query_line[2*N+1];

vector<bool> used; //for dfs (depth-first search) function 
vector<bool> completed; //completed[v] is true, if dfs processed all of v children
vector<vertex> Union; //after update_union(i) Union[u] is an ancestor of v: lca(Union[u],v)=lca(u,v).

vector<int> d_to_union; //d_to_union[i] - distance from vertex i to union[i]
vector<vertex> parent;
vector<int>d_to_parent;

//-------------------------------------------------------------------------

class v1_v2_value{
public:
	vertex v1, v2;
	int value;
	v1_v2_value(vertex a, vertex b, int c) {
		if(a>b) swap(a,b);
		v1=a;
		v2=b;
		value=c;
	}
};	

bool UDsort(v1_v2_value a, v1_v2_value b) {
	if(a.v1==b.v1) return (a.v2<b.v2);
	return (a.v1<b.v1);
}

class vertices_values {
public:
	vector<v1_v2_value> vec;

	int get_value(vertex ver1, vertex ver2) { //binary search (for sorted vec)
		if(ver1>ver2) swap(ver1,ver2);
		int l=0, r=vec.size()-1, m;
		for (;;) {
			m=(l+r)/2;
			if (ver1==vec[m].v1) {
				for(;;) {
					if(ver2==vec[m].v2) return vec[m].value;
					if(ver2<vec[m].v2) m--;
					else m++;
				}
			}
			if (ver1<vec[m].v1) r=m-1;
			else l=m+1;
		}
	}

	void add(vertex ver1, vertex ver2, int val) {
		v1_v2_value temp(ver1,ver2,val);
		vec.push_back(temp);
	}

	void sort() {
		std::sort(vec.begin(), vec.end(), UDsort);
	}

};

vertices_values edges_lengths;
vertices_values answers;

//-------------------------------------------------------------------------

void read_graph(istream&in) {
	int N;
	in>>N;

	graph.resize(N+1);
	used.resize(N+1);
	completed.resize(N+1);
	query.resize(N+1);
	Union.resize(N+1);
	parent.resize(N+1);
	d_to_union.resize(N+1); 
	d_to_parent.resize(N+1);

	vertex v1, v2;
	int length;
	
	for (int i=0; i<N-1; i++){ 	//N vertices => N-1 edges
		in>>v1>>v2>>length;
		edges_lengths.add(v1,v2,length);
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}
	edges_lengths.sort();
}

int d_to_ancestor(vertex node, vertex ancestor) {
	int sum=0;
	vertex a=node, b;
	while(a!=ancestor) {
		b=parent[a];
		sum+=d_to_parent[a];
		a=b;
	}
	return sum;
}


// modified Tarjan's algorithm---------------------------------------------------------

vertex get_union (vertex v) {
	vertex ver=v;
	int len=0;

	while (ver!=Union[ver]) { 
		len+=d_to_union[ver];
		ver=Union[ver];
	}

	Union[v]=ver;
	d_to_union[v]=len;
	return ver;
}

void add_vertex_and_subtree_to_parent_union (vertex ver, vertex parent) {
	Union[ver]=parent;
	d_to_union[ver]=d_to_parent[ver];
}

void dfs (vertex v) {
	Union[v] = v;
	used[v] = true;
	vertex c; //v child
	for (int i=0; i<(int)graph[v].size(); i++) {
		c=graph[v][i];
		if (!used[c]) {
			parent[c]=v;
			d_to_parent[c]=0;
			d_to_parent[c]=edges_lengths.get_value(c,v);
			dfs(c);
			add_vertex_and_subtree_to_parent_union(c, v);
		}
	}

	completed[v]=true;

	for (int i=0; i<(int)query[v].size(); i++) 
		if (completed[query[v][i]]) {
			get_union(query[v][i]);
			answers.add(v, query[v][i], d_to_union[query[v][i]]+d_to_ancestor(v,Union[query[v][i]]));
		}
}

//-------------------------------------------------------------------------

void lengths_of_paths(istream&in) {
//	ofstream out("output.txt");//!
	int i=0;
	while(query_line[i]) {
		cout<<answers.get_value(query_line[i],query_line[i+1])<<endl;
		i+=2;
	}
}

void read_query(istream&in) {
	int M;
	vertex v1, v2;
	bool flag;
	in>>M;
	query_line[2*M]=0;
	
	for(int i=0;i<M;i++) {
		in>>v1>>v2;

		flag=false;
		for (int j=0; j<(int)query[v1].size(); j++) 
			if (query[v1][j]==v2) {
				flag=true;
				break;
			}
			if (!flag) {
				query[v1].push_back(v2);
				query[v2].push_back(v1);
			}
			query_line[2*i]=v1;
			query_line[2*i+1]=v2;
	}
}

//-------------------------------------------------------------------------

int main() {

	istream* in;
//	ifstream infile("input.txt"); 
//	in = &infile;
	in = &cin; 
	
	read_graph(*in); 
	read_query(*in);
	dfs(1);
	answers.sort();
	lengths_of_paths(*in);
	
	//	system("pause");
}
