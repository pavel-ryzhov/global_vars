#include <iostream>
#include <vector>
//#include <fstream>
using namespace std;

class dist_tree
{
public:
	dist_tree()	{
		this->input();
	}

	unsigned int search(int i, int j)
	{
		final = j;
		result = 0;
		check = false;
		dfs(i);
		return result;
	}

private:
	int N, M, vertex_1, vertex_2, len, final, result;
	bool check;
	vector < char > used;
 	vector < vector < pair < int, int > > > tree;

	void input()
	{
		//ifstream cin("test1.txt", ios::in | ios::app);
		cin >> N;
		tree.resize(N + 1);
		used.resize(N + 1, false);

		for(int i = 0; i < N - 1; ++i)
		{
			cin >> vertex_1 >> vertex_2 >> len;
			tree[vertex_1].push_back(make_pair(vertex_2, len));
			tree[vertex_2].push_back(make_pair(vertex_1, len));
		}	
		//cin.close();
	}

	void dfs (int v) 
	{
		if(v == final) {
			check = true;
			return;
		}
		used[v] = true;
		for (vector < pair < int, int > >::iterator i = tree[v].begin(); i != tree[v].end() && !check; ++i)
			if (!used[i->first]){
				dfs (i->first);
				if(check) 
					result += i->second;
			}
		used[v] = false;
	}
};


int main()
{
	//ifstream cin("test2.txt", ios::in | ios::app);
	int M(0), vi(0), vj(0);

	dist_tree obj;

	cin >> M;
	vector < pair <int, int> > way(M);	

	for (int i = 0; i < M; ++i) {
		cin >> vi >> vj;
		way[i] = make_pair(vi, vj);
	}

	for(int i = 0; i < M; ++i)
		cout << obj.search(way[i].first, way[i].second) << endl;

	//cin.close();
	return 0;
}