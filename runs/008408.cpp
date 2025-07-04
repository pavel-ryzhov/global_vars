#include <iostream>
#include <list>
#include <vector>


struct Edge
{
	int name;
	int price;
	Edge(int n,int p);
	Edge(){};
};


class Stack
{
private:
	std::list<Edge> data;
	std::vector<int> way;
public:
	bool Empty();
	void AddEdge(std::list<Edge> edge,int price);
	void push_back(Edge &edge);
	void push_back_way(int i);
	Edge front();
};


class Top
{
private:
	int name;
	std::list<Edge> edge;
	std::list<Edge>::iterator itEdge;
public:
	Top(){};
	~Top(){};
	std::list<Edge> GetAll();
	void Add(int name,int price);
	void Load(int i);
};


class Object
{
private:
	std::list<Top> allTop;
	std::list<Top>::iterator itAllTop;
public:
	void Load(int number);
	int Search(int first, int last);
	Object(){};
	~Object(){};
};


int main (int argc, char* argv[])
{
	Object object;
	int i;
	std::cin >> i;
	object.Load(i);
	std::cin >> i;
	for (int j = 0; j < i; j++)
	{
		int intInF,intInL;
		std::cin >> intInF >> intInL;
		std::cout << object.Search(intInF,intInL) << std::endl;
	}
}
void Object::Load(int number)
{
	Top tempTop;
	int intInF,intInL,intInP;
	for(int i = 0 ;i <= number ; i++){tempTop.Load(i);allTop.push_back(tempTop);}
	for(int i = 1; i < number ; i++)
	{
		std::cin >> intInF >> intInL >> intInP;
		
		itAllTop = allTop.begin();
		for(int j = 0; j < intInF ; j++){++itAllTop;}
		(*itAllTop).Add(intInL,intInP);

		itAllTop = allTop.begin();
		for(int j = 0; j < intInL ; j++){++itAllTop;}
		(*itAllTop).Add(intInF,intInP);
	}
}

int Object::Search(int first,int last)
{
	Stack stack;
	Edge tempEdge(first,0);
	stack.push_back(tempEdge);

	while(!stack.Empty())
	{
		tempEdge = stack.front();
		stack.push_back_way(tempEdge.name);

		if (tempEdge.name == last) return tempEdge.price;

		itAllTop = allTop.begin();
		for(int j = 0; j < tempEdge.name ; j++){++itAllTop;}
		stack.AddEdge((*itAllTop).GetAll(), tempEdge.price);
	}
	return 0;
}
void Top::Load(int i){name = i;}
void Top::Add(int name, int price)
{
	Edge edg(name,price);
	edge.push_back(edg);
}
std::list<Edge> Top::GetAll()
{
	return edge;
}
Edge::Edge(int n,int p)
{
	name = n;
	price = p;
}
bool Stack::Empty()
{
	if (data.empty()) return true;
	else return false;
}
void Stack::AddEdge(std::list<Edge> edge,int price)
{
	std::list<Edge>::iterator itEdge = edge.begin();
	int size = edge.size(),size_way = way.size(),fl;
	for (int i = 0 ; i < size ; i++)
	{
		fl = 0;
		for (int i = 0; i < size_way; i++) if ((*itEdge).name == way[i]) fl = 1;
		if (fl == 0)
		{
			Edge edge((*itEdge).name,(*itEdge).price + price);
			data.push_back(edge);
		}
		itEdge++;
	}
}
void Stack::push_back(Edge &edge)
{
	data.push_back(edge);
}
void Stack::push_back_way(int i)
{
	way.push_back(i);
}
Edge Stack::front()
{
	Edge temp;
	temp = data.front();
	data.pop_front();
	return temp;
}
