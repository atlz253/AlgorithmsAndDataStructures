#include <iostream>

using namespace std;

class Node
{
public:
    int item;
    Node *next = NULL;
    Node *prev = NULL;
};

class List
{
private:
    Node *_first = NULL;
    Node *_last = NULL;

public:
    void add_start(const int a)
    {
        if (_first == NULL)
        {
            _first = new Node();
            _first->item = a;
            _last = _first;
        }
        else
        {
            Node *new_node = new Node();
            new_node->item = a;
            new_node->next = _first;
            _first->prev = new_node;
            _first = new_node;
        }
    }

    void add_end(const int a)
    {
        if (_last == NULL)
        {
            _last = new Node();
            _last->item = a;
           _first = _last;
        }
        else
        {
            Node *new_node = new Node();
            new_node->item = a;
            new_node->prev = _last;
            _last->next = new_node;
            _last = new_node;
        }
    }

    friend ostream &operator<<(ostream &stream, const List *n)
    {
        if (n->_first != NULL)
        {
            Node *p = n->_first;
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
    cout << test;

    delete test;
    return 0;
}
