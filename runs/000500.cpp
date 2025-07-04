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
//#include <time.h>
using namespace std;
struct Duga
{
	unsigned long FNode;
	unsigned long SNode;
    unsigned long dist;
};
typedef list <Duga> DugsType; // ������ ���
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
const int INSIZE = 100; // ������������ ����� �������� � �������� �������� ����� 
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
	DugsType Dugi; // ������ ���, ��������� �� �������� �����
	bool isRoot; // ��� ���� ������
	bool flag; 

public:
	CTreeAnalyse() {m_NodesCol = 0; m_ResCol = 0; isRoot = false; flag = false;}
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
	void FileReadStream(); // ������ �� ������
	bool FindNode(unsigned long num); // ����� ������� � �������
	NodesMass::iterator FindNode2(unsigned long num);
	void AddToDugi(unsigned long& FNode, unsigned long& SNode, unsigned long& dist); // ���������� 
	//� ������ ��� 
    void DugiAnalys(); // ������ ������� ���
	void DugaAnalys(DugsType::iterator d); // ������ ��������� ����
};

//---------------------------------------------------------------------------------------------------
int main()
{
			  
	CTreeAnalyse Tree;     
	Tree.FileRead(); 
//	Tree.FileReadStream();
	Tree.TreeCreating();
	Tree.ShortestWay();
	Tree.Out();
	return 0;
}
//---------------------------������� ������ �� ������----------------------------------
void CTreeAnalyse::FileReadStream()
{
	int strcol = 0;
	char symb = ' '; // ������� ������
	int i = 0;
	string StrFromFile; // ����������� ������
    symb = getchar();
	while (symb != '\n')
	{
		StrFromFile += symb;
		symb = getchar();
	}
	strcol = atoi(StrFromFile.c_str());
    m_InStrs.push_back(StrFromFile); // ������� � ������ ����������� �� ����� ������ 
    StrFromFile = "";
	for (i = 1; i < strcol; i++)
	{
		symb = getchar();
		while (symb != '\n')
		{
			StrFromFile += symb;
			symb = getchar();
		}
        m_InStrs.push_back(StrFromFile); // ������� � ������ ����������� �� ����� ������ 
        StrFromFile = "";
	}
    symb = getchar();
	while (symb != '\n')
	{
	    StrFromFile += symb;
		symb = getchar();
	}
	strcol = atoi(StrFromFile.c_str());
    m_InStrs.push_back(StrFromFile); // ������� � ������ ����������� �� ����� ������ 
    strcol = atoi(StrFromFile.c_str());
	StrFromFile = "";
	for (i = 0; i < strcol; i++)
	{
		symb = getchar();
		while (symb != '\n')
		{
	    	StrFromFile += symb;
			symb = getchar();
		}
        m_InStrs.push_back(StrFromFile); // ������� � ������ ����������� �� ����� ������ 
		StrFromFile = "";
	}
}

//-------------------------------������� ������ ���������� �� �������� �����--------------------------
void CTreeAnalyse::FileRead()
{
    char inFileName[INSIZE]; // �������� �������� �����
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
	DugiAnalys();
}
//----------------------������� ������� ������ (�������-�������-����������) - ���������� ������----
void CTreeAnalyse::Str1Analyse(string& CurrStr)
{
	unsigned long FirstNode = 0, SecNode = 0, dist = 0; // ������ �������, ������ ������� (�� �������)
    // � ���������� ����� ����
	string Curr;
	unsigned int k = 0; // ����������� ������� � ������� ������
	unsigned int num = 0; // ����� ����������� �� ������ �����
	for(k = 0; k < CurrStr.length(); k ++) // ���� �� ������
	{		
	    if (CurrStr[k] != ' ')
		    Curr += CurrStr[k];
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
		}
   	}
	AddToDugi (FirstNode, SecNode, dist); // ��������� ����� ������� � ������
}
//-----------------���������� � ������� ���-------------------------------------------------
void CTreeAnalyse::AddToDugi(unsigned long& FNode, unsigned long& SNode, unsigned long& dist)
{
	Duga duga;
	duga.FNode = FNode;
    duga.SNode = SNode;
	duga.dist = dist;
	Dugi.push_back(duga);
}
//------------------������ ������� ���------------------------------------------------------
void CTreeAnalyse::DugiAnalys()
{
	DugsType::iterator du; 
    
	while (Dugi.size() != 0)
	{
		if (flag == false)
		   du = Dugi.begin();
		else
           du++; 
		DugaAnalys(du);
	}
}
//------------------������ ���� �� ������� ���----------------------------------------
void CTreeAnalyse::DugaAnalys(DugsType::iterator d)
{
	unsigned long f = d->FNode;
    unsigned long s = d->SNode;
    DugsType::iterator j;
	AddNode (d->FNode, d->SNode, d->dist);
	if (flag == true)
		return;
	Dugi.erase(d);
	for (DugsType::iterator i = Dugi.begin(); i != Dugi.end(); i++)
	{
		if (i->SNode == f || i->SNode == s || i->FNode == s)
		{
			AddNode(i->FNode, i->SNode, i->dist);
			j = i;
			i++;
			Dugi.erase(j);
			i--;
		}
 	}
}

