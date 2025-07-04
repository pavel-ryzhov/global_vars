#include <vector>
#include <map>
#include <iostream>
#include <limits.h>
#include <algorithm>

// ����������� - ��� �� ����� ��������
bool hasUnvisitedNodes(bool *visit, int numberPairs)
{
	for(int i = 0; i < numberPairs; i++)
	{
		if(visit[i] == false)
		{
			return true;
		}
	}
	return false;
}

int main()
{
	int numberNodes, startEdge, endEdge, lengthEdge, numberPairs, startPair, endPair;

	std::cin >> numberNodes;

	if(numberNodes == 1)
	{
		std::cout << 0;
		return 0;
	}

	std::vector<std::pair<int, int> > *tree = new std::vector<std::pair<int, int> >[numberNodes];	// ���� ������
	bool *visitNodes = new bool[numberNodes];														// ������ ��� �������� ���������� � ���������� ������
	int *distances = new int[numberNodes];															// ������ ���������� �� �����

	for(int i = 0; i < numberNodes; i++)
	{
		distances[i] = INT_MAX;
		visitNodes[i] = false;
	}
	// ���������� ������
	for(int i = 0; i < numberNodes-1; i++)
	{
		std::cin >> startEdge >> endEdge >> lengthEdge;
		tree[startEdge-1].push_back(std::pair<int, int>(lengthEdge, endEdge));
		tree[endEdge-1].push_back(std::pair<int, int>(lengthEdge, startEdge));
	}

	for(int i = 0; i < numberNodes; i++)
	{
		std::sort(tree[i].begin(), tree[i].end());
	}

	std::cin >> numberPairs;

	if(numberPairs < 1) return -1;

	std::pair<int, int> *pairs = new std::pair<int, int>[numberPairs];	// ������, �������� ���� ��� ������

	// ���������� ������� ��� ��� ������
	for(int i = 0; i < numberPairs; i++)
	{
		std::cin >> startPair >> endPair;
		pairs[i].first = startPair;
		pairs[i].second = endPair;
	}

	int indexMinNode = 0;
	int maxValue = INT_MAX;
	bool exit;

	for(int j = 0; j < numberPairs; j++)
	{
		
		distances[pairs[j].first-1] = 0;	// ������� ����� ��� ������

		do
		{
			exit = true;

			// ���� ������ ���������� ���� ��� ���������
			for(int i = 0; i < numberNodes; i++)
			{
				if(distances[i] < maxValue && visitNodes[i] == false) indexMinNode = i;
			}

			// �������� ���� ��� �����������
			visitNodes[indexMinNode] = true;

			// ���� ������ ���������� �� �������� �����
			for(int p = 0; p < tree[indexMinNode].size(); p++)
			{
				int indexNode = tree[indexMinNode][p].second - 1;
				lengthEdge = tree[indexMinNode][p].first;
				if(visitNodes[indexNode] != true && (distances[indexNode] > (distances[indexMinNode] + lengthEdge))) 
					distances[indexNode] = distances[indexMinNode] + lengthEdge;
			}

		}while(hasUnvisitedNodes(visitNodes, numberPairs));

		// ����� � ���� ����� ����
		std::cout << distances[pairs[j].second-1] << std::endl;

		// ���������� �������� ���������� � ��������� ��� ���������� ������
		for(int i = 0; i < numberNodes; i++)
		{
			visitNodes[i] = false;
			distances[i] = INT_MAX;
		}
	}

	delete []visitNodes;
	delete []tree;
	delete []distances;
	delete []pairs;

	return 0;
}