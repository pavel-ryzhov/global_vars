#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <cstdlib>

using namespace std;

class MyClass
{
    public:

    MyClass();
    ~MyClass();

    void input();
    void output();

    private:

    void find_algorithm(pair<int, int> &p);

    multimap<int,pair<int,int> >mp;
    vector<int>vec;
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
 vec.resize(n);

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

while(!qu.empty()) {
find_algorithm(qu.front());
end.push_back(vec[qu.front().second-1]);
qu.pop();
}
}

void MyClass::find_algorithm(pair<int,int>& p)
{
    int init=p.first, find=p.second;
    int tfirst=0;
    multimap<int,pair<int,int> >m(mp);
    queue<pair<int,int> >que;
    vec[init-1]=0;
    multimap<int,pair<int,int> >::iterator begit,endit;

while(init!=find)
{
begit=m.find(init);
if(begit!=m.end()) {
tfirst=begit->first;
while(tfirst==begit->first) {
vec[begit->second.first-1]=vec[begit->first-1]+begit->second.second;
que.push(make_pair(begit->first,begit->second.first));
m.erase(begit++);
if(begit->first==m.end()->first && begit->second.first==m.end()->second.first) {
break;
}

}
}
init=que.front().second;
que.pop();
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
    myclass.output();
    return 0;
}

