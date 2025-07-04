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
   for(j=0;j<dim;j++) matrix[i][j]=0;
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

TMatrix Graf,Length,Ways,WaysBool;
bool* Was;
int* Leaf;
std::ifstream myin("Tests/my2.txt");

void Init()
 {// this procedure inits
  int i,j,k,N,length;

  std::cin>>N;// getting number of nodes
  Graf.InitMatrix(N);// Making matrix of tree
  Length.InitMatrix(N);// Making matrix of distances between nodes of tree
  Ways.InitMatrix(N);// Making matrix of ways
  WaysBool.InitMatrix(N);// Way was or not
  Was=new bool[N];Leaf=new int[N];
  for(k=0;k<N;k++) { Was[k]=false;Leaf[k]=-1;}
  for (k=1;k<N;k++)
   {
    std::cin>>i;i--;
    std::cin>>j;j--;
    std::cin>>length;
    Graf.matrix[j][i]=1;Graf.matrix[i][j]=1;
    Length.matrix[i][j]=length;Length.matrix[j][i]=length;
   }// for 
//  std::cout<<"Data are initialized!\n";
//  Graf.Print(std::cout);
//  std::cout<<"Matrix of distances!\n";
//  Length.Print(std::cout);
 }// Init

void GetLeaves()
 {
  int i,count,l,j;

//  std::cout<<"There are leaves:\n";
  for(i=1;i<Graf.dim;i++)
   {
    count=0;
    for(j=0;j<Graf.dim;j++) if(Graf.matrix[i][j]!=0) {count++;l=j;}
    if(count==1) Leaf[i]=l;
   }// for
 }

void InitMatrixOfWays(int t)
 {
  int i,j;

  Was[t]=true;
  for(i=0;i<Graf.dim;i++)
   {
    if(Graf.matrix[t][i]!=0 && !Was[i]) 
     {
      InitMatrixOfWays(i);
      Ways.matrix[t][i]=Length.matrix[t][i];WaysBool.matrix[t][i]=1;
       for(j=0;j<Ways.dim;j++)
        if(j!=t && WaysBool.matrix[i][j]!=0) 
         {Ways.matrix[t][j]=Ways.matrix[i][j]+Length.matrix[t][i];
          WaysBool.matrix[t][j]=1;}
     }// if
   }// for
  Was[t]=false;
 }// InitMatrixOfWays

void AddLeavesToWays()
 {
  int k,i,l;

  for(k=1;k<Graf.dim;k++)
   if(Leaf[k]!=-1)
    {
     l=Leaf[k];
     for(i=0;i<Ways.dim;i++) if(i!=k) Ways.matrix[k][i]=Ways.matrix[l][i]+Length.matrix[k][l];
    }// if
 }

void TransponeMatrix()
 {
  int i,j;// makes all matrix

  for(i=0;i<Ways.dim;i++)
   for(j=i+1;j<Ways.dim;j++) { Ways.matrix[j][i]=(Ways.matrix[i][j]);WaysBool.matrix[j][i]=(WaysBool.matrix[i][j]);}
 }

void MakeWays2Rec(int t,int father)
 {// t --- current node,father --- father(previous node of our tree)
  int i;// counter

  for(i=0;i<Ways.dim;i++)
   {
    if(i!=t && WaysBool.matrix[t][i]==0)
     {
      Ways.matrix[t][i]=Ways.matrix[father][i]+Length.matrix[t][father];
      Ways.matrix[i][t]=Ways.matrix[t][i];
      WaysBool.matrix[t][i]=1;WaysBool.matrix[i][t]=1;
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
    std::cout<<Ways.matrix[i][j]<<'\n';
   }// for
 }

void Run()
 {
  //GetLeaves();
  InitMatrixOfWays(0);
//  std::cout<<"This is first matrix of ways:\n";
//  Ways.Print(std::cout);
  MakeWays2();
  //AddLeavesToWays();
  //std::cout<<"All done";
  //TransponeMatrix();
  GetNumbers();// making answers
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
//    std::cout<<"Hello world!";
    Init();
    Run();
//    Print();
    return 0;
}
