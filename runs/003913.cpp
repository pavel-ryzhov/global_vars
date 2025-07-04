#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using std::vector;
using std::queue;
using std::stack;
using std::min;

using std::istream;
using std::ostream;
using std::cout;
using std::endl;
using std::cin;
using std::cerr;

struct Query {
  int left_label_;
  int right_label_;

  istream &operator>>(istream &is) {
    return is >> left_label_ >> right_label_;
  }
};

struct Edge {
  int begin_;
  int end_;
  int length_;

  istream &operator>>(istream &is) {
    return is >> begin_ >> end_ >> length_;
  }
  
  ostream &operator<<(ostream &os) const {
    return os << begin_ << " " << end_ << " " << length_;
  }

  Edge(int begin = 0, int end = 0, int length = 0)
      : begin_(begin)
      , end_(end)
      , length_(length)
      {
  }
};

bool EdgeCompareFunction(Edge lhs, Edge rhs) {
  if (lhs.begin_ < rhs.begin_) {
    return true;
  }
  if (lhs.end_ == rhs.end_) {
    return lhs.end_ < rhs.end_;
  }
  return false;
}

struct EdgeBeginCompare : std::binary_function<Edge, Edge, bool> {
  bool operator()(const Edge &lhs, const Edge &rhs) {
    return lhs.begin_ < rhs.begin_;
  }
};

struct SegmentTreeNode {
  int label_;
  int depth_;

  SegmentTreeNode(int label = 0, int depth = 0)
      : label_(label)
      , depth_(depth)
      {
  }

  SegmentTreeNode(const SegmentTreeNode &rhs)
      : label_(rhs.label_)
      , depth_(rhs.depth_)
      {
  }

  SegmentTreeNode operator=(const SegmentTreeNode &rhs) {
    label_ = rhs.label_;
    depth_ = rhs.depth_;
    return *this;
  }

  bool operator<(const SegmentTreeNode &rhs) const {
    return depth_ < rhs.depth_;
  }
};

// ceil of log_2
int log2(int number) {
  int res = 0;
  for (; 1 << res < number; ++res) {
  }
  return res > 0 ? res - 1 : 0;
}

int log_power( int n, int pow ) {
	int res = 1;
	for( ; pow > 0; pow = pow >> 1, n *= n ) {
		if( pow & 1 ) {
			res *= n;
		}
	}
	return res;
}

// Structure for "range minimum queries" (RMQ)
template <typename T>
class SegmentTree {
private:
  vector<T> data_;
  // answers_[i][k] contans answer in range [i, i + 2^k - 1]
  vector<vector<T> > answers_;

public:
  SegmentTree() {
  }

  ~SegmentTree() {
  }

  void InitByVector(const vector<T> &data) {
    data_ = data;
  }

  void PreProcessing() {
    int data_size = data_.size();
    answers_.resize(data_size);
    for (int left_border = 0; left_border < data_size; ++left_border) {
      answers_[left_border].push_back(data_[left_border]);
    }
    for (int k = 1, pow2 = 1; 2 * pow2 < data_.size(); ++k, pow2 *= 2) {
      for (int left_border = 0; left_border < data_size; ++left_border) {
        int right_border = min(left_border + pow2, data_size - 1);
        answers_[left_border].push_back(
          min(answers_[left_border][k - 1], answers_[right_border][k - 1]));
      }
    }
  }

  T GetMin(int left_border, int right_border) const {
    if (left_border > right_border) {
      return GetMin(right_border, left_border);
    }
    int length = log2(right_border - left_border + 1);
    T left_min = answers_[left_border][length];
    T right_min = answers_[right_border - log_power(2, length) + 1][length];
    return min(left_min, right_min);
  }
};

class TreeNode {
private:
  vector<TreeNode*> children;
  TreeNode *parent_;
  int distance_to_parent_;
  int label_; // name of the tree node
  int distance_to_root_;

public:
  TreeNode() 
      : children(vector<TreeNode*>())
      , parent_(NULL)
      , distance_to_parent_(0)
      , label_(0)
      , distance_to_root_(INT_MAX)
      {
  }

  ~TreeNode() {
  }

  vector<TreeNode*>::const_iterator Begin() const {
    return children.begin();
  }

  vector<TreeNode*>::const_iterator End() const {
    return children.end();
  }

  void AddChild(TreeNode *tree_node) {
    children.push_back(tree_node);
  }

  TreeNode *GetParent() const {
    return parent_;
  }

