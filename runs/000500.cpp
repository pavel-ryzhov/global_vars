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
//#include <time.h>
using namespace std;
struct Duga
{
	unsigned long FNode;
	unsigned long SNode;
    unsigned long dist;
};
typedef list <Duga> DugsType; // массив дуг
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
const int INSIZE = 100; // максимальное число символов в названии входного файла 
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
	DugsType Dugi; // массив дуг, считанных из входного файла
	bool isRoot; // уже есть корень
	bool flag; 

public:
	CTreeAnalyse() {m_NodesCol = 0; m_ResCol = 0; isRoot = false; flag = false;}
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
	void FileReadStream(); // чтение из потока
	bool FindNode(unsigned long num); // поиск вершины в массиве
	NodesMass::iterator FindNode2(unsigned long num);
	void AddToDugi(unsigned long& FNode, unsigned long& SNode, unsigned long& dist); // добавление 
	//в массив дуг 
    void DugiAnalys(); // анализ массива дуг
	void DugaAnalys(DugsType::iterator d); // анализ отдельной дуги
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
//---------------------------функция чтения из потока----------------------------------
void CTreeAnalyse::FileReadStream()
{
	int strcol = 0;
	char symb = ' '; // текущиц символ
	int i = 0;
	string StrFromFile; // считываемая строка
    symb = getchar();
	while (symb != '\n')
	{
		StrFromFile += symb;
		symb = getchar();
	}
	strcol = atoi(StrFromFile.c_str());
    m_InStrs.push_back(StrFromFile); // заносим в массив прочитанную из файла строку 
    StrFromFile = "";
	for (i = 1; i < strcol; i++)
	{
		symb = getchar();
		while (symb != '\n')
		{
			StrFromFile += symb;
			symb = getchar();
		}
        m_InStrs.push_back(StrFromFile); // заносим в массив прочитанную из файла строку 
        StrFromFile = "";
	}
    symb = getchar();
	while (symb != '\n')
	{
	    StrFromFile += symb;
		symb = getchar();
	}
	strcol = atoi(StrFromFile.c_str());
    m_InStrs.push_back(StrFromFile); // заносим в массив прочитанную из файла строку 
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
        m_InStrs.push_back(StrFromFile); // заносим в массив прочитанную из файла строку 
		StrFromFile = "";
	}
}

//-------------------------------функция чтения информации из входного файла--------------------------
void CTreeAnalyse::FileRead()
{
    char inFileName[INSIZE]; // название входного файла
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
	DugiAnalys();
}
//----------------------функция анализа строки (вершина-вершина-расстояние) - извлечение данных----
void CTreeAnalyse::Str1Analyse(string& CurrStr)
{
	unsigned long FirstNode = 0, SecNode = 0, dist = 0; // первая вершина, вторая вершина (ее потомок)
    // и расстояние между ними
	string Curr;
	unsigned int k = 0; // коэффициент символа в текущей строке
	unsigned int num = 0; // номер отделяемого из строки числа
	for(k = 0; k < CurrStr.length(); k ++) // цикл по строке
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
	AddToDugi (FirstNode, SecNode, dist); // добавляем новую вершину в дерево
}
//-----------------добавление в масссив дуг-------------------------------------------------
void CTreeAnalyse::AddToDugi(unsigned long& FNode, unsigned long& SNode, unsigned long& dist)
{
	Duga duga;
	duga.FNode = FNode;
    duga.SNode = SNode;
	duga.dist = dist;
	Dugi.push_back(duga);
}
//------------------анализ массива дуг------------------------------------------------------
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
//------------------анализ дуги из массива дуг----------------------------------------
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

//----------------------------функция добавления вершины в дерево----------------------------
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
	int d = 0;
	NodesMass::iterator n = FindNode2(num);
	while (n->Father != 0)
	{ 
		n = FindNode2(n->Father);
		d++;
	}
	return d;
}

//-----------------нахождение кратчайшего пути для 2-х вершин------------------------
unsigned long CTreeAnalyse::FindWay(unsigned long v1, unsigned long v2)
{
	unsigned long way = 0; // длина кратчайшего пути
	int d1 = 0, d2 = 0; // значение глубин для вершин
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
//-----------------------------вывод на экран---------------------------------------
void CTreeAnalyse::Out()
{
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
// -----------------------------------поиск вершины в массиве-------------------------------	
bool CTreeAnalyse::FindNode(unsigned long num)
{
	for(NodesMass::iterator i = m_Tree.begin(); i != m_Tree.end(); i++)
	{
		if (i->num == num)
			return true;
	}
return false;
}
// -----------------------------------поиск вершины в массиве2------------------------------	
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

	