//----------------------------������� ���������� ������� � ������----------------------------
void CTreeAnalyse::AddNode (unsigned long& FNode, unsigned long& SNode, unsigned long& dist)
{
	TreeNode newNode, nNode;
	if (FindNode(FNode) == false && FindNode(SNode) == false)
	{
	     if (isRoot == false)
         {
			 newNode.num = FNode;
	         newNode.Father = 0;
             newNode.dist = 0;
	         m_Tree.push_back(newNode);
		
	    	 nNode.num = SNode;
	         nNode.Father = FNode;
             nNode.dist = dist;
	         m_Tree.push_back(nNode);
    		 isRoot = true;
    		 return;
		 }
		 else 
		 {
			 flag = true;
			 return;
		 }

	}
	if (FindNode(FNode) == false)
	{
		newNode.num = FNode;
	    newNode.Father = SNode;
	}
	else
	{
		newNode.num = SNode;
	    newNode.Father = FNode;
	}
	
	newNode.dist = dist;
	m_Tree.push_back(newNode);
	flag = false; 
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
	int d = 0;
	NodesMass::iterator n = FindNode2(num);
	while (n->Father != 0)
	{ 
		n = FindNode2(n->Father);
		d++;
	}
	return d;
}

//-----------------���������� ����������� ���� ��� 2-� ������------------------------
unsigned long CTreeAnalyse::FindWay(unsigned long v1, unsigned long v2)
{
	unsigned long way = 0; // ����� ����������� ����
	int d1 = 0, d2 = 0; // �������� ������ ��� ������
	NodesMass::iterator i1, i2;
	if (m_Tree.size() == 0)
		return 0;
	d1 = Depth(v1);
	d2 = Depth(v2);
	while (d1 > d2)
	{
		i1 = FindNode2(v1);
		way += i1->dist;
		v1 = i1->Father;
		d1--;
	}
    while (d1 < d2)
	{
		i2 = FindNode2(v2);
		way += i2->dist;
		v2 = i2->Father;
		d2--;
	}
	while (v1 != v2)
	{
		i1 = FindNode2(v1);
		way += i1->dist;
        v1 = i1->Father;
		i2 = FindNode2(v2);
        way += i2->dist;
        v2 = i2->Father;
	}
    return way;
}
//-----------------------------����� �� �����---------------------------------------
void CTreeAnalyse::Out()
{
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
// -----------------------------------����� ������� � �������-------------------------------	
bool CTreeAnalyse::FindNode(unsigned long num)
{
	for(NodesMass::iterator i = m_Tree.begin(); i != m_Tree.end(); i++)
	{
		if (i->num == num)
			return true;
	}
return false;
}
// -----------------------------------����� ������� � �������2------------------------------	
NodesMass::iterator CTreeAnalyse::FindNode2(unsigned long num)
{
	NodesMass::iterator i;
	for( i = m_Tree.begin(); i != m_Tree.end(); i++)
	{
		if (i->num == num)
			return i;
	}
return i;
}

	
