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
  bool _isFilled;

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

    _isFilled = true;
    f.close();
  }

 public:
  Menu()
  {
    _isFilled = false;
    _avlTree = new AVL();
    _splayTree = new Splay();
  }

  int run()
  {
    int choice;

    while (true)
    {
      cout << "1. заполнить деревья ключами из файла" << endl
           << "2. добавить случайные ключи" << endl
           << "3. поиск 100 ключей" << endl
           << "0. выход из программы" << endl;

      cin >> choice;

      switch (choice)
      {
        case 1:
          if (!_isFilled)
          {
            _fill();
          }
          else
          {
            cout << "Деревья уже заполнены ключами из файла!" << endl;
            cin.get();
          }
          break;
        case 2:

          break;
        case 3:

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
