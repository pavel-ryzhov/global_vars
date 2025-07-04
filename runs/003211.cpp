#include <iostream>
#include <vector>
#include <new>
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

node *readGraph(long *nodeCount, vector<node *> *nodeMas) 
{	
	node* res;
	cin >> *nodeCount;
	try 
	{
		for (long i = 0; i < *nodeCount; i++)
			(*nodeMas).push_back(new node(i+1));
	}
	catch(bad_alloc err)
	{
		long size = (*nodeMas).size();
		for (long i = 0; i < size; i++)
			delete (*nodeMas)[i];
		throw err;
	}
	for (long i = 0; i < (*nodeCount)-1; i++)
	{
		long from, to, length;
		cin >> from >> to >> length;
		(*nodeMas)[from-1]->addChild((*nodeMas)[to-1]);
		(*nodeMas)[to-1]->setFather((*nodeMas)[from-1], length);
	}
	res = (*nodeMas)[0];
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

long log (long n)
{
	int res = 1;
	while (1<<res < n)  ++res;
	return res;
}

long log2 (long n)
{
	int res = 1;
	while (1<<res < n)  ++res;
	if (1<<res > n) --res;
	return res;
}

long pow2 (long n)
{
     long res = 1;
     for (long i = 0; i < n; i++) res *= 2;
     return res;
}

void buildSparseTable(long euLength, long *sparseTable, long *sparseTablePos, long *depthArray)
{
     long stLength = log(euLength);
     long spLength = euLength*stLength;
     for (long i = 0; i < euLength - 1; i++)
     {
         sparseTable[stLength*i] = depthArray[i] < depthArray[i+1]?depthArray[i]:depthArray[i+1];
         sparseTablePos[stLength*i] = depthArray[i] < depthArray[i+1]?i:i+1;
     }
     sparseTable[stLength*(euLength - 1)] = depthArray[euLength - 1];
     sparseTablePos[stLength*(euLength - 1)] = euLength - 1;
     for (long j = 1; j < stLength; j++)
     {
         for (long i = 0; i < euLength; i++)
         {
             long temp = i + pow2(j);
             if (temp >= euLength)
             {
                  sparseTable[i*stLength + j] = sparseTable[i*stLength + j - 1];
                  sparseTablePos[i*stLength + j] = sparseTablePos[i*stLength + j - 1];
             }
             else if (sparseTable[i*stLength + j - 1] < sparseTable[temp*stLength + j - 1])
             {
                  sparseTable[i*stLength + j] = sparseTable[i*stLength + j - 1];
                  sparseTablePos[i*stLength + j] = sparseTablePos[i*stLength + j - 1];
             }
             else
             {
                  sparseTable[i*stLength + j] = sparseTable[temp*stLength + j - 1];
                  sparseTablePos[i*stLength + j] = sparseTablePos[temp*stLength + j - 1];
             }
         }
     } 
}

long answerRMQ(long *sparseTable, long euLength, long *firstDate, long first, long second)
{
     long left, right;
     long stLength = log(euLength);
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
     long deg = log2(right-left);
     long temp = right - pow2(deg);
     return sparseTable[left*stLength + deg] < sparseTable[temp*stLength + deg]?left*stLength + deg:temp*stLength + deg;
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
	long *eulerTour = new(nothrow) long[euLength];
	long *depthArray = new(nothrow) long[euLength];
	long *firstDate = new(nothrow) long[nodeCount];
	long *sparseTable = new(nothrow) long[euLength*log(euLength)];
	long *sparseTablePos = new(nothrow) long[euLength*log(euLength)];
	for (long i = 0; i < nodeCount; i++) firstDate[i] = -1;
	if (!eulerTour || !depthArray || !firstDate || !sparseTable || !sparseTablePos)
    {	
		if (eulerTour) delete[] eulerTour;
		if (depthArray) delete[] depthArray;
		if (firstDate) delete[] firstDate;
		if (sparseTable) delete[] sparseTable;
		if (sparseTablePos) delete[] sparseTablePos;
		delete list;
		cerr << "Err: Need more memory" << endl;
		return 1;
	}
	computeArrays(list, eulerTour, depthArray, firstDate);
    buildSparseTable(euLength, sparseTable, sparseTablePos, depthArray);

    
    long taskCount;
    cin >> taskCount;
    for (long i = 0; i < taskCount; i++)
    {
        long first, second;
        cin >> first >> second;
        if (first == second)
        {
           cout << 0 << endl;
           continue;
        }
        long lca = eulerTour[sparseTablePos[answerRMQ(sparseTable, euLength, firstDate, first, second)]];
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
 
