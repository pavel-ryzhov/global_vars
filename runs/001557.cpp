#include <iostream>
#include <vector>
//------------
//#include <fstream>
//std::ifstream testFile;
//------------
class TTable;
inline void inputPair(int & a, int & b){
	std::cin >> a;
	std::cin >> b;
	a--;
	b--;
}


//---------------
//inline void inputPair(int & a, int & b, std::ifstream & testFile){
//	testFile >> a;
//	testFile >> b;
//	a--;
//	b--;
//}
//-------------------------------

inline void swap(int & a, int & b){
	int temp = b;
	b = a;
	a = temp;
}


struct TEdge{
	int node;
	int cost;
	TEdge(int node, int cost);
};

class TGraph{
	int size;
	std::vector <std::vector <TEdge> > nodes;
	std::vector <int> eulerCount;
public:
	TGraph(int size);
	void addEdge();
	void startTour(TTable & table);
};

class TTable{
	int size;
	std::vector <int> E;	//Ёйлеровский тур
	std::vector <int> L;	//”ровни
	std::vector <int> H;	//первое попадание
	std::vector <int> S;	//рассто€ние от корн€
	std::vector <std::vector <int> > M;	//матрица дл€ быстрого нахождени€
	std::vector <int> Log2;	//таблица логарифмов
public:
	TTable(int size);
	int calcDistance();
	void preProcess();
	void preCalcLogs();
	std::vector <int> & getE() {return E;}
	std::vector <int> & getL() {return L;}
	std::vector <int> & getH() {return H;}
	std::vector <int> & getS() {return S;}
};

inline TEdge::TEdge(int node, int cost){
	TEdge::node = node;
	TEdge::cost = cost;
}

TGraph::TGraph(int size){
	TGraph::size = size;
	nodes.resize(size);
	eulerCount.resize(size, -1);
}

inline void TGraph::addEdge(){
	int a, b, cost;
	inputPair(a, b);
	std::cin >> cost;
	//---------------
	//inputPair(a, b, testFile);
	//testFile >> cost;
	//---------------
	TEdge aEdge(b, cost);
	TEdge bEdge(a, cost);
	nodes[a].push_back(aEdge);
	nodes[b].push_back(bEdge);
	eulerCount[a]++;
	eulerCount[b]++;
}

void TGraph::startTour(TTable & table){
	std::vector <int> & E = table.getE();
	std::vector <int> & L = table.getL();
	std::vector <int> & H = table.getH();
	std::vector <int> & S = table.getS();
	int node = 0;
	int previousNode = 0;
	int nextNode = 0;
	int cost = 0;
	E[0] = 0;
	H[0] = 1;
	S[0] = 0;
	L[0] = 0;
	for (int i = 1; i < E.size(); i++){
		nextNode = nodes[node][eulerCount[node]].node;
		if (H[nextNode] != 0 && eulerCount[node] != 0){
			std::swap(nodes[node][eulerCount[node]], nodes[node][0]);
			nextNode = nodes[node][eulerCount[node]].node;
		}
		cost = nodes[node][eulerCount[node]].cost;
		previousNode = node;
		node = nextNode;
		eulerCount[previousNode]--;
		E[i] = node;
		if (!H[node]){ //условие первого попадани€ 
			H[node] = i;
			S[node] = S[previousNode] + cost;
			L[i] = L[i - 1] + 1;
		}
		else
			L[i] = L[i - 1] - 1;
	}
	H[0] = 0;
}

TTable::TTable(int size){
	TTable::size = size;
	E.resize(size * 2 - 1);
	L.resize(size * 2 - 1);
	H.resize(size, 0);
	S.resize(size);
	Log2.resize(size * 2);
	preCalcLogs();
	M.resize(Log2[size * 2 - 1] + 1);
	for (int i = 0; i < M.size(); i++)
		M[i].resize(size * 2 - 1);
}

void TTable::preCalcLogs(){
	for (int i = 0, j = 0; i < size * 2; ++i) {
		if (1 << (j + 1) <= i)  ++j;
		Log2[i] = j;
	}
}

void TTable::preProcess(){

	int doubleSize = size * 2 - 1;
	for (int i = 0; i < doubleSize; i++)
		M[0][i] = i;


	for (int j = 1; 1 << j <= doubleSize; j++)
		for (int i = 0; i + (1 << j) - 1 < doubleSize; i++)
			if (L[M[j - 1][i]] <= L[M[j - 1][i + (1 << (j - 1))]])
				M[j][i] = M[j - 1][i];
			else
				M[j][i] = M[j - 1][i + (1 << (j - 1))];

}

//inline int TTable::calcDistance(){
//	int a, b;
//	inputPair(a, b);
//	//---------------
//	//inputPair(a, b, testFile);
//	//---------------
//	if (H[a] > H[b])
//		swap(a, b);
//	int iLovest = H[a];
//	for (int i = H[a]; i <= H[b]; i++){
//		if (L[i] < L[iLovest])
//			iLovest = i;
//	}
//	return S[a] + S[b] - 2 * S[E[iLovest]];
//}
inline int TTable::calcDistance(){
	int a, b;
	inputPair(a, b);
	//---------------
	//inputPair(a, b, testFile);
	//---------------
	if (H[a] > H[b])
		swap(a, b);
	int ai = H[a], bi = H[b];
	int k = Log2[bi - ai + 1];

	if (L[M[k][ai]] <= L[M[k][bi - (1 << k) + 1]]) //разобратьс€ с меньше и меньше или равно!!!
		return S[a] + S[b] - 2 * S[E[M[k][ai]]];
	else
		return S[a] + S[b] - 2 * S[E[M[k][bi - (1 << k) + 1]]];
}

int main(int argc, char* argv[])
{
	int size;
	std::cin >> size;
	//------------
	//testFile.open("test.txt");
	//testFile >> size;
	//------------
	std::cerr << size << std::endl;
	TGraph graph(size);
	TTable table(size);
	for (int i = 1; i < size; i++){
		graph.addEdge();
	}
	graph.startTour(table);
	table.preProcess();
	int queryN;
	std::cin >> queryN;
	//-------------------
	//testFile >> queryN;
	//-------------------
	std::cerr << queryN << std::endl;
	std::cerr << "step2" << std::endl;
	for (int i = 0; i < queryN; i++){
		std::cout << table.calcDistance() << std::endl;
	}
	//--------
	//getchar();
	//-----------
}