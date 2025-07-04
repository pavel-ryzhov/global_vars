#include <iostream> 
#include <algorithm>
#include <cstring>

using namespace std;

//Устанавливаем кеш от теущего к первому на все значения
void setCache(unsigned int *edges, long* cache, unsigned int *prevVerts, int prevCount, int nVerts) {
    int path = 0;
    for (int i = prevCount; i > 0; i --) {
        if (cache[prevVerts[i]*(nVerts + 1) + prevVerts[i-1]] != -1) {
            path += cache[prevVerts[i]*(nVerts + 1) + prevVerts[i-1]];
        } else if (cache[prevVerts[i-1]*(nVerts + 1) + prevVerts[i]] != -1) {
            path += cache[prevVerts[i-1]*(nVerts + 1) + prevVerts[i]];
        }
        cache[prevVerts[i-1]*(nVerts + 1) + prevVerts[prevCount]] = path;
    }
}

//считаем поиском в глубину с установкой кеша
int dfs (int curV, int v2, unsigned int *edges, long* min, long* cache, unsigned int *prevVerts, int prevCount, int nVerts) {
    if (curV == v2) {
        return 1;
    }
    //Если от текущей точки к последней в кеше берем это значение
    if (cache[curV*(nVerts + 1) + v2] != -1) {
        min[v2] = min[curV] + cache[curV*(nVerts + 1) + v2];
        return 1;
    } else if (cache[v2*(nVerts + 1) + curV] != -1) {
        min[v2] = min[curV] + cache[v2*(nVerts + 1) + curV];
        return 1;
    }
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
        if (min[otherV] == -1) {
            min[otherV] = min[curV] + edges[k*3 + 2];
            cache[curV*(nVerts + 1) + otherV] = edges[k*3 + 2];
            prevVerts[prevCount] = otherV;
            setCache(edges, cache, prevVerts, prevCount, nVerts);
            if (dfs(otherV, v2, edges, min, cache, prevVerts, prevCount + 1, nVerts)) {
                return 1;
            }
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{  
    //Количество вершин
    int nVerts = 0;
    cin >> nVerts;
    
    //Получаем ребра графа
    unsigned int *edges = new unsigned int[3*(nVerts-1)];
    memset(edges, 0, sizeof(unsigned int)*3*(nVerts-1));
    int i = 0;
    for (i = 0; i < nVerts - 1; i++) {
        cin >> edges[i*3];
        cin >> edges[i*3 + 1];
        cin >> edges[i*3 + 2];
    }
    
    unsigned int *prevVerts = new unsigned int[nVerts];
    memset(prevVerts, 0, sizeof(unsigned int)*nVerts);
    
    long* min = new long[nVerts + 1];
    
    long* cache = new long[(nVerts + 1)*(nVerts + 1)];
    memset(cache, -1, sizeof(long)*(nVerts + 1)*(nVerts + 1));
    
    int nDist = 0, j = 0, k = 0, v1 = 0, v2 = 0, curV = 0, otherV = 0, nextV = 0;
    //Количество пар вершин с кратчайшим расстоянием
    cin >> nDist;
    
    long* distance = new long[nDist];
    memset(distance, 0, sizeof(long)*nDist);
    
    for (i = 0; i < nDist; i++) {
        cin >> v1;
        cin >> v2;
        memset(min, -1, sizeof(long)*(nVerts + 1));
        min[v1] = 0;
        prevVerts[0] = v1;
        dfs(v1, v2, edges, min, cache, prevVerts, 1, nVerts);
        distance[i] = min[v2];
    }
    
    for (i = 0; i < nDist; i++) {
        cout << distance[i] << endl;
    }
    
    delete[] edges;
    delete[] min;
    delete[] prevVerts;
    delete[] distance;
    delete[] cache;
    return 0;
}
