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
int main()
{
 long N,pairN,pol;
 std::cin>>N;
 vw *verw=new vw[N];
 verw[0].num=1;
 verw[0].anc=1;
 verw[0].anclen=0;
 verw[0].depth=0;
 for (long i=1;i<N;i++)
 {
  std::cin>>verw[i].anc>>verw[i].num>>verw[i].anclen;
  if (verw[i].anc>verw[i].num)
  {
   pol=verw[i].anc;
   verw[i].anc=verw[i].num;
   verw[i].num=pol; 
  } 
  for(long j=0;j<i;j++)
  {
   if (verw[j].num==verw[i].anc)
   {
    verw[i].depth=verw[j].depth+1;
   }
  }
 }
 std::cin>>pairN;
 pr *pair=new pr[pairN];
 for (long i=0;i<pairN;i++)
 {
  std::cin>>pair[i].v1>>pair[i].v2;
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
     std::cout<<length<<endl;
     poisk=false;
    }
  }
 }
}
