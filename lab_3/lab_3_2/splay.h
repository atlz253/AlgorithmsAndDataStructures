#ifndef SPLAY_H
#define SPLAY_H

#define SplayTree struct splayTree
#define Node struct node

// BinTree routine
Node
{
  int key;
  Node *left, *right, *parent;
};

// SplayTree operations
SplayTree { Node* root; };

Node* makeNode(Node* parent, int key);
Node* addNode(Node* cur, int key);
void del_tree(Node* node);
void print_sim(Node* node, int tbl);
Node* findNode(Node* cur, Node** prev, int key);
Node* removeNode(Node** treeRoot, Node* node);
void chainGrandParent(Node* gp, Node* p, Node* ch);
Node* rotateRight(Node** treeRoot, Node* r);
Node* rotateLeft(Node** treeRoot, Node* r);

SplayTree* initSplayTree();
int isZigZag(Node* cur);
void zigZag(Node** treeRoot, Node* cur);
void zigZig(Node** treeRoot, Node* cur);
void zig(Node** treeRoot, Node* cur);
Node* splay(Node** root, Node* cur);
Node* insertKey(SplayTree* tree, int key);
Node* findKey(SplayTree* tree, int key);
int removeKey(SplayTree* tree, int key);

#endif  // SPLAY_H
