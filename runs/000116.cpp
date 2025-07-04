#include <iostream>
#include <stdio.h>
#include "vector"
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
		PeakTree[i].state = -2;
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
	int M;
	cin >> M;
	int *Ways = new int[M];
	for (int i = 0; i < M; i++)
	{
		for (int ii = 0; ii < N; ii++)
			PeakTree[ii].state = -2;
		int p, t;
		cin >> p;
		cin >> t;
		p--;
		PeakTree[p].L = 0;
		while (p != t - 1)
		{
			PeakTree[p].state = 0;
			int size = PeakTree[p].near.size();
			for (int j = 0; j < size; j++)
			{
				int k = PeakTree[p].near[j] - 1;
				if (j < size && PeakTree[k].state != 0)
				{
					int wt = searchWay(p + 1, k + 1);
					if (PeakTree[k].state == -2)
					{
						PeakTree[k].L = PeakTree[p].L + WayTree[wt].weight;
						PeakTree[k].state = -1;
					}
					else
					{
						if (PeakTree[k].L > PeakTree[p].L + WayTree[wt].weight)
							PeakTree[k].L = PeakTree[p].L + WayTree[wt].weight;
					}
				}
			}
			int h = 0;
			while (PeakTree[h].state == 0 || PeakTree[h].state == -2)
				h++;
			int min = PeakTree[h].L;
			for (int j = 0; j < N; j++)
			{
				if (PeakTree[j].L < min && PeakTree[j].state == -1)
				{
					min = PeakTree[j].L;
					h = j;
				}
			}
			p = h;
		}
		Ways[i] = PeakTree[p].L;
	}
	for (int i = 0; i < M; i++)
		cout << Ways[i] << endl;
}