  int GetLabel() const {
    return label_;
  }

  int GetDistanceToParent() const {
    return distance_to_parent_;
  }

  int GetDistanceToRoot() const {
    return distance_to_root_;
  }

  void SetDistanceToRoot(int distance_to_root) {
    distance_to_root_ = distance_to_root;
  }

  void SetLabel(int label) {
    label_ = label;
  }

  void SetParent(TreeNode *tree_node) {
    parent_ = tree_node;
  }

  void SetDistance(int length) {
    distance_to_parent_ = length;
  }
};

class LCATree {
private:
  vector<TreeNode> nodes_;
  int root_;
  SegmentTree<SegmentTreeNode> segment_tree_;
  vector<int> lca_first;

  void AddEdge(int parent_index, int child_index, int edge_length) {
    nodes_[parent_index - 1].AddChild(&nodes_[child_index - 1]);
    nodes_[child_index - 1].SetParent(&nodes_[parent_index - 1]);
    nodes_[child_index - 1].SetDistance(edge_length);
  }

  void _PrintPreOrder(const TreeNode *current_node) const {
    if (current_node != NULL) {
      cout << current_node->GetLabel() << " ";
      for (vector<TreeNode*>::const_iterator it = current_node->Begin()
          ; it != current_node->End()
          ; ++it
          ) {
        _PrintPreOrder(*it);
      }
    }
  }

  void FillEulerTour(vector<SegmentTreeNode> *euler_tour) {
    if (root_ > 0) {
      TreeNode *current_tree_node;
      SegmentTreeNode current_segment_node = SegmentTreeNode(nodes_[root_ - 1].GetLabel(), 0);
      stack<SegmentTreeNode> nodes_to_trip;
      nodes_to_trip.push(current_segment_node);

      vector<bool> used_vertex(nodes_.size() + 1, false);

      while (!nodes_to_trip.empty()) {
        current_segment_node = nodes_to_trip.top();
        nodes_to_trip.pop();

        current_tree_node = &nodes_[current_segment_node.label_ - 1];
        euler_tour->push_back(current_segment_node);
        if (!used_vertex[current_segment_node.label_]) {
          lca_first[current_segment_node.label_ - 1] = euler_tour->size() - 1;
          used_vertex[current_segment_node.label_] = true;
          for (vector<TreeNode*>::const_iterator it = current_tree_node->Begin()
              ; it != current_tree_node->End()
              ; ++it
              ) {
            nodes_to_trip.push(SegmentTreeNode(current_segment_node.label_
              , current_segment_node.depth_)
              );
            nodes_to_trip.push(SegmentTreeNode((*it)->GetLabel()
              , current_segment_node.depth_ + 1)
              );
          }
        }
      }
    }
  }

  void UpdateDistances() {
    if (root_ > 0) {
      queue<TreeNode*> nodes_to_update;
      nodes_to_update.push(&nodes_[root_ - 1]);

      while (!nodes_to_update.empty()) {
        TreeNode *current_node = nodes_to_update.front();
        nodes_to_update.pop();

        if (current_node != NULL) {
          if (current_node->GetParent() != NULL) {
            current_node->SetDistanceToRoot(current_node->GetDistanceToParent() + current_node->GetParent()->GetDistanceToRoot());
          } else {
            current_node->SetDistanceToRoot(0);
          }
          for (vector<TreeNode*>::const_iterator it = current_node->Begin()
              ; it != current_node->End()
              ; ++it
              ) {
            nodes_to_update.push(*it);
          }
        }
      }
    }
  }

public:
  LCATree() : nodes_(vector<TreeNode>()), root_(0) {
  }

  ~LCATree() {
  }

  void InitializeByVectorEdge(const vector<Edge> &edges) {
    nodes_.resize(edges.size() + 1);
    root_ = 1;
    if (edges.size() > 0) {
      root_ = edges[0].begin_;
    }
    for (int index = 0; index < edges.size(); ++index) {
      AddEdge(edges[index].begin_, edges[index].end_, edges[index].length_);
      nodes_[index].SetLabel(index + 1);
    }
    nodes_[nodes_.size() - 1].SetLabel(nodes_.size());

    UpdateDistances();
  }

  void PrintPreOrder() const {
    if (root_ > 0) {
      _PrintPreOrder(&nodes_[root_ - 1]);
    }
    cout << endl;
  }

