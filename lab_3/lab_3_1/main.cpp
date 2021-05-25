#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

class Sorter final
{
private:
    int _N = 0;
    int *_arr = nullptr;
    unsigned long int _time;
    unsigned long int _start_time;
    unsigned long int _compare = 0;
    unsigned long int _operations = 0;

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
        cout << "Sorter: создаем копию исходного массива" << endl;
        int *cpy = new int[_N];

        for (int *i = _arr, *j = cpy; i != _arr + _N; i++, j++)
            *j = *i;

        return cpy;
    }

    void _clearResults(void)
    {
        _compare = 0;
        _operations = 0;
        _start_time = clock();
    }

    void _reverseArr(void)
    {
        cout << "Sorter: сортируем массив в обратном порядке" << endl;
        int tmp;

        for (int i = 0; i < _N; i++)
            for (int *j = _arr; j != _arr + _N - 1; j++)
            {

                if (*j < *(j + 1))
                {
                    tmp = *j;
                    *j = *(j + 1);
                    *(j + 1) = tmp;
                }
            }
    }

    void _bubbleSort(int *arr)
    {
        int tmp;

        for (int i = 0; i < _N; i++)
        {
            _compare++;
            for (int *j = arr; j != arr + _N - 1; j++)
            {
                _compare++;
                if (*j > *(j + 1))
                {
                    _compare++;
                    tmp = *j;
                    *j = *(j + 1);
                    *(j + 1) = tmp;
                    _operations += 2;
                }
            }
        }
    }

    void _shakerSort(int *arr)
    {
        int tmp;
        bool sort_or_not = true;

        do
        {
            sort_or_not = true;
            for (int *i = arr; i != arr + _N - 1; i++)
            {
                _compare++;
                if (*i > *(i + 1))
                {
                    _compare++;
                    tmp = *i;
                    *i = *(i + 1);
                    *(i + 1) = tmp;
                    sort_or_not = false;
                    _operations += 2;
                }
            }
            for (int *i = arr + _N - 1; i != arr; i--)
            {
                _compare++;
                if (*i < *(i - 1))
                {
                    _compare++;
                    tmp = *i;
                    *i = *(i - 1);
                    *(i - 1) = tmp;
                    sort_or_not = false;
                    _operations += 2;
                }
            }
            _compare++;
        } while (sort_or_not == false);
    }

    void _quickSort(int *arr, int left, int right)
    {
        int pivot;
        int l_hold = left;
        int r_hold = right;
        pivot = arr[left];

        while (left < right)
        {
            _compare++;
            while ((arr[right] >= pivot) && (left < right))
            {
                _compare += 2;
                right--;
            }
            if (left != right)
            {
                _compare++;
                arr[left] = arr[right];
                _operations++;
                left++;
            }
            while ((arr[left] <= pivot) && (left < right))
            {
                _compare += 2;
                left++;
            }
            if (left != right)
            {
                _compare++;
                arr[right] = arr[left];
                _operations++;
                right--;
            }
        }
        arr[left] = pivot;
        _operations++;
        pivot = left;
        left = l_hold;
        right = r_hold;
        if (left < pivot)
        {
            _compare++;
            _quickSort(arr, left, pivot - 1);
        }
        if (right > pivot)
        {
            _compare++;
            _quickSort(arr, pivot + 1, right);
        }
    }

    void _naturalMerge(int *arr)
    {
        int split;                   /* индекс, по которому делим массив */
        int last, end, i, *p=arr, *tmp;
        char flag = 0;
        int pos1, pos2, pos3;
        tmp = new int[_N];
        do                 /* если есть более 1 элемента */
        {
            _printArr(_arr);
            end = _N; pos2 = pos3 = 0;
            do
            {
                p += pos2; end = _N - pos3;
                for (split=1; split < end && p[split-1] <= p[split]; split++); /*первая серия*/
                if (split == _N) break;
                pos1 = 0; pos2 = split;
                while ( pos1 < split && pos2 < end ) 	/*идет слияние, пока есть хоть один элемент в каждой серии*/
                {
                    if (p[pos1] < p[pos2])
                        tmp[pos3++] = p[pos1++];
                    else
                    {
                        tmp[pos3++] = p[pos2++];
                        if (p[pos2] < p[pos2-1]) break;
                    }
                }
                /* одна последовательность закончилась - копировать остаток другой в конец буфера */
                while ( pos2 < end && tmp[pos3-1]<=p[pos2] )  			 /* пока вторая последовательность не пуста */
                    tmp[pos3++] = p[pos2++];
                while ( pos1 < split )  		/* пока первая последовательность не пуста */
                    tmp[pos3++] = p[pos1++];
            }
            while ( pos3 < _N );
            p = tmp;
            tmp = arr;
            arr = p;
            flag = !flag;
            _printArr(_arr);
        }
        while (split<_N);
        if (flag)
            for (pos1 = 0; pos1 < _N; pos1++)
                arr[pos1] = tmp[pos1];
        delete tmp;
    }

    void _printArr(int *arr)
    {
        for (int *i = arr; i != arr + _N; i++)
            cout << *i << ' ';
        cout << endl;
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
        cout << "Sorter: сортировка неупорядоченного массива" << endl;
//        _clearResults();
//        _bubbleSort(_arrCpy());
//        _time = clock() - _start_time;
//        cout << "Пузырьковая сортировка: операций над элементами массива - " << _operations << " количество сравнений - " << _compare << " время - " << _time << " мс" << endl;

//        _clearResults();
//        _shakerSort(_arrCpy());
//        _time = clock() - _start_time;
//        cout << "Шейкерная сортировка: операций над элементами массива - " << _operations << " количество сравнений - " << _compare << " время - " << _time << " мс" << endl;

//        _clearResults();
//        _quickSort(_arr, 0, _N - 1);
//        _time = clock() - _start_time;
//        cout << "Быстрая сортировка: операций над элементами массива - " << _operations << " количество сравнений - " << _compare << " время - " << _time << " мс" << endl;

        _clearResults();
        _naturalMerge(_arr);
        _time = clock() - _start_time;
        cout << "Сортировка естественным слиянием: операций над элементами массива - " << _operations << " количество сравнений - " << _compare << " время - " << _time << " мс" << endl;


        cout << "Sorter: сортировка упорядоченного массива" << endl;
//        _clearResults();
//        _bubbleSort(_arr);
//        _time = clock() - _start_time;
//        cout << "Пузырьковая сортировка: операций над элементами массива - " << _operations << " количество сравнений - " << _compare << " время - " << _time << " мс" << endl;

//        _clearResults();
//        _shakerSort(_arr);
//        _time = clock() - _start_time;
//        cout << "Шейкерная сортировка: операций над элементами массива - " << _operations << " количество сравнений - " << _compare << " время - " << _time << " мс" << endl;

//        _clearResults();
//        _quickSort(_arr, 0, _N - 1);
//        _time = clock() - _start_time;
        cout << "Быстрая сортировка: операций над элементами массива - " << _operations << " количество сравнений - " << _compare << " время - " << _time << " мс" << endl;

        cout << "Sorter: сортировка массива, упорядоченного в обратном порядке" << endl;
        _reverseArr();

//        _clearResults();
//        _bubbleSort(_arrCpy());
//        _time = clock() - _start_time;
//        cout << "Пузырьковая сортировка: операций над элементами массива - " << _operations << " количество сравнений - " << _compare << " время - " << _time << " мс" << endl;

//        _clearResults();
//        _shakerSort(_arrCpy());
//        _time = clock() - _start_time;
//        cout << "Шейкерная сортировка: операций над элементами массива - " << _operations << " количество сравнений - " << _compare << " время - " << _time << " мс" << endl;

//        _clearResults();
//        _quickSort(_arrCpy(), 0, _N - 1);
//        _time = clock() - _start_time;
//        cout << "Быстрая сортировка: операций над элементами массива - " << _operations << " количество сравнений - " << _compare << " время - " << _time << " мс" << endl;
    }

    ~Sorter()
    {
        delete _arr;
    }
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
            cout << "1. тест массива на 10000 элементов" << endl
                 << "2. тест массива на 50000 элементов" << endl
                 << "0. выход" << endl;
            cin >> choice;

            switch (choice)
            {
            case 1:
                Sorter(10).run();
                break;
            case 2:
                Sorter(50000).run();
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

int main()
{
    return Menu().run();
}
