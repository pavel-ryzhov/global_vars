#include <iostream>
#include <string.h>
#include <stdlib.h>
//#include <fstream>

using namespace std;

struct node {
  unsigned short int number;
  unsigned short int parent;  
  unsigned short int n;
  unsigned short int * child;
  unsigned short int * dist;
  unsigned short int tmp;
};
 
struct rib{
  unsigned short int v1;
  unsigned short int v2;
  unsigned short int weight;
};

void Print_Node (node a){
  cout << "$ = " << a.number <<" parent = "<<a.parent<<" detok = "<<a.n<<" spisok detok:\n"<<endl;
  for (int i = 0; i<a.n; i++){
    cout << a.child[i] <<" ("<<a.dist[i]<<") ";
  }
  cout << endl;
}

unsigned short int Find_Distance(node * Matrix, unsigned short int node1, unsigned short int node2){
  unsigned short int a = 0, b = 0, tmp;
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

int cmp(const void * a, const void * b){
  int c = ((*(node * const) a).number	 - (*(node * const) b).number); 
  return c;
}

void bubble_sort(node Node, int n){
  int i = 0, finish = 1;
  unsigned short int tmp;
  while (finish){
    finish = 0;
    for (i = 1; i< n-1; i++){
      if (Node.child[i-1] > Node.child[i]) {
	tmp = Node.child[i];
	Node.child[i] = Node.child[i-1];
	Node.child[i-1] = tmp;
	tmp = Node.dist[i];
	Node.dist[i] = Node.dist[i-1];
	Node.dist[i-1] = tmp;
	finish = 1;
      }
      if (Node.child[i] > Node.child[i+1]) {
	tmp = Node.child[i];
	Node.child[i] = Node.child[i+1];
	Node.child[i+1] = tmp;
	tmp = Node.dist[i];
	Node.dist[i] = Node.dist[i+1];
	Node.dist[i+1] = tmp;
	finish = 1;
      }
      
      
    }
  }
}

void Clean_Tmp(node * Matrix, unsigned short int n){
  for ( int i = 0; i<n; i++){
    Matrix[i].tmp = 0;
  }
}
void Search_Parents(node * Matrix, unsigned short int n, unsigned short root){
  int i = 0, j = 0, number_of_parent = 0;
  unsigned short int * Layer1 = new  unsigned short int [n];
  unsigned short int * Layer2 = new  unsigned short int [n];
  unsigned short int count1 = 0, count2 = 0;
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
    for (i = 0; i < count1; i++){
      for (j = 0; j < Matrix[Layer1[i]].n; j++){
	if (Matrix[Layer1[i]].child[j] == Matrix[Layer1[i]].parent) continue;
	Matrix[Matrix[Layer1[i]].child[j]].parent = Layer1[i];
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
 
int Detect_Case ( node * Matrix, int n, unsigned short int root, unsigned short int node01, unsigned short int node02){
  unsigned short int node1 = node01, node2 = node02;
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
    if (Matrix[node2].tmp == 1) return 3;
    node2 = Matrix[node2].parent;
  }
  return 4;
}
    
unsigned long long int Calculate_Distance(node * Matrix, unsigned short int n, unsigned short int root, unsigned short int node01, unsigned short int node02, int p){
  unsigned long long int sum = 0;
  unsigned short int node1 = node01, node2 = node02;
  if (p == 0) {
    return 0;
  } else if (p == 1){
    while(node1 != node2){
      sum+=Find_Distance(Matrix, node1, Matrix[node1].parent);
      node1 = Matrix[node1].parent;
    }
    return sum;
  } else if (p == 2){
    while(node2 != node1){
      sum+=Find_Distance(Matrix, node2, Matrix[node2].parent);
      node2 = Matrix[node2].parent;
    }
    return sum;
  } else if (p == 3){
    Clean_Tmp(Matrix,n);
    while (node1 != root){
      Matrix[node1].tmp = 1;
      node1 = Matrix[node1].parent;
    }
    node1 = node01;
    while (Matrix[node2].tmp != 1){
      sum += Find_Distance(Matrix, node2, Matrix[node2].parent);
      node2 = Matrix[node2].parent;
    }
    Matrix[node2].tmp = 2;
    while (Matrix[node1].tmp != 2){
      sum += Find_Distance(Matrix, node1, Matrix[node1].parent);
      node1 = Matrix[node1].parent;
    }
    return sum;
  } else if (p == 4){
    while (node1 != root){
      //cout << "node1 = "<< node1<<endl;
      sum += Find_Distance(Matrix, node1, Matrix[node1].parent);
      node1 = Matrix[node1].parent;
    }
    while (node2 != root){
       //cout << "node2 = "<< node2<<endl;
       //cout << "node2 parent = "<< Matrix[node2].parent<<endl;
      sum += Find_Distance(Matrix, node2, Matrix[node2].parent);
      //cout << "ischems\n";
      node2 = Matrix[node2].parent;
      //cout << "node2 = "<< node2<<endl;
      if (node2 == root) return sum;
      //cout <<"sum = "<<sum<<endl;
    }
    return sum;
  }
}

  
  
int main(void){   
  int n = 0, i = 0, p= 0, vvod = 1;
  unsigned short int root = 0, root_max = 0, node1 = 0, node2 = 0, m = 0;
  unsigned long long int result = 0;
  //if (vvod == 0){
  //  ifstream in;
    //in.open("data.in");
  //}
  node * Matrix;
  rib * Rib;
  unsigned short int * M;
  unsigned short int * number_of_child;
  //in >> n;
  cin >>n;
  Matrix = new node [n];
  Rib = new rib [n];
  number_of_child = new unsigned short int [n];
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
  M = new unsigned short int [2*m];
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
    Matrix[i].child = new unsigned short int [number_of_child[i]];
    Matrix[i].dist = new unsigned short int [number_of_child[i]];  
  }
  for ( i = 0; i< n-1; i++){
    Matrix[Rib[i].v1].child[Matrix[Rib[i].v1].n] = Rib[i].v2;
    Matrix[Rib[i].v1].dist[Matrix[Rib[i].v1].n] = Rib[i].weight;
    Matrix[Rib[i].v1].n++;
    Matrix[Rib[i].v2].child[Matrix[Rib[i].v2].n] = Rib[i].v1;
    Matrix[Rib[i].v2].dist[Matrix[Rib[i].v2].n] = Rib[i].weight;
    Matrix[Rib[i].v2].n++;
  }
  
  //cout << "root = "<<root<< endl;
  for ( i = 0; i< n; i++){ //Otlichno. Vse deti uporyadocheny
    bubble_sort(Matrix[i], Matrix[i].n);
  }
  Search_Parents(Matrix, n, root);
  /*node1 = 8;
  node2 = 6;
  node1--;
  node2--;
  */
  
  for (i = 0; i<m; i++){
    p = Detect_Case(Matrix,n, root, M[2*i], M[2*i+1]);
    //cout << "p = "<< p<<endl;
    result = Calculate_Distance(Matrix, n, root, M[2*i], M[2*i+1], p);
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
  //in.close();
return 0;
}