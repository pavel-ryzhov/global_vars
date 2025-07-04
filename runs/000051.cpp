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

	void search()
	{
		cin >> M;
		vector <unsigned int> ret(M);

		for (unsigned int i = 0; i < M; ++i) {
			cin >> vertex_1 >> final;
			result = 0; check = false;
			dfs(vertex_1);
			ret[i] = result;
		}
		for(unsigned int i = 0; i < M; i++)
			cout << ret[i] << endl;	
	}

private:
	
	bool check;
	vector < bool > used;
	vector < vector < pair < int, int > > > tree;
	unsigned int N, M, vertex_1, vertex_2, len, final, result;

	void input()
	{
		//ifstream cin("test1.txt", ios::in | ios::app);
		cin >> N;
		unsigned int size = N + 1;
		tree.resize(size);
		used.resize(size, false);		

		for(unsigned int i = 1; i < N; ++i)
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
	
	dist_tree obj;	
	obj.search();

	//cin.close();
	return 0;
}