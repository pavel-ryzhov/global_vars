
#include <vector>
#include <iostream>

//////////////////////////////////////////////////////////////////////////

// ���������� �������� �������� �����, ����������� �� ���������� ������ �����
int log2(int aValue) 
{
  int res = 1;
  while (1<<res < aValue)  
    ++res;
  return res;
}

//////////////////////////////////////////////////////////////////////////
// TGraphEdge ���������, �������������� ����� �����

struct TGraphEdge
{
  int iParent;
  int iChild;
  int iWeight;

  TGraphEdge CopyInvert() const
  {
    TGraphEdge temp;
    temp.iParent = iChild;
    temp.iChild = iParent;
    temp.iWeight = iWeight;
    return temp;
  }

  friend std::istream& operator >> (std::istream& aInStream, TGraphEdge& aEdge);
};

// ������
std::istream& operator >>(std::istream& aInStream, TGraphEdge& aEdge)
{
  aInStream >> aEdge.iParent >> aEdge.iChild >> aEdge.iWeight;
  return aInStream;
}

typedef std::vector<TGraphEdge> TEdgeArray;

//////////////////////////////////////////////////////////////////////////
// CNode

class CNode
{
  friend class CWeightedTree;

public:
  CNode(){};
  ~CNode(){}; 

public:
  int EdgeCount() const
  {
    return (int)iNodeEdges.size();
  }

  const TGraphEdge& Edge(int aIndex) const
  {
    return iNodeEdges[aIndex];
  }

private:
  // ��� ������� ���� ������ ��� �����, ��������� �� ����
  std::vector<TGraphEdge> iNodeEdges;
};

//////////////////////////////////////////////////////////////////////////
// CWeightedTree

class CWeightedTree
{
public:
  CWeightedTree(const TEdgeArray& aEdgeList)
  {
    ConstructFromEdges(aEdgeList);
  }

  ~CWeightedTree(){}

public:
  int NodeCount() const
  {
    return (int)iNodeArray.size();
  }

  const CNode& operator[](int aIndex) const
  {
    return iNodeArray[aIndex];
  }

private:
  void ConstructFromEdges(const TEdgeArray& aEdgeList)
  {
    size_t edgeCount = aEdgeList.size();
    iNodeArray.resize(edgeCount + 2); // ����� �� 1 ������, ��� ����� + ��������� ����� ���������� � 1
    for (size_t i = 0; i < edgeCount; ++i)
    { 
      iNodeArray[aEdgeList[i].iParent].iNodeEdges.push_back(aEdgeList[i]);
      iNodeArray[aEdgeList[i].iChild].iNodeEdges.push_back(aEdgeList[i].CopyInvert());
    }
  }

private:
  std::vector<CNode> iNodeArray;
};

//////////////////////////////////////////////////////////////////////////
// TNodeInfo

struct TNodeInfo
{
  TNodeInfo() : iDepth(0), iWeight(0) {}

  int iDepth; // ���������� ����� �� �����
  int iWeight; // ����� ����� ����� �� �����
};

//////////////////////////////////////////////////////////////////////////
// TTreeInfo

struct TTreeInfo
{
  std::vector<TNodeInfo> iNodes;
  std::vector<int> iPosInTraversal; // ������ ������� ��������� ���� � ������
  std::vector<int> iTraversalOrder; // ������� ������ ������
};

//////////////////////////////////////////////////////////////////////////
// DepthFirstTraversal

