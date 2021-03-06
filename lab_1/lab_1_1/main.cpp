#include <cstring>
#include <iostream>

#define TABLE_TOP                                                                                                                                                                                                                                                                                                                    \
  "╔══════════════════════════════════════════╦════════╦════════╦════════════╦════════════╦══════════╗\n║ Название " \
  "игрушки                         ║ Цена   ║ Кол-во ║ Возраст от ║ Возраст до ║ Наличие  ║"
#define TABLE_CONNECT \
  "╠══════════════════════════════════════════╬════════╬════════╬════════════╬════════════╬══════════╣"
#define TABLE_DATA "║ %s%*s║ %-7g║ %-7d║ %-11d║ %-11d║ %s%*s║\n"
#define TABLE_BOTTOM \
  "╚══════════════════════════════════════════╩════════╩════════╩════════════╩════════════╩══════════╝"
#define CLEAR_CONSOLE 1
#define STDINCLEAR          \
  while (getchar() != '\n') \
    ;

#if defined(_WIN64) || defined(_WIN32)
#include <windows.h>
#define CLEAR \
  if (CLEAR_CONSOLE) system("cls")
#elif defined(__linux)
#define CLEAR \
  if (CLEAR_CONSOLE) system("clear")
#endif

#define N 81         // кол-во символов в строке
#define TOY_PAGE 10  // кол-во строк в таблице

using namespace std;

typedef struct toy
{
  char name[N];
  double price;
  int quantity;
  char age_min;
  char age_max;
  union
  {
    bool status;
    char date[9];
  } avaible;
  char variant;
} toy;

void Menu();
int Open(FILE **file, char path[], char rights[]);
void Close(FILE **file);
int StrPadding(char str[], int space);
void View();
void Input(char flag[], void *a, char message[]);
void GetString(char str[N], char message[]);
void AddData();
void CreateFilef();
void ToySearch();
void MaxConstructor();
void ToyDelete();
void ToyEdit();

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
  node *_cur = nullptr;
  bool _direction = true;

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
      node *p = _first, *new_node = new node;
      new_node->item = a;

      while (p->next && p->item.price < a.price) p = p->next;

      if (p->next)
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

  void view(void) { cout << this << endl; }

  void view_reverse(void)
  {
    if (_last)
    {
      node *p = _last;
      do
      {
        cout << p->item.name;
        if (p->prev) cout << " -> ";
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
    for (int i = 0; i < a; i++) p = p->next;

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

  toy getn(void)
  {
    if (_direction)
      if (_cur && _cur->next)
        _cur = _cur->next;
      else
        _cur = _first;
    else if (_cur && _cur->prev)
      _cur = _cur->prev;
    else
      _cur = _last;

    return _cur->item;
  }

  void changeDirection(void) { _direction = !_direction; }

  bool eol(void)
  {
    if (_direction && _cur == _last || !_direction && _cur == _first)
      return true;
    else
      return false;
  }

  void resetCur() { _cur = _last; }

  void set(const int a, const toy t)
  {
    node *p = _first;
    for (int i = 0; i < a; i++) p = p->next;

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
        if (p->next) stream << " -> ";
        p = p->next;
      } while (p);
    }
    else
    {
      stream << "список пуст!" << endl;
    }
    return stream;
  }

  ~List()
  {
    while (_first)
    {
      _cur = _first->next;  // сохраняем ссылку на следующий элемент
      delete _first;        // удаляем текущий
      _first = _cur;
    }
    _last = nullptr;
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
    fread(&current, sizeof(struct toy), 1, f);
    while (!feof(f))
    {
      list->add(current);
      fread(&current, sizeof(struct toy), 1, f);
    }

    Close(&f);
  }

  Menu();

  if (Open(&f, filename, "wb"))
  {
    toy current;

    for (int i = 0; i < list->count(); i++)
    {
      current = list->getn();
      fwrite(&current, sizeof(struct toy), 1, f);
    }

    Close(&f);
  }

  delete list;
  return 0;
}