  void PreProcessing() {
    vector<SegmentTreeNode> euler_tour;
    euler_tour.reserve(2 * nodes_.size() + 1);
    lca_first.resize(nodes_.size(), -1);
    FillEulerTour(&euler_tour);

    segment_tree_.InitByVector(euler_tour);
    segment_tree_.PreProcessing();
  }

  int LCA(int left_label, int right_label) const {
    SegmentTreeNode lca = segment_tree_.GetMin(lca_first[left_label - 1]
      , lca_first[right_label - 1]);
    return lca.label_;
  }

  int GetDistance(int left_label, int right_label) const {
    int lca_label = LCA(left_label, right_label);
    return nodes_[left_label - 1].GetDistanceToRoot()
      + nodes_[right_label - 1].GetDistanceToRoot()
      - 2 * nodes_[lca_label - 1].GetDistanceToRoot();
  }
};

istream &operator>>(istream &is, Edge &edge) {
  return edge.operator>>(is);
}

ostream &operator<<(ostream &os, const Edge &edge) {
  return edge.operator<<(os);
}

istream &operator>>(istream &is, Query &query) {
  return query.operator>>(is);
}


struct ChildNodeIndexWithEdge {
  int child_node_index_;
  Edge edge_;

  ChildNodeIndexWithEdge(int child_node_index = 0, Edge edge = Edge())
      : child_node_index_(child_node_index)
      , edge_(edge) 
      {
  }
};

// add edges from root_node (up to down)
void FillGoodEdge(const vector<vector<ChildNodeIndexWithEdge> > &graph, vector<Edge> *good_edges) {
  vector<bool> used_vertex(graph.size() + 1, false);
  queue<int> nodes_to_trip;
  nodes_to_trip.push(1);

  while (!nodes_to_trip.empty()) {
    int node_index = nodes_to_trip.front();
    nodes_to_trip.pop();

    used_vertex[node_index] = true;
    for (vector<ChildNodeIndexWithEdge>::const_iterator it = graph[node_index - 1].begin()
        ; it != graph[node_index - 1].end()
        ; ++it
        ) {
      if (!used_vertex[(*it).child_node_index_]) {
        good_edges->push_back((*it).edge_);
        nodes_to_trip.push((*it).child_node_index_);
      }
    }
  }
}

void InitTree(LCATree *tree) {
  int tree_size;
  cin >> tree_size;

  if (tree_size < 1) {
    return;
  }

  vector<Edge> edges;
  edges.reserve(2 * (tree_size - 1));

  // graph[parent_node_index][child_index] = child_node_index
  vector<vector<ChildNodeIndexWithEdge> > graph;
  graph.resize(tree_size);

  for (int index = 0; index < tree_size - 1; ++index) {
    Edge current_edge;
    cin >> current_edge;
    Edge reverse_edge = Edge(current_edge.end_, current_edge.begin_, current_edge.length_);
    graph[current_edge.begin_ - 1].push_back(ChildNodeIndexWithEdge(current_edge.end_, current_edge));
    graph[reverse_edge.begin_ - 1].push_back(ChildNodeIndexWithEdge(reverse_edge.end_, reverse_edge));
  }

  vector<Edge> good_edges;
  good_edges.reserve(tree_size - 1);
  FillGoodEdge(graph, &good_edges);

  tree->InitializeByVectorEdge(good_edges);
}

void InitQueries(queue<Query> *queries) {
  int count_query;
  cin >> count_query;

  for (int index = 0; index < count_query; ++index) {
    Query query;
    cin >> query;
    queries->push(query);
  }
}

void RecursionTest();
void StressTest();
void SpeedTest();

int main() {
  LCATree lca_tree;
  queue<Query> queries;

  InitTree(&lca_tree);
  lca_tree.PreProcessing();

  InitQueries(&queries);
  for (; !queries.empty(); queries.pop()) {
    Query query = queries.front();
    printf("%d\n", lca_tree.GetDistance(query.left_label_, query.right_label_));
  }
  return 0;
}

const int kCountTest = 1000;
const int kTreeSize = 80;
const int kCountQuery = 40000;
const int kMaxLengthEdge = 40000;

// Test structure (checked Cartesian tree with random height)

template <typename T>
class CartesianTreeNode {
 private:
  T key_;
  int priority_;

  // added for testing scanner
  int distance_to_parent_;

  // include self-node
  int count_subtree_nodes_;

  CartesianTreeNode *left_;
  CartesianTreeNode *right_;
  CartesianTreeNode *parent_;

