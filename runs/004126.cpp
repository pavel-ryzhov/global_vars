//=============================================================
//  The program finds the distance in the tree.
//  It uses Tarjan algorithm to find least common ancestor.
//
//  Version: 2
//  Author: Zheykars
//=============================================================
#include <vector>
#include <iostream>
#include <map>
#include <utility>
#include <cstdlib>

using namespace std;

//=============================================================
// Globals
//=============================================================
struct EdgeToParent{
    int parent;
    int dist;
};


vector< vector<int> > graph; // граф и все запросы
map< int,vector< pair<int,int> > > query;
vector<int> dsu, ancestor;
vector<bool> u;
int root;
//--------------------------------------------------------------

//=============================================================
// dsu_get realizes operation Find() for disjoint set union
//=============================================================
int dsu_get (int v)
{
        return v == dsu[v] ? v : dsu[v] = dsu_get (dsu[v]);
}
//--------------------------------------------------------------

//=============================================================
// dsu_get realizes operation Union() for disjoint set union.
// Using randomize realization to balance the tree.
//=============================================================
void dsu_unite (int a, int b, int new_ancestor)
{
        a = dsu_get (a);
        b = dsu_get (b);
        if (rand() & 1)  swap (a, b);
        dsu[a] = b;
        ancestor[b] = new_ancestor;
}
//--------------------------------------------------------------

//=============================================================
// dfs realizes depth-first method
// and finds lca of vertexes in querys
//=============================================================
void dfs (int v) {
        dsu[v] = v;
        ancestor[v] = v;
        u[v] = true;

        for (size_t i=0; i<graph[v].size(); ++i)
                if (!u[graph[v][i]]) {
                        dfs(graph[v][i]);
                        dsu_unite(v, graph[v][i], v);
                }

        for (size_t i=0; i<query[v].size(); ++i)
                if (u[query[v][i].first]) {
                        query[v][i].second=ancestor[ dsu_get(query[v][i].first) ];
                }
}
//--------------------------------------------------------------


//=============================================================
// returns LCA(:
//=============================================================
int findLCA(int v, int u)
{
    int tmp;
    for(int i=0; i<query[v].size();++i){
        if(query[v][i].first==u) tmp=query[v][i].second;//return query[v][i].second;
    }
    if(tmp==-1) return findLCA(u,v);
    else return tmp;
}
//--------------------------------------------------------------

//=============================================================
// distance between parent and child
//=============================================================
int distance(int parent, int child, const vector<EdgeToParent> &g)
{
    if(g[child].parent==parent) return g[child].dist;
    else if(parent==child) return 0;
    else return g[child].dist+distance(parent,g[child].parent,g);
}

//--------------------------------------------------------------


//=============================================================
// print results
//=============================================================
void printResults(const vector< pair<int,int> > &q,const vector<EdgeToParent> &g)
{
    int u,v,lca;

    for(int i=0;i<q.size();++i){
        v=q[i].first;
        u=q[i].second;
        lca=findLCA(v,u);
        cout<<distance(lca,v,g)+distance(lca,u,g)<<endl;
    }
}
//--------------------------------------------------------------

//=============================================================
// reading graph
//=============================================================
void readGraph(vector<EdgeToParent> &g,int N)
{
    int p,c,d;
    g.resize(N);

    for(int i=0;i<N;i++){
        g[i].parent=-1;
        g[i].dist=0;
    }

    if(0<N-1){
        cin >> p >> c >> d;
        --p;
        --c;
        root=p;
        g[c].parent=p;
        g[c].dist=d;
        graph[p].push_back(c);
    }

    for(int i=1;i<N-1;++i){
        cin >> p >> c >> d;
        --p;
        --c;

        if(g[p].parent==-1){
            g[p].parent=c;
            g[p].dist=d;
            graph[c].push_back(p);
        }
        else{
            g[c].parent=p;
            g[c].dist=d;
            graph[p].push_back(c);
        }
    }
}
//--------------------------------------------------------------

//=============================================================
// reading queries
//=============================================================
void readQ(vector< pair<int,int> > &q)
{
    int M,l,r;
    cin>>M;
    q.resize(M);

    for(int i=0;i<M;++i){
        cin >> l >> r;
        --l;
        --r;
        query[l].push_back(make_pair(r,-1));
        query[r].push_back(make_pair(l,-1));
        q[i]=make_pair(l,r);
    }
}
//--------------------------------------------------------------

int main()
{
    int N;
    cin>>N;

    dsu.resize(N);
    ancestor.resize(N);
    u.resize(N);
    graph.resize(N);

    // reading graph
    vector<EdgeToParent> g;
    readGraph(g,N);

    // reading queries
    vector< pair<int,int> > q;
    readQ(q);

    dfs(root);
    printResults(q,g);

    return 0;
}
