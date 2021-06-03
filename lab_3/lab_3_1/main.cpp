#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

#define N1 10000
#define N2 50000
#define N3 100000
#define N4 150000

using namespace std;

const string WHITE = "\033[0;37m", RED = "\033[0;31m", GREEN = "\033[0;32m", YELLOW = "\033[0;33m", GREY = "\033[0;90m";

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

  void _loadArr(std::string filePath)
  {
    cout << "Sorter: считываем числа из test_numbers.txt" << endl;
    ifstream f;
    f.open(filePath, ios_base::in);

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
    int i, j, x;
    _memory = sizeof(int) * 3;

    for (i = 1, _otherCmp++; i < _N; i++, _otherCmp++)
      for (j = _N - 1, _otherCmp++; j >= i; j--, _otherCmp++)
        if (++_primaryCmp && arr[j - 1] > arr[j])
        {
          x = arr[j - 1];
          arr[j - 1] = arr[j];
          arr[j] = x;
        }
  }

  void _shakerSort(int *arr)
  {
    int j, k = _N - 1, left = 1, right = _N - 1, x;
    _memory = sizeof(int) * 5;

    do
    {
      for (j = right, _otherCmp++; j >= left; j--, _otherCmp++) /*сначала просматриваем справа налево*/
        if (++_primaryCmp && arr[j - 1] > arr[j])
        {
          x = arr[j - 1];
          arr[j - 1] = arr[j];
          arr[j] = x;
          k = j;
        }
      left = k + 1;

      for (j = left, _otherCmp++; j <= right; j++, _otherCmp++) /*а теперь просматриваем слева направо*/
        if (++_primaryCmp && arr[j - 1] > arr[j])
        {
          x = arr[j - 1];
          arr[j - 1] = arr[j];
          arr[j] = x;
          k = j;
        }
      right = k - 1;
    } while (++_otherCmp && left < right); /*и так до тех пор, пока есть что просматривать*/
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
          while (++_primaryCmp && arr[i] < x) i++;
          while (++_primaryCmp && x < arr[j]) j--;

          if (++_otherCmp && i <= j)
          {
            w = arr[i];
            arr[i] = arr[j];
            arr[j] = w;
            i++;
            j--;
          }

        } while (++_otherCmp && i < j);

        if (++_otherCmp && i < right && ++_otherCmp && right - i >= j - left) /*если правая часть не меньше левой*/
        { /*запись в стек границ правой части*/
          s++;
          stack[s].left = i;
          stack[s].right = right;
          right = j; /*теперь left и right ограничивают левую часть*/
        }
        else if (++_otherCmp && j > left && ++_otherCmp && j - left > right - i) /*если левая часть больше правой*/
        { /*запись в стек границ левой части*/
          s++;
          stack[s].left = left;
          stack[s].right = j;
          left = i; /*теперь left и right ограничивают правую часть*/
        }
        else
          left = right; /*делить больше нечего, интервал "схлопывается"*/
      } while (++_otherCmp && left < right);
    } while (++_otherCmp && s > -1);
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
        for (split = 1, _otherCmp++, _primaryCmp++; split < end && p[split - 1] <= p[split];
             split++, _otherCmp++, _primaryCmp++)
          ; /*первая серия*/
        if (++_otherCmp && split == _N)
        {
          sorted = 1;
          break;
        }
        pos1 = 0;
        pos2 = split;
        while (++_otherCmp && pos1 < split && ++_otherCmp &&
               pos2 < end) /*идет слияние, пока есть хоть один элемент в каждой серии*/
        {
          if (++_primaryCmp && p[pos1] < p[pos2])
          {
            tmp[pos3++] = p[pos1++];
          }
          else
          {
            tmp[pos3++] = p[pos2++];
            if (++_primaryCmp && p[pos2] < p[pos2 - 1]) break;
          }
        }
        /* одна последовательность закончилась - копировать остаток другой в конец буфера */
        while (++_otherCmp && pos2 < end && ++_primaryCmp &&
               tmp[pos3 - 1] <= p[pos2]) /* пока вторая последовательность не пуста */
          tmp[pos3++] = p[pos2++];
        while (++_otherCmp && pos1 < split) /* пока первая последовательность не пуста */
          tmp[pos3++] = p[pos1++];
      } while (++_otherCmp && pos3 < _N);
      if (sorted) break;
      p = tmp;
      tmp = arr;
      arr = p;
      flag = !flag;
    } while (++_otherCmp && split < _N);

    if (flag)
    {
      for (pos1 = 0, _otherCmp++; pos1 < _N; pos1++, _otherCmp++)
      {
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
    cout << GREEN << name << ": основных сравнений - " << _primaryCmp << " вспомогательных сравнений - " << _otherCmp
         << " время - " << _time << " объем требуемой доп памяти - " << _memory << WHITE << endl;
  }

 public:
  Sorter(int N, std::string filePath)
  {
    cout << "Sorter: создание массива на " << N << " элементов" << endl;
    _N = N;
    _arr = new int[_N];
    _loadArr(filePath);
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
           << "2. тест массива на " << N1 << " элементов" << endl
           << "3. тест массива на " << N2 << " элементов" << endl
           << "4. тест массива на " << N3 << " элементов" << endl
           << "5. тест массива на " << N4 << " элементов" << endl
           << "6. тест массива массива с 10 повторными ключами" << endl
           << "7. тест массива массива с 100 повторными ключами" << endl
           << "8. тест массива массива с 500 повторными ключами" << endl
           << "9. тест массива массива с 1000 повторными ключами" << endl
           << "0. выход" << endl;
      cin >> choice;

      switch (choice)
      {
        case 1:
          Sorter(10, "../test_numbers.txt").run();
          break;
        case 2:
          Sorter(N1, "../test_numbers.txt").run();
          break;
        case 3:
          Sorter(N2, "../test_numbers.txt").run();
          break;
        case 4:
          Sorter(N3, "../test_numbers.txt").run();
          break;
        case 5:
          Sorter(N4, "../test_numbers.txt").run();
          break;
        case 6:
          Sorter(N4, "N410.txt").run();
          break;
        case 7:
          Sorter(N4, "N4100.txt").run();
          break;
        case 8:
          Sorter(N4, "N4500.txt").run();
          break;
        case 9:
          Sorter(N4, "N41000.txt").run();
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
