#include <iostream>

#include "avl.hpp"

using namespace std;

int main()
{
  AVL avl;
  int mas[15]={14, 8, 1, 13, 7, 12, 6, 2, 9, 0, 11, 10, 4, 3, 5}, i;

  for (i = 0; i < 15; i++)
    avl.insert(mas[i]);

  avl.print();

  return 0;
}
