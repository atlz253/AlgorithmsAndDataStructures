#include <fstream>
#include <iostream>

#include "avl.hpp"
#include "splay.hpp"

using namespace std;

class Menu
{
 private:
  AVL *_avlTree;
  Splay *_splayTree;

  void _fill(void)
  {
    int tmp;
    ifstream f;
    f.open("../test_numbers.txt", ios_base::in);

    while (!f.eof())
    {
      f >> tmp;
      _avlTree->insertKey(tmp);
      _splayTree->insertKey(tmp);
    }

    f.close();
  }

  void _keysFind(void)
  {
    int cur;
    ifstream f;
    f.open("testKeys.txt", ios_base::in);

    for (size_t i = 0; i < 100; i++)
    {
      f >> cur;

      _splayTree->findKey(cur);
      if (_avlTree->findKey(cur))
        cout << "Ключ " << cur << " найден. ";
      else
        cout << "Ключ " << cur << " не найден. ";
      cout << "Количество сравнений в АВЛ - " << _avlTree->getCurCompares() << " количество сравнений в Splay - "
           << _splayTree->getCurCompares() << endl;
    }
    cout << "Среднее кол-во сравнений в АВЛ - " << _avlTree->getAverageCompares()
         << " среднее кол-во сравнений в Splay - " << _splayTree->getAverageCompares() << endl;

    f.close();
  }

 public:
  Menu()
  {
    _avlTree = new AVL();
    _splayTree = new Splay();
    _fill();
  }

  int run()
  {
    int choice;

    while (true)
    {
      cout << "1. поиск 100 ключей" << endl
           << "2. количество используемой памяти" << endl
           << "0. выход из программы" << endl;

      cin >> choice;

      switch (choice)
      {
        case 1:
          _keysFind();
          break;
        case 2:
          cout << "АВЛ: " << _avlTree->getUsedMemory() << endl << "Splay: " << _splayTree->getUsedMemory() << endl;
          break;
        case 0:
          return 0;
        default:
          cout << "Ошибка ввода!" << endl;
          cin.get();
          break;
      }
    }
  }

  ~Menu()
  {
    delete _avlTree;
    delete _splayTree;
  }
};

int main() { return Menu().run(); }
