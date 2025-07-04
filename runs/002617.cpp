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
  int GetElem(int i,int j);
  void SetElem(int i,int j,int elem);
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
  for (i=0;i<dim;i++) matrix[i]=new int[i+1];

  for(i=0;i<dim;i++)
   for(j=0;j<=i;j++) matrix[i][j]=-1;
 }

int TMatrix::GetElem(int i,int j)
 {
  if(i>j) return matrix[i][j]; else return matrix[j][i];
 }// end GetElem

void TMatrix::SetElem(int i,int j,int elem)
 {
  if(i>j) matrix[i][j]=elem;else matrix[j][i]=elem;
 }

void TMatrix::Print(std::ostream& myout)
 {
  int i,j;

  for(i=0;i<dim;i++)
   {
    for(j=0;j<=i;j++)
     {
      if(matrix[i][j]>=0) myout<<' ';
      if(matrix[i][j]/10==0) myout<<' ';
      if(matrix[i][j]/100==0) myout<<' ';
      myout<<matrix[i][j]<<' ';
     }
    myout<<'\n';
   }// for
 }// Print
/*--------Struct TMatrix---------------*/

TMatrix Ways;
int *NewOld,numb=-1;// this is an array for renaming
std::ifstream myin("Tests/my2.txt");

void Init()
 {// this procedure inits
  int i,j,k,N,length;

  std::cin>>N;// getting number of nodes
  Ways.InitMatrix(N);// Making matrix of ways
  NewOld=new int[N];
  for (k=1;k<N;k++)
   {
    std::cin>>i;i--;
    std::cin>>j;j--;
    std::cin>>length;
    Ways.SetElem(i,j,length);
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
    std::cout<<Ways.GetElem(i,j)<<'\n';;
   }// for
 }

void RenameNodes()
 {
  int *Stack,Top,i,t,f,*Father;

  Stack=new int[Ways.dim];Father=new int[Ways.dim];
  Top=0;Stack[0]=0;Father[0]=-1;
  while(Top>=0)
   {// while stack is not empty
    numb++;t=Stack[Top];f=Father[Top];Top--;
    NewOld[numb]=t;//std::cout<<"Renamed node "<<t<<".New name is:"<<numb<<" .\n";
    for(i=Ways.dim-1;i>=0;i--)
     if(i!=f && Ways.GetElem(t,i)!=-1)
      { Top++;Stack[Top]=i;Father[Top]=t;}
   }// end while Top>=0
  delete Stack;delete Father;
 }

void MakeWaysFirst()
 {
  int i,j,k,N,l,l1;

  N=Ways.dim;Ways.matrix[NewOld[N-1]][NewOld[N-1]]=0;
  for(j=N-2;j>=0;j--)
   {
    Ways.matrix[NewOld[j]][NewOld[j]]=0;
    for(i=j+1;i<N;i++)
     if((l=Ways.GetElem(NewOld[i],NewOld[j]))!=-1)
      {
       for(k=i+1;k<N && (l1=Ways.GetElem(NewOld[i],NewOld[k]))!=-1;k++) Ways.SetElem(NewOld[j],NewOld[k],l1+l);
      }// end if
   }
 }// end MakeWays1

void MakeWaysSecond()
 {// the final step if making a Matrix Of Ways
  int i,j,N,Way,k;

  N=Ways.dim;
  for(j=1;j<N;j++)
   {
    i=j+1;
    while(i<N && Ways.GetElem(NewOld[i],NewOld[j])!=-1) i++;
    for(;i<N && Ways.GetElem(NewOld[i],NewOld[j])==-1;i++)
     {
      Way=Ways.GetElem(NewOld[j-1],NewOld[i]);
      for(k=j;Ways.GetElem(NewOld[k],NewOld[i])==-1;k++)
       Ways.SetElem(NewOld[k],NewOld[i],Ways.GetElem(NewOld[j-1],NewOld[k])+Way);
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

int main()
{
    Init();
    Run();
    return 0;
}
