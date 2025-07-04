/* 
 * File:   tree_main.cpp
 * Author: NesoK
 *
 * Created on 22 Сентябрь 2011 г., 19:23
 */

typedef struct _node node;

typedef struct _branch{
    unsigned short int length;
    unsigned short int number;
    node *node1;
    node *node2;
} branch;

typedef struct _node{
    unsigned short int number;
    unsigned short int counter;
    branch **branches;
} node;

#include <cstdlib>
#include <string.h>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

class Tree
{
public:
    Tree( int numb = 1 ): NumbOfNodes( numb ), Nodes( new node[ numb ] ),
            Branches( new branch[ numb-1 ] ), countOfBranch( 0 )
    {
        memset( Nodes, 0x00, NumbOfNodes * sizeof( node ) );
        memset( Branches, 0x00, (NumbOfNodes - 1) * sizeof( branch ) );
        
        for( int i = 0; i < NumbOfNodes; i++ )
        {
            Nodes[i].number = i + 1;
            Nodes[i].branches = new branch *[ numb-1 ];
            memset( Nodes[i].branches, 0x00, (NumbOfNodes - 1) * sizeof( branch * ) );
        }
    }
    
    bool addBranches( const int &Node1, const int &Node2, const int& length )
    {
        
        if ( countOfBranch == NumbOfNodes - 1 )
            return false;
        
        Branches[countOfBranch].node1 = getNode( Node1 );
        Branches[countOfBranch].node2 = getNode( Node2 );
        Branches[countOfBranch].length = length;
        Branches[countOfBranch].number = countOfBranch;
        getNode( Node1 ) -> branches[ getNode( Node1 )-> counter ] = &Branches[countOfBranch];
        (getNode( Node1 )-> counter) ++;
        getNode( Node2 ) -> branches[ getNode( Node2 )-> counter ] = &Branches[countOfBranch];
        (getNode( Node2 )-> counter) ++;
        countOfBranch++;
        return true;       
    }
    
    int getWay( const int &sourse, const int &dest )
    {
        if( sourse == dest )
            return 0;
        
        node *tempNode = new node[ NumbOfNodes ];
        memcpy( tempNode, Nodes, NumbOfNodes * sizeof( node ) );
        int result = 0;
        
        for( int i = 0; i < countOfBranch; i++)
             result += getBranch( i )->length;

        for( int j = 0; j < countOfBranch; j++)
        {
            for( int i = 0; i < countOfBranch; i++)
            {
                if( getBranch( i )->node1->number != sourse &&  getBranch( i )->node1->number != dest ) 
                {
                    if( getBranch( i )->node1->counter == 1 )
                    {
                        result -= getBranch( i )->length;
                       (getBranch( i )->node1->counter)--;
                       (getBranch( i )->node2->counter)--;
                       continue;
                    }
                }

                if( getBranch( i )->node2->number != sourse &&  getBranch( i )->node2->number != dest ) 
                {
                    if( getBranch( i )->node2->counter == 1 )
                    {
                            result -= getBranch( i )->length;
                            (getBranch( i )->node1->counter)--;
                            (getBranch( i )->node2->counter)--;
                            continue;
                    }
                }

            }
        }
        memcpy( Nodes, tempNode, NumbOfNodes * sizeof( node ) );
        delete[] tempNode;
        return result;
    }
    
    node *getNode( const int &number )
    {
        for( int i = 0; i < NumbOfNodes; i++)
            if ( Nodes[i].number == number ) 
                return &Nodes[i];
        
        return NULL;
    }
    
    branch *getBranch( const int &number )
    {
        for( int i = 0; i < NumbOfNodes-1; i++)
            if ( Branches[i].number == number ) 
                return &Branches[i];
        
        return NULL;
    }
    
    ~Tree()
    {
        for( int i = 0; i < NumbOfNodes; i++ )
                delete[] Nodes[i].branches;
        
        delete[] Nodes;
        delete[] Branches;
    }
private:
    
    node *Nodes;
    branch *Branches;
    unsigned short int NumbOfNodes;
    unsigned short int countOfBranch;
};


int main() 
{
    int numbOfNodes = 0;
    int node1 = 0;
    int node2 = 0;
    int len = 0;    
    int findWays = 0;
    int *ways;
    cin >> numbOfNodes;
    Tree testTree(numbOfNodes);
    for( int i = 0; i < numbOfNodes - 1; i++ )
    {
        cin >> node1;
        cin >> node2;
        cin >> len;
        testTree.addBranches(node1,node2,len);
    }
    
    cin >> findWays;
    ways = new int[findWays];
    memset( ways, 0, findWays * sizeof( int ) );
    
    for( int i = 0; i < findWays; i++ )
    {
        cin >> node1;
        cin >> node2;
        ways[i] = testTree.getWay(node1, node2);
    }
    
    for( int i = 0; i < findWays; i++ )
    {
        cout << ways[i] << endl;
    }
    
    delete[] ways;
    return 0;
}