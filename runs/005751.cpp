// TreeS.cpp: ����� ����������� ���������� � ������
//

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

//ifstream in;
//ofstream out;

typedef struct v { //�������
	vector<pair<int, int> > vert; //���� (����� �������, ���������� �� �� �� �������)	
	int parent; //������, �� �������� ������ � ��� �������
	int rank; //���� �� ����� �� ���� �������.
} vertex;

/* findWay_req: ����� ����������� ����. ��������*/
int findWay_req (vertex *vSet, int from, int to, int way, int parent)
{
	int tmp;
	int i;
		
	if (from == to) //���� ����� �� �������.
		return way;	
	 
	for (i = 0; i < vSet[from].vert.size(); i++) {
		//printf("%d %d \n",vSet[from].vert[i].first, vSet[from].vert[i].second);
		if (vSet[from].vert[i].first != parent) {
			//printf("\n%d",from);
			tmp = findWay_req (vSet, vSet[from].vert[i].first, to, way + vSet[from].vert[i].second, from);
			
			if (tmp)			
				return tmp;
		}
	}

	return 0;
}


/* findWay: ����� ����������� ���� */
int findWay (vertex *vSet, int from, int to, int way, int parent)
{

	int i, j, k;
	//vector<int> stack; //���� ��� ������
	int stack[40000];
	int size = -1;

	if (from == to)
		return 0;
	
	int tmp;

	for (k = 0; k < vSet[from].vert.size(); k++) {
		tmp = vSet[from].vert[k].first;
		vSet[tmp].rank = vSet[from].vert[k].second; //���������� �� ����� �� ����������� � ���� �������
		vSet[tmp].parent = from;
		size++;
		stack[size] = vSet[from].vert[k].first;
		if (to == vSet[from].vert[k].first) //���� ��� �������
			return vSet[from].vert[k].second;
	}
	
	for (i = 0; i < size+1; i++) {
		for (k = 0; k < vSet[stack[i]].vert.size(); k++){
			tmp = vSet[stack[i]].vert[k].first;
			if (tmp != vSet[stack[i]].parent) {
				vSet[tmp].rank = vSet[stack[i]].rank + vSet[stack[i]].vert[k].second; //��������� ���������� �� ����� �� ���� �������
				vSet[tmp].parent = stack[i];
				if (tmp == to)
					return vSet[tmp].rank;
				size++;
				stack[size] = tmp;
				//stack.push_back(vSet[stack[i]].vert[k].first);
			}
		}
	}
	return 0;
}

int main()
{
	long ltime;
	int way;  //���� �� �������
	int NumVert; //���������� ������	
	vertex *vSet; //������ ������
	int nVert; //����� �����
	int i, j, S;
	pair<int, int> tmp;
	int m; //�������
	
	int to, from; //������

	
	//in.open("data.dat");	
	cin >> NumVert;

	vSet = (vertex*)calloc(sizeof(vertex), NumVert+1);

	for (i = 0; i < NumVert-1; i++) {
		cin >> j >> nVert >> S;
		tmp = make_pair(nVert, S);
		vSet[j].vert.push_back(tmp);
		tmp = make_pair(j, S); //������(��������) ����� ����� ���������
		vSet[nVert].vert.push_back(tmp);
	}

	cin >> m;
	while (m)
	{	
		cin>>from>>to;
		way = findWay(vSet, from, to, 0, 0);
		cout<<way<<endl;
		m--;
	}


	free(vSet);	
	return 0;

}