 public:
  CartesianTreeNode() 
      : key_(T())
      , priority_(0)
      , count_subtree_nodes_(1)
      , left_(NULL)
      , right_(NULL)
      , parent_(NULL)
      , distance_to_parent_(INT_MAX)
      {
  }

  T GetKey () const {
    return key_;
  }

  void SetKey (T key) {
    key_ = key;
  }

  int GetPriority () const {
    return priority_;
  }

  void SetPriority (int priority) {
    priority_ = priority;
  }

  bool operator < (const CartesianTreeNode &rhs) const {
    return priority_ < rhs.priority_;
  }

  CartesianTreeNode *GetParent () const {
    return parent_;
  }

  void SetLeft (CartesianTreeNode *left) {
    left_ = left;
  }

  CartesianTreeNode *GetRight () const {
    return right_;
  }

  CartesianTreeNode *GetLeft () const {
    return left_;
  }

  void SetRight (CartesianTreeNode *right) {
    right_ = right;
  }

  void SetParent (CartesianTreeNode *parent) {
    parent_ = parent;
  }

  void SetCountSubtreeNodes (int count_subtree_nodes) {
    count_subtree_nodes_ = count_subtree_nodes;
  }

  int GetCountSubtreeNodes () const {
    return count_subtree_nodes_;
  }

  int GetDistanceToParent() const {
    return distance_to_parent_;
  }

  void SetDistanceToParent(int distance) {
    distance_to_parent_ = distance;
  }
};

template <typename T>
class CartesianTree {
 private:
  vector< CartesianTreeNode<T> > nodes_;
  CartesianTreeNode<T> *root_;

  class CartesianTreeIterator {
    friend class CheckCartesianTree;
   private:
    CartesianTreeNode<T> **root_;
    CartesianTreeNode<T> *current_;
    int free_space_index_;
    vector< CartesianTreeNode<T> > *allocated_memory_;

    CartesianTreeNode<T> *AllocateNode() {
      return &( *( allocated_memory_->begin() + free_space_index_++ ) );
    }

   public:
    CartesianTreeIterator (
        CartesianTreeNode<T> **root
        , vector< CartesianTreeNode<T> > *allocated_memory
        )
        : root_(root)
        , current_(*root)
        , free_space_index_(0)
        , allocated_memory_(allocated_memory)
        {
    }

    ~CartesianTreeIterator () {
    }

    void Insert (const CartesianTreeNode<T> &tree_value) {
      if ( *root_ == NULL ) {
        *root_ = AllocateNode();
        current_ = *root_;
        current_->SetKey(tree_value.GetKey());
        current_->SetPriority(tree_value.GetPriority());
      } else {

        // insert new node (search good place in right path)
        int insert_element_priority = tree_value.GetPriority();
        while ( current_ != NULL && current_->GetPriority() > insert_element_priority ) {
          current_ = current_->GetParent();
        }
        if ( current_ == NULL ) {
          current_ = *root_;
          *root_ = AllocateNode();
          (*root_)->SetLeft(current_);
          (*root_)->SetCountSubtreeNodes(current_->GetCountSubtreeNodes() + 1);
          current_->SetParent(*root_);

          // distance
          current_->SetDistanceToParent(rand() % kMaxLengthEdge);

          current_ = *root_;
          current_->SetKey(tree_value.GetKey());
          current_->SetPriority(tree_value.GetPriority());
        } else {
          CartesianTreeNode<T> *new_node = AllocateNode();
          new_node->SetLeft(current_->GetRight());
          new_node->SetParent(current_);

          if (current_->GetRight() != NULL) {
            current_->GetRight()->SetParent(new_node);
          }

          // distance
          new_node->SetDistanceToParent(rand() % kMaxLengthEdge);

          current_->SetRight(new_node);
          current_ = new_node;
          current_->SetKey(tree_value.GetKey());
          current_->SetPriority(tree_value.GetPriority());

          // update count nodes in subtrees from new_node to root node.
          if ( current_->GetLeft() != NULL ) {
            current_->SetCountSubtreeNodes(current_->GetLeft()->GetCountSubtreeNodes() + 1);
          }
          while ( new_node->GetParent() != NULL ) {
            new_node = new_node->GetParent();
            new_node->SetCountSubtreeNodes(new_node->GetCountSubtreeNodes() + 1);
          }
        }
      }
    }
  };

