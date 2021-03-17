#include <iostream>
#include <cstring>

#define TABLE_TOP "╔══════════════════════════════════════════╦════════╦════════╦════════════╦════════════╗\n║ Название игрушки                         ║ Цена   ║ Кол-во ║ Возраст от ║ Возраст до ║"
#define TABLE_CONNECT "╠══════════════════════════════════════════╬════════╬════════╬════════════╬════════════╣"
#define TABLE_DATA "║ %s%*s║ %-7g║ %-7d║ %-11d║ %-11d║\n"
#define TABLE_BOTTOM "╚══════════════════════════════════════════╩════════╩════════╩════════════╩════════════╝"
#define CLEAR_CONSOLE 0

#if defined(_WIN64) || defined(_WIN32)
#include <windows.h>
#define CLEAR          \
    if (CLEAR_CONSOLE) \
    system("cls")
#elif defined(__linux)
#define CLEAR          \
    if (CLEAR_CONSOLE) \
    system("clear")
#endif

#define N 81
#define TOY_PAGE 10
#define DEBUG 1

using namespace std;

int Menu();
int Open(FILE **file, char path[], char rights[]);
void Close(FILE **file);
int StrPadding(char str[], int space);
void FileView();
void Input(char flag[], void *a, char message[]);
void GetString(char str[N], char message[]);
void AddData();
void CreateFilef();
void ToySearch();
void MaxConstructor();
void ToyDelete();
void ToyEdit();

typedef struct toy
{
    char name[N];
    double price;
    int quantity;
    int age_min;
    int age_max;
} toy;

class List
{
private:
    typedef struct node
    {
        struct toy item;
        node *next = nullptr;
        node *prev = nullptr;
    } node;

    node *_first = nullptr;
    node *_last = nullptr;

    void _add_start(const struct toy a)
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

#if DEBUG
        cout << "Добавление " << a.name << " в начало списка" << endl;
        view();
        view_reverse();
#endif
        }
    }

    void _add_end(const struct toy a)
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
    void add(const struct toy a)
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

            while (p->next && p->item.price < a.price)
                p = p->next;

            if (p->next || p->item.price > a.price)
            {
                new_node->next = p;
                new_node->prev = p->prev;
                p->prev = new_node;
                if (new_node->prev)
                    new_node->prev->next = new_node;
                else
                    _first = new_node;
            }
            else
            {
                _add_end(a);
            }
        }
    }

    void view(void)
    {
        cout << this << endl;
    }

    void view_reverse(void)
    {
        if (_last)
        {
            node *p = _last;
            do
            {
                cout << p->item.name;
                if (p->prev)
                    cout << " -> ";
                p = p->prev;
            } while (p);
        }
        else
        {
            cout << "список пуст!" << endl;
        }
    }

    void del(const unsigned int a)
    {
        node *p = _first;
        for (int i = 0; i < a; i++)
            p = p->next;
        
        if (p->next)
        {
            p->next->prev = p->prev;

            if (p->prev)
                p->prev->next = p->next;
            else
                _first = p->next;
        }
        else
        {
            if (p->prev)
            {
                p->prev->next = nullptr;
                _last = p->prev;
            }
            else
            {
                _first = nullptr;
                _last = nullptr;
            }
                
        }
    }

    int count()
    {
        node *p = _first;
        int num = 0;
        while (p)
        {
            num++;
            p = p->next;
        }
        return num;
    }

    toy get(const unsigned int a)
    {
        node *p = _first;
        for (int i = 0; i < a; i++)
            p = p->next;

        return p->item;
    }

    void set(const unsigned int a, const toy t)
    {
        node *p = _first;
        for (int i = 0; i < a; i++)
            p = p->next;
        
        p->item = t;
    }

    friend ostream &operator<<(ostream &stream, const List *n)
    {
        if (n->_first)
        {
            node *p = n->_first;
            do
            {
                stream << p->item.name;
                if (p->next)
                    stream << " -> ";
                p = p->next;
            } while (p);
        }
        else
        {
            stream << "список пуст!" << endl;
        }
        return stream;
    }
};

List *list = new List();
char filename[N];

int main(int argc, char *argv[])
{
#if defined(_WIN64) || defined(_WIN32)
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    CLEAR;
    if (argc == 2)
    {
        strcpy(filename, argv[1]);
    }
    else if (argc == 1)
    {
        GetString(filename, "Введите имя файла: ");
    }
    else
    {
        printf("Слишком много аргументов!\n");
        return -1;
    }

    FILE *f;

    if (Open(&f, filename, "rb"))
    {
        struct toy current;
        fread(&current, sizeof(struct toy), 1, f); // TODO: создание пустого списка, если файла не существует/нет записей
        while (!feof(f))
        {
            list->add(current);
            fread(&current, sizeof(struct toy), 1, f);
        }

        Close(&f);
    }

    // delete list;
    return Menu();
}

