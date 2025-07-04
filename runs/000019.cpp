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
		vector <long long> ret(M);
		if(M > N / 2)
		{
			vector <vector <long long> > dist(N + 1, vector <long long>(N + 1));
			for(unsigned int i = 1; i <= N; i++)
				for (final = i, result = 0, check = false; final <= N; final++, result = 0, check = false)
				{
					dfs(i);
					dist[i][final] = dist[final][i] = result;
				}			
			for(unsigned int i = 0; i < M; i++)
			{
				cin >> vertex_1 >> vertex_2;
				ret[i] = dist[vertex_1][vertex_2];
			}
			for(unsigned int i = 0; i < M; i++)
				cout << ret[i] << endl;
		}
		else
		{
			for(unsigned int i = 0; i < M; i++)
			{
				cin >> vertex_1 >> vertex_2;
				ret[i] = search(vertex_1, vertex_2);
			}
			for(unsigned int i = 0; i < M; i++)
				cout << ret[i] << endl;
		}

	}	

private:
	unsigned int N, M, vertex_1, vertex_2, len, final;
	bool check;
	long long result;
	vector < char > used;
 	vector < vector < pair < int, int > > > tree;

	void input()
	{
		//ifstream cin("test1.txt", ios::in | ios::app);
		cin >> N;
		tree.resize(N + 1);
		used.resize(N + 1, false);

		for(unsigned int i = 0; i < N - 1; ++i)
		{
			cin >> vertex_1 >> vertex_2 >> len;
			tree[vertex_1].push_back(make_pair(vertex_2, len));
			tree[vertex_2].push_back(make_pair(vertex_1, len));
		}	
		cin >> M;
		//cin.close();
	}

	void dfs (unsigned int v) 
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

	long long search(unsigned int i, unsigned int j)
	{		
		final = j;
		result = 0;
		check = false;
		dfs(i);
		return result;
	}
};


int main()
{
	dist_tree obj;
	obj.solve();
	
	return 0;
}