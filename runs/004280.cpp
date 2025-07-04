//=============================================================
//  The program finds a distance between two nodes in a tree.
//  It uses Tarjan algorithm to find the least common ancestor.
//
//=============================================================
#include <vector>
#include <list>
#include <iostream>
#include <map>
#include <utility>
#include <cstdlib>
#include <fstream>
#include <algorithm>
//#define DEBUG
using namespace std;

//=============================================================
// Globals
//=============================================================
struct EdgeToParent{
    int parent;
    int dist;
};

void reverse(int v, vector<EdgeToParent> &g);
vector< list<int> > graph; 			//g[i] contains a list of children 
map< int,vector< pair<int,int> > > query;	//query[v] contains vector of pairs (u,lca) if exists query v u
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
// and finds lca of vertexes in queries
//=============================================================
void dfs (int v) {
        dsu[v] = v;
        ancestor[v] = v;
        u[v] = true;

        for (list<int>::const_iterator it=graph[v].begin(); it!=graph[v].end(); ++it){
                if (!u[*it]) {
                        dfs(*it);
                        dsu_unite(v, *it, v);
                }
            }
        for (size_t i=0; i<query[v].size(); ++i)
                if (u[query[v][i].first]) {
                        query[v][i].second=ancestor[ dsu_get(query[v][i].first) ];
                }
}
//--------------------------------------------------------------

//=============================================================
// returns id of the LCA(:
//=============================================================
int findLCA(int v, int u)
{
    int tmp;
    for(unsigned int i=0; i<query[v].size();++i){
        if(query[v][i].first==u) tmp=query[v][i].second;
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

    for(unsigned int i=0;i<q.size();++i){
        v=q[i].first;
        u=q[i].second;
        lca=findLCA(v,u);
        cout<<distance(lca,v,g)+distance(lca,u,g)<<endl;
    }
}
//--------------------------------------------------------------

//=============================================================
// Reading graph.
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
        root=p;			//first scanned node will be the root
        g[p].parent=p;
        g[p].dist=0;
        g[c].parent=p;
        g[c].dist=d;
        graph[p].push_back(c);
    }

    for(int i=1;i<N-1;++i){
        cin >> p >> c >> d;
        --p;
        --c;

        if(g[p].parent==-1 || g[p].parent==p){ //if "p" wasnt inserted yet or it is the root of a tree in the forest, then node "c" shall become the parent root for "p"
            g[p].parent=c;
            g[p].dist=d;
            graph[c].push_back(p);
            if(g[c].parent==-1){	//if "c" is inserting first time we shall mark, that its a root in a tree in the forest
                g[c].parent=c;
                g[c].dist=0;}
        }
        else {
            if(g[c].parent!=c &&g[c].parent!=-1){  //if we have to connect two nodes, that are already have parents, then we shall invert one tree
                reverse(c,g);
                g[c].parent=p;
                g[c].dist=d;
                graph[p].push_back(c);
            }
            else {
                g[c].parent=p;
                g[c].dist=d;
                graph[p].push_back(c);
            }
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

//=============================================================
//correcting adjancy list during inverting the tree
//=============================================================
void correctGraph(int c,int p)
{
    graph[c].push_back(p);
    list<int>::iterator it=find(graph[p].begin(),graph[p].end(),c);
    graph[p].erase(it);
}
//--------------------------------------------------------------

//=============================================================
// Reverse the tree. Just like inverting a linked list.
// After reversing node v will become the root.
//=============================================================
void reverse(int v, vector<EdgeToParent> &g)
{
     int cur=v, parent_new=v, dist_new=0, parent_old,dist_old;
     bool done=false;

     while(!done){
         if(g[cur].parent==cur) done=true;
         parent_old=g[cur].parent;
         dist_old=g[cur].dist;
         g[cur].parent=parent_new;
         g[cur].dist=dist_new;
         if(!done) correctGraph(cur,parent_old);
         parent_new=cur;
         cur=parent_old;
         dist_new=dist_old;
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