int Menu()
{
    int choice;

    do
    {
        CLEAR;
        puts("1. Создание файла");
        puts("2. Добавление данных");
        puts("3. Просмотр содержимого файла");
        puts("4. Поиск игрушки");
        puts("5. Сведения о самом дорогом конструкторе");
        puts("6. Удаление данных");
        puts("7. Редактирование данных");
        puts("0. Завершить программу\n");

        printf("Введите пункт меню: ");
        while (!scanf("%d", &choice))
        {
            printf("Введены неверные данные!\nВведите пункт меню: ");
            while (getchar() != '\n')
                ;
        }

        switch (choice)
        {
        case 1:
            CreateFilef();
            break;
        case 2:
            AddData();
            break;
        case 3:
            FileView();
            break;
        case 4:
            ToySearch();
            break;
        case 5:
            MaxConstructor();
            break;
        case 6:
            ToyDelete();
            break;
        case 7:
            ToyEdit();
            break;
        case 0:
            CLEAR;
            break;
        default:
            puts("Введен неверный пункт меню!");
        }

    } while (choice);

    return 0;
}

int Open(FILE **file, char path[], char rights[])
{
    if ((*file = fopen(path, rights)) == NULL)
    {
        CLEAR;
        printf("Ошибка открытия файла!\n");
        getchar();
        return 0;
    }
    else
    {
        return 1;
    }
}

void Close(FILE **file)
{
    if (*file != NULL)
    {
        fclose(*file);
    }
}

int StrPadding(char str[], int n)
{
    /*
        Русские буквы занимают в строке 2 байта, а ASCII 1 байт
    */
    int i;

    for (i = 0; i < N; i++)
    {
        if (str[i] == '\0')
            break;
        else if (str[i] < 0)
            i++;

        n--;
    }

    return n;
}

void FileView()
{
    CLEAR;

    int count, pages_num, i, j;
    struct toy current;
    char choice;

    count = list->count();
    pages_num = count / TOY_PAGE + 1;
    while (count >= TOY_PAGE)
        count = count - TOY_PAGE;

    for (i = 0; i < pages_num; i++)
    {
        CLEAR;
        puts(TABLE_TOP);

        if (i + 1 == pages_num && count == 0)
            break;

        for (j = 0; j < TOY_PAGE; j++)
        {
            if (j + i * TOY_PAGE == list->count())
                break;
            else if (i == 0)
                current = list->get(j);
            else
                current = list->get(j + i * TOY_PAGE);

            puts(TABLE_CONNECT);
            printf(TABLE_DATA, current.name, StrPadding(current.name, 41), " ", current.price, current.quantity, current.age_min, current.age_max);
        }
        puts(TABLE_BOTTOM);
        cout << list << endl;
        list->view_reverse();
        cout << endl;
        printf("<--j   q-выход   l-->\n");

        do
        {
            printf("Ввод: ");
            while (getchar() != '\n')
                ;
            while (!scanf("%c", &choice))
            {
                printf("Ошибка ввода!\nВвод: ");
                while (getchar() != '\n')
                    ;
            }

            if (choice != 'j' && choice != 'q' && choice != 'l')
                printf("Неизвестная команда!\n");
        } while (choice != 'j' && choice != 'q' && choice != 'l');

        if (choice == 'j')
        {
            if (i == 0)
                break;

            i -= 2;
        }
        else if (choice == 'q')
        {
            break;
        }
    }
}

void Input(char flag[], void *a, char message[])
{
    printf(message);
    while (!scanf(flag, a))
    {
        puts("Неверные данные!");
        puts(message);
        while (getchar() != '\n')
            ;
    }
    getchar();
}

void GetString(char str[N], char message[])
{
    int i;

    printf(message);
    fgets(str, N, stdin);
    for (i = 0; i < N; i++)
    {
        if (str[i] == '\n')
        {
            str[i] = '\0';
            break;
        }
    }
}

void AddData()
{
    CLEAR;
    struct toy newt;
    getchar();

    GetString(newt.name, "Введите название игрушки: ");

    Input("%lf", &newt.price, "Введите цену: ");
    Input("%d", &newt.quantity, "Введите количество: ");
    Input("%d", &newt.age_min, "Введите минимальный возраст: ");
    Input("%d", &newt.age_max, "Введите максимальный возраст: ");

    list->add(newt);
    printf("Запись завершена!\n");
}

void CreateFilef()
{
    FILE *f;
    if (Open(&f, filename, "w"))
    {
        printf("Файл создан!\n");
        Close(&f);
    }
}

