#include <iostream>
#include <vector>
#include <cstdlib>
#include <stack>

class CTree
{
	public:
		CTree(unsigned short n, unsigned short maxN = 41000); 
		int findDist(unsigned short l, unsigned short r) const; //< поиск расстояния между вершинами
	private:
		std::vector <std::vector <std::pair<unsigned short, unsigned short> > > m_data;
		std::vector <bool> m_visited; //< список посещенных вершин
		std::vector <unsigned short> m_lvls; //< уровни вершин
		std::vector <unsigned short> m_order; //< порядок обхода вершин
		std::vector <int> m_first; //< время захода в вершины
		std::vector <unsigned short> m_minTree; //< дерево отрезков
		std::vector <int> m_toRoot; //< расстояние от вершины до корня
		unsigned short m_root; //< индекс корня
		unsigned short m_count; //< количество вершин

		void build(int i, int l, int r); //< построение дерева отрезков
		unsigned short findLca(unsigned short l, unsigned short r) const; //< поиск наименьшего общего предка
		unsigned short findMin(int l, int r, int i, int tl, int tr) const; //< поиск минимума на отрезке
};




void
CTree::build(int i, int l, int r)
{
	if (l == r) //если отрезок единичный, минимум на нём - само значение
		m_minTree[i] = m_order[l];
	else 
	{
		//делим отрезок на два и ищем минимумы на них
		int m = (l + r) / 2;
		build(i * 2, l, m); 
		build(i * 2 + 1, m+1, r);
		//минимум на всем отрезке - минимум из минимумов на половинках
		if (m_lvls[m_minTree[i * 2]] < m_lvls[m_minTree[i * 2 + 1]])
			m_minTree[i] = m_minTree[i * 2];
		else
			m_minTree[i] = m_minTree[i * 2 + 1];
	}
}

unsigned short
CTree::findMin(int l, int r, int i, int tl, int tr) const
{
	if (l == tl && r == tr) //< если отрезок совпадает с запросом
		return m_minTree[i]; //< миниму на отрезке - отве
	int m = (tl + tr) / 2;
	if (r <= m) //< если запрос принадлежит левой половине отрезка
		return findMin(l, r, i*2, tl, m); //< ещем минимум на ней
	if (l > m) //< если запрос принадлежит правой половине отрезка
		return findMin(l, r, i*2+1, m+1, tr); //< ещем минимум на ней
	//если запрос принадлежит обем половинкам
	int a = findMin(l, m, i*2, tl, m);
	int b = findMin(m+1, r, i*2+1, m+1, tr);
	//ищем минимум из минимумов на каждой
	if (m_lvls[a] < m_lvls[b])
		return a;
	else
		return b;
}



unsigned short 
CTree::findLca(unsigned short l, unsigned short r) const
{
	//левая граница запроса - время захода в одну вершину
	int a = (m_first[l] < m_first[r]) ? m_first[l] : m_first[r];
	//правая граница запроса - время захода в другую вершину
	int b = (m_first[l] > m_first[r]) ? m_first[l] : m_first[r];
	//наименьший общий предок
	return findMin(a, b, 1, 0, m_order.size() - 1);
}

int
CTree::findDist(unsigned short l, unsigned short r) const
{
	//расстояние межу вершинами - сумма их растояний до наименьшего общего предка
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
	//считываем граф
	unsigned short a(0), b(0), len(0);
	for (int i = 0; i < m_count - 1; ++i)
	{
		std::cin >> a >> b >> len;
		m_data[a].push_back(std::make_pair(b, len));
		m_data[b].push_back(std::make_pair(a, len));
	}
	//любая вершина - корень
	m_root = a;
	//кладем в стек корень, индекс последнего ребенка, расстояние до корня, уровень 
	std::stack <std::pair<std::pair<unsigned short, unsigned short>, std::pair<int, unsigned short> > > st; 
	st.push(std::make_pair(std::make_pair(m_root, m_data[m_root].size() - 1), std::make_pair(0, 0)));
	while (!st.empty())
	{
		unsigned short curVertex = st.top().first.first;
		unsigned short curChild = st.top().first.second;
		int curDist = st.top().second.first;
		unsigned short curLvl = st.top().second.second;
		st.pop();
		
		//если первый раз заходим в вершину
		if (!m_visited[curVertex])
		{
			//сохраняем уровень, расстояние до корня, время захода
			m_visited[curVertex] = true;
			m_lvls[curVertex] = curLvl;
			m_toRoot[curVertex] = curDist;
			m_first[curVertex] = m_order.size();

		}
		//если все дети посещены (индекс текущего ребенка не пренадлежит отцу)
		if (!(0 <= curChild && curChild < m_data[curVertex].size()))
		{
			//учитываем вершину в обходе
			m_order.push_back(curVertex);
			continue;
		}
		unsigned short nextVertex = m_data[curVertex][curChild].first;
		int nextDist = curDist + m_data[curVertex][curChild].second;
		//возвращаем вершину в стек, но с уменьшенным кол-во непройденных детей
		st.push(std::make_pair(std::make_pair(curVertex, curChild - 1), std::make_pair(curDist, curLvl)));
		//если ребенок вершина еще пройден (защита от подъема к корню)
		if (!m_visited[nextVertex])
		{
			//учитываем его и добавляем в стек
			m_order.push_back(curVertex);
			st.push(std::make_pair(std::make_pair(nextVertex, m_data[nextVertex].size() - 1), std::make_pair(nextDist, curLvl + 1)));
		}
	}
	//строим дерево отрезков
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



