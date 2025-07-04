#include <vector>
#include <iostream>

// узел
class TElement
{
public:
	// сосед узла
	class TNeighbour
	{
	private:
		TElement* element; // указатель на соседа
		int distance; // расстояние до соседа
		bool used; // пройдена ли данная связь
	public:
		TNeighbour();
		TNeighbour(TElement*, int);
		TElement* getNeighbour();
		int getDistance();
		bool isUsed();
		void setUsed();
		void clear();
		~TNeighbour();
	};
	typedef std::vector<TElement::TNeighbour>::iterator TNeighPointer;
private:
	int number; // номер узла
	std::vector<TNeighbour> neighbours; // список соседей
public:
	TElement();
	~TElement();
	int getNumber(); // получить номер узла
	void setNumber(int); // задать номер узла
	void addNeighbour(TNeighbour*); // добавить соседа
	void clear(); // очистка всех меток
	// получить начало и конец списка соседей
	TNeighPointer begin();
	TNeighPointer end();
};

// дерево
class TNodes
{
private:
	std::vector<TElement*> nodes; // список узлов
public:
	TNodes();
	~TNodes();
	void addElement(TElement*); // добавить узел
	TElement* getElement(int); // найти узел по его номеру
	void fill(); // ввод
	void print(); // вывод содержимого (для тестирования)
	void clear(); // очистка всех меток
};

// пара узлов, для которых ищется расстояние
class TPair
{
private:
	int first, second;
public:
	TPair();
	TPair(int, int);
	~TPair();
	int getFirst();
	int getSecond();
};

// множество пар узлов
class TPairs
{
private:
	std::vector<TPair> list; // список пар узлов
public:
	TPairs();
	~TPairs();
	void addPair(TPair*); // добавить пару узлов
	void fill(); // ввод
	int findRoute(TNodes*, TPair*); // найти расстояние между парой
	int findR(TNodes*, TElement*, int, int); // найти расстояние от элемента
	void execute(TNodes*); // поиск расстояний между заданными парами
};

TPair::TPair()
{

}

TPair::TPair(int f, int s)
{
	first = f;
	second = s;
}

TPair::~TPair()
{

}

int TPair::getFirst()
{
	return first;
}

int TPair::getSecond()
{
	return second;
}

TPairs::TPairs()
{

}

TPairs::~TPairs()
{

}

void TPairs::addPair(TPair* pair)
{
	list.push_back(*pair);
}

void TPairs::fill()
{
	int i, t1, t2, pairnum;
	TPair *pair;

	std::cin >> pairnum;
	for (i = 0; i < pairnum; i++)
	{
		std::cin >> t1;
		std::cin >> t2;
		pair = new TPair(t1, t2);
		list.push_back(*pair);
	}
}

int TPairs::findR(TNodes* nodes, TElement* element,
		int previous, int destination)
{
	TElement::TNeighPointer t;
	int distance;

	t = element->begin();
	while (t != element->end())
	{
		if (t->getNeighbour()->getNumber() == previous)
			t->setUsed();
		if (!(t->isUsed()))
		{
			t->setUsed();
			if (t->getNeighbour()->getNumber() == destination)
				return t->getDistance();
			distance = findR(nodes, t->getNeighbour(),
					element->getNumber(), destination);
			if (distance != -1)
				return distance + t->getDistance();
		}
		t++;
	}

	return -1;
}

int TPairs::findRoute(TNodes* nodes, TPair* pair)
{
	TElement* element;
	TElement::TNeighPointer t;
	int destination, distance;

	element = nodes->getElement(pair->getFirst());
	destination = pair->getSecond();
	distance = 0;
	t = element->begin();
	while (t != element->end())
	{
		if (t->getNeighbour()->getNumber() == destination)
			return t->getDistance();
		t->setUsed();
		distance = findR(nodes, t->getNeighbour(),
				element->getNumber(), destination);
		if (distance != -1)
			return distance + t->getDistance();
		t++;
	}

	return 0;
}

void TPairs::execute(TNodes* nodes)
{
	std::vector<TPair>::iterator t = list.begin();
	int distance;

	while (t != list.end())
	{
		distance = findRoute(nodes, &(*t));
		std::cout << distance << std::endl;
		nodes->clear();
		t++;
	}
}

TElement::TElement()
{

}

TElement::~TElement()
{

}

TElement::TNeighbour::TNeighbour()
{

}

TElement::TNeighbour::~TNeighbour()
{

}

TElement::TNeighbour::TNeighbour(TElement *elem, int dist)
{
	element = elem;
	distance = dist;
	used = false;
}

TElement* TElement::TNeighbour::getNeighbour()
{
	return element;
}

int TElement::TNeighbour::getDistance()
{
	return distance;
}

bool TElement::TNeighbour::isUsed()
{
	return used;
}

void TElement::TNeighbour::setUsed()
{
	used = true;
}

void TElement::TNeighbour::clear()
{
	used = false;
}

int TElement::getNumber()
{
	return number;
}

void TElement::setNumber(int num)
{
	number = num;
}

void TElement::addNeighbour(TNeighbour* neighbour)
{
	neighbours.push_back(*neighbour);
}

void TElement::clear()
{
	TNeighPointer t;

	t = neighbours.begin();
	while (t != neighbours.end())
	{
		t->clear();
		t++;
	}
}

TElement::TNeighPointer TElement::begin()
{
	return neighbours.begin();
}

TElement::TNeighPointer TElement::end()
{
	return neighbours.end();
}

TNodes::TNodes()
{

}

TNodes::~TNodes()
{

}

void TNodes::addElement(TElement* element)
{
	nodes.push_back(element);
}

TElement* TNodes::getElement(int num)
{
	TElement *element;
	std::vector<TElement*>::iterator t = nodes.begin();

	while (t != nodes.end())
	{
		if ((*t)->getNumber() == num)
			return *t;
		t++;
	}

	element = new TElement();
	element->setNumber(-1);

	return element;
}

void TNodes::fill()
{
	TElement *element1, *element2;
	TElement::TNeighbour *neighbour;
	int i, t1, t2, l, nodenum;

	std::cin >> nodenum;
	nodenum--;
	for (i = 0; i < nodenum; i++)
	{
		std::cin >> t1;
		std::cin >> t2;
		std::cin >> l;
		element1 = getElement(t1);
		element2 = getElement(t2);
		neighbour = new TElement::TNeighbour(element2, l);
		element1->addNeighbour(neighbour);
		neighbour = new TElement::TNeighbour(element1, l);
		element2->addNeighbour(neighbour);
		if (element1->getNumber() == -1)
		{
			element1->setNumber(t1);
			addElement(element1);
		}
		if (element2->getNumber() == -1)
		{
			element2->setNumber(t2);
			addElement(element2);
		}
	}
}

void TNodes::print()
{
	std::vector<TElement*>::iterator i;
	TElement::TNeighPointer j;

	i = nodes.begin();
	while (i != nodes.end())
	{
		std::cout << (*i)->getNumber() << " ";
		j = (*i)->begin();
		while (j != (*i)->end())
		{
			std::cout << j->getNeighbour()->getNumber() << " ";
			std::cout << j->getDistance() << " ";
			j++;
		}
		std::cout << std::endl;
		i++;
	}
}

void TNodes::clear()
{
	std::vector<TElement*>::iterator t;

	t = nodes.begin();
	while (t != nodes.end())
	{
		(*t)->clear();
		t++;
	}
}

int main()
{
	TNodes nodes;
	TPairs pairs;;

	nodes.fill();
	//nodes.print();
	pairs.fill();
	pairs.execute(&nodes);

	return 0;
}
