#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

class node{
public:
	int value;
	int offsps;

	int distance;

	int depth;

	vector<node*> offsprings;
	
	node * ancestor;


	void add(int val, int dist)
	{
		node * added = new node(); 
		offsps++;

		this->offsprings.push_back(added);
		
		this->offsprings[offsps-1]->value = val;
		this->offsprings[offsps-1]->ancestor = this;
		this->offsprings[offsps-1]->depth = this->depth + 1;
		this->offsprings[offsps-1]->distance = this->distance + dist;
	}

	node(){
		this->offsps = 0;
		this->distance = 0;
	};

	node(int val)
	{
		this->value = val;
		this->offsps = 0;
		this->distance = 0;
	}
};

class LCA{
private:
	int height;
	int n;
	node * tree;
	vector <node*> links; //links to the nodes
	vector<int> P; //preprocessing vector
public:
	bool empty;
	LCA();
	void dfs(int node, int nr);
	int LCA_count(int x, int y);
};

LCA::LCA(){
	int buf[3];
	height = 0;
	cin>>n;
	links.resize(n+1);
	P.resize(n+1);
	empty = false;
	if(n == 1)
	{
		empty = true;
		return;
	}
	for(int i = 0; i < n - 1; i++)
	{
		cin>>buf[0];
		cin>>buf[1];
		cin>>buf[2];
		if(i == 0)
		{
			tree = new node(buf[0]);
			tree->depth = 1;
			tree->add(buf[1], buf[2]);
			tree->distance = 0;
			links[buf[0]] = tree;
			links[buf[1]] = tree->offsprings[0];
			height = 2;
			continue;
		}
		else
		{
			links[buf[0]]->add(buf[1], buf[2]);
			links[buf[1]] = links[buf[0]]->offsprings[links[buf[0]]->offsps-1] ;
			if((links[buf[0]]->depth + 1) > height)
				height = links[buf[0]]->depth + 1;
		}
	}
	dfs(1, (int)(sqrt((double)height)));
}
void LCA::dfs(int node, int nr)
{
	// lays in the first section
	if(links[node]->depth < nr)
	{
		P[node] = 1;
	}
	// lays in other sections
	else
	{
		// if lays in the beginning of the section
		if(!(links[node]->depth % nr))
		{
			P[node] = links[node]->ancestor->value;
		}
		else
		{
			P[node] = P[links[node]->ancestor->value];
		}
	}
	for(int i = 0; i < links[node]->offsprings.size(); i++)
		dfs(links[node]->offsprings[i]->value, nr);
}

int LCA::LCA_count(int x, int y)
{
	int a = x;
	int b = y;
	while(P[a]!=P[b])
	{
		if(links[a]->depth > links[b]->depth)
			a = P[a];
		else
			b = P[b];
	}

	while (a != b)
	{
        if(links[a]->depth > links[b]->depth)
			a = links[a]->ancestor->value;
          else
			b = links[b]->ancestor->value;
	}  
	return (links[x]->distance+links[y]->distance - 2 * (links[a]->distance));
	//return a;
}

int main()
{
	int lim;
	LCA * problem = new LCA();
	cin>>lim;
	for(int i = 0; i < lim; i++)
	{
		int a, b;
		cin>>a;
		cin>>b;
		if(!problem->empty)
			cout<<problem->LCA_count(a, b)<<endl;
	}
}