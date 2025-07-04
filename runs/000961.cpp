#include<stdio.h>
#include<vector>
using namespace std;

class node
{
public:
	int nomer;/*если нумерация произвольная*/
	vector<int> vec;/*вер-ключ_1, вес_1, вер-ключ_2, вес_2, ...*/
};


int numNodes = 0;
vector<node*> gr;
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
	int key1 = -1, key2 = -1;
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
		
		key1 = -1; key2 = -1;
		
		for(j = 0; j<gr.size(); j++)
		{
			if(node1 == gr[j]->nomer)
				key1 = j;
			if(node2 == gr[j]->nomer)
				key2 = j;
		}
		
		if(key1 == -1)
		{
			node*nd = new node();
			nd->nomer = node1;
			gr.push_back(nd);
			key1 = gr.size()-1;
		}

		if(key2 == -1)
		{
			node*nd = new node();
			nd->nomer = node2;
			gr.push_back(nd);
			key2 = gr.size()-1;
		}

		gr[key1]->vec.push_back(key2);
		gr[key1]->vec.push_back(weight);

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
		v_temp.push_back(node1);
		v_temp.push_back(node2);

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
	for (size_t i=0; i<gr[v]->vec.size(); i = i+2) {
		int to = gr[v]->vec[i];
		if (!used[to])
			dfs (to, v, weight + gr[v]->vec[i+1]);
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

int find_key(int num)
{
	for(size_t j = 0; j<gr.size(); j++)
		{
			if(num == gr[j]->nomer)
				return j;
		}

	return -1;
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

	int a, b, key1, key2, key3;
	for (size_t i=0; i<n_pair.size(); i++) 
	{
		a = n_pair[i][0];
		b = n_pair[i][1]; 
		key1 = find_key(a);
		key2 = find_key(b);
		if(key1 == -1 || key2 == -1)
		{
			perror("Error in nodes queries!!! Check data in input!");
			return 1;
		}
		key3 = lca(key1, key2); 
		printf("%d\n", ws[key1]+ws[key2] - 2*ws[key3]);
	}


	return 0;
	
}





