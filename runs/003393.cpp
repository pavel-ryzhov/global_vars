#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>
#include <functional>

namespace Tree
{

/*

ќ программе.
—начала по входным данным строитс€ дерево, причЄм св€зи хран€тс€ только наверх. “ак же собираетс€ статистика, какой узел на каком уровне в дереве.
«атем определ€ютс€ все пары, дл€ которых нужно вычислить минимальное рассто€ние.
Ќаконец рассто€ние от узла A до узла B вычисл€етс€ следующим образом. ѕусть A в дереве находитс€ ниже B. —начала нужно пройти по дереву вверх от 
узла A до узла, такого что его уровень равен уровню B. «атем осущетсвл€етс€ по одному проходу вверх и от узла B и от найденного ранее узла, пока 
оба пути не пересекутс€. ѕри этом при каждом переходе искомый путь увеличиваетс€ на соответствующее рассто€ние.
*/

	using namespace std;

	struct Element
	{

		unsigned int _parent;
		unsigned int _length;
		unsigned int _level;

		inline void Set ( unsigned int parent, unsigned int length, unsigned int level);

		Element ( unsigned int parent, unsigned int length, unsigned int level = 0);
		Element ();
	};

	inline void Element :: Set ( unsigned int parent, unsigned int length, unsigned int level)
	{

		_parent = parent;
		_length = length;
		_level = level;
	}


	Element :: Element ( unsigned int parent, unsigned int length, unsigned int level)
	{
		Set ( parent, length, level);
	}

	Element :: Element ()
	{
		Set ( 0, 0, 0);
	}

	class TreeIndex
	{

	public:
		void Create ();

		void SetLevelMap ();

		int GetMinWay ( pair < unsigned int, unsigned int> way);

		typedef map<unsigned int, Element>::iterator iter;

		void Log ();

	protected:
		void SetLevel ( iter);

		map<unsigned int,Element> _tree;
	};

	int TreeIndex :: GetMinWay ( pair < unsigned int, unsigned int> way)
	{

		iter minIter = _tree.find (way.first);
		iter maxIter = _tree.find ( way.second);

		if ( _tree [way.first]._level < _tree [way.second]._level) 
		{

			iter mem = minIter;
			minIter = maxIter;
			maxIter = mem;
		}

		int count = 0;

		while ( minIter->second._level != maxIter->second._level)
		{
			count += minIter->second._length;
			minIter = _tree.find ( minIter->second._parent);
		}
		//теперь minIter и maxIter указывают на узлы, наход€щиес€ на одном и том же уровне
		while ( minIter != maxIter)
		{

			count += minIter->second._length;
			count += maxIter->second._length;
			minIter = _tree.find ( minIter->second._parent);
			maxIter = _tree.find ( maxIter->second._parent);
		}

		return count;
	}

	void TreeIndex :: SetLevel ( iter cur)
	{

		if ( cur == _tree.end ()) throw "TreeIndex::SetLevel ( iter) - cur == _tree.end () - wrong argument";
		iter beg = cur;
		int level = 0;

		while ( cur ->second._parent != 0)
		{
			level ++;
			cur = _tree.find (cur ->second._parent);
			if ( cur == _tree.end ()) throw "TreeIndex::SetLevel ( iter) - there is an error in the tree";
		}

		beg ->second._level = level;
	}

	void TreeIndex :: SetLevelMap ()
	{
		if ( !_tree.empty ()) //throw "can't set level map because tree is empty";
			for ( iter cur = _tree.begin (); cur != _tree.end (); cur ++)
				SetLevel ( cur);
	}

	void TreeIndex :: Create ()
	{

		unsigned int number = 0, cur = 0, next = 0, length = 0;

		cin >> number;
		if ( number == 0) throw "wrong input data";

		_tree = map<unsigned int, Element> ();

		for ( unsigned int i = 0; i < number; i ++)
		{

			cin >> cur >> next >> length;
			if ( cur == 0 || next == 0 || length == 0) throw "wrong input data";

			pair<iter, bool> curRes = _tree.insert ( pair<unsigned int, Element> ( cur, Element ()));

			_tree [next] = Element ( cur, length);
		}
	}


	void TreeIndex :: Log ()
	{

		cout << "TreeIndex :: Log ():\n";

		for ( iter i = _tree.begin (); i != _tree.end (); i ++)
			cout << "tree [" << i-> first << "] = ( " << i -> second._parent << " , " << i -> second._length << 
			" , " << i -> second._level << " )" << endl;
	}

	void SolveTask ( TreeIndex& tree)
	{

		int number = 0;
		cin >> number;
		if ( number == 0) throw "wrong input data";

		vector<pair<unsigned int, unsigned int> > way ( number);

		for ( int i = 0; i < number; i ++)
		{

			cin >> way [i].first >> way [i].second;
			cout << tree.GetMinWay ( way[i]) << endl;
		}
	}

}//namespace Tree - end

using namespace Tree;



int main ()
{

	try
	{
		TreeIndex tree;
		
		tree.Create ();
		tree.SetLevelMap ();
		SolveTask (  tree);
	//	tree.Log ();
	}
	catch ( const char* str)
	{

		cout << "exception:" << str << endl;
	}
	catch ( ...)
	{

		throw;
	}

	return 0;
}
