#include <iostream>
#include <stdio.h>
#include "vector"
#include "queue"
using namespace std;

struct Way
{
	int start;
	int end;
	int weight;
};

struct Peak
{
	vector<int> near;
	int L;
	int state;
};

int N, M;
vector<Way> WayTree;
vector<Way> Ways;
struct Peak *PeakTree;

void read()
{
	cin >> N;
	struct Way w;
	for (int i = 0; i < N - 1; i++)
	{
		cin >> w.start;
		cin >> w.end;
		cin >> w.weight;
		WayTree.push_back(w);
	}
	cin >> M;
	for (int i = 0; i < M; i++)
	{
		cin >> w.start;
		cin >> w.end;
		w.weight = -1;
		Ways.push_back(w);
	}
}

void makePeakTree()
{
	PeakTree = new struct Peak[N];
	for (int i = 0; i < N; i++)
	{
		PeakTree[i].L = -1;
		PeakTree[i].state = -1;
	}
	for (int i = 0; i < N - 1; i++)
	{
		int k1 = WayTree[i].start - 1;
		int k2 = WayTree[i].end - 1;
		PeakTree[k1].near.push_back(k2 + 1);
		PeakTree[k2].near.push_back(k1 + 1);
	}
}

int searchWay(int start, int end)
{
	for (int i = 0; i < N - 1; i++)
		if ((WayTree[i].start == start && WayTree[i].end == end) || (WayTree[i].end == start && WayTree[i].start == end))
		{
			return i;
		}
	return -1;
}

void printWays()
{
	for (int i = 0; i < M; i++)
		cout << Ways[i].weight << endl;
}

int main()
{
	read();
	makePeakTree();
	for (int i = 0; i < M; i++)
	{
		for (int ii = 0; ii < N; ii++)
			PeakTree[ii].state = -1;
		queue<int> que;
		int s = Ways[i].start - 1;
		int t = Ways[i].end - 1;
		int p = s;
		PeakTree[p].L = 0;
		while (p != t)
		{
			int size = PeakTree[p].near.size();
			for (int j = 0; j < size; j++)
			{
				int k = PeakTree[p].near[j] - 1;
				if (PeakTree[k].state != 0)
				{
					int wt = searchWay(p + 1, k + 1);
					que.push(k + 1);
					PeakTree[k].L = PeakTree[p].L + WayTree[wt].weight;
					PeakTree[k].state = 0;
				}
			}
			p = que.front() - 1;
			que.pop();
		}
		Ways[i].weight = PeakTree[t].L;
	}
	printWays();
}
