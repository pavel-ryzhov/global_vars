#include <iostream>
#include <fstream>

struct TElem{
  unsigned int son;
  unsigned int way;
  TElem* next;
 };

struct TArrElem{
  unsigned int father;
  unsigned int way;
 };

std::ifstream myin("Tests/my2.txt");
unsigned int N,* queue1,* queue2;
bool* Was;
TElem** Graf;
TArrElem* Fathers;

void Init()
 {
  unsigned int i,a,b,len;
  TElem* p1;

  std::cin>>N;// N -- is a number of nodes
  Graf=new TElem*[N];Was=new bool[N];
  for(i=0;i<N;i++) {Graf[i]=NULL;Was[i]=false;}
  for(i=0;i<N-1;i++)
   {
    std::cin>>a;std::cin>>b;a--;b--;std::cin>>len;
    if(Graf[a]==NULL)
     {
      Graf[a]=new TElem;p1=Graf[a];
      p1->son=b;p1->way=len;p1->next=NULL;
     }
    else
     {
      p1=Graf[a];
      while(p1->next!=NULL) p1=p1->next;
      p1->next=new TElem;
      p1->next->son=b;p1->next->way=len;p1->next->next=NULL;
     }// end else
    if(Graf[b]==NULL)
     {
      Graf[b]=new TElem;
      Graf[b]->son=a;Graf[b]->way=len;Graf[b]->next=NULL;
     }
    else
     {
      p1=Graf[b];
      while(p1->next!=NULL) p1=p1->next;
      p1->next=new TElem;
      p1->next->son=a;p1->next->way=len;p1->next->next=NULL;
     }// end else
   }// end for
 }// end Init

void MakeArrayOfSons()
 {
  unsigned int i,head,tail,node;
  TElem* p1,*p2;

  Fathers=new TArrElem[N];queue1=new unsigned int[N];queue2=new unsigned int[N];
  head=0;tail=1;queue1[0]=0;Fathers[0].father=0;Fathers[0].way=0;
  while(head<tail)
   {
    node=queue1[head];head++;
    Was[node]=true;p1=Graf[node];
    while(p1!=NULL)
     {
      if(!Was[p1->son])
       {
        queue1[tail]=p1->son;Fathers[p1->son].father=node;Fathers[p1->son].way=p1->way;
        tail++;
       }// end if
      p1=p1->next;
     }// end while
   }// end while
  for(i=0;i<N;i++)
   {
    p1=Graf[i];
    while(p1!=NULL) {p2=p1->next;delete p1;p1=p2;}
   }
  delete Graf;
 }// end MakeArrayOfSons

/*void PrintArrayOfSons()
 {
  unsigned int i;

  std::cout<<"Root is 1.\n";
  for(i=1;i<N;i++) std::cout<<"Node "<<i+1<<"is a son of a node "<<Fathers[i].father+1<<".Way:"<<Fathers[i].way<<".\n";
 }// end PrintArrayOfSons

void PrintGraf()
 {
  unsigned int i;
  TElem* p1;

  for(i=0;i<N;i++)
   {
    std::cout<<"Node "<<i+1<<".Sons:\n";
    p1=Graf[i];
    while(p1!=NULL) {std::cout<<"Son: "<<p1->son+1<<",Way: "<<p1->way<<'\n';p1=p1->next;}
   }
 }
*/
int GetWay(unsigned int a,unsigned int b)
 {
  unsigned int i,node1,node2,way1,way2;

  if(a==b) return 0;
  for(i=0;i<N;i++) Was[i]=false;
  node1=a;node2=b;way1=way2=0;queue1[node1]=0;queue2[node2]=0;
  //Was[node1]=Was[node2]=true;node1=Fathers[node1].father;node2=Father[node2].father;
  while(!(Was[node1] || Was[node2]) && node1!=0 && node2!=0 && node1!=node2)
   {
    Was[node1]=true;Was[node2]=true;
    queue1[node1]=way1;queue2[node2]=way2;
    way1+=Fathers[node1].way;way2+=Fathers[node2].way;
    node1=Fathers[node1].father;
    node2=Fathers[node2].father;
   }// end while
  if(node1==node2) return way2+way1;
  if(node1==0)
   {
    Was[node1]=true;queue1[node1]=way1;
    while(!Was[node2])
     {
      Was[node2]=true;queue2[node2]=way2;way2+=Fathers[node2].way;
      node2=Fathers[node2].father;
     }
    return way2+queue1[node2];
   } else
  if(node2==0)
   {
    Was[node2]=true;queue2[node2]=way2;
    while(!Was[node1])
     {
      Was[node1]=true;queue1[node1]=way1;way1+=Fathers[node1].way;
      node1=Fathers[node1].father;
     }
    return way1+queue2[node1];
   }
  if(Was[node1] && Was[node2]) return way1+way2;
  if(Was[node1]) return way1+queue2[node1];
  return queue1[node2]+way2;
 }

void MakeAnswer()
 {
  unsigned int i,m,a,b,way;

  std::cin>>m;
  for(i=0;i<m;i++)
   {
    std::cin>>a;std::cin>>b;a--;b--;way=GetWay(a,b);
    std::cout<<way<<'\n';
   }//end for
 }

int main()
 {
  Init();
  MakeArrayOfSons();
  MakeAnswer();
  return 0;
 }
