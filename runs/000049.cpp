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

	void solve()
	{
		vector <unsigned int> ret(M);
		
		for(; final < size; final++) {
			result = 0;
			dfs(final);
		}

		for(unsigned int i = 0; i < M; i++)
		{
			cin >> vertex_1 >> vertex_2;
			ret[i] = dist[vertex_1][vertex_2];
		}
		for(unsigned int i = 0; i < M; i++)
			cout << ret[i] << endl;	
	}	

private:	
	unsigned int result;
	vector < bool > used;
	vector <vector <unsigned int> > dist;
 	vector < vector < pair < int, int > > > tree;	
	unsigned int N, M, vertex_1, vertex_2, len, final, size;

	void input()
	{
		//ifstream cin("test1.txt", ios::in | ios::app);
		cin >> N;
		size = N + 1;
		final = 1;
		tree.resize(size);
		used.resize(size, false);
		dist.resize(size);
		dist[1].resize(size);

		for(unsigned int i = 1; i < size; i++)
			tree[i].reserve(size);

		for(unsigned int i = 1; i < N; ++i)
		{
			dist[i + 1].resize(size);
			cin >> vertex_1 >> vertex_2 >> len;
			tree[vertex_1].push_back(make_pair(vertex_2, len));
			tree[vertex_2].push_back(make_pair(vertex_1, len));
		}	
		cin >> M;
		//cin.close();
	}
	void dfs (int v) 
	{
		used[v] = true;
		for (vector < pair < int, int > >::iterator i = tree[v].begin(); i != tree[v].end(); ++i)
			if (!used[i->first]){
				result += i->second;
				dist[final][i->first] = result;
					dfs (i->first);
				result -= i->second;				
			}
		used[v] = false;
	}	
};


int main()
{
	dist_tree obj;
	obj.solve();	
	return 0;
}