#include "splay.hpp"

#include <iostream>

Node* Splay::makeNode(Node* parent, int key)
{
  Node* node = new Node;
  node->left = node->right = NULL;
  node->parent = parent;
  node->key = key;
  return node;
}

Node* Splay::addNode(Node* cur, int key)
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

void Splay::_print(Node* node, int tbl)
{
  if (node->right) _print(node->right, tbl + 5);
  printf("%*d\n", tbl, node->key);
  if (node->left) _print(node->left, tbl + 5);
}

Node* Splay::findNode(Node* cur, Node** prev, int key)
{
  while (++curCompares && cur)
  {
    if (++curCompares && cur->key == key)
      return cur;
    else
    {
      *prev = cur;
      curCompares++;
      cur = (cur->key > key ? cur->left : cur->right);
    }
  }
  return NULL;
}

Node* Splay::removeNode(Node** treeRoot, Node* node)
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

void Splay::chainGrandParent(Node* gp, Node* p, Node* ch)
{
  if (gp->left == p)
    gp->left = ch;
  else
    gp->right = ch;
}

Node* Splay::rotateRight(Node** treeRoot, Node* r)
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

Node* Splay::rotateLeft(Node** treeRoot, Node* r)
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

int Splay::isZigZag(Node* cur)
{
  Node *p = cur->parent, *gp = p->parent;

  return (p->right == cur && gp->left == p) || (p->left == cur && gp->right == p);
}

void Splay::zigZag(Node** treeRoot, Node* cur)
{
  Node* p = cur->parent;
  if (p->right == cur && p->parent->left == p)
    rotateRight(treeRoot, rotateLeft(treeRoot, p)->parent);
  else
    rotateLeft(treeRoot, rotateRight(treeRoot, p)->parent);
}

void Splay::zigZig(Node** treeRoot, Node* cur)
{
  Node* p = cur->parent;
  if (p->left == cur && p->parent->left == p)
    rotateRight(treeRoot, rotateRight(treeRoot, p->parent));
  else
    rotateLeft(treeRoot, rotateLeft(treeRoot, p->parent));
}

void Splay::zig(Node** treeRoot, Node* cur)
{
  Node* p = cur->parent;
  if (p->left == cur)
    rotateRight(treeRoot, p);
  else
    rotateLeft(treeRoot, p);
}

Node* Splay::splay(Node** root, Node* cur)
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

void Splay::delTree(Node* node)
{
  if (node->left) delTree(node->left);
  if (node->right) delTree(node->right);
  free(node);
}

Splay::Splay()
{
  totalCompares = 0;
  comparesCount = 0;
  t = new SplayTree;
  memory = sizeof(SplayTree);
  t->root = nullptr;
}

void Splay::print() { _print(t->root, 10); }

Node* Splay::insertKey(int key)
{
  memory += sizeof(Node);
  if (!t->root) t->root = makeNode(NULL, key);
  return splay(&t->root, addNode(t->root, key));
}

Node* Splay::findKey(int key)
{
  curCompares = 0;
  comparesCount++;
  Node* prev = NULL;
  Node* res = findNode(t->root, &prev, key);
  totalCompares += curCompares;

  if (res) return splay(&t->root, res);
  if (prev) splay(&t->root, prev);
  return NULL;
}

int Splay::removeKey(int key)
{
  memory -= sizeof(Node);
  Node* prev = NULL;
  Node* res = findNode(t->root, &prev, key);

  if (res)
    splay(&t->root, removeNode(&t->root, res));
  else if (prev)
    splay(&t->root, prev);
  return res ? 1 : 0;
}

unsigned long int Splay::getUsedMemory(void) { return memory; }

unsigned long int Splay::getCurCompares(void) { return curCompares; }

unsigned long int Splay::getAverageCompares(void) { return totalCompares / comparesCount; }

Splay::~Splay() { delTree(t->root); }
