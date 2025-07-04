/*
	Новая версия с построением графа предшествования
	во время обхода графа в глубину
*/

#include <iostream>
#include <vector>
#include <cassert>

// шаблонная вершина графа: U - тип весов рёбер (по умолчанию unsigned)
template<typename U>
struct GraphNode {
	// список смежности
	std::vector<unsigned> adjacent;
	// веса
	std::vector<U> weights;
};

// граф - массив вершин
template<typename T>
struct Graph {
	std::vector<GraphNode<T> > nodes;
};

// таймер для поиска в глубину
class Timer
{
// конструирование/разрушение 
public:
	Timer() : m_Time(0) { }

// открытые функции-члены 
public:
	// получить текущее время
	unsigned GetTime() {
		return ++m_Time;
	}
// закрытые данные-члены
private:
	unsigned m_Time;
};

// LCA-карта, шаблон - тип веса в графе
template<typename T>
class LCAMap {
// конструирование/разрушение
public:
	LCAMap() : m_Graph(NULL) { }
	LCAMap(const Graph<T>& inGraph) : m_Graph(&inGraph) { }

// открытые функции-члены
public:
	// создание LCA-карты
	void CreateLCAMap();
	// получение номера LCA-вершины для пары вершин
	T GetLCA(T inA, T inB) const;
	
	unsigned GetPredecessor(unsigned inA) const;
	// получение признака, выше ли inA чем inB
	// относительно корня
	bool Upper(T inA, T inB) const;
	T GetUpweight(unsigned inA) const;
// закрытые функции-члены
private:
	// поиск в глубину по графу
	void DFSSearch(unsigned inV, unsigned inP = 0);

// закрытые данные-члены
private:
	// локальная структура
	// для хранения формата 
	// временных засечек
	template<typename U>
	struct Time {
		U in;
		U out;
	};
	// массив весов предшественников
	std::vector<T> m_Upweight;
	// L = logN
	unsigned m_L;
	// служебный массив пройденных вершин для DFS
	std::vector<bool> m_Explored;
	// служебные данные для вершин, полученные в ходе DFS
	std::vector<std::vector<T> > m_Up;
	// временные засечки для вершин
	std::vector<Time<T> > m_TimeStamps;
	// таймер
	Timer m_Tmr;
	// граф
	const Graph<T>* m_Graph;
};

// поиск маршрутов на основе LCA-карты
// (шаблонный параметр - тип весов в графе)
template<typename T>
class LCAPathFinder {
// конструирование/разрушение
public:
	LCAPathFinder();
	LCAPathFinder(const LCAMap<T>& inMap) : m_Map(&inMap) { }

// открытые функции-члены
public:
	// получение веса кратчайшего маршрута с использованием
	// графа предшествования
	T GetWeightBetween(T inA, T inB);

// закрытые данные-члены
private:
	// карта LCA
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
		// чтение данных по вершинам
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
		// чтение задач
		unsigned from = 0, to = 0;
		std::cin >> from;
		std::cin >> to;
		// вывод ответа
		unsigned path = lcapf.GetWeightBetween(from - 1, to - 1);
		std::cout << path << "\n" << std::flush;
	}
	return 0;
}

// Реализация LCAMap
//////////////////////////////////////////////////////////////

// создание карты LCA
template<typename T>
void LCAMap<T>::CreateLCAMap() {
	assert(m_Graph != NULL && "invalid graph for LCA map creation selected");
	// инициализация

	m_Upweight.resize(m_Graph->nodes.size());
	// массив пройденных вершин
	m_Explored.resize(m_Graph->nodes.size());
	// временные метки
	m_TimeStamps.resize(m_Graph->nodes.size());
	// массив для LCA
	m_Up.resize(m_Graph->nodes.size());
	m_L = 1;
	
	// вычисление потолка logN
	while((m_L << 1) <= m_Graph->nodes.size())
		++m_L;
	for(unsigned i = 0; i < m_Graph->nodes.size(); ++i)
		m_Up[i].resize(m_L + 1);
	
	// поиск в глубину от корня
	DFSSearch(0);
	
}

// поиск в глубину с заполнением данных LCA
// (добавлено построение графа предшествования)
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

// признак того, что inA выше inB относительно корня
template<typename T>
bool LCAMap<T>::Upper(T inA, T inB) const {
	return m_TimeStamps[inA].in <= m_TimeStamps[inB].in && m_TimeStamps[inA].out >= m_TimeStamps[inB].out;
}

// получение номера вершины LCA для двух вершин
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

// получение предшественника
template<typename T>
unsigned LCAMap<T>::GetPredecessor(unsigned inA) const {
	return m_Up[inA][0];
}

// получение веса предшественника
template<typename T>
T LCAMap<T>::GetUpweight(unsigned inA) const {
	return m_Upweight[inA];
} 

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////


// Реализация LCAPathFinder
//////////////////////////////////////////////////////////////


// Divide-and-conquer-метод
// получения кратчайшего марщрута 
// на основе графа предшествования
template<typename T>
T LCAPathFinder<T>::GetWeightBetween(T inA, T inB)
{
	// останов рекурсии
	if(inA == inB)
		return T(0);

	T lca = m_Map->GetLCA(inA, inB);
	// inA выше
	if(lca == inA) {
		T res = T(0);
		while(inB != inA) {
			res += m_Map->GetUpweight(inB);
			inB = m_Map->GetPredecessor(inB);
		}
		return res;
	}

	// inB выше
	else if(lca == inB) {
		T res = T(0);
		while(inA != inB) {
			res += m_Map->GetUpweight(inA);
			inA = m_Map->GetPredecessor(inA);
		}
		return res;
	}

	else
		// рекурсивно - вес между lca и inA + вес между lca и inB
		return GetWeightBetween(lca, inA) + GetWeightBetween(lca, inB);
}