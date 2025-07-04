#include <iostream>
#include <vector>
#include <algorithm>

typedef unsigned short node;						//вершина дерева
typedef std::vector<std::vector<std::pair<node, unsigned short> > > tree;
													//собственно дерево

class Tree_Info
{													//информация о дереве и методы работы с ней
														
	std::vector<std::vector<int> > m_reverse_sparse;//вспомогательная таблица для быстрого поиска по алгоритму Фарах-Колтона и Бендера
	
	std::vector<node>m_bypass,						//вектор обхода дерева
					 m_first;						//вектор индексов вершин дерева в предыдущем векторе

	std::vector<unsigned int> m_heights,			//высоты вершин относительно корня
					 m_degrees;						//вектор ближайших верхних степеней двойки 

	void fillBypass(const tree& t, node i = 0, unsigned int h = 0)
	{												//рекуррентная функция, передаётся дерево t (чтобы не хранить в классе), 
													//номер очередной вершины i и текущая высота h
		m_bypass.push_back(i);
		m_heights[i] = h;
		m_first[i] = m_bypass.size() - 1;
		std::vector<std::pair<node, unsigned short> >::const_iterator iter = t[i].begin(),
																	  iter_end = t[i].end();
		for(; iter != iter_end; ++iter)
		{
			if (m_heights[iter->first] == -1)		//проверка, записана ли информация об очередной вершине
			{
				fillBypass(t, iter->first, h + iter->second);
				m_bypass.push_back(i);
			}
		}
	}

public:
	void preprocess(const tree& t)
	{
		int m_count = t.size();
		m_bypass.reserve(2*m_count);
		m_heights.assign(m_count, -1);
		m_first.resize(m_count);
		fillBypass(t);

		int bpSize = m_bypass.size();
		int logSize = 0;
		while (1 << ++logSize < bpSize);
		m_reverse_sparse.resize(logSize);

		m_reverse_sparse[0].reserve(bpSize);
		std::vector<node>::const_iterator	iter = m_bypass.begin(),
											iter_end = m_bypass.end();
		for (; iter != iter_end; ++iter)
			m_reverse_sparse[0].push_back(m_heights[*iter]);

		for (int i = 0; i < logSize - 1; ++i)
		{
			m_reverse_sparse[i + 1].assign(bpSize, 0);
			for (int j = 0; j + (1 << i) < bpSize; ++j)
			{
				m_reverse_sparse[i + 1][j] = std::min(m_reverse_sparse[i][j], m_reverse_sparse[i][j + (1 << i)]);
			}
		}

		m_degrees.resize(bpSize);
		for (int i = 0, j = 0; i < bpSize; ++i) 
		{
			if (1 << (j + 1) <= i) 
				++j;
			m_degrees[i] = j;
		}
	}

	int getWayCost(node lhs, node rhs) const
	{												//получить длину кратчайшего пути как сумма расстояний вершин от их ближайшего общего предка
		node l = m_first[lhs],
			 r = m_first[rhs];

		if (l > r)
			std::swap(l, r);
		
		int d = m_degrees[r - l + 1],
			min = std::min(m_reverse_sparse[d][l], m_reverse_sparse[d][r - (1 << d) + 1]);

		return  m_heights[lhs] + m_heights[rhs] - 2 * min;
	}
};


int main()
{
	tree t;
	int count, height;
	node lhs, rhs;

	std::cin >> count;
	t.resize(count--);

	for (int i = 0; i < count;)
	{
		std::cin >> lhs >> rhs >> height;
		if (--lhs == --rhs)							//Превращение интервала [1; N] в [0; N - 1]
			std::cout << "Rewrite tree edge info #" << i + 1 << std::endl;
		else 
		{
			t[lhs].push_back(std::make_pair(rhs, height) );
			t[rhs].push_back(std::make_pair(lhs, height) );
			++i;
		}
	}

	Tree_Info g;
	g.preprocess(t);	
	std::cin >> count;

	for (int i = 0; i < count; ++i)
	{
		std::cin >> lhs >> rhs;
		if (--lhs == --rhs)							//Превращение интервала [1; N] в [0; N - 1]
			std::cout << '0';
		else
			std::cout << g.getWayCost(lhs, rhs);
		std::cout << std::endl;
	}
	std::cin.ignore(std::cin.rdbuf()->in_avail(), '\n');
	std::cin.get();
	return 0;
}