#include <fstream>
#include <iostream>

struct TMatrix
 {
  int dim;
  int** matrix;
  TMatrix();
  ~TMatrix();
  void InitMatrix(int dim1);
  void Print(std::ostream&);
 };
// struct TMatrix
/*--------Struct TMatrix---------------*/
TMatrix::TMatrix()
 {
  dim=0;
  matrix=NULL;
 }// constructor end

TMatrix::~TMatrix()
 {
  if (matrix!=NULL)
   {
    int i;

    for (i=0;i<dim;i++) delete matrix[i];
    delete matrix;
   }// if
 }// destructor end
 
void TMatrix::InitMatrix(int dim1)
 {
  int i,j;

  dim=dim1;
  matrix=new int*[dim];
  for (i=0;i<dim;i++) matrix[i]=new int[dim];

  for(i=0;i<dim;i++)
   for(j=0;j<dim;j++) matrix[i][j]=-1;
 }

void TMatrix::Print(std::ostream& myout)
 {
  int i,j;

  for(i=0;i<dim;i++)
   {
    for(j=0;j<dim;j++) 
     {
      if(matrix[i][j]<10) myout<<' ';
      if(matrix[i][j]<100) myout<<' ';
      myout<<matrix[i][j]<<' ';
     }
    myout<<'\n';
   }// for
 }// Print
/*--------Struct TMatrix---------------*/

TMatrix Graf,Ways;
int* OldNew,*NewOld,numb=-1;// this is an array for renaming
bool* Was;
std::ifstream myin("Tests/my2.txt");

void Init()
 {// this procedure inits
  int i,j,k,N,length;

  std::cin>>N;// getting number of nodes
  Graf.InitMatrix(N);// Making matrix of tree
  Ways.InitMatrix(N);// Making matrix of ways
  Was=new bool[N];
  OldNew=new int[N];NewOld=new int[N];
  for(k=0;k<N;k++) Was[k]=false;
  for (k=1;k<N;k++)
   {
    std::cin>>i;i--;
    std::cin>>j;j--;
    std::cin>>length;
    Graf.matrix[j][i]=length;Graf.matrix[i][j]=length;
   }// for 
 }// Init

void GetNumbers()
 {
  int k,m,i,j;

  std::cin>>m;
//  std::cout<<m<<"There are answers!\n";
  for(k=0;k<m;k++)
   {
    std::cin>>i;std::cin>>j;i--;j--;
    if(OldNew[i]<=OldNew[j]) std::cout<<Ways.matrix[OldNew[i]][OldNew[j]]<<'\n';
    else std::cout<<Ways.matrix[OldNew[j]][OldNew[i]]<<'\n';
   }// for
 }

void RenameNodesRec(int t,int father)
 {
  int i;

//  std::cout<<"Rename nodes: old node "<<t+1<<", new node "<<numb+1<<".\n";
  numb++;NewOld[numb]=t;OldNew[t]=numb;
  for(i=0;i<Graf.dim;i++)
   if(i!=father && Graf.matrix[t][i]!=-1) RenameNodesRec(i,t);
 }// end RenameNodes

void RenameNodes()
 {
  int i;

  numb++;NewOld[0]=0;OldNew[0]=0;
  for(i=1;i<Graf.dim;i++)
   if(Graf.matrix[0][i]!=-1) RenameNodesRec(i,0);
 }

void MakeWaysFirst()
 {
  int i,j,k,N,l;

  N=Ways.dim;Ways.matrix[N-1][N-1]=0;
  for(i=N-2;i>=0;i--)
   {
    Ways.matrix[i][i]=0;
    for(j=i+1;j<N;j++)
     if(Graf.matrix[NewOld[i]][NewOld[j]]!=-1)
      {
       l=Graf.matrix[NewOld[i]][NewOld[j]];
       for(k=j;Ways.matrix[j][k]!=-1 && k<N;k++) Ways.matrix[i][k]=Ways.matrix[j][k]+l;
      }// end if
   }
 }// end MakeWays1

void MakeWaysSecond()
 {// the final step if making a Matrix Of Ways
  int i,j,N,Way,k;

  N=Ways.dim;
  for(i=1;i<N;i++)
   {
    j=i+1;
    while(j<N && Ways.matrix[i][j]!=-1) j++;
    for(;j<N && Ways.matrix[i][j]==-1;j++)
     {
      Way=Ways.matrix[i-1][j];
      for(k=i;Ways.matrix[k][j]==-1;k++) Ways.matrix[k][j]=Ways.matrix[i-1][k]+Way;
     }// end for j
   }//end for i
 }// end MakeWays2

void Run()
 {
  numb=-1;
  RenameNodes();// from root
  MakeWaysFirst();// first step
  MakeWaysSecond();// second step
  GetNumbers();
 }

void Print()
 {// This function prints matrix to screen
  int i,j;

  std::cout<<"Ways\n";
  for(i=0;i<Ways.dim;i++)
   {
    for(j=0;j<Ways.dim;j++) 
     {
      if(Ways.matrix[i][j]<10) std::cout<<' ';
      if(Ways.matrix[i][j]<100) std::cout<<' ';
      std::cout<<Ways.matrix[i][j]<<' ';
     }
    std::cout<<'\n';
   }
 }

int main()
{
    Init();
    Run();
    return 0;
}
