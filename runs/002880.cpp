/*
 * File:   taskb.cpp
 * Author: Sergey Nikishin
 *
 * Created on 3 Сентябрь 2010 г.
 */
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <iterator>
using std::string;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
#include <vector>

typedef std::vector< int > IntVector;
typedef std::pair< int, int > IntPair;
typedef std::vector< IntPair > PairsVector;

// список ребер до потомков (с весами)
struct ChildNode
{
    int adjacentNode;
    int weight;
};

typedef std::vector<ChildNode> ChildList;
typedef std::vector<ChildList> TreeData;

// хранит предварительные рассчеты и выдает длину пути по запросу
class LCAdata
{
public:
    LCAdata( const TreeData & tree_data )
    : treeData( tree_data ), walkOrder()
    , nodeWalkIndex( tree_data.size () ), weights( tree_data.size () )
    {
        InitLCAdata();
    }

    // найти длину кратчайшего пути
    int FindDistance( const int node1, const int node2) const
    {
        if( node1 == node2 ) {
            return 0;
        }

        // найти границы отрезка
        int index1 = nodeWalkIndex[ node1 ];
        int index2 = nodeWalkIndex[ node2 ];
        if ( index1 > index2) {
            std::swap ( index1, index2 );
        }

        // вес ближайшего общего предка
        int min_parent_weight = FindMinElement ( index1, index2, 0, walkOrder.size () - 1 );

        // результат - сумма весов данных вершин без учета веса общего предка
        return weights[ node1 ] + weights[ node2 ] - 2 * min_parent_weight;
    }

    // вывести данные на экран
    void Print() const
    {
        cout << "LCA data:\n";
        cout << "walk order:\n";
        for ( int i = 0; i < walkOrder.size (); ++i )
        {
            cout << walkOrder[ i ] + 1 << " -> ";
        }

        cout << "\nnode walk indexes:\n";
        for ( int i = 0; i < nodeWalkIndex.size (); ++i )
        {
            cout << i + 1 << "-" << nodeWalkIndex[ i ] << ", ";
        }
        
        cout << "\nweights:\n";
        for ( int i = 0; i < weights.size (); ++i )
        {
            cout << i + 1 << "--" << weights[ i ] << ", ";
        }

        cout << "\ntree:\n";
        for ( int i = 0; i < segmentsTree.size (); ++i )
        {
            cout << segmentsTree[ i ] << ", ";
        }

        cout << endl;
    }


private:
    // обход дерева в глубину
    void TreeWalk( int current_node, int weight_acumulator = 0 )
    {
        // записать вершину в список обхода и её вес
        weights[ current_node ] = weight_acumulator;

        nodeWalkIndex[ current_node ] = walkOrder.size ();
        walkOrder.push_back ( current_node );


        // обойти все поддеревья
        const ChildList & child_list = treeData[ current_node ];
        ChildList::const_iterator it = child_list.begin ();
        for ( ; it != child_list.end (); ++it )
        {
            // обойти каждое поддерево
            TreeWalk( it->adjacentNode, weight_acumulator + it->weight );

            // и на выходе еще раз вписать данную вершину в список обхода
            walkOrder.push_back ( current_node );
        }
    }

    // найти минимум на отрезке
    // (Дерево Фенвика)
    int FindMinElement( int left, int right, int first, int last, int treeIndex = 1 ) const
    {
        // закончить обход, если совпали
        if ( left == first && right == last ) {
            return segmentsTree[ treeIndex ];
        }

	int middle = ( first + last ) / 2;

	if ( right <= middle ) {
            return FindMinElement ( left, right, first, middle, treeIndex * 2 );
        }
	if ( left > middle ) {
            return FindMinElement ( left, right, middle + 1, last, treeIndex * 2 + 1 );
        }

	return std::min( FindMinElement ( left, middle, first, middle, treeIndex * 2 )
                , FindMinElement ( middle + 1, right, middle + 1, last, treeIndex * 2 + 1 ) );
    }

