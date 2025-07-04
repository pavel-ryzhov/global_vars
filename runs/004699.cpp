/* 
 * File:   main.cpp
 * Author: nergen
 *
 * Created on 16 Март 2011 г., 14:42
 */

#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
vector<vector<int> > graph;
vector<int> Order,First,High;
vector<bool> used;
int N, QN;
void dfs(int v,int h=1) {
    used[v]=true;
    First[v]=Order.size();
    Order.push_back(v);
    High[v]=h;
    for (int i=1;i<=N;++i)
        if (!used[i] & graph[v][i]!= -1) {
            dfs(i,h+1);
            Order.push_back(v);
        }
}
int length (int F,int S) {
    int ln=0,FHieth=High[Order[F]],SHieth=High[Order[S]];
    for (int i=F;i<S;++i) {
        if (High[Order[i]]>High[Order[i+1]] & FHieth>High[Order[i+1]]){
            ln+=graph[Order[i]][Order[i+1]];
            FHieth=High[Order[i+1]];
        }
        if (High[Order[S+(F-i)-1]]<High[Order[S+(F-i)]] & High[Order[S+(F-i)-1]]<SHieth){
            ln+=graph[Order[S+(F-i)-1]][Order[S+(F-i)]];
            SHieth=High[Order[S+(F-i)-1]];
        }
        if (SHieth==FHieth){
            return ln;
        }
    }
    return ln;
}
/*
 * 
 */
int main() {
    //fstream cin("test1");
    //if (!cin) {cout << "error\n"; return 1;}
    cin >> N;
    First.reserve(N+1);
    High.reserve(N+1);
    used.reserve(N+1);
    graph.reserve(N+1);
    for (int i=1;i<N+1;++i)
        graph[i].assign(N+1,-1);
    for (int i=1,first=0,second=0; i<N; ++i) {
        cin >> first >> second;
        cin >> graph[first][second];
        graph[second][first]=graph[first][second];
    }
    dfs(1);
    cin >> QN;
    for (int i=0, first, second; i<QN; ++i) {
        cin >> first >> second;
        First[first]>First[second]?
            cout << length(First[second],First[first]) << endl
                :cout << length(First[first],First[second]) << endl;
    }
    //cin.close();
    
    return 0;
}

