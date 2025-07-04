#include <cstdio>
#include <vector>
#include <map>
//#include <windows.h>
using namespace std;

const int MaxVertexNumber = 40000;// ������������ ����� �������

class LCA{// ����� ���������� ������ ������. 
	// ������������ �������� ������ � ������� (Schieber B., Vishkin U. "On finding lowest common ancestors: simplifications and parallelization")
	// ���������� �� �������� (Dan Gusfield "Algorithms on strings, trees and sequences")
public:
	struct Node{// ���� ������
		Node(): dfs(-1), A(-1), p(NULL){}// ������������� �������� ���������� ��� ����������� ����, ��� ���� �� �������
		int I;// dfs-����� �������, � ������� �������� ������������� ������ ����� ���������� ����� ������� ����� ����� ���� ������ ��������� ���� �������
		int A;// ��� A(i) = 1 ������ ���� ���� ���� ����� ��������������� � T, ������� ������������ � ������ i � B (B - ������ �������� ������, T- �������� ������)
		Node* p;// ��������
		int dfs;// ���������� ����� ������� ��� dfs ������
		vector<Node*> c;// ����
		// ���������������� ������, �� ������������ ���� �������
		int cost;// ��������� ��������� ����� � dfs ������
	};
	
	LCA(int MaxVertexNum): tree(MaxVertexNum+1), L(MaxVertexNum+1){}// ����������� �������� ����������� ��������� ����� ������� � ������

	void AddEdge(int a, int b){// ������� ����� � ������
		//assert((unsigned)a < tree.size() && (unsigned)b < tree.size());// a, b < MaxVertexNum
		tree[b].c.push_back(&tree[a]);
		tree[a].c.push_back(&tree[b]);
	}// AddEdge()

	void Preprocess(int root){// ������������� ��������� ������ ��� ������������ ������ LCA, root = ����� �������� �������
		//assert((unsigned)root < tree.size());// root < MaxVertexNum
		CalcIL(root);
		CalcA(root);
	}// Preprocess()

