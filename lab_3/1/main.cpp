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
                 << "0. выход" << endl;
            cin >> choice;

            switch (choice)
            {
            case 1:
                Sorter(10000).run();
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
