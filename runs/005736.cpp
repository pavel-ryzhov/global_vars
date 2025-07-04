// TreeS.cpp: ����� ����������� ���������� � ������
//

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

typedef struct v { //�������
	vector<pair<int, int> > vert; //���� (����� �������, ���������� �� �� �� �������)	
} vertex;


/* findWay: ����� ����������� ���� */
int findWay (vertex *vSet, int from, int to, int way, int parent)
{
	int tmp;
	int i;
	
	if (from == to) //���� ����� �� �������.
		return way;	
	 
	for (i = 0; i < vSet[from].vert.size(); i++) {
		if (vSet[from].vert[i].first != parent) {
			tmp = findWay (vSet, vSet[from].vert[i].first, to, way + vSet[from].vert[i].second, from);
			
			if (tmp)			
				return tmp;
		}
	}

	return 0;
}

int main()
{
	int m;
	int way;  //���� �� �������
	int NumVert; //���������� ������	
	vertex *vSet; //������ ������
	int nVert; //����� �����
	int i, j, S;
	pair<int, int> tmp;

	
	int to, from; //������

	cin >> NumVert;	

	vSet = (vertex*)calloc(sizeof(vertex), NumVert+1);

	for (i = 0; i < NumVert-1; i++) {
		cin>>j>>nVert>>S;
		tmp = make_pair(nVert, S);
		vSet[j].vert.push_back(tmp);		
		tmp = make_pair(j, S); //������(��������) ����� ����� ���������
		vSet[nVert].vert.push_back(tmp);
	}

	cin>>m;
	
	while (m)
	{		
		cin>>from>>to;
		way = findWay(vSet, from, to, 0, 0);
		cout<<way<<endl;
		m--;
	}

	free(vSet);	
//	getchar();
	return 0;

}

