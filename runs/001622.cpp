#include <cstdlib>
#include <iostream>
#include <vector>
#include <stack>
#include <fstream>


using namespace std;

typedef vector< pair<int, int>* > p_vector;
typedef vector< p_vector > svector; 



/* void print(int i)
{
	stack<int> st;
	
	for (i; i>0; i--)
	{
		st.push(i);
	}
	while (st.size()) 
	{
		cout<<st.top()<<endl;
		st.pop();
	}
}*/
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

 void DeleteRib(svector &vi, int cur, int old)
 {
			 for (p_vector::iterator it=vi[cur].begin(); it!=vi[cur].end(); it++)
					{
						if( (*it)->first==old) 
						{
							vi[cur].erase(it);
							break;
						}
						
					}
 }

 void clear(p_vector &vi)
 {
	 	 for (p_vector::iterator it=vi.begin(); it!=vi.end(); it++) delete (*it);
 }

 void clear(svector &vi)
 {
	 for (svector::iterator it=vi.begin(); it!=vi.end(); it++) clear(*it);
		
 }
 

int main(int argc, char* argv[])
{
	//ifstream in("C:\tree.txt");
	//if (!in) cout<<"WRONG!"<<endl;
	int n = 0; 
	cin>>n;
	svector tree(n+1);
	p_vector test;
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
	
	//in.close();
		cout<<endl;

		stack<pair<int,int>*> path;
		//print(tree);
		//print(test);
		system("CLS");
		svector SavedTree = tree;
		//cout<<" size "<<tree[1][0].first<<endl;

		 for (int i=0; i<test.size();i++)
		{
			
			tree=SavedTree;
			int startv= test[i]->first;
			int endv = test[i]->second;
			int cur = startv;
			int old = startv;
			//tree[startv-1].erase(tree[startv-1].begin());
			//pair<int,int>* p = new pair<int,int>(cur,0);
			path.push(new pair<int,int>(cur,0));
			int length=0;
			
			

			while (path.top()->first!=endv)
			{
				if (tree[cur].size()>0)
				{
					old=cur;
					path.push(tree[cur][0]);
					cur=tree[cur][0]->first;
					
					DeleteRib(tree, cur, old);
					DeleteRib(tree, old, cur);
				}
				else
				{
					path.pop();
					cur=path.top()->first;
				}
				
			}
			int* l = new int;
			*l=0;
			//cout<<*l<<endl;
 			while (path.size()) 
			{
				//cout<<path.top()->first<<"->";
				*l+=path.top()->second;
				//delete path.top();
				path.pop();
			}
			
			cout<<*l<<endl;
			delete l;
			
		}
		 
		 clear(test);
		 clear(tree);
		// time = clock()-time;
		// cout<<endl<< time<<" time "<<endl;

	//print(10000);
	
	
	//system("PAUSE");
	return 0;
}