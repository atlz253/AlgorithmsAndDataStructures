#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>

const std::string WHITE = "\033[0;37m", RED = "\033[0;31m", GREEN = "\033[0;32m", YELLOW = "\033[0;33m",
                  GREY = "\033[0;90m";

using namespace std;

class Sorter final
{
 private:
  int _N = 0;
  int *_arr = nullptr;
  unsigned long int _time;
  unsigned long int _start_time;
  unsigned long int _otherCmp = 0;
  unsigned long int _primaryCmp = 0;
  unsigned long int _memory = 0;

  void _loadArr(void)
  {
    cout << "Sorter: считываем числа из test_numbers.txt" << endl;
    ifstream f;
    f.open("../test_numbers.txt", ios_base::in);

    for (int *i = _arr; i != _arr + _N; i++)
    {
      f >> *i;
    }

    f.close();
  }

  int *_arrCpy(void)
  {
    cout << GREY << "Sorter: создаем копию исходного массива" << WHITE << endl;
    int *cpy = new int[_N];

    for (int *i = _arr, *j = cpy; i != _arr + _N; i++, j++) *j = *i;

    return cpy;
  }

  void _clearResults(void)
  {
    _otherCmp = 0;
    _primaryCmp = 0;
    _memory = 0;
    _start_time = clock();
  }

  void _reverseArr()
  {
    cout << GREY << "Sorter: сортируем массив в обратном порядке" << WHITE << endl;
    int tmp;
    bool sort_or_not = true;
    _memory = sizeof(int) + sizeof(bool) + sizeof(int *);

    do
    {
      sort_or_not = true;
      for (int *i = _arr; i != _arr + _N - 1; i++)
      {
        _otherCmp++;
        if (*i < *(i + 1))
        {
          _primaryCmp++;
          tmp = *i;
          *i = *(i + 1);
          *(i + 1) = tmp;
          sort_or_not = false;
        }
      }
      for (int *i = _arr + _N - 1; i != _arr; i--)
      {
        _otherCmp++;
        if (*i > *(i - 1))
        {
          _primaryCmp++;
          tmp = *i;
          *i = *(i - 1);
          *(i - 1) = tmp;
          sort_or_not = false;
        }
      }
      _otherCmp++;
    } while (sort_or_not == false);
  }

  void _bubbleSort(int *arr)
  {
    int tmp;
    _memory = 3 * sizeof(int);

    for (int i = 0; i < _N; i++)
    {
      _otherCmp++;
      for (int *j = arr; j != arr + _N - 1; j++)
      {
        _otherCmp++;
        if (*j > *(j + 1))
        {
          _primaryCmp++;
          tmp = *j;
          *j = *(j + 1);
          *(j + 1) = tmp;
        }
      }
    }
  }

  void _shakerSort(int *arr)
  {
    int tmp;
    bool sort_or_not = true;
    _memory = sizeof(int) + sizeof(bool) + sizeof(int *);

    do
    {
      sort_or_not = true;
      for (int *i = arr; i != arr + _N - 1; i++)
      {
        _otherCmp++;
        if (*i > *(i + 1))
        {
          _primaryCmp++;
          tmp = *i;
          *i = *(i + 1);
          *(i + 1) = tmp;
          sort_or_not = false;
        }
      }
      for (int *i = arr + _N - 1; i != arr; i--)
      {
        _otherCmp++;
        if (*i < *(i - 1))
        {
          _primaryCmp++;
          tmp = *i;
          *i = *(i - 1);
          *(i - 1) = tmp;
          sort_or_not = false;
        }
      }
      _otherCmp++;
    } while (sort_or_not == false);
  }

