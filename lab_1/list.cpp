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

    void _add_start(const int a)
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

    void _add_end(const int a)
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

public:
    void add(const int a)
    {
        if (!_first)
        {
            _add_start(a);
        }
        else
        {
            node
                *p = _first, 
                *new_node = new node;
            new_node->item = a;

            while (p->next && p->item < a)
                p = p->next;
            
            if (p->next || p->item > a)
            {
                new_node->next = p;
                new_node->prev = p->prev;
                if (p->prev)
                    p->prev->next = new_node;
                else
                    _first = new_node;
            }
            else
            {
                _add_end(a);
            }
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
    test->add(1);
    test->add(3);
    test->add(4);
    test->add(2);
    test->add(10);
    test->add(7);
    test->add(2);
    test->add(4);
    test->add(4);


    cout << test;

    delete test;
    return 0;
}
