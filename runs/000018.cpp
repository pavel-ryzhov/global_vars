// vim: et ts=4 sts=4 sw=4 :
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

typedef int GraphNodeIndex;
typedef unsigned int Weight;

/**
 * @brief Двоичный логарифм с округлением к большему целому.
 *
 * @pre \f$2 \le n < 2^{8 \mathop{\mathrm{sizeof}}(n) - 2}\f$.
 */
int log2_ceil( int n )
{
    assert( 2 <= n && n < (1 << (8*sizeof(n) - 2)) );

    int res = 1;
    while ( (1 << res) < n )
        ++res;
    return res;
}

/**
 * @brief Соединения в графе.
 *
 * Для восстановления ребра необходимо знать из какой вершины это
 * соединение установлено (см. GraphNode::children).
 */
struct GraphConnection
{
    GraphNodeIndex node; /**< Одна из вершин ребра. */
    Weight weight;       /**< Вес соединения. */

    GraphConnection( ):
        node( -1 ), weight( 0 )
    {
    }

    GraphConnection( GraphNodeIndex n, Weight w ):
        node( n ), weight( w )
    {
    }
};


/**
 * @brief Узел в графе (дереве).
 */
struct GraphNode
{
    GraphConnection parent;                 /**< Ребро, соединяющее узел с родителем. */
    int depth;                              /**< Глубина, равна весу пути от корня до узла. У корня равна 0. */
    std::vector< GraphNodeIndex > children; /**< Дочерние элементы. */

    GraphNode( ):
        parent(), depth( 0 ),
        children()
    {
    }
};

/**
 * @brief Неориентированный связный граф без циклов (дерево).
 *
 * Взвешенный граф с возможностью вычисления веса расстояния между
 * двумя вершинами.
 */
class Graph
{
    typedef std::vector< GraphNode > GraphVector;

public:
    /**
     * @brief Конструктор.
     *
     * @param nodes Количество узлов в графе.
     */
    Graph( int nodes ):
        graph_( nodes ),
        ready_( false ),
        blockSize_( 0 ),
        order_(), first_( 0 ),
        sparseTable_( 0 ),
        blockHash_( 0 ), blockRMQ_( 0 ),
        log2_floor_( 0 )
    {
    }
    
    /**
     * @brief Конструктор.
     *
     * @note
     * Данные построенные buildTree() не копируются.
     */
    Graph( const Graph& g ):
        graph_( g.graph_ ),
        ready_( false ),
        blockSize_( 0 ),
        order_(), first_( 0 ),
        sparseTable_( 0 ),
        blockHash_( 0 ), blockRMQ_( 0 ),
        log2_floor_( 0 )
    {
    }

    /**
     * @brief Деструктор.
     */
    ~Graph( )
    {
        cleanup( );
    }

    /**
     * @brief Оператор присваивания.
     *
     * @note
     * Данные построенные buildTree() не копируются.
     */
    Graph& operator=( const Graph& g )
    {
        cleanup( );
        graph_ = g.graph_;
        return *this;
    }

    /**
     * @brief Добавление ребра.
     *
     * Ребро соединяет вершины \p a и \p b и имеет вес \p weight.
     *
     * @param a Первая вершина ребра. Нумерация с 0.
     * @param b Вторая вершина ребра. Нумерация с 0.
     * @param weight Вес ребра.
     *
     * @note
     * Функция сбрасывает результат работы buildTree().
     */
    void addEdge( GraphNodeIndex a, GraphNodeIndex b, Weight weight )
    {
        assert( 0 <= a && a < graph_.size() );
        assert( 0 <= b && b < graph_.size() );

        if ( graph_[a].parent.node == -1 )
        {
            graph_[a].parent.node = b;
            graph_[a].parent.weight = weight;
            graph_[b].children.push_back( a );
        }
        else if ( graph_[b].parent.node == -1 )
        {
            graph_[b].parent.node = a;
            graph_[b].parent.weight = weight;
            graph_[a].children.push_back( b );
        }
        else
        {
            assert( !"invalid edge (probably loop)" );
        }

        if ( ready_ )
        {
            cleanup( );
        }
    }

