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
};
int main()
{
 unsigned int N,pairN,pol,s=0;
 vw ve1,ve2;
 std::cin>>N;
 rebro *reb=new rebro[N-1];
 vw *verw=new vw[N];
 vw *next=new vw[N];
 verw[0].num=1;
 verw[0].anc=1;
 verw[0].anclen=0;
 verw[0].depth=0;
 next[0].num=1;
 next[0].anc=1;
 next[0].anclen=0;
 next[0].depth=0;
 for (unsigned int i=0;i<N-1;i++)
 {
  std::cin>>reb[i].vr1>>reb[i].vr2>>reb[i].len;
 }
 std::cin>>pairN;
 pr *pair=new pr[pairN];
 for (unsigned int i=0;i<pairN;i++)
 {
  std::cin>>pair[i].v1>>pair[i].v2;
 }
 for (unsigned int i=0;i<N;i++)
 {
  for (unsigned int j=0;j<N-1;j++)
  {
   if ((next[i].num==reb[j].vr1)&&(reb[j].vr2!=next[i].anc))
   {
    s++;
    next[i+s].num=reb[j].vr2;
    next[i+s].anc=next[i].num;
    next[i+s].depth=next[i].depth+1;
    next[i+s].anclen=reb[j].len;
    verw[reb[j].vr2-1]=next[i+s];
   }
   else if ((next[i].num==reb[j].vr2)&&(reb[j].vr1!=next[i].anc))
   {
    s++;
    next[i+s].num=reb[j].vr1;
    next[i+s].anc=next[i].num;
    next[i+s].depth=next[i].depth+1;
    next[i+s].anclen=reb[j].len;
    verw[reb[j].vr1-1]=next[i+s];
   }
  }
  s--;
 }
 delete []next;
 for (unsigned int i=0;i<pairN;i++)
 {
  bool seekfl1=false,seekfl2=false;
  unsigned int j=0;
  ve1=verw[pair[i].v1-1];
  ve2=verw[pair[i].v2-1];
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
    ve1=verw[ve1.anc-1];
   }
   else if ((ve2.depth>ve1.depth)&&(ve2.anc!=ve1.num))
   {
    length+=ve2.anclen;
    ve2=verw[ve2.anc-1];
   }
   else if ((ve2.depth==ve1.depth)&&(ve1.num!=ve2.num))
   {
    length+=ve1.anclen;
    ve1=verw[ve1.anc-1];
    length+=ve2.anclen;
    ve2=verw[ve2.anc-1];
   }
   else if (ve1.num==ve2.num)
   {
    std::cout<<length<<endl;\
    poisk=false;
   }
  }
 }
 delete []verw;
 delete []reb;
 return 0;
}
