#include <iostream>
#include <algorithm>
#include <map>
#include <fstream>
#include <vector>
#include <list>
#include <stdio.h>
#include <string.h>

typedef unsigned int uint;

//������� ������ ���������
struct half_rib;
//�������
struct vertex;
/*��������� ������ ���������. �������� ������� ������ (������ �������)
������������� ���� �� �������� ��������� � ����� �������� � ��� (rib)*/
typedef std::vector<std::list<half_rib> > connectionContainer;
//��������� ��� ������. ������� - ������ ������
typedef std::vector<vertex>				 vertexContainer;
//������� ������ ���������
void setConnectionInfo(connectionContainer& connectionList, std::istream& input, uint N);
/*
�� ������ ��������� ��������� ������
� ������� � ������ ������� ������ ���� ��������,
� ��� ������ ������� ������������� �� ����������� "������"
*/
void setVertexInfo(connectionContainer& connectionList, vertexContainer& vertArr, uint i = 0);
//����������� ��� ������� �� ����� ������
uint getEven(vertexContainer& vertArr, uint& from, uint& to);
//������� ��� ������� �� �������
uint climbUp(vertexContainer& vertArr, uint& from, uint& to);

/*
	�������� ��������� (� ����������� ��������� ���������) ����������� �� ������ ������� 
	�� ������ �����������, ����� ��� ��������������� ����������� ����� �� ��� ���, 
	���� �� "����������" � ����� �������.
*/


const uint maxLineLen = 20;
//�������� ������, ������������ �-������� ��� ��������� ��������������
void getRib(uint& id1, uint& id2, uint& cost, std::istream& input);
void getVertPair(uint& one, uint& two, std::istream& input);
void getInt(uint& i, std::istream& input);

struct vertex
{
	int parentId;			//����� ��������
	uint parentTravelCost;	//���� ����������� �� ��������
	uint level;				//�������
	vertex()
	{
		parentId = -1;
	}
};
int main()
{
	uint N = 0;
	std::istream& input(std::cin);
	//������� ���������� ������
	::getInt(N,input);
	vertexContainer vertArr(N);
	//������������ ������. 
	{//����� ���� ��� ������ ����� ������������, ����������� ������ ������ ���������
		connectionContainer connectionList(N);	
		setConnectionInfo(connectionList,input,N);
		setVertexInfo(connectionList,vertArr);
	}
	
	//������� ���������� ��� ������
	::getInt(N,input);
	uint from = 0;
	uint to = 0;
	while(N--)
	{
		::getVertPair(from,to,input);

		uint sum = 0;
		//�������� ������
		sum += getEven(vertArr,from,to);
		//������� �� ����� �������
		sum += climbUp(vertArr,from,to);
		//������� ���������
		printf("%u\n",sum);
	}
	return 0;
}

struct half_rib
{
	uint id;
	uint cost;
};



uint getEven(vertexContainer& vertArr, uint& from, uint& to)
{
	uint sum = 0;
	//����������, ��� ����; �������� � ���
	uint& lowerOne = (vertArr[from].level < vertArr[to].level) ? to : from;
	while(vertArr[from].level != vertArr[to].level)
	{
			//��������� ��������� ����
			sum += vertArr[lowerOne].parentTravelCost;
			//�������
			lowerOne = vertArr[lowerOne].parentId;
	}
	return sum;
}


uint climbUp(vertexContainer& vertArr, uint& from, uint& to)
{
	uint sum = 0;
	while(from != to)
	{
		//��������� ��������� ���������
		sum += vertArr[from].parentTravelCost;
		sum += vertArr[to].parentTravelCost;
		//������� �����
		from = vertArr[from].parentId;
		to = vertArr[to].parentId;
	}
	return sum;
}

void setConnectionInfo(connectionContainer& connectionList, std::istream& input, uint N)
{
	for(uint i=0; i<N-1; i++)
	{
		//��� ������� ���������� ����� ������� �� �������� � ������ ���������
		//��� ������ �� ���� ������
		half_rib first;
		half_rib second;
		uint cost = 0;
		::getRib(first.id,second.id,cost,input);
		first.cost = second.cost = cost;
		connectionList[first.id].push_back(second);
		connectionList[second.id].push_back(first);
	}
}

void setVertexInfo(connectionContainer& connectionList, vertexContainer& vertArr, uint i)
{	
	if(i==0)
	{
		vertArr[0].parentId = 0;
		vertArr[0].level = 0;
	}
	for(std::list<half_rib>::iterator it = connectionList[i].begin(); it != connectionList[i].end(); it++)
	{
		//��������������� ��������� �� ������ ���������, ..
		if(vertArr[it->id].parentId==-1)					//���� ������ ������� ��� �� ���� ����������
		{
			vertArr[it->id].parentId = i;					//����������� ������������ ��������� � ������
			vertArr[it->id].parentTravelCost = it->cost;	//����������� ��������� ����������� �� ��������
			vertArr[it->id].level = vertArr[i].level+1;		//����������� ������� � ������
			setVertexInfo(connectionList,vertArr,it->id);	//����������� ���� ����� � ������������ ���������
		}
	}
}

void getRib(uint& id1, uint& id2, uint& cost, std::istream& input)
{
	static char buf[maxLineLen];
	input.getline(buf,maxLineLen);
	id1 = atoi(strtok(buf," "));
	id2 = atoi(strtok(NULL," "));
	id1--;
	id2--;
	cost = atoi(strtok(NULL," "));
}

void getVertPair(uint& one, uint& two, std::istream& input)
{
	static char buf[maxLineLen];
	input.getline(buf,maxLineLen);
	one = atoi(strtok(buf," "));
	two = atoi(strtok(NULL," "));
	one--;
	two--;
}

void getInt(uint& i, std::istream& input)
{
	static char buf[maxLineLen];
	input.getline(buf,maxLineLen);
	i = atoi(buf);
}
