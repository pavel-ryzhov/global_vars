/**
    \file
    \brief  Поиск кратчайшего пути между вершинами дерева
    \author Малина Анна
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
    unsigned long SNode;// <номер 1-й вершины, номер 2-й вершины>, 
//между которыми необходимо вычислить длину кратчайшего пути
};
typedef vector <Pair> NumsMass;
typedef list <string> StringMass; // массив строк
typedef vector <unsigned long> NumMass; // массив чисел (длины кратчайших путей между вершинами)
struct TreeNode; 
typedef vector <TreeNode> NodesMass; // массив вершин 
const char* p_EXPR1 = "Enter your inputfile name\n";
const char* p_EXPR2 = "File opening error!\n";
const char* p_EXPR3 = "To stop executing program enter: end \n ";
const char* p_EXPR4 = "Result:\n";
const int INFILENAMESIZE = 100; // максимальное число символов в названии входного файла 
//----------------------------------------------------------
struct TreeNode // вершина дерева
{
	unsigned long num; // номер вершины;
	unsigned long dist; // расстояние до предка
	unsigned long Father; 	
};
//-----------------------------------------------------------
class CTreeAnalyse
{
private:
	unsigned long m_NodesCol; // количество вершиин в дереве    	
    unsigned long m_ResCol; // количество вершин, для которых нужно найти длину кратчайшего пути
	NumsMass m_ResNodes; // вершины, между которыми необходимо вычислить длину кратчайшего пути
	StringMass m_InStrs;// массив строк из входного файла
	NodesMass m_Tree; // дерево
	NumMass m_Ways; // длины кратчайших путей между вершинами

public:
	CTreeAnalyse() {m_NodesCol = 0; m_ResCol = 0;}
	~CTreeAnalyse(){}
	void FileRead (); //функция чтения информации из входного файла
    void TreeCreating(); // функция обработки строк из текущего файла(создание дерева)
    void Str1Analyse(string& CurrStr); // функция анализа строки (вершина-вершина-расстояние)
	void Str2Analyse(string& CurrStr); // функция анализа строки (вершины для нахождения пути)
	void AddNode (unsigned long& FNode, unsigned long& SNode, unsigned long& dist); // добавление
	// вершины
    void ShortestWay(); // нахождение кратчайших 
	// путей между вершинами
	unsigned long Depth(unsigned long& num); // определение глубины вершины 
	unsigned long FindWay(unsigned long v1, unsigned long v2); // нахождение кратчайшего пути 
	// между двумя вершинами
	void Out(); // вывод на экран
	void OutToFile(); //вывод в файл 

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

//-------------------------------функция чтения информации из входного файла--------------------------
void CTreeAnalyse::FileRead()
{
    char inFileName[INFILENAMESIZE]; // название входного файла
	char symb = '!'; // текущиц символ
	string StrFromFile; // считываемая из файла строка
	FILE * inFile; // указатель на входной файл
	printf(p_EXPR1);
	scanf("%s",inFileName);
	if ((string)inFileName == "end")
		exit(1);
	inFile = fopen (inFileName, "r"); // открываем входной файл
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
			m_InStrs.push_back(StrFromFile); // заносим в массив прочитанную из файла строку 
            StrFromFile = "";
		}
		fclose(inFile);
	}
}
//---------------------функция обработки строк из текущего файла(создание дерева)-----------------------
void CTreeAnalyse::TreeCreating( )
{
  
	m_NodesCol = atoi (m_InStrs.begin()->c_str());
	// добавим корень!!!:
   	TreeNode Root;
    Root.num = 1;
	Root.Father = 0;
	Root.dist = 0;
	m_Tree.push_back(Root);
	unsigned int j = 1; // счетчик вершин
    StringMass::iterator i;
	for (i = ++m_InStrs.begin(); i !=m_InStrs.end() && j < m_NodesCol; i++)
	{ 
		Str1Analyse(*i); // анализ текущей строки
		j++;
	}
	// добавляем информацию о вершинах, между которыми нужно найти кратчайший путь
	m_ResCol = atoi (i->c_str());
	i++;
	j = 0;
	for (; i != m_InStrs.end() && j < m_ResCol; i ++ )
	{
		Str2Analyse(*i);
		j++;
	}
}
//----------------------функция анализа строки (вершина-вершина-расстояние) - извлечение данных----
void CTreeAnalyse::Str1Analyse(string& CurrStr)
{
	unsigned long FirstNode = 0, SecNode = 0, dist = 0; // первая вершина, вторая вершина (ее потомок)
    // и расстояние между ними
	string Curr;
	unsigned int k = 0; // коэффициент символа в текущей строке
	unsigned int num = 0; // номер отделяемого из строки числа
	while( k < CurrStr.length()) // цикл по строке
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
	AddNode (FirstNode, SecNode, dist); // добавляем новую вершину в дерево
}
//----------------------------функция добавления вершины в дерево----------------------------
void CTreeAnalyse::AddNode (unsigned long& FNode, unsigned long& SNode, unsigned long& dist)
{
	TreeNode newNode;
	newNode.num = SNode;
	newNode.Father = FNode;
	newNode.dist = dist;
	m_Tree.push_back(newNode);
}
//--------------------------функция анализа строки (вершины, между которыми необходимо-------- 
//--------------------------найти кратчайший путь)---------------------------------------------
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
//-------------------нахождение кратчайшего пути---------------------------------------------
void CTreeAnalyse::ShortestWay()
{
	unsigned long way = 0; // длина кратчайшего пути
	// цикл по массиву вершин, для которых необходимо вычислить длину кратчайшего пути
	for (NumsMass::iterator i = m_ResNodes.begin(); i != m_ResNodes.end(); i++)
	{
		way = FindWay (i->FNode, i->SNode);
        m_Ways.push_back(way);
	}
}
//------------------нахождение глубины вершины----------------------------------------------
unsigned long CTreeAnalyse::Depth(unsigned long& num) 
{
	int j = num;
	int d = 0; // глубина
	while (m_Tree[j - 1].Father != 0)
	{ 
		j = m_Tree[j - 1].Father;
		d++;
	}
	return d;
}

//-----------------нахождение кратчайшего пути для 2-х вершин------------------------
unsigned long CTreeAnalyse::FindWay(unsigned long v1, unsigned long v2)
{
	unsigned long way = 0; // длина кратчайшего пути
	int d1 = 0, d2 = 0; // значение глубин для вершин
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
//-----------------------------вывод на экран---------------------------------------
void CTreeAnalyse::Out()
{
	printf(p_EXPR4); 
	for (NumMass::iterator i = m_Ways.begin(); i != m_Ways.end(); i++)
		printf ("%u \n",*i);
}
//----------------------------вывод в файл------------------------------------------
void CTreeAnalyse::OutToFile()
{
	FILE* out;
	out = fopen("out", "w");
	for (NumMass::iterator i = m_Ways.begin(); i != m_Ways.end(); i++)
		fprintf (out, "%u\n",*i);
	fclose(out);
}
