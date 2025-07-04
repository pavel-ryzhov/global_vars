#include <iostream> 
#include <utility> 
#include <map> 
#include <vector> 
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
    //Количество вершин
    int nVerts = 0;
    cin >> nVerts;
    
    //Получаем ребра графа
    map <pair<int,int>, int> edges;
    int i = 0, v1 = 0, v2 = 0;
    pair<int, int> vs;
    for (i = 0; i < nVerts - 1; i++) {
        cin >> v1;
        cin >> v2;
        vs = make_pair(v1, v2);
        cin >> edges[vs];
    }
    
    
    int nDist = 0, curV = 0, otherV = 0, nextV = 0;
    map <int, int> min;
    map <pair<int, int>, int>::const_iterator edgesIt;
    map <int, int>::const_iterator minIt;
    vector <int> distance;
    vector <int>::const_iterator distIt;
    
    //Количество пар вершин с кратчайшим расстоянием
    cin >> nDist;
    for (i = 0; i < nDist; i++) {
        cin >> v1;
        cin >> v2;
        
        min[v1] = 0;
        for (curV = v1; curV != v2;) {
            //считаем минимальные расстояния от текущей вершины
            for (edgesIt=edges.begin(); edgesIt != edges.end(); edgesIt++) {
                if ((*edgesIt).first.first == curV) {
                    otherV = (*edgesIt).first.second;
                } else if ((*edgesIt).first.second == curV) {
                    otherV = (*edgesIt).first.first;
                } else {
                    continue;
                }
                if (min.count(otherV) == 0 || min[otherV] > min[curV] + (*edgesIt).second) {
                    min[otherV] = min[curV] + (*edgesIt).second;
                }
            }
            
            //вычисляем вершину с минимальным (но большим, чем до текущей) расстоянием до нее 
            nextV = -1;
            for (minIt = min.begin(); minIt != min.end(); minIt++) {
                if ((*minIt).second > min[curV] && (nextV == -1 || min[nextV] > (*minIt).second)) {
                    nextV = (*minIt).first;
                }
            }
            //это никогда не должно сработать
            if (nextV == -1) {
                curV = v2;
            } else {
                curV = nextV;
            }
        }
        distance.push_back(min[curV]);
        min.clear();
    }
    //Выводим значения   
    for(distIt = distance.begin(); distIt != distance.end(); distIt ++) {
        cout << (*distIt) << endl;
    }
    
    return 0;
}
