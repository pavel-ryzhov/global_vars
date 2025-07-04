#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int no_path = 20000000;              //вес при отсутствии ребра между 2 вершинами
    int a,b,nodes,ways;                   //a и b - смежные вершины графа, w - вес между ними
    cin >> nodes;
    
    vector <int> Line(nodes, no_path);      
    vector < vector < int > > g(nodes, Line); //Двумерный массив, строка и столбец - номера вершины графа, значение i,j - вес между ребрами

    for(int i=0;i<nodes-1;i++)
    {
       cin >> a >> b;
       cin >> g[ a-1 ][ b-1 ];
       g[ b-1 ][ a-1 ] = g[ a-1 ][ b-1 ];
       g[i][i]=0;
    } 

    g[ nodes-1 ][ nodes-1 ] = 0;  
    
    for(int i=1; i<nodes+1; i++)     //Данный алгоритм медленнее алгоритма Дейкстры, однако позволяет строить пути из всех вершин во все вершины. При использовании алгоритма дейкстры
       for(int j=0; j<nodes; j++)    //при смене вершины, из которой начинается путь, пришлось бы перестраивать граф и пересчитывать все заново.
          for(int k=0; k<nodes; k++)
              if ( g[j][k] > (g[j][i - 1] + g[i - 1][k]) )  g[j][k] = g[j][i - 1] + g[i - 1][k];
    
    cin >> ways;
    for(int i=0; i<ways; i++)
    {
       cin >> a >> b;
       cout << g[ a-1 ][ b-1 ] << endl;
    } 
    return 0;
}
