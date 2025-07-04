#include <iostream>


using namespace std;
//method of binary lift
//Karpulevich E A

int ** graph;
int ** rootsToFind;
int ** up;
int N, M, Log;
int timer;
int * tin, *tout;
bool * used;
int * masLen;


void dfs (int v, int p = 0) {
	used[v] = true;
	tin[v] = ++timer;
	up[v][0] = p;
	for (int i = 1; i <= Log; ++i)
		up[v][i] = up[up[v][i - 1]][i - 1];
	for (int i = 0; i < N; ++i) {
		if (graph[v][i] != -1)
		{
			int to = i;
			if (!used[to])
				dfs (to, v);
		}
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
			sum += graph [upPoint][temp];
			upPoint = temp;
		}
	return sum;
}

int main(int argc, char * argv[])
{
	int i, j;

	int tempA, tempB, tempWeight;

	//input
	//graph
	cin >> N;

	
	Log = 1;
	while ((1 << Log) <= N)  
		++Log;
	up = new int * [N];
	for (i = 0; i < N; i++)  
	{
		up [i] = new int [Log + 1];
	}
	graph = new int * [N];
	for (i = 0 ; i < N ; i++ )
	{
		graph [i] = new int [N];
		for (j = 0 ; j < N ; j++ )
		{
			graph [i][j] = -1;
		}
	}

	for (i = 0 ; i < N - 1 ; i++ )
	{
		cin >> tempA;
		cin >> tempB;
		cin >> tempWeight;
		graph [tempA - 1][tempB - 1] = tempWeight;
		graph [tempB - 1][tempA - 1] = tempWeight;
	}
	tin = new int [N];
	tout = new int [N];
	used = new bool [N];
	masLen = new int [N];
	for (i = 0 ; i < N ; i++ )
	{
		used[i] = false;
	}

	
	//preprocessing
	dfs (0);
	
	//wanted to count
	cin >> M;
	rootsToFind = new int * [M];
	for (i = 0 ; i < M ; i++ )
	{
		int temp;
		rootsToFind [i] = new int [2];
		
		cin >> temp;
		rootsToFind [i][0] = temp - 1;
		cin >> temp;
		rootsToFind [i][1] = temp - 1;
	}	

	

	//algorithm
	for (i = 0 ; i < M ; i++ )
	{
		//lca
		int res = lca (rootsToFind[i][0], rootsToFind[i][1]);
		//len
		int len = 0;
		int upPoint;
		upPoint = rootsToFind[i][0];
		len += pathLen(upPoint, res);
		upPoint = rootsToFind[i][1];
		len += pathLen(upPoint, res);
		masLen[i] = len;
	}

	for (i = 0 ; i < M ; i++ )
	{
		cout << masLen[i] << endl;
	}

	//delete
	for (i = 0 ; i < M ; i++ )
	{
		delete[] rootsToFind [i];
	}
	delete [] rootsToFind;
	for (i = 0 ; i < N ; i++ )
	{
		delete [] graph [i];
		delete [] up [i];
	}
	delete [] graph;
	delete [] up;
	delete [] tin;
	delete [] tout;
	delete [] used;
	delete [] masLen;

	return 0;
}


