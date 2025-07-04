#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class c_Graph
{
private:
	vector< vector <pair<int,int> > > m_graph;
	vector<int> m_lenth;
	vector<bool> m_used;
	bool m_run;
	int m_way;
	vector<pair<int,int> > m_finds_point;
public:
	c_Graph()
	{
		m_run = true, m_way = 0;
	}
	void find_lenth();
	void find_graph(int v, int finish, int lastleng);
	void set_data();
	void get_data();
	void clear_data();
};

void c_Graph::set_data()
{
	int count_top = 0;

	cin>>count_top;

	for(int i=0;i<count_top;++i){
		vector<pair<int,int> > vec;
		m_graph.push_back(vec);
	}
	
	for(int i=0;i<count_top-1; ++i){
		int num_top = 0;
		pair<int, int> buf_pair1,buf_pair2;
		cin>>num_top>>buf_pair1.first>>buf_pair1.second;

		buf_pair1.first--;

		buf_pair2.first = num_top-1;
		buf_pair2.second = buf_pair1.second;

		m_graph.at(num_top-1).push_back(buf_pair1);
		m_graph.at(buf_pair1.first).push_back(buf_pair2);
	}

	cin>>count_top;
	
	for(int i=0;i<count_top; ++i){
		pair<int,int> pair;
		cin>>pair.first;
		cin>>pair.second;
		pair.first--;
		pair.second--;
		m_finds_point.push_back(pair);
	}

	for(int i=0;i<m_graph.size();++i)
		m_used.push_back(false);

}

void c_Graph::get_data()
{
	for(int i=0;i<m_lenth.size();++i)
		cout<<m_lenth.at(i)<<"\n";
}
void c_Graph::clear_data()
{
	for(int i=0;i<m_graph.size();++i)
		m_used.at(i)=false;
	m_way = 0;
	m_run = true;
}

void c_Graph::find_lenth()
{	
	for(int i=0; i<m_finds_point.size();++i){
		find_graph(m_finds_point.at(i).first,m_finds_point.at(i).second,0);
		clear_data();
	}
}

void c_Graph::find_graph(int v, int finish, int lastleng)
{
	if(v == finish){
		m_lenth.push_back(m_way);
		m_run = false; 
	}

	if(m_run){
		m_used[v]=true;
		for(int i=0; i<m_graph[v].size();++i){
			int CurrentNode = m_graph[v][i].first;
			if(!m_used[CurrentNode]){
				m_way += m_graph[v][i].second;
				find_graph(CurrentNode,finish,m_graph[v][i].second);
			}
		}
		m_way -= lastleng;
	}
}

int main()
{
	c_Graph g;
	g.set_data();
	g.find_lenth();
	g.get_data();

	char ch = cin.get();

	return 0;
}