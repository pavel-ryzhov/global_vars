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

	Arc()
	{

	};

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
	vector<vector<unsigned long> > PathLengthArray;
	vector<bool> UsedNodesBoolArray;
	vector<unsigned int> UsedNodes;

	void ReadTreeFromSTDIN()
	{
		try
		{
			unsigned int FirstNode, SecondNode, Weight, NodeCount;
			
			cin >> NodeCount;		

			TreeArcs = vector<vector<Arc> >(NodeCount, vector<Arc>(0));
			PathLengthArray = vector<vector<unsigned long> >(NodeCount); //, vector<unsigned long>(NodeCount));
			for(int i=0; i<NodeCount; i++)
			{
				PathLengthArray[i].resize(i+1);
			}
			UsedNodesBoolArray = vector<bool>(NodeCount);	

			for(unsigned int i=0; i < NodeCount - 1; i++)
			{
				cin >> FirstNode >> SecondNode >> Weight;

				Arc arc1(FirstNode-1, Weight);
				TreeArcs[SecondNode-1].push_back(arc1);

				Arc arc2(SecondNode-1, Weight);
				TreeArcs[FirstNode-1].push_back(arc2);
			}

		}
		catch(char *str)
		{
			cerr << "Îøèáêà: " << str << "\n";
		}
	};

	void BuildPathLengthArray (unsigned int v) 
	{
		UsedNodesBoolArray[v] = true;
		UsedNodes.push_back(v);
		for (vector<Arc>::iterator i=TreeArcs[v].begin(); i!=TreeArcs[v].end(); i++)
		{
			if ( !UsedNodesBoolArray[(*i).Node] )
			{
				for(unsigned int m = 0; m < UsedNodes.size(); m++)
				{
					PathLengthArray[max(UsedNodes[m],(*i).Node)][min(UsedNodes[m],(*i).Node)] = PathLengthArray[max(UsedNodes[m],v)][min(UsedNodes[m],v)] + (*i).Weight;
				}
				BuildPathLengthArray((*i).Node);
			}			
		}
	};

	void ReadQuestionsAndPrintAnswers() 
	{
		unsigned int QuestionCount;
		cin >> QuestionCount;

		unsigned int FirstNode;
		unsigned int SecondNode;
		for(unsigned int i = 0; i < QuestionCount; i++)
		{
			cin >> FirstNode >> SecondNode;

			cout << PathLengthArray[max(FirstNode-1, SecondNode-1)][min(FirstNode-1, SecondNode-1)] << endl;
		}
	};

};

int main()
{
	Tree tree;

	tree.ReadTreeFromSTDIN();

	tree.BuildPathLengthArray(0);

	tree.ReadQuestionsAndPrintAnswers();

	return 0;
};
