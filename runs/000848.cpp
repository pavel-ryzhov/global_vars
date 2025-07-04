/*
	���������� �������� � ������������ ������:
	������ m_Up ��������� �������� N * N ������ N * logN
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <cmath>

// ������� ������ ���������
template<typename T>
struct GraphNode {
	GraphNode() : num(0), T(0) { }
	GraphNode(unsigned inNum, T inWeight) : num(inNum), weight(inWeight) { }
	GraphNode(const GraphNode& rhs) : num(rhs.num), weight(rhs.weight) { }
	unsigned num;
	T weight;
};

// ���� - ������ ������
template<typename T>
struct Graph {
	typedef std::vector<GraphNode<T> > adjlist;
	std::vector<adjlist> nodelists;
};

// ������ ��� ������ � �������
class Timer
{
// ���������������/���������� 
public:
	Timer() : m_Time(0) { }

// �������� �������-����� 
public:
	// �������� ������� �����
	unsigned GetTime() {
		return ++m_Time;
	}
// �������� ������-�����
private:
	unsigned m_Time;
};

// LCA-�����, ������ - ��� ���� � �����
template<typename T>
class LCAMap {
// ���������������/����������
public:
	LCAMap() : m_Graph(NULL) { }
	LCAMap(const Graph<T>& inGraph) : m_Graph(&inGraph) { }

// �������� �������-�����
public:
	// �������� LCA-�����
	void CreateLCAMap();
	// ��������� ������ LCA-������� ��� ���� ������
	T GetLCA(T inA, T inB) const;
	
	unsigned GetPredecessor(unsigned inA) const;
	// ��������� ��������, ���� �� inA ��� inB
	// ������������ �����
	bool Upper(T inA, T inB) const;
	T GetUpweight(unsigned inA) const;
// �������� �������-�����
private:
	// ����� � ������� �� �����
	void DFSSearch(unsigned inV, unsigned inP = 0);

// �������� ������-�����
private:
	// ��������� ���������
	// ��� �������� ������� 
	// ��������� �������
	template<typename U>
	struct Time {
		U in;
		U out;
	};
	// ������ ����� ����������������
	std::vector<T> m_Upweight;
	// L = logN
	unsigned m_L;
	// ��������� ������ ���������� ������ ��� DFS
	std::vector<bool> m_Explored;
	// ��������� ������ ��� ������, ���������� � ���� DFS
	std::vector<std::vector<T> > m_Up;
	// ��������� ������� ��� ������
	std::vector<Time<T> > m_TimeStamps;
	// ������
	Timer m_Tmr;
	// ����
	const Graph<T>* m_Graph;
};

// ����� ��������� �� ������ LCA-�����
// (��������� �������� - ��� ����� � �����)
template<typename T>
class LCAPathFinder {
// ���������������/����������
public:
	LCAPathFinder();
	LCAPathFinder(const LCAMap<T>& inMap) : m_Map(&inMap) { }

// �������� �������-�����
public:
	// ��������� ���� ����������� �������� � ��������������
	// ����� ���������������
	T GetWeightBetween(T inA, T inB);

// �������� ������-�����
private:
	// ����� LCA
	const LCAMap<T>* m_Map;	
};



int main(int argc, char* argv[])
{
	typedef unsigned GraphWeight;

	unsigned input = 0;
	std::cin >> input;
	Graph<GraphWeight> g;
	g.nodelists.resize(input);
	for(unsigned i = 0; i < input - 1; ++i) {
		unsigned from = 0, to = 0, weight = 0;
		// ������ ������ �� ��������
		std::cin >> from;
		std::cin >> to;
		std::cin >> weight;
		g.nodelists[to - 1].push_back(GraphNode<GraphWeight>(from - 1, weight));
		g.nodelists[from - 1].push_back(GraphNode<GraphWeight>(to - 1, weight));
	}
	
	LCAMap<unsigned> m(g);
	m.CreateLCAMap();
	LCAPathFinder<unsigned> lcapf(m);
	std::cin >> input;
	for(int i = 0; i < input; ++i)
	{
		// ������ �����
		unsigned from = 0, to = 0;
		std::cin >> from;
		std::cin >> to;
		// ����� ������
		unsigned path = lcapf.GetWeightBetween(from - 1, to - 1);
		std::cout << path << "\n" << std::flush;
	}
	return 0;
}

// ���������� LCAMap
//////////////////////////////////////////////////////////////

// �������� ����� LCA
template<typename T>
void LCAMap<T>::CreateLCAMap() {
	assert(m_Graph != NULL && "invalid graph for LCA map creation selected");
	// �������������

	m_L = 1;
	// ���������� ������� logN
	while(std::pow(static_cast<long double>(2), static_cast<int>(m_L)) <= m_Graph->nodelists.size())
		++m_L;

	m_Upweight.resize(m_Graph->nodelists.size());
	// ������ ���������� ������
	m_Explored.resize(m_Graph->nodelists.size());
	// ��������� �����
	m_TimeStamps.resize(m_Graph->nodelists.size());
	// ������ ��� LCA

	m_Up.reserve(m_Graph->nodelists.size());
	for(unsigned i = 0; i < m_Graph->nodelists.size(); ++i)
		m_Up.push_back(std::vector<unsigned>(m_L + 1));
	
	// ����� � ������� �� �����
	DFSSearch(0);
	
}

// ����� � ������� � ����������� ������ LCA
// (��������� ���������� ����� ���������������)
template<typename T>
void LCAMap<T>::DFSSearch(unsigned inV, unsigned inP) {
	m_Explored[inV] = 1;

	m_TimeStamps[inV].in = m_Tmr.GetTime();
	m_Up[inV][0] = inP;
	
	for(unsigned i = 1; i <= m_L; ++i)
		m_Up[inV][i] = m_Up[m_Up[inV][i - 1]][i - 1];

	for(unsigned i = 0; i < m_Graph->nodelists[inV].size(); ++i) {
		GraphNode<T> to = m_Graph->nodelists[inV][i];
		if(!m_Explored[to.num]) {
			m_Upweight[to.num] = to.weight;
			DFSSearch(to.num, inV);
		}
	}
	m_TimeStamps[inV].out = m_Tmr.GetTime();
}

// ������� ����, ��� inA ���� inB ������������ �����
template<typename T>
bool LCAMap<T>::Upper(T inA, T inB) const {
	return m_TimeStamps[inA].in <= m_TimeStamps[inB].in && m_TimeStamps[inA].out >= m_TimeStamps[inB].out;
}

// ��������� ������ ������� LCA ��� ���� ������
template<typename T>
T LCAMap<T>::GetLCA(T inA, T inB) const {
	if(Upper(inA, inB)) 
		return inA;
	if(Upper(inB, inA))
		return inB;

	for(long i = m_L; i >= 0; --i)
		if(!Upper(m_Up[inA][i], inB))
			inA = m_Up[inA][i];
	return m_Up[inA][0];
}

// ��������� ���������������
template<typename T>
unsigned LCAMap<T>::GetPredecessor(unsigned inA) const {
	return m_Up[inA][0];
}

// ��������� ���� ���������������
template<typename T>
T LCAMap<T>::GetUpweight(unsigned inA) const {
	return m_Upweight[inA];
} 

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////


// ���������� LCAPathFinder
//////////////////////////////////////////////////////////////


// Divide-and-conquer-�����
// ��������� ����������� �������� 
// �� ������ ����� ���������������
template<typename T>
T LCAPathFinder<T>::GetWeightBetween(T inA, T inB)
{
	// ������� ��������
	if(inA == inB)
		return T(0);

	T lca = m_Map->GetLCA(inA, inB);
	// inA ����
	if(lca == inA) {
		T res = T(0);
		while(inB != inA) {
			res += m_Map->GetUpweight(inB);
			inB = m_Map->GetPredecessor(inB);
		}
		return res;
	}

	// inB ����
	else if(lca == inB) {
		T res = T(0);
		while(inA != inB) {
			res += m_Map->GetUpweight(inA);
			inA = m_Map->GetPredecessor(inA);
		}
		return res;
	}

	else
		// ���������� - ��� ����� lca � inA + ��� ����� lca � inB
		return GetWeightBetween(lca, inA) + GetWeightBetween(lca, inB);
}