void ToySearch()
{
    CLEAR;
    int age;
    double price;
    toy current;

    do
    {
        printf("Введите возраст и цену: ");
        while (scanf("%d%lf", &age, &price) != 2)
        {
            while (getchar() != '\n')
                ;
            printf("Ошибка ввода!\nВведите возраст и цену: ");
        }
        if (age < 0 || price < 0)
            printf("Введено отрицательное значение!\n");
    } while (age < 0 || price < 0);
    while (getchar() != '\n')
        ;

    puts(TABLE_TOP);
    for (int i = 0; i < list->count(); i++)
    {
        current = list->get(i);
        if (current.age_min <= age && current.age_max >= age && current.price <= price)
        {
            puts(TABLE_CONNECT);
            printf(TABLE_DATA, current.name, StrPadding(current.name, 41), " ", current.price, current.quantity, current.age_min, current.age_max);
        }
    }
    puts(TABLE_BOTTOM);

    printf("Для продолжения нажмите любую клавишу...");
    getchar();
}

void MaxConstructor()
{
    CLEAR;
    double max_price = 0;
    toy current;

    for (int i = 0; i < list->count(); i++)
    {
        current = list->get(i);
        for (int j = 0; j < N; j++)
            if (current.name[j] == -48 && current.name[j + 1] == -102 && current.name[j + 20] == -47 && current.name[j + 21] == -128 && max_price < current.price)
                max_price = current.price;
    }

    for (int i = 0; i < list->count(); i++)
    {
        current = list->get(i);
        for (int j = 0; j < N; j++)
        {
            if (current.name[j] == -48 && current.name[j + 1] == -102 && current.name[j + 20] == -47 && current.name[j + 21] == -128 && max_price == current.price)
            { // Проверка 2 байт 'К' и 'р'
                puts(TABLE_TOP);
                puts(TABLE_CONNECT);
                printf(TABLE_DATA, current.name, StrPadding(current.name, 41), " ", current.price, current.quantity, current.age_min, current.age_max);
                puts(TABLE_BOTTOM);

                while (getchar() != '\n')
                    ;
                printf("Для продолжение нажмите любую клавишу...");
                getchar();
            }
        }
    }
}

void ToyDelete()
{
    CLEAR;
    FILE *f, *t;
    char del[N], choice;
    struct toy current;

    while (getchar() != '\n')
        ;
    GetString(del, "Введите строку: ");

    for (int i = 0; i < list->count(); i++)
    {
        current = list->get(i);
        if (!strcmp(current.name, del))
        {
            puts(TABLE_TOP);
            puts(TABLE_CONNECT);
            printf(TABLE_DATA, current.name, StrPadding(current.name, 41), " ", current.price, current.quantity, current.age_min, current.age_max);
            puts(TABLE_BOTTOM);

            do
            {
                printf("\nВы хотите удалить данный товар?\ny - да n - нет\n");
                while (scanf("%c", &choice) != 1)
                {
                    while (getchar() != '\n')
                        ;
                    printf("Ошибка ввода!\nВы хотите удалить данный товар?\ny - да n - нет\n");
                }
                if (choice != 'y' && choice != 'n')
                    printf("Ошибка ввода!\n");
            } while (choice != 'y' && choice != 'n');

            if (choice == 'y')
            {
                list->del(i);
            }
        }
    }
}

void ToyEdit()
{
    CLEAR;
    int int_choice;
    char edit[N], choice;
    struct toy current;

    while (getchar() != '\n')
        ;
    GetString(edit, "Введите строку: ");

    for (int i = 0; i < list->count(); i++)
    {
        current = list->get(i);
        if (!strcmp(current.name, edit))
        {
            puts(TABLE_TOP);
            puts(TABLE_CONNECT);
            printf(TABLE_DATA, current.name, StrPadding(current.name, 41), " ", current.price, current.quantity, current.age_min, current.age_max);
            puts(TABLE_BOTTOM);

            do
            {
                printf("\nВы хотите изменить данный товар?\ny - да n - нет\n");
                while (scanf("%c", &choice) != 1)
                {
                    while (getchar() != '\n')
                        ;
                    printf("Ошибка ввода!\nВы хотите изменить данный товар?\ny - да n - нет ");
                }
                if (choice != 'y' && choice != 'n')
                    printf("Ошибка ввода!\n");
            } while (choice != 'y' && choice != 'n');

            if (choice == 'y')
            {
                do
                {
                    puts("1. Изменить название");
                    puts("2. Изменить цену");
                    puts("3. Изменить количество");
                    puts("4. Изменить минимальный возраст");
                    puts("5. Изменить максимальный возраст");
                    puts("0. Завершить редактирование");
                    Input("%d", &int_choice, "Введите пункт: ");
                    CLEAR;

                    switch (int_choice)
                    {
                    case 1:
                        GetString(current.name, "Введите название игрушки: ");
                        break;
                    case 2:
                        Input("%lf", &current.price, "Введите цену: ");
                        break;
                    case 3:
                        Input("%d", &current.quantity, "Введите количество: ");
                        break;
                    case 4:
                        Input("%d", &current.age_min, "Введите минимальный возраст: ");
                        break;
                    case 5:
                        Input("%d", &current.age_max, "Введите максимальный возраст: ");
                        break;
                    case 0:
                        break;
                    default:
                        puts("Введен неверный пункт меню!");
                    }
                } while (int_choice);
            }
        }

        list->set(i, current);
    }
}
