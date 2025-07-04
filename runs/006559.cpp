#include <assert.h>

#include <vector>
#include <set>
#include <list>
#include <iostream>
#include <algorithm>

using namespace std;

// Модуль graphINode
#ifndef GRAPH_INODE_H
#define GRAPH_INODE_H

// Интерфей связи между узлами. Тип содержимого, тип узлов
template<typename T> class IGraphLink;

// Узел. Тип содержимого, тип узлов
template<typename T>
class IGraphNode {
public:
	virtual ~IGraphNode() {};

	// Данные об узле
	virtual T GetInstance() = 0; 
	virtual void SetInstance(T value) = 0;

	// Длинна пути до данного узла
	virtual double GetVec() = 0; 
	virtual void SetVec(double value) = 0;

	virtual bool IsVisit() = 0;
	virtual void SetIsVisit(bool value) = 0;

	// Ребра графа, выходщие из данного узла
	virtual vector<IGraphLink<T>*>* GetLinks() = 0; 
};

template<typename T> 
class IGraphLink {
public:
	virtual ~IGraphLink() {};

	// Начало ребра
	virtual IGraphNode<T>* GetOwner() = 0; 
	virtual void SetOwner(IGraphNode<T>* value) = 0;

	// Конец ребра
	virtual IGraphNode<T>* GetTarget() = 0; 
	virtual void SetTarget(IGraphNode<T>* value) = 0;

	// Вес ребра
	virtual double GetWeight() = 0; 
	virtual void SetWeight(double value) = 0;
};

struct inode_free {
public:
	template<typename T>
	void operator() (const T* ptr) const {
		delete ptr;
	}
};

#endif

// Модуль graphNode
#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

template<typename T> class GraphNode;

// Стандартная реализация ребра графа
template<typename T>
class GraphLink : public IGraphLink<T> {
public:
	GraphLink() { m_Target = 0; m_Owner = 0; m_Weight = 0; }
	~GraphLink() { 
	}
public:
	// Начало ребра
	virtual IGraphNode<T>* GetOwner() { return m_Owner; }
	virtual void SetOwner(IGraphNode<T>* value) { m_Owner = (GraphNode<T>*)value; }

	// Конец ребра
	virtual IGraphNode<T>* GetTarget() { return m_Target; }
	virtual void SetTarget(IGraphNode<T>* value) { m_Target = (GraphNode<T>*)value; }

	// Вес ребра
	virtual double GetWeight() { return m_Weight; }
	virtual void SetWeight(double value) { m_Weight = value; }
protected:
	GraphNode<T>* m_Target;
    GraphNode<T>* m_Owner;
    double m_Weight;
};

// Стандартная реализация узла графа
template<typename T>
class GraphNode : public IGraphNode<T> {
public:
	GraphNode(T instance) { m_Instance = instance; m_Vec = 0;  m_isVisit = false; }
	~GraphNode() {
		for_each(m_links.begin(), m_links.end(), inode_free());
	}

public:
	// Данные об узле
	virtual T GetInstance() { return m_Instance; }
	virtual void SetInstance(T value) { m_Instance = value; }

	// Длинна пути до данного узла
	virtual double GetVec() { return m_Vec; }
	virtual void SetVec(double value) { m_Vec = value; }

	virtual bool IsVisit() { return m_isVisit; }
	virtual void SetIsVisit(bool value) { m_isVisit = value; }

	// Ребра графа, выходщие из данного узла
	virtual vector<IGraphLink<T>*>* GetLinks() { return (std::vector<IGraphLink<T>*>*)&m_links; }

protected:
	T m_Instance;
	double m_Vec;
	bool m_isVisit;
	vector<GraphLink<T>*> m_links;
};

#endif

// Модуль graphFunctor
#ifndef GRAPH_FUNCTOR_H
#define GRAPH_FUNCTOR_H

template<class T>
struct graph_node_less : public binary_function<T, T, bool>
{
public:
	bool operator()(const T& _lhs, const T& _rhs) const	{
		return (_lhs->GetInstance() < _rhs->GetInstance());
	}
};


