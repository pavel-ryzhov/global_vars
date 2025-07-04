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
  if(dim1>0)
   {
    matrix=new int*[dim];
    for (i=0;i<dim;i++) matrix[i]=new int[dim];

    for(i=0;i<dim;i++)
     for(j=0;j<dim;j++) matrix[i][j]=0;
   }
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
bool* Was;

void Init()
 {// this procedure inits
  int i,j,k,N,length;

  std::cin>>N;// getting number of nodes
//  std::cout<<"Hello\n";
  Graf.InitMatrix(N);// Making matrix of tree
  Ways.InitMatrix(N);// Making matrix of ways
  Was=new bool[N];
  for(k=0;k<N;k++) Was[k]=false;
  for (k=1;k<N;k++)
   {
    std::cin>>i;i--;
    std::cin>>j;j--;
    std::cin>>length;
    Graf.matrix[j][i]=length;Graf.matrix[i][j]=length;
   }// for 
//  std::cout<<"Data are initialized!\n";
//  Graf.Print(std::cout);
 }// Init

void InitMatrixOfWays(int t)
 {
  int i,j;

  Was[t]=true;
  for(i=0;i<Graf.dim;i++)
   {
    if(Graf.matrix[t][i]!=0 && !Was[i]) 
     {
      InitMatrixOfWays(i);
      Ways.matrix[t][i]=Graf.matrix[t][i];
       for(j=0;j<Ways.dim;j++)
        if(j!=t && Ways.matrix[i][j]!=0) Ways.matrix[t][j]=Ways.matrix[i][j]+Graf.matrix[t][i];
     }// if
   }// for
  Was[t]=false;
 }// InitMatrixOfWays

void TransponeMatrix()
 {
  int i,j;// makes all matrix

  for(i=0;i<Ways.dim;i++)
   for(j=i+1;j<Ways.dim;j++) Ways.matrix[j][i]=(Ways.matrix[i][j]);
 }

void MakeWays2Rec(int t,int father)
 {// t --- current node,father --- father(previous node of our tree)
  int i;// counter

  for(i=0;i<Ways.dim;i++)
   {
    if(i!=t && Ways.matrix[t][i]==0)
     {
      Ways.matrix[t][i]=Ways.matrix[father][i]+Graf.matrix[t][father];
      Ways.matrix[i][t]=Ways.matrix[t][i];
     }// if
   }// for i
  for(i=0;i<Graf.dim;i++) 
   if(Graf.matrix[t][i]!=0 && i!=father) MakeWays2Rec(i,t);
 }// MakeWays2Rec

void MakeWays2()
 {
  int i;

  for(i=0;i<Graf.dim;i++) 
   if(Graf.matrix[0][i]!=0)
    {
     MakeWays2Rec(i,0);
    }// if
 }// MakeWays 2

void GetNumbers()
 {
  int k,m,i,j;

  std::cin>>m;
//  std::cout<<m<<"There are answers!\n";
  for(k=0;k<m;k++)
   {
    std::cin>>i;std::cin>>j;i--;j--;
    if(i>=0 && i<Ways.dim && j>=0 && j<Ways.dim) std::cout<<Ways.matrix[i][j]<<'\n';
   }// for
 }

void Run()
 {
  InitMatrixOfWays(0);
  MakeWays2();
//  Ways.Print(std::cout);
  GetNumbers();// making answers
 }

int main()
{
//    std::cout<<"Hello world!";
    Init();
    Run();
    return 0;
}