  void _quickSort(int *arr)
  {
    const int M = log(_N) / log(2) + 1;
    int i, j, left, right, s, x, w;

    struct stack
    {
      int left, right;
    } * stack;
    stack = (struct stack *)malloc(M * sizeof(struct stack));

    s = 0;
    stack[0].left = 0;
    stack[0].right = _N - 1;

    _memory = sizeof(const int) + 7 * sizeof(int) + M * sizeof(struct stack);

    do /*выбор из стека последнего запроса*/
    {
      left = stack[s].left;
      right = stack[s].right;
      s--;
      do /*разделение а[left]… a[right]*/
      {
        i = left;
        j = right;
        x = arr[(left + right) / 2];
        do
        {
          while (arr[i] < x)
          {
            i++;
            _otherCmp++;
          }
          while (x < arr[j])
          {
          j--;
          _otherCmp++;
          }
          if (i <= j)
          {
            _primaryCmp++;
            w = arr[i];
            arr[i] = arr[j];
            arr[j] = w;
            i++;
            j--;
          }
          _otherCmp++;
        } while (i < j);
        if (i < right && right - i >= j - left) /*если правая часть не меньше левой*/
        {                                       /*запись в стек границ правой части*/
          _otherCmp++;
          s++;
          stack[s].left = i;
          stack[s].right = right;
          right = j; /*теперь left и right ограничивают левую часть*/
        }
        else if (j > left && j - left > right - i) /*если левая часть больше правой*/
        {                                          /*запись в стек границ левой части*/
          _otherCmp++;
          s++;
          stack[s].left = left;
          stack[s].right = j;
          left = i; /*теперь left и right ограничивают правую часть*/
        }
        else
          left = right; /*делить больше нечего, интервал "схлопывается"*/
        _otherCmp++;
      } while (left < right);
      _otherCmp++;
    } while (s > -1);
    free(stack);
  }

  void _naturalMerge(int *arr)
  {
    int split; /* индекс, по которому делим массив */
    int end, *p = arr, *tmp;
    char flag = 0, sorted = 0;
    int pos1, pos2, pos3;
    tmp = (int *)malloc(_N * sizeof(int));
    _memory = 5 * sizeof(int) + 2 * sizeof(int *) + _N * sizeof(int);

    do /* если есть более 1 элемента */
    {
      end = _N;
      pos2 = pos3 = 0;

      do
      {
        p += pos2;
        end = _N - pos3;
        for (split = 1; split < end && p[split - 1] <= p[split]; split++) _otherCmp += 2; /*первая серия*/
        if (split == _N)
        {
          _otherCmp++;
          sorted = 1;
          break;
        }
        pos1 = 0;
        pos2 = split;
        while (pos1 < split && pos2 < end) /*идет слияние, пока есть хоть один элемент в каждой серии*/
        {
          _otherCmp += 3;
          if (p[pos1] < p[pos2])
          {
            tmp[pos3++] = p[pos1++];
            _primaryCmp++;
          }
          else
          {
            tmp[pos3++] = p[pos2++];
            _primaryCmp += 2;
            if (p[pos2] < p[pos2 - 1]) break;
          }
        }
        /* одна последовательность закончилась - копировать остаток другой в конец буфера */
        while (pos2 < end && tmp[pos3 - 1] <= p[pos2]) /* пока вторая последовательность не пуста */
        {
          _otherCmp += 2;
          tmp[pos3++] = p[pos2++];
        }
        while (pos1 < split) /* пока первая последовательность не пуста */
        {
          _otherCmp++;
          tmp[pos3++] = p[pos1++];
        }
        _otherCmp++;
      } while (pos3 < _N);
      if (sorted) break;
      p = tmp;
      tmp = arr;
      arr = p;
      flag = !flag;
      _otherCmp++;
    } while (split < _N);
    if (flag)
    {
      for (pos1 = 0; pos1 < _N; pos1++)
      {
      _otherCmp++;
      tmp[pos1] = arr[pos1];
      }
      free(arr);
    }
    else
      free(tmp);
  }

  void _printArr(int *arr)
  {
    for (int *i = arr; i != arr + _N; i++) cout << *i << ' ';
    cout << endl;
  }

