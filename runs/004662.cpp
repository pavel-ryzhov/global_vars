#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

const unsigned short int INF = 50000;

struct vertex{
       int name;
       int parent;
       int tmp;
       };

void PrintMatrix (unsigned short int * Matrix, int n){
     for (int i = 0; i<n; i++){
         for (int j = 0; j < n; j++){
            cout << Matrix[i*n + j] << " ";
         }
         cout << "\n";
     }
}

void CleanVertexsTmp (vertex * Vertexs, unsigned long long int n){
     for ( int i =0; i<n; i++){
         Vertexs[i].tmp = 0;
     }
}
         
/*void PrintVertexs(vertex * Vertexs, int n){
     for (int i = 0; i<n; i++){
         printf("name = %d, parent = %d\n", Vertexs[i].name, Vertexs[i].parent);
     }
     printf("\n\n");
}*/

void InitVertexs(vertex * Vertexs, unsigned long long int n){
     for (int i = 0; i<n; i++){
         Vertexs[i].name = i; Vertexs[i].parent= -2; Vertexs[i].tmp = 0;
     }
}
       
void Search_Parents2(vertex * Vertexs, unsigned short int * Matrix, unsigned long long int n, unsigned short int &root){
    // printf("Ya tut\n");
     int line = 0, line_max = 0, number_of_parents = 0, i =0, j = 0;
     for ( i = 0; i < n; i++){ //opredelyaem kto budet kornem
         line = 0;
         for (j = 0; j < n; j++){
             if (Matrix[i*n + j] < INF) line++;
         }
         if (line > line_max) {line_max = line; root = i;}
     }     
     Vertexs[root].parent = -1;
     number_of_parents++;
     while ( number_of_parents < n){
       //cout << number_of_parents << "\n";
          for (i = 0; i<n; i++){ //perebiraem vse vershiny
	    //cout << i << "\n";
              if ((Vertexs[i].parent > -2)&&(Vertexs[i].tmp == 0)){ //neprosmotrennye i u kotoryh opredelen roditel
                                     for( j = 0; j < n; j++){ //perebiraem ih potomkov
                                          if (( Matrix[i*n + j] < INF)&&(j != Vertexs[i].parent)){ //otlichnyh ot roditelej
                                                Vertexs[j].parent = i;
                                                number_of_parents++;
                                          }
                                     }
                                     Vertexs[i].tmp = 1;
              }
          }
     }
}          

void Search_Parents3(vertex * Vertexs, unsigned short int * Matrix, unsigned long long int n, unsigned short int &root){
     int line = 0, line_max = 0, number_of_parents = 0;
     unsigned short int i =0, j = 0;
     unsigned short int Layer1[40000], Layer2[40000];
     unsigned short int m1 = 0,m2 = 0, m_hold = 0;
     for (i = 0; i< 40000; i++){
       Layer1[i] = -1;
       Layer2[i] = -1;
     }
     for ( i = 0; i < n; i++){ //opredelyaem kto budet kornem
         line = 0;
         for (j = 0; j < n; j++){
             if (Matrix[i*n + j] < INF) line++;
         }
         if (line > line_max) {line_max = line; root = i;}
     }
     Vertexs[root].parent = -1;
     number_of_parents++;
     for(i = 0; i < n; i++){
	if (Matrix[root*n + i] < INF) {
	  Vertexs[i].parent = root;
	  Layer1[m1] = i;
	  m1++;
	  number_of_parents++;
	}
     }
     while ( number_of_parents < n){
       m2 = 0;
       //cout << number_of_parents << " = number_of_parents \n";
       //if (m1 == 0) break;
	for (j = 0; j < m1; j++){
	  for (i = 0; i < n; i++){
	    if ((Matrix[Layer1[j]*n + i] < INF)){//&&(i != Vertexs[j].parent)) {
	      if (i == Vertexs[j].parent ) {continue;}
	      Vertexs[i].parent = Layer1[j];
	      number_of_parents++;
	      Layer2[m2] = i;
	      m2++;
	    }
	  }
	}
	for (i = 0; i < m2; i++){
	  Layer1[i] = Layer2[i];
	  Layer2[i] = -1;
	}
	for (i = m2; i< m1; i++){
	  Layer1[i] = -1;
	}
	m1 = m2;
     }
}
	   
	



