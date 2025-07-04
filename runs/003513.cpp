#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>


using namespace std;

/**
*  ����� ���������� �������
*/
template <typename T>
class vector2
{
public:
	vector2()
	{
		arr = NULL;
	}

	void assign(size_t m, size_t n, int val)
	{
		this->m = m;
		this->n = n;
		arr = new T[m*n];
		memset(arr, val, m*n*sizeof(arr[0]));
	}

	inline T& operator()(int i, int j)
	{
		return arr[i*n+j];
	}

	~vector2()
	{
		if (arr != NULL)
			delete[] arr;
	}
private:
	size_t m, n;
	T *arr;
};

/**
*  ����� ����������� �������
*/
template <typename T>
class vector3
{
public:
	vector3()
	{
		arr = NULL;
	}

	void assign(size_t m, size_t n, size_t l, int val)
	{
		this->m = m;
		this->n = n;
		this->l = l;
		arr = new T[m*n*l];
		memset(arr, val, m*n*l*sizeof(arr[0]));
	}

	inline T& operator()(int i, int j, int k)
	{
		return arr[(i*n+j)*l +k];
	}

	~vector3()
	{
		if (arr != NULL)
			delete[] arr;
	}
private:
	size_t m, n, l;
	T *arr;
};

class Tree
{
public:
	/**
	*	�����������
	*	��������� ������ ��� ���� ����������� ��������
	*/
	Tree(int n)
	{
		N = n;
		logN = (int)log(2*N);
		sqrtN = (int)sqrt((double)2*N);
		maxBlocks = (N*2) / ((logN+1)/2) + 1;

		graph.insert(graph.end(), N, (Node*)NULL);
		for ( int i = 0; i < N ; i++)
		{
			graph[i] = new Node();
			graph[i]->index = i;
			graph[i]->parent = NULL;
			graph[i]->length = 0;
		}

		bt.assign(maxBlocks, logN + 1, 255);

		bhash = new int[maxBlocks];

		brmq.assign(sqrtN, logN/2 + 1 , logN/2 + 1 , 255);
		
		log2 = new int[2*N];

		h.assign(N, -1);
		a_pos.assign(N, 0);
		a.reserve (N*2);
	};

	~Tree()
	{
		delete[] bhash;
		delete[] log2;

		for(int i = 0; i < N; ++i)
			delete graph[i];
		graph.clear();
	};

	/**
	*	���������� ������� � ����
	*/
	void AddVertex(int from, int to, int len)
	{
		if (graph[to]->parent == NULL && to != 0)
		{
			graph[from]->childs.push_back(to);
			graph[to]->length = len;
			graph[to]->parent = graph[from];
		}
		else
		{
			graph[to]->childs.push_back(from);
			graph[from]->length = len;
			graph[from]->parent = graph[to];
		}
	}

	/**
	*  ���������� ��������� �� �������������� n+1
 	*/
	int log (int n) 
	{
		int res = 1;
		while (1<<res < n)  ++res;
		return res;
	}

	/**
	*  ��������� ���� ����� ���� ������
	*/
	inline int min_h (int i, int j) 
	{
		return h[a[i]] < h[a[j]] ? i : j;
	}
	