 public:
  class CheckCartesianTree {
   public:
    static void CheckCurrentCountSubtreeValues (CartesianTreeNode<T> *current) {
      if ( current == NULL ) {
        return;
      }

      int count_nodes = 0;
      if ( current->GetLeft() != NULL ) {
        count_nodes += current->GetLeft()->GetCountSubtreeNodes();
      }
      if ( current->GetRight() != NULL ) {
        count_nodes += current->GetRight()->GetCountSubtreeNodes();
      }
      if ( ++count_nodes != current->GetCountSubtreeNodes() ) {
        cout << "problems with node (key,priority,size): ("
          << current->GetKey() << ","
          << current->GetPriority() << ","
          << current->GetCountSubtreeNodes() << ")" << endl;
        exit(1);
      } else {
        /*
        cout << "no problems with node (key,priority,size): ("
          << current->GetKey() << ","
          << current->GetPriority() << ","
          << current->GetCountSubtreeNodes() << ")" << endl;
        //*/
      }

      CheckCurrentCountSubtreeValues(current->GetLeft());
      CheckCurrentCountSubtreeValues(current->GetRight());
    }

    static void CheckCountSubtreeValues (CartesianTree<T> &cartesian_tree) {
      CartesianTreeNode<T> *current = cartesian_tree.root_;
      CheckCurrentCountSubtreeValues(current);
    }
  };

 private:

  template <typename outT, typename R>
  void InOrderOutput (
      CartesianTreeNode<T> *current
      , outT *inorder_output
      , R (CartesianTreeNode<T>::*function)() const
      ) const {

    if ( current == NULL ) {
      return;
    }
    InOrderOutput(current->GetLeft(), inorder_output, function);
    inorder_output->push_back( (current->*function)() );
    InOrderOutput(current->GetRight(), inorder_output, function);
  }

  int GetDepth (CartesianTreeNode<T> *current) const {
    if ( current == NULL ) {
      return 0;
    }
    int left_depth = GetDepth(current->GetLeft());
    int right_depth = GetDepth(current->GetRight());
    int max_depth = left_depth > right_depth ? left_depth : right_depth;
    return max_depth + 1;
  }

  void BuildByExistsNodes (const vector< CartesianTreeNode<T> > &copy_nodes) {
    input_iterator *inserter = Begin();
    for ( typename vector< CartesianTreeNode<T> >::const_iterator it = copy_nodes.begin()
        ; it != copy_nodes.end()
        ; ++it
        ) {

      inserter->Insert(*it);
    }
  }

 public:
  CartesianTree()
      : root_(NULL)
      {
  }

  typedef CartesianTreeIterator input_iterator;

  input_iterator *Begin() {
    input_iterator *new_instance = new input_iterator(&root_, &nodes_);
    return new_instance;
  }

  template <typename keysT>
  void GetInorderKeys (keysT *inorder_keys) const {
    inorder_keys->clear();
    inorder_keys->reserve(nodes_.size());
    InOrderOutput(root_, inorder_keys, &CartesianTreeNode<T>::GetKey);
  }

  template <typename prioritiesT>
  void GetInorderPriorities (prioritiesT *inorder_priorities) const {
    inorder_priorities->clear();
    inorder_priorities->reserve(nodes_.size());
    InOrderOutput(root_, inorder_priorities, &CartesianTreeNode<T>::GetPriority);
  }

  template <typename countNodesT>
  void GetInorderCountSubtreeNodes (countNodesT *inorder_count_nodes) const {
    inorder_count_nodes->clear();
    inorder_count_nodes->reserve(nodes_.size());
    InOrderOutput(root_, inorder_count_nodes, &CartesianTreeNode<T>::GetCountSubtreeNodes);
  }

  // Height of tree, which contains only 1 element = 0!
  int GetMaxHeight () const {
    return GetDepth(root_) - 1;
  }

  template <typename keysT>
  void BuildByKeys (const keysT &keys) {
    int count_nodes = keys.size();
    nodes_.resize(count_nodes);

    vector< CartesianTreeNode<T> > copy_nodes;
    copy_nodes.resize(count_nodes);
    for (int index = 0; index < count_nodes; ++index) {
      copy_nodes.at(index).SetKey(keys.at(index));
      copy_nodes.at(index).SetPriority(rand());
    }

    BuildByExistsNodes(copy_nodes);
  }

