#include <vector>
#include <stdio.h>
#include <queue>
#include <iostream>
#include <stdlib.h>
//#include <conio.h>

std::vector < std::vector<int> > g;  // ����
std::vector < std::vector<int> > h;  // ����
int *Distance;                // ������� ����������

int request(int n, int s, int end)
{
  std::vector <bool> used (n);
  std::vector <int> d (n), outd (n);
  std::queue < int > q;
  q.push (s);
  used[s] = true;
  outd[s] = 0;
  while (!q.empty())
  {
    int v = q.front();
    q.pop();
    for (size_t i = 0; i<g[v].size(); i++)
    {
      int to = g[v][i];
      if (!used[to])
      {
        used[to] = true;
        q.push (to);
        d[to] = d[v] + 1;
        outd[to] = outd[v] + h[v][i];
      }
    }
  }
  return outd[end];
}

int main ()
{
  int i,j,x,y,dist;
  int n,m;                                                // ����� ������
  // ������ �����
  scanf("%d",&n);
  std::vector < int > result (n);
  Distance=(int*)malloc(n*n*sizeof(int));                    //�������������
  for (i = 0; i<n; i++)
    for (j = 0; j<n; j++)
      Distance[i*n+j]=-1;

  for (i = 0; i<n-1; i++)
  {
    scanf("%d%d%d",&x,&y,&dist);                        //���� �������
    Distance[(x-1)*n+y-1]=dist;
    Distance[(y-1)*n+x-1]=dist;
  }
/*  for (i = 0; i<n; i++)                                 //������������� �������
    for (j = 0; j<n; j++)
    {
      if(Distance[i*n+j]>-1)
        Distance[j*n+i]=Distance[i*n+j];
      else if(Distance[j*n+i]>-1)
        Distance[i*n+j]=Distance[j*n+i];
    }
        for (i = 0; i<n; i++)
        {
          for (j = 0; j<n; j++)
            printf("%d ", Adj[i*n+j]);
          printf("\n");
        }
*/
  for (i = 0; i<n; i++)                                 //���������� �����
  {
    g.push_back(std::vector < int > ());
    h.push_back(std::vector < int > ());
    for(j = 0; j<n; j++)
    {
      if(Distance[i*n+j]>-1)
      {
        g[i].push_back(j);
        h[i].push_back(Distance[i*n+j]);
      }
    }
  }
//        for (int i = 0; i<n; i++)
//                cout << d[i] << "  ";
//        cout << endl;
//   for (i = 0; i<n; i++)
//     cout << request(n, s, i) << "  ";
  scanf("%d",&m);
  for (i = 0; i<m; i++)
  {
    scanf("%d%d",&x,&y);
    result[i]=request(n, x-1, y-1);
    printf("%d\n", result[i]);
  }
//  for (i = 0; i<m; i++)
//  getch();
  return 0;
}
