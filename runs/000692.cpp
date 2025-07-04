#include <iostream> 
#include <algorithm>
#include <cstring>

using namespace std;

void setCache(long* cache, int v1, int v2, int nVerts, long dist) {
    if (v1 < v2) {
        cache[v1*(nVerts + 1) + v2] = dist;
    } else {
        cache[v2*(nVerts + 1) + v1] = dist;
    }
}

long getCache(long* cache, int v1, int v2, int nVerts) {
    if (v1 == v2) {
        return 0;
    } else if (v1 < v2) {
        return cache[v1*(nVerts + 1) + v2];
    } else {
        return cache[v2*(nVerts + 1) + v1];
    }
}

//Устанавливаем кеш от теущего к первому на все значения
void setPathCache(long* cache, unsigned int prevV, unsigned int *prevVerts, int prevCount, int nVerts) {
    int p = getCache(cache, prevVerts[prevCount], prevV, nVerts);
    int path = 0;
    for (int i = prevCount - 1; i >= 0; i --) {
        setCache(cache, prevVerts[prevCount], prevVerts[i], nVerts, p + getCache(cache, prevV, prevVerts[i], nVerts));
    }
}


//считаем поиском в глубину с установкой кеша
int dfs (int curV, unsigned int *edges, long* cache, unsigned int *prevVerts, int prevCount, int nVerts, int prevV = 0) {
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
            setCache(cache, curV, otherV, nVerts, edges[k*3 + 2]);
            prevVerts[prevCount] = otherV;
            setPathCache(cache, curV, prevVerts, prevCount, nVerts);
            prevCount++;
            prevCount = dfs(otherV, edges, cache, prevVerts, prevCount, nVerts, curV);
        }
    }
    return prevCount;
}



int main(int argc, char *argv[])
{  
    //Количество вершин
    int nVerts = 0;
    cin >> nVerts;
    
    //Получаем ребра графа
    long* cache = new long[(nVerts + 1)*(nVerts + 1)];
    memset(cache, -1, sizeof(long)*(nVerts + 1)*(nVerts + 1));
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
    
    prevVerts[0] = 1;
    dfs(1, edges, cache, prevVerts, 1, nVerts);
    
    int nDist = 0, j = 0, k = 0, v1 = 0, v2 = 0, curV = 0, otherV = 0, nextV = 0;
    //Количество пар вершин с кратчайшим расстоянием
    cin >> nDist;
        
    for (i = 0; i < nDist; i++) {
        cin >> v1;
        cin >> v2;
        cout << getCache(cache, v1, v2, nVerts) << endl;
    }
    
    delete[] edges;
    delete[] prevVerts;
    delete[] cache;
    return 0;
}