template<typename T, class N = IGraphNode<T>*>
struct graph_node_equal : public unary_function<N, bool> {
public:
	graph_node_equal(const T &value) : arg(value) {}

	bool operator() (N const _val) const {
		return _val->GetInstance() == (this)->arg;
	}
private:
	T arg;
};

template<typename T, class L = IGraphLink<T>*>
struct graph_link_equal : public unary_function<L, bool> {
public:
	graph_link_equal(const L &value) : arg(value) {}

	bool operator() (L const _val) const {
		return ((_val->GetOwner() == arg->GetOwner()) && (_val->GetTarget() == arg->GetTarget())) ||
			((_val->GetOwner() == arg->GetTarget()) && (_val->GetTarget() == arg->GetOwner()));
	}
private:
	L arg;
};


struct graph_free {
public:
	template<typename T>
	void operator() (const T* ptr) const {
		delete ptr;
	}
};

#endif

// Модуль graphIFactory
#ifndef GRAPH_IFACTORY_H
#define GRAPH_IFACTORY_H

template<typename T, class N = IGraphNode<T>*, class L = IGraphLink<T>*>
class IGraphFactory {	
public:
	virtual ~IGraphFactory() {};

	virtual N CreateGraphNode(const T value) { return 0; }
	virtual L CreateGraphLink() { return 0; }
	virtual void link(N _nodeStInst, N _nodeEdInst, double _weight) { }
};

#endif

// Модуль graphFactory
#ifndef GRAPH_FACTORY_H
#define GRAPH_FACTORY_H

template<typename T, class N = IGraphNode<T>*, class L = IGraphLink<T>*>
class GraphFactory : public IGraphFactory<T, N, L> {	
public:
	virtual N CreateGraphNode(const T value) { return (N)(new GraphNode<T>(value)); }
	virtual L CreateGraphLink() { return (L)(new GraphLink<T>()); }

	virtual void link(N _nodeStInst, N _nodeEdInst, double _weight) { 
		assert(_nodeStInst);
		assert(_nodeEdInst);

		L _link = this->CreateGraphLink();
		_link->SetOwner(_nodeStInst);
		_link->SetTarget(_nodeEdInst);
		_link->SetWeight(_weight);

		vector<L>* _plinkSt = _nodeStInst->GetLinks();

		typename vector<L>::iterator _itrSt = find_if(_plinkSt->begin(), _plinkSt->end(), graph_link_equal<T, L>(_link));
		if (_itrSt == _plinkSt->end()) {
			_plinkSt->push_back((IGraphLink<T>*)_link);
		} else {
			delete _link;
			return;
		}

		L _link_r = this->CreateGraphLink();
		_link_r->SetOwner(_nodeEdInst);
		_link_r->SetTarget(_nodeStInst);
		_link_r->SetWeight(_weight);

		vector<L>* _plinkEd = _nodeEdInst->GetLinks();
		_plinkEd->push_back((L)_link_r);
	}
};

#endif

// Модуль graph
#ifndef GRAPH_H
#define GRAPH_H

// Граф, тип содержимого узла, тип узла, тип связи
template<typename T, class N = IGraphNode<T>*, class L = IGraphLink<T>*>
class Graph : public set<N, graph_node_less<N> > {
public:
	typedef N node_value;
	typedef L link_value;
	typedef pair<N, bool> pair_value;
	typedef set<N, graph_node_less<N> > graph_set;
public:
	Graph(IGraphFactory<T, N, L>* factory = new GraphFactory<T>()) {
		m_factory = factory;
	}
	~Graph() { 
		for_each(graph_set::begin(), graph_set::end(), graph_free()); 
		delete m_factory; 
	}
public:

	// Вставка содержимого в граф
	virtual pair_value insert(T _instVal) {
		pair<typename set<N, graph_node_less<N> >::iterator,bool> ret;

		N _node = m_factory->CreateGraphNode(_instVal);

		ret = graph_set::insert(_node);

		if (!ret.second) { delete _node; _node = 0; }
		return pair<N, bool>(*(ret.first), ret.second);
	}

