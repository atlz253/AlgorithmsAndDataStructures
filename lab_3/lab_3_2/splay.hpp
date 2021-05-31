#ifndef SPLAY_HPP
#define SPLAY_HPP

#define SplayTree struct splayTree
#define Node struct splayNode

Node
{
  int key;
  Node* left;
  Node* right;
  Node* parent;
};

SplayTree { Node* root; };

class Splay
{
 private:
  SplayTree* t;

  unsigned long int curCompares;
  unsigned long int comparesCount;
  unsigned long int totalCompares;

  Node* makeNode(Node* parent, int key);
  Node* addNode(Node* cur, int key);

  void _print(Node* node, int tbl);

  Node* findNode(Node* cur, Node** prev, int key);
  Node* removeNode(Node** treeRoot, Node* node);

  void chainGrandParent(Node* gp, Node* p, Node* ch);

  Node* rotateLeft(Node** treeRoot, Node* r);
  Node* rotateRight(Node** treeRoot, Node* r);

  int isZigZag(Node* cur);
  Node* splay(Node** root, Node* cur);
  void zig(Node** treeRoot, Node* cur);
  void zigZag(Node** treeRoot, Node* cur);
  void zigZig(Node** treeRoot, Node* cur);

  void delTree(Node* node);

 public:
  Splay();

  void print();

  Node* findKey(int key);
  int removeKey(int key);
  Node* insertKey(int key);

  unsigned long int getCurCompares(void);
  unsigned long int getAverageCompares(void);

  ~Splay();
};

#endif  // SPLAY_HPP
