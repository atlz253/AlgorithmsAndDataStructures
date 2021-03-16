#include <iostream>

using namespace std;

class List
{
private:
    typedef struct node
    {
        int item;
        node *next = nullptr;
        node *prev = nullptr;
    } node;

    node *_first = nullptr;
    node *_last = nullptr;

public:
    void add_start(const int a)
    {
        if (!_first)
        {
            _first = new node;
            _first->item = a;
            _last = _first;
        }
        else
        {
            node *new_node = new node;
            new_node->item = a;
            new_node->next = _first;
            _first->prev = new_node;
            _first = new_node;
        }
    }

    void add_start(const int a, const unsigned int num)
    {
        if (num == 0)
        {
            add_start(a);
        }
        else
        {
            node
                *p = _first,
                *new_node = new node;

            for (int i = 0; i < num; i++)
            {
                if (p == nullptr)
                    break;
                else
                    p = p->next;
            }

            if (p)
            {
                new_node->item = a;
                new_node->next = p;
                new_node->prev = p->prev;
                p->prev->next = new_node;
                p->prev = new_node;
            }
            else
            {
                add_end(a);
            }
        }
    }

    void add_end(const int a)
    {
        if (!_last)
        {
            _last = new node;
            _last->item = a;
            _first = _last;
        }
        else
        {
            node *new_node = new node;
            new_node->item = a;
            new_node->prev = _last;
            _last->next = new_node;
            _last = new_node;
        }
    }

    friend ostream &operator<<(ostream &stream, const List *n)
    {
        if (n->_first)
        {
            node *p = n->_first;
            do
            {
                stream << p->item;
                if (p->next != NULL)
                    stream << " -> ";
                p = p->next;
            } while (p != NULL);
        }
        else
        {
            stream << "список пуст!" << endl;
        }
        return stream;
    }
};

int main()
{
    List *test = new List();
    test->add_start(1);
    test->add_end(2);
    test->add_end(3);
    test->add_end(4);
    test->add_end(5);
    test->add_end(6);
    test->add_start(100, 1);
    cout << test;

    delete test;
    return 0;
}
