#include <cstdlib>
#include <vector>
#include <deque>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
    unsigned int i, j, p, q, k, temp, c;

    unsigned int num_of_nodes;
    cin >> num_of_nodes;

    vector< vector<bool> > connected;
    connected.resize(num_of_nodes);
    vector< vector<unsigned int> > dist;
    dist.resize(num_of_nodes);
    vector<int> color;
    color.resize(num_of_nodes);
    for( i = 0; i < num_of_nodes; i++) {
        dist.at(i).resize(num_of_nodes);
        connected.at(i).resize(num_of_nodes);
        color.at(i)=-1;
            for( j = 0; j < num_of_nodes; j++) {
                connected.at(i).at(j)=false;
                dist.at(i).at(j)=0;
            }
        connected.at(i).at(i)=true;
    }

    vector< vector<unsigned int> > edges;
    edges.resize(num_of_nodes);
    for( k = 0; k < num_of_nodes-1; k++) {
        cin >> i >> j >> temp;
        i--;
        j--;
        dist.at(i).at(j)=temp;
        dist.at(j).at(i)=temp;
        connected.at(i).at(j)=true;
        connected.at(j).at(i)=true;
        edges.at(i).push_back(j);
        edges.at(j).push_back(i);
    }

    unsigned int num_of_pairs;
    cin >> num_of_pairs;
    vector<unsigned int> from, to;
    from.resize(num_of_pairs);
    to.resize(num_of_pairs);
    for( i = 0; i < num_of_pairs; i++) {
        cin >> from[i] >> to[i];
        from.at(i)--;
        to.at(i)--;
    }

    vector<unsigned int> start_node;
    vector< deque<unsigned int> > current;
    vector< vector<unsigned int> > visited;
    vector<unsigned int> ignited_node, current_node;
    vector<unsigned int> node, spring_num;
    node.resize(2);
    spring_num.resize(2);
    for( k = 0; k < num_of_pairs; k++) {        
        node.at(0)=from.at(k);
        node.at(1)=to.at(k);
        if( !connected.at(node.at(0)).at(node.at(1)) ) {
            for( i = 0; i < 2; i++ ) {
                if( color.at(node.at(i))==-1 ) {
                    start_node.push_back(node.at(i));
                    spring_num.at(i)=start_node.size()-1;
                    color.at(node.at(i))=spring_num.at(i);
                    current_node.push_back(node.at(i));
                    ignited_node.push_back(node.at(i));
                    visited.resize(start_node.size());
                    current.resize(start_node.size());
                    visited.at(spring_num.at(i)).push_back(node.at(i));
                    current.at(spring_num.at(i)).push_back(node.at(i));
                }
                else
                    spring_num.at(i)=color.at(node.at(i));
            }
            while( color.at(node.at(0))!=color.at(node.at(1)) ) {
                for( i = 0; i < 2; i++ ) {
                    c=spring_num.at(i);
                    if( !current.at(c).empty() ) {
                        current_node.at(c)=current.at(c).front();
                        current.at(c).pop_front();
                        for ( vector<unsigned int>::iterator it=edges.at(current_node.at(c)).begin(); it!=edges.at(current_node.at(c)).end(); ++it ) {
                            ignited_node.at(c)=*it;
                            if( color.at(*it) == -1 ) {
                                for( vector<unsigned int>::iterator jt=visited.at(c).begin(); jt!=visited.at(c).end(); ++jt ) {
                                    temp=dist.at(*jt).at(current_node.at(c))+dist.at(current_node.at(c)).at(*it);
                                    dist.at(*jt).at(*it)=temp;
                                    dist.at(*it).at(*jt)=temp;
                                    connected.at(*jt).at(*it)=true;
                                    connected.at(*it).at(*jt)=true;
                                }
                                color.at(*it)=c;
                                current.at(c).push_back(*it);
                                visited.at(c).push_back(*it);
                            }
                            else if( color.at(*it) != c ) {
                                //CONNECTION!
                                j=color.at(*it);
                                p=current_node.at(c);
                                q=*it;
                                for( vector<unsigned int>::iterator lt=visited.at(c).begin(); lt!=visited.at(c).end(); ++lt )
                                    for( vector<unsigned int>::iterator jt=visited.at(j).begin(); jt!=visited.at(j).end(); ++jt ) {
                                        temp=dist.at(*jt).at(q)+dist.at(q).at(p)+dist.at(p).at(*lt);
                                        dist.at(*jt).at(*lt)=temp;
                                        dist.at(*lt).at(*jt)=temp;
                                        connected.at(*jt).at(*lt)=true;
                                        connected.at(*lt).at(*jt)=true;
                                    }
                                for( vector<unsigned int>::iterator jt=visited.at(j).begin(); jt!=visited.at(j).end(); ++jt ) {
                                    visited.at(c).push_back(*jt);
                                    color.at(*jt)=c;
                                }
                                for( vector<unsigned int>::iterator jt=visited.at(j).begin(); jt!=visited.at(j).end(); ++jt )
                                    current.at(c).push_back(*jt);
                                current.at(j).clear();
                                visited.at(j).clear();
                            }
                        }
                    }
                }
            }
        }
    }
    for( i = 0; i < num_of_pairs; i++)
            cout << dist.at(from.at(i)).at(to.at(i)) << endl;
    return 0;
}