#include <stdio.h>
#include <string.h>

const int INF = 1000;

struct vertex{
       int name;
       int parent;
       int tmp;
       };

void PrintMatrix (int * Matrix, int n){
     for (int i = 0; i<n; i++){
         for (int j = 0; j < n; j++){
             printf("%d ",Matrix[i*n + j]);
         }
         printf("\n");
     }
}    

void CleanVertexsTmp (vertex * Vertexs, int n){
     for ( int i =0; i<n; i++){
         Vertexs[i].tmp = 0;
     }
}
         
void PrintVertexs(vertex * Vertexs, int n){
     for (int i = 0; i<n; i++){
         printf("name = %d, parent = %d\n", Vertexs[i].name, Vertexs[i].parent);
     }
     printf("\n\n");
}

void InitVertexs(vertex * Vertexs, int n){
     for (int i = 0; i<n; i++){
         Vertexs[i].name = i; Vertexs[i].parent= -2; Vertexs[i].tmp = 0;
     }
}
       
void Search_Parents2(vertex * Vertexs, int * Matrix, int n, int &root){
    // printf("Ya tut\n");
     int line = 0, number_of_parents = 0, i =0, j = 0;
     for ( i = 0; i < n; i++){ //opredelyaem kto budet kornem
         line = 0;
         for (j = 0; j < n; j++){
             if (Matrix[i*n + j] < INF) line++;
         }
         if (line > 2) {root = i; break;}
     }
     Vertexs[root].parent = -1;
     number_of_parents++;
     while ( number_of_parents < n){
          for (i = 0; i<n; i++){ //perebiraem vse vershiny
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

void input(){};

void Parsing_Matrix(int * Adjacency_matrix, int n){
     int i = 0;
     int j = 0;
     char str[100];
     while (i < n){
           gets(str);
           for (j = 0; j < strlen(str); ++j){
           }
     }
}

void Parsing_Matrix2(int * Matrix, int * Routes, int &n, int &m){
     int i = 0, v1 = 0,v2 = 0,weight;
     scanf("%d", &n);
     Matrix = new int[n*n];
     for (i = 0; i<n*n; i++){Matrix[i] = INF;}
     /*for (i = 0; i < n-1; i++){
         scanf("%d %d %d", &v1, &v2, &weight);
         Matrix[v1*n+v2] = weight;
         Matrix[v2*n+v1] = weight;
     }*/
     PrintMatrix(Matrix, n);
     scanf("%d", &m);
     Routes = new int [2*m];
     //printf("opr putej kolichestvo\n");
     for (i = 0; i < m; i++){
         //printf("ozhidaem put\n");
         scanf("%d", &v1);
         //printf("vveli put1 %d\n", i);
         //Routes[2*i] = v1;
         //printf("i = %d\n", i);
         scanf("%d", &v1);
         //printf("vveli put2 %d\n", i);
         //Routes[2*i+1] = v1;
     }
}
      


int Distance(vertex * Vertexs, int* Matrix, int n, int p, int node01, int node02, int root){
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
                sum += Matrix[node2*n + node1];
                node2 = Vertexs[node2].parent;
          }
          return sum;
    }
    if (p == 3) {
          CleanVertexsTmp(Vertexs, n);
          while (Vertexs[node2].parent != root){
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
          
int Detect_case(vertex * Vertexs, int n, int root, int node01, int node02){
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
    int n,m, root = 0, result = 0, i = 0, v1 = 0,v2 = 0,weight;;

    input();
    int node1 = 0;
    int node2 = 0;
    int p = 0;
    int * Adjacency_matrix;// = new int[n*n];
    int * Routes;
    //Parsing_Matrix2(Adjacency_matrix, Routes, n,m);
     scanf("%d", &n);
     //n = 6;
     Adjacency_matrix = new int[n*n];
     for (i = 0; i<n*n; i++){Adjacency_matrix[i] = INF;}
     //Adjacency_matrix[] = 7;
     for (i = 0; i < n-1; i++){
         scanf("%d %d %d", &v1, &v2, &weight);
         Adjacency_matrix[(v1-1)*n+v2-1] = weight;
         Adjacency_matrix[(v2-1)*n+v1-1] = weight;
     }
     
     //PrintMatrix(Adjacency_matrix, n);
     scanf("%d", &m);
     Routes = new int [2*m];
     //printf("opr putej kolichestvo\n");
     if (n == 1) {
           for (i = 0; i < m; i++) {scanf("%d %d", &v1, &v2);}
           for (i = 0; i < m; i++){printf("0\n");}} else
     for (i = 0; i < m; i++){
         //printf("ozhidaem put\n");
         scanf("%d", &v1);
         //printf("vveli put1 %d\n", i);
         Routes[2*i] = v1-1;
         //printf("i = %d\n", i);
         scanf("%d", &v1);
         //printf("vveli put %d\n", i);
         Routes[2*i+1] = v1-1;
     }
    
    vertex * Vertexs = new vertex[n];
    InitVertexs(Vertexs, n);
    //printf("pristupaem k poisku roditelej\n");
    Search_Parents2(Vertexs, Adjacency_matrix, n, root);
    //printf("root %d\n", root);
    for ( i = 0; i < m; i++){
        node1 = Routes[2*i];
        node2 = Routes[2*i+1];
        p = Detect_case(Vertexs, n, root, node1, node2);
        //printf("sluchaj opredelen %d\n", p);
        result = Distance(Vertexs, Adjacency_matrix, n, p, node1, node2, root);
        printf("%d\n", result);
    }
    //getchar();
    scanf("%d",&n);
    delete[] Adjacency_matrix;
    delete[] Routes;
    return 0;
}
       
