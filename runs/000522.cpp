#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

typedef vector < vector<int> > graph;
typedef vector<int>::const_iterator const_graph_iter;


vector<int> lca_h, lca_dfs_list, lca_first, lca_tree;
vector<char> lca_dfs_used;
graph g,s; //g-основной граф, s-расстояния
vector<int> query_nodes_from;
vector<int> query_nodes_to;

template <typename T>
string toString(T val)
{
    ostringstream oss;
    oss<< val;
    return oss.str();
}

template<typename T> 
T fromString(const string& s) 
{
  istringstream iss(s);
  T res;
  iss >> res;
  return res;
}

void lca_dfs (int v, int h = 0)
{
	lca_dfs_used[v] = true;
	lca_h[v] = h;
	lca_dfs_list.push_back (v);
		for (unsigned int i=0;i<g[v].size();i++)
		if (!lca_dfs_used[g[v][i]])
		{
			lca_dfs (g[v][i], h+s[v][i]);
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

void lca_prepare ()
{
	int n = (int) g.size();
	lca_h.resize (n);
	lca_dfs_list.reserve (n*2);
	lca_dfs_used.assign (n, 0);

	lca_dfs (0);

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

	if (left > right) {
		int temp=left;
		left=right;
		right=temp;
	}
	return lca_tree_min (1, 0, (int)lca_dfs_list.size()-1, left, right);
}

int read_from_file(){

		int i,j;
		
		string buf;
				
		getline(cin,buf);
		int num_of_nodes=fromString<int>(buf);
		g.resize(num_of_nodes);
		s.resize(num_of_nodes);
		
		for(j=0;j<num_of_nodes-1;j++){
		   
		   getline(cin,buf);
		   
		   int pos=buf.find(" ");
		   string buf2=buf.substr(0,pos);
		   int from_node=fromString<int>(buf2)-1;
		   buf=buf.substr(pos+1);
		   pos=buf.find_first_not_of(" ");
		   buf=buf.substr(pos);
		   pos=buf.find(" ");
		   buf2=buf.substr(0,pos);
		   int to_node=fromString<int>(buf2)-1;
           buf=buf.substr(pos+1);
		   pos=buf.find_first_not_of(" ");
		   buf=buf.substr(pos);
		   pos=buf.find(" ");
		   buf2=buf.substr(0,pos);
		   if(from_node>to_node){
              int temp=from_node;
			  from_node=to_node;
			  to_node=temp;
		   }
		   g[from_node].push_back(to_node);
		   s[from_node].push_back(fromString<int>(buf2));   
		}


        getline(cin,buf);

		int num_of_results=fromString<int>(buf);
		     
		for(i=0;i<num_of_results;i++){

		   getline(cin,buf);

           int pos=buf.find(" ");
		   string buf2=buf.substr(0,pos);
		   query_nodes_from.push_back(fromString<int>(buf2)-1);
		   buf=buf.substr(pos+1);
		   pos=buf.find_first_not_of(" ");
		   buf=buf.substr(pos);
		   pos=buf.find(" ");
		   buf2=buf.substr(0,pos);
		   query_nodes_to.push_back(fromString<int>(buf2)-1);
        }

		return 0;
	}

int main()
{
	read_from_file();
    
	/* cout<<"g:"<<endl<<endl;

	for (int k=0;k<g.size();k++){
       for (int m=0;m<g[k].size();m++){
		   cout<<g[k][m]<<" ";
	   }
	   cout<<endl;
	}
    
    cout<<"s:"<<endl<<endl;

	for (int k=0;k<s.size();k++){
       for (int m=0;m<s[k].size();m++){
		   cout<<s[k][m]<<" ";
	   }
	   cout<<endl;
	} */




	lca_prepare ();

	for (unsigned int i=0;i<query_nodes_from.size();i++)
	{

		int v = lca (query_nodes_from[i], query_nodes_to[i]); // наименьший общий предок
		//cout<<" from "<< query_nodes_from[i]<<" to "<< query_nodes_to[i]<<" lca = "<<v<<endl; 
		int h=lca_h[query_nodes_from[i]]+lca_h[query_nodes_to[i]]-2*lca_h[v];
		cout<<h<<endl;
	}
}