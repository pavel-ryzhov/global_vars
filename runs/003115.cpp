#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>

using std::cin;
using std::cout;
using std::endl;

using std::max;
using std::min;

using std::vector;
using std::pair;
using std::make_pair;

/*
Определение дерева
*/

class TreeNode {
public:
	TreeNode();
	int getLength(int neighbour) const {
		return neighbours_[neighbour].second;
	}
	int getLengthToRoot() const {
		return lengthToRoot_;
	}
	int getFirstInOrder() const {
		return firstInOrder_;
	}
	int getHeight() const {
		return height_;
	}
	int getNeighbourCount() const {
		return neighbours_.size();
	}
	int getNeighbour(int neighbour) const {
		return neighbours_[neighbour].first;
	}
	void addNeighbour (int neighbours, int length) {
		neighbours_.push_back(make_pair(neighbours, length));
	}
	void setLengthToRoot(int length) {
		lengthToRoot_ = length;
	}
	void setHeight (int parentHeight) {
		height_ = parentHeight + 1;
	}
	void setFirstInOrder (int firstInOrder) {
		firstInOrder_ = firstInOrder;
	}
private:
	vector< pair<int, int> > neighbours_;
	int lengthToRoot_;
	void deleteSons_(TreeNode *); 
	int height_;
	int firstInOrder_;
};

TreeNode::TreeNode():
	neighbours_(), lengthToRoot_(0), firstInOrder_(-1), height_(0) {}


class Tree {
public:
	Tree(int nodeCount): tree_(nodeCount) {}
	void createTree();
	void visitInOrder(vector<int> * order);	
	const TreeNode * getNode(int nodeNumber) const {
		return &tree_[nodeNumber];
	}
private:
	enum color {WHITE, BLACK, GREY};
	vector<TreeNode> tree_;
	void visitNode_ (int node, vector<int> * order, vector<int> * colors);
};

void Tree::visitNode_(int node, vector<int> *order, vector<int> *colors) {
	colors->at(node) = GREY;
	order->push_back(node);
	if (tree_[node].getFirstInOrder() == -1) {
		tree_[node].setFirstInOrder(order->size() - 1);
	}
	for (int neighbour = 0; neighbour < tree_[node].getNeighbourCount(); ++neighbour) {
		if (colors->at(tree_[node].getNeighbour(neighbour)) == WHITE) {
			tree_[tree_[node].getNeighbour(neighbour)].setHeight(tree_[node].getHeight());
			tree_[tree_[node].getNeighbour(neighbour)].setLengthToRoot(tree_[node].getLengthToRoot() + tree_[node].getLength(neighbour));
			visitNode_(tree_[node].getNeighbour(neighbour), order, colors);
			order->push_back(node);
		}
	}
	colors->at(node) = BLACK;
}

void Tree::visitInOrder(vector<int> * order) {
	vector<int> colors(tree_.size(), WHITE);
	visitNode_(0, order, &colors);			
}

void Tree::createTree() {
	for (int edge = 0; edge < (int)tree_.size() - 1; ++edge) {
		int first, second;
		int length;
		cin >> first >> second >> length;
		--first;
		--second;
		tree_[first].addNeighbour(second, length);
		tree_[second].addNeighbour(first, length);
	}
}

/*
Окончание определения дерева.
*/

/*
Определение класса решающего задачу RMQ (+/-)1
*/

class RMQfinder {
public:
	RMQfinder(vector<int> * range, Tree * tree): 
	  range_(range), tree_(tree), blocksMin_(), sparseTable_(), minInUniqueBlocks_(), masks_(), 
		  blockSize_(max(0.5 * log((double)(range_->size()))/log(2.0), 1.0)) {}
	void preprocess();
	int getRMQ(int first, int second) const;
private:
	vector<int> * range_;
	Tree * tree_;
	int blockSize_;
	vector<int> blocksMin_;
	vector< vector<int> > sparseTable_;
	//i-ый элемент равен k, если 2^k <= i < 2^(k+1)
	vector<int> powersOf2_;
	//маски блоков
	vector<int> masks_;
	//предподсчитанные минимумы для всех типов блоков
	vector< vector< vector<int> > > minInUniqueBlocks_;
	void fillMasks_();
	void fillMinInUniqueBlocks_();
	void fillPowersOf2_ ();
	int getValue_(int key) const;
	void setBlocksMin_ ();
	int findBlockMin_ (int begin, int end) const;
	void fillSparseTable_ ();
	int findMinimumOf2_ (int first, int second) const;
	int getMinimumBetweenBlocks_ (int begin, int end) const; 
};

