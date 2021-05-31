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

  unsigned long int curCompares;
  unsigned long int comparesCount;
  unsigned long int totalCompares;

  node* makeNode(int k);
  node* balance(node* p);  // балансировка узла p

  int bfactor(node* p);  //вычисление баланса
  void fixHeight(node* p);  //корректировка высоты после добавления/удаления узлов

  node* findmin(node* p);  // поиск узла с минимальным ключом в дереве p
  node* _searchKey(node* p, int key);

  node* rotateLeft(node* q);   // левый поворот вокруг q
  node* rotateRight(node* p);  // правый поворот вокруг p

  void _print(tree t, int tbl);

  tree _insert(tree p, int k);  // вставка ключа k в дерево с корнем p

  tree _remove(tree p, int k);  // удаление ключа k из дерева p
  node* removemin(node* p);     // удаление узла с минимальным ключом из дерева p

  void delTree(tree t);

 public:
  AVL();

  void print();

  node* findKey(int key);

  void insertKey(int k);

  void removeKey(int k);

  unsigned long int getCurCompares(void);
  unsigned long int getAverageCompares(void);

  ~AVL();
};

#endif  // AVL_HPP
