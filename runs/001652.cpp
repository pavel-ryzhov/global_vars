#include <cstdlib>
#include <iostream>
#include <vector>


using namespace std;

typedef vector< pair<int, int>* > p_vector;
typedef vector< p_vector > svector; 
svector tree;
	p_vector test;



 void print(svector vi)
{
	
		for (int i=0; i< vi.size(); i++)
	{
		
		for (int k = 0 ;k<vi[i].size(); k++)
		{
			cout<<i+1<<" "<<vi[i][k]->first<<" "<<vi[i][k]->second<<endl;

		}

	}
}

 void print(p_vector vi)
 {
	 for (int i=0; i<vi.size(); i++)
	 {
		 cout<<vi[i]->first<<" "<<vi[i]->second<<endl;
	 }
 }

vector<bool> used;
vector<int> len;
vector<int> mistake;



 void dfs(int v, int length, int b)
 {
	
	 used[v] = true;
	 mistake[v]=b;
	 len[v]=length;
	// b++;
	 for (p_vector::iterator i=tree[v].begin(); i!=tree[v].end(); ++i)
		 if (!used[(*i)->first])
		 {
			 
			 if ((*i)->second==0) 
			 {
				 
				 (*i)->second=1;
				 dfs ((*i)->first,length+(*i)->second, b+1);

			 }
			 else dfs ((*i)->first,length+(*i)->second, b);
			
		 }
		 
		 
			//cout<<v<<" "<<len[v]<<endl;
 }


 void clear(p_vector &vi)
 {
	 	 for (p_vector::iterator it=vi.begin(); it!=vi.end(); it++) delete (*it);
 }

 void clear(svector &vi)
 {
	 for (svector::iterator it=vi.begin(); it!=vi.end(); it++) clear(*it);
		
 }

int lca(svector &vi, int start, int ends)
 {
	 while (start!=ends)
	 {
		 if (len[start]>len[ends])
		 {
			 for (int i=0; i<vi[start].size(); i++)
				 if (len[vi[start][i]->first]<=len[start])
				 {
					 start=vi[start][i]->first;
					 break;
				 }
		 }
		 else 
		 {
			  for (int i=0; i<vi[ends].size(); i++)
				  if (len[ vi[ends][i]->first ]<=len[ends])
				 {
					 ends=vi[ends][i]->first;
					 break;
				 }

		 }
		
	 } 
	  return start;
 }
 

int main(int argc, char* argv[])
{
	
	//ifstream in("C:\tree.txt");
	//if (!in) cout<<"WRONG!"<<endl;
	int n = 0; 
	cin>>n;

	tree=svector(n+1);
	len=vector<int>(n+1);
	mistake=vector<int>(n+1);
	used = vector<bool>(n+1);
	//test;
	for (int i=0; i<n-1; i++)
	{ 
		int v1=0,v2=0,l=0;
		cin>>v1>>v2>>l;

		pair<int,int>* p1 = new pair<int,int>(v2,l);
		pair<int,int>* p2 = new pair<int,int>(v1,l);
		
		tree[v1].insert(tree[v1].end(), p1);
		tree[v2].insert(tree[v2].end(), p2);
	}
	cin>>n;
	for (int i=0; i<n; i++)
	{
		int v1=0,v2=0;
		cin>>v1>>v2;
		pair<int,int>* p= new pair<int,int>(v1,v2);
		test.insert(test.end(), p);
	}
	
	
	
	
		string result="";

		dfs(1,0,0);
		for (int i=0; i<test.size();i++)
		{
			int startv= test[i]->first;
			int endv = test[i]->second;
			int com=lca(tree, startv, endv);
			long int res= len[startv]-mistake[startv]+len[endv]-mistake[endv]-2*(len[com]-mistake[com]);
			cout<<res<<endl;
		}
		
		 
		 
		 clear(test);
		 clear(tree);
	//system("PAUSE");
	return 0;
}