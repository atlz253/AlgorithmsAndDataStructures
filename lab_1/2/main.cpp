#include <iostream>

#define CLEAR system("clear");

using namespace std;

class Deque
{
protected:
    bool _isNatural(const int num)
    {
        if (num <= 0)
            return false;
        else
            return true;
    }

public:
    virtual bool addStart(const int a) = 0;
    virtual bool addEnd(const int a) = 0;
    virtual void delStart(void) = 0;
    virtual void delEnd(void) = 0;
    virtual unsigned int readStart(void) = 0;
    virtual unsigned int readEnd(void) = 0;
    virtual bool isEmpty(void) = 0;
    virtual bool isFilled(void) = 0;
    virtual void sort(void) = 0;
    virtual void simple(void) = 0;
    virtual ~Deque() = default;
};

class ListDeque : public Deque
{
private:
    typedef struct node
    {
        unsigned int num;
        node *next = nullptr;
        node *prev = nullptr;
    } node;

    node *_first = nullptr;
    node *_last = nullptr;

public:
    bool addStart(const int a) override
    {
        if (_isNatural(a))
        {
            if (!_first)
            {
                _first = new node;
                _first->num = a;
                _last = _first;
            }
            else
            {
                node *new_node = new node;
                new_node->num = a;
                new_node->next = _first;
                _first->prev = new_node;
                _first = new_node;
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    bool addEnd(const int a) override
    {
        if (_isNatural(a))
        {
            if (!_last)
            {
                _last = new node;
                _last->num = a;
                _first = _last;
            }
            else
            {
                node *new_node = new node;
                new_node->num = a;
                new_node->prev = _last;
                _last->next = new_node;
                _last = new_node;
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    void delStart(void) override
    {
        if (_last)
        {
            node *p = _last->prev;
            p->next = nullptr;
            delete _last;
            _last = p;
        }
    }

    void delEnd(void) override
    {
        if (_first)
        {
            node *p = _first->next;
            p->prev = nullptr;
            delete _first;
            _first = p;
        }
    }

    unsigned int readStart(void) override
    {
        return _first->num;
    }

    unsigned int readEnd(void) override
    {
        return _last->num;
    }

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

    virtual void sort(void) override
    {
    }

    virtual void simple(void) override
    {
    }

    ~ListDeque()
    {
        while (_first)
        {
            _last = _first->next; // сохраняем ссылку на следующий элемент
            delete _first;        // удаляем текущий
            _first = _last;
        }
    }
};

class Menu
{
private:
    Deque *_deque = nullptr;

    void _input(const string &message, int &num)
    {
        while (true)
        {
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
                break;
            }
        }
    }

public:
    void init(void)
    {
        int choice, a;

        do
        {
            CLEAR;
            cout << "1. Дек с помощью связной структуры данных" << endl
                 << "2. Дек с помощью векторной структуры данных" << endl;
            _input("Ввод: ", choice);

            switch (choice)
            {
            case 1:
                _deque = new ListDeque();
                break;
            case 2:
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
                 << "0. Выход" << endl;
            _input("Ввод: ", choice);

            switch (choice)
            {
            case 1:
                _input("Введите натуральное число: ", a);
                if (!_deque->addStart(a))
                {
                    cout << "Число не является натуральным!" << endl;
                    cin.get();
                }
                break;
            case 2:
                _input("Введите натуральное число: ", a);
                if (!_deque->addEnd(a))
                {
                    cout << "Число не является натуральным!" << endl;
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
                cout << "Прочитанное число: " << _deque->readStart() << endl;
                cin.get();
                break;
            case 6:
                cout << "Прочитанное число: " << _deque->readEnd() << endl;
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
            }
        } while (choice);
    }

    ~Menu()
    {
        delete _deque;
    }
};

int main()
{
    Menu *menu = new Menu();
    menu->init();
    delete menu;
    return 0;
}
