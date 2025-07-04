// TreeS.cpp: Поиск кратчайшего расстояния в дереве
//

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

typedef struct v { //вершина
	pair<int, int> *vert; //рёбра (номер вершины, расстояние до неё от текущей)	
	int size;
	int parent; //предок, из которого пришли в эту вершину
	int rank; //путь от корня до этой вершины.
} vertex;

/* findWay_req: поиск кратчайшего пути. Рекурсия*/
/*int findWay_req (vertex *vSet, int from, int to, int way, int parent)
{
	int tmp;
	int i;
		
	if (from == to) //если дошли до вершины.
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
}*/
/* findWay: поиск кратчайшего пути */
int findWay (vertex *vSet, int from, int to, int way, int parent)
{

	int i, j, k;
	//vector<int> stack; //стэк для вершин
	int stack[40000];
	int size = -1;

	if (from == to)
		return 0;
	
	int tmp;
	int tmp_rank, tmp_parent, tmp_stacki;


	for (k = 0; k < vSet[from].size; k++) {
		tmp = vSet[from].vert[k].first;
		vSet[tmp].rank = vSet[from].vert[k].second; //расстояние от корня до добавленной в стэк вершины
		vSet[tmp].parent = from;
		size++;
		stack[size] = vSet[from].vert[k].first;
		if (to == vSet[from].vert[k].first) //если она искомая
			return vSet[from].vert[k].second;
	}
	
	for (i = 0; i < size+1; i++) {
		tmp_parent = vSet[stack[i]].parent;
		tmp_rank = vSet[stack[i]].rank;
		tmp_stacki = stack[i];
		for (k = 0; k < vSet[tmp_stacki].size; k++){
			tmp = vSet[tmp_stacki].vert[k].first;
			if (tmp != tmp_parent) {
				vSet[tmp].rank = tmp_rank + vSet[tmp_stacki].vert[k].second; //добавляем расстояние от корня до этой вершины
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
	int way;  //путь до вершины
	int NumVert; //количество вершин	
	vertex *vSet; //массив вершин
	int nVert; //номер ребра
	int i, j, S;
	pair<int, int> tmp;
	int m; //запросы]
	
	int to, from; //запрос

		
	//in.open("data.dat");	
	cin >> NumVert;

	vSet = (vertex*)calloc(sizeof(vertex), NumVert+1);
	
	for (i = 0; i < NumVert-1; i++ )
		vSet[i].size = -1;

	for (i = 0; i < NumVert-1; i++) {
		cin >> j >> nVert >> S;
		tmp = make_pair(nVert, S);
		vSet[j].size++;
		vSet[j].vert = (pair<int, int> *) realloc(vSet[j].vert, sizeof(pair<int, int>) * (vSet[j].size + 1));
		vSet[j].vert[vSet[j].size] = tmp;
		tmp = make_pair(j, S); //вторая(обратная) связь между вершинами
		vSet[nVert].size++;
		vSet[nVert].vert =(pair<int, int> *)realloc(vSet[nVert].vert, sizeof(pair<int, int>) * (vSet[nVert].size + 1));
		vSet[nVert].vert[vSet[nVert].size]= tmp;
	}
	//m = 5000;
	cin >> m;
	//vSetGLOBAL = vSet;
	while (m)
	{	
		cin>>from>>to;
		way = findWay(vSet, from, to, 0, 0);
		m--;
		cout<<way<<endl;
	}	
	for (i = 0; i < NumVert - 1; i++)
		free(vSet[i].vert);
	free(vSet);	
	return 0;

}