	// Поиск узла по содержимому
	virtual node_value find(T _instVal) {
		//typename set<N, graph_node_less<N> >::iterator p = 
		//	std::find_if(graph_set::begin(), graph_set::end(), graph_node_equal<T, N>(_instVal));

		N _node = m_factory->CreateGraphNode(_instVal);
		typename set<N, graph_node_less<N> >::iterator p = graph_set::find(_node);
		delete _node;

		if (p != graph_set::end()) return *p;
		else return 0;
	}

	// Связывание узлов. Если узел не существует, то ошибка. Если узлы уже связаны, то пропуск
	virtual void link(node_value _nodeStInst, node_value _nodeEdInst, double _weight) {
		m_factory->link(_nodeStInst, _nodeEdInst, _weight);
	}
protected:
	IGraphFactory<T, N, L>* m_factory;
};

#endif

// Модуль graphTreeNode
#ifndef GRAPHTREE_NODE_H
#define GRAPHTREE_NODE_H

template<typename T>
class IGraphTreeNode : public IGraphNode<T>  {
public:
	virtual ~IGraphTreeNode() {};

	virtual IGraphTreeNode<T>* GetParent() = 0;
	virtual void SetParent(IGraphTreeNode<T>* value) = 0;

	virtual IGraphLink<T>* GetParentLink() = 0;
	virtual void SetParentLink(IGraphLink<T>* value) = 0;
};

// Реализация узла графа без циклов (дерево)
template<typename T>
class GraphTreeNode : public IGraphTreeNode<T> {
public:
	GraphTreeNode(T instance) : m_Instance(instance), m_Parent(0), m_ParentLink(0) { m_Instance = instance; m_Vec = 0;  m_isVisit = false; }
	~GraphTreeNode() { 
		for_each(m_links.begin(), m_links.end(), inode_free());
	}

public:
	// Данные об узле
	virtual T GetInstance() { return m_Instance; }
	virtual void SetInstance(T value) { m_Instance = value; }

	// Длинна пути до данного узла
	virtual double GetVec() { return m_Vec; }
	virtual void SetVec(double value) { m_Vec = value; }

	virtual bool IsVisit() { return m_isVisit; }
	virtual void SetIsVisit(bool value) { m_isVisit = value; }

	// Ребра графа, выходщие из данного узла
	virtual vector<IGraphLink<T>*>* GetLinks() { return (std::vector<IGraphLink<T>*>*)&m_links; }

protected:
	T m_Instance;
	double m_Vec;
	bool m_isVisit;
	vector<GraphLink<T>*> m_links;

public:
	virtual IGraphTreeNode<T>* GetParent() { return m_Parent; }
	virtual void SetParent(IGraphTreeNode<T>* value) { m_Parent = (GraphTreeNode<T>*)value; }

	virtual IGraphLink<T>* GetParentLink() { return m_ParentLink; }
	virtual void SetParentLink(IGraphLink<T>* value) { m_ParentLink = (GraphLink<T>*)value; }

protected:
	GraphTreeNode<T>* m_Parent;
	GraphLink<T>* m_ParentLink;
};

#endif

// Модуль graphTreeFactory
#ifndef GRAPHTREE_FACTORY_H
#define GRAPHTREE_FACTORY_H

template<typename T, class N = IGraphTreeNode<T>*, class L = IGraphLink<T>*>
class GraphTreeFactory : public IGraphFactory<T, N, L> {	
public:
	virtual N CreateGraphNode(const T value) { return new GraphTreeNode<T>(value); }
	virtual L CreateGraphLink() { return new GraphLink<T>(); }

