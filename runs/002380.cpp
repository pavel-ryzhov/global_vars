#include <iostream>
using namespace std;

class Node //����� ��� ������
{
private:
	public:
	Node *MasterNode; //������
	unsigned int LengthToMaster;//���������� �� ������
	unsigned int Height;//������ ������ � ������
	unsigned int Index;//����� �������

	Node()
	{
		MasterNode=0;
		LengthToMaster=0;
		Height=0;
		Index=0;
	}
	~Node(){}
};

unsigned int NodesCount;//���������� ������
unsigned int PairsCount;//���������� ��� ��� ���������� ����������
bool First1=false;//�������� �� ����� ������ ������� ��������

void ParsePairs(Node *NodeArr, unsigned int **Pairs)//���������� ���������� ����� ���������
{	
	unsigned int FirstN, SecN;//������ ������������ ������
	unsigned long int Length;//���������
	for(unsigned int i=0;i<PairsCount;i++)
	{
		Length=0;
		FirstN=Pairs[i][0];
		SecN=Pairs[i][1];
		if(FirstN==SecN){cout<<0<<endl;continue;}//����������� ������ ���������� ������
		if(First1){FirstN--;SecN--;}//� ������� ��������� � ����
		for(;NodeArr[FirstN].Height!=NodeArr[SecN].Height;)//����������� �� ������� � ������� ������� �� ��� ��� ���� ������ �� ����������
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
			for(;FirstN!=SecN;)//����������� �� ������ ������� ���� �������������� ������� �� ������ �������
			{
				Length+=NodeArr[FirstN].LengthToMaster;
				FirstN=NodeArr[FirstN].MasterNode->Index;
				Length+=NodeArr[SecN].LengthToMaster;
				SecN=NodeArr[SecN].MasterNode->Index;
			}
			cout<<Length<<endl;//����� ����������

	}
}
void ParseNodeNew(Node *NodeArr)//��������� ������, ���������� ������� � ������
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
	cin>>NodesCount;//���� ���������� ������
	Node *NodeArr=new Node[NodesCount];
	NodeArr[0].LengthToMaster=0;//�������� �����
	NodeArr[0].MasterNode=0;
	NodeArr[0].Height=0; 
	NodeArr[0].Index=0;
	ParseNodeNew(NodeArr);//���� ������

	cin>>PairsCount;//���� ���������� ���
	unsigned int **Pairs=new unsigned int*[PairsCount];  
	for(unsigned int i=0;i<PairsCount;i++)Pairs[i]=new unsigned int[2];
	for(unsigned int i=0;i<PairsCount;i++)cin>>Pairs[i][0]>>Pairs[i][1];//���� ���
	ParsePairs(NodeArr, Pairs);//���������� ���������� � �����
	return 0;
}