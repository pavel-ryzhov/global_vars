#include <iostream>
#include <vector>

using namespace std;

class CTree
{
public:
	/**
	\���������� ������
	\treeSize - ������ ������.
	*/
	CTree(int treeSize)
	{
		treeList.resize(treeSize);
		order.reserve(3 * treeSize);
		heights.resize(treeSize, -1);
		first.resize(treeSize, -1);
		dist.resize(treeSize, -1);
	}

	/**
	\��������� ����� � ������.
	\firstVer - ����� ������ �����.
	\secondVer - ����� ����� �����.
	\len - ��� �����.
	*/
	void addEdge(int firstVer, int secondVer, int len)
	{
		if (firstVer < treeList.size() && secondVer < treeList.size())
		{
			treeList[firstVer].push_back(make_pair(secondVer, len));
			treeList[secondVer].push_back(make_pair(firstVer, len));
		}
	}

	//������������.
	void preCalc()
	{
		if (treeList.size() != 0)
		{
			dfs(0, 0, 0);
			rmTree.resize(4 * order.size(), - 1);
			buildRmTree(0, 0, order.size());
		}
	}

	/**
	\���������� ���������� ����� ����� ������.
	\firstVer - ����� ������ �������.
	\secondVer - ����� ������ �������.
	*/
	int getDist(int firstVer, int secondVer)
	{
		int retVal = 0;
		if (firstVer < treeList.size() && secondVer < treeList.size())
		{
			int commVer = findLca(firstVer, secondVer);
			retVal = dist[firstVer] + dist[secondVer] - 2 * dist[commVer];
		}
		return retVal;
	}

private:

	/**
	\����� ������ ������ ���� ������.
	\firstVer - ����� ������ �������.
	\secondVer - ����� ������ �������.
	*/
	int findLca(int firstVer, int secondVer)
	{
		int retVal = 0;
		if (first[firstVer] > first[secondVer])
		{
			swap(firstVer, secondVer);
		}
		int left = first[firstVer];
		int right = first[secondVer] + 1;
		retVal = findMin(0, 0, order.size(), left, right);
		return retVal;
	}

	/**
	\����� ������� � ����������� ������� � ������ ��������.
	\root - ������ �������� ���������.
	\startLeft - ����� ������� �������� ���������.
	\startRight - ������ ������� �������� ���������.
	\curLeft - ����� ������� �������� �������.
	\curRight -������ ������� �������� �������.
	*/
	int findMin(int root, int startLeft, int startRight, int curLeft, int curRight)
	{
		int retVal = 0;
		int medium = (startLeft + startRight) / 2;
		if (startLeft == curLeft && startRight == curRight)
		{
			retVal = rmTree[root];
		}
		else if (curLeft >= medium)
		{
			retVal = findMin(2 * root + 2, medium, startRight, curLeft, curRight);
		}
		else if (curRight <= medium)
		{
			retVal = findMin(2 * root + 1, startLeft, medium, curLeft, curRight);
		}
		else
		{
			int anc1 = findMin(2 * root + 1, startLeft, medium, curLeft, medium);
			int anc2 = findMin(2 * root + 2, medium, startRight, medium, curRight);;
			if (heights[anc1] < heights[anc2])
			{
				retVal = anc1;
			}
			else
			{
				retVal = anc2;
			}
		}
		return retVal;
	}

	/**
	\����� ������ � �������(�������������).
	\curVer - ����� ������� �������.
	\curHeight - ������ ������� �������.
	\curPath - �������� ���� �� ����� �� ������� �������.
	*/
	void dfs(int curVer, int curHeight, int curPath)
	{
		order.push_back(curVer);
		heights[curVer] = curHeight;
		dist[curVer] = curPath;
		first[curVer] = order.size() - 1;
		for (int nextIdx = 0; nextIdx < treeList[curVer].size(); ++nextIdx)
		{
			int nextVer = treeList[curVer][nextIdx].first;
			int len = treeList[curVer][nextIdx].second;
			if (heights[nextVer] == -1)
			{
				dfs(nextVer, curHeight + 1, curPath + len);
				order.push_back(curVer);
			}
		}
	}

	/**
	\���������� ������ ��������.
	\curIdx - ������ ������� ������� � ������ ��������.
	\left - ������ �������.
	\right - ����� �������.
	*/
	void buildRmTree(int curIdx, int left, int right)
	{
		if (right - left != 1)
		{
			int medium = (left + right) / 2;
			buildRmTree(2 * curIdx + 1, left, medium);
			buildRmTree(2 * curIdx + 2, medium, right);
			int leftMin = rmTree[2 * curIdx + 1];
			int rightMin = rmTree[2 * curIdx + 2];
			if (heights[leftMin] < heights[rightMin])
			{
				rmTree[curIdx] = leftMin;
			}
			else
			{
				rmTree[curIdx] = rightMin;
			}
		}
		else
		{
			rmTree[curIdx] = order[left];
		}
	}

private:
	vector < vector <pair <int, int> > >	treeList;				//������. Pair: First - ����������, Second - ���. 
	vector < int>							order;					//������� ������ � ������.
	vector < int>							heights;				//������ ������.
	vector < int>							first;					//��������� �� ������ ������� � ������� order.
	vector < int>							rmTree;					//������ �������� �� ������� order.
	vector < int>							dist;					//���������� �� ����� �� ������.
};


int main()
{
	int verCount = 0;
	int first = 0;
	int second = 0;
	int dist = 0;
	cin >> verCount;
	CTree lcaTree(verCount);
	for (int i = 0; i < verCount - 1; ++i)
	{
		cin >> first >> second >> dist;
		--first;
		--second;
		lcaTree.addEdge(first, second, dist);
	}
	lcaTree.preCalc();
	int queryCount = 0;
	cin >> queryCount;
	for (int i = 0; i < queryCount; ++i)
	{
		cin >> first >> second;
		--first;
		--second;
		cout << lcaTree.getDist(first, second) << endl;
	}
	return 0;
}