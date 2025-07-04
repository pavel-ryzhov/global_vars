#include <iostream>
using namespace std;
class vw
{
 public:
 long num;
 long anc;
 long anclen;
 long depth;
};
class pr
{
 public:
 long v1;
 long v2;
};
class rebro
{
 public:
 long vr1;
 long vr2;
 long len;
};
int main()
{
 long N,pairN,pol,s=0;
 std::cin>>N;
 rebro *reb=new rebro[N-1];
 vw *verw=new vw[N];
 verw[0].num=1;
 verw[0].anc=1;
 verw[0].anclen=0;
 verw[0].depth=0;
 for (long i=0;i<N-1;i++)
 {
  std::cin>>reb[i].vr1>>reb[i].vr2>>reb[i].len;
 }
 std::cin>>pairN;
 pr *pair=new pr[pairN];
 for (long i=0;i<pairN;i++)
 {
  std::cin>>pair[i].v1>>pair[i].v2;
 }
 for (long i=0;i<N;i++)
 {
  for (long j=0;j<N-1;j++)
  {
   if ((verw[i].num==reb[j].vr1)&&(reb[j].vr2!=verw[i].anc))
   {
    s++;
    verw[i+s].num=reb[j].vr2;
    verw[i+s].anc=verw[i].num;
    verw[i+s].depth=verw[i].depth+1;
    verw[i+s].anclen=reb[j].len;
   }
   else if ((verw[i].num==reb[j].vr2)&&(reb[j].vr1!=verw[i].anc))
   {
    s++;
    verw[i+s].num=reb[j].vr1;
    verw[i+s].anc=verw[i].num;
    verw[i+s].depth=verw[i].depth+1;
    verw[i+s].anclen=reb[j].len;
   }
  }
  s--;
 }
 for (long i=0;i<pairN;i++)
 {
  bool seekfl1=false,seekfl2=false;
  long j=0,k1=0,k2=0;
  while ((!seekfl1)||(!seekfl2))
  {
   if (pair[i].v1==verw[j].num)
   {
    k1=j;
    seekfl1=true;
   }
   if (pair[i].v2==verw[j].num)
   {
    k2=j;
    seekfl2=true;
   }
   j++;
  }
  vw ve1,ve2;
  ve1=verw[k1];
  ve2=verw[k2];
  long length=0;
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
    bool sk=true;
    long l1=0;
    while ((sk)&&(l1<N))
    {
     if (verw[l1].num==ve1.anc)
     {
      
      length+=ve1.anclen;
      ve1=verw[l1];
      sk=false;
     }
     l1++;
    }
   }
   else if ((ve2.depth>ve1.depth)&&(ve2.anc!=ve1.num))
   {
    bool sk=true;
    long l2=0;
    while ((sk)&&(l2<N))
    {
     if (verw[l2].num==ve2.anc)
     {
      length+=ve2.anclen;
      ve2=verw[l2];
      sk=false;
     }
     l2++;
    }
   }
   else if ((ve2.depth==ve1.depth)&&(ve1.num!=ve2.num))
   {
    bool sk1=true,sk2=true;
    long l3=0;
    while ((sk1||sk2)&&(l3<N))
    {
     if (verw[l3].num==ve1.anc)
     {
      length+=ve1.anclen;
      ve1=verw[l3];
      sk1=false;
     }
     if (verw[l3].num==ve2.anc)
     {
      length+=ve2.anclen;
      ve2=verw[l3];
      sk2=false;
     }
     l3++;
    }
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