 private:
  void SplitLeft (CartesianTreeNode<T> *sub_root
      , int count_nodes_to_cut
      , CartesianTreeNode<T> **left_root
      , CartesianTreeNode<T> **right_root
      ) {

    if ( sub_root == NULL ) {
      left_root = NULL;
      right_root = NULL;
      return;
    } 
    
    int count_left_nodes = sub_root->GetLeft() ? sub_root->GetLeft()->GetCountSubtreeNodes() : 0;
    if ( count_nodes_to_cut < count_left_nodes ) {
      CartesianTreeNode<T> *local_left_root = NULL;
      CartesianTreeNode<T> *local_right_root = NULL;

      int count_right_nodes_with_root = sub_root->GetRight() 
        ? sub_root->GetRight()->GetCountSubtreeNodes() + 1 
        : 1;
      sub_root->SetCountSubtreeNodes(count_right_nodes_with_root);

      SplitLeft(
        sub_root->GetLeft()
        , count_nodes_to_cut
        , &local_left_root
        , &local_right_root
        );
      sub_root->SetLeft(local_right_root);
      int count_nodes_added_right_tree = local_right_root 
        ? local_right_root->GetCountSubtreeNodes() 
        : 0;
      sub_root->SetCountSubtreeNodes(count_right_nodes_with_root + count_nodes_added_right_tree);
      
      *left_root = local_left_root;
      *right_root = sub_root;

    } else if ( count_nodes_to_cut == count_left_nodes ) {
      int count_right_nodes_with_root = sub_root->GetRight() 
        ? sub_root->GetRight()->GetCountSubtreeNodes() + 1
        : 1;
      
      sub_root->SetCountSubtreeNodes(count_right_nodes_with_root);
      *left_root = sub_root->GetLeft();
      *right_root = sub_root;
      sub_root->SetLeft(NULL);

    } else {
      CartesianTreeNode<T> *local_left_root = NULL;
      CartesianTreeNode<T> *local_right_root = NULL;

      int count_left_nodes_with_root = sub_root->GetLeft()
        ? sub_root->GetLeft()->GetCountSubtreeNodes() + 1
        : 1;
      sub_root->SetCountSubtreeNodes(count_left_nodes_with_root);

      SplitLeft(
        sub_root->GetRight()
        , count_nodes_to_cut - count_left_nodes_with_root
        , &local_left_root
        , &local_right_root
        );
      sub_root->SetRight(local_left_root);
      int count_nodes_added_left_tree = local_left_root
        ? local_left_root->GetCountSubtreeNodes()
        : 0;
      sub_root->SetCountSubtreeNodes(count_left_nodes_with_root + count_nodes_added_left_tree);
      
      *left_root = sub_root;
      *right_root = local_right_root;
    }
  }

  void SplitLeft (int count_nodes_to_cut) {
    CartesianTreeNode<T> *left_root = NULL;
    CartesianTreeNode<T> *right_root = NULL;
    SplitLeft(root_, count_nodes_to_cut, &left_root, &right_root);
  }

  void SplitRight (int count_nodes_to_cut) {
    CartesianTreeNode<T> *left_root = NULL;
    CartesianTreeNode<T> *right_root = NULL;

    int count_nodes = nodes_.size();
    SplitLeft(root_, count_nodes - count_nodes_to_cut, &left_root, &right_root);
  }

  void Merge (
      CartesianTreeNode<T> *left_tree
      , CartesianTreeNode<T> *right_tree
      , CartesianTreeNode<T> **root 
      ) {

    if ( left_tree == NULL ) {
      *root = right_tree;
      return;
    }

    if ( right_tree == NULL ) {
      *root = left_tree;
      return;
    }

    if ( left_tree->GetPriority() < right_tree->GetPriority() ) {
      CartesianTreeNode<T> *subtree_root = NULL;
      Merge(left_tree->GetRight(), right_tree, &subtree_root);

      int count_nodes_left_subtree = left_tree->GetLeft()
        ? left_tree->GetLeft()->GetCountSubtreeNodes()
        : 0;
      int count_nodes_right_subtree = subtree_root ? subtree_root->GetCountSubtreeNodes() : 0;
      left_tree->SetCountSubtreeNodes(count_nodes_left_subtree + 1 + count_nodes_right_subtree);
      left_tree->SetRight(subtree_root);
      *root = left_tree;
    } else {
      CartesianTreeNode<T> *subtree_root = NULL;
      Merge(left_tree, right_tree->GetLeft(), &subtree_root);

      int count_nodes_right_subtree = right_tree->GetRight()
        ? right_tree->GetRight()->GetCountSubtreeNodes()
        : 0;
      int count_nodes_left_subtree = subtree_root ? subtree_root->GetCountSubtreeNodes() : 0;
      right_tree->SetCountSubtreeNodes(count_nodes_left_subtree + 1 + count_nodes_right_subtree);
      right_tree->SetLeft(subtree_root);
      *root = right_tree;
    }
  }

