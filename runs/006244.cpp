#include <iostream>
#include <map>
#include <vector>
#include <queue>

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

    map<pair<int,int>,int>mp;
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
 typedef pair<int,int> Key;
 unsigned int n=0,m=0, v1=0, v2=0, length=0, p1=0, p2=0;

 cout<<"Vvedite kol-vo vershin: "<<endl;
 cin>>n;
 vec.resize(n);

for(size_t i=0; i<n-1; ++i) {
 cout<<"Vvedite informaciu o rebrax:"<<endl;
 cin>>v1>>v2>>length;
 mp.insert(make_pair(Key(v1,v2),length));
 mp.insert(make_pair(Key(v2,v1),length));
}

cout<<"Vvedite kol-vo vershin dlya poucka:"<<endl;
cin>>m;

for(size_t i=0; i<m; ++i)
{
cout<<"Vershiny:"<<endl;
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
    int top=0;
    int find=p.first;
    map<pair<int,int>, int> m(mp);
    queue<pair<int,int> >que;
    queue<pair<int,int> >temp;
    vec[p.first-1]=0;

map<pair<int,int>, int>::iterator it;

while(top!=p.second)
{
    for(it=m.begin(); it!=m.end(); ++it)
    {
      if(it->first.first==find) {
        vec[it->first.second-1]=vec[it->first.first-1]+it->second;
        que.push(make_pair(it->first.first,it->first.second));
        temp.push(make_pair(it->first.first,it->first.second));
    }
   }
find=que.front().second;
top=que.front().second;
que.pop();

while(!temp.empty())
{
    m.erase(make_pair(temp.front().first,temp.front().second));
    m.erase(make_pair(temp.front().second,temp.front().first));
    temp.pop();
}
}

}

void MyClass::output()
{
vector<int>::iterator i;
cout<<"Resultat:"<<endl;
    for(i=end.begin(); i!=end.end(); ++i) {
    cout<<*i<<endl;
    }
}

int main(int argc, char **argv)
{
    MyClass myclass;
    myclass.input();
    myclass.output();
    return 0;
}

