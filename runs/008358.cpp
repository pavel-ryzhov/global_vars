#include <iostream>
#include <vector>
#include <map>
#include <stdlib.h>
#include <utility>
using namespace std;

const int MAXN = 40000;
vector<unsigned short> g[MAXN], q[MAXN];
unsigned short M, tempEl;
bool u[MAXN];
pair<unsigned short, unsigned> dsu[MAXN], element;
pair<unsigned short, unsigned short> temp1, temp2;
unsigned results[MAXN], sum;
multimap<pair<unsigned short, unsigned short>, unsigned short> qLinks;


class Element
{
private:
	map<unsigned short, unsigned short> cost;
	unsigned short parent;
public:
	
	unsigned short getCost(int i)
	{
		return cost[i];
	}

	void setCost(unsigned short _cost, unsigned short i)
	{
		cost[i] = _cost;
	}

	unsigned short getParent()
	{
		return parent;
	}
	void setParent(unsigned short _parent)
	{
		parent = _parent;
	}
} elements[MAXN];
 
pair<unsigned short, unsigned> dsu_get (unsigned short v) 
{
	if (v != dsu[v].first)
	{
		unsigned cost = dsu[v].second;
		dsu[v] = dsu_get(dsu[v].first);
		dsu[v].second += cost;
	}
	return dsu[v];
}
 
void dsu_unite (unsigned short b, unsigned short a) 
{
	dsu[a] = make_pair(b, elements[a].getCost(b));
}
 
void dfs (unsigned short v, unsigned short anc) 
{
	dsu[v] = make_pair(v, 0); 
	elements[v].setParent(anc);
	u[v] = true;
	for (size_t i=0; i<g[v].size(); ++i)
		if (!u[g[v][i]]) 
		{
			dfs (g[v][i], v);
			dsu_unite (v, g[v][i]);
		}
	for (size_t i=0; i<q[v].size(); ++i)
		if (u[q[v][i]]) 
		{
			element =  dsu_get(q[v][i]);
			sum = 0;
			tempEl = v;
			while (element.first != tempEl)
			{
				sum += elements[tempEl].getCost(elements[tempEl].getParent());
				tempEl = elements[tempEl].getParent();
			}
			
			temp1 = make_pair(v, q[v][i]);
			temp2 = make_pair(q[v][i], v);
			if (qLinks.count(temp1) > 0) 
			{
				if (qLinks.count(temp1) == 1)
					results[ qLinks.find(temp1)->second ] = sum + dsu[q[v][i]].second;
				else
				{
					pair<multimap<pair<unsigned short, unsigned short>, unsigned short>::iterator, multimap<pair<unsigned short, unsigned short>, unsigned short>::iterator> range;
					range = qLinks.equal_range(temp1);
					for (multimap<pair<unsigned short, unsigned short>, unsigned short>::iterator it = range.first; it != range.second; ++it)
					{
						results[ it->second ] = sum + dsu[q[v][i]].second;
					}
				}
			}
			if (qLinks.count(temp2) > 0)
			{
				if (qLinks.count(temp2) == 1)
					results[ qLinks.find(temp2)->second ] = sum + dsu[q[v][i]].second;
				else
				{
					pair<multimap<pair<unsigned short, unsigned short>, unsigned short>::iterator, multimap<pair<unsigned short, unsigned short>, unsigned short>::iterator> range;
					range = qLinks.equal_range(temp2);
					for (multimap<pair<unsigned short, unsigned short>, unsigned short>::iterator it = range.first; it != range.second; ++it)
					{
						results[ it->second ] = sum + dsu[q[v][i]].second;
					}
				}
				
			}
		}
}

int main()
{
	unsigned short N, beg, end, a, b, cost;
	pair<unsigned short, unsigned short> tempPair;

	cin >> N;
	if (N == 1) 
	{
		cin >> M;
		cin >> a >> b;
		cout << 0;
		return 0;
	}
	
	for (int i = 0; i < N - 1; i++)
	{
		cin >> beg >> end >> cost;
		--beg; --end;
		elements[beg].setCost(cost, end);
		elements[end].setCost(cost, beg);
		g[beg].push_back(end);
		g[end].push_back(beg);
	}
	
	cin >> M;
	for (int i = 0; i < M; i++)
	{
		cin >> a >> b;
		--a; --b;
		q[a].push_back(b);
		q[b].push_back(a);
		tempPair = make_pair(a, b);
		qLinks.insert(pair<pair<unsigned short, unsigned short>, unsigned short>(tempPair, i));
	}
	
	dfs(0, 0);
	
	for (int i = 0; i < M; i++)
	{
		cout << results[i] << '\n';
	}
	
	return 0;
}