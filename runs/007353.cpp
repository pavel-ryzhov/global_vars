#include <iostream>
using namespace std;
class vw
{
 public:
 unsigned int num;
 unsigned int anc;
 unsigned int anclen;
 unsigned int depth;
};
class pr
{
 public:
 unsigned int v1;
 unsigned int v2;
};
class rebro
{
 public:
 unsigned int vr1;
 unsigned int vr2;
 unsigned int len;
 rebro* next;
 rebro* prev;
};
rebro* head=NULL;
int Empty()
{
 if (head->next==head && head->prev==head)
 return 1;
 else
 return 0;
}


int main()
{
 unsigned int N,pairN,pol,s=0;
 vw ve1,ve2;
 std::cin>>N;
 rebro* reb;
 vw *verw=new vw[N+1];
 vw *next=new vw[N+1];
 verw[1].num=1;
 verw[1].anc=1;
 verw[1].anclen=0;
 verw[1].depth=0;
 next[1].num=1;
 next[1].anc=1;
 next[1].anclen=0;
 next[1].depth=0;
 for (unsigned int i=0;i<N-1;i++)
 {
  reb=new rebro;
  std::cin>>reb->vr1>>reb->vr2>>reb->len;
  if (head==NULL)
  {
   reb->prev=NULL;
   reb->next=NULL;
   head=reb;
  }
  else
  {
   head->next=reb;
   reb->next=NULL;
   reb->prev=head;
   head=reb;
  }
 }
 std::cin>>pairN;
 pr *pair=new pr[pairN];
 for (unsigned int i=0;i<pairN;i++)
 {
  std::cin>>pair[i].v1>>pair[i].v2;
 }
 bool flag=false;
 for (unsigned int i=1;i<=N;i++)
 {
  reb=head;
  do 
  {
   if ((next[i].num==reb->vr1)&&(reb->vr2!=next[i].anc))
   {
    s++;
    next[i+s].num=reb->vr2;
    next[i+s].anc=next[i].num;
    next[i+s].depth=next[i].depth+1;
    next[i+s].anclen=reb->len;
    verw[reb->vr2]=next[i+s];
    if ((reb->next==NULL)&&(reb->prev!=NULL))
    {
     reb->prev->next=NULL;
     head=reb->prev;
    } 
    else if ((reb->prev==NULL)&&(reb->next!=NULL))
    {
     reb->next->prev=NULL;
    }
    else if ((reb->prev==NULL)&&(reb->next==NULL))
    {
     head=reb;
     flag=true;
    }
    else
    {
     reb->prev->next=reb->next;
     reb->next->prev=reb->prev;
    }
    delete reb;
   }
   else if ((next[i].num==reb->vr2)&&(reb->vr1!=next[i].anc))
   {
    s++;
    next[i+s].num=reb->vr1;
    next[i+s].anc=next[i].num;
    next[i+s].depth=next[i].depth+1;
    next[i+s].anclen=reb->len;
    verw[reb->vr1]=next[i+s];
    if ((reb->next==NULL)&&(reb->prev!=NULL))
    {
     reb->prev->next=NULL;
     head=reb->prev;
    } 
    else if ((reb->prev==NULL)&&(reb->next!=NULL))
    {
     reb->next->prev=NULL;
    }
    else if ((reb->prev==NULL)&&(reb->next==NULL))
    {
     head=reb;
     flag=true;
    }
    else
    {
     reb->prev->next=reb->next;
     reb->next->prev=reb->prev;
    }
    delete reb;
   }
  reb=reb->prev;
  }
  while(reb);
  s--;
  if (flag==true)
   break;
 }
 delete []next;
 delete []reb;
 for (unsigned int i=0;i<pairN;i++)
 {
  bool seekfl1=false,seekfl2=false;
  ve1=verw[pair[i].v1];
  ve2=verw[pair[i].v2];
  unsigned int length=0;
  bool poisk=true;
  while (poisk)
  {
   if (ve1.anc==ve2.num)
   {
    length+=ve1.anclen;
    std::cout<<length<<endl;
    poisk=false;
   }
   else if (ve2.anc==ve1.num)
   {
    length+=ve2.anclen;
    std::cout<<length<<endl;
    poisk=false;
   }
   else if ((ve1.depth>ve2.depth)&&(ve1.anc!=ve2.num))
   {
    length+=ve1.anclen;
    ve1=verw[ve1.anc];
   }
   else if ((ve2.depth>ve1.depth)&&(ve2.anc!=ve1.num))
   {
    length+=ve2.anclen;
    ve2=verw[ve2.anc];
   }
   else if ((ve2.depth==ve1.depth)&&(ve1.num!=ve2.num))
   {
    length+=ve1.anclen;
    ve1=verw[ve1.anc];
    length+=ve2.anclen;
    ve2=verw[ve2.anc];
   }
   else if (ve1.num==ve2.num)
    {
     std::cout<<length<<endl;\
     poisk=false;
    }
  }
 }
 delete []verw;
 return 0;
}
