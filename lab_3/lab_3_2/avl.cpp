#include "avl.hpp"

#include <iostream>

int AVL::bfactor(node* p) { return (p->left ? p->left->height : 0) - (p->right ? p->right->height : 0); }

node* AVL::makeNode(int k)
{
  node* n = (node*)malloc(sizeof(n));
  if (n == nullptr) return nullptr;
  n->key = k;
  n->left = n->right = nullptr;
  n->height = 1;
  return n;
}

void AVL::fixHeight(node* p)
{
  unsigned char hl = p->left ? p->left->height : 0;
  unsigned char hr = p->right ? p->right->height : 0;
  p->height = (hl > hr ? hl : hr) + 1;
}

node* AVL::rotateRight(node* p)
{
  node* q = p->left;
  p->left = q->right;
  q->right = p;
  fixHeight(p);
  fixHeight(q);
  return q;
}

node* AVL::rotateLeft(node* q)
{
  node* p = q->right;
  q->right = p->left;
  p->left = q;
  fixHeight(q);
  fixHeight(p);
  return p;
}

node* AVL::balance(node* p)
{
  fixHeight(p);
  if (bfactor(p) == -2)
  {
    if (bfactor(p->right) > 0) p->right = rotateRight(p->right);
    return rotateLeft(p);
  }
  if (bfactor(p) == 2)
  {
    if (bfactor(p->left) < 0) p->left = rotateLeft(p->left);
    return rotateRight(p);
  }
  return p;  // балансировка не нужна
}

node* AVL::findmin(node* p) { return p->left ? findmin(p->left) : p; }

node* AVL::removemin(node* p)
{
  if (p->left == 0) return p->right;
  p->left = removemin(p->left);
  return balance(p);
}

node* AVL::_searchKey(node* p, int key)
{
  if (p == nullptr) return nullptr;
  int k = p->key;
  if (++curCompares && k == key)
    return p;
  else if (++curCompares && k > key)
    return _searchKey(p->left, key);
  else if (++curCompares && k < key)
    return _searchKey(p->right, key);
  return nullptr;
}

void AVL::_print(tree t, int tbl)
{
  if (!t) return;
  if (t->right) _print(t->right, tbl + 5);
  printf("%*d(%d)\n", tbl, t->key, t->height);
  if (t->left) _print(t->left, tbl + 5);
}

tree AVL::_insert(tree p, int k)
{
  if (!p) return makeNode(k);
  if (k == p->key) return p;
  if (k < p->key)
    p->left = _insert(p->left, k);
  else
    p->right = _insert(p->right, k);
  return balance(p);
}

tree AVL::_remove(tree p, int k)
{
  if (!p) return 0;
  if (k < p->key)
    p->left = _remove(p->left, k);
  else if (k > p->key)
    p->right = _remove(p->right, k);
  else  //  k == p->key
  {
    node* q = p->left;
    node* r = p->right;
    free(p);
    if (!r) return q;
    node* min = findmin(r);
    min->right = removemin(r);
    min->left = q;
    return balance(min);
  }
  return balance(p);
}

void AVL::delTree(tree t)
{
  if (!t) return;
  if (t->left) delTree(t->left);
  if (t->right) delTree(t->right);
  delete t;
}

AVL::AVL()
{
  totalCompares = 0;
  comparesCount = 0;
  t = nullptr;
}

void AVL::removeKey(int k) { t = _remove(t, k); }

node* AVL::findKey(int key)
{
  curCompares = 0;
  comparesCount++;
  node* result = _searchKey(t, key);
  totalCompares += curCompares;
  return result;
}

void AVL::insertKey(int k) { t = _insert(t, k); }

void AVL::print() { _print(t, 10); }

unsigned long int AVL::getCurCompares(void) { return curCompares; }

unsigned long int AVL::getAverageCompares(void) { return totalCompares / comparesCount; }

AVL::~AVL() { delTree(t); }
