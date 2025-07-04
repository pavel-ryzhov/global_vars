#include <cstdio>
#include <vector>
#include <map>
//#include <windows.h>
using namespace std;

const int MaxVertexNumber = 40000;// Максимальный номер вершины

class LCA{// Поиск ближайшего общего предка. 
	// Используется алгоритм Шибера и Вишкина (Schieber B., Vishkin U. "On finding lowest common ancestors: simplifications and parallelization")
	// реализация по Гасфилду (Dan Gusfield "Algorithms on strings, trees and sequences")
public:
	struct Node{// Узел дерева
		Node(): dfs(-1), A(-1), p(NULL){}// Отрицательные значения используем для определения того, что узел не посещен
		int I;// dfs-номер вершины, у которой двоичное представление номера имеет наибольшее число ведущих нулей среди всех вершин поддерева этой вершины
		int A;// Бит A(i) = 1 только если этот узел имеет вредшественника в T, который проецируется в высоту i в B (B - полное двоичное дерево, T- исходное дерево)
		Node* p;// Родитель
		int dfs;// Порядковый номер вершины при dfs обходе
		vector<Node*> c;// Дети
		// Пользовательские данные, не используемые этим классом
		int cost;// Стоимость входящего ребра в dfs дереве
	};
	
	LCA(int MaxVertexNum): tree(MaxVertexNum+1), L(MaxVertexNum+1){}// Конструктор получает максимально возможный номер вершины в дереве

	void AddEdge(int a, int b){// Вставка ребра в дерево
		//assert((unsigned)a < tree.size() && (unsigned)b < tree.size());// a, b < MaxVertexNum
		tree[b].c.push_back(&tree[a]);
		tree[a].c.push_back(&tree[b]);
	}// AddEdge()

	void Preprocess(int root){// Препроцессная обработка дерева для последующего поиска LCA, root = номер корневой вершины
		//assert((unsigned)root < tree.size());// root < MaxVertexNum
		CalcIL(root);
		CalcA(root);
	}// Preprocess()

	Node* Lca(Node* x, Node* y){
		unsigned k, i, mask, w, l, j;
		Node*xbar, *ybar;

		// Шаги 1 и 2
		i = MSB(x->I ^ y->I);
		mask = 0xffffffff << i;
		j = h( (x->A & y->A) & mask );

		// Шаг 3
		mask = ~(0xffffffff << j);		
		l = h(x->A);// 3a. Находим позицию l с крайней правой единицей в Ax
		if (l == j) xbar = x;// 3b. 
		else {
			k = MSB(x->A & mask);//3c. Находим позицию самой левой единицы в Ax справа от позиции j
			w	= (x->I & (0xffffffff << k)) | (1 << k);// Формируем число, состоящее из битов I(x) слева от позиции k, затем 1 в позиции k, затем нули. (Это будет I(w))
			xbar	= L[w]->p;// Берем в качестве xbar родителя вершины w
		}

		// Шаг 4 (Такой же как и 3 только для y)
		l = h(y->A);
		if (l == j) ybar = y;
		else {
			k = MSB(y->A & mask);
			w = (y->I & (0xffffffff << k)) | (1 << k);
			ybar = L[w]->p;
		}

		return (xbar->dfs < ybar->dfs ? xbar : ybar);
	}// FindLca()

	vector<Node>& GetTree(){return tree;}

private:
	struct Tables{// Вспомогательный класс для вычисления наибольшего и наименьшего значащего бита. Нумерация битов от 1
		enum{table_sz = 65536};// Размер таблиц. Может имеет смысл уменьшить до 256, для снижения cache misses? Потребует переписания функций msb() и lsb()
		Tables(){
			int i, j, mask, msb, lsb;
			msb_table[0] = lsb_table[0] = 0;
			for(msb = -1, i = j = 1; i < 256; ++i){// Заполняем первые 256 элементов таблиц
				if(i == j) j <<= 1, ++msb;
				msb_table[i] = msb;
				for (lsb = 0, mask = 1; !(mask & i); ++lsb, mask <<= 1);
				lsb_table[i] = lsb;
			}// for i
			for( ; i < table_sz; ++i){// остальные
				if(i == j) j <<= 1, ++msb;
				msb_table[i] = msb;
				if(i & 0xff) lsb_table[i] = lsb_table[i & 0xff];
				else lsb_table[i] = 8 + lsb_table[(i >> 8)& 0xff];
			}// for i
		}// Tables()
		int lsb(int n){ return (n & 0xffff ? lsb_table[n & 0xffff] : 16 + lsb_table[n >> 16]);}
		int msb(int n){ return (n & 0xffff0000 ? 16 + tab.msb_table[n >> 16] : tab.msb_table[n]);}
		int msb_table[table_sz], lsb_table[table_sz];		
	};// struct Tables
	static int h(int n){return tab.lsb(n);}
	static int MSB(int n){return tab.msb(n);}

