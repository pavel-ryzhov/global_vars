#include<stdio.h>
#include<vector>
using namespace std;


int numNodes = 0;
vector<vector<int> > gr;
vector<vector<int> > n_pair;


int l;
vector<char> used;
vector<int> tin, tout, ws;/*ws - "высоты" = сумме весов ребер*/
int timer;
vector <vector<int> > up;


int fill_data()
{
	int numN = 0;
	scanf("%d", & numN);
	numNodes = numN;
	size_t i = 0, j = 0;
	int node1 = 0, node2 = 0, weight = 0; 
	gr.resize(numN);
	numN--;
	if(numN == 0) 
	{
		scanf("%d", & node1);
		scanf("%d", & node1);
		scanf("%d", & node1);
		return -5;
	}
	/*fill graph*/
	while(i< numN)
	{
		scanf("%d", & node1);
		scanf("%d", & node2);
		scanf("%d", & weight);

		gr[node1-1].push_back(node2-1);
		gr[node1-1].push_back(weight);
		gr[node2-1].push_back(node1-1);
		gr[node2-1].push_back(weight);

		i++;
	}

	/*fill queries*/
	scanf("%d", & numN);
	i = 0;
	while(i<numN)
	{
		vector<int> v_temp;
		scanf("%d", & node1);
		scanf("%d", & node2);
		v_temp.push_back(node1-1);
		v_temp.push_back(node2-1);

		n_pair.push_back(v_temp);
		i++;
	}

	return numN;
}

void dfs (int v, int p = 0, int weight = 0) 
{
	used[v] = true;
	tin[v] = ++timer;
	up[v][0] = p;
	ws[v] = weight;

	for (int i=1; i<=l; ++i)
		up[v][i] = up[up[v][i-1]][i-1];
	for (size_t i=0; i<gr[v].size(); i = i+2) {
		int to = gr[v][i];
		if (!used[to])
			dfs (to, v, weight + gr[v][i+1]);
	}
	tout[v] = ++timer;
}

bool upper (int a, int b) 
{
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca (int a, int b) 
{
	if (upper (a, b))  return a;
	if (upper (b, a))  return b;
	for (int i=l; i>=0; --i)
		if (! upper (up[a][i], b))
			a = up[a][i];
	return up[a][0];
}



int main()
{
	
	int res = fill_data();

	if(res == -5)
	{
		printf("0");
		return 0;
	}
	used.resize(numNodes);
	tin.resize(numNodes);
	tout.resize(numNodes);
	up.resize(numNodes);
	ws.resize(numNodes);
	l = 1;
	while ((1<<l) <= numNodes)  ++l;
	for (int i=0; i<numNodes; ++i)  up[i].resize(l+1);
	dfs (0);

	int a, b, c;
	for (size_t i=0; i<n_pair.size(); i++) 
	{
		a = n_pair[i][0];
		b = n_pair[i][1]; 

		c = lca(a, b); 
		printf("%d\n", ws[a]+ws[b] - 2*ws[c]);
	}


	return 0;
	
}





