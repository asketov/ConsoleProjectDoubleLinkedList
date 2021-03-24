#include <iostream>
#include <fstream>
#include <string>

typedef struct student DataType;

using namespace std;

struct BeginEnd read_file(string file);
struct BeginEnd add_el(struct BeginEnd list, DataType student);
struct BeginEnd new_node(struct BeginEnd list, DataType student);
void show_begin(struct BeginEnd list);
void print_student(int n, DataType student);
DataType input_student();
void show_end(struct BeginEnd list);
void search(struct BeginEnd list);
void number_of_twos(struct BeginEnd list);
void show_students_with_twos(struct BeginEnd list);
struct BeginEnd delete_student(struct BeginEnd list);
void del_element(struct node* cur);
void print_file(struct BeginEnd list, string file);
bool compare_surname_char(DataType temp, DataType temp1);

#pragma pack(push, 1)
struct student
{
    char surname[20];
    char ball_inf;
    char ball_math;
    char ball_phys;
    union
    {
        char male, female;
    };
};
#pragma pack (pop)

struct BeginEnd
{
    struct node* begin, * end;
};

struct node
{
    DataType data;
    struct node* next, * prev;
};

int main(int argc, char* argv[])
{
    setlocale(0, "Russian");
    string file;
    char menu;
    struct BeginEnd students;
    if (argc > 1)
    {
        file = argv[1];
    }
    else
    {
        cout << "Имя файла:";
        getline(cin, file);
    }
    students = read_file(file);
    do
    {
        system("CLS");
        cout << "1. Insert" << endl;
        cout << "2. Show from the begin" << endl;
        cout << "3. Show from the end" << endl;
        cout << "4. Search" << endl;
        cout << "5. Delete" << endl;
        cout << "6. Exit" << endl;
        menu = getchar(); getchar();
        switch (menu)
        {
        case '1': students = new_node(students, input_student());  break;
        case '2': show_begin(students);  break;
        case '3': show_end(students); break;
        case '4': search(students); break;
        case '5': students = delete_student(students); break;
        }
    } while (menu != '6');
    print_file(students, file);
    return 0;
}
struct BeginEnd read_file(string file)
{
    DataType temp;
    ifstream fout(file, istream::binary);
    struct BeginEnd spisok;
    spisok.begin = NULL; spisok.end = NULL;
    if (fout)
    {
        while (fout.read((char*)&temp, sizeof(DataType)))
        {
            spisok = add_el(spisok, temp);
        }
        fout.close();
        return spisok;
    }
    else
    {
        cout << "Файл не открыт";
        getchar();
        return spisok;
    }
}
struct BeginEnd add_el(struct BeginEnd list, DataType student)
{
    struct BeginEnd BegEndOld = list;
    struct node* temp;
    temp = new struct node;
    temp->data = student;
    if (list.begin == NULL) //если первый элемент
    {
        temp->next = NULL;
        temp->prev = NULL;
        list.begin = temp;
        list.end = temp;
        return list;
    }
    if (list.begin->data.surname[0] >= student.surname[0]) //если элемент выше 1 элемента и становится 1 элементом
    {
        temp->next = list.begin;
        temp->prev = NULL;
        if (list.begin) /*если добавляем в непустой список*/
            list.begin->prev = temp;
        list.begin = temp;
        return list;
    }
    while (list.begin != BegEndOld.end)
    {
        if (list.begin->data.surname[0] < student.surname[0])
        {
            list.begin = list.begin->next;
        }
        else
        {
            temp->next = list.begin;
            temp->prev = list.begin->prev;
            list.begin->prev->next = temp;
            list.begin->prev = list.begin;
            return BegEndOld;
        }
    }
    temp->next = NULL;
    temp->prev = BegEndOld.end;
    if (BegEndOld.end) /*если добавляем в непустой список*/
        BegEndOld.end->next = temp;
    else /*если добавляемый элемент единственный в списке*/
        BegEndOld.begin = temp;
    BegEndOld.end = temp;
    return BegEndOld;
}
struct BeginEnd new_node(struct BeginEnd list, DataType student)
{
    list = add_el(list, student);
    return list;
}
void show_begin(struct BeginEnd list)
{
    string line = "--------------------------------------------------------------------------------";
    string up = "|  N |          Surname                 |    Phys     |   Math     |   Inf   |s|";
    int n = 1;
    system("CLS");
    cout << up << line;
    while (list.begin)
    {
        print_student(n, list.begin->data);
        list.begin = list.begin->next;
        n++;
    }
    getchar();
}
void print_student(int n, DataType student)
{
    string line = "--------------------------------------------------------------------------------";
    cout << "|"; cout.width(3); cout << n;  cout.width(2); cout << "|"; cout.width(17); cout << student.surname; cout.width(18); cout << "|";
    cout.width(5); cout << student.ball_phys; cout.width(9); cout << "|"; cout.width(5); cout << student.ball_math; cout.width(8); cout << "|";
    cout.width(5); cout << student.ball_inf; cout.width(5); cout << "|"; if (student.male == '1') cout << "m"; else cout << "f"; cout << "|"; cout << line;

}
DataType input_student()
{
    system("CLS");
    DataType student;
    char choise;
    cout << "Введите 1 - если мужчина, введите 2 - если женщина:";
    choise = getchar();
    if (choise == '1') student.male = '1';
    else student.female = '2';
    cout << "Введите фамилию студента:";
    cin >> student.surname;
    cout << "Введите оценку по физике:";
    cin >> student.ball_phys;
    cout << "Введите оценку по математике:";
    cin >> student.ball_math;
    cout << "Введите оценку по информатике:";
    cin >> student.ball_inf;
    getchar();
    return student;
}
void show_end(struct BeginEnd list)
{
    string up = "|  N |          Surname                 |    Phys     |   Math     |   Inf   |s|--------------------------------------------------------------------------------";
    int n = 1;
    system("CLS");
    cout << up;
    while (list.end)
    {
        print_student(n, list.end->data);
        list.end = list.end->prev;
        n++;
    }
    getchar();
}
void search(struct BeginEnd list)
{
    char menu;
    do
    {
        system("CLS");
        cout << "1. number of twos in each subject" << endl;
        cout << "2. Show list students with twos" << endl;
        cout << "3. Back" << endl;
        menu = getchar(); getchar();
        switch (menu)
        {
        case '1': number_of_twos(list);  break;
        case '2': show_students_with_twos(list);  break;
        }
    } while (menu != '3');
}
void number_of_twos(struct BeginEnd list)
{
    int kol_2_phys = 0, kol_2_math = 0, kol_2_inf = 0;
    system("CLS");
    while (list.begin)
    {
        if (list.begin->data.ball_phys == '2') kol_2_phys += 1;
        if (list.begin->data.ball_math == '2') kol_2_math += 1;
        if (list.begin->data.ball_inf == '2') kol_2_inf += 1;
        list.begin = list.begin->next;
    }
    cout << "Количество двоек по физике:" << kol_2_phys << endl;
    cout << "Количество двоек по математике:" << kol_2_math << endl;
    cout << "Количество двоек по информатике:" << kol_2_inf << endl;
    getchar();
}
void show_students_with_twos(struct BeginEnd list)
{
    int n = 1;
    system("CLS");
    cout << "Список студентов, имеющих хотя бы одну двойку:" << endl;
    while (list.begin)
    {
        if (list.begin->data.ball_phys == '2' || list.begin->data.ball_math == '2' || list.begin->data.ball_inf == '2')
        {

            cout << n++ << ")" << list.begin->data.surname << endl;
        }
        list.begin = list.begin->next;
    }
    getchar();
}
struct BeginEnd delete_student(struct BeginEnd list)
{
    system("CLS");
    DataType student;
    struct BeginEnd list_old; list_old.begin = list.begin; list_old.end = list.end;
    if (list.begin == NULL)
    {
        cout << "Список пуст, удаление невозможно";
        getchar();
        return list;
    }
    cout << "Введите фамилию студента, которого хотите удалить:";
    cin >> student.surname;
    cout << "Введите его оценку по физике:";
    cin >> student.ball_phys;
    cout << "Введите его оценку по математике:";
    cin >> student.ball_math;
    cout << "Введите его оценку по информатике:";
    cin >> student.ball_inf;
    getchar();
    while (list.begin)
    {
        if (compare_surname_char(student, list.begin->data) && list.begin->data.ball_phys == student.ball_phys && list.begin->data.ball_math == student.ball_math
            && list.begin->data.ball_inf == student.ball_inf)
        {
            if (list.begin->prev == NULL) /*если удаляем первый элемент*/
            {
                struct node* temp;
                if (list.begin->next == NULL)
                {
                    temp = list.begin;
                    list.begin = NULL;
                    list.end = NULL;
                }
                else
                {
                    temp = list.begin;
                    list.begin = list.begin->next; /*переставляем указатель на следующий элемент*/
                    list.begin->prev = NULL; /*обнуляем указатель на удаляемый элемент*/
                }
                delete(temp);
                return list;
            }
            else if (list.begin->next == NULL) /*если удаляем последний элемент*/
            {
                struct node* temp;

                temp = list.end;
                list.end = list.end->prev; /*переставляем указатель на предыдущий элемент*/
                list.end->next = NULL; /*обнуляем указатель на удаляемый элемент*/
                delete(temp); /*первый удаляем*/
                list.begin = list_old.begin;
                return list;
            }
            else
            {
                del_element(list.begin);
                list.begin = list_old.begin;
                return list;
            }
        }
        list.begin = list.begin->next;
    }
    cout << "Студент не найден, повторите попытку";
    getchar();
    return list_old;
}
void del_element(struct node* cur) /*удаление текущего (важно(!) не первого и не последнего)*/
{
    cur->next->prev = cur->prev; /*указателю prev следующего элемента присваиваем адрес предшествующего удаляемому*/
    cur->prev->next = cur->next; /*указателю next предыдущего элемента присваиваем адрес следующего за удаляемым*/
    delete(cur);
}
void print_file(struct BeginEnd list, string file)
{
    ofstream fout(file, ostream::binary);
    while (list.begin)
    {
        fout.write((char*)&list.begin->data, sizeof(list.begin->data));
        list.begin = list.begin->next;
    }
    fout.close();
}
bool compare_surname_char(DataType temp, DataType temp1)
{
    string surname1 = string(temp.surname);
    string surname2 = string(temp1.surname);
    if (surname1 == surname2) return true;
    else return false;
}