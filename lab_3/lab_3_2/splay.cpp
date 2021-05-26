#include "splay.h"

#include <iostream>

Node* makeNode(Node* parent, int key)
{
  Node* node = (Node*)malloc(sizeof(Node));
  node->left = node->right = NULL;
  node->parent = parent;
  node->key = key;
  return node;
}

Node* addNode(Node* cur, int key)
{
  if (cur->key == key) return cur;

  Node* tmp;

  if (cur->key > key)
  {
    if (cur->left)
      tmp = addNode(cur->left, key);
    else
      tmp = cur->left = makeNode(cur, key);
  }
  else
  {
    if (cur->right)
      tmp = addNode(cur->right, key);
    else
      tmp = cur->right = makeNode(cur, key);
  }

  return tmp;
}

void del_tree(Node* node)
{
  if (node->left) del_tree(node->left);
  if (node->right) del_tree(node->right);
  free(node);
}

void print_sim(Node* node, int tbl)
{
  if (node->right) print_sim(node->right, tbl + 5);
  printf("%*d\n", tbl, node->key);
  if (node->left) print_sim(node->left, tbl + 5);
}

Node* findNode(Node* cur, Node** prev, int key)
{
  while (cur)
  {
    if (cur->key == key)
      return cur;
    else
    {
      *prev = cur;
      cur = (cur->key > key ? cur->left : cur->right);
    }
  }
  return NULL;
}

Node* removeNode(Node** treeRoot, Node* node)
{
  Node *prev, *higherClosest, *p, *ch, *removedNode;
  prev = higherClosest = p = ch = NULL;

  if (node->left && node->right)
  {
    higherClosest = findNode(node, &prev, node->key + 1);
    if (!higherClosest)
    {
      higherClosest = prev;
      p = prev->parent;
    }
    else
    {
      p = prev;
    }
    node->key = higherClosest->key;

    if (higherClosest == p->left)
      p->left = higherClosest->right;
    else
      p->right = higherClosest->right;

    if (higherClosest->right) higherClosest->right->parent = p;

    removedNode = higherClosest;
  }
  else
  {
    p = node->parent;
    ch = node->left ? node->left : node->right;
    if (!p)
      *treeRoot = ch;
    else
    {
      if (p->left == node)
        p->left = ch;
      else
        p->right = ch;
    }
    if (ch) ch->parent = p;

    removedNode = node;
  }

  free(removedNode);
  return p;
}

void chainGrandParent(Node* gp, Node* p, Node* ch)
{
  if (gp->left == p)
    gp->left = ch;
  else
    gp->right = ch;
}

// returns new subtree root
Node* rotateRight(Node** treeRoot, Node* r)
{
  Node* ch = r->left;

  r->left = ch->right;
  if (ch->right) ch->right->parent = r;
  ch->parent = r->parent;

  if (r->parent)
    chainGrandParent(r->parent, r, ch);
  else
    *treeRoot = ch;

  ch->right = r;
  r->parent = ch;

  return ch;
}

Node* rotateLeft(Node** treeRoot, Node* r)
{
  Node* ch = r->right;

  r->right = ch->left;
  if (ch->left) ch->left->parent = r;
  ch->parent = r->parent;

  if (r->parent)
    chainGrandParent(r->parent, r, ch);
  else
    *treeRoot = ch;

  ch->left = r;
  r->parent = ch;

  return ch;
}

SplayTree* initSplayTree()
{
  SplayTree* st = (SplayTree*)malloc(sizeof(SplayTree));
  st->root = NULL;

  return st;
}

int isZigZag(Node* cur)
{
  Node *p = cur->parent, *gp = p->parent;

  return (p->right == cur && gp->left == p) || (p->left == cur && gp->right == p);
}

void zigZag(Node** treeRoot, Node* cur)
{
  Node* p = cur->parent;
  if (p->right == cur && p->parent->left == p)
    rotateRight(treeRoot, rotateLeft(treeRoot, p)->parent);
  else
    rotateLeft(treeRoot, rotateRight(treeRoot, p)->parent);
}

void zigZig(Node** treeRoot, Node* cur)
{
  Node* p = cur->parent;
  if (p->left == cur && p->parent->left == p)
    rotateRight(treeRoot, rotateRight(treeRoot, p->parent));
  else
    rotateLeft(treeRoot, rotateLeft(treeRoot, p->parent));
}

void zig(Node** treeRoot, Node* cur)
{
  Node* p = cur->parent;
  if (p->left == cur)
    rotateRight(treeRoot, p);
  else
    rotateLeft(treeRoot, p);
}

Node* splay(Node** root, Node* cur)
{
  if (!cur) return NULL;

  while (cur->parent)
  {
    if (cur->parent->parent)
      if (isZigZag(cur))
        zigZag(root, cur);
      else
        zigZig(root, cur);
    else
      zig(root, cur);
  }
  return cur;
}

Node* insertKey(SplayTree* tree, int key)
{
  if (!tree->root) tree->root = makeNode(NULL, key);
  return splay(&tree->root, addNode(tree->root, key));
}

Node* findKey(SplayTree* tree, int key)
{
  Node* prev = NULL;
  Node* res = findNode(tree->root, &prev, key);

  if (res) return splay(&tree->root, res);
  if (prev) splay(&tree->root, prev);
  return NULL;
}

int removeKey(SplayTree* tree, int key)
{
  Node* prev = NULL;
  Node* res = findNode(tree->root, &prev, key);

  if (res)
    splay(&tree->root, removeNode(&tree->root, res));
  else if (prev)
    splay(&tree->root, prev);
  return res ? 1 : 0;
}
