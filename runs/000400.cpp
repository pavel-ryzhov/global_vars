#include <iostream>
#include <list>
#include <fstream>

class Tree
{
public:
	Tree( size_t nodeCount ): k( nodeCount ) 
	{ 
		nodes = new Node[k];
	}

	~Tree()
	{
		delete [] nodes;
	}

	void connect( size_t idx1, size_t idx2, size_t distance )
	{
		nodes[ idx1 - 1 ].neighbours.push_back( Node::Way( nodes + idx2 - 1, distance ) );
		nodes[ idx2 - 1 ].neighbours.push_back( Node::Way( nodes + idx1 - 1, distance ) );
	}

	void preprocess()
	{
		setParent( nodes, 0, 0 );
	}

	size_t distance( size_t idx1, size_t idx2 )
	{
		size_t dis = 0;
		Node *l = nodes + idx1 - 1;
		Node *r = nodes + idx2 - 1;

		if( l->depth < r->depth )
		{
			l = nodes + idx2 - 1;
			r = nodes + idx1 - 1;
		}

		while( l->depth != r->depth )
		{
			dis += l->distanceToParent;
			l = l->parent;
		}

		while( l != r )
		{
			dis = dis + l->distanceToParent + r->distanceToParent;
			l = l->parent;
			r = r->parent;
		}

		return dis;
	}

private:

	struct Node
	{
		struct Way
		{ 
			Way( Node *a, size_t d ): aim(a), distance(d) {}
			Node * aim;
			size_t distance;
		};
		std::list< Way > neighbours;
		Node *parent;
		size_t depth;
		size_t distanceToParent;
	};

	void setParent( Node *cur, Node *par, size_t depth )
	{
		cur->parent = par;
		cur->depth = depth;
		for( std::list< Node::Way >::iterator it = cur->neighbours.begin(), 
			 end = cur->neighbours.end(); it != end; ++it )
		{
			if( it->aim != par )
				setParent( it->aim, cur, depth+1 );
			else
				cur->distanceToParent = it->distance;
		}
	}

	Node *nodes;
	size_t k;
};

int main( int argc, char *argv[] )
{
	using std::cin;

	size_t idx1, idx2, dis, count;
		
	cin >> count;
	Tree tree( count );
	while( --count )
	{
		cin >> idx1 >> idx2 >> dis;
		tree.connect( idx1, idx2, dis );
	}
	tree.preprocess();

	cin >> count;
	while( count-- )
	{
		cin >> idx1 >> idx2;
		std::cout << tree.distance( idx1, idx2 ) << std::endl;			
	}
}
