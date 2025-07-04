// TreeS.cpp: Поиск кратчайшего расстояния в дереве
//

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

typedef struct v { //вершина
	vector<pair<int, int> > vert; //рёбра (номер вершины, расстояние до неё от текущей)	
} vertex;


/* findWay: поиск кратчайшего пути */
int findWay (vertex *vSet, int from, int to, int way, int parent)
{
	int tmp;
	int i;
	
	if (from == to) //если дошли до вершины.
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
	int way;  //путь до вершины
	int NumVert; //количество вершин	
	vertex *vSet; //массив вершин
	int nVert; //номер ребра
	int i, j, S;
	pair<int, int> tmp;

	
	int to, from; //запрос

	cin >> NumVert;	

	vSet = (vertex*)calloc(sizeof(vertex), NumVert+1);

	for (i = 0; i < NumVert-1; i++) {
		cin>>j>>nVert>>S;
		tmp = make_pair(nVert, S);
		vSet[j].vert.push_back(tmp);		
		tmp = make_pair(j, S); //вторая(обратная) связь между вершинами
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

