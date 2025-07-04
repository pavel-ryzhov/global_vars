#include<iostream>
using namespace std;
int shortPath(int a,int b);
int cost[10][10], a[10][10], i, j, k, c;
 
int main()
{
  int n, m;
  cin >> n;
  cin >> m;
for(k=1; k <= m; k++) {
cin >> i >> j >> c;
a[i][j] = cost[i][j] = c;
}
for(i = 1; i <= n; i++)
for(j = 1; j <= n; j++) {
if(a[i][j]== 0 && i !=j)
a[i][j]=40000;
}
for(k = 1; k <= n; k++)
for(i = 1; i <= n; i++)
for(j = 1; j <= n; j++)
a[i][j]=shortPath(a[i][j],a[i][k]+a[k][j]);
cout <<" ";
for(i = 1; i <= n; i++) {

for(j = 1; j <= n; j++) {
  if(a[i][j] !=40000)
  cout << a[i][j] <<" ";
  }
cout <<"\n";
}
return 0;
}

int shortPath(int a,int b) {
if(a < b)
return a;
else
return b;
}