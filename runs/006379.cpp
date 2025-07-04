#include <iostream>
#include <vector>

using namespace std;

vector < vector<int> > g,r; // g - граф, r - длины ребер графа
vector < vector<int> > up;
vector<int> tin, tout;
vector<char> used;

void dfs(int v,const int l,int p=0)
{    static int timer;
	used[v]=true;
	tin[v]=++timer;
	up[v][0]=p;
	for(int i=1; i<=l; ++i)
	   up[v][i]=up[up[v][i-1]][i-1];
	for(size_t i=0; i<g[v].size(); ++i)
     {
	   int to=g[v][i];
	   if(!used[to])
		 dfs(to,l,v);
	} /* i */
	tout[v]=++timer;
} /* dfs */
/***************************************************************************/

bool upper (int a,int b)
{
	return tin[a] <= tin[b] && tout[a] >= tout[b];
} /* upper */
/***************************************************************************/

int lca(int a,int b,const int l)
{    
	if(upper(a,b)) return a;
	if(upper(b,a)) return b;
	for(int i=l; i>=0; --i)
	   if(! upper(up[a][i],b))
		 a=up[a][i];
	return up[a][0];
} /* lca */
/***************************************************************************/

// Расчет длины перехода в графе
long GetLength(int start,int finish)
{    int i;
	long length=0;
	/**********************************************************************/
     if(start==finish)
        return 0;
     do
     {
        for(i=0; g[i][start]!=start; i++);
        length+=r[i][start];
        start=i;
        //cout<<start+1<<" ";
     } while (start!=finish);
     //cout<<endl;
     return length;
} /* GetLength */
/***************************************************************************/

int main()
{    int i,j,k;        // переменные циклов
	int a,b;          // текущий запрос (номера вершин)
     int l;
     int n,m;          // n - число вершин, m - число запросов
	int commonParent; // наименьший общий предок
     long *length;      // конечная длина перехода в графе
     /**********************************************************************/
     cin>>n;
     g.resize(n); r.resize(n);
     used.resize(n),  tin.resize(n),  tout.resize(n),  up.resize(n);

     for(i=0;i<n;i++)
     {
        g[i].resize(n);
        r[i].resize(n);
        for(j=0;j<n;j++)
        {
           g[i][j]=0;
           r[i][j]=0;
        } /* j */
     } /* i */

     // чтение информации о ребрах графа
     for(k=0;k<n-1;k++)
     {
        cin>>i>>j;
        i--; j--;
        g[i][j]=j;
        cin>>r[i][j];
     } /* k */

     // препроцессинг
     l=1;
     while((1<<l) <= n)
        ++l;
     for(i=0; i<n; ++i)
        up[i].resize(l+1);
     dfs(0,l);

     // обработка запросов
     cin>>m;
     length=new long[m];
     for(i=0;i<m;i++)
     {
          cin>>a>>b;
          a--; b--;
          commonParent=lca(a,b,l); // ответ на запрос
          //cout<<commonParent+1<<endl;
          length[i]=GetLength(a,commonParent)+GetLength(b,commonParent);
          //cout<<endl<<"Length: "<<length<<endl;
     }
     for(i=0;i<m;i++)
        cout<<length[i]<<endl;
     delete[] length;
     return 0;
} /* main */
/***************************************************************************/