  // for testing distances in tree
  void FillVectorEdge(const CartesianTreeNode<T> *current_node, vector<Edge> *edges) const {
    if (current_node != NULL) {
      if (current_node->GetParent() != NULL) {
        edges->push_back(Edge(current_node->GetParent()->GetKey()
          , current_node->GetKey()
          , current_node->GetDistanceToParent()
          ));
      }
      FillVectorEdge(current_node->GetLeft(), edges);
      FillVectorEdge(current_node->GetRight(), edges);
    }
  }

 public:
  void Shift (int left, int right, int shift) {
    CartesianTreeNode<T> *left_root = NULL;
    CartesianTreeNode<T> *middle_root = NULL;
    SplitLeft(root_, left - 1, &left_root, &middle_root);

    CartesianTreeNode<T> *shift_root = NULL;
    CartesianTreeNode<T> *right_root = NULL;
    SplitLeft(middle_root, right - left + 1, &shift_root, &right_root);

    CartesianTreeNode<T> *shift_left_root = NULL;
    CartesianTreeNode<T> *shift_right_root = NULL;
    SplitLeft(shift_root, shift, &shift_left_root, &shift_right_root);

    Merge(shift_right_root, shift_left_root, &shift_root);
    Merge(shift_root, right_root, &middle_root);
    Merge(left_root, middle_root, &root_);
  }

  // for testing distances in tree
  void GetAllEdge(vector<Edge> *edges) const {
    edges->resize(0);
    edges->reserve(nodes_.size());
    FillVectorEdge(root_, edges);
  }
};

// complexity - O(n^3)
void CalculateDistances(const vector<Edge> &edges, vector<vector<int> > *distances) {
  int count_nodes = edges.size() + 1;
  distances->resize(0);
  distances->resize(count_nodes);
  for (int index = 0; index < count_nodes; ++index) {
    (*distances)[index].resize(count_nodes, kMaxLengthEdge * kTreeSize);
    (*distances)[index][index] = 0;
  }

  for (int edge_id = 0; edge_id < edges.size(); ++edge_id) {
    (*distances)[edges[edge_id].begin_ - 1][edges[edge_id].end_ - 1] = edges[edge_id].length_;
    (*distances)[edges[edge_id].end_ - 1][edges[edge_id].begin_ - 1] = edges[edge_id].length_;
  }

  for (int middle = 0; middle < count_nodes; ++middle) {
    for (int left = 0; left < count_nodes; ++left) {
      for (int right = 0; right < count_nodes; ++right) {
        (*distances)[left][right] = min((*distances)[left][right]
          , (*distances)[left][middle] + (*distances)[middle][right]
          );
        (*distances)[right][left] = (*distances)[left][right];
      }
    }
  }
}

// Only tests

void OutputEdges(const vector<Edge> &edges) {
  for (int index = 0; index < edges.size(); ++index) {
    cout << edges[index] << endl;
  }
}

void GenerateGoodEdges(const vector<Edge> &bad_edges, vector<Edge> *good_edges) {
  int tree_size = bad_edges.size() + 1;

  vector<Edge> all_edges;
  all_edges.reserve(2 * (tree_size - 1));

  // graph[parent_node_index][child_index] = child_node_index
  vector<vector<ChildNodeIndexWithEdge> > graph;
  graph.resize(tree_size);

  for (int index = 0; index < tree_size - 1; ++index) {
    Edge current_edge = bad_edges[index];
    Edge reverse_edge = Edge(current_edge.end_, current_edge.begin_, current_edge.length_);
    graph[current_edge.begin_ - 1].push_back(ChildNodeIndexWithEdge(current_edge.end_, current_edge));
    graph[reverse_edge.begin_ - 1].push_back(ChildNodeIndexWithEdge(reverse_edge.end_, reverse_edge));
  }

  good_edges->resize(0);
  good_edges->reserve(tree_size - 1);
  FillGoodEdge(graph, good_edges);
}

