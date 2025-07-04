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

void buildSparseTable(long euLength, long stLength, long *sparseTable, long *sparseTablePos, long *depthArray)
{
	for (long i = 0; i < euLength; i++)
	{
        long arg = stLength*i;
		sparseTable[arg] = depthArray[i];
		sparseTablePos[arg] = i;
	}
	for (long j = 1; j < stLength; j++)
	{
		for (long i = 0; i < euLength; i++)
		{
			long temp = i + pow2(j-1);
			long arg1 = i*stLength + j;
			long arg2 = temp*stLength + j;
			if (temp >= euLength)
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

long answerRMQ(long *sparseTable, long euLength, long stLength, long *firstDate, long first, long second)
{
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
     long deg = log2bottom(right-left);
     long temp = right - pow2(deg) + 1;
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
    long stLength = log2top(euLength);
    long spLength = euLength*stLength;
	long *eulerTour = new(nothrow) long[euLength];
	long *depthArray = new(nothrow) long[euLength];
	long *firstDate = new(nothrow) long[nodeCount];
	long *sparseTable = new(nothrow) long[spLength];
	long *sparseTablePos = new(nothrow) long[spLength];
	memset(firstDate, -1, nodeCount*sizeof(long));
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
    buildSparseTable(euLength, stLength, sparseTable, sparseTablePos, depthArray);

    long taskCount;
    cin >> taskCount;
    for (long i = 0; i < taskCount; i++)
    {
        long first, second;
        cin >> first >> second;
        long lca = eulerTour[sparseTablePos[answerRMQ(sparseTable, euLength, stLength, firstDate, first, second)]];
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
 
