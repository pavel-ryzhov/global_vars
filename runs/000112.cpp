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
	int state; //-2 - ещё не рассматривали, -1 - временная, 0 - постоянная, вычеркнута
};

int N, M;
struct Way *WayTree;
struct Way *Ways;
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
	cin >> M;
	Ways = new struct Way[M];
	for (int i = 0; i < M; i++)
	{
		cin >> Ways[i].start;
		cin >> Ways[i].end;
		Ways[i].weight = -1;
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

void printWayTree()
{
	cout << "WayTree" << endl;
	for (int i = 0; i < N - 1; i++)
	{
		cout << "start = " << WayTree[i].start << " end = " << WayTree[i].end << " weight = " << WayTree[i].weight << endl;
	}
}

void printWays(bool all)
{
	if (all)
	{
		cout << "Ways" << endl;
		for (int i = 0; i < M; i++)
		{
			cout << "start = " <<Ways[i].start << " end = " << Ways[i].end << " weight = " << Ways[i].weight << endl;
		}
	}
	else
	{
		for (int i = 0; i < M; i++)
		{
			cout << Ways[i].weight << endl;
		}
	}
}

void printPeakTree()
{
	cout << "PeakTree" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << "L = " << PeakTree[i].L << " st = " << PeakTree[i].state << endl;
		cout << "  ";
		for (int j = 0; j < PeakTree[i].near.size(); j++)
			cout << PeakTree[i].near[j] << " ";
		cout << endl;
	}
}

int main()
{
	read();
	makePeakTree();
	for (int i = 0; i < M; i++)
	{
		for (int ii = 0; ii < N; ii++)
			PeakTree[ii].state = -2;
		int s = Ways[i].start - 1;
		int t = Ways[i].end - 1;
		int p = s;
		PeakTree[p].L = 0;
		while (p != t)
		{
			PeakTree[p].state = 0;
			for (int j = 0; j < PeakTree[p].near.size(); j++)
			{
				if (PeakTree[PeakTree[p].near[j] - 1].state == 0)
					j++;
				if (j < PeakTree[p].near.size())
				{
					int k = PeakTree[p].near[j] - 1;
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
		Ways[i].weight = PeakTree[p].L;
	}
	printWays(false);
}
