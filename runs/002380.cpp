#include <iostream>
using namespace std;

class Node //класс для вершин
{
private:
	public:
	Node *MasterNode; //предок
	unsigned int LengthToMaster;//расстояние до предка
	unsigned int Height;//высота верины в дереве
	unsigned int Index;//номер вершины

	Node()
	{
		MasterNode=0;
		LengthToMaster=0;
		Height=0;
		Index=0;
	}
	~Node(){}
};

unsigned int NodesCount;//количество вершин
unsigned int PairsCount;//количество пар для нахождения расстояний
bool First1=false;//Является ли номер первой вершины единицей

void ParsePairs(Node *NodeArr, unsigned int **Pairs)//вычисление расстояния между вершинами
{	
	unsigned int FirstN, SecN;//номера сравниваемых вершин
	unsigned long int Length;//результат
	for(unsigned int i=0;i<PairsCount;i++)
	{
		Length=0;
		FirstN=Pairs[i][0];
		SecN=Pairs[i][1];
		if(FirstN==SecN){cout<<0<<endl;continue;}//тривиальный случай совпадения вершин
		if(First1){FirstN--;SecN--;}//в массиве нумерация с нуля
		for(;NodeArr[FirstN].Height!=NodeArr[SecN].Height;)//поднимаемся от вершины с бОльшей высотой до тех пор пока высоты не сравняются
		{
			if(NodeArr[FirstN].Height>NodeArr[SecN].Height)
			{
				Length+=NodeArr[FirstN].LengthToMaster;
				FirstN=NodeArr[FirstN].MasterNode->Index;
			}
			else
			{
				Length+=NodeArr[SecN].LengthToMaster;
				SecN=NodeArr[SecN].MasterNode->Index;
			}
		}
			for(;FirstN!=SecN;)//поднимаемся от каждой вершины пока результирующие вершины не станут равными
			{
				Length+=NodeArr[FirstN].LengthToMaster;
				FirstN=NodeArr[FirstN].MasterNode->Index;
				Length+=NodeArr[SecN].LengthToMaster;
				SecN=NodeArr[SecN].MasterNode->Index;
			}
			cout<<Length<<endl;//вывод расстояния

	}
}
void ParseNodeNew(Node *NodeArr)//Обработка строки, добавление вершины в массив
{
	int MasterN, NewN, Length;
	for(unsigned int i=0;i<NodesCount-1;i++)
	{
		cin>>MasterN>>NewN>>Length;
		if(i==0 && MasterN==1)First1=true;
		if(First1){MasterN--;NewN--;}
		NodeArr[NewN].Index=NewN;
		NodeArr[NewN].LengthToMaster=Length;
		NodeArr[NewN].MasterNode=&NodeArr[MasterN];
		NodeArr[NewN].Height=NodeArr[MasterN].Height+1;
	}
}
int main()
{	
	cin>>NodesCount;//ввод количества вершин
	Node *NodeArr=new Node[NodesCount];
	NodeArr[0].LengthToMaster=0;//Описание корня
	NodeArr[0].MasterNode=0;
	NodeArr[0].Height=0; 
	NodeArr[0].Index=0;
	ParseNodeNew(NodeArr);//ввод вершин

	cin>>PairsCount;//ввод количества пар
	unsigned int **Pairs=new unsigned int*[PairsCount];  
	for(unsigned int i=0;i<PairsCount;i++)Pairs[i]=new unsigned int[2];
	for(unsigned int i=0;i<PairsCount;i++)cin>>Pairs[i][0]>>Pairs[i][1];//ввод пар
	ParsePairs(NodeArr, Pairs);//вычисление расстояний в парах
	return 0;
}