#include <iostream>
#include <vector>
#include <utility>
using namespace std;

vector<int> *g, *q, *p, *query; // граф, все запросы, цена веток и порядок запросов.
int *dsu, *ancestor;
int *price, *ans;
bool *u;
vector<bool> *o;
int n;				//Number of vertex
int m;				//Number of requests

int dsu_get (int v) {
	return v == dsu[v] ? v : dsu[v] = dsu_get (dsu[v]);
}

void dsu_unite (int a, int b, int new_ancestor) {
	a = dsu_get (a),  b = dsu_get (b);
	dsu[a] = b,  ancestor[b] = new_ancestor;
}
 
int find (int v, int f) {
	for (size_t i = 0; i < q[v].size(); ++i)
	{
		if (q[v][i] == f)
			return i;
	}
	return -1;
}

int findInQuery(int v1, int v2) {
	for (int k = 0; k < m; k++){
		for (int l = 0; l < query[k].size()-1; l++){
			if (query[k][l] == v1 && query[k][l+1] == v2){
				cout<<"k="<<k<<endl;
				cout<<"v1="<<v1<<endl;
				cout<<"v2="<<v2<<endl;
				ans[k] = price[v1]+price[v2]-2*price[ancestor[dsu_get(v2)]];
			}
			if (query[k][l] == v2 && query[k][l+1] == v1){
				cout<<"k="<<k<<endl;
				cout<<"v1="<<v1<<endl;
				cout<<"v2="<<v2<<endl;
				ans[k] = price[v1]+price[v2]-2*price[ancestor[dsu_get(v2)]];
			}
		}
	}
	return -1;
}

void dfs (int v) {
	dsu[v] = v,  ancestor[v] = v;
	u[v] = true;
	for (size_t i=0; i<g[v].size(); ++i)
		if (!u[g[v][i]]) {
			price[g[v][i]] = p[v][i] + price[v];
			dfs (g[v][i]);
			dsu_unite (v, g[v][i], v);
		}
	for (size_t i=0; i<q[v].size(); ++i)
		if (u[q[v][i]] && !o[v][i]) {
			//printf ("%d %d -> %d\n", v+1, q[v][i]+1,
				//ancestor[ dsu_get(q[v][i]) ]+1);
			findInQuery(v, q[v][i]);
			//price[v]+price[q[v][i]]-2*price[ancestor[dsu_get(q[v][i])]]<<endl;
			o[v][i] = true;
			o[ q[v][i] ][ find(q[v][i], v) ] = true;
		}
}

int main() {
        int v1, v2, pr;	//temporary variables, to fill graph
        
        cin>>n;
        ancestor = new int[n];
        dsu = new int[n];
		price = new int[n];
		price[0] = 0;
        u = new bool[n];
        for (int i = 0; i<n; i++)
		{
			ancestor[i] = 0;
			dsu[i] = 0;
			u[i] = false;
		}
		g = new vector<int>[n];
		p = new vector<int>[n];
        for(int i = 0; i < n-1; i++)
        {
            cin>>v1>>v2>>pr;
            v1--;
            v2--;
            //Because array start on 0, but vertices start from 1;
            g[v1].push_back(v2);
			p[v1].push_back(pr);
        }
        cin>>m;
        q = new vector<int>[n];
		o = new vector<bool>[n];
		query = new vector<int>[m];
		ans = new int[m];
		for (int i = 0; i<m; i++)
		{
			ans[i] = 0;
		}
        for(int i = 0; i < m; i++)
        {
                cin>>v1>>v2;
                v1--;
                v2--;
                q[v1].push_back(v2);
                q[v2].push_back(v1);
				query[i].push_back(v1);
				query[i].push_back(v2);
				o[v1].push_back(false);
				o[v2].push_back(false);
        }
		
        for (int i = 0; i < m; i++)
		{
			cout<<"query["<<i<<"] = "<<query[i][0]<<"   ";
			cout<<"query["<<i<<"] = "<<query[i][1]<<endl;
		}
		dfs(0);
		for (int i = 0; i < m; i++)
		{
			cout<<ans[i]<<endl;
		}
		cin>>m;
        return 0;
}