	void CalcIL(int root){
		Node* w = &tree[root];
		w->p = w;// Родитель корневого узла он сам
		int dfs = 0;
		vector<Node*> s;// Стек
		s.push_back(w);
		
		while(!s.empty()){			
			w = s.back(); s.pop_back();			
			if(w->c.size() == 1 && dfs != 0){// Если лист, (dfs != 0 - чтобы не рассматривать корень как лист, если у него один сын)
				w->dfs = w->I = ++dfs;
				L[dfs] = w;// Если полоса размера 1 то он и будет головой (в дальнейшем это значение может изменится)
			}else if(w->dfs < 0){// Внутренний непосещенный узел				
				w->dfs = w->I = ++dfs;
				s.push_back(w);// Сюда еще вернемся, после того как будут обработаны все потомки			
				for(vector<Node*>::iterator it = w->c.begin(), end = w->c.end(); it != end; ++it){
					if((*it)->dfs >= 0) continue;// Если обратое ребро то далее
					(*it)->p = w;// Устанавливаем родителя
					s.push_back(*it);
				}// for it
			}else{// Внутренний посещенный узел (все потомки обработаны)
				// Т.к. узел посещен то у всех детей посчитаны I. Ищем у кого он максимальный
				int maxI = w->I, h_maxI = h(maxI);
				for(vector<Node*>::iterator it = w->c.begin(), end = w->c.end(); it != end; ++it)
					if((*it)->dfs > w->dfs && h((*it)->I) > h_maxI) maxI = (*it)->I, h_maxI = h(maxI);
				w->I = maxI;
				L[maxI] = w;// Головой maxI будет его родитель т.е. w			
			}// else 
		}// while
	}// CalcIL()

	void CalcA(int root){		
		Node* w = &tree[root];
		w->A = 0;
		vector<Node*> stk(w->c.begin(), w->c.end());
		while(!stk.empty()){
			w = stk.back(); stk.pop_back();
			if(w->A >= 0) continue;//Если узел посещен, то далее
			w->A = w->p->A | 1 << h(w->I);			
			stk.insert(stk.end(), w->c.begin(), w->c.end());
		}// while
	}// CalcA()

	vector<Node*> L;// Leader - голова полосы (полоса - подможество вершин с одинаковыми I)
	vector<Node> tree;// Память под узлы дерева, индекс совпадает с номером вершины
	static Tables tab;
};//class LCA
LCA::Tables LCA::tab;

class COST{// Класс для хранения весов ребер. Считаем, что вес (a,b) == (b,a), а также (a,a) == 0
public:
	void AddEdge(int a, int b, int cost){ if(a != b) Find(a, b) = cost;}
	int operator()(int a, int b){ return (a != b) ? Find(a, b) : 0;}// Возвращает вес ребра (a,b)
private:
	int& Find(int a, int b){ return (a > b) ? M[make_pair(b, a)] : M[make_pair(a, b)];}
	map<pair<int,int>, int> M;
};

int main(){
	//freopen("g.txt", "rt", stdin);
	//UINT st = GetTickCount();
	LCA Lca(MaxVertexNumber);
	int n, m;// Количество вершин и запросов, 
	int a, b, c;// Номера вершин и стоимость
	COST Cost;// Временно храним стоимости ребер

	scanf("%d", &n);
	for(int i = 1; i < n; ++i){
		scanf("%d%d%d", &a, &b, &c);
		Lca.AddEdge(a, b);
		Cost.AddEdge(a, b, c);
	}
	Lca.Preprocess(b);// Для данной задачи в качестве корня можно выбрать любую вершину
	// Записываем стоимости ребер от вершины к родителю в узелы вершины дерева LCA для более быстрого подсчета расстояния
	vector<LCA::Node>& tree = Lca.GetTree();
	for(unsigned i = 0; i < tree.size(); ++i){
		if(tree[i].p == NULL) continue;
		tree[i].cost = Cost(i, (int)(tree[i].p - &tree[0]));
	}
	// Обрабатываем запросы
	scanf("%d", &m);
	for(int i = 0; i < m; ++i){
		scanf("%d%d", &a, &b);		
		LCA::Node *na, *nb, *x;
		na = &tree[a]; nb = &tree[b];
		x = Lca.Lca(na, nb);
		int TotalCost = 0;
		// Поднимаемся вверх до общего предка, суммируя расстояния
		while(na != x) TotalCost+= na->cost, na = na->p;
		while(nb != x) TotalCost+= nb->cost, nb = nb->p;
		printf("%d\n", TotalCost);
	}
	//printf("dt = %d\n", GetTickCount() - st);
	return 0;
}