void StressTest() {
  vector<int> keys;
  keys.resize(kTreeSize);
  for ( int index = 0; index < kTreeSize; ++index ) {
    keys.at(index) = index + 1;
  }

  vector<Edge> edges;
  vector<vector<int> > distances;
  vector<Edge> good_edges;

  for (int test_id = 0; test_id < kCountTest; ++test_id) {
    CartesianTree<int> cartesian_tree;
    cartesian_tree.BuildByKeys(keys);
    cartesian_tree.GetAllEdge(&edges);

    CalculateDistances(edges, &distances);
    // shuffle edges (make them bad)
    std::random_shuffle(edges.begin(), edges.end());
    GenerateGoodEdges(edges, &good_edges);

    //cout << "count edges (bad, good): " << edges.size() << " " << good_edges.size() << endl;

    LCATree lca_tree;
    lca_tree.InitializeByVectorEdge(good_edges);
    lca_tree.PreProcessing();

    for (int lca_test_id = 0; lca_test_id < kCountQuery; ++lca_test_id) {
      int left = rand() % kTreeSize;
      int right = rand() % kTreeSize;
      if (distances[left][right] != lca_tree.GetDistance(left + 1, right + 1)) {
        cout << "Fault!" << endl;
        OutputEdges(edges);
        cout << "check pair: " << (left + 1) << " " << (right + 1) << endl;
        cout << "Real distance: " << distances[left][right] << endl;
        cout << "Fast distance: " << lca_tree.GetDistance(left + 1, right + 1) << endl;
        return;
      }
    }
    cout << "OK!" << endl;
  }
}

void SpeedTest() {
  vector<int> keys;
  keys.resize(kTreeSize);
  for ( int index = 0; index < kTreeSize; ++index ) {
    keys.at(index) = index + 1;
  }

  vector<Edge> edges;
  vector<vector<int> > distances;
  vector<Edge> good_edges;

  CartesianTree<int> cartesian_tree;
  cartesian_tree.BuildByKeys(keys);
  cartesian_tree.GetAllEdge(&edges);
  std::random_shuffle(edges.begin(), edges.end());

  vector<std::pair<int, int> > queries;
  queries.reserve(kCountQuery);

  for (int lca_test_id = 0; lca_test_id < kCountQuery; ++lca_test_id) {
    int left = rand() % kTreeSize;
    int right = rand() % kTreeSize;
    queries.push_back(std::make_pair(left + 1, right + 1));
  }

  cerr << "Start testing" << endl;
  float time = clock();

  LCATree lca_tree;
  GenerateGoodEdges(edges, &good_edges);
  lca_tree.InitializeByVectorEdge(good_edges);
  lca_tree.PreProcessing();

  for (int lca_test_id = 0; lca_test_id < kCountQuery; ++lca_test_id) {
    printf("%d\n", lca_tree.GetDistance(queries[lca_test_id].first, queries[lca_test_id].second));
  }

  time = clock() - time;
  cerr << "Time: " << (time / CLOCKS_PER_SEC) << "s" << endl;
}

void RecursionTest() {
  vector<Edge> edges;
  vector<Edge> good_edges;
  edges.reserve(kTreeSize - 1);
  for (int index = 0; index + 1< kTreeSize; ++index) {
    edges.push_back(Edge(kTreeSize - index, kTreeSize - index - 1, kTreeSize - index - 1));
  }

  vector<std::pair<int, int> > queries;
  queries.reserve(kCountQuery);

  for (int lca_test_id = 0; lca_test_id < kCountQuery; ++lca_test_id) {
    /*
    if (lca_test_id + 2 < kTreeSize) {
      queries.push_back(std::make_pair(1, lca_test_id + 2));
    } else {
      queries.push_back(std::make_pair(lca_test_id, lca_test_id));
    }
    */
    queries.push_back(std::make_pair(1, kTreeSize));
  }

  float time = clock();

  LCATree lca_tree;
  GenerateGoodEdges(edges, &good_edges);
  lca_tree.InitializeByVectorEdge(good_edges);
  lca_tree.PreProcessing();

  for (int lca_test_id = 0; lca_test_id < kCountQuery; ++lca_test_id) {
    int distance = lca_tree.GetDistance(queries[lca_test_id].first, queries[lca_test_id].second);
    /*
    if (lca_test_id + 2 < kTreeSize) {
      if (distance != (lca_test_id + 1) * (lca_test_id + 2) / 2) {
        printf("%d\n", distance);
        cerr << "need: " << ((lca_test_id + 1) * (lca_test_id + 2) / 2) << endl;
        break;
      }
    } else {
      if (distance != 0) {
        printf("%d\n", distance);
        cerr << "need: " << 0 << endl;
        break;
      }
    }
    */
    printf("%d\n", distance);
  }

  time = clock() - time;
  cerr << "Time: " << (time / CLOCKS_PER_SEC) << "s" << endl;
}