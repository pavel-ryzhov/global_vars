#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;
          // Node and forward declaration because g++ does
          // not understand nested classes.
class word;
class AvlNode;
class AvlTree;
class dict;

bool my_less(const pair<string,int> & a, const pair<string,int> & b){
  if(a.second != b.second)
    return a.second > b.second;
  else
    return a.first < b.first;
}

char let2dig(const char &a){
  switch(a){
  case 'a':
  case 'b':
  case 'c':
    return '2';
    break;
  case 'd':
  case 'e':
  case 'f':
    return '3';
    break;
  case 'g':
  case 'h':
  case 'i':
    return '4';
    break;
  case 'j':
  case 'k':
  case 'l':
    return '5';
    break;
  case 'm':
  case 'n':
  case 'o':
    return '6';
    break;
  case 'p':
  case 'q':
  case 'r':
  case 's':
    return '7';
    break;
  case 't':
  case 'u':
  case 'v':
    return '8';
    break;
  case 'w':
  case 'x':
  case 'y':
  case 'z':
    return '9';
    break;
  }
}


class word{
private:
  vector<pair<string,int> > data;
  void sort(const pair<string,int> in);
public:
  void sort( );
  void insert(const pair<string,int> & in);
  void print_mass();
  word(const pair<string,int> & in);
  word( const word & in) : data( in.data ) { }
  friend class dict;
};
/*
  void insert(const pair<string,int> &in){
  data.push_back(in);
  std::sort(data.begin(),data.end(),my_less);
  }
*/

void word::print_mass(){
  for(int i = 0; i < data.size(); i++)
    cout<<data[i].first<<" -- "<<data[i].second<<"     ";
  cout<<endl;
}
  
void word::sort( ){
  std::sort(data.begin(), data.end(), my_less);
}
  
void word::sort(const pair<string,int>   in){
  vector<pair<string,int> >::iterator it0=find(data.begin(),data.end(),in),it1=data.begin(),it2=it1+int((it0-it1)/2);
  data.erase(it0);
  if(it0 - 1 == data.begin()){
    (*it1).second <= in.second ? data.insert(it1,in):data.insert(it0,in);
    return;
  }
  while(it0-it1>1){
    if((*it2).second <= in.second && (*(it2-1)).second > in.second){
      data.insert(it2,in);
      return;
    }
    if((*it2).second > in.second){
      it1 = it2;
      it2 = it1 + (int)((it0 - it1) / 2);
    }
    if((*(it2-1)).second<=in.second){
      it0 = it2;
      it2 = it1 + (int)((it0 - it1) / 2);
    }
  }
  (*it1).second <= in.second ? data.insert(it1,in):data.insert(it0,in);
  return;
}

void word::insert( const pair<string,int> & in ){
  data.push_back(in);
}

word::word( const pair<string,int> & in ){
  data.push_back( in );
}

class AvlNode{
  string element;
  word *data;
  AvlNode *left;
  AvlNode *right;
  int height;
  
  AvlNode( const string & theElement, const pair<string,int> & d, AvlNode *lt, AvlNode *rt, int h = 0 ):
    element( theElement ), left( lt ), right( rt ), height( h ) {data = new word(d);}
  
  AvlNode( const string & theElement, word * & d, AvlNode *lt, AvlNode *rt, int h = 0 ): element( theElement ), data( d ), left( lt ), right( rt ), height( h ) { }
  
  void insert( const pair<string,int> & d);
  
  friend class AvlTree;
};

void AvlNode::insert( const pair<string,int> & d ){
  data->insert( d );
}
		
		
        // AvlTree class
        //
        // CONSTRUCTION: with ITEM_NOT_FOUND object used to signal failed finds
        //
        // ******************PUBLIC OPERATIONS*********************
        // void insert( x )       --> Insert x
        // void remove( x )       --> Remove x (unimplemented)
        // Comparable find( x )   --> Return item that matches x
        // Comparable findMin( )  --> Return smallest item
        // Comparable findMax( )  --> Return largest item
        // boolean isEmpty( )     --> Return true if empty; else false
        // void makeEmpty( )      --> Remove all items
        // void printTree( )      --> Print tree in sorted order

