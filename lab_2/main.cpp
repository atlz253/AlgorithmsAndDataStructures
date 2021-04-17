/*
Найти все вершины орграфа, недостижимые от заданной его вершины
*/

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class GraphMatrix
{
private:
    bool **_matrix = nullptr;
    int _vertex = 0;

public:
    GraphMatrix(const int vertex)
    {
        _vertex = vertex;
        _matrix = new bool*[_vertex];

        bool **pp, *p;

        for (pp = _matrix; pp != _matrix + _vertex; pp++)
        {
            *pp = new bool[_vertex];

            for (p = *pp; p != *pp + _vertex; p++)
                *p = false;
        }
    }

    bool set(const int out, const int in)
    {
        if (_vertex < in || _vertex < out)
        {
            return false;
        }
        else
        {
            *(*(_matrix + in - 1) + out - 1) = !*(*(_matrix + in - 1) + out - 1);
            return true;
        }
    }

    void print(void)
    {
        bool **pp, *p;

        for (pp = _matrix; pp != _matrix + _vertex; pp++)
        {
            for (p = *pp; p != *pp + _vertex; p++)
                if (*p)
                    cout << "1 ";
                else
                    cout << "0 ";

            cout << endl;
        }
    }

    ~GraphMatrix() //TODO: реализовать деструктор
    {
    }
};

class Menu
{
private:
    GraphMatrix *_graph = nullptr;

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

    void _newGraph(void)
    {
        // string fname;
        // cout << "Введите название графа: ";
        // cin >> fname;

        int choice;
        _graph = new GraphMatrix(_input("Введите количество вершин: ")); //TODO: не открыт ли другой граф?

        do
        {
            _graph->print();
            cout << "1. добавить/убрать ребро" << endl
                 << "0. выход" << endl;
            choice = _input("Ввод: ");

            switch (choice)
            {
            case 1:
                if (!_graph->set(_input("Введите входящую вершину: "), _input("Введите исходящую вершину: "))) //TODO: защита от ввода нуля
                {
                    cout << "Не удалось добавить ребро!" << endl;
                    cin.get();
                }
                break;
            case 0:
                break;
            default:
                cout << "Ошибка ввода!" << endl;
                break;
            }
        } while (choice);

        // ofstream *fout = new ofstream(fname, ios_base::out | ios_base::binary | ios_base::trunc);
    }

public:
    void init(void)
    {
        int choice;

        do
        {
            cout << "1. создать/перезаписать граф" << endl
                 << "0. выход" << endl;
            choice = _input("Ввод: ");

            switch (choice)
            {
            case 1:
                _newGraph();
                break;
            case 0:
                break;
            default:
                cout << "Ошибка ввода!" << endl;
                break;
            }
        } while (choice);
    }
};

int main()
{
    Menu *menu = new Menu();
    menu->init();
    delete menu;
    return 0;
}
