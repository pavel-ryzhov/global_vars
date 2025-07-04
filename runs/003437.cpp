/* �������� ������ ����������, ������� �� ���������� ����������� ������ ������ (�������� �������).
\  ���������� ������� ���������� �� ����� ������ �� ���� ��������� ������. 
\  �����, �� ������ ������ � ���������� ����� ��������� i � j, ������� ���������� ������
\  ����� ���������� �� ������� i �� ����� � ������� j �� �����, �� ������� ���������� 
\  ���������� �� �� ����������� ������ ������ �� �����.
*/
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

int root(1), res(0), N(0), M(0);                  ///<�������� ������ ������ (root) � ���������� ��� ���������� ���� � ������.>
vector < bool > used;							  ///<������ ���������� ������ ������ (������������ ��� ������ � �������).>
vector < int > dsu, ancestor, result, dist;		  ///<������ ��������, �������, ����������� � ���������� �� ������ �� �����.>
vector < vector < pair < int, int > > > tree, qq; ///<������(tree), ���������� ������� �����, �.�. i-� ���� �������� ����� �������,>
                                                  ///<� ������� ��������� i-� ������� � ��� �����. ������ �������� (qq). >
												  ///<��������� qq: i-� ���� �������� ����� ������� j (������ �� ����� ����������>
												  ///<����� ��������� (i, j)) � ���������� ����� ������� (��� ������������ �����������).>

void input();									  ///<������� ������ �������� ������.>
void dfs (int);									  ///<����� � ������� � ����� ���������� ����� ��������� ���������.>
void dfs_cost (int);							  ///<���������� ����� �� ����� ������ �� ������ (�� ������ ������ � �������).>
void dsu_unite (int, int, int);					  ///<������� ����������� ���������������� ��������.>
int dsu_get (int);								  ///<���� ���������, �������� ����������� �������, � ���������� ��� �������������.>

int main() 
{	
	input();
	dfs_cost(root);
	dfs (root);

	///<����� ��������� ����������.>
	for(int i = 0; i < M; i++)
		cout << result[i] << endl;

	return 0;
}

void input() {
	int vertex_1, vertex_2, cost;
	cin >> N;

	unsigned int size = N + 1;
	dsu.resize(size);
	tree.resize(size);
	dist.resize(size);
	used.resize(size, false);
	ancestor.resize(size);

	for(int i = 1; i < N; ++i)
	{
		cin >> vertex_1 >> vertex_2 >> cost;
		tree[vertex_1].push_back(make_pair(vertex_2, cost));
		tree[vertex_2].push_back(make_pair(vertex_1, cost));
	}	

	cin >> M;
	qq.resize(size);
	result.resize(M);
	for(int i = 0; i < M; i++)
	{
		cin >> vertex_1 >> vertex_2;
		qq[vertex_1].push_back(make_pair(vertex_2, i));
		qq[vertex_2].push_back(make_pair(vertex_1, i));
	}

}

int dsu_get (int v) {
	return v == dsu[v] ? v : dsu[v] = dsu_get (dsu[v]);     
}

void dsu_unite (int a, int b, int new_ancestor) {
	a = dsu_get(a),  b = dsu_get(b);
	if (rand() & 1)  
		swap (a, b);
	dsu[a] = b,  ancestor[b] = new_ancestor;
}

void dfs (int v) {
	dsu[v] = v,  ancestor[v] = v;
	used[v] = true;
	for (size_t i = 0; i < tree[v].size(); ++i)
		if (!used[tree[v][i].first]) {
			dfs (tree[v][i].first);
			dsu_unite (v, tree[v][i].first, v);
		}
	for (size_t i = 0; i < qq[v].size(); ++i)
		result[qq[v][i].second] = dist[v] + dist[qq[v][i].first] - 2 * dist[ancestor[dsu_get(qq[v][i].first)]];					
}

void dfs_cost (int v) 
{
	used[v] = true;
	for (vector < pair < int, int > >::iterator iter = tree[v].begin(); iter != tree[v].end(); ++iter)
		if (!used[iter->first]) {
			res += iter->second;
			dist[iter->first] = res;
			dfs_cost (iter->first);
			res -= iter->second;				
		}
		used[v] = false;
}	