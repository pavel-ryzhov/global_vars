#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stack>
using namespace ::std;
struct triple
{
	int first;
	int second;
	int length;
};
int main ()
{
	int secondSepIndex;
	int firstVertex;
	int secondVertex;
	int edgeSize;
	int vertexCount;
	int numberOfPairs;
	int lca;
	vector<triple> unknownEdges;
	string line;

	cin  >> vertexCount;

	int  *parent = new int [vertexCount+1];
	bool *par    = new bool[vertexCount+1];
	int  *depth  = new int [vertexCount+1];

	for (int i=0;i<vertexCount+1;i++)
	{
		parent[i]=0;
		par[i]=false;
		depth[i]=0;
	}
	
	for (int i = 0;i < vertexCount-1; i++)
	{
		if (i==0)
		{
			cin >> firstVertex;
			cin >> secondVertex;
			cin >> edgeSize;
			parent[secondVertex] = firstVertex;
			parent[firstVertex]  = -1;
	
			par[secondVertex] = true;
			par[firstVertex]  = true;
	
			depth[firstVertex]  = 0;
			depth[secondVertex] = edgeSize;		
		}
		else
		{
			cin >> firstVertex;
			cin >> secondVertex;
			cin >> edgeSize;
			if (par[firstVertex] == true)
			{
				parent[secondVertex] = firstVertex;
				par[secondVertex] = true;
				depth[secondVertex] = depth[firstVertex] + edgeSize;
			}
			else
				if (par[secondVertex] == true)
				{
					parent[firstVertex] = secondVertex;
					par[firstVertex] = true;
					depth[firstVertex] = depth[secondVertex]+edgeSize;		
				}
				else
				{
					triple tripleEdge;

					tripleEdge.first  = firstVertex;
					tripleEdge.second = secondVertex;
					tripleEdge.length = edgeSize;
	
					unknownEdges.push_back(tripleEdge);
				}
		}
	}
	while (!unknownEdges.empty())
	{
		for (int i=0;i<unknownEdges.size();i++)
		{
			if (par[unknownEdges.at(i).first] == true)
			{
				parent[unknownEdges.at(i).second] = unknownEdges.at(i).first;
				par[unknownEdges.at(i).second] = true;
				depth[unknownEdges.at(i).second] = depth[unknownEdges.at(i).first] + unknownEdges.at(i).length;

				unknownEdges.erase(unknownEdges.begin()+i);
			}
			else
				if (par[unknownEdges.at(i).second] == true)
				{
					parent[unknownEdges.at(i).first] = unknownEdges.at(i).second;
					par[unknownEdges.at(i).first] = true;
					depth[unknownEdges.at(i).first] = depth[unknownEdges.at(i).second]+unknownEdges.at(i).length;	

					unknownEdges.erase(unknownEdges.begin()+i);
				}			
		}
	}
	cin>>numberOfPairs;

	for (int i=0;i<numberOfPairs;i++)
	{
		cin >> firstVertex;
		cin >> secondVertex;
		if (firstVertex==secondVertex) 
		{
			cout<<"0\n";
		}
		else
		{
			stack<int> firstStack;
			stack<int> secondStack;

			int a = firstVertex;
			int b = secondVertex;

			while(parent[a]>-1)
			{
				firstStack.push(a);
				a=parent[a];
			}
			firstStack.push(a);

			while(parent[b] > -1)
			{
				secondStack.push(b);
				b = parent[b];
			}
			secondStack.push(b);
			while (firstStack.size()>0 && secondStack.size()>0)
			{
				if (firstStack.top() == secondStack.top())
				{
					firstStack.pop();
					secondStack.pop();
				}
				else
					break;
			}
			if (firstStack.empty())
			{
				if(secondStack.empty())
				{
					lca=firstVertex;
				}
				else
				{
					lca=parent[secondStack.top()];
				}
			}
			else
			{
				lca=parent[firstStack.top()];
			}
			cout<<depth[firstVertex]+depth[secondVertex]-2*depth[lca]<<"\n";
		}
	}

	return 0;
}