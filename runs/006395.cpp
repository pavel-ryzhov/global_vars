#include <iostream>
#include <vector>

using namespace std;

class CNode
{
  private:
     int length;     // длина ребра
     int i;          // номер вершины
     CNode *parent;  // родительский узел
  public:
     CNode(int i,int length=0,CNode* parent=NULL)
     {
        this->i=i;
        this->length=length;
        this->parent=parent;
     }
     int GetLength(void) { return length; }
     void SetLength(int length) { this->length=length; }

     int GetI(void) { return i; }
     void SetI(int i) { this->i=i; }

     CNode* GetParent(void) { return parent; }
     void SetParent(CNode* parent) { this->parent=parent; }

     void GetFullPath(int k,vector<int> &kpath);
}; // CNode

class CNodes
{
  private:
     int n; // число вершин
     CNode **node;
  public:
     CNodes(int n)
     {
        this->n=n;
        node=new CNode* [n];
        for(int i=0;i<n;i++)
        {
           node[i]=NULL;
           node[i]=new CNode(i);
        } /* i */
     }
     ~CNodes()
     {
        for(int i=0;i<n;i++)
           if(node[i]!=NULL)
              delete node[i];
        delete[] node;
     }
     CNode** GetNodes() { return node; }
     void GetFullPath(int k,vector<int> &kpath);
     unsigned long GetLength(vector<int> &apath,vector<int> &bpath);
}; // CNodes

// --------------------------------------------------------------------------

// Получение прямой ветви от ребра k до вершины графа
void CNodes::GetFullPath(int k,vector<int> &kpath)
{    int i;
     CNode *nd=node[k];
     /**********************************************************************/
     kpath.clear();
     while(nd!=NULL)
     {
        i=nd->GetI();
        kpath.push_back(i);
        //cout<<i+1<<" ";
        nd=nd->GetParent();
     }
} /* CNodes::GetFullPath */
/***************************************************************************/

unsigned long CNodes::GetLength(vector<int> &apath,vector<int> &bpath)
{    vector<int> *minArray,*maxArray;
     unsigned int i,minSize,maxSize;
     unsigned long length;
     int k;
     /**********************************************************************/
     minArray=&apath; maxArray=&bpath;
     if(apath.size()>bpath.size())
     {
        minArray=&bpath; maxArray=&apath;
     }
     minSize=minArray->size(); maxSize=maxArray->size();

     // расчет кратчайшей длины перехода между вершинами
     length=0;
     for(i=0;i<maxSize-minSize;i++)
        length+=node[(*maxArray)[i]]->GetLength();
     k=0;
     while((*maxArray)[i+k]!=(*minArray)[k])
     {
        length+=node[(*maxArray)[i+k]]->GetLength();
        length+=node[(*minArray)[k]]->GetLength();
        k++;
     }
     return length;
} /* CNodes::GetLength */
/***************************************************************************/

int main()
{    unsigned int i;
     unsigned int a,b;          // текущий запрос (номера вершин)
     unsigned int n,m;          // n - число вершин, m - число запросов
	unsigned long *length;     // конечная длина перехода в графе
     CNodes *nodes=NULL;        // граф
     vector<int> apath,bpath;  
     // --- files ---
     /**********************************************************************/
     cin>>n;
     nodes=new CNodes(n);
     if(nodes!=NULL)
     {
        // установление связей между вершинами
        for(i=0;i<n-1;i++)
        {
		 int parent,node,value,temp;
           cin>>node>>parent>>value;
           parent--; node--;

           if(nodes->GetNodes()[node]->GetParent()!=NULL)
           {
              temp=node;
              node=parent;
              parent=temp;
           }

           nodes->GetNodes()[node]->SetParent(nodes->GetNodes()[parent]);
           nodes->GetNodes()[node]->SetLength(value);
           nodes->GetNodes()[node]->SetI(node);
        } /* i */

        // обработка запросов
        cin>>m;
        length=new unsigned long[m];
        for(i=0;i<m;i++)
        {
           cin>>a>>b;
           a--; b--;
           apath.clear(); bpath.clear();
           nodes->GetFullPath(a,apath);
           nodes->GetFullPath(b,bpath);
           length[i]=nodes->GetLength(apath,bpath);
        } /* i */

        for(i=0;i<m;i++)
           cout<<length[i]<<endl;

        delete[] length;
        delete nodes;
     } // if(nodes!=NULL)
     else cout<<"Out of memory!";
     return 0;
} /* main */
/***************************************************************************/
