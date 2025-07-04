#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<int> > M; // for RMQ

double log2(int a)
{
	return log((double)a) / log(2.0);
}

int pow2(int a) // 2^a
{
	return 1 << a;
}

void RMQ_preprocessing(vector<int>& A)
{
	int N = A.size();
	M.assign(N, vector<int>(ceil(log2(N))));
			// M[i][j] contains index of RMQ(i, i + 2^j);

	for (int i = 0; i < N; ++i)
	{
		M[i][0] = i;
	}
	for (int j = 1; pow2(j) <= N; ++j)
	{
		for (int i = 0; i + pow2(j) - 1 < N; ++i)
		{
			if (A[M[i][j - 1]] < A[M[i + pow2(j - 1)][j - 1]])
			{
				M[i][j] = M[i][j - 1];
			}
			else
			{
				M[i][j] = M[i + pow2(j - 1)][j - 1];
			}
		}
	}
}

// index of minimum element of array A in range [i,j]
int RMQ(vector<int>& A, int i, int j)
{
	if (j < i) // if nessesary, swaping i and j;
	{
		i ^= j ^= i ^= j;
	}
	int k = floor(log2(j - i + 1));

	if (A[M[i][k]] <= A[M[j - pow2(k) + 1][k]])
	{
		return M[i][k];
	}
	else
	{
		return M[j - pow2(k) + 1][k];
	}
}

void dfs(vector<vector<pair<int,int> > >& tree, vector<bool>& used, vector<pair<int,int> >& parent, vector<int>& order, vector<int>& firstapp, int v)
{
	order.push_back(v);
	if (firstapp[v] < 0)
	{
		firstapp[v] = order.size() - 1;
	}
	used[v] = true;
	for (int i = 0; i < tree[v].size(); ++i)
	{
		if (!used[tree[v][i].first])
		{
			parent[tree[v][i].first] = make_pair(v, tree[v][i].second);
			dfs(tree, used, parent, order, firstapp, tree[v][i].first);
			order.push_back(v);
		}
	}
}

int main()
{

	int N = 0; // vertices amount
	cin >> N;
	vector<vector<pair<int,int> > > tree(N, vector<pair<int,int> > (0)); 
							// i-th row contain vector of pairs <a,b> where
							// a stands for number of connected vertice and
							// b stands for weight of respective edge
	for (int i = 0; i < N - 1; ++i)
	{
		int v1, v2, w; 
		cin >> v1 >> v2 >> w;
		tree[v1 - 1].push_back(make_pair(v2 - 1, w));
		tree[v2 - 1].push_back(make_pair(v1 - 1, w));
	}

	vector<bool> used(N, false); // were we in i-th vertex during dfs or not
	vector<pair<int,int> > parent(N); // parent of i-th vertex in a tree and weight of respective edge;
	vector<int> order(0); // vertex order in dfs
	order.reserve(2 * N - 1);
	vector<int> firstapp(N, -1); // first appearance of vertex in order array
	dfs(tree, used, parent, order, firstapp, 0);

	vector<int> order_with_firstapp(2 * N - 1); // order with numbers
	for (int i = 0; i < order.size(); ++i)
	{
		order_with_firstapp[i] = firstapp[order[i]];
	}

	if (N > 1)
	{
		RMQ_preprocessing(order_with_firstapp);
	}

	int Q = 0; // queries amount
	cin >> Q;
	for (int q = 0; q < Q; ++q)
	{
		int i, j;
		cin >> i >> j;
		--i;
		--j;
		if (N > 1)
		{
			int indLCA = RMQ(order_with_firstapp, firstapp[i], firstapp[j]);
			int LCA = order[indLCA];
			int weightSum = 0;
			for (int p = i; p != LCA; p = parent[p].first)
			{
				weightSum += parent[p].second;
			}
			for (int p = j; p != LCA; p = parent[p].first)
			{
				weightSum += parent[p].second;
			}
			cout << weightSum << endl;
		}
		else
		{
			cout << 0 << endl;
		}
	}
	return 0;
}