class DepthFirstTraversal
{
public:
  static void Run(const CWeightedTree& aTree, TTreeInfo& aTreeInfo)
  {
    if (aTree.NodeCount() < 1) 
      return;

    aTreeInfo.iNodes.resize(aTree.NodeCount());
    aTreeInfo.iPosInTraversal.resize(aTree.NodeCount(), -1);

    DftStep(aTree, aTreeInfo, 1);
  }

private:
  static void DftStep(const CWeightedTree& aTree, TTreeInfo& aTreeInfo, int aNode)
  {
    if (aTreeInfo.iPosInTraversal[aNode] == -1) 
      aTreeInfo.iPosInTraversal[aNode] = (int)aTreeInfo.iTraversalOrder.size();
    else
    {
      return;
    }
    aTreeInfo.iTraversalOrder.push_back(aNode);
    int edgeCount = aTree[aNode].EdgeCount();
    for (int i = 0; i < edgeCount; ++i)
    {
      const TGraphEdge& edge = aTree[aNode].Edge(i);
      int child = edge.iChild;
      if (aTreeInfo.iPosInTraversal[child] == -1)
      {
        aTreeInfo.iNodes[child].iWeight = 
          aTreeInfo.iNodes[aNode].iWeight + edge.iWeight;
        aTreeInfo.iNodes[child].iDepth = 
          aTreeInfo.iNodes[aNode].iDepth + 1;
        DftStep(aTree, aTreeInfo, child);
        aTreeInfo.iTraversalOrder.push_back(aNode);
      }
    }
  }
};

//////////////////////////////////////////////////////////////////////////
// CRmqSlow - ����� ����������� �������� �� ������� �� O(Nlog(N))

class CRmqSlow
{
public:
  CRmqSlow();
  ~CRmqSlow();
  // ��������� �������������� �� O(Nlog(N))
  void Run(const std::vector<int>& aSequence);
  // ���� ������� �� ������� [aLeftIndex; aRightIndex] �� O(1)
  int Get(int aLeftIndex, int aRightIndex);

private:
  int argmin(int aIndex1, int aIndex2) const;

private:
  std::vector<int> iSequence; 
  std::vector< std::vector<int> > iSparseTable;
};

//////////////////////////////////////////////////////////////////////////
// CRmqSlow - ����� ����������� �������� �� ������� �� O(Nlog(N))

CRmqSlow::CRmqSlow() {}
CRmqSlow::~CRmqSlow() {}

void CRmqSlow::Run(const std::vector<int>& aSequence)
{
  iSequence.assign(aSequence.begin(), aSequence.end());
  int len = (int)iSequence.size();
  int logLen = log2(len);
  iSparseTable.assign(len, std::vector<int>(logLen + 1, 0));

  for (int left = 0; left < len; ++left)
  {
    iSparseTable[left][0] = left;
  }
  for ( int i = 1; i <= logLen; ++i )
  {
    for (int left = 0; left < len; ++left)
    {
      int right = left + (1<<(i-1));
      if (right < len)
      {
        iSparseTable[left][i] = argmin(iSparseTable[left][i-1], iSparseTable[right][i-1]);
      }
      else
      {
        iSparseTable[left][i] = iSparseTable[left][i-1];
      }
    }
  }
}

int CRmqSlow::Get(int aLeftIndex, int aRightIndex)
{
  if (aLeftIndex > aRightIndex) 
    return Get(aRightIndex, aLeftIndex);
  int k = log2(aRightIndex - aLeftIndex + 1) - 1;
  return argmin(iSparseTable[aLeftIndex][k], iSparseTable[aRightIndex - (1<<k) + 1][k]);
}

//////////////////////////////////////////////////////////////////////////

int CRmqSlow::argmin(int aIndex1, int aIndex2) const
{
  return (iSequence[aIndex1] <= iSequence[aIndex2]) ? aIndex1 : aIndex2;
}

//////////////////////////////////////////////////////////////////////////
// CLca

class CLca
{
public:
  // ������ aTreeInfo ������ ������������ ������, ��� CLca
  // �������� �������� aTreeInfo �� ����������
  CLca(const TTreeInfo& aTreeInfo);
  ~CLca();
public:
  // ���������� �� O(N)
  void Run();
  // ���������� ����� ������ ��� �����, �������� �������� 
  int GetLca(int aNodeNum1, int aNodeNum2) const;

private:
  // ���������� ��������� �� ���� ���������� ������
  void CalcMinsInUniqueBlocks();
  // ���������� �������� � �����
  void CalcMinsInBlock(int aBlockNumber);
  // ���������� ��������� ����� ����� ������
  void CalcMinsBetweenBlocks();

private:
  // ������ ������� ��������� ���� � ������
  int FirstPosInTraversal(int aNodeIndex) const;
  // ����� ����� �� ���� �� �����
  int Depth(int aNodeIndex) const;
  // �������������� ���������� ������
  int BlockId(int aBlockNumber) const;
  // ��������� � ������ ����, ���������������� �������� � �����
  // aLeft, aRight - �������� ������ �����
  int MinInBlock(int aBlockIndex, int aLeft, int aRight) const;
  // ��������� � ������ ���� � ����������� ��������
  int MinByDepth(int aPos1, int aPos2) const;

private:
  typedef std::vector< std::vector<int> > TBlock;

private:
  const TTreeInfo* iTreeInfo;
  int iBlockLen;
  int iBlockCount;
  mutable std::vector<int> iBlockIds;
  // ����� ����� ����������� ������� � ������� ������
  CRmqSlow* iMinsBetweenBlocks; 
  // �������� ������������ �������� ������ ������� ����������� �����
  std::vector<TBlock> iMinsInBlocks; 
};

