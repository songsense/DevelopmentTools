//
//  Tools.h
//  CrackingCodingInterview
//
//  Created by 宋思明 on 6/29/13.
//  Copyright (c) 2013 宋思明. All rights reserved.
//

#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <queue>
#include <unordered_set>
#include <unordered_map>


using namespace std;

struct TrieNode {
private:
  char c;
  string s;
  vector<TrieNode *> next;
  bool isWord;
  bool hasChild;
  TrieNode();
public:
  ~TrieNode();
  TrieNode(const char &cc, const string &ss, const bool &iw, const bool &ic) : c(cc), s(ss), next(vector<TrieNode*>(26, nullptr)), isWord(iw), hasChild(ic) {}
  TrieNode(const TrieNode &t) : c(t.c), s(t.s), next(t.next), isWord(t.isWord), hasChild(t.hasChild) {}
  TrieNode & operator = (const TrieNode &t) {
    if (this == &t)
      return *this;
    this->c = t.c;
    this->s = t.s;
    this->next = t.next;
    this->isWord = t.isWord;
    this->hasChild = t.hasChild;
    return *this;
  }
  TrieNode *GetNextNode (const char &character);
  TrieNode *SetNextNode (const char &character, TrieNode *node) {next[character - 97] = node; return node;};
  void SetNodeIsWord(const string &ss) {isWord = true; s = ss;}
  const bool &GetNodeIsWord() { return isWord;}
  void SetNodeHasChild() {hasChild = true;}
  const bool &GetNodeHasChild() {return hasChild;}
  const char &GetNodeChar() {return c;}
};

class Trie {
private:
  TrieNode root;
  TrieNode *curNode;
  Trie(const Trie &);
  Trie & operator = (const Trie &);
  void AddWord(const string &word, const size_t &pos); // Add a word to the Trie
public:
  Trie() : root(' ', "", false, false) , curNode(&root) {}
  Trie(const vector<string> &wordList) : root(' ', "", false, true) , curNode(&root) {BuildTrie(wordList);}
  void BuildTrie(const vector<string> &wordList); // Build Trie accoding to word list
  void AddWord(const string &word); // Add a word to the Trie
  bool ReadNextChar(const char &c, bool &moreWord,bool &isExist); // return true if a word is found
  void Reset2Root(); // start over
  bool Search(const string &str);
};


