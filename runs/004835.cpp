#include <cstdlib>
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

typedef vector < vector<pair<int, int> > > graph;



typedef vector<pair<int, int> >::const_iterator const_graph_iter;



vector<int> lca_h, lca_dfs_list, lca_first, lca_tree;
vector<char> lca_dfs_used;
vector < vector<unsigned short int> > edges ;  // ������ ��������� ������ � ������
//map <string, int> e; 
map <unsigned int, int> e; 



void lca_dfs (const graph & g, int v, int h = 1)
{
	lca_dfs_used[v] = true;
	lca_h[v] = h;
	lca_dfs_list.push_back (v);
	for (const_graph_iter i = g[v].begin(); i != g[v].end(); ++i)
		if (!lca_dfs_used[(*i).first])
		{
			lca_dfs (g, (*i).first, h+1);
			lca_dfs_list.push_back (v);
		}
}

void lca_build_tree (int i, int l, int r)
{
	if (l == r)
		lca_tree[i] = lca_dfs_list[l];
	else
	{
		int m = (l + r) >> 1;
		lca_build_tree (i+i, l, m);
		lca_build_tree (i+i+1, m+1, r);
		if (lca_h[lca_tree[i+i]] < lca_h[lca_tree[i+i+1]])
			lca_tree[i] = lca_tree[i+i];
		else
			lca_tree[i] = lca_tree[i+i+1];
	}
}

void lca_prepare (const graph & g, int root)
{
	int n = (int) g.size();
	lca_h.resize (n);
	lca_dfs_list.reserve (n*2);
	lca_dfs_used.assign (n, 0);

	lca_dfs (g, root);
    
	int m = (int) lca_dfs_list.size();
	lca_tree.assign (lca_dfs_list.size() * 4 + 1, -1);
	lca_build_tree (1, 0, m-1);

	lca_first.assign (n, -1);
	for (int i = 0; i < m; ++i)
	{
		int v = lca_dfs_list[i];
		if (lca_first[v] == -1)
			lca_first[v] = i;
	}
}

int lca_tree_min (int i, int sl, int sr, int l, int r)
{
	if (sl == l && sr == r)
		return lca_tree[i];
	int sm = (sl + sr) >> 1;
	if (r <= sm)
		return lca_tree_min (i+i, sl, sm, l, r);
	if (l > sm)
		return lca_tree_min (i+i+1, sm+1, sr, l, r);
	int ans1 = lca_tree_min (i+i, sl, sm, l, sm);
	int ans2 = lca_tree_min (i+i+1, sm+1, sr, sm+1, r);
	return lca_h[ans1] < lca_h[ans2] ? ans1 : ans2;
}

int lca (int a, int b)
{
	int left = lca_first[a],
		right = lca_first[b];
	if (left > right)  swap (left, right);
	return lca_tree_min (1, 0, (int)lca_dfs_list.size()-1, left, right);
}

int lspl_to_lca(int lca, int v, const graph & g) // ���������� ����� ����������� ���� �� ������� �� �� LCA
{
	int left = lca_first[lca];
	int right = lca_first[v];
	if (left > right)  swap (left, right);

	stack< pair<int, int> > path_stack;
	pair<int, int> p;

	int lspl = 0;
	for (int i = left; i < right; i++)
	{
		p.first = lca_dfs_list[i];
		p.second = lca_dfs_list[i + 1];
		
		if (!path_stack.empty())
		{
			pair<int, int> p2(p.second, p.first);
			if (path_stack.top() == p2) path_stack.pop();
			else path_stack.push(p);
		}
		else path_stack.push(p);
	}	
	while (!path_stack.empty())
	{
		//lspl += edges[path_stack.top().first][path_stack.top().second];
		
		/*ostringstream stm1, stm2;
		int v1 = path_stack.top().first; 
		int v2 = path_stack.top().second;
			
		stm2 << v2;
		string sv2 = stm2.str();
		
		lspl += e[(int)(v1 * pow((double)10, (double)sv2.length()) + (v2))];
		path_stack.pop();*/
		
		int v1 = path_stack.top().first; 
		int v2 = path_stack.top().second;
        
        int s1 = g[v1].size();
        int s2 = g[v2].size();
        
        if (s1 < s2)
        {
    		for (int i = 0; i < s1; i++)
    		{
    			if (g[v1][i].first == v2)
    			{
    				lspl += g[v1][i].second;
    				path_stack.pop();
    				break;
    			}
    		}
        }
        else 
        {
            for (int i = 0; i < s2; i++)
    		{
    			if (g[v2][i].first == v1)
    			{
    				lspl += g[v2][i].second;
    				path_stack.pop();
    				break;
    			}
    		} 
        }
	}
	
	
	return lspl;
}



int main(int argc, char *argv[])
{
	int v1, v2;
	int i, length;
	
	graph g;  // ������� ��������� �����
	int root; // ������ ������
	int n;    // ���������� ������ � �����e
	//vector<int> e; // ����� �����
	int m; // ���������� ��� ������, ��� ������� ����� ����� ����� ����������� ����
    vector < vector<int> > pairs; // ������ ������, ����� �������� ���������� ��������� ����������     
    
	// ��������� ����� ������
    cin >> n;
   
    for (i = 0; i < n; i++) 
	{
		g.push_back(vector<pair<int, int> >(1, pair<int, int>(-1, 0)));
		//edges.push_back(vector<unsigned short int>(n, 0));
	} 
    
    // ��������� ������ � ����� � ����� �����
	if (n > 1)
	{
		for (i = 0; i < n - 1; i++)
		{
			ostringstream stm1, stm2;
			cin >> v1 >> v2 >> length;

			//edges[v1 - 1][v2 - 1] = length;
			//edges[v2 - 1][v1 - 1] = length;
            			
			//stm1 << v1 - 1;
			//string sv1 = stm1.str();
			
			//stm2 << v2 - 1;
			//string sv2 = stm2.str();			

			//e[(v1 - 1) * pow((double)10, (double)sv2.length()) + (v2 - 1)] = length;
			//e[(v2 - 1) * pow((double)10, (double)sv1.length()) + (v1 - 1)] = length;
            
			if (g[v1 - 1][0].first == -1) { g[v1 - 1][0].first = v2 - 1; g[v1 - 1][0].second = length; }
			else g[v1 - 1].push_back(pair<int, int>(v2 - 1, length));
		
			if (g[v2 - 1][0].first  == -1) { g[v2 - 1][0].first  = v1 - 1; g[v2 - 1][0].second = length; }
			else g[v2 - 1].push_back(pair<int, int>(v1 - 1, length));
		}
	}
	else 
	{
		g[0][0].first = 0;
		g[0][0].second = 0;
	}
	
        
     // ��������� ���������� ��� ������, ��� ������� ����� ����� ����� ����������� ����
    cin >> m;

    // ��������� ������ pairs �������� (m x 2) ������    
    for (i = 0; i < m; i++) pairs.push_back(vector<int>(2, 0));
    
     // ��������� ������ � ����� � ����� �����
    for (i = 0; i < m; i++)
    {
        cin >> pairs[i][0] >> pairs[i][1];
    }

    root = 0; // ����� �������� �������

	lca_prepare (g, root);
   	
    for (i = 0; i < m; i++)
	{
		int lca_v = lca(pairs[i][0] - 1, pairs[i][1] - 1); // ������� LCA ��� ���� ������
		cout << abs(lspl_to_lca(lca_v, pairs[i][0] - 1, g) + lspl_to_lca(lca_v, pairs[i][1] - 1, g)) << endl; 
	}

	//system("PAUSE");
    return EXIT_SUCCESS;
}
