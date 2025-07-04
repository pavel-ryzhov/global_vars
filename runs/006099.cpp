#include <map>
#include <vector>
#include <iostream>
using namespace std;
typedef vector<int> vInt;

class myNode
{
	public:
	int len;
	vInt listLength;
	vInt listPrev;
	map<int,int> v;
};
class myTree
{
	vector<myNode> graph;
	int find(int beg, int end)
	{
		if(beg==end) return 0;
		myNode *nodeBeg = &graph[beg];
		myNode *nodeEnd = &graph[end];

		if(nodeBeg->len < nodeEnd->len)
		{
			swap(nodeBeg,nodeEnd);
			swap(beg,end);
		}

		int lenSegment = 0, step = 0;

		if(nodeBeg->listPrev[nodeEnd->len]!=end)
			for(int i=nodeEnd->len-1; ;i--)
				if(nodeBeg->listPrev[i]==nodeEnd->listPrev[i])
				{
					step=nodeEnd->len-i;
					lenSegment=nodeEnd->listLength[nodeEnd->len-step];
					break;
				}
		return lenSegment+nodeBeg->listLength[nodeEnd->len-step];
	}

	void precalc(int prev=1, int _this=1,vInt vecLen = vInt(),vInt vecPr = vInt(), int len=0)
	{
		myNode *node = &graph[_this];
		node->len = len;
		node->listLength = vecLen;
		node->listPrev = vecPr;

		if(prev!=_this)
		{
			node->listLength.push_back(node->v[prev]);
			node->listPrev.push_back(prev);
		}
		for(map<int,int>::iterator i=node->v.begin();i!=node->v.end();i++)
			if((*i).first!=prev)
				precalc(_this,(*i).first,node->listLength,node->listPrev,len+1);
		//Вычисляем растояние до каждого предка
		for(int i=node->listLength.size()-2; i>=0 ;i--)
			node->listLength[i]+=node->listLength[i+1];

	}
	public:

	myTree()
	{
		int N,M;

		cin>>N;
		graph.resize(N+1);
		//Заполняем граф
		for(int i=0;i<N-1;i++)
		{
			int a,b,c;
			cin>>a>>b>>c;
			graph[a].v[b]=c;
			graph[b].v[a]=c;
		}
		cin>>M;
		precalc();
		vInt out;
		//Поиск
		for(int i=0;i<M;i++)
		{
			int a,b;
			cin>>a>>b;
			out.push_back(find(a,b));
		}
		//Вывод
		for(int i=0;i<M;i++)
			cout<<out[i]<<'\n';
	}
};
int main()
{
	myTree t;
	return 0;
}

