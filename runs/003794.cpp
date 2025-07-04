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

	int id; // ����, �� ������� ������� ������ �����
	int len; // ����� �����
};

// ����
class CNode : public vector<CEdge>
{
public:
	CNode(){reset();}

// �����
	void reset()
	{
		x = 0;
		idPrev = -1;
	}

	int x; // ���������� �� ����
	int idPrev; // ����, �� �������� ������ ������ � ������� ����
};

// ����
class CGraph
{
public:
// �����������
// N - ����� �����
	CGraph(int N)
	{
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

		reset();

		queue<int> q; // ������� ��������� �����
		q.push(n1);

		while(!q.empty())
		{
			int v = q.front();
			q.pop();
			for(unsigned int i = 0; i < nodes[v].size(); i++) // ������ ���� �������� �����
			{
				int v2 = nodes[v][i].id; // ����� ��������� ����
				if(v2 == nodes[v].idPrev) continue; // ���� ��������� � ���������� ������� - ����������

				nodes[v2].x = nodes[v][i].len + nodes[v].x; // ������� ����������
				nodes[v2].idPrev = v; // �������� �������� �������

				if(v2 == n2) return nodes[v2].x; // ��������� �������� ����

				q.push(v2); // � ������� ���������
			}
		}

		return 0;
	}

// �����
	void reset()
	{
		for(int i = 0; i < Nn; i++)
		{
			nodes[i].reset();
		}
	}

private:

	CNode* nodes; // ������ �����
	int Nn; // ����� �����
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

