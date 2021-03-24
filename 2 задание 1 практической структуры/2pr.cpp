
#include <iostream>
#include "Classes.cpp"

using namespace std;
void create_mnogochlen(int n, IBaseClass& structure);
void difference_of_polynomials(IBaseClass& structure1, IBaseClass& structure2, int n1, int n2);

int main()
{
    setlocale(LC_ALL, "Russian");
    char choise;
    int n1, n2, i = 1;
    cout << "Выберите структуру хранения:" << endl << "1. Векторная" << endl << "2. Связная" << endl;
    choise = getchar();
    system("cls");
    if (choise == '1')
    {
        cout << "Введите количество членов первого многочлена:";
        cin >> n1;
        class vector Vector(n1);
        create_mnogochlen(n1, Vector);
        cout << "Введите количество членов второго многочлена:";
        cin >> n2;
        class vector Vector1(n2);
        create_mnogochlen(n2, Vector1);
        difference_of_polynomials(Vector, Vector1, n1, n2);
       
    }
    else if (choise == '2')
    {
        class Connected first, second;
        cout << "Введите количество членов первого многочлена:";
        cin >> n1;
        create_mnogochlen(n1, first);
        cout << "Введите количество членов второго многочлена:";
        cin >> n2;
        create_mnogochlen(n2, second);
        difference_of_polynomials(first, second, n1, n2);
        

    }
    else { cout << "Цифра введена неверно, повторите попытку"; }
    return 0;
}

void create_mnogochlen(int n, IBaseClass& structure)
{
    int i = 1;
    while (i <= n)
    {
        DataType Info;
        cout << "Введите с" << i << ":";
        cin >> Info.coef;
        cout << "Введите e" << i << ":";
        cin >> Info.degree;
        structure.EnQueue(Info);
        i++;
    }
}
void difference_of_polynomials(IBaseClass& structure1, IBaseClass& structure2, int n1, int n2)
{
    DataType first_p, second_p;
    if (n1 > n2)
    {
        while (n1 != n2)
        {
            first_p = structure1.DeQueue();
            cout << first_p.coef << "*x^" << first_p.degree << "+";
            n1--;
        }
        while (n1 != 0)
        {
            first_p = structure1.DeQueue();
            second_p = structure2.DeQueue();
            if (n1 != 1) 
            { 
                if ((first_p.coef - second_p.coef) < 0)
                {
                    cout << "(" << first_p.coef - second_p.coef << ")" << "*x^" << first_p.degree << "+";
                }
                else cout << first_p.coef - second_p.coef << "*x^" << first_p.degree << "+";
            }
            else
            {
                if ((first_p.coef - second_p.coef) < 0)
                {
                    cout << "(" << first_p.coef - second_p.coef << ")" << "*x^" << first_p.degree;
                }
                else cout << first_p.coef - second_p.coef << "*x^" << first_p.degree;
            }
            n1--;
        }
    }
    else if (n2 > n1)
    {
        while (n2 != n1)
        {
            second_p = structure2.DeQueue();
            cout << -second_p.coef << "*x^" << second_p.degree;
            n2--;
        }
        cout << "+";
        while (n2 != 0)
        {
            first_p = structure1.DeQueue();
            second_p = structure2.DeQueue();
            if (n2 != 1)
            {
                if ((first_p.coef - second_p.coef) < 0)
                {
                    cout << "(" << first_p.coef - second_p.coef << ")" << "*x^" << first_p.degree << "+";
                }
                else cout << first_p.coef - second_p.coef << "*x^" << first_p.degree << "+";
            }
            else
            { 
                if ((first_p.coef - second_p.coef) < 0)
                {
                    cout << "(" << first_p.coef - second_p.coef << ")" << "*x^" << first_p.degree;
                }
                else cout << first_p.coef - second_p.coef << "*x^" << first_p.degree;
            }
            n2--;
        }
    }
    else if (n1 == n2)
    {
        while (n1 != 0)
        {
            first_p = structure1.DeQueue();
            second_p = structure2.DeQueue();
            if (n1 != 1)
            { 
                if ((first_p.coef - second_p.coef) < 0)
                {
                    cout << "(" << first_p.coef - second_p.coef << ")" << "*x^" << first_p.degree << "+";
                }
                else cout << first_p.coef - second_p.coef  << "*x^" << first_p.degree << "+";
            }
            else 
            { 
                if ((first_p.coef - second_p.coef) < 0)
                {
                    cout << "(" << first_p.coef - second_p.coef << ")" << "*x^" << first_p.degree;
                }
                else cout << first_p.coef - second_p.coef << "*x^" << first_p.degree;
            }
            n1--;
        }
    }
}
