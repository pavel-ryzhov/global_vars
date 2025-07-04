#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
    char filenamein[]="in.txt", filenameout[]="out.txt";
    FILE *foutput;
    int no_path = 20000000;              //вес при отсутствии ребра между 2 вершинами
    int a,b,w,ind=0,nodes, ways;                   //a и b - смежные вершины графа, w - вес между ними
    char inbuff[80], outbuff[10];
    string str1;
    cin >> nodes;

    vector <int> Line(nodes, no_path);      
    vector < vector < int > > g(nodes, Line); //Двумерный массив, строка и столбец - номера вершины графа, значение i,j - вес между ребрами

    for(int i=0;i<nodes;i++)
    {
       cin >> a >> b;
       cin >> g[ a-1 ][ b-1 ];
    } 
 
    for(int i=0; i<nodes; i++)    g[i][i]=0;
    for(int i=1;i<nodes+1;i++)     //Данный алгоритм медленнее алгоритма Дейкстры, однако позволяет строить пути из всех вершин во все вершины. При использовании алгоритма дейкстры
       for(int j=0;j<nodes;j++)    //при смене вершины, из которой начинается путь, пришлось бы перестраивать граф и пересчитывать все заново.
          for(int k=0;k<nodes;k++)
              if ( g[j][k] > (g[j][i - 1] + g[i - 1][k]) )  g[j][k] = g[j][i - 1] + g[i - 1][k];
       
    for(int i=0; i<nodes; i++)
    for(int j=0; j<nodes; j++)
    {
       cout << g[i][j] << endl;        
    }       
  /*  cin >> ways;
    char endstr='\0', newline='\n';
    foutput=fopen(filenameout,"w");
    for(int i=0; i<nodes; i++)
    for(int j=0; j<nodes; j++)
    {
        //cin >> a >> b;
        //cout << "Way: " << a << " - " << b << ": " << g[a - 1][b - 1] << endl;
        //sprintf(outbuff,"%i",g[i - 1][j - 1]);
        
        sprintf(outbuff,"%i",g[i][j]);
        fputs(outbuff, foutput);
       // fputs(&endstr, foutput);  //fputs не пишет \0\n в конце строки, пришлось сделать вручную
       // fputs(&newline, foutput);
    }
    
    fclose(foutput);*/
    return 0;
}
