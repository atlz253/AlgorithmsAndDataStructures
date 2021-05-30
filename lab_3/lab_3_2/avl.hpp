#ifndef AVL_HPP
#define AVL_HPP

struct node  // структура для представления узлов дерева
{
  int key;
  unsigned char height;
  struct node *left, *right;
};

typedef struct node node;
typedef struct node* tree;

class AVL
{
 private:
  tree t;

  node* makeNode(int k);
  node* balance(node* p);  // балансировка узла p

  int bfactor(node* p);  //вычисление баланса
  void fixHeight(node* p);  //корректировка высоты после добавления/удаления узлов

  node* findmin(node* p);    // поиск узла с минимальным ключом в дереве p
  bool _searchKey(node* p, int key);

  node* rotateLeft(node* q);   // левый поворот вокруг q
  node* rotateRight(node* p);  // правый поворот вокруг p

  void _print(tree t, int tbl);

  tree _insert(tree p, int k);  // вставка ключа k в дерево с корнем p

  tree _remove(tree p, int k);  // удаление ключа k из дерева p
  node* removemin(node* p);  // удаление узла с минимальным ключом из дерева p

  void del_tree(tree t);

 public:
  AVL();

  void print();

  bool searchKey(int key);

  void insert(int k);

  void remove(int k);

  ~AVL();
};

#endif  // AVL_HPP
