/**
 * File:   B.cpp
 * Author: Nesterenko Denis Sergeevich
 *
 * Created on 2 October 2010, 22:32
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>

#define MAX_SIZE 1000   //Max размер массивов depth[], parent[], depth_bin[]

using namespace std;

typedef vector< pair<int, int> > Edge;              //Для пар вершин
typedef vector< vector< pair<int, int> > > Tree;    //Дерево

/**
 * Стуктура для получения введенных данных из функции inputData()
 */
struct inputData {
    int numOfVertexes;  //Количество вершин (узлов) дерева (графа)
    int numOfPairs;     //Количество пар вершин,
                        // для которых нужно найти длину кратчайшего пути
    Tree tree;          //Дерево (граф)
    Edge nodes;         //Номера вершин,
                        // между которыми необходимо вычислить расстояние
};

/**
 * Функция получения введенных данных
 * @return {inputData} inData
 */
inputData getData(){
    inputData inData;   //Возвращаемая структура
    int treeVN;         //Количество вершин дерева
    int treeFN;         //Количество пар (для нахождения кратчайшего пути)
    scanf("%d", &treeVN);
    Tree tree(treeVN);
    Edge nodes;
    if(treeVN <= 0) {
        cerr << "error:" << endl;
        cerr << "The number of vertices in the graph must be >= 0!" << endl;
        exit(1);
    }//if
    else {
        if(treeVN == 1) {
            tree[0].push_back(make_pair(0, 0));
        }//if
        else {
            int b, e, l;
            for(int i = 0; i < treeVN - 1; i++) {
                scanf("%d  %d  %d", &b, &e, &l);
                if(b > 0 && e > 0 && l > 0)
                    tree[b - 1].push_back(make_pair(e - 1, l));
                else {
                    cerr << "error:" << endl;
                    cerr << "The edges numbers must be  > 0!" << endl;
                    exit(1);
                }//else
            }//for
        }//else
        scanf("%d", &treeFN);
        if(treeFN <= 0) {
            cerr << "error:" << endl;
            cerr << "The number of couples must be > 0!" << endl;
            exit(1);
        }//if
        int n1, n2;
        for(int i = 0; i < treeFN; i++) {
            scanf("%d  %d", &n1, &n2);
            if(n1 > 0 && n2 > 0)
                nodes.push_back(make_pair(n1 - 1, n2 - 1));
            else {
                cerr << "error:" << endl;
                cerr << "The numbers of couples must be > 0!" << endl;
                exit(1);
            }//else
        }//for
    }//else
    inData.numOfVertexes = treeVN;
    inData.numOfPairs = treeFN;
    inData.tree = tree;
    inData.nodes = nodes;
    return inData;
}//getData

/**
 * Функция препроцессинга (рукурсивная функция)
 * Обход графа в глубину. Находясь в каждой вершине, мы заносим в массив depth[]
 * путь от корня до вершины, в массив parent[] — вершину, из которой мы пришли
 * (родительскую вершину), а в массив depth_bin[] — уровень текущей вершины
 * относительно корня (т.е. кол-во вершин-уровней, отделяющих вершину от корня).
 * Независимо от числа пар-вершин, между которыми необходимо найти кратчайшее
 * расстояние, препроцессинг выполняется один раз.
 *
 * @param v             Исходная вершина
 * @param lastleng      Длина последнего добавленного к way ребра
 * @param from          С какой вершины мы пришли (на предыдущей итерации)
 * @param used[]        Для хранения информации о том, посещена вершина или нет
 * @param depth[]       Путь от корня до вершины
 * @param parent[]      Вершина из которой мы пришли (родительская вершина)
 * @param depth_bin[]   Уровень текущей вершины относительно корня
 * @param tree          Неориентированный связный граф без циклов (дерево)
 * @param way           Путь от вершины v до одной из рассматриваемых вершин
 * @param way_bin       Уровень относительно корня
 * @return              {int}
 */
int dfs(int v,
        int lastleng,
        int from,
        vector <bool> &used,
        int* depth,
        int* parent,
        int* depth_bin,
        Tree &tree,
        int* way,
        int* way_bin) {

cerr << "v: " << v << "   "
     << "lastleng: " << lastleng << "   "
     << "from: " << from << endl;

    used[v] = true;
    parent[v] = from;
    depth[v] = *way;
    depth_bin[v] = *way_bin;
    for(int i = 0; i < tree[v].size(); i++) {
        int CurrentNode = tree[v][i].first;
        int CurrentLen = tree[v][i].second;
        if(!used[CurrentNode]) {
            *way += CurrentLen;
            *way_bin = *way_bin + 1;
            //*way_bin++;
            dfs(CurrentNode,
                CurrentLen,
                v,
                used,
                depth,
                parent,
                depth_bin,
                tree,
                way,
                way_bin);
        }
        else
            return 0;
    }
    *way_bin = *way_bin - 1;
    //*way_bin--;
    *way -= lastleng;
}

int main(int argc, char** argv, char** env) {

    inputData data = getData();
    int numOfVertexes = data.numOfVertexes;
    int numOfPairs = data.numOfPairs;
    Tree tree = data.tree;
    Edge nodes = data.nodes;

cerr << "\nnumOfVertexes: " << numOfVertexes << endl;
for(int i = 0; i < tree.size(); i++) {
    cerr << "tree[" << i << "]: " << endl;
    for(int j = 0; j < tree[i].size(); j++)
        cerr << "   " << tree[i][j].first << " _ " << tree[i][j].second << endl;
}
cerr << endl << "numOfPairs: " << numOfPairs << endl;
for(int i = 0; i < numOfPairs; i++) {
    cerr << "nodes[" << i << "]: " << endl;
    cerr << "   " << nodes[i].first << " _ " << nodes[i].second << endl;
}

    vector <bool> used;         //Посещена ли вершина или нет

    int depth[MAX_SIZE];
    int parent[MAX_SIZE];
    int depth_bin[MAX_SIZE];

    int way = 0;
    int way_bin = 0;

    //Изначально заполняем массив false - ни одна из вершин не посещена
    for(int i = 0; i < numOfVertexes; i++)
        used.push_back(false);

    //Препроцессинг.
    dfs(0, 0, 0, used, depth, parent, depth_bin, tree, &way, &way_bin);

cerr << "depth_bin: " << endl;
for(int i = 0; i < 10; i++) {
    cerr << depth_bin[i] << "   ";
}
cerr << endl;
cerr << "parent: " << endl;
for(int i = 0; i < 10; i++) {
    cerr << parent[i] << "   ";
}
cerr << endl;
cerr << "depth: " << endl;
for(int i = 0; i < 10; i++) {
    cerr << depth[i] << "   ";
}
cerr << endl << endl;

    //Поиск LCA и вычисление расстояния.
    int lca = 0;
    int lcb = 0;
    for(int i = 0; i < numOfPairs; i++) {
        int a = nodes[i].first;
        int b = nodes[i].second;
        lca = a;
        lcb = b;
cerr << "lca: " << lca << " lcb: " << lcb << endl;
        while(depth_bin[a] != depth_bin[b]) {
            if(depth_bin[a] > depth_bin[b])
                a = parent[a];
            else
                b = parent[b];
        }//while
        while (a != b) {
            a = parent[a];
            b = parent[b];
        }//while
        int way_ab = depth[lca] + depth[lcb] - 2 * depth[a];
//cerr << "Way from " << lca << " to " << lcb << " = " << way_ab << endl;
        cout << way_ab << endl;
    }//for

    return 0;
}//main