	virtual void link(N _nodeStInst, N _nodeEdInst, double _weight) { 
		assert(_nodeStInst);
		assert(_nodeEdInst);
		
		L _link = CreateGraphLink();
		_link->SetOwner(_nodeStInst);
		_link->SetTarget(_nodeEdInst);
		_link->SetWeight(_weight);

		vector<L>* _plinkSt = _nodeStInst->GetLinks();

		typename vector<L>::iterator _itrSt = find_if(_plinkSt->begin(), _plinkSt->end(), graph_link_equal<T, L>(_link));
		if (_itrSt == _plinkSt->end()) {
			_plinkSt->push_back((IGraphLink<T>*)_link);
		} else {
			delete _link;
			return;
		}

		L _link_r = CreateGraphLink();
		_link_r->SetOwner(_nodeEdInst);
		_link_r->SetTarget(_nodeStInst);
		_link_r->SetWeight(_weight);

		vector<L>* _plinkEd = _nodeEdInst->GetLinks();
		_plinkEd->push_back((IGraphLink<T>*)_link_r);
	}
};

#endif

// Модуль graphTree
#ifndef GRAPHTREE_H
#define GRAPHTREE_H

template<typename T>
class GraphTree : public Graph<T, IGraphTreeNode<T>*> {
public:
	typedef Graph<T, IGraphTreeNode<T>*> Base;
    typedef typename Graph<T, IGraphTreeNode<T>*>::node_value node_value;
	typedef typename Graph<T, IGraphTreeNode<T>*>::link_value link_value;
public:
	GraphTree(IGraphFactory<T, IGraphTreeNode<T>*>* factory = new GraphTreeFactory<T>()) : Graph<T, IGraphTreeNode<T>*>(factory) { m_Root = 0; }
	~GraphTree() {}

public:
	// Связывание узлов. Построение дерева. Если узел не существует, то ошибка. Если узлы уже связаны, то пропуск
	virtual void link(node_value _nodeStInst, node_value _nodeEdInst, double _weight) {
		Base::m_factory->link(_nodeStInst, _nodeEdInst, _weight);

		if (!m_Root) { 
			m_Root = _nodeStInst; 
			_nodeStInst->SetParent(m_Root); 
			_nodeStInst->SetParentLink(0);
		}

		if (!_nodeStInst->GetParent()) {
			// у первой вершины нет ссылки на родителя(направление к корню дерева)
			if (!_nodeEdInst->GetParent()) {
				// Пустой подграф несвязанный с корнем дерева
				return;
			}
			else {
				_nodeStInst->SetParent(_nodeEdInst);
				_nodeStInst->SetParentLink(_nodeStInst->GetLinks()->back());
				sublink(_nodeStInst);
			}
		}
		else {
			// у второй вершины нет ссылки на родителя(направление к корню дерева)
			if (!_nodeEdInst->GetParent()) {
				_nodeEdInst->SetParent(_nodeStInst);
				_nodeEdInst->SetParentLink(_nodeEdInst->GetLinks()->back());
				sublink(_nodeEdInst);
			}
			else {
				//throw "Ошибка ER0001: В графе обнаружен цикл. Граф не является деревом.";
				return;
			}
		}


	}

	node_value GetRoot() { return m_Root; }

protected:
	void sublink(node_value _node) {
		vector<link_value>* plinks = _node->GetLinks();

		node_value subnode = 0;
		for (typename vector<link_value>::iterator i = plinks->begin(); i != plinks->end(); i++) {
			subnode = (node_value)(*i)->GetTarget();

			if ((subnode != _node->GetParent()) && (!subnode->GetParent())) {
				subnode->SetParent(_node);
				subnode->SetParentLink(*i);
				sublink(subnode);
			}
		}
	}

protected:
	node_value m_Root;
};

#endif

// Модуль graphTraversal
#ifndef GRAPH_TRAVERSAL_H
#define GRAPH_TRAVERSAL_H

