#include <cstdlib>
#include <cstdio>
#include <vector>

namespace matsuk {
    
using std::vector;
using std::pair;

/******************************************************************************
 * class TreeDSU -- implementation of LCA finder (Tarjan algorithm)
 *****************************************************************************/

class TreeDSU {
public:
    TreeDSU (size_t nodes);

    /*!
     * Read tree edges from stdin
     */
    void LoadTreeStructure ();

    /*!
     * Read LCA queries from stdin
     */
    void LoadQueries ();

    /*!
     * Process LCA queries into @answers
     */
    void ComputeLCA (vector<size_t> * answers);

private:
    /*!
     * Tree edges type
     * \pair::first Connected node
     * \pair::second Edge length
     */
    typedef vector< pair<size_t, size_t> > Edge;

    /*!
     * Stored LCA queries type
     * \pair::first Second connected node
     * \pair::second Query number
     */
    typedef vector< pair<size_t, size_t> > StoredQuery;

    vector<Edge> edges;             //! Edges of each node
    vector<size_t> rank;            //! Nodes rank in tree
    vector<size_t> setParent;       //! Node's parent in DSU
    vector<size_t> distInDSU;       //! Node's distance from set root
    vector<size_t> distFrom0;       //! Stack of distances from tree root
    vector<StoredQuery> toFind;     //! Queries by first node
    size_t totalQueries;

    vector<size_t> * pAnswers;      //! Shortcut to answers structure
    vector<bool> isVisited;         //! Service structure for DFS

    /*!
     * Get root of @node's set. Balances DSU structure
     */
    size_t getRootDSU (size_t node);

    /*!
     * Merge two sets in DSU. Root of @n1's set becomes new set's root 
     */
    void mergeSetsDSU (size_t n1, size_t n2, size_t dist);

    /*!
     * DFS for queries answers
     */
    void DFSforLCA (size_t node);
};

TreeDSU::TreeDSU(size_t nodes) :
    edges(nodes), rank(nodes), setParent(nodes), 
    distInDSU(nodes), distFrom0(1, 0), toFind(nodes), 
    totalQueries(0), pAnswers(NULL), isVisited(nodes, false)
{
    rank[0] = 0;
}

size_t TreeDSU::getRootDSU (size_t node) {
    if (node >= setParent.size()) {
        return 0;
    }
    if (node == setParent[node]) {
        return node;
    }
    size_t root = getRootDSU( setParent[node] );
    distInDSU[node] += distInDSU[ setParent[node] ];
    return setParent[node] = root;
}

void TreeDSU::mergeSetsDSU (size_t n1, size_t n2, size_t dist) {
    n1 = getRootDSU(n1);
    n2 = getRootDSU(n2);
    distInDSU[n2] = dist;
    setParent[n2] = n1;
}

void TreeDSU::DFSforLCA (size_t node) {
    if (node >= edges.size()) {
        return;
    }
    setParent[node] = node;
    isVisited[node] = true;
    for (size_t to = 0; to < edges[node].size(); ++to) {
        size_t newNode = edges[node][to].first;
        size_t edgeLength = edges[node][to].second;
        if (! isVisited[newNode]) {
            // Move deeper in tree
            rank[newNode] = rank[node] + 1;
            distFrom0.push_back(distFrom0.back() + edgeLength);
            DFSforLCA(newNode);
            distFrom0.pop_back();
            mergeSetsDSU(node, newNode, edgeLength);
        }
    }
    for (size_t to = 0; to < toFind[node].size(); ++to) {
        size_t secondNode = toFind[node][to].first;
        size_t writeTo = toFind[node][to].second;
        if (isVisited[secondNode]) {
            // Been there, data is ready
            size_t root = getRootDSU(secondNode);
            (*pAnswers)[writeTo] = distFrom0.back() 
                - distFrom0[rank[root]] + distInDSU[secondNode];
        } else {
            // Answer this query later
            toFind[secondNode].push_back( pair<size_t,size_t>(node, writeTo) );
        }
    }
}

void TreeDSU::ComputeLCA (vector<size_t> * answers) {
    answers->resize(totalQueries);
    pAnswers = answers;
    DFSforLCA(0);
}

void TreeDSU::LoadTreeStructure() {
    size_t nodes = edges.size();
    for (size_t i = 0; i + 1 < nodes; ++i) {
        size_t begin, end, length;
        if (scanf("%u %u %u", &begin, &end, &length) == 3 && 
            begin <= nodes && end <= nodes) 
        {
            edges[begin-1].push_back( pair<size_t,size_t>(end-1, length) );
            edges[end-1].push_back( pair<size_t,size_t>(begin-1, length) );
        }
    }
}

void TreeDSU::LoadQueries() {
    size_t nodes = toFind.size();
    if (scanf("%u", &totalQueries)) {
        for (size_t i = 0; i < totalQueries; ++i) {
            size_t first, second;
            if (scanf("%u %u", &first, &second) == 2 && 
                first <= nodes && second <= nodes) 
            {
                toFind[first-1].push_back( pair<size_t,size_t>(second-1, i) );
            }
        }
    }
}

}; // namespace matsuk

using namespace matsuk;

void OutputAnswers (const vector<size_t> & answers) {
    for (size_t i = 0; i < answers.size(); ++i) {
        printf("%u\n", answers[i]);
    }
}

int main(int argc, const char *argv[])
{
    size_t nodes;
    if (! scanf("%u", &nodes)) {
        return -1;
    }
    TreeDSU LCAfinder(nodes);
    LCAfinder.LoadTreeStructure();
    LCAfinder.LoadQueries();

    vector<size_t> answers;
    LCAfinder.ComputeLCA(&answers);
    OutputAnswers(answers);
    return 0;
}
