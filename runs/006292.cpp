#include <iostream>
#include <vector>

using namespace std;

/**
 * Destination node structure
 */
struct DestNode {
    /**
     * Node Id
     */
    int nId;
    
    /**
     * Edge weight
     */
    int weight;
};

/**
 * MinLengthFinder
 *
 * Finds minimal way between two nodes in tree
 */
class MinLengthFinder
{
    public:
        MinLengthFinder(vector< vector<DestNode> > *tree)
        {
            this->tree = tree;
            countMaxTreeHeight();            
            
            int n = tree->size();
            used.resize(n, false);
            timeIn.resize(n);
            timeOut.resize(n);
            up.resize(n);
            timer = 0;
            
            // prepare depth-first search data
            dfs(1, 1);
        }
        
        int shortLength(int src, int dest)
        {
            int lca = getLca(src, dest);
            int len = 0;
            
            // count length from src to lca
            for (int curr = src; curr != lca; curr = up[curr][0]) {
                len += getEdgeWeight(curr, up[curr][0]);
            }
            // count length from dest to lca
            for (int curr = dest; curr != lca; curr = up[curr][0]) {
                len += getEdgeWeight(curr, up[curr][0]);
            }
            
            return len;
        }
        
    private:
    
        int getEdgeWeight(int src, int dest)
        {
            if (src == dest) {
                return 0;
            }
            
            for (int i = 0, c = (*tree)[src].size(); i < c; ++i) {
                if ((*tree)[src][i].nId == dest) {
                    return (*tree)[src][i].weight;
                }
            }
            
            // src and dest are not neighbours
            return -1;
        }
        
        void countMaxTreeHeight()
        {
            int size = tree->size() - 1;

            h = 1;            
            while (1 << h <= size) {
                ++h;
            }
        }
    
        void dfs(int nId, int parentId)
        {
            used[nId] = true;
            timeIn[nId] = ++timer;
            
            up[nId].resize(h + 1);            
            up[nId][0] = parentId;
            
            // count 2^i parent of node nId
            for (int i = 1; i <= h; ++i) {
                up[nId][i] = up[ up[nId][i - 1] ][i - 1];
            }
            
            for (int i = 0, c = (*tree)[nId].size(); i < c; ++i) {
                if (!used[ (*tree)[nId][i].nId ]) {
                    dfs((*tree)[nId][i].nId, nId);
                }
            }
            
            timeOut[nId] = ++timer;
        }
        
        /**
         * Returns true if node upperNode is a parent of node lowerNode
         */
        bool isUpper(int upperNode, int lowerNode)
        {
            return timeIn[upperNode] <= timeIn[lowerNode] &&
                    timeOut[upperNode] >= timeOut[lowerNode];
        }
        
        int getLca(int n1, int n2)
        {
            if (isUpper(n1, n2)) {
                return n1;
            }
            if (isUpper(n2, n1)) {
                return n2;
            }
            
            int curr = n1;
            for (int i = h; i >= 0; --i) {
                if (!isUpper(up[curr][i], n2)) {
                    curr = up[curr][i];
                }
            }
            
            return up[curr][0];
        }
        
        /**
         * The tree
         *
         * For every node (index of vector 'tree') contains list of neighbour nodes
         */
        vector< vector<DestNode> > *tree;
        
        /**
         * Array of boolean to member checked nodes
         */
        vector<bool> used;
        vector<int> timeIn;
        vector<int> timeOut;
        
        /**
         * Contains 1, 2, 4, ..., 2^h parents for every node
         */
        vector< vector<int> > up;
        int h;
        int timer;
};

/**
 * Read tree from standart input
 */
bool readTree(vector< vector<DestNode> > &tree)
{
    int n = 0;
    cin >> n;
    
    if (n > 0) {
        tree.resize(n + 1);
        for (int i = 0, c = n - 1; i < c; ++i) {
            int src = 0, dest = 0, weight = 0;
            DestNode dst = {0, 0}, dstR = {0, 0};
            cin >> src >> dest >> weight;
            
            dst.nId  = dest;
            dstR.nId = src;
            dst.weight = dstR.weight = weight;
            tree[src].push_back(dst);
            tree[dest].push_back(dstR);
        }
        
        return true;
    }
    
    return false;
}

int main()
{
    vector< vector<DestNode> > tree;
        
    if (readTree(tree)) {
        int testNum = 0;
        cin >> testNum;
        
        if (testNum > 0) {
            MinLengthFinder mf(&tree);
            
            for (int i = 0; i < testNum; ++i) {
               int src = 0, dest = 0;
               cin >> src >> dest;
               
               cout << mf.shortLength(src, dest) << endl;
            }
        }
    } else {
        return 1;
    }
    
    return 0;
}
