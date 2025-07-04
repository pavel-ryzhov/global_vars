#include <iostream>
#include <vector>
#include <list>
#include <new>
#include <string.h>
using namespace std;

class node
{
	private:
		long num;
		node *father;
		long length;
		vector<node *> childs;
	public:
		node(long num);
		~node();
		void setFather(node *father, long length);
		void addChild(node *child);
		long getNum() {return this->num;}
		node *getFather() {return this->father;}
		long getChildsCount() {return this->childs.size();}
		node *getChild(int i) {return this->childs[i];}
		long getLength() {return this->length;}
};

node::node(long num)
{
	this->num = num;
}

node::~node()
{
	int size = this->childs.size();
	for (long i = 0; i < size; i++)
		delete this->childs[i];
}

void node::setFather(node *father, long length)
{
	this->father = father;
	this->length = length;
}

void node::addChild(node *child)
{
	this->childs.push_back(child);   
}

struct rib
{
	long a, b, len;
};

struct rib makeRib(long a, long b, long len)
{
	struct rib temp;
	temp.a = a;
	temp.b = b;
	temp.len = len;
	return temp;
}

node *readGraph(long *nodeCount, vector<node *> *nodeMas) 
{	
	node* res;
	list<struct rib> ribs;
	list<long> stack;
	cin >> *nodeCount;
	try 
	{
        long a, b, len;
		for (long i = 0; i < (*nodeCount) - 1; i++)
		{
			(*nodeMas).push_back(new node(i+1));
            cin >> a >> b >> len;
            ribs.push_back(makeRib(a, b, len));
        }
        (*nodeMas).push_back(new node(*nodeCount));
	}
	catch(bad_alloc err)
	{
		long size = (*nodeMas).size();
		for (long i = 0; i < size; i++)
			delete (*nodeMas)[i];
		throw err;
	}
    if (ribs.empty()) res = (*nodeMas)[0];
    else
    {
		list<struct rib>::iterator p = ribs.begin();
		res = (*nodeMas)[(p->a)-1];
		stack.push_back(p->a);
		stack.push_back(p->b);
		(*nodeMas)[(p->a)-1]->addChild((*nodeMas)[(p->b)-1]);
		(*nodeMas)[(p->b)-1]->setFather((*nodeMas)[(p->a)-1], p->len);
		p = ribs.erase(p);
		while (!stack.empty() && !ribs.empty())
		{
			long curStackSize = stack.size();
			vector<long> curStack;
			list<long>::iterator q = stack.begin();
			for (long i = 0; i < curStackSize; i++)
			{
               curStack.push_back(*q);
               q++;
            }
			stack.clear();
			p = ribs.begin(); 
			while (p != ribs.end())
			{
				bool flag = false;
				for (long i = 0; i < curStackSize; i++)
				{
					long curVertex = curStack[i];
					if (curVertex == p->a)
					{
						stack.push_back(p->a);
						stack.push_back(p->b);
						(*nodeMas)[(p->a)-1]->addChild((*nodeMas)[(p->b)-1]);
						(*nodeMas)[(p->b)-1]->setFather((*nodeMas)[(p->a)-1], p->len);
						p = ribs.erase(p);
						flag = true;
						break;
					}
					else if (curVertex == p->b)
					{
						stack.push_back(p->b);
						stack.push_back(p->a);
						(*nodeMas)[(p->b)-1]->addChild((*nodeMas)[(p->a)-1]);
						(*nodeMas)[(p->a)-1]->setFather((*nodeMas)[(p->b)-1], p->len);
						p = ribs.erase(p);
						flag = true;
						break;
					}	
				}
				if (!flag) p++;
			}
		}
	}
	return res;
}

void computeArrays(node *list, long *eulerTour, long *depthArray, long *firstDate)
{
	static long step;
	static long depth;
	long num = list->getNum();
	eulerTour[step] = num;
	depthArray[step] = depth;
	if (firstDate[num-1] == -1) firstDate[num-1] = step;
	long size = list->getChildsCount();
	++step;
	for (long i = 0; i < size; i++)
	{
        ++depth;
        computeArrays(list->getChild(i), eulerTour, depthArray, firstDate);
        eulerTour[step] = num;
        ++step;
	}
	--depth;
    eulerTour[step] = num;
	depthArray[step] = depth;
}

long log2top (long n)
{
	int res = 1;
	while (1<<res < n)  ++res;
	return res;
}

long log2bottom (long n)
{
	int res = 1;
	while (1<<res < n)  ++res;
	if (1<<res > n) --res;
	return res;
}

long pow2 (long n)
{
     long res = 1;
     for (long i = 0; i < n; i++) res = res<<1;
     return res;
}

