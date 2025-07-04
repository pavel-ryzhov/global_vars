#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

typedef unsigned int uint;

class Tree
{
    public:
        Tree( const uint top = 0, const uint length = 0 );
        ~Tree();

        void newBranch( const uint from, const uint to, const uint length );
        size_t length( const uint from, const uint to );
    private:
        void newBranch( const uint to, const uint length );
        Tree *findTop( const uint top );
        Tree *LCA( const uint top1, const uint top2 );
        size_t depth( const uint top );

        uint m_top;
        uint m_length;
        list< Tree * > m_branches;

        Tree *m_parent;
};

Tree::Tree( const uint top, const uint length )
    : m_top( top )
    , m_length( length )
{
}

Tree::~Tree()
{
    for( list< Tree * >::iterator i = m_branches.begin(); i != m_branches.end(); i++ )
        delete ( *i );
}

void
Tree::newBranch( const uint from, const uint to, const uint length )
{
    Tree *branch = 0;
    if( ( branch = findTop( from ) ) )
        branch->newBranch( to, length );
    else if( ( branch = findTop( to ) ) )
        branch->newBranch( from, length );
    else
    {
        branch = new Tree( from, 0 );
        branch->m_parent = this;
        branch->newBranch( to, length );
        m_branches.push_back( branch );
    }
}

void
Tree::newBranch( const uint to, const uint length )
{
    Tree *branch = new Tree( to, length );
    branch->m_parent = this;
    m_branches.push_back( branch );
}

Tree *
Tree::findTop( const uint top )
{
    if( top == m_top )
        return this;

    Tree *branch = 0;
    for( list< Tree * >::iterator i = m_branches.begin(); i != m_branches.end(); i++ )
        if( ( branch = ( *i )->findTop( top ) ) )
            return branch;

    return 0;
}

Tree *
Tree::LCA( const uint top1, const uint top2 )
{
    for( list< Tree * >::iterator i = m_branches.begin(); i != m_branches.end(); i++ )
        if( ( *i )->findTop( top1 ) && ( *i )->findTop( top2 ) )
            return ( *i )->LCA( top1, top2 );

    return this;
}

size_t
Tree::length( const uint from, const uint to )
{
    Tree *lca = LCA( from, to );
    return lca->depth( from ) + lca->depth( to );
}

size_t
Tree::depth( const uint top )
{
    Tree *branch = findTop( top );

    if( !branch )
        return 0;

    size_t depth = 0;
    while( branch->m_top != m_top )
    {
        depth += branch->m_length;
        branch = branch->m_parent;
    }

    return depth;
}

int
main()
{
    Tree *tree = new Tree();

    uint n = 0;
    uint f = 0, t = 0, l = 0;

    cin >> n;
    while( --n )
    {
        cin >> f >> t >> l;
        tree->newBranch( f, t, l );
    }

    cin >> n;
    while( n-- )
    {
        cin >> f >> t;
        cout << tree->length( f, t ) << endl;
    }

    delete tree;
    return 0;
}
