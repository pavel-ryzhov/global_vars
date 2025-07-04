#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <cstdlib>

using std::cout;
using std::cin;
using std::vector;
using std::pair;
using std::list;
using std::make_pair;
using std::swap;

typedef list< pair<int, int> > Edge; //first int to link, second to weight
typedef vector< Edge > Tree; 
typedef vector< vector< pair<int, int> > > Queries;

vector<int> dsu, ancestor;
vector<long long> depth;
vector<bool> visited;

int dsu_get(int v)
{
	return v == dsu[v] ? v : dsu[v] = dsu_get(dsu[v]);
}

void dsu_unite(int a, int b, int new_ancestor)
{
	a = dsu_get(a);
	b = dsu_get(b);
	if ( rand() & 1 )
		swap(a,b);
	dsu[a] = b;
	ancestor[b] = new_ancestor;
}

template<class T> std::ostream& operator<<(std::ostream& out, const vector<T>& vec)
{
	size_t size = vec.size();
	for ( size_t i=0; i<size-1; ++i )
		out << vec[i] << std::endl;
	out << vec[size-1];
	return out;
}
void input_data(Tree& t, Queries& q, vector<long long>& answers)
{
	int n, a, b, l;
	cin >> n;
	t.resize(n);
	dsu.resize(n);
	ancestor.resize(n);
	depth.resize(n);
	visited.resize(n);
	q.resize(n);
	for ( int i=0; i<n-1; ++i )
	{
		cin >> a >> b >> l;
		--a;
		--b;
		t[a].push_front( make_pair(b, l) );
		t[b].push_front( make_pair(a, l) );
	}
	cin >> n;
	answers.resize(n);
	for ( int i=0; i<n; ++i )
	{
		cin >> a >> b;
		--a;
		--b;
		q[a].push_back( make_pair(b, i));
		q[b].push_back( make_pair(a, i) );
	}
}

void solve(int v, int weight, Tree& t, Queries& q, vector<long long>& answers)
{
	dsu[v] = v;
	ancestor[v] = v;
	depth[v] = weight;
	visited[v] = true;
	for ( list<pair<int,int> >::iterator i = t[v].begin(); i != t[v].end(); ++i )
		if ( !visited[i->first] )
		{
			solve(i->first, i->second+weight, t, q, answers);
			dsu_unite(v, i->first, v);
		}
	for ( size_t i=0; i<q[v].size(); ++i )
		if ( visited[q[v][i].first] )
		{
			answers[q[v][i].second] = depth[v] + depth[q[v][i].first] - 2*depth[ancestor[dsu_get(q[v][i].first)]];
		}
}

int main()
{
	Tree t;
	Queries q;
	vector<long long> answers;
	input_data(t, q, answers);
	solve(0, 0, t, q, answers);
	cout << answers;
	return 0;
}