//////////////////////////////////////////////////////////////////////////
// CLca

CLca::CLca(const TTreeInfo& aTreeInfo)
{
  iTreeInfo = &aTreeInfo;
  int traversalLen = (int)iTreeInfo->iTraversalOrder.size();
  iBlockLen = (log2(traversalLen) + 1) / 2;
  iBlockCount = traversalLen / iBlockLen + (traversalLen % iBlockLen ? 1: 0);
  iBlockIds.resize(iBlockCount, -1);
  iMinsInBlocks.resize(1 << (iBlockLen - 1));
  iMinsBetweenBlocks = new CRmqSlow();
}

CLca::~CLca()
{
  delete iMinsBetweenBlocks;
}

//////////////////////////////////////////////////////////////////////////

void CLca::Run()
{
  CalcMinsInUniqueBlocks();
  CalcMinsBetweenBlocks();
}

int CLca::GetLca(int aNodeNum1, int aNodeNum2) const
{
  int pos1 = FirstPosInTraversal(aNodeNum1);
  int pos2 = FirstPosInTraversal(aNodeNum2);
  if (pos1 > pos2)
  {
    pos1 = FirstPosInTraversal(aNodeNum2);
    pos2 = FirstPosInTraversal(aNodeNum1);
  }
  int res = pos1;
  int blockLeft = pos1 / iBlockLen + 1;
  int blockRight = pos2 / iBlockLen - 1;
  int prefix = pos1 % iBlockLen;
  int suffix = pos2 % iBlockLen;
  if (blockLeft <= blockRight)
  {
    int minBlockNumber = iMinsBetweenBlocks->Get(blockLeft, blockRight);
    res = MinInBlock(minBlockNumber, 0, iBlockLen - 1);
  }
  if (blockLeft - 1 < blockRight + 1)
  {
    res = MinByDepth(res, MinInBlock(blockLeft - 1, prefix, iBlockLen - 1));
    res = MinByDepth(res, MinInBlock(blockRight + 1, 0, suffix));
  } // �����, ��� ������� � ����� �����
  else
  {
    res = MinByDepth(res, MinInBlock(blockLeft - 1, prefix, suffix));
  }

  return iTreeInfo->iTraversalOrder[res];
}

//////////////////////////////////////////////////////////////////////////

void CLca::CalcMinsInUniqueBlocks()
{
  for (int i = 0; i < iBlockCount; ++i)
  {
    if (iMinsInBlocks[BlockId(i)].size() == 0) // ���� �������� ��� ������ ���� ����� �� ���������
    {
      CalcMinsInBlock(i);
    }
  }
}

void CLca::CalcMinsInBlock(int aBlockNumber)
{
  int traversalLen = (int)iTreeInfo->iTraversalOrder.size(); // ����� ������������������
  TBlock& block = iMinsInBlocks[BlockId(aBlockNumber)]; // ������� ����
  int blockOffset = aBlockNumber * iBlockLen; // �������� �������� ����� �� ������ ������������������

  block.assign(iBlockLen, std::vector<int>(iBlockLen, 0));

  for (int left = 0; left < iBlockLen; ++left)
  {
    block[left][left] = left;
    for (int right = left + 1; right < iBlockLen; ++right)
    {
      if (blockOffset + right < traversalLen)
        block[left][right] = MinByDepth(blockOffset + block[left][right - 1],
        blockOffset + right) - blockOffset;
      else
        block[left][right] = block[left][right - 1];
    }
  }
}

