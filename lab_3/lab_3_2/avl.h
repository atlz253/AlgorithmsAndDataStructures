#ifndef AVL_H
#define AVL_H

struct node  // структура для представления узлов дерева
{
  int key;
  unsigned char height;
  struct node *left, *right;
};

typedef struct node node;
typedef struct node* tree;

int bfactor(tree p);
node* make_node(int k);
void fixheight(node* p);
node* rotateright(node* p);
node* rotateleft(node* q);
node* balance(node* p);
tree avl_insert(tree p, int k);
node* findmin(node* p);
node* removemin(node* p);
tree avl_remove(tree p, int k);
void print_sim_avl(tree t, int tbl);
void del_tree_avl(tree t);

#endif  // AVL_H
