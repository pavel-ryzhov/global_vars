#include <vector>
#include <iostream>
#define MINUS_ODIN 64000

using namespace std;
//method of binary lift
//Karpulevich E A

struct Point{
	unsigned short to;
	unsigned short len;
};

typedef vector < vector<Point> > graphType;

graphType g;

unsigned short ** up;
int N, M, Log;
int timer;
int * tin, *tout;
bool * used;


void dfs (int v, int p = 0) {
	used[v] = true;
	tin[v] = ++timer;
	up[v][0] = p;
	for (int i = 1; i <= Log; ++i)
		up[v][i] = up[up[v][i - 1]][i - 1];
	for (unsigned short i = 0; i < g[v].size(); ++i) {
		int to = g[v][i].to;
		if (!used[to])
			dfs (to, v);
	}
	tout[v] = ++timer;
}

bool upper (int a, int b) {
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca (int a, int b) {
	if (upper (a, b))  return a;
	if (upper (b, a))  return b;
	for (int i = Log; i >= 0; --i)
		if (! upper (up[a][i], b))
			a = up[a][i];
	return up[a][0];
}

int pathLen (int upPoint, int res)
{
	int sum = 0;
	while (upPoint != res)
		{
			int temp = up[upPoint][0];
			for(unsigned short i = 0; i < g[upPoint].size(); i++)
			{
				if( g [upPoint][i].to == temp)
					sum += g [upPoint][i].len;
			}
			upPoint = temp;
		}
	return sum;
}

int main(int argc, char * argv[])
{
	int i;

	int tempA, tempB, tempWeight;

	//input
	//graph
	cin >> N;

	
	Log = 1;
	while ((1 << Log) <= N)  
		++Log;
	up = new unsigned short * [N];
	for (i = 0; i < N; i++)  
	{
		up [i] = new unsigned short [Log + 1];
	}

	g.resize(N);
	for (i = 0 ; i < N - 1 ; i++ )
	{
		g[i].resize(0);
	}

	for (i = 0 ; i < N - 1 ; i++ )
	{
		cin >> tempA;
		cin >> tempB;
		cin >> tempWeight;
		
		Point x;
		x.len = tempWeight;
		x.to = tempB - 1;
		g[tempA - 1].push_back(x);
		x.len = tempWeight;
		x.to = tempA - 1;
		g[tempB - 1].push_back(x);
	}
	for (i = 0 ; i < N - 1 ; i++ )
	{
		Point x;
		x.len = 0;
		x.to = i;
		g[i].push_back(x);
	}

	tin = new int [N];
	tout = new int [N];
	used = new bool [N];
	for (i = 0 ; i < N ; i++ )
	{
		used[i] = false;
	}

	
	//preprocessing
	dfs (0);
	
	//wanted to count
	cin >> M;


	//algorithm
	for (i = 0 ; i < M ; i++ )
	{
		int a, b;
		
		cin >> a;
		a -= 1;
		cin >> b;
		b -= 1;
	
	
		//lca
		int res = lca (a, b);
		//len
		int len = 0;
		int upPoint;
		upPoint = a;
		len += pathLen(upPoint, res);
		upPoint = b;
		len += pathLen(upPoint, res);
		cout << len << endl;
	}

		


	//delete
	for (i = 0 ; i < N ; i++ )
	{
		delete [] up [i];
	}
	delete [] up;
	delete [] tin;
	delete [] tout;
	delete [] used;

	return 0;
}