struct Point {
  double x;
  double y;
  Point(double x_, double y_) : x(x_), y(y_) {}
  Point(Point &point) : x(point.x), y(point.y) {}
  Point(const Point &point) : x(point.x), y(point.y) {}
  Point& operator=(Point &point) {
    swap(x, point.x);
    swap(y, point.y);
    return *this;
  }
  Point& operator=(const Point &point) {
    Point tmp(point);
    swap(x, tmp.x);
    swap(y, tmp.y);
    return *this;
  }
};
struct ListNode {
private:
  ListNode (ListNode &);
  ListNode (ListNode const &);
  ListNode& operator=(ListNode &);
  ListNode& operator=(ListNode const &);
public:
  int val;
  ListNode *next;
  ListNode (int x) : val(x), next(NULL) {}
  static void GenerateListNode(const int A[], int n, ListNode *&l) {
    if (n == 0) {
      l = nullptr;
      return;
    }
    l = new ListNode(A[0]);
    ListNode *tmp = l;
    for (int i = 1; i < n; i++) {
      ListNode *ll = new ListNode(A[i]);
      tmp->next = ll;
      tmp = ll;
    }
  }
  static void GenerateListNode(const vector<int> &A, ListNode *&l) {
    if (A.empty()) {
      l = nullptr;
      return;
    }
    l = new ListNode(A[0]);
    ListNode *tmp = l;
    for (size_t i = 1; i < A.size(); i++) {
      ListNode *ll = new ListNode(A[i]);
      tmp->next = ll;
      tmp = ll;
    }
  }
  static void PrintListNode(ListNode *l) {
    while (l!=nullptr) {
      cout<<l->val<<" ";
      l = l->next;
    }
    cout<<endl;
  }
  static void PrintListNode (ListNode *head, stringstream &sstr) {
    while (head != nullptr) {
      sstr<<head->val<<"->";
      head = head->next;
    }
    sstr<<"#";
  }
};
struct Tree {
private:
  Tree (Tree &);
  Tree (Tree const &);
  Tree& operator=(Tree &);
  Tree& operator=(Tree const &);
public:
  int val;
  Tree *left;
  Tree *right;
  Tree *parent;
  Tree(int x) : val(x), left(nullptr), right(nullptr), parent(nullptr) {}
  static void GenerateTree(const vector<int> &B, Tree *&tree) {
    if (B.empty()) {
      tree = nullptr;
      return;
    }
    vector<int> A(B);
    if (A.size()%2 == 0)
      A.push_back(INT_MIN);
    if (A[0] == INT_MIN)
      return;
    tree = new Tree(A[0]);

    size_t nextPos(1);
    Tree *node(nullptr);
    list<size_t> queuePos;
    list<Tree *> queueNode;
    queuePos.push_back(0ul);
    queueNode.push_back(tree);
    while (true) {
      if (nextPos >= A.size())
        break;
      //size_t pos = queuePos.front();
      node = queueNode.front();
      queuePos.pop_front();
      queueNode.pop_front();
      if (A[nextPos] == INT_MIN) {
        nextPos++;
      }
      else {
        Tree *newNode = new Tree(A[nextPos]);
        node->left = newNode;
        newNode->parent = node;
        queuePos.push_back(nextPos++);
        queueNode.push_back(newNode);
      }
      if (A[nextPos] == INT_MIN) {
        nextPos++;
      }
      else {
        Tree *newNode = new Tree(A[nextPos]);
        node->right = newNode;
        newNode->parent = node;
        queuePos.push_back(nextPos++);
        queueNode.push_back(newNode);
      }
    }
  }
  static void PrintTree(Tree *tree, ostringstream &ss) {
    list<Tree *> queue;
    if (tree == nullptr)
      return;
    ss<<tree->val<<'\t';
    queue.push_back(tree);
    while (!queue.empty()) {
      Tree *node = queue.front();
      queue.pop_front();
      if (node == nullptr)
        return;
      else {
        if (node->left == nullptr)
          ss<<"#\t";
        else {
          ss<<node->left->val<<'\t';
          queue.push_back(node->left);
        }
        if (node->right == nullptr)
          ss<<"#\t";
        else {
          ss<<node->right->val<<'\t';
          queue.push_back(node->right);
        }
      }
    }
  }
  static void PrintTree2File(Tree *tree, ostringstream &ss) {
    ss<<"<p>";
    PrintTree(tree, ss);
    ss<<"</p>";
  }
};

template <typename T,typename U>
struct Vertex {
private:
  Vertex& operator=(Vertex &);
  Vertex& operator=(Vertex const &);
public:
  size_t no;
  T val;
  unordered_map<size_t,U> neighbor;
  Vertex(const size_t &n,const T &v,const vector<size_t> &Neighbor,const vector<U> &NeighborVal) : no(n),val(v)
  {
    for (size_t i = 0; i < Neighbor.size(); i++) {
      neighbor.insert(pair<size_t,U>(Neighbor[i],NeighborVal[i]));
    }
  }
  Vertex(const size_t &n,const T &v) : no(n),val(v) {}
  Vertex() : no(-1) {}
  Vertex (Vertex &v) : no(v.no), val(v.val), neighbor(v.neighbor) {};
  Vertex (Vertex const &v) : no(v.no), val(v.val), neighbor(v.neighbor) {};
};

