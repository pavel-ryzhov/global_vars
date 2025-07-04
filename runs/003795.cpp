#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

// ������������ �����
class CEdge
{
public:
// �����������
// i - ����, �� ������� ������� ������ �����
// l - ����� �����
	CEdge(int i, int l)
	{
		id = i;
		len = l;
	}

	int id;	 // ����, �� ������� ������� ������ �����
	int len; // ����� �����
};

// ����
class CNode : public vector<CEdge>
{
public:
// �����������
	CNode()
	{
		x = 0;
		idPar = -1;
		mark = 0;
	}

	int x;		// ���������� �� ����
	int idPar;	// ����-��������
	int mark;	// ����� � ����������� ����� ����
};

// ���� 
class CGraph
{
public:
// �����������
// N - ����� �����
	CGraph(int N)
	{
		currMark = 0;
		Nn = N;
		nodes = new CNode[N];
	}

	~CGraph()
	{
		delete[] nodes;
	}

// ���������� ���������������� �����
// n1 - ��������� ����
// n2 - �������� ����
// len - ����� �����
	void addEdge(int n1, int n2, int len)
	{
		nodes[n1].push_back(CEdge(n2, len));
		nodes[n2].push_back(CEdge(n1, len));
	}

// ��������� ���������� ����� ������
// n1 - ��������� ����
// n2 - �������� ����
// return - ���������� ����� ������
	int getDistance(int n1, int n2)
	{
		if(n1 == n2) return 0;

		currMark++; // ����� ����� => ������ �����

		gotoRoot(n1);
		int n3 = findRootWay(n2);

		return nodes[n1].x + nodes[n2].x - 2*nodes[n3].x;
	}

// ���������� ���������� �� ����� ������������ �����
	void calcRootDistance()
	{
		queue<int> q; // ������� ��������� �����
		q.push(0);

		while(!q.empty())
		{
			int v = q.front();
			q.pop();
			for(unsigned int i = 0; i < nodes[v].size(); i++) // ������ ���� �������� �����
			{
				int v2 = nodes[v][i].id; // ����� ��������� ����
				if(v2 == nodes[v].idPar) continue; // ���� ��������� � ���������� ������� - ����������

				nodes[v2].x = nodes[v][i].len + nodes[v].x; // ������� ����������
				nodes[v2].idPar = v; // �������� �������� �������

				q.push(v2); // � ������� ���������
			}
		}
	}

private:	

// �������� ��� ������� �� ��������� ���� �� �����
// id - �������� ����
	void gotoRoot(int id)
	{
		while(id)
		{
			nodes[id].mark = currMark;
			id = nodes[id].idPar;
		}
	}

// ���� � �����, ������� �� ��������� ����, ���� �� ���������� �����
// id - �������� ����
// return - ������ ������������� ���� � ������
	int findRootWay(int id)
	{
		while(id)
		{
			if(nodes[id].mark == currMark) return id;
			id = nodes[id].idPar;
		}
		return 0;
	}

	CNode* nodes; // ������ �����
	int Nn; // ����� �����
	int currMark; // ������� �������� �����
};

int main(int argc, char* argv[])
{
	int i;
	int N = 0;

// ����� �����
	scanf("%d", &N);
	if(N <= 0) return 0;

// �������� �����
	CGraph gr(N);
	for(i = 0; i < N-1; i++)
	{
		int n1, n2, len;
		scanf("%d %d %d", &n1, &n2, &len);
		gr.addEdge(n1-1, n2-1, len);
	}

// ����� ��� �����, ����� �������� �������� ���������� ����������
	scanf("%d", &N);

// ��������� ���������� �� ����� ������
	gr.calcRootDistance();

// ���������
	vector<int> dist;

// ��������� ���������� ��� ���� ��� �����
	for(i = 0; i < N; i++ )
	{
		int n1, n2;
		scanf("%d %d", &n1, &n2);
		dist.push_back(gr.getDistance(n1-1, n2-1));
	}

// ����� ����������
	for(i = 0; i < N; i++ )
	{
		printf("%d\n", dist[i]);
	}

	return 0;
}

