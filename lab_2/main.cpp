/*
Найти все вершины орграфа, недостижимые от заданной его вершины
*/

#include <string>
#include <fstream>
#include <iostream>

bool debug = false;

using namespace std;

class GraphMatrix
{
private:
    char **_matrix = nullptr;
    char _vertex = 0;

public:
    GraphMatrix(const char vertex)
    {
        _vertex = vertex;
        _matrix = new char *[_vertex];

        char i, j;

        for (i = 0; i < _vertex; i++)
        {
            *(_matrix + i) = new char[_vertex];

            for (j = 0; j < _vertex; j++)
                if (i != j)
                    *(*(_matrix + i) + j) = 0;
                else
                    *(*(_matrix + i) + j) = '-';
        }
    }

    GraphMatrix(const string fname)
    {
        ifstream *fin = new ifstream(fname, ios_base::in);
        char **pp, *p;

        *fin >> _vertex;
        _matrix = new char *[_vertex];

        for (pp = _matrix; pp != _matrix + _vertex; pp++)
        {
            *pp = new char[_vertex];

            for (p = *pp; p != *pp + _vertex; p++)
                fin->get(*p);
        }

        fin->close();
        delete fin;
    }

    bool set(const int out, const int in)
    {
        if (_vertex < in || _vertex < out || in == out)
        {
            return false;
        }
        else
        {
            char *p = *(_matrix + in - 1) + out - 1;

            if (*p)
                *p = 0;
            else
                *p = 1;

            return true;
        }
    }

    void print(void)
    {
        char **pp, *p;

        for (pp = _matrix; pp != _matrix + _vertex; pp++)
        {
            for (p = *pp; p != *pp + _vertex; p++)
                if (*p == '-')
                    cout << *p << ' ';
                else
                    cout << (int)*p << ' ';

            cout << endl;
        }
    }

    void unattainable(const char vertex)
    {
        char i, j, *mark = new char[_vertex];
        for (i = 0; i < _vertex; i++)
            if (i == vertex - 1)
                *(mark + i) = 1;
            else
                *(mark + i) = 0;

        for (i = 0; i < _vertex; i++)
        {
            if (*(mark + i) == 1)
            {
                for (j = 0; j < _vertex; j++)
                {
                    if (*(*(_matrix + i) + j) == 1 && *(mark + j) == 0)
                        *(mark + j) = 1;

                    if (debug)
                        cout << "i=" << (int)i << ' ' << (int)*(*(_matrix + i) + j) << ' ' << "j=" << (int)j << ' ' << (int)*(mark + j) << endl;
                }
                if (debug)
                    cout << endl;

                *(mark + i) = 2;
                i = 0;
            }
        }

        cout << "Недостижимые вершины: ";
        for (i = 0; i < _vertex; i++)
            if (*(mark + i) == 0)
                cout << '(' << i + 1 << ") ";
        cout << endl;

        delete mark;
    }

    void save(const string fname)
    {
        ofstream *fout = new ofstream(fname, ios_base::out | ios_base::trunc);
        char **pp, *p;

        *fout << _vertex;
        for (pp = _matrix; pp != _matrix + _vertex; pp++)
            for (p = *pp; p != *pp + _vertex; p++)
                *fout << *p;

        fout->close();
        delete fout;
    }

    ~GraphMatrix() //TODO: реализовать деструктор
    {
    }
};

class GraphList
{
private:
    typedef struct node
    {
        char vertex;
        node *next = nullptr;
    } node;
    node **_list = nullptr;
    char _vertex = 0;

public:
    GraphList(const string fname)
    {
        node *p;
        char i, j, tmp;
        ifstream *fin = new ifstream(fname, ios_base::in);

        *fin >> _vertex;
        _list = new node *[_vertex];

        for (i = 0; i < _vertex; i++)
        {
            *(_list + i) = new node;
            p = *(_list + i);
            p->vertex = i + 1;
            if (debug)
                cout << '[' << (int)p->vertex << "]";

            for (j = 0; j < _vertex; j++)
            {
                fin->get(tmp);
                if (tmp == 1)
                {
                    p->next = new node;
                    p = p->next;
                    p->vertex = j + 1;
                    if (debug)
                        cout << " -> " << (int)p->vertex;
                }
            }

            if (debug)
                cout << endl;
        }

        fin->close();
        delete fin;
    }

    void print(void)
    {
        node **pp, *p;

        for (pp = _list; pp != _list + _vertex; pp++)
        {
            for (p = *pp; p != nullptr; p = p->next)
            {
                if (p == *pp)
                    cout << '[' << (int)p->vertex << "]";
                else
                    cout << (int)p->vertex << ' ';

                if (p->next != nullptr)
                    cout << " -> ";
            }
            cout << endl;
        }
    }
};

class Menu
{
private:
    GraphMatrix *_matrix = nullptr;
    GraphList *_list = nullptr;

    char _input(const string &message)
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
        char choice;
        _matrix = new GraphMatrix(_input("Введите количество вершин: ")); //TODO: не открыт ли другой граф?

        do
        {
            _matrix->print();
            cout << "1. добавить/убрать ребро" << endl
                 << "0. выход" << endl;
            choice = _input("Ввод: ");

            if (choice == 1)
            {
                if (!_matrix->set(_input("Введите входящую вершину: "), _input("Введите исходящую вершину: "))) //TODO: защита от ввода нуля
                {
                    cout << "Не удалось добавить ребро!" << endl;
                    cin.get();
                }
            }
            else if (choice != 0)
            {
                cout << "Ошибка ввода!" << endl;
            }
        } while (choice);
    }

public:
    void init(void)
    {
        char choice;

        do
        {
            cout << "1. создать/перезаписать граф" << endl
                 << "2. сохранить граф в файл" << endl
                 << "3. загрузить граф из файла" << endl
                 << "4. вывести матрицу смежностей" << endl
                 << "5. найти все вершины орграфа, недостижимые от заданной его вершины" << endl
                 << "6. отладочная печать [" << debug << ']' << endl
                 << "7. вывести список смежностей" << endl
                 << "0. выход" << endl;
            choice = _input("Ввод: ");

            if (choice == 1)
            {
                _newGraph();
            }
            else if (choice == 2)
            {
                string fname;
                cout << "Введите название графа: ";
                cin >> fname;
                _matrix->save(fname);
            }
            else if (choice == 3)
            {
                string fname;
                cout << "Введите название графа: ";
                cin >> fname;
                _matrix = new GraphMatrix(fname);
                _list = new GraphList(fname);
            }
            else if (choice == 4)
            {
                _matrix->print();
                cin.get();
            }
            else if (choice == 5)
            {
                _matrix->unattainable(_input("Введите номер вершины: "));
                cin.get();
            }
            else if (choice == 6)
            {
                debug = !debug;
            }
            else if (choice == 7)
            {
                _list->print();
            }
            else if (choice != 0)
            {
                cout << "Ошибка ввода!" << endl;
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