template <typename T,typename U>
class Graph {
private:
  unordered_map<size_t,Vertex<T,U> > nodeList;
  Graph (Graph &);
  Graph (Graph const &);
  Graph& operator=(Graph &);
  Graph& operator=(Graph const &);
public:
  Graph() {}
  void clear() { nodeList.clear(); }
  size_t size() { return nodeList.size();};
  void addVertex(const size_t &no, const T&val, const vector<size_t > &neighbor,const vector<U> &NeighborVal, const bool &bidirectional);
  void deleteVertex(const size_t &no);
  bool isVertexExist(const size_t &no);
  void addEdge(const bool &bidirectional, const size_t &originNo, const size_t &destinationNo, const U &edgeVal);
  void deleteEdge(const bool &bidirectional, const size_t &originNo, const size_t &destinationNo);
  bool isEdgeExist(const bool &bidirectional, const size_t &originNo, const size_t &destinationNo);
  void GenerateGraph(const bool &bidirectional,
                     const vector<size_t> &nodeNo,
                     const vector<T> &nodeVal,
                     const vector<vector<size_t> >&neighbor,
                     const vector<vector<U> > &neighborVal);
  size_t vertexCount();
  size_t edgeCount();
  void getNeightbor(const size_t no, vector<size_t> &neighbor);
  void PrintGraph(ostringstream &ss);
  void PrintGraph2File(ostringstream &ss);
  bool isRouteExisted(const size_t &originNo, const size_t &destinationNo, vector<size_t> &route);
};
// Graph
template<typename T, typename U>
void Graph<T,U>::addEdge(const bool &bidirectional, const size_t &originNo, const size_t &destinationNo, const U &edgeVal) {
  typename decltype(nodeList)::iterator itr1(nodeList.find(originNo)), itr2(nodeList.find(destinationNo));
  if (itr1 == nodeList.end() || itr2 == nodeList.end())
    return;
  itr1->second.neighbor.insert(pair<size_t,U>(destinationNo,edgeVal));
  if (bidirectional)
    itr2->second.neighbor.insert(pair<size_t,U>(originNo,edgeVal));
}
template <typename T,typename U>
void Graph<T,U>::deleteEdge(const bool &bidirectional, const size_t &originNo, const size_t &destinationNo) {
  typename decltype(nodeList)::iterator itr1(nodeList.find(originNo)), itr2(nodeList.find(destinationNo));
  if (itr1 == nodeList.end() || itr2 == nodeList.end())
    return;
  itr1->second.neighbor.erase(destinationNo);
  if (bidirectional)
    itr2->second.neighbor.erase(originNo);
}
template<typename T, typename U>
void Graph<T,U>::addVertex(const size_t &no, const T&val, const vector<size_t> &neighbor,
                           const vector<U> &NeighborVal, const bool &bidirectional) {
  if (nodeList.count(no) == 0) {
    Vertex<T,U> newVertex(no, val);
    nodeList.insert(pair<size_t,Vertex<T,U> >(no,newVertex));
    for (size_t i = 0; i < neighbor.size(); i++) {
      addEdge(bidirectional, no, neighbor[i], NeighborVal[i]);
    }
  }
}
template<typename T, typename U>
void Graph<T,U>::deleteVertex(const size_t &no) {
  if (nodeList.count(no) > 0) {
    nodeList.erase(no);
    for (typename decltype(nodeList)::iterator itr = nodeList.begin(); itr != nodeList.end(); ++itr) {
      itr->second.neighbor.erase(no);
    }
  }
}
template<typename T, typename U>
void Graph<T,U>::GenerateGraph(const bool &bidirectional,
                               const vector<size_t> &nodeNo,
                               const vector<T> &nodeVal,
                               const vector<vector<size_t> >&neighbor,
                               const vector<vector<U> > &neighborVal) {
  for (size_t i = 0; i < nodeNo.size(); i++) {
    Vertex<T,U> newVertex(nodeNo[i], nodeVal[i]);
    nodeList.insert(pair<size_t,Vertex<T,U> >(nodeNo[i],newVertex));
  }
  for (size_t i = 0; i < neighbor.size(); i++) {
    for (size_t j = 0; j < neighbor[i].size(); j++) {
      nodeList[nodeNo[i]].neighbor.insert(pair<size_t,U>(neighbor[i][j],neighborVal[i][j]));
    }
  }
}
template<typename T, typename U>
bool Graph<T,U>::isVertexExist(const size_t &no) {
  return nodeList.count(no)>0;
}
template<typename T, typename U>
bool Graph<T,U>::isEdgeExist(const bool &bidirectional, const size_t &originNo, const size_t &destinationNo) {
  if (!bidirectional) {
    if (nodeList.count(originNo) == 0) {
      return false;
    }
    else {
      if (nodeList[originNo].neighbor.count(destinationNo) == 0)
        return false;
      else
        return true;
    }
  }
  else {
    if (nodeList.count(originNo) == 0 || nodeList.count(destinationNo) == 0)
      return false;
    else {
      if (nodeList[originNo].neighbor.count(destinationNo) == 0 ||
          nodeList[destinationNo].neighbor.count(originNo) == 0)
        return false;
      else
        return true;
    }
  }
}
template<typename T, typename U>
size_t Graph<T,U>::vertexCount() {
  return nodeList.size();
}
template<typename T, typename U>
size_t Graph<T,U>::edgeCount() {
  size_t count(0);
  for (typename decltype(nodeList)::iterator itr = nodeList.begin(); itr != nodeList.end(); ++itr) {
    count += itr->second.neighbor.size();
  }
  return count;
}
template<typename T, typename U>
void Graph<T,U>::getNeightbor(const size_t no, vector<size_t> &neighbor) {
  neighbor.clear();
  typename decltype(nodeList)::iterator itr = nodeList.find(no);
  if (itr != nodeList.begin()) {
    for (auto itr2 = itr->second.neighbor.begin();
         itr2 != itr->second.neighbor.end(); ++itr2) {
      neighbor.push_back(itr2->first);
    }
  }
}
template<typename T, typename U>
void Graph<T,U>::PrintGraph(ostringstream &ss) {
  if (nodeList.empty())
    ss<<"empty graph";
  for (auto itr1 = nodeList.begin(); itr1 != nodeList.end(); ++itr1) {
    ss<<"Node: "<<itr1->first<<" Node Value: "<<itr1->second.val<<" Node's Neighbors: ";
    for (auto itr2 = itr1->second.neighbor.begin();
         itr2 != itr1->second.neighbor.end(); ++itr2) {
      ss<<"("<<itr2->first<<", "<<itr2->second<<")\n";
    }
  }
}
template<typename T, typename U>
void Graph<T,U>::PrintGraph2File(ostringstream &ss) {
  if (nodeList.empty())
    ss<<"empty graph";
  for (auto itr1 = nodeList.begin(); itr1 != nodeList.end(); ++itr1) {
    ss<<"<p>Node ID: "<<itr1->first<<"</p><p>Node Value: "<<itr1->second.val<<"</p><p>Node's Neighbors:</p>";
    for (auto itr2 = itr1->second.neighbor.begin();
         itr2 != itr1->second.neighbor.end(); ++itr2) {
      ss<<"<p>("<<itr2->first<<", "<<itr2->second<<")</p>";
    }
    ss<<"<p>==========</p>";
  }
}
template<typename T, typename U>
bool Graph<T,U>::isRouteExisted(const size_t &originNo, const size_t &destinationNo, vector<size_t> &route) {
  route.clear();
  if (originNo == destinationNo) {
    route.push_back(originNo);
    return true;
  }
  auto itr1 = nodeList.find(originNo), itr2 = nodeList.find(destinationNo);
  if (itr1 == nodeList.end() || itr2 == nodeList.end())
    return false;
  queue<size_t> vertexQueue;
  queue<vector<size_t> > routeQueue;
  unordered_set<size_t> visited;

  size_t vID;
  vertexQueue.push(originNo);
  route.push_back(originNo);
  routeQueue.push(route);
  visited.insert(originNo);
  while (!vertexQueue.empty()) {
    route = routeQueue.front(); routeQueue.pop();
    vID = vertexQueue.front(); vertexQueue.pop();
    for (auto itr3 = nodeList[vID].neighbor.begin();
         itr3 != nodeList[vID].neighbor.end(); itr3++) {
      if (itr3->first == destinationNo) {
        route.push_back(destinationNo);
        return true;
      }
      if (visited.count(itr3->first) == 0) {
        visited.insert(itr3->first);
        route.push_back(itr3->first);
        routeQueue.push(route);
        vertexQueue.push(itr3->first);
      }
    }
  }
  route.clear();
  return false;
}

