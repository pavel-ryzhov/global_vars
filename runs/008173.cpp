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
            Branches( new branch[ numb-1 ] ), countOfBranch( 0 ), summ( 0 )
    {
        memset( Nodes, 0x00, NumbOfNodes * sizeof( node ) );
        memset( Branches, 0x00, (NumbOfNodes - 1) * sizeof( branch ) );        
    }
    
    void addBranches( const int &Node1, const int &Node2, const int& length )
    {    
        if ( !Nodes[Node1-1].number )
        {
            Nodes[Node1-1].number = Node1;
            Nodes[Node1-1].branches = new branch *[ NumbOfNodes-1 ];
//            memset( Nodes[Node1-1].branches, 0x00, (NumbOfNodes - 1) * sizeof( branch * ) );
        }
        if ( !Nodes[Node2-1].number )
        {
            Nodes[Node2-1].number = Node2;
            Nodes[Node2-1].branches = new branch *[ NumbOfNodes-1 ];
//            memset( Nodes[Node2-1].branches, 0x00, (NumbOfNodes - 1) * sizeof( branch * ) );
        }
        
        Branches[countOfBranch].node1 = &Nodes[Node1-1];
        Branches[countOfBranch].node2 = &Nodes[Node2-1];
        Branches[countOfBranch].length = length;
        Branches[countOfBranch].number = countOfBranch;
        Nodes[Node1-1].branches[ Nodes[Node1-1].counter ] = &Branches[countOfBranch];
        Nodes[Node1-1].counter ++;
        Nodes[Node2-1].branches[ Nodes[Node2-1].counter ] = &Branches[countOfBranch];
        Nodes[Node2-1].counter ++;
        countOfBranch++;  
    }
    
    void parseSumm()
    {
        for( int i = 0; i < countOfBranch; i++)
             summ += Branches[i].length;
    }
    
    int getWay( const int &sourse, const int &dest )
    {
        node *tempNode = new node[ NumbOfNodes ];
        memcpy( tempNode, Nodes, NumbOfNodes * sizeof( node ) );
        
        int result = summ;
        
        bool flag1 = true;
        for( int j = 0; j < NumbOfNodes; j++)
        {
            for( int i = 0; i < countOfBranch; i++)
            {                
                if( Branches[i].node1->number != sourse &&  Branches[i].node1->number != dest ) 
                {
                    if( Branches[i].node1->counter == 1  && Branches[i].node2->counter != 0)
                    {
                        result -= Branches[i].length;        
                       Branches[i].node1->counter--;
                       Branches[i].node2->counter--;
                       flag1 = false;
                       continue;
                    }
                }

                if( Branches[i].node2->number != sourse &&  Branches[i].node2->number != dest ) 
                {
                    if( Branches[i].node2->counter == 1 && Branches[i].node1->counter != 0)
                    {
                            result -= Branches[i].length;
                            Branches[i].node1->counter--;
                            Branches[i].node2->counter--;
                            flag1 = false;
                            continue;
                    }
                }
            }
            if( flag1 )
                break;
            else
                flag1 = true;
        }
        memcpy( Nodes, tempNode, NumbOfNodes * sizeof( node ) );
        delete[] tempNode;
        return result;
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
    int summ;
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
    int *nodes1;
    int *nodes2;
    cin >> numbOfNodes;
    Tree testTree(numbOfNodes);
    for( int i = 0; i < numbOfNodes - 1; i++ )
    {
//        cin >> node1;
//        cin >> node2;
//        cin >> len;
        scanf("%d", &node1);
        scanf("%d", &node2);
        scanf("%d", &len);
        testTree.addBranches(node1,node2,len);
    }
    
 //   cin >> findWays;
    scanf("%d", &findWays);
    ways = new int[findWays];
    nodes1 = new int[findWays];
    nodes2 = new int[findWays];
    
//    memset( ways, 0, findWays * sizeof( int ) );
//    memset( nodes1, 0, findWays * sizeof( int ) );
//    memset( nodes2, 0, findWays * sizeof( int ) );
    
    testTree.parseSumm();
    for( int i = 0; i < findWays; i++ )
    {
 //       cin >> node1;
//        cin >> node2;
        scanf("%d", &node1);
        scanf("%d", &node2);
        
        if (node1 == node2)
        {
            ways[i] = 0;
            continue;
        }
        
        for( int j = 0; j < i; j++)
        {
            
            if( !nodes2[j] && !nodes1[j] && nodes1[j] == node2 && node1 == nodes2[j] )
            {
                ways[i] = ways[j];
                break;
            }
        }
        
        nodes1[i] = node1;
        nodes2[i] = node2;
        if ( ways[i] )
            continue;
        else
            ways[i] = testTree.getWay(node1, node2);
    }
    
    for( int i = 0; i < findWays; i++ )
    {
        printf("%d\n",ways[i]);
    }
    
    delete[] nodes1;
    delete[] nodes2;
    delete[] ways;
    return 0;
}