    // построить дерево поиска
    void BuildSegmentsTree ( int treeIndex, int left, int right )
    {
	if ( 1 == treeIndex ) {
            segmentsTree.resize ( walkOrder.size() * 4 + 1 );
        }

        // для одного элемента записать значение
	if ( left != right )
        {
            int middle = ( left + right ) / 2;
            // вычислить правое и левое поддерево
            BuildSegmentsTree ( treeIndex * 2, left, middle );
            BuildSegmentsTree ( treeIndex * 2 + 1, middle + 1, right );
            segmentsTree[ treeIndex ] = std::min( segmentsTree[ treeIndex * 2 ],  segmentsTree[ treeIndex * 2 + 1 ] );
	}
        else {
           segmentsTree[ treeIndex ] = weights[ walkOrder[ left ] ];
        }
    }

    // предварительная обработка дерева, построение
    void InitLCAdata()
    {
        // обойти дерево для генерации всех нужных значений
        TreeWalk ( 0 );

        // построить дерево отрезков
        BuildSegmentsTree ( 1, 0, walkOrder.size () - 1 );
    }

    const TreeData & treeData;
    IntVector walkOrder; // список вершин по порядку их обхода в глубину
    IntVector nodeWalkIndex; // где в этом списке находится вершина
    IntVector weights; // вес всех вершин
    IntVector segmentsTree; // дерево отрезков для расчетов
};

/*
 * вывести дерево на экран
 */
void PrintTreeData( const TreeData & treeData )
{
    cout << "\n\ttree data:";
    TreeData::const_iterator it = treeData.begin ();
    for ( int i=0; it != treeData.end (); ++it, ++i )
    {
        cout << "\nnode # " << i + 1;
        cout << "\nedges to:\n";

        const ChildList & child_list = *it;

        ChildList::const_iterator child_it = child_list.begin ();
        for ( ; child_it != child_list.end (); ++child_it )
        {
            cout << "- " << child_it->adjacentNode + 1 << " ("
                    << child_it->weight << ")\n";
        }

        cout << endl;
    }
}

/*
 * прочитать дерево из потока
 */
void ReadTreeData ( TreeData * treeData, const int nodesCount )
{
    if ( !treeData ) {
        cerr << "ReadTreeData: bad arguments" << endl;
        return;
    }

    int node = 0;
    ChildNode child_node = {0, 0};

    for ( int i = 0; i < nodesCount; ++i )
    {
        cin >> node;
        cin >> child_node.adjacentNode;
        cin >> child_node.weight;
        --node;
        --child_node.adjacentNode;
        ( *treeData )[ node ].push_back ( child_node );
    }
}

/*
 * ввести входные данные
 */
void ReadStream ( TreeData * treeData, PairsVector * pairs )
{
    if ( !treeData || !pairs ) {
        cerr << "ReadStream: bad arguments" << endl;
        return;
    }

    // получить количество вершин
    int nodes_count = 0;
    cin >> nodes_count;

    cerr << "info... nodes_count: " << nodes_count << endl;
    treeData->resize ( nodes_count );

    // и само дерево
    ReadTreeData( treeData, nodes_count - 1);

    // получить количество пар
    int pairs_count = 0;
    cin >> pairs_count;
    cerr << "info... pairs_count: " << pairs_count << endl;

    // и сами пары
    for ( int i = 0; i < pairs_count; ++i )
    {
        IntPair pair;
        cin >> pair.first;
        cin >> pair.second;
        --pair.first;
        --pair.second;
        pairs->push_back ( pair );
    }
}

/*
 * вычислить все расстояния
 */
void ProcessPairs ( const PairsVector & pairs, const LCAdata & data )
{
    PairsVector::const_iterator it = pairs.begin ();
    for ( ; it != pairs.end (); ++it ) {
        cout << data.FindDistance ( it->first, it->second ) << endl;
    }
}

/*
 *
 */
int main ( int argc, char** argv )
{
    TreeData treeData;
    PairsVector pairs;
    // получить данные из потока (дерево и пары вершин для нахождения расстояний)
    ReadStream ( &treeData, &pairs );

    // первоначально обработать дерево
    LCAdata lca ( treeData );

    // обработать все пары
    ProcessPairs ( pairs, lca );

    return 0;
}