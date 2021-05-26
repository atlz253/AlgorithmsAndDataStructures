#include "avl.h"

#include <iostream>

int bfactor(tree p)  //вычисление баланса
{
  return (p->left ? p->left->height : 0) - (p->right ? p->right->height : 0);
}

node* make_node(int k)
{
  node* n = (node*)malloc(sizeof(n));
  if (n == NULL) return NULL;
  n->key = k;
  n->left = n->right = NULL;
  n->height = 1;
  return n;
}

void fixheight(node* p)  //корректировка высоты после добавления/удаления узлов
{
  unsigned char hl = p->left ? p->left->height : 0;
  unsigned char hr = p->right ? p->right->height : 0;
  p->height = (hl > hr ? hl : hr) + 1;
}

node* rotateright(node* p)  // правый поворот вокруг p
{
  node* q = p->left;
  p->left = q->right;
  q->right = p;
  fixheight(p);
  fixheight(q);
  return q;
}

node* rotateleft(node* q)  // левый поворот вокруг q
{
  node* p = q->right;
  q->right = p->left;
  p->left = q;
  fixheight(q);
  fixheight(p);
  return p;
}

node* balance(node* p)  // балансировка узла p
{
  fixheight(p);
  if (bfactor(p) == -2)
  {
    if (bfactor(p->right) > 0) p->right = rotateright(p->right);
    return rotateleft(p);
  }
  if (bfactor(p) == 2)
  {
    if (bfactor(p->left) < 0) p->left = rotateleft(p->left);
    return rotateright(p);
  }
  return p;  // балансировка не нужна
}

tree avl_insert(tree p, int k)  // вставка ключа k в дерево с корнем p
{
  if (!p) return make_node(k);
  if (k == p->key) return p;
  if (k < p->key)
    p->left = avl_insert(p->left, k);
  else
    p->right = avl_insert(p->right, k);
  return balance(p);
}

node* findmin(node* p)  // поиск узла с минимальным ключом в дереве p
{
  return p->left ? findmin(p->left) : p;
}

node* removemin(node* p)  // удаление узла с минимальным ключом из дерева p
{
  if (p->left == 0) return p->right;
  p->left = removemin(p->left);
  return balance(p);
}

tree avl_remove(tree p, int k)  // удаление ключа k из дерева p
{
  if (!p) return 0;
  if (k < p->key)
    p->left = avl_remove(p->left, k);
  else if (k > p->key)
    p->right = avl_remove(p->right, k);
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

void print_sim_avl(tree t, int tbl)
{
  if (t->right) print_sim_avl(t->right, tbl + 5);
  printf("%*d(%d)\n", tbl, t->key, t->height);
  if (t->left) print_sim_avl(t->left, tbl + 5);
}

void del_tree_avl(tree t)
{
  if (t->left) del_tree_avl(t->left);
  if (t->right) del_tree_avl(t->right);
  free(t);
}
