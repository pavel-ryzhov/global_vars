#include <iostream>
#include <vector>

using namespace std;
#define MAX_N 40000
#define LOG_N 16

int n;
vector<int> graph[2][MAX_N];
vector<int> tree[MAX_N];
int h[MAX_N];
int up[MAX_N][LOG_N];

bool b[MAX_N];
void buildTree(int v, int l)
{
	h[v] = l;
	b[v] = 1;
	for (int i=0;i<graph[0][v].size();i++)
	{
		int v2 = graph[0][v][i];
		int dl = graph[1][v][i];
		if (!b[v2])
		{
			tree[v].push_back(v2);
			up[v2][0] = v;
			buildTree(v2, l+dl);
		}
	}
}

int tin[MAX_N];
int tout[MAX_N];
int time_;
void buildtime_(int v)
{
	tin[v] = time_;
	time_++;
	for (int i=1;i<LOG_N;i++)
		up[v][i] = up[up[v][i-1]][i-1];

	for (int i=0;i<tree[v].size();i++)
		buildtime_(tree[v][i]);
	tout[v] = time_;
	time_++;
}

bool upper(int a, int b)
{
	return ((tin[a] <= tin[b]) && (tout[a] >= tout[b]));
}

int r(int a, int b)
{
	if (upper(a,b)) return h[b]-h[a];
	if (upper(b,a)) return h[b]-h[a];
	
	int p = a;
	for (int i=LOG_N-1;i>=0;i--)
	{
		if (!upper(up[p][i], b))
			p = up[a][i];
	}
	p = up[p][0];
	return h[a] + h[b] - 2*h[p];
}

int main()
{
	cin>>n;
	for (int i=0;i<n-1;i++)
	{
		int a,b,l;
		cin>>a>>b>>l;
		graph[0][a-1].push_back(b-1);
		graph[1][a-1].push_back(l);
		graph[0][b-1].push_back(a-1);
		graph[1][b-1].push_back(l);
	}
	
	for (int i=0;i<n;i++) b[i]=0;
	buildTree(0, 0);

	time_ = 0;
	for (int i=0;i<LOG_N;i++) up[0][i]=0;
	buildtime_(0);

	int m;
	cin>>m;
	for (int u=0;u<m;u++)
	{
		int a,b;
		cin>>a>>b;
		cout<<r(a-1,b-1)<<endl;
	}
	return 0;
}