class AvlTree{
public:
  explicit AvlTree( );
  AvlTree( const AvlTree & rhs );
  ~AvlTree( );
  
//            const string & findMin( ) const;		//
//            const string & findMax( ) const;		//
  word * find( const string & x )const;
  bool isEmpty( ) const;
  void printTree( ) const;
  
  void makeEmpty( );
  void insert( const string & x , const pair<string, int> & d);
  void remove( const string & x );
  void sort( );
  
  const AvlTree & operator=( const AvlTree & rhs );
  
private:
  AvlNode *root;

  word * elementAt( AvlNode *t )const;

  void sort( AvlNode * t ) const;
  void insert( const string & x, const pair<string,int> & d, AvlNode * & t ) const;
  //            AvlNode * findMin( AvlNode *t ) const;	//
//            AvlNode * findMax( AvlNode *t ) const;	//
  AvlNode * find( const string & x, AvlNode *t )const;
  void makeEmpty( AvlNode * & t ) const;
  void printTree( AvlNode *t ) const;
  AvlNode * clone( AvlNode * t ) const;
  
  // Avl manipulations
  int height( AvlNode * t ) const;
  int max( int lhs, int rhs ) const;
  void rotateWithLeftChild( AvlNode * & k2 ) const;
  void rotateWithRightChild( AvlNode * & k1 ) const;
  void doubleWithLeftChild( AvlNode * & k3 ) const;
  void doubleWithRightChild( AvlNode * & k1 ) const;
};


		
    /**
     * Implements an unbalanced Avl search tree.
     * Note that all "matching" is based on the compares method.
     * @author Mark Allen Weiss
     */
        /**
         * Construct the tree.
         */
AvlTree::AvlTree( ) : root( NULL ) { }

        /**
         * Copy constructor.
         */
AvlTree::AvlTree( const AvlTree & rhs ) : root( NULL ){
  *this = rhs;
}

void AvlTree::sort ( ){
  sort( root );
}

void AvlTree::sort( AvlNode * t )const{
  if(t != NULL){
    t->data->sort();
    sort( t->left );
    sort( t->right );
  }
}
		
        /**
         * Destructor for the tree.
         */

AvlTree::~AvlTree( ){
  makeEmpty( );
}

        /**
         * Insert x into the tree; duplicates are ignored.
         */

void AvlTree::insert( const string & x, const pair<string,int> & d ){
  //  cout<<"x -- "<<x<<endl<<"d -- "<<d.first<<"  "<<d.second<<endl;
  //  if(root == NULL)
  //    cout<<"NULL"<<endl;
  insert( x, d, root );
}

        /**
         * Remove x from the tree. Nothing is done if x is not found.
         */

void AvlTree::remove( const string & x ){
  cout << "Sorry, remove unimplemented; " << x << " still present" << endl;
}

        /**
         * Find the smallest item in the tree.
         * Return smallest item or ITEM_NOT_FOUND if empty.
         */

		 /*
        const string & AvlTree::findMin( ) const
        {
            return elementAt( findMin( root ) );
        }
		*/

        /**
         * Find the largest item in the tree.
         * Return the largest item of ITEM_NOT_FOUND if empty.
         */

		 /*
        const string & AvlTree::findMax( ) const
        {
            return elementAt( findMax( root ) );
        }
		*/

        /**
         * Find item x in the tree.
         * Return the matching item or ITEM_NOT_FOUND if not found.
         */

		 
word * AvlTree::find( const string & x )const{
  return elementAt( find( x, root ) );
}
		

        /**
         * Make the tree logically empty.
         */

void AvlTree::makeEmpty( ){
  makeEmpty( root );
}

        /**
         * Test if the tree is logically empty.
         * Return true if empty, false otherwise.
         */

bool AvlTree::isEmpty( ) const{
  return root == NULL;
}

        /**
         * Print the tree contents in sorted order.
         */