	Node* Lca(Node* x, Node* y){
		unsigned k, i, mask, w, l, j;
		Node*xbar, *ybar;

		// ���� 1 � 2
		i = MSB(x->I ^ y->I);
		mask = 0xffffffff << i;
		j = h( (x->A & y->A) & mask );

		// ��� 3
		mask = ~(0xffffffff << j);		
		l = h(x->A);// 3a. ������� ������� l � ������� ������ �������� � Ax
		if (l == j) xbar = x;// 3b. 
		else {
			k = MSB(x->A & mask);//3c. ������� ������� ����� ����� ������� � Ax ������ �� ������� j
			w	= (x->I & (0xffffffff << k)) | (1 << k);// ��������� �����, ��������� �� ����� I(x) ����� �� ������� k, ����� 1 � ������� k, ����� ����. (��� ����� I(w))
			xbar	= L[w]->p;// ����� � �������� xbar �������� ������� w
		}

		// ��� 4 (����� �� ��� � 3 ������ ��� y)
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
	struct Tables{// ��������������� ����� ��� ���������� ����������� � ����������� ��������� ����. ��������� ����� �� 1
		enum{table_sz = 65536};// ������ ������. ����� ����� ����� ��������� �� 256, ��� �������� cache misses? ��������� ����������� ������� msb() � lsb()
		Tables(){
			int i, j, mask, msb, lsb;
			msb_table[0] = lsb_table[0] = 0;
			for(msb = -1, i = j = 1; i < 256; ++i){// ��������� ������ 256 ��������� ������
				if(i == j) j <<= 1, ++msb;
				msb_table[i] = msb;
				for (lsb = 0, mask = 1; !(mask & i); ++lsb, mask <<= 1);
				lsb_table[i] = lsb;
			}// for i
			for( ; i < table_sz; ++i){// ���������
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
		w->p = w;// �������� ��������� ���� �� ���
		int dfs = 0;
		vector<Node*> s;// ����
		s.push_back(w);
		
		while(!s.empty()){			
			w = s.back(); s.pop_back();			
			if(w->c.size() == 1 && dfs != 0){// ���� ����, (dfs != 0 - ����� �� ������������� ������ ��� ����, ���� � ���� ���� ���)
				w->dfs = w->I = ++dfs;
				L[dfs] = w;// ���� ������ ������� 1 �� �� � ����� ������� (� ���������� ��� �������� ����� ���������)
			}else if(w->dfs < 0){// ���������� ������������ ����				
				w->dfs = w->I = ++dfs;
				s.push_back(w);// ���� ��� ��������, ����� ���� ��� ����� ���������� ��� �������			
				for(vector<Node*>::iterator it = w->c.begin(), end = w->c.end(); it != end; ++it){
					if((*it)->dfs >= 0) continue;// ���� ������� ����� �� �����
					(*it)->p = w;// ������������� ��������
					s.push_back(*it);
				}// for it
			}else{// ���������� ���������� ���� (��� ������� ����������)
				// �.�. ���� ������� �� � ���� ����� ��������� I. ���� � ���� �� ������������
				int maxI = w->I, h_maxI = h(maxI);
				for(vector<Node*>::iterator it = w->c.begin(), end = w->c.end(); it != end; ++it)
					if((*it)->dfs > w->dfs && h((*it)->I) > h_maxI) maxI = (*it)->I, h_maxI = h(maxI);
				w->I = maxI;
				L[maxI] = w;// ������� maxI ����� ��� �������� �.�. w			
			}// else 
		}// while
	}// CalcIL()

	void CalcA(int root){		
		Node* w = &tree[root];
		w->A = 0;
		vector<Node*> stk(w->c.begin(), w->c.end());
		while(!stk.empty()){
			w = stk.back(); stk.pop_back();
			if(w->A >= 0) continue;//���� ���� �������, �� �����
			w->A = w->p->A | 1 << h(w->I);			
			stk.insert(stk.end(), w->c.begin(), w->c.end());
		}// while
	}// CalcA()

	vector<Node*> L;// Leader - ������ ������ (������ - ����������� ������ � ����������� I)
	vector<Node> tree;// ������ ��� ���� ������, ������ ��������� � ������� �������
	static Tables tab;
};//class LCA
LCA::Tables LCA::tab;

class COST{// ����� ��� �������� ����� �����. �������, ��� ��� (a,b) == (b,a), � ����� (a,a) == 0
public:
	void AddEdge(int a, int b, int cost){ if(a != b) Find(a, b) = cost;}
	int operator()(int a, int b){ return (a != b) ? Find(a, b) : 0;}// ���������� ��� ����� (a,b)
private:
	int& Find(int a, int b){ return (a > b) ? M[make_pair(b, a)] : M[make_pair(a, b)];}
	map<pair<int,int>, int> M;
};

int main(){
	//freopen("g.txt", "rt", stdin);
	//UINT st = GetTickCount();
	LCA Lca(MaxVertexNumber);
	int n, m;// ���������� ������ � ��������, 
	int a, b, c;// ������ ������ � ���������
	COST Cost;// �������� ������ ��������� �����

	scanf("%d", &n);
	for(int i = 1; i < n; ++i){
		scanf("%d%d%d", &a, &b, &c);
		Lca.AddEdge(a, b);
		Cost.AddEdge(a, b, c);
	}
	Lca.Preprocess(b);// ��� ������ ������ � �������� ����� ����� ������� ����� �������
	// ���������� ��������� ����� �� ������� � �������� � ����� ������� ������ LCA ��� ����� �������� �������� ����������
	vector<LCA::Node>& tree = Lca.GetTree();
	for(unsigned i = 0; i < tree.size(); ++i){
		if(tree[i].p == NULL) continue;
		tree[i].cost = Cost(i, (int)(tree[i].p - &tree[0]));
	}
	// ������������ �������
	scanf("%d", &m);
	for(int i = 0; i < m; ++i){
		scanf("%d%d", &a, &b);		
		LCA::Node *na, *nb, *x;
		na = &tree[a]; nb = &tree[b];
		x = Lca.Lca(na, nb);
		int TotalCost = 0;
		// ����������� ����� �� ������ ������, �������� ����������
		while(na != x) TotalCost+= na->cost, na = na->p;
		while(nb != x) TotalCost+= nb->cost, nb = nb->p;
		printf("%d\n", TotalCost);
	}
	//printf("dt = %d\n", GetTickCount() - st);
	return 0;
}