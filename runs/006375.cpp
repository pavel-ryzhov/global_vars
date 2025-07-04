#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <cstdlib>
#include <algorithm>

using namespace std;

template <typename T1, typename T2, typename T3>
class pair3d
{
  public:
  pair3d(): first(T1()), second(T2()), third(T3()) {}
  pair3d(const T1 &t1, const T2 &t2, const T3 &t3): first(t1), second(t2), third(t3) {}
  ~pair3d(){}
  T1 first;
  T2 second;
  T3 third;
};

template <typename T1, typename T2, typename T3, typename T4>
class pair4d
{
  public:
  pair4d(): first(T1()), second(T2()), third(T3(), fourth(T4())) {}
  pair4d(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4): first(t1), second(t2), third(t3), fourth(t4) {}
  ~pair4d(){}
  friend  bool operator< (const pair4d &a, const pair4d &b) {return a.first < b.first;}
  T1 first;
  T2 second;
  T3 third;
  T4 fourth;
};
typedef pair4d<int, int, int, int> Value4D;
typedef pair3d<int, int, int> Value3D;
class MyClass
{
    public:

    MyClass();
    ~MyClass();

    void input();
    void output();
    void make_tree();
    void find_algorithm();

    private:

    multimap<int, pair<int,int> >mp;
    vector<Value4D>vec;
    queue<pair<int,int> >qu;
    vector<int>end;
};

MyClass::MyClass()
{
}

MyClass::~MyClass()
{
}

void MyClass::input()
{
 typedef pair<int,int> Value;
 unsigned int n=0,m=0, v1=0, v2=0, length=0, p1=0, p2=0;
 cin>>n;

for(size_t i=0; i<n-1; ++i) {
 cin>>v1>>v2>>length;
 mp.insert(make_pair(v1,Value(v2,length)));
 mp.insert(make_pair(v2,Value(v1,length)));
}

cin>>m;

for(size_t i=0; i<m; ++i)
{
cin>>p1>>p2;
qu.push(make_pair(p1,p2));
}

}

void MyClass::make_tree()
{
    multimap<int, pair<int,int> >m(mp);
    queue<Value3D>q;
    multimap<int,pair<int,int> >::iterator beg,end;
    int temp1=0, temp2=0;
    q.push(Value3D(1,1,0));
    vec.push_back(Value4D(1,0,0,0));

    while(!q.empty()) {

    beg=m.lower_bound(q.front().second);
    end=m.upper_bound(q.front().second);

    if(beg!=end) {
        while(beg!=end) {
        if(beg->first!=temp1 || beg->second.first!=temp2) {
        q.push(Value3D(beg->first,beg->second.first,q.front().third+1));
        vec.push_back(Value4D(beg->second.first,beg->first,beg->second.second,q.front().third+1));
        }
        ++beg;
        }
    }
    q.pop();
    if(!q.empty()) {
    temp1=q.front().second;
    temp2=q.front().first; }
    }
}

void MyClass::find_algorithm()
{

unsigned int length=0, level1=0, level2=0, sum1=0, sum2=0, prev1=0, prev2=0, i=0, j=0;

sort(vec.begin(),vec.end());

while(!qu.empty()) {

i=qu.front().first-1;
j=qu.front().second-1;

prev1=vec[i].second;
prev2=vec[j].second;

while(true) {

level1=vec[i].fourth;
level2=vec[j].fourth;

if(level1>level2){
while(level1!=level2) {
sum1+=vec[i].third;
i=vec[i].second-1;
prev1=vec[i].second;
level1=vec[i].fourth;
}
} else if(level1<level2){
while(level2!=level1) {
sum2+=vec[j].third;
j=vec[j].second-1;
prev2=vec[j].second;
level2=vec[j].fourth;

}
}

if(level1==level2) {
if(i==j){
break;
} else
if(prev1==prev2) {
sum1+=vec[i].third;
sum2+=vec[j].third;
break;
} else {
sum1+=vec[i].third;
sum2+=vec[j].third;

i=vec[i].second-1;
prev1=vec[i].second;
level1=vec[i].fourth;

j=vec[j].second-1;
prev2=vec[j].second;
level2=vec[j].fourth;
}
}

}

length=sum1+sum2;
end.push_back(length);
sum1=0; sum2=0;
length=0;

   qu.pop();
}

}

void MyClass::output()
{
    if(!end.empty()) {
    vector<int>::iterator i;
    for(i=end.begin(); i!=end.end(); ++i) {
    cout<<*i<<endl;
    }
    } else {exit(1);}
}

int main(int argc, char **argv)
{
    MyClass myclass;
    myclass.input();
    myclass.make_tree();
    myclass.find_algorithm();
    myclass.output();
    return 0;
}