    /**
     * @brief Выполнение предварительных вычислений, необходимых
     *        для работы distance().
     *
     * Сложность: \f$\mathcal{O}(n)\f$.
     */
    void buildTree( )
    {
        if ( ready_ )
        {
            cleanup( );
        }

        if ( graph_.size() <= 1 )
        {
            ready_ = true;
            return;
        }

        /* Preparing order_ and first_ arrays */
        order_.reserve( graph_.size()*2 );
        first_ = new int[graph_.size()];
        std::fill( first_, first_ + graph_.size(), -1 );
        visitNode( getRoot() );

        /* Calculating sparse table on blocks */
        blockSize_ = log2_ceil( order_.size() )/2;
        int blocks = (order_.size() + blockSize_ - 1) / blockSize_;
        int levels = log2_ceil( blocks );
        sparseTable_ = new int*[levels + 1];

        /* Calculating sparse table for i = 0 */
        sparseTable_[0] = new int[blocks];
        int block = 0;
        int minnode = 0;
        for ( int i = 0, l = 0; i < order_.size(); ++i, ++l )
        {
            // sparseTable_[0][block] = min within block

            if ( l == blockSize_ )
            {
                sparseTable_[0][block] = minnode;

                ++block;
                l = 0;
                minnode = order_[i];
            }

            if ( graph_[order_[i]].depth < graph_[minnode].depth )
            {
                minnode = order_[i];
            }
        }
        sparseTable_[0][block] = minnode;

        /* Calculating sparse table for i = 1...levels */
        for ( int i = 1; i <= levels; ++i )
        {
            // sparseTable[i][l] = min within [l, l + 2^i), i = 1...levels, l = 0...(blocks - 1)
            sparseTable_[i] = new int[blocks];

            for ( block = 0; block < blocks; ++block )
            {
                if ( block + (1 << (i-1)) >= blocks )
                {
                    sparseTable_[i][block] = sparseTable_[i-1][block];
                }
                else
                {
                    int l = sparseTable_[i-1][block];
                    int r = sparseTable_[i-1][block + (1 << (i-1))];
                    sparseTable_[i][block] = minDepthNode( l, r );
                }
            }
        }

        /* Calculating hashes of blocks */
        blockHash_ = new int[blocks];
        block = 0;
        for ( int i = 0, l = 0; i < order_.size() || l < blockSize_; ++i, ++l )
        {
            if ( l == blockSize_ )
            {
                ++block;
                l = 0;
            }

            if ( l == 0 )
            {
                blockHash_[block] = 0;
            }
            else if ( i >= order_.size() || minDepthNode(order_[i-1], order_[i]) == order_[i-1] )
            {
                blockHash_[block] += 1 << (l - 1);
            }
        }

        /* Calculating RMQ for blocks */
        blockRMQ_ = new int**[1 << (blockSize_ - 1)];
        std::fill( blockRMQ_, blockRMQ_ + (1 << (blockSize_ - 1)), (int**)0 );
        for ( int i = 0; i < blocks; ++i )
        {
            int hash = blockHash_[i];
            if ( blockRMQ_[hash] != 0 )
                continue;

            blockRMQ_[hash] = new int*[blockSize_];
            for ( int l = 0; l < blockSize_; ++l )
            {
                /* r = l...(blockSize_ - 1) */
                blockRMQ_[hash][l] = new int[blockSize_ - l];
                blockRMQ_[hash][l][0] = l;
                for ( int r = l + 1; r < blockSize_; ++r )
                {
                    if ( i*blockSize_ + r < order_.size() )
                    {
                        int ans = blockRMQ_[hash][l][r - l - 1];
                        if ( graph_[order_[i*blockSize_ + ans]].depth < graph_[order_[i*blockSize_ + r]].depth )
                            blockRMQ_[hash][l][r - l] = ans;
                        else
                            blockRMQ_[hash][l][r - l] = r;
                    }
                    else
                    {
                        blockRMQ_[hash][l][r - l] = blockRMQ_[hash][l][r - l - 1];
                    }
                }
            }
        }

        /* Calculating floor(log2(n)) */
        log2_floor_ = new int[graph_.size()];
        log2_floor_[0] = 0; /* oh... */
        log2_floor_[1] = 0;
        for ( int i = 2, l = 0; i < graph_.size(); ++i )
        {
            if ( (i & (i-1)) == 0 )
                ++l;
            log2_floor_[i] = l;
        }

        ready_ = true;
    }