template<typename T>
double traversal(GraphTree<T> &tree, IGraphTreeNode<T>* _nodeSt, IGraphTreeNode<T>* _nodeEd) {
	double st_path = 0;
	double ed_path = 0;
	double res = 0;
	
	if (!_nodeSt) return res;
	if (!_nodeEd) return res;
	if (_nodeSt == _nodeEd) return 0;

	//for (typename GraphTree<T>::iterator itr = tree.begin(); itr != tree.end(); itr++) {
	//	(*itr)->SetVec(0);
	//	(*itr)->SetIsVisit(false);
	//}
	list<typename GraphTree<T>::node_value> path;

	typename GraphTree<T>::node_value _root = tree.GetRoot();

    path.push_back(_nodeSt);
	_nodeSt->SetIsVisit(true);
	typename GraphTree<T>::node_value _parentSt = _nodeSt->GetParent();
	
	path.push_back(_nodeEd);
	_nodeEd->SetIsVisit(true);
	typename GraphTree<T>::node_value _parentEd = _nodeEd->GetParent();

	typename GraphTree<T>::link_value _parentStLink = _nodeSt->GetParentLink();
	typename GraphTree<T>::link_value _parentEdLink = _nodeEd->GetParentLink();

	while(	(_parentStLink) ||
			(_parentEdLink) )  {

		if (!(_parentSt || _parentEd)) break;
		
		if (_parentStLink)	{
			st_path += _parentStLink->GetWeight(); 

			if (!_parentSt->IsVisit()) {

                path.push_back(_parentSt);
				_parentSt->SetVec(st_path);
				_parentSt->SetIsVisit(true);
				_parentStLink = _parentSt->GetParentLink();
				_parentSt = _parentSt->GetParent();
				res = st_path;
			}
			else {
				res = _parentSt->GetVec() + st_path;
				break;
			}
		}

		if (_parentEdLink) {
			ed_path += _parentEdLink->GetWeight();
		
			if (!_parentEd->IsVisit()) {
			
			    path.push_back(_parentEd);
				_parentEd->SetVec(ed_path);
				_parentEd->SetIsVisit(true);
				_parentEdLink = _parentEd->GetParentLink();
				_parentEd = _parentEd->GetParent();
				res = ed_path;
			}
			else {
				res = _parentEd->GetVec() + ed_path;
				break;
			}
		}
	}
	
	for (typename list<typename GraphTree<T>::node_value>::iterator itr = path.begin(); itr != path.end(); itr++) {
		(*itr)->SetVec(0);
		(*itr)->SetIsVisit(false);
	}
	
	return res;
}

#endif

int main(void)
{
	GraphTree<int> graph;

	int N = 0; // Кол-во вершин в дереве
	cin >> N;

	if (!N) { 
		cout << 0 << endl;
		return 0;
	}

	for (int i = 0; i < N - 1; i++) {
		int nodeSt = -1;
		int nodeEd = -1;
		int weight = -1;

		cin >> nodeSt >> nodeEd >> weight;
		
		if ((nodeSt < 0) ||
			(nodeEd < 0) ||
			(weight < 0)) {
				cout << 0 << endl;
				return 0;
		}

		// обработка вершин
		graph.link(graph.insert(nodeSt).first, graph.insert(nodeEd).first, weight);
	}

	int M = 0; // Кол пар вершин, для которых нужно найти длину кратчайшего пути
	cin >> M;

	if (!M) { 
		cout << 0 << endl;
		return 0;
	}
	
	vector<pair<int, int> > t_paths;

	for (int i = 0; i < M; i++) {
		int nodeSt = -1;
		int nodeEd = -1;

		cin >> nodeSt >> nodeEd;

		if ((nodeSt < 0) ||
			(nodeEd < 0)) {
				cout << 0 << endl;
				return 0;
		}

		t_paths.push_back(pair<int, int>(nodeSt, nodeEd));
	}

	for (vector<pair<int, int> >::iterator i = t_paths.begin(); i != t_paths.end(); i++) {

		GraphTree<int>::node_value pNodeSt = graph.find((*i).first);
		GraphTree<int>::node_value pNodeEd = graph.find((*i).second);

		// рассчет длины пути
		cout << traversal(graph, pNodeSt, pNodeEd) << endl;
	}

//  int u = 0;
//	cin >> u;
	return 0;
}
