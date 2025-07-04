#include <iostream>
#include <vector>
#include <cassert>

// шаблонный граф: U - тип весов рёбер (по умолчанию unsigned)
template<typename U>
struct Graph {
	std::vector<std::vector<std::pair<unsigned, U> > > edges;
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

	// получение признака, выше ли inA чем inB
	// относительно корня
	bool Upper(T inA, T inB) const;

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
	LCAPathFinder(const Graph<T>& inG, const LCAMap<T>& inMap) : m_Graph(&inG), m_Map(&inMap) { }

// открытые функции-члены
public:
	// получение веса кратчайшего маршрута между inA и inB
	T GetWeightBetween(T inA, T inB);

// закрытые данные-члены
private:
	// граф
	const Graph<T>* m_Graph;
	// карта LCA
	const LCAMap<T>* m_Map;	
};



int main(int argc, char* argv[])
{
	unsigned input = 0;
	std::cin >> input;
	Graph<unsigned> g;
	g.edges.resize(input);
	for(unsigned i = 0; i < g.edges.size() - 1; ++i) {
		unsigned from = 0, to = 0, weight = 0;
		// чтение данных по вершинам
		std::cin >> from;
		std::cin >> to;
		std::cin >> weight;
		// граф неориентированный, каждое ребро = 2 ребра
		g.edges[from - 1].push_back(std::pair<unsigned, unsigned>(to - 1, weight));
		g.edges[to - 1].push_back(std::pair<unsigned, unsigned>(from - 1, weight));
	}

	LCAMap<unsigned> m(g);
	m.CreateLCAMap();
	LCAPathFinder<unsigned> lcapf(g, m);

	std::cin >> input;
	for(int i = 0; i < input; ++i)
	{
		// чтение задач
		unsigned from = 0, to = 0;
		std::cin >> from;
		std::cin >> to;
		// вывод ответа
		std::cout << lcapf.GetWeightBetween(from - 1, to - 1) << "\n";
	}
	return 0;
}

// Реализация LCAMap
//////////////////////////////////////////////////////////////

// создание карты LCA
template<typename T>
void LCAMap<T>::CreateLCAMap() {
	assert(m_Graph != NULL && "invalid graph for DFS map creation selected");
	
	m_Explored.resize(m_Graph->edges.size());
	m_TimeStamps.resize(m_Graph->edges.size());
	m_Up.resize(m_Graph->edges.size());
	m_L = 1;
	
	// вычисление потолка logN
	while((m_L << 1) <= m_Graph->edges.size())
		++m_L;
	for(unsigned i = 0; i < m_Graph->edges.size(); ++i)
		m_Up[i].resize(m_L + 1);
	
	// поиск в глубину от корня
	DFSSearch(0);
	
}

// поиск в глубину с заполнением данных LCA
template<typename T>
void LCAMap<T>::DFSSearch(unsigned inV, unsigned inP) {
	m_Explored[inV] = 1;
	m_TimeStamps[inV].in = m_Tmr.GetTime();
	m_Up[inV][0] = inP;
	
	for(unsigned i = 1; i <= m_L; ++i)
		m_Up[inV][i] = m_Up[m_Up[inV][i - 1]][i - 1];

	for(unsigned i = 0; i < m_Graph->edges[inV].size(); ++i) {
		unsigned to = m_Graph->edges[inV][i].first;
		if(!m_Explored[to])
			DFSSearch(to, inV);
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

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////


// Реализация LCAPathFinder
//////////////////////////////////////////////////////////////

// Divide-and-conquer-метод
// получения кратчайшего маршрута на основе LCA
template<typename T>
T LCAPathFinder<T>::GetWeightBetween(T inA, T inB)
{
	// останов рекурсии
	if(inA == inB)
		return T(0);

	T lca = m_Map->GetLCA(inA, inB);
	// inA выше
	if(lca == inA) {
		// находим вершину testnode на пути inA - inB
		for(unsigned i = 0; i < m_Graph->edges[inA].size(); ++i) {
			T testnode = m_Graph->edges[inA][i].first;
			if(m_Map->Upper(inA, testnode) && m_Map->GetLCA(testnode, inB) == testnode) {
				// вес между inA и testnode + рекурсивно вес между testnode и inB 
				return m_Graph->edges[inA][i].second + GetWeightBetween(testnode, inB);
			}
		}
	}
	// inB выше
	else if(lca == inB) {
		// находим вершину testnode на пути inB - inA
		for(unsigned i = 0; i < m_Graph->edges[inB].size(); ++i) {
			T testnode = m_Graph->edges[inB][i].first;
			if(m_Map->Upper(inB, testnode) && m_Map->GetLCA(testnode, inA) == testnode) {
				// вес между inB и testnode + рекурсивно вес между testnode и inA 
				return m_Graph->edges[inB][i].second + GetWeightBetween(testnode, inA);
			}
		}
	}

	else
		// рекурсивно - вес между lca и inA + вес между lca и inB
		return GetWeightBetween(lca, inA) + GetWeightBetween(lca, inB);
}