	/**
	* ����� ������ � �������
	*/
	void Dfs (int v, int curh) 
	{
		h[v] = curh;
		a_pos[v] = (int)a.size();
		a.push_back (v);
		for (size_t i=0; i<graph[v]->childs.size(); ++i)
			if (h[graph[v]->childs[i]] == -1) 
			{
				Dfs (graph[v]->childs[i], curh+1);
				a.push_back (v);
			}
	}
	/**
	*  ������������� ������ �� O(N)
	*/
	void Build() 
	{
		int sz = (int)a.size();
		block = (log(sz) + 1) / 2;
		int blocks = sz / block + (sz % block ? 1 : 0);

		// ������������ ������� � ������ ����� � ������ �������
		//memset (bt, 255, sizeof bt);
		for (int i=0, bl=0, j=0; i<sz; ++i, ++j) 
		{
			if (j == block)
				j = 0,  ++bl;
			if (bt(bl,0) == -1 || min_h (i, bt(bl,0)) == i)
				bt(bl,0) = i;
		}

		for (int j=1; j<=log(sz); ++j)
		{
			for (int i=0; i<blocks; ++i) 
			{
				int ni = i + (1<<(j-1));
				if (ni >= blocks)
					bt(i,j) = bt(i,j-1);
				else
					bt(i,j) = min_h (bt(i,j-1), bt(ni,j-1));
			}
		}

		// ��������� ���������� ����� ������� �����
		memset (bhash, 0, maxBlocks* sizeof(bhash[0]));
		for (int i=0, bl=0, j=0; i<sz||j<block; ++i, ++j) 
		{
			if (j == block)
				j = 0,  ++bl;
			if (j > 0 && (i >= sz || min_h (i-1, i) == i-1))
				bhash[bl] += 1<<(j-1);
		}

		// ������������ RMQ ������ ������� �����
		//memset (brmq, 255, sizeof brmq);
		for (int i=0; i<blocks; ++i) 
		{
			int id = bhash[i];
			if (brmq(id,0,0) != -1)  continue;
			for (int l=0; l<block; ++l) 
			{
				brmq(id,l,l) = l;
				for (int r=l+1; r<block; ++r) 
				{
					brmq(id,l,r) = brmq(id,l,r-1);
					if (i*block+r < sz)
						brmq(id,l,r) =
							min_h (i*block+brmq(id,l,r), i*block+r) - i*block;
				}
			}
		}

		// ������������ ��������� � ����������
		for (int i=0, j=0; i<sz; ++i) 
		{
			if (1<<(j+1) <= i)  ++j;
			log2[i] = j;
		}
	}

	// ����� RMQ � ����� #bl [l;r] �� O(1)
	inline int lca_in_block (int bl, int l, int r) 
	{
		return brmq(bhash[bl],l,r) + bl*block;
	}

	// ����� LCA �� O(1)
	int LCA (int v1, int v2) 
	{
		int l = a_pos[v1],  r = a_pos[v2];
		if (l > r)  swap (l, r);
		int bl = l/block,  br = r/block;
		if (bl == br)
			return a[lca_in_block(bl,l%block,r%block)];
		int ans1 = lca_in_block(bl,l%block,block-1);
		int ans2 = lca_in_block(br,0,r%block);
		int ans = min_h (ans1, ans2);
		if (bl < br - 1) 
		{
			int pw2 = log2[br-bl-1];
			int ans3 = bt(bl+1,pw2);
			int ans4 = bt(br-(1<<pw2),pw2);
			ans = min_h (ans, min_h (ans3, ans4));
		}
		return a[ans];
	}

	/**
	*	����� ������ ����
	*/
	int GetPath(int v, int v1, int v2)
	{
		int sum = 0;
		Node* node = graph[v1];
		while (node->index != v)
		{
			sum += node->length;
			node = node->parent;
		}
		node = graph[v2];
		while (node->index != v)
		{
			sum += node->length;
			node = node->parent;
		}
		return sum;
	}

private:
	int N; // ����� ������ � ������
	int logN; // �������� N
	int sqrtN; // ������ �� N
	int maxBlocks;// ������������ ���������� ������
	
	int block; // ������ ����� = 0.5 log a.size()
	vector2<int> bt; // ������� ������
	int *bhash;// ������ ����� ������
	vector3<int> brmq;// rmq ������ ������� �����
	int *log2;// ������ ��� �������� ���������������� ����������

	//������� � ������
	struct Node
	{ 
		Node* parent;
		int index; 
		int length; // ����� ����� �� ������
		vector<int> childs;
	};
	/// ������ ������ ������
	vector<Node*> graph;
	/// ������ ����� ������
	vector<int> h;
	/// ������ � ������� ��� ������ ������� ����� ������� ������� � ������� list
	vector<int> a_pos;
	/// ������ � ������� ����������� ������� � �������� ������
	vector<int> a;
};

int main()
{
	int N, M; // ���������� ������ � ���������� ��� ��� ������� ���� ����� ����������
	int v1, v2; // ������� ����� �������� ���� ����� ����������
	int from, to, len;
	
	cin >> N;
	Tree tree(N);

	for ( int i = 0; i < N - 1; i++)
		{
			cin >> from;
			cin >> to;
			cin >> len;
			tree.AddVertex(from - 1, to - 1, len);	
		}

	tree.Dfs(0,1);
	tree.Build();

	cin >> M;
	for (int i = 0; i< M ; i++)
	{
		// �������� ������
		cin >> v1;
		cin >> v2;
		int v = tree.LCA (v1-1, v2-1); // ����� �� ������
		cout << tree.GetPath(v, v1-1, v2-1) << endl;
	}
}