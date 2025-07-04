#include <string.h>
#include <iostream>
//#include <fstream>
using namespace std;

const int INF = 100000;

struct vertex{
       int name;
       int parent;
       int tmp;
       };

/*void PrintMatrix (int * Matrix, int n){
     for (int i = 0; i<n; i++){
         for (int j = 0; j < n; j++){
             printf("%d ",Matrix[i*n + j]);
         }
         printf("\n");
     }
}*/    

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
       
void Search_Parents2(vertex * Vertexs, int * Matrix, unsigned long long int n, int &root){
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

unsigned long long int Distance(vertex * Vertexs, int* Matrix, unsigned long long int n, int p, int node01, int node02, int root){
    int sum = 0, node1 = node01, node2 = node02, node3 = 0; // p - sluchaj 
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
           while (node2 != root){
                 sum += Matrix[node2*n+Vertexs[node2].parent];
                 node2 = Vertexs[node2].parent;
           }
           while (node1 != root){
                 sum += Matrix[node1*n+Vertexs[node1].parent];
                 node1 = Vertexs[node1].parent;
           }
           return sum;
    }          
return -1;
}
          
int Detect_case(vertex * Vertexs, unsigned long long int n, int root, int node01, int node02){
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
    int  root = 0, i = 0, v1 = 0,v2 = 0, weight = 0;
    unsigned long long int result, m, n = 0; 
    int node1 = 0;
    int node2 = 0;
    /*ifstream in;
    ofstream out;
    in.open("data.in");
    out.open("data.out");
    */
    int p = 0;
    int * Adjacency_matrix;
    int * Routes;
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
     Adjacency_matrix = new int[n*n];
     for (i = 0; i<n*n; i++){Adjacency_matrix[i] = INF;}
     for (i = 0; i < n-1; i++){
	 cin >> v1 >> v2 >> weight;
         Adjacency_matrix[(v1-1)*n+v2-1] = weight;
         Adjacency_matrix[(v2-1)*n+v1-1] = weight;
     }
     
     cin >> m;
     Routes = new int [2*m];
     for (i = 0; i < m; i++){
	 cin >> v1;
         Routes[2*i] = v1-1;
	 cin >> v1;
         Routes[2*i+1] = v1-1;
     }
    
    vertex * Vertexs = new vertex[n];
    InitVertexs(Vertexs, n);
    Search_Parents2(Vertexs, Adjacency_matrix, n, root);
    //cout << "Nasli parents\n";
    //cout << "root =" << root << "\n";
    for ( i = 0; i < m; i++){
	//cout << i;
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
       