void AvlTree::printTree( ) const
{
  if( isEmpty( ) )
    cout << "Empty tree" << endl;
  else
    printTree( root );
}

		
        /**
         * Deep copy.
         */

const AvlTree & AvlTree::operator=( const AvlTree & rhs ){
  if( this != &rhs ){
    makeEmpty( );
    root = clone( rhs.root );
  }
  return *this;
}

        /**
         * Internal method to get element field in node t.
         * Return the element field or ITEM_NOT_FOUND if t is NULL.
         */

word * AvlTree::elementAt( AvlNode *t )const{
  if( t == NULL )
    return NULL;
  else
    return t->data;
}

        /**
         * Internal method to insert into a subtree.
         * x is the item to insert.
         * t is the node that roots the tree.
         */

void AvlTree::insert( const string & x, const pair<string, int> & d, AvlNode * & t ) const{
  if( t == NULL ){
    //    cout<<"###"<<endl;
    t = new AvlNode( x, d, NULL, NULL );}
  else if( x < t->element ){
    insert( x, d, t->left );
    if( height( t->left ) - height( t->right ) == 2 )
      if( x < t->left->element )
	rotateWithLeftChild( t );
      else
	doubleWithLeftChild( t );
  }
  else if( t->element < x ){
    insert( x, d, t->right );
    if( height( t->right ) - height( t->left ) == 2 )
      if( t->right->element < x )
	rotateWithRightChild( t );
      else
	doubleWithRightChild( t );
  }
  else
    t->insert(d);  // Duplicate; do nothing
  t->height = max( height( t->left ), height( t->right ) ) + 1;
}

        /**
         * Internal method to find the smallest item in a subtree t.
         * Return node containing the smallest item.
         */

		 /*
        AvlNode * AvlTree::findMin( AvlNode *t ) const
        {
            if( t == NULL)
                return t;

            while( t->left != NULL )
                t = t->left;
            return t;
        }
		*/

        /**
         * Internal method to find the largest item in a subtree t.
         * Return node containing the largest item.
         */

		 /*
        AvlNode * AvlTree::findMax( AvlNode *t ) const
        {
            if( t == NULL )
                return t;

            while( t->right != NULL )
                t = t->right;
            return t;
        }
		*/
		
        /**
         * Internal method to find an item in a subtree.
         * x is item to search for.
         * t is the node that roots the tree.
         * Return node containing the matched item.
         */

AvlNode * AvlTree::find( const string & x, AvlNode *t )const{
  while( t != NULL )
//		cout<<endl<<t->element<<endl;
    if( x < t->element )
      t = t->left;
    else if( t->element < x )
      t = t->right;
    else
      return t;    // Match
  
  return NULL;   // No match
}

        /**
         * Internal method to make subtree empty.
         */

void AvlTree::makeEmpty( AvlNode * & t ) const{
  if( t != NULL ){
    makeEmpty( t->left );
    makeEmpty( t->right );
    delete t;
  }
  t = NULL;
}

        /**
         * Internal method to clone subtree.
         */

AvlNode * AvlTree::clone( AvlNode * t ) const{
  if( t == NULL )
    return NULL;
  else
    return new AvlNode( t->element, t->data, clone( t->left ), clone( t->right ), t->height );
}

        /**
         * Return the height of node t or -1 if NULL.
         */

int AvlTree::height( AvlNode *t ) const{
  return t == NULL ? -1 : t->height;
}

        /**
         * Return maximum of lhs and rhs.
         */

int AvlTree::max( int lhs, int rhs ) const{
  return lhs > rhs ? lhs : rhs;
}

        /**
         * Rotate binary tree node with left child.
         * For AVL trees, this is a single rotation for case 1.
         * Update heights, then set new root.
         */

void AvlTree::rotateWithLeftChild( AvlNode * & k2 ) const{
  AvlNode *k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;
  k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
  k1->height = max( height( k1->left ), k2->height ) + 1;
  k2 = k1;
}

        /**
         * Rotate binary tree node with right child.
         * For AVL trees, this is a single rotation for case 4.
         * Update heights, then set new root.
         */