void buildBlocksArray(long euLength, long blocksCount, long blocksSize, long *blocksArray, long *blocksArrayPos, long *depthArray)
{
     for (long i = 0; i < blocksCount - 1; i ++)
     {
         long offset = i*blocksSize;
         long min = depthArray[offset];
         long minPos = offset;
         for (long j = 1; j < blocksSize; j++)
         {
             if (depthArray[offset + j] < min)
             {
                 min = depthArray[offset + j];
                 minPos = offset + j;
             }
         }
         blocksArray[i] = min;
         blocksArrayPos[i] = minPos;
     }
     long i = blocksCount - 1;
     long offset = i*blocksSize;
     long lim = euLength - offset;
     long min = depthArray[offset];
     long minPos = offset;
     for (long j = 1; j < lim; j++)
     {
         if (depthArray[offset + j] < min)
         {
             min = depthArray[offset + j];
             minPos = offset + j;
         }
     }
     blocksArray[i] = min;
     blocksArrayPos[i] = minPos;
}

void buildSparseTable(long blocksCount, long stLength, long *sparseTable, long *sparseTablePos, long *blocksArray, long *blocksArrayPos)
{
	for (long i = 0; i < blocksCount; i++)
	{
        long arg = stLength*i;
		sparseTable[arg] = blocksArray[i];
		sparseTablePos[arg] = blocksArrayPos[i];
	}
	for (long j = 1; j < stLength; j++)
	{
		for (long i = 0; i < blocksCount; i++)
		{
			long temp = i + pow2(j-1);
			long arg1 = i*stLength + j;
			long arg2 = temp*stLength + j;
			if (temp >= blocksCount)
			{
				sparseTable[arg1] = sparseTable[arg1 - 1];
				sparseTablePos[arg1] = sparseTablePos[arg1 - 1];
			}
			else if (sparseTable[arg1 - 1] < sparseTable[arg2 - 1])
			{
				sparseTable[arg1] = sparseTable[arg1 - 1];
				sparseTablePos[arg1] = sparseTablePos[arg1 - 1];
			}
			else
			{
				sparseTable[arg1] = sparseTable[arg2 - 1];
				sparseTablePos[arg1] = sparseTablePos[arg2 - 1];
			}
		}
	} 
}

void buildMaskTable(long masksCount, long blocksSize, long **maskTable)
{
    for (long k = 0; k < masksCount; k++)
    {
        for (long i = 0; i < blocksSize; i++)
        {
            long offset = i*blocksSize;
            maskTable[k][offset + i] = i;
            for (long j = i + 1; j < blocksSize; j++)
            {
                unsigned long curMask = k;
                long min = 0;
                long curVal = 0;
                long minPos = i;
                for (long l = i + 1; l <= j; l++)
                {
                    if ((curMask>>(blocksSize-l-1)) & 01) curVal++;
                    else
                    {
                        curVal--;
                        if (curVal < min)
                        {
                            min = curVal;
                            minPos = l;
                        } 
                    }
                }
                maskTable[k][offset + j] = minPos;
                maskTable[k][j*blocksSize + i] = minPos;
            }
        }
    }
}

long computeMask(long blocksSize, long euLength, long blockNumber, long *depthArray)
{
    long blocksCountBottom = euLength/blocksSize;
    long offset = blockNumber*blocksSize;
    unsigned long res = 0;
    if (offset + blocksSize < euLength)
    {
        for (long i = blocksSize - 1; i > 0; i--)
        {
            unsigned long temp = depthArray[offset + i] - depthArray[offset + i-1] > 0?01:00;
            res = res | (temp << (blocksSize - 1 - i));
        }
    }
    else
    {
        for (long i = euLength - offset - 1; i > 0; i--)
        {
            unsigned long temp = depthArray[offset + i] - depthArray[offset + i-1] > 0?01:00;
            res = res | (temp << (blocksSize - 1 - i));
        }
    }
    return res;
}