int RMQfinder::getValue_(int key) const {
	return tree_->getNode(key)->getHeight(); 
}

int RMQfinder::findBlockMin_(int begin, int end) const {
	int blockSize = end - begin;
	int blockMin = begin;
		for (int positionInBlock = 0; positionInBlock < blockSize; ++positionInBlock) {
 			if (getValue_(range_->at(begin + positionInBlock)) < getValue_(range_->at(blockMin))) {
				blockMin = blockSize*blocksMin_.size() + positionInBlock;
			}
		}
	return blockMin;
}

void RMQfinder::setBlocksMin_() {
	while (blockSize_*(blocksMin_.size() + 1) < range_->size()) {
		blocksMin_.push_back(findBlockMin_(blockSize_*blocksMin_.size(), blockSize_*blocksMin_.size() + blockSize_));
	}
	blocksMin_.push_back(findBlockMin_(blockSize_*blocksMin_.size(), range_->size() - 1));
}

int RMQfinder::getRMQ(int first, int second) const {
	int firstBlock = div(first, blockSize_).quot;
	int secondBlock = div(second, blockSize_).quot;
	int minInFirst = 0;
	int minInSecond = 0;
	int minimumBetween = 0;
	if (secondBlock == firstBlock) { 
		return range_->at(firstBlock*blockSize_ + minInUniqueBlocks_[masks_[firstBlock]][first - firstBlock*blockSize_][second - first]);
	} else {
		minInFirst = firstBlock*blockSize_ + minInUniqueBlocks_[masks_[firstBlock]][first - firstBlock*blockSize_][blockSize_ - 1];
		minInSecond = secondBlock*blockSize_+ minInUniqueBlocks_[masks_[secondBlock]][0][second - secondBlock*blockSize_];	
		if (secondBlock - firstBlock < 2) {
			minimumBetween = minInFirst;
		} else {
			minimumBetween = getMinimumBetweenBlocks_(firstBlock, secondBlock);
		}
	}
	return range_->at(findMinimumOf2_(findMinimumOf2_(minInFirst, minInSecond), minimumBetween));
}

int RMQfinder::findMinimumOf2_ (int first, int second) const {
	return getValue_(range_->at(first)) < getValue_(range_->at(second)) ? first : second; 
}

void RMQfinder::fillSparseTable_() {
	sparseTable_.resize(blocksMin_.size());
	for (int begin = 0; begin < blocksMin_.size(); ++begin) {
		sparseTable_[begin].push_back(blocksMin_[begin]);
	}
	for (int length = 1; pow(2.0, double(length)) < blocksMin_.size(); ++length) {
		for (int begin = 0; begin < blocksMin_.size(); ++begin) {
			sparseTable_[begin].push_back(
				findMinimumOf2_(sparseTable_[begin][length - 1], 
						sparseTable_[min(begin + (int)pow(2.0,double(length - 1)), (int)(sparseTable_.size()) - 1)][length - 1])
			);
		}
	}	
}

void RMQfinder::fillPowersOf2_() {
	double power = 0;
	double length = 1;
	powersOf2_.push_back(0);
	while (length < blocksMin_.size()) {
		while (powersOf2_.size() < 2*length) {
			powersOf2_.push_back(int(power));
		}
		++power;
		length = pow(2.0, power);
	}
}

int RMQfinder::getMinimumBetweenBlocks_(int begin, int end) const {
	--end;
	++begin;
	int length = powersOf2_[end - begin + 1];
	return findMinimumOf2_(
		sparseTable_[begin][length], sparseTable_[end - pow(2.0, length) + 1][length]
	);
}

void RMQfinder::preprocess() {
	setBlocksMin_();
	fillSparseTable_();
	fillPowersOf2_();
	fillMasks_();
	fillMinInUniqueBlocks_();
}

void RMQfinder::fillMasks_() {
	int position = 0;
	int blockNumber = 0;
	masks_.resize(ceil((double)div(range_->size(), blockSize_).quot) + 1);
	while (position < range_->size() && blockNumber < masks_.size()) {
		int mask = 0;
		int positionInBlock = 1;
		while (positionInBlock < blockSize_ && position + positionInBlock < range_->size()) {
			if (getValue_(range_->at(position + positionInBlock)) < getValue_(range_->at(position + positionInBlock - 1))) {
				mask *= 2;
			} else {
			    mask *= 2;
				++mask;
			}
			++positionInBlock;
		}
		while (positionInBlock < blockSize_) {
			mask *= 2;
			++mask;
			++positionInBlock;
		} 
		position += blockSize_;
		if (blockNumber < masks_.size()) {
			masks_[blockNumber] = mask;
		}
		++blockNumber;
	}
}

