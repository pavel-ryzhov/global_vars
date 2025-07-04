/**
    \file
    \brief  ����� ����������� ���� ����� ��������� ������
    \author ������ ����
*/

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <list>
#include <vector>
using namespace std;
struct Pair
{
	unsigned long FNode;
    unsigned long SNode;// <����� 1-� �������, ����� 2-� �������>, 
//����� �������� ���������� ��������� ����� ����������� ����
};
typedef vector <Pair> NumsMass;
typedef list <string> StringMass; // ������ �����
typedef vector <unsigned long> NumMass; // ������ ����� (����� ���������� ����� ����� ���������)
struct TreeNode; 
typedef vector <TreeNode> NodesMass; // ������ ������ 
const char* p_EXPR1 = "Enter your inputfile name\n";
const char* p_EXPR2 = "File opening error!\n";
const char* p_EXPR3 = "To stop executing program enter: end \n ";
const char* p_EXPR4 = "Result:\n";
const int INFILENAMESIZE = 100; // ������������ ����� �������� � �������� �������� ����� 
//----------------------------------------------------------
struct TreeNode // ������� ������
{
	unsigned long num; // ����� �������;
	unsigned long dist; // ���������� �� ������
	unsigned long Father; 	
};
//-----------------------------------------------------------
class CTreeAnalyse
{
private:
	unsigned long m_NodesCol; // ���������� ������� � ������    	
    unsigned long m_ResCol; // ���������� ������, ��� ������� ����� ����� ����� ����������� ����
	NumsMass m_ResNodes; // �������, ����� �������� ���������� ��������� ����� ����������� ����
	StringMass m_InStrs;// ������ ����� �� �������� �����
	NodesMass m_Tree; // ������
	NumMass m_Ways; // ����� ���������� ����� ����� ���������

public:
	CTreeAnalyse() {m_NodesCol = 0; m_ResCol = 0;}
	~CTreeAnalyse(){}
	void FileRead (); //������� ������ ���������� �� �������� �����
    void TreeCreating(); // ������� ��������� ����� �� �������� �����(�������� ������)
    void Str1Analyse(string& CurrStr); // ������� ������� ������ (�������-�������-����������)
	void Str2Analyse(string& CurrStr); // ������� ������� ������ (������� ��� ���������� ����)
	void AddNode (unsigned long& FNode, unsigned long& SNode, unsigned long& dist); // ����������
	// �������
    void ShortestWay(); // ���������� ���������� 
	// ����� ����� ���������
	unsigned long Depth(unsigned long& num); // ����������� ������� ������� 
	unsigned long FindWay(unsigned long v1, unsigned long v2); // ���������� ����������� ���� 
	// ����� ����� ���������
	void Out(); // ����� �� �����
	void OutToFile(); //����� � ���� 

};

//---------------------------------------------------------------------------------------------------
int main()
{
	printf( p_EXPR3 );
	while(1)
	{
		CTreeAnalyse Tree;     
	    Tree.FileRead(); 
	    Tree.TreeCreating();
	    Tree.ShortestWay();
	    Tree.Out();
	    Tree.OutToFile();
	}
	return 0;
}

