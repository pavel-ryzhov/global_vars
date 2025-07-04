#include <iostream>
#include <map>

using namespace std;

typedef unsigned int uint;
typedef map< uint, map< uint, uint > > vertixMap;
typedef std::map< uint, std::map< uint, bool > > visibilityMap;

class Tree
{
    public:
        Tree();
        ~Tree();

        void newEdge( const uint vert1, const uint vert2, const uint length );
        void prepareTree( const uint vert = 1 );

        size_t length( const uint vert1, const uint vert2 ) const;
    private:
        uint LCA( const uint curVert, const uint vert1, const uint vert2 ) const;
        bool isConnected( const uint vert1, const uint vert2 ) const;
        size_t depth( const uint curVert, const uint vert ) const;

        vertixMap *m_vertices;
        visibilityMap *m_verticesVisibilityCache;
};

Tree::Tree()
    : m_vertices( new vertixMap )
    , m_verticesVisibilityCache( new visibilityMap )
{
}

Tree::~Tree()
{
    delete m_vertices;
    delete m_verticesVisibilityCache;
}

void
Tree::newEdge( const uint vert1, const uint vert2, const uint length )
{
    ( *m_vertices )[ vert1 ][ vert2 ] = length;
    ( *m_vertices )[ vert2 ][ vert1 ] = length;
}

size_t
Tree::length( const uint from, const uint to ) const
{
    if( from == to )
        return 0;

    uint lca = LCA( 1, from, to );
    return depth( lca, from ) + depth( lca, to );
}

uint
Tree::LCA( const uint curVert, const uint vert1, const uint vert2 ) const
{
    for( std::map< uint, uint >::iterator i = m_vertices->at( curVert ).begin();
         i != m_vertices->at( curVert ).end(); i++ )
    {
        if( isConnected( i->first, vert1 ) && isConnected( i->first, vert2 ) )
            return LCA( i->first, vert1, vert2 );
    }

    return curVert;
}

bool
Tree::isConnected( const uint vert1, const uint vert2 ) const
{
    if( vert1 == vert2 || ( *m_verticesVisibilityCache )[ vert1 ][ vert2 ] )
        return true;

    for( std::map< uint, uint >::iterator i = m_vertices->at( vert1 ).begin();
         i != m_vertices->at( vert1 ).end(); i++ )
    {
        if( isConnected( i->first, vert2 ) )
        {
            ( *m_verticesVisibilityCache )[ vert1 ][ vert2 ] = true;
            return true;
        }
    }

    ( *m_verticesVisibilityCache )[ vert1 ][ vert2 ] = false;
    return false;
}

void
Tree::prepareTree( const uint vert )
{
    if( m_vertices->count( vert ) == 0 )
        return;

    for( std::map< uint, uint >::iterator i = m_vertices->at( vert ).begin();
         i != m_vertices->at( vert ).end(); i++ )
    {
        ( *m_vertices )[ i->first ].erase( vert );
        prepareTree( i->first );
    }
}

size_t
Tree::depth( const uint curVert, const uint vert ) const
{
    if( curVert == vert )
        return 0;

    if( m_vertices->at( curVert ).size() == 1 )
        return m_vertices->at( curVert ).begin()->second + depth( m_vertices->at( curVert ).begin()->first, vert );

    for( std::map< uint, uint >::iterator i = m_vertices->at( curVert ).begin();
         i != m_vertices->at( curVert ).end(); i++ )
    {
        if( isConnected( i->first, vert ) )
            return i->second + depth( i->first, vert );
    }

    return 0;
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
        tree->newEdge( f, t, l );
    }

    tree->prepareTree();

    cin >> n;
    while( n-- )
    {
        cin >> f >> t;
        cout << tree->length( f, t ) << endl;
    }

    delete tree;
    return 0;
}