void CLca::CalcMinsBetweenBlocks()
{
  std::vector<int> blockMinArray(iBlockCount); // ������� � ������ �����
  for (int i = 0; i < iBlockCount; ++i)
  {
    blockMinArray[i] = Depth(iTreeInfo->iTraversalOrder[MinInBlock(i, 0, iBlockLen - 1)]);
  }

  iMinsBetweenBlocks->Run(blockMinArray);
}

//////////////////////////////////////////////////////////////////////////

int CLca::FirstPosInTraversal(int aNodeIndex) const
{
  return iTreeInfo->iPosInTraversal[aNodeIndex];
}

int CLca::Depth(int aNodeIndex) const
{
  return iTreeInfo->iNodes[aNodeIndex].iDepth;
}

int CLca::BlockId(int aBlockNumber) const
{
  if (iBlockIds[aBlockNumber] == -1)
  {
    int res = 0;
    const std::vector<TNodeInfo>& nodes = iTreeInfo->iNodes; // R?
    const std::vector<int>& traversal = iTreeInfo->iTraversalOrder;
    for (int i = 0; i < iBlockLen - 1; ++i)
    {
      res = res<<1;
      int blockOffset = aBlockNumber * iBlockLen;
      if (blockOffset + i + 1 < traversal.size())
      {
        if (nodes[traversal[blockOffset + i + 1]].iDepth > nodes[traversal[blockOffset + i]].iDepth)
          res++;
      }
      else
      {
        res++;
      }
    }
    iBlockIds[aBlockNumber] = res;
  }

  return iBlockIds[aBlockNumber];
}

int CLca::MinInBlock(int aBlockIndex, int aLeft, int aRight) const
{
  int index = aBlockIndex * iBlockLen + iMinsInBlocks[BlockId(aBlockIndex)][aLeft][aRight];
  return index;
}

int CLca::MinByDepth(int aPos1, int aPos2) const
{
  return (Depth(iTreeInfo->iTraversalOrder[aPos1]) <= Depth(iTreeInfo->iTraversalOrder[aPos2])) ? aPos1 : aPos2;
}

//////////////////////////////////////////////////////////////////////////

struct TQuery
{
  int iFirstNode;
  int iSecondNode;
};

typedef std::vector<TQuery> TQueryList;

//////////////////////////////////////////////////////////////////////////

// ������ ����� � ��������
void readGraphAndQueries(TEdgeArray& aEdgeList, TQueryList& aQueries)
{
  int edgeCount; 
  std::cin >> edgeCount;
  --edgeCount; // ����� �� 1 ������, ��� �����
  if (edgeCount > 0)
    aEdgeList.resize(edgeCount);
  for (int i = 0; i < edgeCount; ++i)
  {
    std::cin >> aEdgeList[i]; 
  }

  int queryCount;
  std::cin >> queryCount;
  aQueries.resize(queryCount);
  for (int i = 0; i < queryCount; ++i)
  {
    std::cin >> aQueries[i].iFirstNode;
    std::cin >> aQueries[i].iSecondNode;
  }
}

//////////////////////////////////////////////////////////////////////////

int main()
{
  TEdgeArray edgeList;
  TQueryList queries;

  readGraphAndQueries(edgeList, queries);

  CWeightedTree tree(edgeList);

  TTreeInfo treeInfo;
  DepthFirstTraversal::Run(tree, treeInfo);

  CLca lca(treeInfo);
  lca.Run();

  int queryCount = (int)queries.size();
  for (int i = 0; i < queryCount; ++i)
  {
    int ancestor = lca.GetLca(queries[i].iFirstNode, queries[i].iSecondNode);
    int weight =  treeInfo.iNodes[queries[i].iFirstNode].iWeight + 
                  treeInfo.iNodes[queries[i].iSecondNode].iWeight - 
                  2 * treeInfo.iNodes[ancestor].iWeight;
    std::cout << weight << std::endl;
  }

  return 0;
}