void AvlTree::rotateWithRightChild( AvlNode * & k1 ) const{
  AvlNode *k2 = k1->right;
  k1->right = k2->left;
  k2->left = k1;
  k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
  k2->height = max( height( k2->right ), k1->height ) + 1;
  k1 = k2;
}

        /**
         * Double rotate binary tree node: first left child.
         * with its right child; then node k3 with new left child.
         * For AVL trees, this is a double rotation for case 2.
         * Update heights, then set new root.
         */

void AvlTree::doubleWithLeftChild( AvlNode * & k3 ) const{
  rotateWithRightChild( k3->left );
  rotateWithLeftChild( k3 );
}

        /**
         * Double rotate binary tree node: first right child.
         * with its left child; then node k1 with new right child.
         * For AVL trees, this is a double rotation for case 3.
         * Update heights, then set new root.
         */

void AvlTree::doubleWithRightChild( AvlNode * & k1 ) const{
  rotateWithLeftChild( k1->right );
  rotateWithRightChild( k1 );
}

        /**
         * Internal method to print a subtree in sorted order.
         * t points to the node that roots the tree.
         */

		 

void AvlTree::printTree( AvlNode *t ) const{
  if( t != NULL ){
    printTree( t->left );
    cout << t->element << endl;
    t->data->print_mass();
    printTree( t->right );
  }
}

class dict{
private:
  AvlTree * data;
public:
  string __1(const int & in);
  void insert(const string & in,const int & freq);
  void sort();
  string decript(const string & in) const;
  void print() const;
  dict(){data=new AvlTree;}
};

string dict::__1(const int & in){
  switch (in){
  case 0:
    return ".";
    break;
  case 1:
    return ",";
    break;
  case 2:
    return "?";
    break;
  }
}

void dict::insert(const string & in,const int & freq){
  string key;
  for(int i=0;i<in.length(); i++)
    key+=let2dig(in[i]);
  //  cout<<"@@@"<<endl;
  data->insert(key, pair<string,int>(in,freq));
}

void dict::sort(){
  data->sort();	
}

string dict::decript( const string & in ) const{
	/*
	cout<<endl<<endl;
	print();
	cout<<endl;
	*/
  size_t pos_star = in.find('*');
  word * prom;
  string pr;
  int p;
  if(pos_star != string::npos){
    //   cout<<endl<<in.substr(0, pos_star)<<endl;
    p=in.length()-pos_star;
    prom = data->find(in.substr(0, pos_star));
    //    prom->print_mass();
    pr = prom->data[p].first;
    prom->data[p].second++;
    //   cout<<endl<<"###   "<<(prom->data[p].second)<<endl;
    prom->sort(prom->data[p]);
    return pr;
    
  }
  else{
    prom = data->find(in);
    prom->data[0].second++;
    return prom->data[0].first;
  }
}

void dict::print() const{
  data->printTree();
}

            // Test program
int main(){
  int n,j;
  string prom;
  //  char prom1[100000];
  dict base_;
  cin>>n;
  for(int i = 0; i < n; i++){
    cin>>prom>>j;
    base_.insert(prom,j);
  }
  base_.sort();
  // base_.print();
  getline(cin,prom);
  getline(cin,prom);
  for(int i = 0; i < prom.length(); i++){
    if(prom[i] != ' ' && prom[i] != '1'){
      for(j = i + 1; j < prom.length(); j++)
	if(prom[j] == ' ' || prom[j] == '1')
	  break;
      //      cout<<prom.substr(i, j - i-1)<<endl;
      cout<<base_.decript(prom.substr(i, j - i));
      i = j - 1;
    }
    if(prom[i] == '1'){
      for(j = i + 1; j < prom.length(); j++)
	if(prom[j] != '*')
	  break;
      cout<<base_.__1( j - i - 1);
      i = j - 1;
    }
    if(prom[i] == ' ')
      cout<<' ';
  }
  cout<<endl;


  return 0;
}
