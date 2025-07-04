#include <cstdlib>
#include <iostream>
#include <vector>

#define MYASSERT(X) if(!(X)) { cout << "error at line: " << __LINE__ << std::endl; exit(1); }

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::swap;
using std::pair;

const int MAX = 40000;
const int INF = MAX*500;
const int NO_PATH = -1;

int preprocess(const vector<vector<int> > &tree,
				vector<int> &rounds,
				vector<int> &roundPos,
				vector<int> &heights,
				vector<bool> &usedNodes,
				vector<int> &fathers,
				int nodeNum,
				int height);
void preprocessDown(const vector<vector<int> > &tree,
				vector<int> &rounds,
				vector<int> &roundPos,
				vector<int> &heights,
				int nodeNum,
				int height);
void buildSegmentTree(
				const vector<int> &rounds,
				const vector<int> &roundPos,
				const vector<int> &heights,
				vector<int> &segTree,
				int nodeNum,
				int left,
				int right);
int findPath(const vector<vector<int> > &tree,
				pair<int,int> inputNodes,
				const vector<int> &rounds,
				const vector<int> &roundPos,
				const vector<int> &heights,
				const vector<int> &segTree,
				const vector<int> &fathers);
int findFromRoot(const vector<vector<int> > &tree, const vector<int> &fathers, int nodeNum);
int findLCA(int i, 
			int segLeft,
			int segRight, 
			int left, 
			int right, 
			const vector<int> &segTree,
			const vector<int> &heights);

void out(const vector<int> &segTree)
{
	for (int i = 0; i < segTree.size(); ++i)
	{
		cout << segTree[i] << " ";
	}
	cout << endl;
}

int main()
{
	// ***** load data
	int verticies = 0;
	cin >> verticies;
	MYASSERT(verticies >= 0 && verticies < MAX);
	if (verticies == 0) 
	{
		cout << NO_PATH << endl;
		return 0;
	}
	vector<vector<int> > tree(verticies);
	for (int i = 0; i < verticies; ++i)
	{
		tree[i].resize(verticies, INF);
	}
	for (int i = 0; i < verticies-1; ++i)
	{
		int a, b, w;
		cin >> a >> b >> w;
		MYASSERT(a >= 0 && a < MAX);
		MYASSERT(b >= 0 && b < MAX);
		MYASSERT(w >= 0 && w < MAX);
		if (a > b) swap(a, b);
		tree[a-1][b-1] = tree[b-1][a-1] = w;
	}
	int nodesNum = 0;
	cin >> nodesNum;
	MYASSERT(nodesNum >= 0 && nodesNum < MAX);
	if (nodesNum == 0)
	{
		cout << NO_PATH << endl;
		return 0;
	}
	vector<pair<int,int> > inputNodes(nodesNum);
	for (int i = 0; i < nodesNum; ++i)
	{
		int a, b;
		cin >> a >> b;
		inputNodes[i].first= a-1;
		inputNodes[i].second= b-1;
	}

	// ***** preprocess
	// build walking list
	vector<int> rounds;
	vector<int> roundPos(tree.size(), -1);
	vector<int> heights(tree.size(), 0);
	vector<bool> usedNodes(tree.size(), false);
	vector<int> fathers(tree.size(), 0);
	preprocess(tree, rounds, roundPos, heights, usedNodes, fathers, 0, 0);

	// build segments tree
	vector<int> segTree(rounds.size() * 4 + 1, -1);
	buildSegmentTree(rounds, roundPos, heights, segTree, 1, 0, rounds.size() - 1);

	// ***** find paths
	for (int i = 0; i < inputNodes.size(); ++i)
	{
		int result = findPath(tree, inputNodes[i], rounds, roundPos, heights, segTree, fathers);
		cout << result << endl;
	}

	return 0;
}

void buildSegmentTree(const vector<int> &rounds,
						const vector<int> &roundPos,
						const vector<int> &heights,
						vector<int> &segTree, 
						int i, 
						int left,
						int right)
{
	if (left == right) 
		segTree[i] = rounds[left];
	else
	{
		int medium = (left + right) >> 1;
		buildSegmentTree(rounds, roundPos, heights, segTree, i*2, left, medium);
		buildSegmentTree(rounds, roundPos, heights, segTree, i*2+1, medium+1, right);
		if (heights[segTree[i*2]] < heights[segTree[i*2+1]])
			segTree[i] = segTree[i*2];
		else
			segTree[i] = segTree[i*2+1];
	}
}

int preprocess(const vector<vector<int> > &tree,
				vector<int> &rounds,
				vector<int> &roundPos,
				vector<int> &heights,
				vector<bool> &usedNodes,
				vector<int> &fathers,
				int nodeNum,
				int height)
{
	rounds.push_back(nodeNum);
	if (roundPos[nodeNum] == -1) roundPos[nodeNum] = rounds.size() -1;
	heights[nodeNum] = height;
	usedNodes[nodeNum] = true;
	for (int i = 0; i < tree.size(); ++i)
	{
		if (tree[nodeNum][i] != INF && !usedNodes[i]) 
		{	
			fathers[i] = nodeNum;
			preprocess(tree, rounds, roundPos, heights, usedNodes, fathers, i, height + 1);
			rounds.push_back(nodeNum);
		}
	}
	return 0;
}

int findPath(const vector<vector<int> > &tree,
				pair<int,int> inputNodes,
				const vector<int> &rounds,
				const vector<int> &roundPos,
				const vector<int> &heights,
				const vector<int> &segTree,
				const vector<int> &fathers)
{
	int ra = findFromRoot(tree, fathers, inputNodes.first);
	int rb = findFromRoot(tree, fathers, inputNodes.second);
	int first = roundPos[inputNodes.first];
	int last = roundPos[inputNodes.second];
	if (first > last) swap(first, last);
	int lcaNum = findLCA(1, 0, rounds.size()-1, first, last, segTree, heights);
	int rlca = findFromRoot(tree, fathers, lcaNum);
	return ra + rb - 2 * rlca;
	return 0;
}

int findFromRoot(const vector<vector<int> > &tree, const vector<int> &fathers, int nodeNum)
{
	int curNode = nodeNum;
	int prevNode = 0;
	int w = 0;

	while(curNode != 0)
	{
		prevNode = curNode;
		curNode = fathers[prevNode];
		if (tree[prevNode][curNode] != INF) w += tree[prevNode][curNode];
		else return NO_PATH;
	}
	return w;
}

int findLCA(int i, 
			int segLeft,
			int segRight, 
			int left, 
			int right, 
			const vector<int> &segTree,
			const vector<int> &heights)
{
	if (segLeft == left && segRight == right)
	{
		return segTree[i];
	}
	int segMed = (segLeft + segRight) >> 1;
	if (right <= segMed) 
	{
		return findLCA(i*2, segLeft, segMed, left, right, segTree, heights);
	}
	if (left > segMed)
	{
		return findLCA(i*2+1, segMed+1, segRight, left, right, segTree, heights);
	}
	int result1 = findLCA(i*2, segLeft, segMed, left, segMed, segTree, heights);
	int result2 = findLCA(i*2+1, segMed+1, segRight, segMed+1, right, segTree, heights);
	return heights[result1] < heights[result2] ? result1 : result2;
}