unsigned long long int Distance(vertex * Vertexs, unsigned short int* Matrix, unsigned long long int n, int p, int node01, int node02, int root){
    unsigned short int node1 = node01, node2 = node02, node3 = 0; // p - sluchaj 
    unsigned long long int sum = 0;
    if (p == 0){
          return 0;
    }
    if (p == 1){
          while (node1 != node2){
                sum += Matrix[node1*n + Vertexs[node1].parent];
                node1 = Vertexs[node1].parent;
          }
          return sum;
    }
    if (p == 2){
          while (node2 != node1){
                sum += Matrix[node2*n + Vertexs[node2].parent];
                node2 = Vertexs[node2].parent;
          }
          return sum;
    }
    if (p == 3) {
          CleanVertexsTmp(Vertexs, n);
          while (node2!= root){
                Vertexs[node2].tmp = 1;
                node2 = Vertexs[node2].parent;
          }
          while (Vertexs[node1].tmp != 1){
                node1 = Vertexs[node1].parent;
          }
          node3 = node1;
          node1 = node01;
          node2 = node02;
          while (node1 != node3){
                sum += Matrix[node1*n+Vertexs[node1].parent];
                node1 = Vertexs[node1].parent;
          }
          while (node2 != node3){
                sum += Matrix[node2*n+Vertexs[node2].parent];
                node2 = Vertexs[node2].parent;
          }
          return sum;
    }
    if (p == 4) {
           node1 = node01;
           node2 = node02;
	   //cout << "prisvoenie proshlo\n";
           while (node2 != root){
		 //cout << "node2 = " << node2 <<"\n";
                 sum += Matrix[node2*n+Vertexs[node2].parent];
                 node2 = Vertexs[node2].parent;
           }
           //cout << "1yj cikl OK\n";
           while (node1 != root){
		 //cout << "node1 = " << node1 <<"\n";
                 sum += Matrix[node1*n+Vertexs[node1].parent];
                 node1 = Vertexs[node1].parent;
           }
           //cout << "2yj cikl tozhe\n";
           return sum;
    }          
return -1;
}
          
int Detect_case(vertex * Vertexs, unsigned long long int n, unsigned short int root, unsigned short int node01, unsigned short int node02){
    int node1 = node01, node2 = node02;
    if (node1 == node2) return 0;
    CleanVertexsTmp(Vertexs, n);
    while (node1 != root){
          if (node1 == node2) return 1;
          Vertexs[node1].tmp = 1;
          node1 = Vertexs[node1].parent;
    }
    node1 = node01;
    
    while (node2 != root){
          if (node2 == node1) return 2;
          if (Vertexs[node2].tmp == 1) return 3;
          node2 = Vertexs[node2].parent;
    }
return 4;
}
    
  
int main(){
    int  i = 0, weight = 0;
    unsigned long long int result = 0;
    unsigned int m = 0, n = 0; 
    unsigned short int node1 = 0, root = 0, v1 = 0,v2 = 0, node2 = 0;
    ifstream in;
    //ofstream out;
    in.open("a.in");
    //out.open("data.out");
    
    int p = 0;
    unsigned short int * Adjacency_matrix;
    unsigned short int * Routes;
     cin >> n;
     if (n == 1) {
	   cin >> m;
           for (i = 0; i < m; i++){
		cin >> node1 >> node2;
           }
           for (i = 0; i < m; i++){
		cout << 0;
                if (m > 1) cout << " ";
           }
           return 0;
     }
     Adjacency_matrix = new unsigned short int[n*n];
     for (i = 0; i<n*n; i++){Adjacency_matrix[i] = INF;}
     for (i = 0; i < n-1; i++){
	 cin >> v1 >> v2 >> weight;
         Adjacency_matrix[(v1-1)*n+v2-1] = weight;
         Adjacency_matrix[(v2-1)*n+v1-1] = weight;
     }
     cin >> m;
     Routes = new unsigned short int [2*m];
     for (i = 0; i < m; i++){
	 cin >> v1;
         Routes[2*i] = v1-1;
	 cin >> v1;
         Routes[2*i+1] = v1-1;
     }
    //PrintMatrix(Adjacency_matrix, n);
    vertex * Vertexs = new vertex[n];
    InitVertexs(Vertexs, n);
    Search_Parents3(Vertexs, Adjacency_matrix, n, root);
    //cout << "Nasli parents\n";
    //cout << "root =" << root << "\n";
    //cout << "m = " << m<< "\n";
    for ( i = 0; i < m; i++){
	//cout << i <<" =i\n";
	node1 = Routes[2*i];
        node2 = Routes[2*i+1];
        //cout << "opredelyaem sluchaj";
        p = Detect_case(Vertexs, n, root, node1, node2);
	//cout << "sluchaj "<< p << "\n";
        result = Distance(Vertexs, Adjacency_matrix, n, p, node1, node2, root);
	cout << result << "\n";
    }
    /*in.close();
    out.close();*/
    delete[] Adjacency_matrix;
    delete[] Routes;
    return 0;
}
       
