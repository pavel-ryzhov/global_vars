/*
	����� ������ � ����������� ����� ���������������
	�� ����� ������ ����� � �������
*/

#include <iostream>
#include <vector>
#include <cassert>

// ��������� ������� �����: U - ��� ����� ���� (�� ��������� unsigned)
template<typename U>
struct GraphNode {
	// ������ ���������
	std::vector<unsigned> adjacent;
	// ����
	std::vector<U> weights;
};

// ���� - ������ ������
template<typename T>
struct Graph {
	std::vector<GraphNode<T> > nodes;
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
	unsigned input = 0;
	std::cin >> input;
	Graph<unsigned> g;
	g.nodes.resize(input);
	
	for(unsigned i = 0; i < g.nodes.size() - 1; ++i) {
		unsigned from = 0, to = 0, weight = 0;
		// ������ ������ �� ��������
		std::cin >> from;
		std::cin >> to;
		std::cin >> weight;
		g.nodes[to - 1].adjacent.push_back(from - 1);
		g.nodes[to - 1].weights.push_back(weight);
		g.nodes[from - 1].adjacent.push_back(to - 1);
		g.nodes[from - 1].weights.push_back(weight);
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

	m_Upweight.resize(m_Graph->nodes.size());
	// ������ ���������� ������
	m_Explored.resize(m_Graph->nodes.size());
	// ��������� �����
	m_TimeStamps.resize(m_Graph->nodes.size());
	// ������ ��� LCA
	m_Up.resize(m_Graph->nodes.size());
	m_L = 1;
	
	// ���������� ������� logN
	while((m_L << 1) <= m_Graph->nodes.size())
		++m_L;
	for(unsigned i = 0; i < m_Graph->nodes.size(); ++i)
		m_Up[i].resize(m_L + 1);
	
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

	for(unsigned i = 0; i < m_Graph->nodes[inV].adjacent.size(); ++i) {
		unsigned to = m_Graph->nodes[inV].adjacent[i];
		if(!m_Explored[to]) {
			m_Upweight[to] = m_Graph->nodes[inV].weights[i];
			DFSSearch(to, inV);
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