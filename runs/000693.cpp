#include <iostream> 
#include <algorithm>
#include <cstring>

using namespace std;

//считаем дерево с установкой уровня глубины вложенности, верхней точки и расстояния до верхней точки для каждой точки дерева
void dfs (int curV, unsigned int *edges, unsigned int *vUp, unsigned int *levels, unsigned int *path, int nVerts, unsigned int prevV = 0, int level = 0) {
    //Если от текущей точки к последней в кеше берем это значение
    int otherV = 0;
    for (int k = 0; k < nVerts - 1; k++) {
        if (edges[k*3] == curV) {
            otherV = edges[k*3 + 1];
        } else if (edges[k*3 + 1] == curV) {
            otherV = edges[k*3];
        } else {
            continue;
        }

        //если есть другая точка
        if (otherV != prevV) {
            levels[otherV] = level + 1;
            vUp[otherV] = curV;
            path[otherV] = edges[k*3 + 2];
            dfs(otherV, edges, vUp, levels, path, nVerts, curV, level + 1);
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
    unsigned int *edges = new unsigned int[3*(nVerts-1)];
    memset(edges, 0, sizeof(unsigned int)*3*(nVerts-1));
    int i = 0;
    for (i = 0; i < nVerts - 1; i++) {
        cin >> edges[i*3];
        cin >> edges[i*3 + 1];
        cin >> edges[i*3 + 2];
    }
    
    dfs(1, edges, vUp, levels, path, nVerts);

    int nDist = 0, v1 = 0, v2 = 0, pathV = 0;
    
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
    
    delete[] edges;
    delete[] levels;
    delete[] vUp;
    delete[] path;
    return 0;
}