int bitK(int mask, int k) { 
	return bool((int)pow(2.0, k) & mask);
}

void RMQfinder::fillMinInUniqueBlocks_() {
	minInUniqueBlocks_.resize((int)pow(2.0, blockSize_ - 1));
	for (int mask = 0; mask < minInUniqueBlocks_.size(); ++mask) {
		minInUniqueBlocks_[mask].resize(blockSize_);
		vector<int> height(blockSize_);
		height[0] = 0;
		minInUniqueBlocks_[mask][0].resize(blockSize_);
		for (int begin = 1; begin < blockSize_; ++begin) {
			if (bitK(mask, blockSize_ - 1 - begin) == 0) {
				height[begin] = height[begin - 1] - 1;
			} else {
				height[begin] = height[begin - 1] + 1;
			}
			minInUniqueBlocks_[mask][begin].resize(blockSize_);
			minInUniqueBlocks_[mask][begin][0] = begin;
		}
		for (int begin = 0; begin < blockSize_; ++begin) {
			for (int length = 1; length < blockSize_; ++length) {
				if (length + begin >= blockSize_) {
					minInUniqueBlocks_[mask][begin][length] = minInUniqueBlocks_[mask][begin][blockSize_ - begin - 1];	
				} else {
					if (height[begin + length] < height[minInUniqueBlocks_[mask][begin][length - 1]]) {
						minInUniqueBlocks_[mask][begin][length] = begin + length;
					} else {
						minInUniqueBlocks_[mask][begin][length] = minInUniqueBlocks_[mask][begin][length - 1];
					}
				}
			}
		}
	}
}

/*
Окончание определения класса решающего задачу RMQ
*/

/*
Определение класса решающего задачу LCA
*/
class LCAfinder {
public:
	LCAfinder(Tree * tree): tree_(tree), order_(), rmq_(NULL) {} 
	void preprocess();
	int getLCA (int first, int second) const; 
private:
	Tree * tree_;
	vector<int> order_;
	RMQfinder * rmq_;
};

void LCAfinder::preprocess() {
	tree_->visitInOrder(&order_);
	rmq_ = new RMQfinder(&order_, tree_);
	rmq_->preprocess();
}

int LCAfinder::getLCA(int first, int second) const {
	--first;
	--second;
	return rmq_->getRMQ(
			min(tree_->getNode(first)->getFirstInOrder(), tree_->getNode(second)->getFirstInOrder()), 
			max(tree_->getNode(first)->getFirstInOrder(), tree_->getNode(second)->getFirstInOrder())
		) + 1;
}
/*
Окончание определения класса решающего задачу LCA
*/

class PathFinder {
public:
	PathFinder(Tree * tree): tree_(tree), theLCAfinder_(tree) {}
	void answerQueries();
	void init();
private:
	Tree * tree_;
	LCAfinder theLCAfinder_;	
	vector< pair<int,int> > queries_;
	void readQueries_();
};

void PathFinder::init() {
	theLCAfinder_.preprocess();
	readQueries_();
}

void PathFinder::readQueries_() {
	int queryCount;
	cin >> queryCount;
	queries_.resize(queryCount);
	for (int query = 0; query < queryCount; ++query) {
		int node1, node2;
		cin >> node1 >> node2;
		queries_[query] = make_pair(node1, node2);
	}
}

void PathFinder::answerQueries() {
	for (int query = 0; query < queries_.size(); ++query) {
		int lca =
			theLCAfinder_.getLCA(min(queries_[query].first, queries_[query].second), max(queries_[query].first, queries_[query].second));
		int length = tree_->getNode(queries_[query].first - 1)->getLengthToRoot() + tree_->getNode(queries_[query].second - 1)->getLengthToRoot() - 2*tree_->getNode(lca - 1)->getLengthToRoot();
		cout << length << endl;
	}	
}

int main () {
	int nodeCount;
	cin >> nodeCount;
	Tree tree(nodeCount);
	tree.createTree();
	PathFinder thePathFinder(&tree);
	thePathFinder.init();
	thePathFinder.answerQueries();
	return 0;
}
