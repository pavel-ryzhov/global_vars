// TreeS.cpp: ����� ����������� ���������� � ������

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
//#include <fstream>


using namespace std;


//ifstream in;

typedef struct v { //�������
	vector<pair<int, int> > vert; //���� (����� �������, ���������� �� �� �� �������)	
	pair<int, int> *vert_arr;
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
	int tmp_rank, tmp_parent, tmp_stacki;


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
		tmp_parent = vSet[stack[i]].parent;
		tmp_rank = vSet[stack[i]].rank;
		tmp_stacki = stack[i];
		for (k = 0; k < vSet[tmp_stacki].vert.size(); k++){
			tmp = vSet[tmp_stacki].vert_arr[k].first;
			if (tmp != tmp_parent) {
				vSet[tmp].rank = tmp_rank + vSet[tmp_stacki].vert_arr[k].second; //��������� ���������� �� ����� �� ���� �������
				vSet[tmp].parent = tmp_stacki;
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
	//m = 5000;
	cin >> m;
	
	for (i = 0; i < NumVert+1; i++)
	{
		vSet[i].vert_arr = (pair<int, int> *) calloc(vSet[i].vert.size(), sizeof(pair<int, int>));
		for (j = 0; j < vSet[i].vert.size(); j++)
			vSet[i].vert_arr[j] = vSet[i].vert[j];
	}

	while (m)
	{	
		cin>>from>>to;
		way = findWay(vSet, from, to, 0, 0);
		m--;
		cout << way << endl;
	}
	free(vSet);	
	return 0;

}

