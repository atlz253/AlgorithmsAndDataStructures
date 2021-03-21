#include <iostream>

#define CLEAR_CONSOLE 1
#define CLEAR          \
    if (CLEAR_CONSOLE) \
        system("clear");

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
    virtual int readStart(void) = 0;
    virtual int readEnd(void) = 0;
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
        int num;
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
            }
        }
    }

    int readStart(void) override
    {
        return _first->num;
    }

    int readEnd(void) override
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
        if (_first)
        {
            int tmp;
            node
                *f = _first,
                *s = nullptr,
                *min = nullptr;

            while (f)
            {
                s = f->next;
                min = f;
                while (s)
                {
                    if (s->num < min->num)
                        min = s;

                    s = s->next;
                }

                if (min != f)
                {
                    tmp = f->num;
                    f->num = min->num;
                    min->num = tmp;
                }

                f = f->next;
            }
        }
    }

    virtual void simple(void) override
    {
        if (_first)
        {
            int i;
            node
                *f = _first,
                *s = nullptr;

            while (f)
            {
                s = f->next;
                for (i = 2; i < f->num; i++)
                {
                    cout << f->num << ' ' << i << ' ' << f->num % i << endl;
                    if (f->num % i == 0)
                    {
                        cout << "Удаление " << f->num << endl;
                        if (f->prev)
                            f->prev->next = s;
                        else
                            _first = s;

                        if (s)
                            s->prev = f->prev;
                        else
                            _last = f;

                        delete f;
                        break;
                    }
                }
                f = s;
            }
        }
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

class VectorDeque : public Deque
{
private:
    int *_first = nullptr;
    int *_last = nullptr;
    int _size = 0;

public:
    bool addStart(const int a) override
    {
        if (_isNatural(a))
        {
            int *tmp;

            tmp = (int *)malloc((_size + 1) * sizeof(int)); // создаем новый массив
            if (tmp)
            {
                int *p = tmp;

                *tmp = a;                       // присваиваем новый элемент в начало массива
                for (int i = 0; i < _size; i++) // копируем данные из старого массива
                {
                    *(p + i + 1) = *(_first + i);
                }
                free(_first); // удаляем старый массив
                _first = tmp;
                _last = _first + _size;
                _size++;
                return true;
            }
            else
            {
                cout << "Ошибка выделения памяти!" << endl;
                cin.get();
                return false;
            }
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
            int *tmp;

            _size++;
            tmp = (int *)realloc(_first, _size * sizeof(int)); // выделение памяти для нового элемента

            if (tmp)
            {
                _first = tmp;

                if (_last) // если добавили первый элемент в дек
                    _last = _last + 1;
                else
                    _last = _first;

                *_last = a;
                return true;
            }
            else
            {
                _size--;
                cout << "Ошибка выделения памяти!" << endl;
                cin.get();
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    void delStart(void) override
    {
    }

    void delEnd(void) override
    {
    }

    int readStart(void) override
    {
        return *_first;
    }

    int readEnd(void) override
    {
        return *_last;
    }

    bool isEmpty(void) override
    {
        return false;
    }

    bool isFilled(void) override
    {
        return true;
    }

    void sort(void) override
    {
    }

    void simple(void) override
    {
    }

    ~VectorDeque()
    {
        free(_first);
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
                _deque = new VectorDeque();
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
                _deque->sort();
                break;
            case 10:
                _deque->simple();
                break;
            case 0:
                break;
            default:
                cout << "Неверный пункт меню!" << endl;
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
