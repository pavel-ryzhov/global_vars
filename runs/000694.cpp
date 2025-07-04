#include <iostream> 
#include <algorithm>
#include <cstring>
#include <vector>
#include <utility>

using namespace std;

//считаем дерево с установкой уровня глубины вложенности, верхней точки и расстояния до верхней точки для каждой точки дерева
void make_tree(int curV, const vector <vector< pair <int, int> > > & edges, unsigned int *vUp, unsigned int *levels, unsigned int *path, int nVerts, unsigned int prevV = 0, int level = 0) {
    //Если от текущей точки к последней в кеше берем это значение
    int size = edges[curV].size();
    for (int i = 0; i < size ; i++) {
        //если есть другая точка
        if (edges[curV][i].first != prevV) {
            levels[edges[curV][i].first] = level + 1;
            vUp[edges[curV][i].first] = curV;
            path[edges[curV][i].first] = edges[curV][i].second;
            make_tree(edges[curV][i].first, edges, vUp, levels, path, nVerts, curV, level + 1);
        }
    }
}

int main(int argc, char *argv[])
{  
    //Количество вершин
    int nVerts = 0;
    cin >> nVerts;
    
    //Верхняя тока для каждой точки дерева
    unsigned int* vUp = new unsigned int[nVerts + 1];
    memset(vUp, 0, sizeof(unsigned int)*(nVerts + 1));
    
    //Уровень вложенности каждой точки
    unsigned int* levels = new unsigned int[nVerts + 1];
    memset(levels, 0, sizeof(unsigned int)*(nVerts + 1));
    
    //Расстояние до верхней точки
    unsigned int* path = new unsigned int[nVerts + 1];
    memset(path, 0, sizeof(unsigned int)*(nVerts + 1));
    
    //Получаем ребра графа
    vector <vector< pair <int, int> > > edges(nVerts + 1);

    int i = 0, v1 = 0, v2 = 0, vd = 0;
    for (i = 0; i < nVerts - 1; i++) {
        cin >> v1;
        cin >> v2;
        cin >> vd;
        edges[v1].push_back(make_pair(v2, vd));
        edges[v2].push_back(make_pair(v1, vd));
    }
    
    //Создаем дерево
    make_tree(1, edges, vUp, levels, path, nVerts);

    int nDist = 0, pathV = 0;    
    //Количество пар вершин с кратчайшим расстоянием
    cin >> nDist;
    //Идем вверх по дереву
    for (i = 0; i < nDist; i++) {
        cin >> v1;
        cin >> v2;
        pathV = 0;
        if (levels[v1] > levels[v2]) {
            while(levels[v1] != levels[v2]) {
                pathV += path[v1];
                v1 = vUp[v1];
            }
        } else if (levels[v2] > levels[v1]) {
            while(levels[v1] != levels[v2]) {
                pathV += path[v2];
                v2 = vUp[v2];
            }
        }
        while(v1 != v2) {
            pathV += path[v1];
            pathV += path[v2];
            v1 = vUp[v1];
            v2 = vUp[v2];
        }
        cout << pathV << endl;
    }
    
    delete[] levels;
    delete[] vUp;
    delete[] path;
    return 0;
}
