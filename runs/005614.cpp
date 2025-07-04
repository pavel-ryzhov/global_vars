#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <stack>
#include <algorithm>

//#include <fstream>

class Node {
public:
  Node(int vertex, int distance): vertex_(vertex), distance_(distance), visible_(false) {}

  int vertex() const {return vertex_;}
  int distance() const {return distance_;}
  void set_visible(bool value) {visible_ = value;}
  bool visible() const {return visible_;}

private:
  int vertex_;
  int distance_;
  bool visible_;
};

Node* process_node(std::stack<Node *>& st, std::list<Node *> Adj)
{
  if (Adj.size() == 0) {
    return 0;
  }
  else {
    std::list<Node *>::iterator it = Adj.begin();
    while (it != Adj.end()) {
      if (!(*it)->visible()) {
        (*it)->set_visible(true);
        st.push(*it);
        return st.top();
      }
      else
        it++;
    }
    return 0;
  }
}

void do_euler(std::vector<int>& E, std::vector<int>& L, std::vector<int>& R, std::vector<std::list<Node *> >& Gr)
{
  int start_vertex = 0;
  std::vector< std::list<Node *> >::iterator it = Gr.begin();
  while (it != Gr.end()) {
    if ((*it).size() == 0) {
      start_vertex++;
      it++;
    }
    else
      break;
  }
  Node *node_num = new Node(start_vertex, 0);
  Node* current_vertex;
  std::stack<Node *> st;
  int level = 0;

  E[0] = node_num->vertex();
  L[0] = level;
  R[0] = 0;
  st.push(node_num);
  for (unsigned int step = 1; step < E.size(); step++) {
    current_vertex = process_node(st, Gr[node_num->vertex()]);
    if (current_vertex != 0) {
      E[step] = current_vertex->vertex();
      L[step] = current_vertex->distance();
      R[current_vertex->vertex()] = step;
      node_num = current_vertex;
    }
    else {
      node_num = st.top();
      L[step] = -node_num->distance();
      st.pop();
      node_num = st.top();
      E[step] = node_num->vertex();
    }
  }
}

int distance(std::vector<int>& E, std::vector<int>& D, std::vector<int>& R, int left, int right)
{
  int distance = 0; 
  int lca_idx = left;
  int new_left, new_right;
  
  if (left > right)
    std::swap(left, right);

  for (int E_idx = left; E_idx <= right; E_idx++) {
    if (E[lca_idx] > E[E_idx])
      lca_idx = E_idx;
  }

  new_left = R[E[lca_idx]];
  new_right = R[E[left]];
  if (left != lca_idx) {
  if (new_left > new_right)
    std::swap(new_left, new_right);
  if (new_left != lca_idx)
    for (int D_idx = new_left + 1; D_idx <= new_right; D_idx++)
      distance += D[D_idx];
  }
  if (right != lca_idx) {
  new_right = R[E[right]];
  for (int D_idx = new_left + 1; D_idx <= new_right; D_idx++)
    distance += D[D_idx];
  }
  return distance;
}

int main(int argc, char *argv[])
{
  std::string str;
  int N;    // Число вершин
  int M;    // Число пар вершин по которым ищем расстояния
  int root_vertex, to_vertex, weight;

//  std::ifstream file(argv[1]);
  std::getline(std::cin, str);
//  std::getline(file, str);
  N = std::atoi(str.c_str());


  std::vector< std::list<Node *> > G(N);
  std::vector<int> E(2 * N - 1);
  std::vector<int> L(2 * N - 1);
  std::vector<int> R(N);


  for (int i = 0; i < N - 1; i++) {
    std::cin >> root_vertex;
    std::cin >> to_vertex;
    std::cin >> weight;
//    file >> root_vertex;
//    file >> to_vertex;
//   file >> weight;
    G[root_vertex - 1].push_back(new Node(to_vertex - 1, weight));
  }

  // Строим необходимые массивы для поиска наименьшего общего предка
  do_euler(E, L, R, G);

//  file >> M;
  std::cin >> M;
  int u, v;
  std::vector<int> D(M);
  for (int i = 0; i < M; i++) {
    std::cin >> u;
    std::cin >> v;
//    file >> u;
//    file >> v;
    if (u > v)
      std::swap(u, v);
    D[i] = distance(E, L, R, R[u - 1], R[v - 1]);
  }
  for (std::vector<int>::const_iterator it = D.begin(); it != D.end(); it++)
    std::cout << *it << '\n';
  return 0;
}