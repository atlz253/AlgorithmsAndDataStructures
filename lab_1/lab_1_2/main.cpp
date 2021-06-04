#include <iostream>

#define CLEAR_CONSOLE 1
#define CLEAR \
  if (CLEAR_CONSOLE) system("clear");

using namespace std;

class Deque
{
 public:
  virtual bool addStart(const int a) = 0;
  virtual bool addEnd(const int a) = 0;
  virtual void delStart(void) = 0;
  virtual void delEnd(void) = 0;
  virtual int readStart(void) = 0;
  virtual int readEnd(void) = 0;
  virtual bool isEmpty(void) = 0;
  virtual bool isFilled(void) = 0;
  virtual int getSize(void) = 0;
  virtual ~Deque() = default;
};

class ListDeque : public Deque
{
 private:
  typedef struct node
  {
    int num;
    node *next = nullptr;
    node *prev = nullptr;
  } node;

  node *_first = nullptr;
  node *_last = nullptr;

 public:
  bool addStart(const int a) override
  {
    if (!_first)
    {
      _first = new node;
      _first->num = a;
      _last = _first;
      return true;
    }
    else
    {
      node *new_node = new node;
      new_node->num = a;
      new_node->next = _first;
      _first->prev = new_node;
      _first = new_node;
      return true;
    }

    return false;
  }

  bool addEnd(const int a) override
  {
    if (!_last)
    {
      _last = new node;
      _last->num = a;
      _first = _last;
      return true;
    }
    else
    {
      node *new_node = new node;
      new_node->num = a;
      new_node->prev = _last;
      _last->next = new_node;
      _last = new_node;
      return true;
    }

    return false;
  }

  void delStart(void) override
  {
    if (_first)
    {
      if (_first->next)
      {
        node *p = _first->next;
        p->prev = nullptr;
        delete _first;
        _first = p;
      }
      else
      {
        delete _first;
        _first = nullptr;
        _last = nullptr;
      }
    }
  }

  void delEnd(void) override
  {
    if (_last)
    {
      if (_last->prev)
      {
        node *p = _last->prev;
        p->next = nullptr;
        delete _last;
        _last = p;
      }
      else
      {
        delete _last;
        _last = nullptr;
        _first = nullptr;
      }
    }
  }

  int readStart(void) override { return _first->num; }

  int readEnd(void) override { return _last->num; }

  virtual bool isEmpty(void) override
  {
    if (!_first)
      return true;
    else
      return false;
  }

  virtual bool isFilled(void) override
  {
    if (_first)
      return true;
    else
      return false;
  }

  virtual int getSize(void) override { return 0; }

  ~ListDeque()
  {
    while (_first)
    {
      _last = _first->next;  // сохраняем ссылку на следующий элемент
      delete _first;         // удаляем текущий
      _first = _last;
    }
  }
};

class VectorDeque : public Deque
{
 private:
  int _size = 0;

  int *_end = nullptr;
  int *_head = nullptr;

  int *_first = nullptr;
  int *_last = nullptr;

 public:
  VectorDeque(const int size)
  {
    _size = size;
    _head = new int[size];
    _end = _head + _size - 1;
  }

  bool addStart(const int a) override
  {
    bool dequeIsFull = _first && ((_first == _head && _last == _head + _size - 1) || (_first == _last + 1));

    if (!_first)
    {
      _first = _last = _head;
      *_first = a;
      return true;
    }
    else if (!dequeIsFull && _head == _first)
    {
      _first = _end;
      *_first = a;
      return true;
    }
    else if (!dequeIsFull)
    {
      _first--;
      *_first = a;
      return true;
    }
    return false;
  }

  bool addEnd(const int a) override
  {
    bool dequeIsFull = _first && ((_first == _head && _last == _head + _size - 1) || (_first == _last + 1));

    if (!_first)
    {
      _first = _last = _head;
      *_last = a;
      return true;
    }
    else if (!dequeIsFull && _last == _end)
    {
      _last = _head;
      *_last = a;
      return true;
    }
    else if (!dequeIsFull)
    {
      _last++;
      *_last = a;
      return true;
    }
    return false;
  }

  void delStart(void) override
  {
    if (_first == _last)
      _first = _last = nullptr;
    else if (_first == _end)
      _first = _head;
    else
      _first++;
  }

  void delEnd(void) override
  {
    if (_first == _last)
      _first = _last = nullptr;
    else if (_last == _head)
      _last = _end;
    else
      _last--;
  }

  int readStart(void) override
  {
    if (_first) return *_first;
    return -1;
  }

  int readEnd(void) override
  {
    if (_last) return *_last;
    return -1;
  }

  bool isEmpty(void) override
  {
    if (_first)
      return false;
    else
      return true;
  }

  bool isFilled(void) override
  {
    if (_first)
      return true;
    else
      return false;
  }

  virtual int getSize(void) override { return _size; }

  ~VectorDeque() { delete[] _head; }
};

bool isNatural(const int num)
{
  if (num <= 0)
    return false;
  else
    return true;
}

bool isSimple(const int num)
{
  for (int i = 2; i < num; i++)
    if (num % i == 0) return false;
  return true;
}

