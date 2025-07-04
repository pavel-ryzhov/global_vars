#include <iostream>
using namespace std;

// Граф хранится в одномерном массиве:
// Индекс в массиве соответствует номеру вершины (с поправкой на то, что индексация в массиве начинается с 0);
// lvl - "уровень" вершины, характеризует удаленность данной вершины от корня (у корня это поле равно 0);
// prev - ближайший предок;
// length - вес ребра (prev, "текущая вершина");
struct vertex {
    unsigned short lvl, prev, length;
    
    vertex() : lvl(0), prev(0), length(0) {}
}* arr;

// Количество вершин
unsigned short N;

// Я не знаю, в какой последовательности будут вводится данные о ребрах.
// Если данные вводятся в хаотичном порядке, то определение значений полей lvl требует
// отдельных затрат. Функция setBranch(a) выставляет значения lvl для "ветки", начиная
// с вершины a (двигаясь в сторону корня). Функция setAllLevels выставляет значения lvl
// для всего дерева.
void setBranch (unsigned short v) {
    // Находим корень
    if(arr[v-1].lvl == 0) {
        setBranch(arr[v-1].prev);
        arr[v-1].lvl = arr[arr[v-1].prev-1].lvl+1;
    }
}
void setAllLevels () {
    for(int i=0; i<N; i++) {
        if( arr[i].prev == 0 ) {
            arr[i].lvl = 1;
            break;
        }
    }
    
    for(int j=1; j<=N; j++) {
        setBranch(j);
    }
}

// Поиск пути от вершины a до вершины b
unsigned short searchWay (unsigned short a, unsigned short b) {
    if(a == b) return 0;
    unsigned short result = 0;
    
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
    
    unsigned short v1, v2, len;
    
    // Ввод N-1 строчек
    for(int i=1; i<N; i++) {
        cin>>v1>>v2>>len;
        
        arr[v2-1].prev = v1;
        arr[v2-1].length = len;
    }
    setAllLevels();
    
    int M; cin>>M;
    
    for(int i=0; i<M; i++) {
        cin>>v1>>v2;
        cout<<searchWay(v1, v2)<<endl;
    }
    
    delete [] arr;
    return 0;
}