long answerRMQ(long blocksSize, long euLength, long *depthArray, long **maskTable, long *sparseTable, long *sparseTablePos, long stLength, long left, long right)
{
     long leftSp, rightSp;
     long leftMin, rightMin;
     long leftBlock = left/blocksSize;
     long rightBlock = right/blocksSize;
     if (leftBlock == rightBlock)
     {
          return leftBlock*blocksSize + maskTable[computeMask(blocksSize, euLength, leftBlock, depthArray)][(left%blocksSize)*blocksSize + right%blocksSize];
     }
     if (left%blocksSize == 0)
     {
          leftSp = leftBlock;
          leftMin = -1;
     }
     else
     {
         leftSp = leftBlock + 1;
         leftMin = leftBlock*blocksSize + maskTable[computeMask(blocksSize, euLength, leftBlock, depthArray)][(left%blocksSize)*blocksSize + blocksSize - 1];
     }
     if ((right + 1)%blocksSize == 0)
     {
          rightSp = rightBlock;
          rightMin = -1;
     }
     else
     {
         rightSp = rightBlock - 1;
         rightMin = rightBlock*blocksSize + maskTable[computeMask(blocksSize, euLength, rightBlock, depthArray)][right%blocksSize];
     }
     
     long deg, temp, pos;
     if (rightSp < leftSp) pos = -1;
     else
     {
          deg = log2bottom(rightSp-leftSp);
          temp = rightSp - pow2(deg) + 1;
          pos = sparseTablePos[sparseTable[leftSp*stLength + deg] < sparseTable[temp*stLength + deg]?leftSp*stLength + deg:temp*stLength + deg];
     }
     
     long res;
     if (pos != -1) res = pos;
     else if (leftMin != -1) res = leftMin;
     else if (rightMin != -1) res = rightMin;
     else res = -1;
     
     if (leftMin != -1) res = depthArray[leftMin] < depthArray[res]?leftMin:res;
     if (rightMin != -1) res = depthArray[rightMin] < depthArray[res]?rightMin:res;
     return res;
}

int main()
{
	node *list;
	long nodeCount;
	vector<node *> nodeMas;
	try
	{
		list = readGraph(&nodeCount, &nodeMas);
    }
    catch(bad_alloc err)
    {
		cerr << "Err: Need more memory" << endl;
		return 1;
    }
    long euLength = 2*nodeCount-1;
    long blocksSize = euLength <= 2?1:log2top(euLength)/2;
    long blocksSizeSqr = blocksSize*blocksSize;
    long blocksCount = euLength/blocksSize;
    if (euLength%blocksSize) blocksCount++;
    long stLength = log2top(blocksCount);
    long spLength = blocksCount*stLength;
    long masksCount = pow2(blocksSize - 1);
	long *eulerTour = new(nothrow) long[euLength];
	long *depthArray = new(nothrow) long[euLength];
	long *firstDate = new(nothrow) long[nodeCount];
	memset(firstDate, -1, nodeCount*sizeof(long));
	long *blocksArray = new (nothrow) long[blocksCount];
	long *blocksArrayPos = new (nothrow) long[blocksCount];
	long *sparseTable = new(nothrow) long[spLength];
	long *sparseTablePos = new(nothrow) long[spLength];
	long **maskTable = new(nothrow) long *[masksCount];
	for (long i = 0; i < masksCount; i++)
    {
        maskTable[i] = new(nothrow) long[blocksSizeSqr];
    }
    if (!eulerTour || !depthArray || !firstDate || !blocksArray || !blocksArrayPos || !sparseTable || !sparseTablePos || !maskTable)
    {	
		if (eulerTour) delete[] eulerTour;
		if (depthArray) delete[] depthArray;
		if (firstDate) delete[] firstDate;
		if (blocksArray) delete[] blocksArray;
		if (blocksArrayPos) delete[] blocksArrayPos;
		if (sparseTable) delete[] sparseTable;
		if (sparseTablePos) delete[] sparseTablePos;
		if (maskTable) delete[] maskTable;
		delete list;
		cerr << "Err: Need more memory" << endl;
		return 1;
	}
	computeArrays(list, eulerTour, depthArray, firstDate);
	buildBlocksArray(euLength, blocksCount, blocksSize, blocksArray, blocksArrayPos, depthArray);
    buildSparseTable(blocksCount, stLength, sparseTable, sparseTablePos, blocksArray, blocksArrayPos);
    buildMaskTable(masksCount, blocksSize, maskTable);

    long taskCount;
    cin >> taskCount;
    for (long i = 0; i < taskCount; i++)
    {
        long first, second;
        cin >> first >> second;
        long left, right;
        if (firstDate[first-1] < firstDate[second-1])
        {
            left = firstDate[first-1];
            right = firstDate[second-1];
        }
        else
        {
            left = firstDate[second-1];
            right = firstDate[first-1];
        }
        long lca = eulerTour[answerRMQ(blocksSize, euLength, depthArray, maskTable, sparseTable, sparseTablePos, stLength, left, right)];
        long length = 0;
        node *temp = nodeMas[first-1];
        while (temp->getNum() != lca)
        {
              length += temp->getLength();
              temp = temp->getFather();
        }
        temp = nodeMas[second-1];
        while (temp->getNum() != lca)
        {
              length += temp->getLength();
              temp = temp->getFather();
        }
        cout << length << endl;
    }
	return 0;
}
 