class Tools {
public:
  //////////////////// Print vector<vector<T>>
  template<typename T>
  void PrintMatrix(const vector<vector<T> > &mat){
    for (size_t i = 0; i < mat.size(); i++){
      for (size_t j = 0; j < mat[i].size(); j++)
        cout<<mat[i][j]<<"\t";
      cout<<endl;
    }
    cout<<endl;
    //cout<<mat.size()*mat[0].size()<<endl;
  }
  template<typename T>
  void PrintMatrix(const vector<vector<T> > &mat, stringstream &sstr){
    for (size_t i = 0; i < mat.size(); i++){
      for (size_t j = 0; j < mat[i].size(); j++)
        sstr<<mat[i][j]<<"\t";
      sstr<<endl;
    }
  }
  template<typename T>
  string PrintMatrix2String(const vector<vector<T> > &mat) {
    stringstream ss;
    for (size_t i = 0; i < mat.size(); i++){
      for (size_t j = 0; j < mat[i].size(); j++) {
        ss<<mat[i][j]<<"\t";
      }
      ss<<'\n';
    }
    return ss.str();
  }
  template<typename T>
  void PrintMatrix2File(const vector<vector<T> > &mat, stringstream &sstr){
    for (size_t i = 0; i < mat.size(); i++){
      sstr<<"<p>";
      for (size_t j = 0; j < mat[i].size(); j++) {
        sstr<<mat[i][j]<<"\t";
      }
      sstr<<"</p>";
    }
    sstr<<'\n';
    //sstr<<mat.size()*mat[0].size()<<endl;
  }
  template<typename T>
  bool GenerateNewMatrix(vector<vector<T> > &mat, const vector<T> &vec,
                         const unsigned long &row, const unsigned long &col) {
    if (vec.size() != row*col)
      return false;
    mat.clear();
    int count(0);
    for (size_t i = 0; i < row; i++) {
      vector<T> line;
      for (size_t j = 0; j < col; j++) {
        line.push_back(vec[count++]);
      }
      mat.push_back(move(line));
    }
    return true;
  }
  template<typename T>
  bool GenerateNewMatrix(vector<vector<T> > &mat, int vec[],
                         const unsigned long &row, const unsigned long &col) {
    mat.clear();
    for (size_t i = 0; i < row; i++) {
      vector<T> line;
      for (size_t j = 0; j < col; j++) {
        line.push_back(vec[i*row+j]);
      }
      mat.push_back(move(line));
    }
    return true;
  }
  //////////////////// Print vector<T>
  template<typename T>
  void PrintVector(const vector<T> &vec) {
    for (size_t j = 0; j < vec.size(); j++)
      cout<<vec[j]<<'\t';
    cout<<endl;
  }
  template<typename T>
  void PrintVector(const vector<T> &vec, ostringstream &sstr) {
    for (size_t j = 0; j < vec.size(); j++)
      sstr<<vec[j];
  }
  template<typename T>
  void PrintVector2File(const vector<T> &vec, ostringstream &sstr) {
    for (size_t j = 0; j < vec.size(); j++)
      sstr<<vec[j]<<'\t';
  }
  /////////////////// new c style string
  void new_c_str(char *&str, const string &s) {
    str = new char[s.size()+1];
    memcpy(str, s.c_str(), s.size());
    str[s.size()] = 0;
  }
  void new_c_str_N(char *&str, const string &s, const int &N) {
    if (N < static_cast<int>(s.size())) {
      new_c_str(str, s);
      return;
    }
    str = new char[N];
    memcpy(str, s.c_str(), N);
    str[N] = 0;
  }
};

