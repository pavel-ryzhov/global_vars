#include <iostream>
#include <vector>
using namespace std;

// Граф хранится в одномерном массиве:
// Индекс в массиве соответствует номеру вершины (с поправкой на то, что индексация в массиве начинается с 0);
// lvl - "уровень" вершины, характеризует удаленность данной вершины от корня (у корня это поле равно 0);
// prev - ближайший предок;
// length - вес ребра (prev, "текущая вершина");
// vert - нужно для первоначального заполнения, ибо сразу проставить значения предыдущих полей нельзя
struct vertex {
    unsigned short lvl, prev, length;
    
    struct edge {
        unsigned short vert, length;
        
        edge(unsigned short ver, unsigned short l) : vert(ver), length(l) {}
    };
    vector<edge> vert;
}* arr;

// Количество вершин
unsigned short N;

// Функция для проставления полей lvl, prev, length (проставляет их для "ветки", начиная с указанной вершины;
// по-сути является обходом в глубину)
void createNormalBranch (unsigned short v) {
    for(vector<vertex::edge>::iterator i = arr[v-1].vert.begin(); i != arr[v-1].vert.end(); i++) {
        if(arr[i->vert - 1].lvl == 0) {
            arr[i->vert - 1].prev = v;
            arr[i->vert - 1].lvl = arr[v-1].lvl + 1;
            arr[i->vert - 1].length = i->length;
            createNormalBranch(i->vert);
        }
    }
}

// Поиск пути от вершины a до вершины b
unsigned long long searchWay (unsigned short a, unsigned short b) {
    if(a == b) return 0;
    unsigned long long result = 0;
    
    // Переменные a и b будут использоваться как указатели на вершины;
    // для начала сделаем так, что бы вершины a и b были на одинаковом удалении от корня (на одном уровне),
    // для этого будем двигаться в сторону корня от наиболее удаленной вершины, не забывая подсчитывать пройденное
    // расстояние:
    
    if(arr[a-1].lvl > arr[b-1].lvl) {
        do {
            result += arr[a-1].length;
            a = arr[a-1].prev;
        } while (arr[a-1].lvl != arr[b-1].lvl);
    } else if(arr[a-1].lvl < arr[b-1].lvl) {
        do {
            result += arr[b-1].length;
            b = arr[b-1].prev;
        } while (arr[b-1].lvl != arr[a-1].lvl);
    }
    
    // Теперь, когда рассматриваемые вершины равноудалены от корня, движемся, пока не встретим общего предка:
    while( a-1 != b-1) {
        result += arr[a-1].length + arr[b-1].length;
        a = arr[a-1].prev;
        b = arr[b-1].prev;
    }
    
    return result;
}

int main () {
    cin>>N;
    arr = new vertex[N];
    arr[0].lvl = 1;
    
    unsigned short v1, v2, len;
    for(int i=1; i<N; i++) {
        cin>>v1>>v2>>len;
        
        arr[v1-1].vert.push_back( vertex::edge(v2, len) );
        arr[v2-1].vert.push_back( vertex::edge(v1, len) );
    }
    createNormalBranch(1);
    
    unsigned short M; cin>>M;
    
    for(int i=0; i<M; i++) {
        cin>>v1>>v2;
        cout<<searchWay(v1, v2)<<endl;
    }
    
    delete [] arr;
}
