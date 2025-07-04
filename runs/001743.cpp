#include <fstream>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Arc
{
public:
	unsigned int FirstNode;
	unsigned int SecondNode;
	unsigned int Weight;

	Arc()
	{

	};

	Arc(unsigned int firstNode, unsigned int secondNode, unsigned int weight)
	{
		FirstNode = firstNode;
		SecondNode = secondNode;
		Weight = weight;
	};
};

class TwoNodes
{
public:
	unsigned int FirstNode;
	unsigned int SecondNode;

	TwoNodes(unsigned int firstNode, unsigned int secondNode)
	{
		FirstNode = firstNode;
		SecondNode = secondNode;
	};
};

class Tree
{
public:
	vector<vector<unsigned int> > TreeLinks;
	vector<Arc> ArcList;
	vector<TwoNodes> QuestionList;

	vector<unsigned int> InDepthNodeList;
	vector<unsigned int> FirstPositionList;

	vector<bool> Used;

	void ReadTreeFromFile(string filename)
	{
		ifstream in;  // Поток для чтения
		in.open(filename.c_str());
		
		try
		{
			unsigned int FirstNode;
			unsigned int SecondNode;
			unsigned int Weight;

			unsigned int NodeCount;
			in >> NodeCount;
			
			vector<vector<unsigned int> > treelinks(NodeCount, vector<unsigned int>(0));
			TreeLinks =  treelinks;

			vector<bool> used(NodeCount);
			Used = used;

			vector<unsigned int> firstPositionList(NodeCount);
			FirstPositionList = firstPositionList;
			
			for(unsigned int i=0; i < NodeCount - 1; i++)
			{
				in >> FirstNode;
				in >> SecondNode;
				in >> Weight;
				Arc arc(FirstNode-1, SecondNode-1, Weight);
				ArcList.push_back(arc);

				TreeLinks[FirstNode-1].push_back(SecondNode-1);
				TreeLinks[SecondNode-1].push_back(FirstNode-1);
			}

			unsigned int QuestionCount;
			in >> QuestionCount;
			for(unsigned int i=0; i < QuestionCount; i++)
			{
				in >> FirstNode;
				in >> SecondNode;
				TwoNodes twoNode(FirstNode-1, SecondNode-1);
				QuestionList.push_back(twoNode);
			}
		}
		catch(char *str)
		{
			cerr << "Ошибка: " << str << "\n";
		}
		in.close();
	};

	void ReadTreeFromSTDIN()
	{	
		try
		{
			unsigned int FirstNode;
			unsigned int SecondNode;
			unsigned int Weight;

			unsigned int NodeCount;
			cin >> NodeCount;
			
			vector<vector<unsigned int> > treelinks(NodeCount, vector<unsigned int>(0));
			TreeLinks =  treelinks;

			vector<bool> used(NodeCount);
			Used = used;

			vector<unsigned int> firstPositionList(NodeCount);
			FirstPositionList = firstPositionList;
			
			for(unsigned int i=0; i < NodeCount - 1; i++)
			{
				cin >> FirstNode;
				cin >> SecondNode;
				cin >> Weight;
				Arc arc(FirstNode-1, SecondNode-1, Weight);
				ArcList.push_back(arc);

				TreeLinks[FirstNode-1].push_back(SecondNode-1);
				TreeLinks[SecondNode-1].push_back(FirstNode-1);
			}

			unsigned int QuestionCount;
			cin >> QuestionCount;
			for(unsigned int i=0; i < QuestionCount; i++)
			{
				cin >> FirstNode;
				cin >> SecondNode;
				TwoNodes twoNode(FirstNode-1, SecondNode-1);
				QuestionList.push_back(twoNode);
			}
		}
		catch(char *str)
		{
			cerr << "Ошибка: " << str << "\n";
		}
	};

	void MakeTourInDepth (unsigned int v) 
	{
		Used[v] = true;
		InDepthNodeList.push_back(v);
		for (vector<unsigned int>::iterator i=TreeLinks[v].begin(); i!=TreeLinks[v].end(); i++)
		{
			if (!Used[*i])
			{
				MakeTourInDepth (*i);
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

	void GetAnswersToFile() 
	{
		ofstream out;  // Поток для записи
		string filename = "C:\\Yandex\\Answer2.txt";
		out.open(filename.c_str());

		for(unsigned int question = 0; question < QuestionList.size(); question++)
		{
			unsigned int FirstNode = QuestionList[question].FirstNode;
			unsigned int SecondNode = QuestionList[question].SecondNode;

			unsigned int FirstNodePosition = FirstPositionList[FirstNode];
			unsigned int SecondNodePosition = FirstPositionList[SecondNode];

			if(FirstNodePosition > SecondNodePosition)
			{
				unsigned int temp = SecondNodePosition;
				SecondNodePosition = FirstNodePosition;
				FirstNodePosition = temp;
			}
			
			vector<unsigned int> workNodeList;
			for(unsigned int i = FirstNodePosition; i <= SecondNodePosition; i++)
			{
				workNodeList.push_back(InDepthNodeList[i]);
			}

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
				bool b = false;
				unsigned int k = 0;
				while(!b)
				{
					if( (ArcList[k].FirstNode == workNodeList[i] && ArcList[k].SecondNode == workNodeList[i+1])
						|| (ArcList[k].SecondNode == workNodeList[i] && ArcList[k].FirstNode == workNodeList[i+1])
						)
					{
						b = true;
						Length += ArcList[k].Weight;
					}
					k++;
				}
			}

			out << Length << endl;

		}

		out.close();
	};

	void GetAnswersToSTDOUT() 
	{
		for(unsigned int question = 0; question < QuestionList.size(); question++)
		{
			unsigned int FirstNode = QuestionList[question].FirstNode;
			unsigned int SecondNode = QuestionList[question].SecondNode;

			unsigned int FirstNodePosition = FirstPositionList[FirstNode];
			unsigned int SecondNodePosition = FirstPositionList[SecondNode];

			if(FirstNodePosition > SecondNodePosition)
			{
				unsigned int temp = SecondNodePosition;
				SecondNodePosition = FirstNodePosition;
				FirstNodePosition = temp;
			}
			
			vector<unsigned int> workNodeList;
			for(unsigned int i = FirstNodePosition; i <= SecondNodePosition; i++)
			{
				workNodeList.push_back(InDepthNodeList[i]);
			}

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
				bool b = false;
				unsigned int k = 0;
				while(!b)
				{
					if( (ArcList[k].FirstNode == workNodeList[i] && ArcList[k].SecondNode == workNodeList[i+1])
						|| (ArcList[k].SecondNode == workNodeList[i] && ArcList[k].FirstNode == workNodeList[i+1])
						)
					{
						b = true;
						Length += ArcList[k].Weight;
					}
					k++;
				}
			}

			cout << Length << endl;

		}
	};

};

int main()
{
	Tree tree;

	//tree.ReadTreeFromFile("C:\\Yandex\\2.txt");
	tree.ReadTreeFromSTDIN();


	tree.MakeTourInDepth(0);

	tree.BuildFirstList();

	
	//tree.GetAnswersToFile();
	tree.GetAnswersToSTDOUT();




	return 0;
};