    /**
     * @brief Вычисление веса расстояния между двумя вершинами.
     *
     * Сложность: \f$\mathcal{O}(1)\f$.
     *
     * @note
     * Этой функции необходимы данные, которые вычисляет buildTree().
     * Если этих данных нет, то buildTree() будет вызвана автоматически
     * (что может существенно увеличить время работы функции).
     */
    Weight distance( GraphNodeIndex a, GraphNodeIndex b )
    {
        if ( !ready_ )
            buildTree();
        assert( ready_ );

        if ( graph_.size() <= 1 )
        {
            return 0;
        }

        /* searching min within [first_[a], first_[b]] */
        int l = first_[a];
        int r = first_[b];

        if ( l > r )
            std::swap( l, r );

        int bl = l/blockSize_;
        int br = r/blockSize_;

        int min;
        if ( bl == br )
        {
            min = blockRMQ( bl, l%blockSize_, r%blockSize_ );
        }
        else
        {
            int minl = blockRMQ( bl, l%blockSize_, blockSize_ - 1 );
            int minr = blockRMQ( br, 0, r%blockSize_ );
            min = minDepthNode( minl, minr );

            if ( bl < br - 1 )
            {
                int pow2 = log2_floor_[br - bl - 1];
                int minm = minDepthNode( sparseTable_[pow2][bl+1], sparseTable_[pow2][br - (1 << pow2)] );
                min = minDepthNode( min, minm );
            }
        }

        /* calculating distance */
        Weight d = graph_[a].depth + graph_[b].depth - 2*graph_[min].depth;
        return d;
    }

private:
    GraphVector graph_;
    bool ready_;                          /**< Флаг готовности к вычислению расстояний. */
    int blockSize_;
    std::vector< GraphNodeIndex > order_; /**< Порядок обхода дерева в глубину. */
    int* first_;                          /**< order_[first_[n]] == n. */
    GraphNodeIndex** sparseTable_;
    int* blockHash_;                      /**< Массив с хэшами блоков. */
    int*** blockRMQ_;                     /**< blockRMQ_[id][l][r-l] хранит решение задачи RMQ
                                               внутри блока с хэшем id на отрезке [l, r]. */
    int* log2_floor_;                     /**< Предварительно вычисленные значения floor(log2(n)). */

    void cleanup( )
    {
        if ( first_ )
        {
            delete[] first_;
            first_ = 0;
        }

        if ( sparseTable_ )
        {
            int blocks = (order_.size() + blockSize_ - 1) / blockSize_;
            int levels = log2_ceil( blocks );

            for ( int i = 0; i <= levels; ++i )
                delete[] sparseTable_[i];
            delete[] sparseTable_;

            sparseTable_ = 0;
        }

        if ( blockHash_ )
        {
            delete[] blockHash_;
            blockHash_ = 0;
        }

        if ( blockRMQ_ )
        {
            for ( int i = 0; i < (1 << (blockSize_ - 1)); ++i )
            {
                if ( blockRMQ_[i] )
                {
                    for ( int l = 0; l < blockSize_; ++l )
                        delete[] blockRMQ_[i][l];
                    delete[] blockRMQ_[i];
                }
            }
            delete[] blockRMQ_;

            blockRMQ_ = 0;
        }

        if ( log2_floor_ )
        {
            delete[] log2_floor_;
            log2_floor_ = 0;
        }

        order_.clear( );
        ready_ = false;
    }

    GraphNodeIndex minDepthNode( GraphNodeIndex a, GraphNodeIndex b )
    {
        if ( graph_[a].depth <= graph_[b].depth )
            return a;
        else
            return b;
    }

    /**
     * @brief Решение задачи RMQ внутри блока.
     *
     * Нахождение узла с минимальным весом внутри блока \p block массива
     * \c order_ на отрезке [\p l, \p r].
     *
     * @return Индекс узла в массиве graph_.
     */
    GraphNodeIndex blockRMQ( int block, int l, int r )
    {
        assert( ready_ );

        return order_[blockRMQ_[blockHash_[block]][l][r-l] + block*blockSize_];
    }

    GraphNodeIndex getRoot( )
    {
        GraphNodeIndex root;
        for ( root = 0; root < graph_.size(); ++root )
        {
            if ( graph_[root].parent.node == -1 )
                break;
        }

        assert( root != graph_.size() && "root not found (probably loop)" );

        return root;
    }

    /**
     * @brief Рекурсивная функция обхода дерева в глубину.
     *
     * Заполняет массивы order_, first_ и вычисляет глубину каждого узла.
     */
    void visitNode( GraphNodeIndex n, int depth = 0 )
    {
        GraphNode& node = graph_[n];

        order_.push_back( n );
        node.depth = depth;

        if ( first_[n] == -1 )
            first_[n] = order_.size() - 1;

        for ( std::vector< GraphNodeIndex >::const_iterator it = node.children.begin(); it != node.children.end(); ++it )
        {
            visitNode( *it, depth + graph_[*it].parent.weight );
            order_.push_back( n );
        }
    }
};

int main( )
{
    int numOfNodes;
    std::cin >> numOfNodes;

    Graph graph( numOfNodes );
    for ( int i = 0; i < numOfNodes-1; ++i )
    {
        int a, b;
        int weight;
        std::cin >> a >> b >> weight;

        graph.addEdge( a - 1, b - 1, weight );
    }

    int numOfTasks;
    std::cin >> numOfTasks;

    for ( int i = 0; i < numOfTasks; ++i )
    {
        int a, b;
        std::cin >> a >> b;

        std::cout << graph.distance( a - 1, b - 1 ) << "\n";
    }

    return 0;
}
