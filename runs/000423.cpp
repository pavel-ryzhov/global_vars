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

int N;
struct Way *WayTree;
struct Peak *PeakTree;

void read()
{
	cin >> N;
	WayTree = new struct Way[N - 1];
	for (int i = 0; i < N - 1; i++)
	{
		cin >> WayTree[i].start;
		cin >> WayTree[i].end;
		cin >> WayTree[i].weight;
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

int main()
{
	read();
	makePeakTree();
	int M, p, t;
	cin >> M;
	for (int i = 0; i < M; i++)
	{
		for (int ii = 0; ii < N; ii++)
			PeakTree[ii].state = -1;
		queue<int> que;
		cin >> p;
		cin >> t;
		p--;
		t--;
		PeakTree[p].L = 0;
		PeakTree[p].state = 0;
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
		cout << PeakTree[t].L << endl;
	}
}