  void _printResults(std::string name)
  {
    cout << GREEN << name << ": основных сравнений - " << _primaryCmp
         << " вспомогательных сравнений - " << _otherCmp << " время - " << _time << " мс"
         << " объем требуемой доп памяти - " << _memory << WHITE << endl;
  }

 public:
  Sorter(int N)
  {
    cout << "Sorter: создание массива на " << N << " элементов" << endl;
    _N = N;
    _arr = new int[_N];
    _loadArr();
  }

  void run(void)
  {
    int *tmp;

    cout << endl << endl << YELLOW << "Sorter: сортировка неупорядоченного массива" << WHITE << endl;
    tmp = _arrCpy();
    _clearResults();
    _bubbleSort(tmp);
    _time = clock() - _start_time;
    _printResults("Пузырьковая сортировка");
    delete tmp;

    tmp = _arrCpy();
    _clearResults();
    _shakerSort(tmp);
    _time = clock() - _start_time;
    _printResults("Шейкерная сортировка");
    delete tmp;

    tmp = _arrCpy();
    _clearResults();
    _quickSort(tmp);
    _time = clock() - _start_time;
    _printResults("Быстрая сортировка");
    delete tmp;

    _clearResults();
    _naturalMerge(_arr);
    _time = clock() - _start_time;
    _printResults("Сортировка естественным слиянием");


    cout << endl << endl << YELLOW << "Sorter: сортировка упорядоченного массива" << WHITE << endl;
    _clearResults();
    _bubbleSort(_arr);
    _time = clock() - _start_time;
    _printResults("Пузырьковая сортировка");

    _clearResults();
    _shakerSort(_arr);
    _time = clock() - _start_time;
    _printResults("Шейкерная сортировка");

    _clearResults();
    _quickSort(_arr);
    _time = clock() - _start_time;
    _printResults("Быстрая сортировка");

    _clearResults();
    _naturalMerge(_arr);
    _time = clock() - _start_time;
    _printResults("Сортировка естественным слиянием");

    cout << endl << endl << YELLOW << "Sorter: сортировка массива, упорядоченного в обратном порядке" << WHITE << endl;
    _reverseArr();

    tmp = _arrCpy();
    _clearResults();
    _bubbleSort(tmp);
    _time = clock() - _start_time;
    _printResults("Пузырьковая сортировка");
    delete tmp;

    tmp = _arrCpy();
    _clearResults();
    _shakerSort(tmp);
    _time = clock() - _start_time;
    _printResults("Шейкерная сортировка");
    delete tmp;

    tmp = _arrCpy();
    _clearResults();
    _quickSort(tmp);
    _time = clock() - _start_time;
    _printResults("Быстрая сортировка");
    delete tmp;

    _clearResults();
    _naturalMerge(_arr);
    _time = clock() - _start_time;
    _printResults("Сортировка естественным слиянием");
  }

  ~Sorter() { delete _arr; }
};

class Menu final
{
 private:
 public:
  int choice;

  int run(void)
  {
    while (true)
    {
      cout << "1. тест массива на 10 элементов" << endl
           << "2. тест массива на 10000 элементов" << endl
           << "3. тест массива на 50000 элементов" << endl
           << "4. тест массива на 100000 элементов" << endl
           << "5. тест массива на 150000 элементов" << endl
           << "0. выход" << endl;
      cin >> choice;

      switch (choice)
      {
        case 1:
          Sorter(10).run();
          break;
        case 2:
          Sorter(10000).run();
          break;
        case 3:
          Sorter(50000).run();
          break;
        case 4:
          Sorter(100000).run();
          break;
        case 5:
          Sorter(150000).run();
          break;
        case 0:
          return 1;
        default:
          cout << "Ошибка ввода!" << endl;
          break;
      }
    }
  }
};

int main() { return Menu().run(); }
