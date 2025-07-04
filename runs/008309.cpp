#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

const int MAXN = 10000;
vector<int> g[MAXN], q[MAXN];
int dsu[MAXN], ancestor[MAXN], minAncestor[MAXN];
bool u[MAXN];
int request[MAXN][2], M;

class Element
{
private:
	Element* element;
	int cost;
	int number;
public:
	Element()
	{
		element = NULL;
		cost = 0;
		number = 0;
	}
	Element(Element* _element, int _cost, int _number)
	{
		element = _element;
		cost = _cost;
		number = _number;
	}
	Element* getElement()
	{
		return element;
	}

	void setElement(Element* _element)
	{
		element = _element;
	}

	int getCost()
	{
		return cost;
	}

	void setCost(int _cost)
	{
		cost = _cost;
	}

	int getNumber()
	{
		return number;
	}

	void setNumber(int _number)
	{
		number = _number;
	}
};
 
int dsu_get (int v) 
{
	return v == dsu[v] ? v : dsu[v] = dsu_get (dsu[v]);
}
 
void dsu_unite (int a, int b, int new_ancestor) 
{
	a = dsu_get (a),  b = dsu_get (b);
	if (rand() & 1)  swap (a, b);
	dsu[a] = b,  ancestor[b] = new_ancestor;
}
 
void dfs (int v) 
{
	dsu[v] = v,  ancestor[v] = v;
	u[v] = true;
	for (size_t i=0; i<g[v].size(); ++i)
		if (!u[g[v][i]]) 
		{
			dfs (g[v][i]);
			dsu_unite (v, g[v][i], v);
		}
	for (size_t i=0; i<q[v].size(); ++i)
		if (u[q[v][i]]) 
		{
			for (int j = 0; j < M; j++)
			{	
				if ( ( (request[j][0] == v) && (request[j][1] == q[v][i]) ) || ( (request[j][0] == q[v][i]) && (request[j][1] == v) ) )
				{
					minAncestor[j] = ancestor[ dsu_get(q[v][i]) ];
					break;
				}
			} 
		}
}

int main()
{
	int N, parent, child, cost, a, b, tempInd;
	Element elements[MAXN];
	int results[MAXN], sum;

	cin >> N;
	if (N == 1) 
	{
		cin >> parent >> child >> cost;
		cin >> M;
		cin >> a >> b;
		cout << cost;
		return 0;
	}
	
	elements[0].setElement(NULL);
	elements[0].setCost(0);
	elements[0].setNumber(0);
	for (int i = 0; i < N - 1; i++)
	{
		cin >> parent >> child >> cost;
		--child; --parent;
		elements[child].setElement(&elements[parent]);
		elements[child].setCost(cost);
		elements[child].setNumber(child);
		g[parent].push_back(child);
		g[child].push_back(parent);
	}
	
	cin >> M;
	for (int i = 0; i < M; i++)
	{
		cin >> a >> b;
		--a; --b;
		request[i][0] = a; request[i][1] = b;
		q[a].push_back(b);
		q[b].push_back(a);
	}

	dfs(0);

	for (int i = 0; i < M; i++)
	{
		sum = 0;
		tempInd = request[i][0];
		while (minAncestor[i] != elements[tempInd].getNumber())
		{
			sum += elements[tempInd].getCost();
			tempInd = elements[tempInd].getElement()->getNumber();
		}
		tempInd = request[i][1];
		while (minAncestor[i] != elements[tempInd].getNumber())
		{
			sum += elements[tempInd].getCost();
			tempInd = elements[tempInd].getElement()->getNumber();
		}
		results[i] = sum;
	}

	for (int i = 0; i < M; i++)
		cout << results[i] << '\n';
}