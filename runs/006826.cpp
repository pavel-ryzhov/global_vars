#include <iostream>
#include <vector>
#include <cstdlib>


#define WHITE 0
#define GRAY 1
#define BLACK 2


using namespace std;

class Node
{
public:
    Node(int n, int _l): node_num(n), l(_l) {};
    
    int node_num;
    int l;
};


class Graph
{
    
public:
    Graph(int s): graph(s), size(s), color(s, WHITE), parents(s, 0), in_time(s), out_time(s), root(0) { };
    
    void stdin_build();
    void dfs();
    
    bool upper(int, int);
    int lca(int, int);
    int get_parent(int, int);
    
    int get_path_lenght(int, int);
    
    
private:
    void dfs_visit(int);
    int  get_lenght(int, int);
    
    vector< vector<Node> > graph;
    
    vector<int> color;
    vector<int> parents;
    vector<int> in_time;
    vector<int> out_time;
    
    int time;
    int size;
    int root;
};

int Graph::get_lenght(int a, int b)
{
    for(vector<Node>::iterator it = graph[a].begin(); it != graph[a].end(); it++)
    {
        if(it->node_num == b) return it->l;
    }
    
}


void Graph::stdin_build()
{
    int s, d, l; // source, destination, lenght
    bool root_flag = false;
    
    for ( int i = 0; i < size - 1; i++)
    {
        cin >> s >> d >> l;
        
        
        graph[s-1].push_back(Node(d-1, l));
        graph[d-1].push_back(Node(s-1, l));
        
        /*
        graph[s-1][d-1] = (l == 0 ? -1 : l);
        graph[d-1][s-1] = (l == 0 ? -1 : l);
        
       if(!root_flag) graph[s-1][d-1] = (l == 0 ? -1 : l);
        else graph[d-1][s-1] = (l == 0 ? -1 : l);
        
        if(parents[d-1] == 0) parents[d-1] = s-1;
        else // whoops, we found another root! We need to transpose our graph matrix, add some flag and set new root
        {
            root = d-1;
            root_flag = true;
            
            parents.clear();
            parents.resize(size);
            
            transpose();
        }*/
    } 
}


void Graph::dfs()
{
    time = 0;
    
    dfs_visit(0);
    
}

void Graph::dfs_visit(int u)
{    
    color[u] = GRAY;
    time ++;
    
    in_time[u] = time;
    
    for(vector<Node>::iterator it = graph[u].begin(); it != graph[u].end(); it++)
    {
        if(color[it->node_num] == WHITE)
        {
            parents[it->node_num] = u;
            dfs_visit(it->node_num);
        }
    }
    
    
    /*
    for(int i=0; i < graph[u].size(); i++)
    {
        if(color[i] == WHITE && graph[u][i] != 0)
        {
            parents[i] = u;
            dfs_visit(i);
        }
    }*/
    
    color[u] = BLACK;
    out_time[u] = time;
}

bool Graph::upper(int a, int b)
{
    return in_time[a] <= in_time[b] && out_time[a] >= out_time[b];
}

int Graph::lca(int a, int b)
{
    int l = 1;
    while ((1<<l) <= size) l ++;
    
    int lca = 0;
    if (upper(a, b)) lca = a;
    else if (upper(b, a)) lca = b;
    else
    {
        int p;
        
        for(int i = l; i > 0; i--)
        {
            p = get_parent(a, i);
            
            if(!upper(p, b)) a = p;
        }
        
        lca = parents[a];
    }
    
    return lca;
}

int Graph::get_parent(int a, int b)
{
    int p = a;
    for(int i = 0; i < b; i++) p = parents[p];

    return p;
}

int Graph::get_path_lenght(int a, int b)
{    
    int l = lca(a, b);
    int path = 0;
    
    int a_parent = a, b_parent = b;
    bool a_on_lca = (a == l ? true: false), b_on_lca = (b == l ? true: false);
    
    
    
    while (!(a_on_lca && b_on_lca))
    {
        if(!a_on_lca)
        {
            a_parent = parents[a];
            path += get_lenght(a_parent, a);
            
            if(a_parent == l) a_on_lca = true;
            a = a_parent;
        }
        
        if(!b_on_lca)
        {
            b_parent = parents[b];
            path += get_lenght(b_parent, b);
            
            if(b_parent == l) b_on_lca = true;
            b = b_parent;
        }
        
    }
    
    return path;
}



int main (int argc, const char * argv[])
{ 
    int size = 0;
    cin >> size;
    
    Graph g(size);
            
    g.stdin_build();
    g.dfs();
    
    int M;
    cin >> M;
    
    int s, d; // source, destination
    for ( int i = 0; i < M; i++)
    {
        cin >> s >> d;
        
        cout << g.get_path_lenght(s-1, d-1) << endl;
    }
    
    return 0;
}



