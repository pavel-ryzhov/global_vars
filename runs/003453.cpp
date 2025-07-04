#include <iostream>
#include <vector>
#include <cstdlib>
#include <stack>

class CTree
{
	public:
		CTree(unsigned short n, unsigned short maxN = 41000); 
		int findDist(unsigned short l, unsigned short r) const; //< ����� ���������� ����� ���������
	private:
		std::vector <std::vector <std::pair<unsigned short, unsigned short> > > m_data;
		std::vector <bool> m_visited; //< ������ ���������� ������
		std::vector <unsigned short> m_lvls; //< ������ ������
		std::vector <unsigned short> m_order; //< ������� ������ ������
		std::vector <int> m_first; //< ����� ������ � �������
		std::vector <unsigned short> m_minTree; //< ������ ��������
		std::vector <int> m_toRoot; //< ���������� �� ������� �� �����
		unsigned short m_root; //< ������ �����
		unsigned short m_count; //< ���������� ������

		void build(int i, int l, int r); //< ���������� ������ ��������
		unsigned short findLca(unsigned short l, unsigned short r) const; //< ����� ����������� ������ ������
		unsigned short findMin(int l, int r, int i, int tl, int tr) const; //< ����� �������� �� �������
};




void
CTree::build(int i, int l, int r)
{
	if (l == r) //���� ������� ���������, ������� �� �� - ���� ��������
		m_minTree[i] = m_order[l];
	else 
	{
		//����� ������� �� ��� � ���� �������� �� ���
		int m = (l + r) / 2;
		build(i * 2, l, m); 
		build(i * 2 + 1, m+1, r);
		//������� �� ���� ������� - ������� �� ��������� �� ����������
		if (m_lvls[m_minTree[i * 2]] < m_lvls[m_minTree[i * 2 + 1]])
			m_minTree[i] = m_minTree[i * 2];
		else
			m_minTree[i] = m_minTree[i * 2 + 1];
	}
}

unsigned short
CTree::findMin(int l, int r, int i, int tl, int tr) const
{
	if (l == tl && r == tr) //< ���� ������� ��������� � ��������
		return m_minTree[i]; //< ������ �� ������� - ����
	int m = (tl + tr) / 2;
	if (r <= m) //< ���� ������ ����������� ����� �������� �������
		return findMin(l, r, i*2, tl, m); //< ���� ������� �� ���
	if (l > m) //< ���� ������ ����������� ������ �������� �������
		return findMin(l, r, i*2+1, m+1, tr); //< ���� ������� �� ���
	//���� ������ ����������� ���� ����������
	int a = findMin(l, m, i*2, tl, m);
	int b = findMin(m+1, r, i*2+1, m+1, tr);
	//���� ������� �� ��������� �� ������
	if (m_lvls[a] < m_lvls[b])
		return a;
	else
		return b;
}



unsigned short 
CTree::findLca(unsigned short l, unsigned short r) const
{
	//����� ������� ������� - ����� ������ � ���� �������
	int a = (m_first[l] < m_first[r]) ? m_first[l] : m_first[r];
	//������ ������� ������� - ����� ������ � ������ �������
	int b = (m_first[l] > m_first[r]) ? m_first[l] : m_first[r];
	//���������� ����� ������
	return findMin(a, b, 1, 0, m_order.size() - 1);
}

int
CTree::findDist(unsigned short l, unsigned short r) const
{
	//���������� ���� ��������� - ����� �� ��������� �� ����������� ������ ������
	return m_toRoot[l] + m_toRoot[r] - 2 * m_toRoot[findLca(l, r)];
}



CTree::CTree(unsigned short n, unsigned short maxN)
	: m_data(maxN)
	, m_visited(maxN, false)
	, m_lvls(maxN)
	, m_toRoot(maxN)
	, m_order(0)
	, m_first(maxN)
	, m_root(0)
	, m_count(n)
	, m_minTree(0)
{
	//��������� ����
	unsigned short a(0), b(0), len(0);
	for (int i = 0; i < m_count - 1; ++i)
	{
		std::cin >> a >> b >> len;
		m_data[a].push_back(std::make_pair(b, len));
		m_data[b].push_back(std::make_pair(a, len));
	}
	//����� ������� - ������
	m_root = a;
	//������ � ���� ������, ������ ���������� �������, ���������� �� �����, ������� 
	std::stack <std::pair<std::pair<unsigned short, unsigned short>, std::pair<int, unsigned short> > > st; 
	st.push(std::make_pair(std::make_pair(m_root, m_data[m_root].size() - 1), std::make_pair(0, 0)));
	while (!st.empty())
	{
		unsigned short curVertex = st.top().first.first;
		unsigned short curChild = st.top().first.second;
		int curDist = st.top().second.first;
		unsigned short curLvl = st.top().second.second;
		st.pop();
		
		//���� ������ ��� ������� � �������
		if (!m_visited[curVertex])
		{
			//��������� �������, ���������� �� �����, ����� ������
			m_visited[curVertex] = true;
			m_lvls[curVertex] = curLvl;
			m_toRoot[curVertex] = curDist;
			m_first[curVertex] = m_order.size();

		}
		//���� ��� ���� �������� (������ �������� ������� �� ����������� ����)
		if (!(0 <= curChild && curChild < m_data[curVertex].size()))
		{
			//��������� ������� � ������
			m_order.push_back(curVertex);
			continue;
		}
		unsigned short nextVertex = m_data[curVertex][curChild].first;
		int nextDist = curDist + m_data[curVertex][curChild].second;
		//���������� ������� � ����, �� � ����������� ���-�� ������������ �����
		st.push(std::make_pair(std::make_pair(curVertex, curChild - 1), std::make_pair(curDist, curLvl)));
		//���� ������� ������� ��� ������� (������ �� ������� � �����)
		if (!m_visited[nextVertex])
		{
			//��������� ��� � ��������� � ����
			m_order.push_back(curVertex);
			st.push(std::make_pair(std::make_pair(nextVertex, m_data[nextVertex].size() - 1), std::make_pair(nextDist, curLvl + 1)));
		}
	}
	//������ ������ ��������
	m_minTree.resize(m_order.size() * 4 + 1);
	build(1, 0, m_order.size() - 1);
}



int main()
{
	int n, m, l, r;
	std::cin >> n;
	CTree tree(n);
	std::cin >> m;
	for (int i = 0; i < m; ++i)
	{
		std::cin >> l >> r;
		std::cout << tree.findDist(l, r) << std::endl;
	}
	return 0;
}