Deque *simple(Deque *deque)
{
  Deque *tmp;

  if (deque->getSize())
    tmp = new VectorDeque(deque->getSize());
  else
    tmp = new ListDeque();

  while (deque->isFilled())
  {
    if (isSimple(deque->readStart())) tmp->addEnd(deque->readStart());
    deque->delStart();
  }

  return tmp;
}

Deque *sort(Deque *deque)
{
  Deque *tmp;

  if (deque->getSize())
    tmp = new VectorDeque(deque->getSize());
  else
    tmp = new ListDeque();

  while (deque->isFilled())
  {
    if (tmp->isEmpty() || tmp->readStart() < deque->readStart())
    {
      tmp->addStart(deque->readStart());
      deque->delStart();
    }
    else if (tmp->readEnd() > deque->readStart())
    {
      tmp->addEnd(deque->readStart());
      deque->delStart();
    }
    else
    {
      int n = deque->readStart();
      deque->delStart();

      while (tmp->readStart() > n)
      {
        deque->addStart(tmp->readStart());
        tmp->delStart();
      }

      tmp->addStart(n);
    }
  }

  return tmp;
}

class Menu
{
 private:
  Deque *_deque = nullptr;

  int _input(const string &message)
  {
    while (true)
    {
      int num;
      char c;
      cout << message;
      cin >> num;
      c = getchar();

      if (cin.fail() || c != '\n')
      {
        cout << "Ошибка ввода!" << endl;
        cin.clear();
        cin.ignore(32767, '\n');
      }
      else
      {
        return num;
      }
    }
  }

 public:
  void init(void)
  {
    Deque *tmpd;
    int choice, tmp;

    do
    {
      CLEAR;
      cout << "1. Дек с помощью связной структуры данных" << endl
           << "2. Дек с помощью векторной структуры данных" << endl;
      choice = _input("Ввод: ");

      switch (choice)
      {
        case 1:
          _deque = new ListDeque();
          break;
        case 2:
          tmp = _input("Введите размер очереди: ");
          while (tmp <= 0)
          {
            cout << "Ошибка ввода!" << endl;
            cin.get();
            tmp = _input("Введите размер очереди: ");
          }
          _deque = new VectorDeque(tmp);
          break;
        default:
          cout << "Ошибка ввода!" << endl;
      }
    } while (choice != 1 && choice != 2);

    do
    {
      CLEAR;
      cout << "1. Добавить число в начало дека" << endl
           << "2. Добавить число в конец дека" << endl
           << "3. Удалить число в начале дека" << endl
           << "4. Удалить число в конце дека" << endl
           << "5. Прочитать число в начале дека" << endl
           << "6. Прочитать число в конце дека" << endl
           << "7. Проверка заполнения дека" << endl
           << "8. Проверка пустоты дека" << endl
           << "9. Сортировка дека в порядке неубывания" << endl
           << "10. Удалить из дека элементы, оставив только простые числа" << endl
           << "11. Добавить в дек тестовые значения (5 -> 3 -> 4 -> 1 -> 2)" << endl
           << "0. Выход" << endl;
      choice = _input("Ввод: ");

      switch (choice)
      {
        case 1:
          tmp = _input("Введите натуральное число: ");
          if (!isNatural(tmp) || !_deque->addStart(tmp))
          {
            cout << "Очередь переполненна или число не является натуральным!" << endl;
            cin.get();
          }
          break;
        case 2:
          tmp = _input("Введите натуральное число: ");
          if (!isNatural(tmp) || !_deque->addEnd(tmp))
          {
            cout << "Очередь переполненна или число не является натуральным!" << endl;
            cin.get();
          }
          break;
        case 3:
          _deque->delStart();
          break;
        case 4:
          _deque->delEnd();
          break;
        case 5:
          if (_deque->isFilled())
            cout << "Прочитанное число: " << _deque->readStart() << endl;
          else
            cout << "Дек пустой" << endl;

          cin.get();
          break;
        case 6:
          if (_deque->isFilled())
            cout << "Прочитанное число: " << _deque->readEnd() << endl;
          else
            cout << "Дек пустой" << endl;

          cin.get();
          break;
        case 7:
          if (_deque->isFilled())
            cout << "Дек заполнен" << endl;
          else
            cout << "Дек пустой" << endl;
          cin.get();
          break;
        case 8:
          if (_deque->isEmpty())
            cout << "Дек пустой" << endl;
          else
            cout << "Дек заполнен" << endl;
          cin.get();
          break;
        case 9:
          tmpd = _deque;
          _deque = sort(tmpd);
          delete tmpd;
          break;
        case 10:
          tmpd = _deque;
          _deque = simple(tmpd);
          delete tmpd;
          break;
        case 11:
          _deque->addEnd(5);
          _deque->addEnd(3);
          _deque->addEnd(4);
          _deque->addEnd(1);
          _deque->addEnd(2);
        case 0:
          break;
        default:
          cout << "Неверный пункт меню!" << endl;
          cin.get();
          break;
      }
    } while (choice);
  }

  ~Menu() { delete _deque; }
};

int main()
{
  Menu *menu = new Menu();
  menu->init();
  delete menu;
  return 0;
}
