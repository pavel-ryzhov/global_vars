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
	vector<vector<Arc> >* TreeArcs;
	vector<vector<unsigned long> >* PathLengthArray;
	vector<bool>* Used;

	~Tree()
	{
		delete(TreeArcs);
		delete(PathLengthArray);
		delete(Used);
	}

	/*
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

			TreeArcs = new vector<vector<Arc> >(NodeCount, vector<Arc>(0));
			PathLengthArray = new vector<vector<unsigned long> >[NodeCount];
			Used = new vector<bool>(NodeCount);

			for(unsigned int i=0; i < NodeCount - 1; i++)
			{
				in >> FirstNode;
				in >> SecondNode;
				in >> Weight;
				Arc arc1(FirstNode-1, Weight);
				TreeArcs->at(SecondNode-1).push_back(arc1);

				Arc arc2(SecondNode-1, Weight);
				TreeArcs->at(FirstNode-1).push_back(arc2);
			}

		}
		catch(char *str)
		{
			cerr << "Ошибка: " << str << "\n";
		}
		in.close();
	};
	*/


	void ReadTreeFromSTDIN()
	{
		try
		{
			unsigned int FirstNode;
			unsigned int SecondNode;
			unsigned int Weight;

			unsigned int NodeCount;
			cin >> NodeCount;		

			TreeArcs = new vector<vector<Arc> >(NodeCount, vector<Arc>(0));
			PathLengthArray = new vector<vector<unsigned long> >(NodeCount, vector<unsigned long>(NodeCount));
			Used = new vector<bool>(NodeCount);

			for(unsigned int i=0; i < NodeCount - 1; i++)
			{
				cin >> FirstNode;
				cin >> SecondNode;
				cin >> Weight;
				Arc arc1(FirstNode-1, Weight);
				TreeArcs->at(SecondNode-1).push_back(arc1);

				Arc arc2(SecondNode-1, Weight);
				TreeArcs->at(FirstNode-1).push_back(arc2);
			}

		}
		catch(char *str)
		{
			cerr << "Ошибка: " << str << "\n";
		}
	};

	void BuildPathLengthArray (unsigned int v) 
	{
		Used->at(v) = true;
		for (vector<Arc>::iterator i=TreeArcs->at(v).begin(); i!=TreeArcs->at(v).end(); i++)
		{
			if ( !Used->at((*i).Node) )
			{
				for(unsigned int m = 0; m < Used->size(); m++)
				{
					if(Used->at(m))
					{
						PathLengthArray->at(m).at((*i).Node) = PathLengthArray->at(m).at(v) + (*i).Weight;
						PathLengthArray->at((*i).Node).at(m) = PathLengthArray->at(m).at((*i).Node);
					}
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
		vector<unsigned long> Answers;
		for(unsigned int i = 0; i < QuestionCount; i++)
		{
			cin >> FirstNode;
			cin >> SecondNode;

			Answers.push_back(PathLengthArray->at(FirstNode-1).at(SecondNode-1));
		}

		for(unsigned int i = 0; i < Answers.size(); i++)
		{
			cout << Answers[i] << endl;
		}
	};

};

int main()
{
	Tree tree;

	//tree.ReadTreeFromFile("C:\\Yandex\\2.txt");
	tree.ReadTreeFromSTDIN();

	tree.BuildPathLengthArray(0);

	tree.ReadQuestionsAndPrintAnswers();

	return 0;
};
