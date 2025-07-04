#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
    int no_path = 20000000;              //��� ��� ���������� ����� ����� 2 ���������
    int a,b,w,nodes,ways;                   //a � b - ������� ������� �����, w - ��� ����� ����
    cin >> nodes;
    
    vector <int> Line(nodes, no_path);      
    vector < vector < int > > g(nodes, Line); //��������� ������, ������ � ������� - ������ ������� �����, �������� i,j - ��� ����� �������

    for(int i=0;i<nodes-1;i++)
    {
       cin >> a >> b;
       cin >> g[ a-1 ][ b-1 ];
       g[ b-1 ][ a-1 ] = g[ a-1 ][ b-1 ];
    } 

    for(int i=0; i<nodes; i++)    g[i][i]=0;
    
    for(int i=1; i<nodes+1; i++)     //������ �������� ��������� ��������� ��������, ������ ��������� ������� ���� �� ���� ������ �� ��� �������. ��� ������������� ��������� ��������
       for(int j=0; j<nodes; j++)    //��� ����� �������, �� ������� ���������� ����, �������� �� ������������� ���� � ������������� ��� ������.
          for(int k=0; k<nodes; k++)
              if ( g[j][k] > (g[j][i - 1] + g[i - 1][k]) )  g[j][k] = g[j][i - 1] + g[i - 1][k];
    
    cin >> ways;
    for(int i=0; i<ways; i++)
    {
       cin >> a >> b;
       cout << g[ a-1 ][ b-1 ] << endl;
    } 
       cin >> ways;
    return 0;
}
