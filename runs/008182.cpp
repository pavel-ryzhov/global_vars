#include <vector>
#include <iostream>
#include <map>

using namespace std;

//������� � 4
//��� ����������� ����� � �������, ����������� ������ ������� (���� �� ������� ��� �������)


typedef vector < vector<int> > graph;
typedef vector<int>::const_iterator const_graph_iter;

vector<char> used;
vector<int> way;

map<pair<int, int>, int> query; //��� �������
vector<pair<int, int> > query_list; //��� ������� �� �������


char build_way(const graph & g, const graph & ribs, int & r, int v1, int v2)
{
	//��� � � ������ � ������� ���������� �� ����� �����
	// �� � ���� ��� � ������� way ��������� ����, ��� �� ��� �� v1 � v2
	used[v1] = true;
	way.push_back(v1);
	for (const_graph_iter i = g[v1].begin(); i != g[v1].end(); ++i)
		if(v1 != v2) //���� ����� �� ����������� �������, ������������
		{
			if (!used[*i])
			{
				char f = build_way(g, ribs, r, *i, v2);
				if(!f && way[way.size()-2] == v1)
					way.pop_back();
				if(f)
				{
					//������� ��������� ������ ����������
					r += ribs[v1][i-g[v1].begin()];
					map<pair<int, int>, int>::iterator it = query.find(make_pair(v2, v1));
					if(it != query.end())
					{
						(*it).second = r;
					}
					return true;
				}
			}
		}
		else
			return true;
	return false;
}

int main()
{
	graph g, ribs;
	
	//������ ����
	unsigned nSize;

	cin >> nSize;
	g.reserve(nSize); 

	vector<int> t;
	g.assign(nSize, t);
	ribs.assign(nSize, t);

		for(unsigned i=0; i<nSize-1; i++)
	{
		int nT0, nT1, nT2;
		cin >> nT0 >> nT1 >> nT2;

		g[--nT0].push_back(--nT1);
		g[nT1].push_back(nT0);
		ribs[nT0].push_back(nT2);
		ribs[nT1].push_back(nT2);
	}

	//��������� ����������
	cin >> nSize;
	query_list.reserve(nSize);
	for (unsigned i=0; i<nSize; i++)
	{
		int v1, v2; // �������� ������
		cin >> v1 >> v2;
		if(--v1 < --v2)
		{
			query_list.push_back(make_pair(v1, v2));
			query.insert(make_pair(make_pair(v1, v2), -1));
		}
		else
		{
			query_list.push_back(make_pair(v2, v1));
			query.insert(make_pair(make_pair(v2, v1), -1));
		}
	}

	for(unsigned i=0; i<nSize; i++) //����� ����������
	{
		int v=0;
		way.clear();
		used.assign(g.size(), false);

		map<pair<int, int>, int>::iterator it = query.find(make_pair(query_list[i].first, query_list[i].second));
		if((*it).second == -1)
		{
			//������ ������
			build_way(g, ribs, v, query_list[i].second, query_list[i].first);
			cout << v << endl;
		}
		else
			cout << (*it).second << endl;
	}
	return 0;
}