/*
Длина кратчайшего пути в дереве между вершинами A и B
вычисляется как L(A) + L(B) - 2L(LCA(A,B)), где
L(V) - заранее вычисленная длина от корня о вершины,
LCA(A,B) - наименьший общий предок A и B
Задача LCA сводится к задаче RMQ и решается за O(1)
и с препроцессингом за O(nlogn) построением sparse table
*/
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <cmath>
using namespace std;

struct intPair
{
    intPair(const int x, const int y) : first(x), second(y) {}
    bool operator< (const intPair &other) const
    {
        if (first < other.first) return true; else return false;
    }
    int first;
    int second;
};

typedef map< intPair, unsigned int > weightsMap;
typedef vector< intPair > testsArray;
typedef vector< unsigned int > intArray;
typedef set< unsigned int > intSet;
typedef vector< vector< unsigned int > > twoDimArray;
typedef vector< unsigned int >::iterator intIter;
typedef vector< intPair >::const_iterator pairIntIter;

inline unsigned int log2(const unsigned int x)
{
    return static_cast<unsigned int>(floor(log(static_cast<float>(x)) * 1.4427));
}

/*
Обходом в глубину заполняет массивы длин от корня до вершины, порядка обхода,
высот вершин при обходе и время первого захода в вершину
*/
void deepFirstSearch(const twoDimArray &tree, unsigned int node, unsigned int height,
                     intArray &length, intArray &order, intArray &heights, intArray &first,
                     intSet &visited, weightsMap &weight)
{
    order.push_back(node);
    heights.push_back(height);
    visited.insert(node);
    if (first[node - 1] == 0)
    {
        first[node - 1] = order.size();
    }
    vector<unsigned int> children = tree[node - 1];
    for (intIter child = children.begin(); child != children.end(); child++)
    {
        if (visited.find(*child) == visited.end())
        {
            length[*child - 1] = length[node - 1]
                                 +
                                 weight.find(intPair(*child, node))->second;
            deepFirstSearch(tree, *child, height + 1, length, order,
                            heights, first, visited, weight);
            order.push_back(node);
            heights.push_back(height);
        }
    }
}

/*
Загружает дерево и тесты из входных данных 
*/
unsigned int loadTree(twoDimArray &tree, weightsMap &weights, testsArray &tests)
{
    unsigned int vertCount = 0;
    scanf("%u",&vertCount);
    tree.resize(vertCount);
    unsigned int first, second, weight;
    for (unsigned int i = 0; i < vertCount - 1; i++)
    {
        scanf("%u%u%u", &first, &second, &weight);
        tree[first - 1].push_back(second);
        tree[second - 1].push_back(first);
        weights.insert(make_pair< intPair, int >(intPair(first, second), weight));
        weights.insert(make_pair< intPair, int >(intPair(second, first), weight));
    }
    unsigned int testCount = 0;
    scanf("%u", &testCount);
    tests.reserve(testCount);
    for (unsigned int i = 0; i < testCount; i++)
    {
        scanf("%u%u", &first, &second);
        tests.push_back(intPair(first, second));
    }
    return vertCount;
}

/*
Строит sparse table
*/
void makeTable(const intArray &height, twoDimArray &table)
{
    unsigned int size = height.size();
    unsigned int maxLog = log2(size);
    table.resize(size);
    for (unsigned int i = 0; i < size; i++)
    {
        table[i].resize(maxLog + 1);
        table[i][0] = i;
    }
    for (unsigned int j = 1; j <= maxLog; j++)
    {
        for (unsigned int i = 0; i < size + 1 - (1 << j); i++)
        {
            if (height[table[i][j - 1]] < height[table[i + (1 << (j - 1))][j - 1]])
                table[i][j] = table[i][j - 1];
            else
                table[i][j] = table[i + (1 << (j - 1))][j - 1];
        }
    }
}

/*
Находит ответ для задачи RMQ в таблице
*/
inline unsigned int rmq(const intArray &order, const intArray &height,
                        const twoDimArray &table, unsigned int l, unsigned int r)
{
    unsigned int k = log2(r - l + 1);
    if (height[table[l][k]] <= height[table[r + 1 - (1 << k)][k]])
        return order[table[l][k]];
    else
        return order[table[r + 1 - (1 << k)][k]];
}

/*
Вычисляет и выводит ответ для каждого теста
*/
void computeLengths(const intArray &order, const intArray &height,
                    const twoDimArray &table, const intArray &first,
                    const intArray &length, const testsArray &tests)
{
    for (pairIntIter test = tests.begin(); test != tests.end(); test++)
    {
        unsigned int firstNode = test->first;
        unsigned int secondNode = test->second;
        unsigned int x = first[firstNode - 1];
        unsigned int y = first[secondNode - 1];
        unsigned int left = min(x, y) - 1;
        unsigned int right = max(x, y) - 1;
        unsigned int node = rmq(order, height, table, left, right);
        unsigned long int sum = length[firstNode-1] + length[secondNode-1] - 2 * length[node - 1];
        printf("%u\n",sum);
    }
}

int main()
{
    twoDimArray tree;
    weightsMap weight;
    testsArray tests;
    unsigned int vertCount = loadTree(tree, weight, tests);
    intArray order; //порядок при обходе в глубину
    intArray height; //высота вершины при обходе
    intArray first(vertCount, 0); //индекс первого вхождения вершины в порядке обхода
    intArray length(vertCount, 0); //расстояние от вершины до корня
    intSet visited;
    deepFirstSearch(tree, 1, 1, length, order, height, first, visited, weight);
    twoDimArray table;
    makeTable(height, table);
    computeLengths(order, height, table, first, length, tests);

    return 0;
}