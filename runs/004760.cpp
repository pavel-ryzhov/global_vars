#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

struct node {
  int number;
  int parent;  
  int n;
  int * child;
  int * dist;
  long long int dist_to_root;
  int tmp;
};
 
struct rib{
  int v1;
  int v2;
  int weight;
};

void Quicksort(int * a, int *  dist, int p, int r);
int Partition(int * a, int *  dist, int p, int r);
void swap(int * a, int *  dist, int i, int j);

void Print_Node (node a){
  cout << "$ = " << a.number <<" parent = "<<a.parent<<" detok = "<<a.n<<" spisok detok:\n"<<endl;
  for (int i = 0; i<a.n; i++){
    cout << a.child[i] <<" ";//<<a.dist[i]<<") ";
  }
  cout << endl;
}

int Find_Distance(node * Matrix, int node1, int node2){
  int a = 0, b = 0, tmp;
  b = Matrix[node1].n;
  tmp = 0;
  while (Matrix[node1].child[tmp] != node2){
    tmp = (int) (a+b)/2;
    if (Matrix[node1].child[tmp] > node2) {
      b = tmp;
    } else {a = tmp;}
  }
  return Matrix[node1].dist[tmp];
}
    
void Print_All_Node ( node * Matrix, int n){
  for (int i = 0; i< n; i++){
    //cout << i<<endl;
    Print_Node(Matrix[i]);
  }
}

void Clean_Tmp(node * Matrix, int n){
  for ( int i = 0; i<n; i++){
    Matrix[i].tmp = 0;
  }
}

void Search_Parents(node * Matrix, int n, unsigned short root){
  int i = 0, j = 0, number_of_parent = 0;
  int * Layer1 = new  int [n];
  int * Layer2 = new  int [n];
  int count1 = 0, count2 = 0;
  Matrix[root].parent = 50000;
  for (i = 0; i < n; i++){
    Layer1[i] = 0;
    Layer2[i] = 0;
  }
  Layer1[0] = root;
  count1 = 1;
  number_of_parent++;
  while (number_of_parent < n){
    count2 = 0;
    for (i = 0; i < count1; i++){ // perebor roditelej
      for (j = 0; j < Matrix[Layer1[i]].n; j++){ //perebor detok
	if (Matrix[Layer1[i]].child[j] == Matrix[Layer1[i]].parent) continue;
	Matrix[Matrix[Layer1[i]].child[j]].parent = Layer1[i];
	Matrix[Matrix[Layer1[i]].child[j]].dist_to_root = Matrix[Layer1[i]].dist_to_root + Matrix[Layer1[i]].dist[j];
	number_of_parent++;
	Layer2[count2++] = Matrix[Layer1[i]].child[j];
      }
    }
    for (i = 0; i < count2; i++){
      Layer1[i] = Layer2[i];
    }
    for ( i = count2; i< count1; i++){
      Layer1[i] = 0;
    }
    count1 = count2;
  }
}
 
int Detect_Case ( node * Matrix, int n, int root, int node01, int node02, int &rod){
  int node1 = node01, node2 = node02;
  rod = 0;
  if (node1 == node2) return 0; 
  if (node1 == root) return 2;
  Clean_Tmp(Matrix,n);
  while (node1 != root){
    Matrix[node1].tmp = 1;
    node1 = Matrix[node1].parent;
  }
  if ((Matrix[node2].tmp == 1)||(node2 == root)) return 1;
  while (node2 != root){
    if (node2 == node01) return 2;
    if (Matrix[node2].tmp == 1) { rod = node2; return 3;}
    node2 = Matrix[node2].parent;
  }
  return 4;
}
    
unsigned long long int Calculate_Distance(node * Matrix, int n, int root, int node01, int node02, int p, int rod){
  unsigned long long int sum = 0;
  int node1 = node01, node2 = node02;
  if (p == 0) {
    return 0;
  } else if (p == 1){
    sum = Matrix[node1].dist_to_root - Matrix[node2].dist_to_root;
  } else if (p == 2){
    sum = Matrix[node2].dist_to_root - Matrix[node1].dist_to_root;
  } else if (p == 3){
    sum = Matrix[node1].dist_to_root + Matrix[node2].dist_to_root - 2*Matrix[rod].dist_to_root;
  } else if (p == 4){
    sum = Matrix[node1].dist_to_root + Matrix[node2].dist_to_root;
  }
  return sum;
}

 
  
int main(void){   
  int n = 0, i = 0, p= 0, vvod = 1;
  int tmp = 0, root = 0, root_max = 0, node1 = 0, node2 = 0, m = 0;
  unsigned long long int result = 0;
  int rod = 0;
  //if (vvod == 0){
    ifstream in;
    in.open("data.in");
  //}
  node * Matrix;
  rib * Rib;
  int * M;
  int * number_of_child;
  //in >> n;
  cin >>n;
  Matrix = new node [n];
  Rib = new rib [n];
  number_of_child = new int [n];
  for (i = 0; i<n; i++){
    number_of_child[i] = 0;
  }  
  for (i = 0; i< n-1; i++){ //opredelyaem kolichestvo detok u kazhdoj vershiny
    
    //in >> Rib[i].v1 >> Rib[i].v2 >> Rib[i].weight;
    cin >> Rib[i].v1 >> Rib[i].v2 >> Rib[i].weight;
    number_of_child[--Rib[i].v1]++;
    number_of_child[--Rib[i].v2]++;
  }
  //in >> m;
  cin >>m;
  M = new int [2*m];
  for (i = 0; i < m; i++){
    //in >> M[2*i] >> M[2*i+1];
    cin >> M[2*i] >> M[2*i+1];
    M[2*i]--;
    M[2*i+1]--;
  }
  
  for (i = 0; i<n; i++){ //vydelyaem pamyat pod detok i ischem root
    if (number_of_child[i] > root_max) {root = i; root_max = number_of_child[i];}
    Matrix[i].n = 0;
    Matrix[i].tmp = 0;
    Matrix[i].number = i;
    Matrix[i].child = new int [number_of_child[i]];
    Matrix[i].dist = new int [number_of_child[i]];  
  }
  Matrix[root].dist_to_root = 0;
  for ( i = 0; i< n-1; i++){
    Matrix[Rib[i].v1].child[Matrix[Rib[i].v1].n] = Rib[i].v2;
    Matrix[Rib[i].v1].dist[Matrix[Rib[i].v1].n] = Rib[i].weight;
    Matrix[Rib[i].v1].n++;
    Matrix[Rib[i].v2].child[Matrix[Rib[i].v2].n] = Rib[i].v1;
    Matrix[Rib[i].v2].dist[Matrix[Rib[i].v2].n] = Rib[i].weight;
    Matrix[Rib[i].v2].n++;
  }
  //Print_Node(Matrix[6]);
  //cout<<"tut\n";
  
   //cout << "tut3s\n";
   //Print_Node(Matrix[6]);
  Search_Parents(Matrix, n, root);
  
  for (i = 0; i<m; i++){
    p = Detect_Case(Matrix,n, root, M[2*i], M[2*i+1], rod);
    //cout << "p = "<< p<<endl;
    result = Calculate_Distance(Matrix, n, root, M[2*i], M[2*i+1], p, rod);
    cout << result <<"\n";
    result = 0;
  }
  //cout << " distance between "<<++node1<<" and "<< ++node2<< " = "<<result<<endl; 
  //cout << "preved"<< endl;
  delete[] Matrix;
  delete[] Rib;
  delete[] M;
  M = NULL;
  Rib = NULL;
  Matrix = NULL;
  in.close();
return 0;
}