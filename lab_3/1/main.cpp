#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

class Sorter final
{
private:
    int _N = 0;
    int *_arr = nullptr;

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
        unsigned long int compare = 0, operations = 0, start_time = clock(), end_time;

        for (int i = 0; i < _N; i++)
        {
            for (int *j = arr; j != arr + _N - 1; j++)
            {
                compare++;
                if (*j > *(j + 1))
                {
                    tmp = *j;
                    *j = *(j + 1);
                    *(j + 1) = tmp;
                    operations += 2;
                }
            }
        }
        end_time = clock();

        cout << "Пузырьковая сортировка: операций над элементами массива - " << operations << " количество сравнений - " << compare << " время - " << end_time - start_time << " мс" << endl;
    }

    void _shakerSort(int *arr)
    {
        int tmp;
        bool sort_or_not = true;
        unsigned long int compare = 0, operations = 0, start_time = clock(), end_time;

        do
        {
            sort_or_not = true;
            for (int *i = arr; i != arr + _N - 1; i++)
            {
                compare++;
                if (*i > *(i + 1))
                {
                    tmp = *i;
                    *i = *(i + 1);
                    *(i + 1) = tmp;
                    sort_or_not = false;
                    operations += 2;
                }
            }
            for (int *i = arr + _N - 1; i != arr; i--)
            {
                compare++;
                if (*i < *(i - 1))
                {
                    tmp = *i;
                    *i = *(i - 1);
                    *(i - 1) = tmp;
                    sort_or_not = false;
                    operations += 2;
                }
            }
        } while (sort_or_not == false);
        end_time = clock();

        cout << "Шейкерная сортировка: операций над элементами массива - " << operations << " количество сравнений - " << compare << " время - " << end_time - start_time << " мс" << endl;
    }

    void _quickSort(int *arr, int left, int right)
    {
        int pivot;
        int l = left, l_hold = l;
        int r = right, r_hold = r;
        pivot = arr[l];
        static unsigned long int compare = 0, operations = 0, start_time, end_time;

        if (l == 0 && r == _N - 1)
            start_time = clock();

        while (l < r)
        {
            compare++;
            while ((arr[r] >= pivot) && (l < r))
            {
                compare += 2;
                r--;
            }
            if (l != r)
            {
                compare++;
                arr[l] = arr[r];
                operations++;
                l++;
            }
            while ((arr[l] <= pivot) && (l < r))
            {
                compare += 2;
                l++;
            }
            if (l != r)
            {
                compare++;
                arr[r] = arr[l];
                operations++;
                r--;
            }
        }
        arr[l] = pivot;
        operations++;
        pivot = l;
        l = l_hold;
        r = r_hold;
        if (l < pivot)
        {
            compare++;
            _quickSort(arr, l, pivot - 1);
        }
        if (r > pivot)
        {
            compare++;
            _quickSort(arr, pivot + 1, r);
        }
        if (l == 0 && r == _N - 1)
        {
            end_time = clock();
            cout << "Быстрая сортировка: операций над элементами массива - " << operations << " количество сравнений - " << compare << " время - " << end_time - start_time << " мс" << endl;
        }
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
        _bubbleSort(_arrCpy());
        _shakerSort(_arrCpy());
        _quickSort(_arr, 0, _N - 1);

        cout << "Sorter: сортировка упорядоченного массива" << endl;
        _bubbleSort(_arrCpy());
        _shakerSort(_arrCpy());
        _quickSort(_arrCpy(), 0, _N - 1);

        cout << "Sorter: сортировка массива, упорядоченного в обратном порядке" << endl;
        _reverseArr();
        _bubbleSort(_arrCpy());
        _shakerSort(_arrCpy());
        _quickSort(_arrCpy(), 0, _N - 1);
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
                Sorter(10000).run();
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
