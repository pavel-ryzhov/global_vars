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


class Top
{
private:
	int name;
	std::list<Edge> data;
	std::list<Edge>::iterator itdata;
public:
	Top(){};
	~Top(){};
	void Add(int name,int price);
	int GetName(){return name;}
	int Size();
	Edge Pop(std::vector<std::vector<int> > first);
	void Load(int i);
};


class Object
{
private:
	std::list<Top> data;
	std::list<Top>::iterator itdata;
	std::vector<Edge> order;
	std::vector<std::vector<int> > first;
public:
	//инициирует наше дерево
	void Load(int number);
	//дерево преобразует в вектор Order
	void Reload();
	//поиск ответа на запрос между  first и last
	int Search(int first, int last);
	int abs(int a);
	Object(){};
	~Object(){};
};


int main (int argc, char* argv[])
{
	Object object;
	int i;
	std::cin >> i;
	object.Load(i);
	object.Reload();
	std::cin >> i;
	for (int j = 0; j < i; j++)
	{
		int intInF,intInL;
		std::cin >> intInF >> intInL;
		std::cout << object.Search(intInF,intInL) << std::endl;
	}
	std::cin >> i;
}

void Object::Load(int number)
{
	Top tempTop;
	int intInF,intInL,intInP;
	for(int i = 0 ;i <= number ; i++)
	{
		std::vector<int> temp;
		first.push_back(temp);
		tempTop.Load(i);
		data.push_back(tempTop);
	}
	for(int i = 1; i < number ; i++)
	{
		std::cin >> intInF >> intInL >> intInP;

		itdata = data.begin();
		for(int j = 0; j < intInF ; j++){++itdata;}
		(*itdata).Add(intInL,intInP);

		itdata = data.begin();
		for(int j = 0; j < intInL ; j++){++itdata;}
		(*itdata).Add(intInF,intInP);
	}
}

void Object::Reload()
{
	int j = 0;
	Edge edge;
	itdata = data.begin();
	itdata++;
	while(true)
	{
		if ((*itdata).Size() == 0) break;
		edge = (*itdata).Pop(first);
		first[edge.name].push_back(j);
		order.push_back(edge);
		itdata = data.begin();
		for (int i = 0 ;i < edge.name; i++) itdata++;
		j++;
	}
}

int Object::Search(int f,int l)
{
	int needf = 0,needl = 0, sizef = first[f].size(),sizel = first[l].size(),sum;
	sum = abs(first[f][0] - first[l][0]);
	for (int i = 0; i < sizef; i++)
	for (int j = 0; j < sizel; j++)
	{
		if (abs(first[f][i] - first[l][j]) < sum)
		{
			sum = abs(first[f][i] - first[l][j]);
			needf = i;
			needl = j;
		}
	}
	if (abs(first[f][needf] - first[l][needl]) == 1) 
	{
		if (first[f][needf] < first[l][needl]) return order[first[l][needl]].price;
		else return order[first[f][needf]].price;
	}
	if (abs(first[f][needf] - first[l][needl]) == 0) return 0;

	if (first[f][needf] > first[l][needl])
		sum = Search(f,order[first[f][needf] - 1].name) + Search(order[first[f][needf] - 1].name, l);
	else
		sum = Search(f,order[first[f][needf] + 1].name) + Search(order[first[f][needf] + 1].name, l);
	return sum;
}

int Object::abs(int i)
{
	if (i < 0) i = i*(-1);
	return i;
}

void Top::Load(int i)
{
	name = i;
}

void Top::Add(int name, int price)
{
	Edge edg(name,price);
	data.push_back(edg);
}
Edge Top::Pop(std::vector<std::vector<int> > first)
{
	Edge edge;
	itdata = data.end();
	if (data.size() > 1)
	{
		itdata--;
		edge = (*itdata);
		while (first[edge.name].size() != 0 && itdata != data.begin())
		{
			itdata--;
			edge = (*itdata);
		}
		data.erase(itdata);
		return edge;
	}
	edge = data.front();
	data.pop_front();
	return edge;
}

int Top::Size()
{
	return data.size();
}

Edge::Edge(int n,int p)
{
	name = n;
	price = p;
}