void Menu()
{
  int choice;

  do
  {
    CLEAR;
    puts("1. Создание файла");
    puts("2. Добавление данных");
    puts("3. Просмотр содержимого списка");
    puts("4. Поиск игрушки");
    puts("5. Сведения о самом дорогом конструкторе");
    puts("6. Удаление данных");
    puts("7. Редактирование данных");
    puts("8. Просмотр списка");
    puts("9. Просмотр списка в обратном направлении");
    puts("0. Завершить программу\n");

    printf("Введите пункт меню: ");
    while (!scanf("%d", &choice))
    {
      printf("Введены неверные данные!\nВведите пункт меню: ");
      STDINCLEAR;
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
        View();
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
      case 8:
        CLEAR;
        list->view();
        STDINCLEAR;
        getchar();
        break;
      case 9:
        CLEAR;
        list->view_reverse();
        STDINCLEAR;
        getchar();
        break;
      case 0:
        CLEAR;
        break;
      default:
        puts("Введен неверный пункт меню!");
    }

  } while (choice);
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

void View()
{
  /*
      Просмотр всех записей в списке
  */
  CLEAR;
  int i, j;
  toy current;
  char choice;

  while (true)
  {
    CLEAR;

    if (list->count())  // есть ли в списке записи?
    {
      puts(TABLE_TOP);
      for (i = 0; i < TOY_PAGE; i++)  // печатаем TOY_PAGE элементов таблицы
      {
        puts(TABLE_CONNECT);

        current = list->getn();  // получаем следующий элемент списка

        printf(TABLE_DATA, current.name, StrPadding(current.name, 41), " ", current.price, current.quantity,
               current.age_min, current.age_max,
               current.variant ? (current.avaible.status ? "Есть" : "Нет") : (current.avaible.date),
               current.variant ? (current.avaible.status ? 5 : 6) : (1), " ");

        if (list->eol())  // проверка на конец списка
          break;
      }
      puts(TABLE_BOTTOM);
      puts("<--j   q-выход   l-->");

      do
      {
        printf("Ввод: ");
        STDINCLEAR;
        while (!scanf("%c", &choice))
        {
          printf("Ошибка ввода!\nВвод: ");
          STDINCLEAR;
        }

        if (choice != 'j' && choice != 'q' && choice != 'l') printf("Неизвестная команда!\n");
      } while (choice != 'j' && choice != 'q' && choice != 'l');

      if (choice == 'j')  // если вернулись обратно
      {
        list->changeDirection();  // меняем направление чтения списка

        for (j = 0; j < TOY_PAGE + i + 1; j++)  // возвращаемся на страницу назад
        {
          list->getn();

          if (list->eol())  // проверка на конец списка
          {
            list->getn();
            break;
          }
        }

        list->changeDirection();
      }
      else if (choice == 'q')
      {
        list->resetCur();  // ставим указатель в начальное положение
        return;
      }
    }
    else
    {
      puts("В списке отсутствуют записи");
      STDINCLEAR;
      getchar();
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
    STDINCLEAR;
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
  int choice;
  struct toy newt;
  getchar();

  GetString(newt.name, "Введите название игрушки: ");

  Input("%lf", &newt.price, "Введите цену: ");
  Input("%d", &newt.quantity, "Введите количество: ");
  Input("%d", &newt.age_min, "Введите минимальный возраст: ");
  Input("%d", &newt.age_max, "Введите максимальный возраст: ");

  do
  {
    puts("1. товар присутствует в магазине");
    puts("2. товар отсутствует в магазине");
    puts("3. ввести дату поступления в магазин");
    while (!scanf("%d", &choice))
    {
      printf("Введены неверные данные!\nВведите пункт меню: ");
      STDINCLEAR;
    }

    switch (choice)
    {
      case 1:
        newt.avaible.status = true;
        newt.variant = 1;
        break;
      case 2:
        newt.avaible.status = false;
        newt.variant = 1;
        break;
      case 3:
        Input("%s", &newt.avaible.date, "Введите дату поступления: ");
        newt.variant = 0;
        break;
    }
  } while (choice < 1 || choice > 3);

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
  char avaible[9];
  double price;
  toy current;

  do
  {
    printf("Введите возраст и цену: ");
    while (scanf("%d%lf", &age, &price) != 2)
    {
      STDINCLEAR;
      printf("Ошибка ввода!\nВведите возраст и цену: ");
    }
    if (age < 0 || price < 0) printf("Введено отрицательное значение!\n");
  } while (age < 0 || price < 0);
  STDINCLEAR;

  puts(TABLE_TOP);
  for (int i = 0; i < list->count(); i++)
  {
    current = list->getn();
    if (current.age_min <= age && current.age_max >= age && current.price <= price)
    {
      puts(TABLE_CONNECT);

      printf(TABLE_DATA, current.name, StrPadding(current.name, 41), " ", current.price, current.quantity,
             current.age_min, current.age_max,
             current.variant ? (current.avaible.status ? "Есть" : "Нет") : (current.avaible.date),
             current.variant ? (current.avaible.status ? 5 : 6) : (1), " ");
    }
  }
  puts(TABLE_BOTTOM);

  list->resetCur();
  printf("Для продолжения нажмите любую клавишу...");
  getchar();
}

void MaxConstructor()
{
  CLEAR;
  char avaible[9];
  double max_price = 0;
  toy current;

  for (int i = 0; i < list->count(); i++)
  {
    current = list->getn();
    for (int j = 0; j < N; j++)
      if (current.name[j] == -48 && current.name[j + 1] == -102 && current.name[j + 20] == -47 &&
          current.name[j + 21] == -128 && max_price < current.price)
        max_price = current.price;
  }
  list->resetCur();

  for (int i = 0; i < list->count(); i++)
  {
    current = list->getn();
    for (int j = 0; j < N; j++)
    {
      if (current.name[j] == -48 && current.name[j + 1] == -102 && current.name[j + 20] == -47 &&
          current.name[j + 21] == -128 && max_price == current.price)  // Проверка 2 байт 'К' и 'р'
      {
        puts(TABLE_TOP);
        puts(TABLE_CONNECT);
        printf(TABLE_DATA, current.name, StrPadding(current.name, 41), " ", current.price, current.quantity,
               current.age_min, current.age_max,
               current.variant ? (current.avaible.status ? "Есть" : "Нет") : (current.avaible.date),
               current.variant ? (current.avaible.status ? 5 : 6) : (1), " ");
        puts(TABLE_BOTTOM);

        STDINCLEAR;
        printf("Для продолжение нажмите любую клавишу...");
        getchar();
      }
    }
  }
  list->resetCur();
}

void ToyDelete()
{
  CLEAR;
  FILE *f, *t;
  char avaible[9];
  char del[N], choice;
  struct toy current;

  STDINCLEAR;
  GetString(del, "Введите строку: ");

  for (int i = 0; i < list->count(); i++)
  {
    current = list->getn();
    if (!strcmp(current.name, del))
    {
      puts(TABLE_TOP);
      puts(TABLE_CONNECT);
      printf(TABLE_DATA, current.name, StrPadding(current.name, 41), " ", current.price, current.quantity,
             current.age_min, current.age_max,
             current.variant ? (current.avaible.status ? "Есть" : "Нет") : (current.avaible.date),
             current.variant ? (current.avaible.status ? 5 : 6) : (1), " ");
      puts(TABLE_BOTTOM);

      do
      {
        printf("\nВы хотите удалить данный товар?\ny - да n - нет\n");
        while (scanf("%c", &choice) != 1)
        {
          STDINCLEAR;
          printf("Ошибка ввода!\nВы хотите удалить данный товар?\ny - да n - нет\n");
        }
        if (choice != 'y' && choice != 'n') printf("Ошибка ввода!\n");
      } while (choice != 'y' && choice != 'n');

      if (choice == 'y')
      {
        list->del(i);
      }
    }
  }
  list->resetCur();
}

void ToyEdit()
{
  CLEAR;
  int int_choice;
  struct toy current;
  char edit[N], choice, avaible[9];

  STDINCLEAR;
  GetString(edit, "Введите строку: ");

  for (int i = 0; i < list->count(); i++)
  {
    current = list->getn();
    if (!strcmp(current.name, edit))
    {
      puts(TABLE_TOP);
      puts(TABLE_CONNECT);
      printf(TABLE_DATA, current.name, StrPadding(current.name, 41), " ", current.price, current.quantity,
             current.age_min, current.age_max,
             current.variant ? (current.avaible.status ? "Есть" : "Нет") : (current.avaible.date),
             current.variant ? (current.avaible.status ? 5 : 6) : (1), " ");
      puts(TABLE_BOTTOM);

      do
      {
        printf("\nВы хотите изменить данный товар?\ny - да n - нет\n");
        while (scanf("%c", &choice) != 1)
        {
          STDINCLEAR;
          printf("Ошибка ввода!\nВы хотите изменить данный товар?\ny - да n - нет ");
        }
        if (choice != 'y' && choice != 'n') printf("Ошибка ввода!\n");
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
          puts("6. Изменить наличие в магазине");
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
            case 6:
              do
              {
                puts("1. товар присутствует в магазине");
                puts("2. товар отсутствует в магазине");
                puts("3. ввести дату поступления в магазин");
                while (!scanf("%d", &choice))
                {
                  printf("Введены неверные данные!\nВведите пункт меню: ");
                  STDINCLEAR;
                }

                switch (choice)
                {
                  case 1:
                    current.avaible.status = true;
                    current.variant = 1;
                    break;
                  case 2:
                    current.avaible.status = false;
                    current.variant = 1;
                    break;
                  case 3:
                    Input("%s", &current.avaible.date, "Введите дату поступления: ");
                    current.variant = 0;
                    break;
                }
              } while (choice < 1 || choice > 3);
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
  list->resetCur();
}