//-------------------------------������� ������ ���������� �� �������� �����--------------------------
void CTreeAnalyse::FileRead()
{
    char inFileName[INFILENAMESIZE]; // �������� �������� �����
	char symb = '!'; // ������� ������
	string StrFromFile; // ����������� �� ����� ������
	FILE * inFile; // ��������� �� ������� ����
	printf(p_EXPR1);
	scanf("%s",inFileName);
	if ((string)inFileName == "end")
		exit(1);
	inFile = fopen (inFileName, "r"); // ��������� ������� ����
	if (inFile == NULL) 
	{
		perror (p_EXPR2);
		exit(1);
	}
	else
	{
		while (symb != EOF)
        {
            while (symb != '\n' && symb != EOF )
            {
                if (symb != '!')
				    StrFromFile += symb;
				symb = fgetc(inFile);
            }
            symb = fgetc(inFile);
			m_InStrs.push_back(StrFromFile); // ������� � ������ ����������� �� ����� ������ 
            StrFromFile = "";
		}
		fclose(inFile);
	}
}
//---------------------������� ��������� ����� �� �������� �����(�������� ������)-----------------------
void CTreeAnalyse::TreeCreating( )
{
  
	m_NodesCol = atoi (m_InStrs.begin()->c_str());
	// ������� ������!!!:
   	TreeNode Root;
    Root.num = 1;
	Root.Father = 0;
	Root.dist = 0;
	m_Tree.push_back(Root);
	unsigned int j = 1; // ������� ������
    StringMass::iterator i;
	for (i = ++m_InStrs.begin(); i !=m_InStrs.end() && j < m_NodesCol; i++)
	{ 
		Str1Analyse(*i); // ������ ������� ������
		j++;
	}
	// ��������� ���������� � ��������, ����� �������� ����� ����� ���������� ����
	m_ResCol = atoi (i->c_str());
	i++;
	j = 0;
	for (; i != m_InStrs.end() && j < m_ResCol; i ++ )
	{
		Str2Analyse(*i);
		j++;
	}
}
//----------------------������� ������� ������ (�������-�������-����������) - ���������� ������----
void CTreeAnalyse::Str1Analyse(string& CurrStr)
{
	unsigned long FirstNode = 0, SecNode = 0, dist = 0; // ������ �������, ������ ������� (�� �������)
    // � ���������� ����� ����
	string Curr;
	unsigned int k = 0; // ����������� ������� � ������� ������
	unsigned int num = 0; // ����� ����������� �� ������ �����
	while( k < CurrStr.length()) // ���� �� ������
	{
		Curr += CurrStr[k];
		if (k < CurrStr.length() - 1)
		   k++;
		if( CurrStr[k] == ' ' || k == CurrStr.length() - 1  )
		{
			switch (num)
			{
			case 0:
				FirstNode = atoi(Curr.c_str());
				break;
			case 1:
				SecNode = atoi(Curr.c_str());
				break;
			case 2:
				dist = atoi(Curr.c_str());
				break;
			}
		Curr = "";
		num++;	
		k++;
		}
	}
	AddNode (FirstNode, SecNode, dist); // ��������� ����� ������� � ������
}
//----------------------------������� ���������� ������� � ������----------------------------
void CTreeAnalyse::AddNode (unsigned long& FNode, unsigned long& SNode, unsigned long& dist)
{
	TreeNode newNode;
	newNode.num = SNode;
	newNode.Father = FNode;
	newNode.dist = dist;
	m_Tree.push_back(newNode);
}
//--------------------------������� ������� ������ (�������, ����� �������� ����������-------- 
//--------------------------����� ���������� ����)---------------------------------------------
void CTreeAnalyse::Str2Analyse(string& CurrStr)
{
	Pair CurrPair;
	string curr;
	int k = 0;
	while (CurrStr[k] != ' ')
	{
		curr += CurrStr[k];
		k++;
	}
	CurrPair.FNode = atoi(curr.c_str());
	curr = "";
	k++;
    while (k < CurrStr.length())
	{
		curr += CurrStr[k];
		k++;
	}
	CurrPair.SNode = atoi(curr.c_str());
	m_ResNodes.push_back(CurrPair);
}
//-------------------���������� ����������� ����---------------------------------------------
void CTreeAnalyse::ShortestWay()
{
	unsigned long way = 0; // ����� ����������� ����
	// ���� �� ������� ������, ��� ������� ���������� ��������� ����� ����������� ����
	for (NumsMass::iterator i = m_ResNodes.begin(); i != m_ResNodes.end(); i++)
	{
		way = FindWay (i->FNode, i->SNode);
        m_Ways.push_back(way);
	}
}
//------------------���������� ������� �������----------------------------------------------
unsigned long CTreeAnalyse::Depth(unsigned long& num) 
{
	int j = num;
	int d = 0; // �������
	while (m_Tree[j - 1].Father != 0)
	{ 
		j = m_Tree[j - 1].Father;
		d++;
	}
	return d;
}

//-----------------���������� ����������� ���� ��� 2-� ������------------------------
unsigned long CTreeAnalyse::FindWay(unsigned long v1, unsigned long v2)
{
	unsigned long way = 0; // ����� ����������� ����
	int d1 = 0, d2 = 0; // �������� ������ ��� ������
	d1 = Depth(v1);
	d2 = Depth(v2);
	while (d1 > d2)
	{
		way += m_Tree[v1 - 1].dist;
		v1 = m_Tree[v1 - 1].Father;
		d1--;
	}
    while (d1 < d2)
	{
		way += m_Tree[v2 - 1].dist;
		v2 = m_Tree[v2 - 1].Father;
		d2--;
	}
	while (v1 != v2)
	{
		way += m_Tree[v1 - 1].dist;
        v1 = m_Tree[v1 - 1].Father;
        way += m_Tree[v2 - 1].dist;
        v2 = m_Tree[v2 - 1].Father;
	}
    return way;
}
//-----------------------------����� �� �����---------------------------------------
void CTreeAnalyse::Out()
{
	printf(p_EXPR4); 
	for (NumMass::iterator i = m_Ways.begin(); i != m_Ways.end(); i++)
		printf ("%u \n",*i);
}
//----------------------------����� � ����------------------------------------------
void CTreeAnalyse::OutToFile()
{
	FILE* out;
	out = fopen("out", "w");
	for (NumMass::iterator i = m_Ways.begin(); i != m_Ways.end(); i++)
		fprintf (out, "%u\n",*i);
	fclose(out);
}
