#include <fstream>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Arc
{
public:
	unsigned int Node;
	unsigned int Weight;

	Arc(){};

	Arc(unsigned int node, unsigned int weight)
	{
		Node = node;
		Weight = weight;
	};
};

class Tree
{
public:
	vector<vector<Arc> > TreeArcs;

	vector<unsigned int> InDepthNodeList;
	vector<unsigned int> FirstPositionList;

	vector<bool> Used;

	void ReadTree()
	{	
		try
		{
			unsigned int FirstNode;
			unsigned int SecondNode;
			unsigned int Weight;

			unsigned int NodeCount;
			cin >> NodeCount;
			
			TreeArcs = vector<vector<Arc> >(NodeCount, vector<Arc>(0));
			Used = vector<bool>(NodeCount);

			vector<unsigned int> firstPositionList(NodeCount);
			FirstPositionList = firstPositionList;
			
			for(unsigned int i=0; i < NodeCount - 1; i++)
			{
				cin >> FirstNode >> SecondNode >> Weight;

				Arc arc1(FirstNode-1, Weight);
				Arc arc2(SecondNode-1, Weight);

				TreeArcs[FirstNode-1].push_back(arc2);
				TreeArcs[SecondNode-1].push_back(arc1);
			}
		}
		catch(char *str)
		{
			cerr << "Îøèáêà: " << str << "\n";
		}
	};

	void MakeTourInDepth (unsigned int v) 
	{
		Used[v] = true;
		InDepthNodeList.push_back(v);
		for (vector<Arc>::iterator i=TreeArcs[v].begin(); i!=TreeArcs[v].end(); i++)
		{
			if (!Used[(*i).Node])
			{
				MakeTourInDepth ((*i).Node);
				InDepthNodeList.push_back(v);
			}			
		}
	};

	void BuildFirstList() 
	{
		for(unsigned int i = 1; i < InDepthNodeList.size(); i++)
		{
			if(FirstPositionList[InDepthNodeList[i]] == 0 && InDepthNodeList[i] != 0)
				FirstPositionList[InDepthNodeList[i]] = i;
		}		
	};

	void GetAnswers() 
	{
		unsigned int QuestionCount;
		unsigned int FirstNode;
		unsigned int SecondNode;
		unsigned int FirstNodePosition;
		unsigned int SecondNodePosition;
		vector<unsigned int> workNodeList;
		
		cin >> QuestionCount;
		for(unsigned int i = 0; i < QuestionCount; i++)
		{
			cin >> FirstNode >> SecondNode;

			FirstNodePosition = FirstPositionList[FirstNode-1];
			SecondNodePosition = FirstPositionList[SecondNode-1];

			if(FirstNodePosition > SecondNodePosition)
				swap(FirstNodePosition,SecondNodePosition);
					
			workNodeList.resize(SecondNodePosition - FirstNodePosition + 1);
			copy(InDepthNodeList.begin() + FirstNodePosition, InDepthNodeList.begin() + SecondNodePosition + 1, workNodeList.begin() );

			for(unsigned int i = 0; i < workNodeList.size(); i++)
			{
				for(unsigned int j = workNodeList.size() - 1; j > i; j--)
				{
					if(workNodeList[i] == workNodeList[j])
					{
						workNodeList.erase(workNodeList.begin() + i,workNodeList.begin() + j);
						break;
					}
				}
			}

			unsigned long Length = 0;
			for(unsigned int i = 0; i < workNodeList.size() - 1; i++)
			{
				for(int j = 0; j < TreeArcs[workNodeList[i]].size(); j++)
				{
					if(TreeArcs[workNodeList[i]][j].Node == workNodeList[i+1])
					{
						Length += TreeArcs[workNodeList[i]][j].Weight;
						break;
					}
				}	
			}

			cout << Length << endl;
			workNodeList.clear();
		}
	};

};

int main()
{
	Tree tree;

	//freopen("C:\\Yandex\\2.txt","r",stdin); 
	//freopen("C:\\Yandex\\Answer2.txt","w",stdout); 

	tree.ReadTree();

	tree.MakeTourInDepth(0);

	tree.BuildFirstList();

	tree.GetAnswers();




	return 0;
};

