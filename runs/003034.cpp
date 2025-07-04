#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>

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

namespace
{
using namespace std;

class Cache
{
public:
	explicit Cache(unsigned int size = 1024*1024, int filler = -1, unsigned int windowSize = 512):
	realSize(size),
	filler(filler),
	pFile(0),
	left(filler),
	changed(false),
	mem(0),
	windowSize(windowSize)
	{
		unsigned int tail = realSize % windowSize;
		if (tail != 0)
		{
			int head = realSize / windowSize;
			alignedSize = (head + 1) * windowSize;
		}
		else alignedSize = realSize;

		pFile = fopen("cache.tmp", "w+");
		for (int i = 0; i < alignedSize; ++i)
		{
			fwrite(&filler, sizeof(int), 1, pFile);
		}
		mem = (int *)calloc(windowSize, sizeof(int));

		int result;
		result = fseek(pFile, 0, SEEK_SET);
		if (result) { printf("error11");exit(0);}
		result = fread(mem, sizeof(int), windowSize, pFile);
		if (result != windowSize) { printf("error22");exit(0);}
		left = 0;
	}

	~Cache()
	{
		this->flush();
		free(mem);
		fclose(pFile);
	}

	int & operator[](int index)
	{
		if (index < 0) return filler;
		if (index >= realSize) return filler;
		updateCache(index);
		return mem[index % windowSize];
	}

	void flush()
	{
		int result;
		result = fseek(pFile, left * windowSize*sizeof(int), SEEK_SET);
		if (result) { printf("error1");exit(0);}
		result = fwrite(mem, sizeof(int), windowSize, pFile);
		if (result != windowSize) { printf("error2");exit(0);}
	}

private:
	void updateCache(int index)
	{
		int result;
		if (index >= left && index < left + windowSize) return;

		result = fseek(pFile, left * windowSize * sizeof(int), SEEK_SET);
		if (result) { printf("error3");exit(0);}
		result = fwrite(mem, sizeof(int), windowSize, pFile);
		if (result != windowSize) { printf("error4");exit(0);}

		left = index / windowSize;
		result = fseek(pFile, left * windowSize * sizeof(int), SEEK_SET);
		if (result) { printf("error5");exit(0);}
		result = fread(mem, sizeof(int), windowSize, pFile);
		if (result != windowSize) 
		{
			cout << windowSize << " " << result << endl;
			printf("error6");exit(0);
		}
	}

private:
	unsigned int windowSize;
	unsigned int realSize, alignedSize;
	int filler;
	FILE *pFile;
	unsigned int left;
	bool changed;
	int *mem;
};
};

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
				//vector<int> &segTree,
				Cache &segTree,
				int nodeNum,
				int left,
				int right);
int findPath(const vector<vector<int> > &tree,
				pair<int,int> inputNodes,
				const vector<int> &rounds,
				const vector<int> &roundPos,
				const vector<int> &heights,
				//const vector<int> &segTree,
				Cache &segTree,
				const vector<int> &fathers);
int findFromRoot(const vector<vector<int> > &tree, const vector<int> &fathers, int nodeNum);
int findLCA(int i, 
			int segLeft,
			int segRight, 
			int left, 
			int right, 
			//const vector<int> &segTree,
			Cache &segTree,
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
	//vector<int> segTree(rounds.size() * 4 + 1, -1);
	Cache segTree(rounds.size() * 4 + 1, -1, 1024);
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
						//vector<int> &segTree, 
						Cache &segTree,
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
				//const vector<int> &segTree,
				Cache &segTree,
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
			//const vector<int> &segTree,
			Cache &segTree,
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


