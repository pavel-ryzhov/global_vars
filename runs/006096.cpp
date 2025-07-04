/* ������ B. ���������� � ������.
 * ���� �������:
 *	-	���� � ��� ������� ����� ����� �������� ����� ���������� ������, ������� ����������� ������������ ����� ������� ��� ������ LCA.
 *
 *	-	��������� ������, �� ���� ���������� ������ ������ ���������� �� ����� �� i-�� ������� ������ branch_length,
 *		�������� ����� ���� ����� ��������� �� �������: L = branch_length[a] + branch_length[b] - 2 * branch_length[LCA(a, b)].
 *
 *	-	LCA(a, b) ����� �������� ������� ��������: �������� ����������� ����������� �������� A �� ��������� ������ ������,
 *		������� �������� ������������ ������� ��� ��������� �� ������ (������� ���������������� �����������): dsu[] (�� O(n)),
 *		����� �� ~O(1) �� ����� �������� LCA(a, b) � ��������� ����� ���� �� ����� ������ � ������� ������ �����.
 */

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

typedef pair<int, int> item;
typedef vector<item> requests;			// ��� ��������
typedef vector<item> graph;				// vector �� ��������� pair, �.�. ��� ���������� ������� ����� �����

const int MAX = 40000;
graph G[MAX];							// ����
requests Q[MAX];						// ������� �������� - ������ �� �������� �� 2-� ���������, ��� � ����� ������ ����� ���������� ��������
long branch_length[MAX], ancestor[MAX];	// ������� ���������� �� ����� � �������
bool u[MAX];
int dsu[MAX];							// dsu - ������� ���������������� ��������
long ans[MAX];							// ������ �������


int find(int v) {return v == dsu[v] ? v : dsu[v] = find(dsu[v]); }	// ����� ������������� � ���������� path compression
void unite(int a, int b, int new_ancestor)							// �����, ������������ ������������ (������������ ����������������� ���������)
{
	a = find(a); b = find(b);
	if(rand() & 1) swap(a, b);
	dsu[a] = b; ancestor[b] = new_ancestor;
}


// ����� ����� � ������� � ����������� ��������������� ��������� �� �������������� �������� � ������� �� �������
void dfs(int v)
{
	int LCA;
	dsu[v] = v; ancestor[v] = v; u[v] = true;

	// ���� ������, ����� dsu � ���������� ������ �� ����� �� ���� ������, ������� ����� � branch_length[]
	for ( size_t i = 0; i < G[v].size(); i++ )
		if ( !u[G[v][i].first] )
		{
			branch_length[G[v][i].first] = branch_length[v] + G[v][i].second;
			dfs(G[v][i].first);
			unite(v, G[v][i].first, v);
		}
	// ����������� �� �������� ��� v
	for ( size_t i = 0; i < Q[v].size(); i++ )
		if ( u[Q[v][i].first] )
		{
			LCA = ancestor[find(Q[v][i].first)];
			ans[Q[v][i].second] = branch_length[v] + branch_length[Q[v][i].first] - 2 * branch_length[LCA];	// ��������� ����� ���� �� ����������� ���� �������
		}

}

int main()
{
	// ��������� ������� ����. fixed: � ������ ������ ��������� ���� ���������� �� ���������, ����� ���������� branch_length ���������� � ������� dfs
	int N; cin >> N;
	int a, b, l;
	for (int i = 0; i < N-1; i++)
	{
		cin >> a >> b >> l; a--, b--;
		G[a].push_back(item(b, l)); G[b].push_back(item(a, l));
	}

	// ��������� �������
	int M; cin >> M;
	for (int i = 0; i < M; i++)
	{
		cin >> a >> b; a--, b--;
		Q[a].push_back(item(b, i)), Q[b].push_back(item(a, i));	// ������� ���������� ���, �.�. ��� ������� �������� �� �� �����, � ����� ������������������ ����� ������� ���������
	}

	// ������� ���� � �������, ������� �� ��������������� �������
	branch_length[0] = 0;
	dfs(0);

	// ������� ������ �� ������� � ����������� �������
	for (int i = 0; i < M; i++)
		cout << ans[i] << endl;

	return 0;
}