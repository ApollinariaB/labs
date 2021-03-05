// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <cstdlib>
#include <iostream>
#include <fstream>

const int max_rand = 10;

using namespace std;

void AddEl(int&, int*&, int&);
void DelEl(int&, int*&, int&);
void AddElAfter(int&, int*&);
void DelElSpec(int&, int*&);
void ReadArr(int*, int);
void InFileRand(int);
void PrintArr(int*, int&);



int main()
{
    setlocale(0, "Rus");

    int count, r;
    int p;


    cout << "Введите первоначальный размер массива: "; cin >> count; cout << endl;
    int* arr = new int[count];
    InFileRand(count);
    ReadArr(arr, count);
    PrintArr(arr, count);

    do {
        cout << "\n\nВыберите номер задачи: ";
        cout << "\n1 - Добавить элемент в конец массива";
        cout << "\n2 - Добавить элемент в начало массива";
        cout << "\n3 - Удалить элемент с конца массива";
        cout << "\n4 - Удалить элемент с начала массива";
        cout << "\n5 - Добавить элемент на k - ую позицию в массиве";
        cout << "\n6 - Удалить k - ый элемент массива";
        cout << "\n7 - Добавить элемент массива после встреченного элемента с заданным значением";
        cout << "\n8 - Удалить все элементы массива с заданным значением";
        cout << "\n0 - Выход\n> ";
        cin >> r; cout << "\n";

        if (r == 1) { p = 2; AddEl(count, arr, p); }
        if (r == 2) { p = 0; AddEl(count, arr, p); }
        if (r == 3) { p = 2; DelEl(count, arr, p); }
        if (r == 4) { p = 0; DelEl(count, arr, p); }
        if (r == 5) { p = 1; AddEl(count, arr, p); }
        if (r == 6) { p = 1; DelEl(count, arr, p); }
        if (r == 7) AddElAfter(count, arr);
        if (r == 8) DelElSpec(count, arr);

        cout << "\n";
        PrintArr(arr, count);
    } while (r != 0);
}

void InFileRand(int n)
{
    fstream f_out("arr.txt", ios::out);
    if (f_out)
    {
        for (int i = 0; i < n; i++) {
            f_out << rand() % max_rand << " ";
        }
        f_out.close();
    }
    else cout << "Ошибка, файл не был открыт";

}



void ReadArr(int* arr, int n)
{
    fstream f_in("arr.txt", ios::in);
    if (f_in) {
        for (int i = 0; i < n; i++) {
            f_in >> arr[i];
        }
        f_in.close();
    }
    else cout << "Ошибка, файл не был открыт";
}

void PrintArr(int* arr, int& n)
{
    for (int i = 0; i < n; i++) {
        cout << "[" << i << "]: " << arr[i] << endl;
    }

}

void AddEl(int& count, int*& arr, int& p)
{
    int index; int number;
    cout << "Введите ЧИСЛО, которое будет добавлено в массив: "; cin >> number;
    if (p == 0)
    {
        index = 0;
    }
    else if (p == 2)
    {
        index = count;
    }
    else if (p == 1)
    {
        cout << "Задайте ИНДЕКС элемента, на место которого будет подставлено число: ";
        do
        {
            cin >> index;
            if (index < 0 || index > count) cout << "Введенный индекс отсутствует, попробуйте еще раз\n\n";
        } while (index < 0 || index > count);
    }
    if (index >= 0 && index <= count)
    {
        count = count + 1;
        int* buff = new int[count];
        for (int i = 0; i < index; i++)
        {
            buff[i] = arr[i];
        }
        buff[index] = number;
        for (int i = index + 1; i < count; i++)
        {
            buff[i] = arr[i - 1];
        }
        delete[] arr;
        arr = buff;
    }
}
void DelEl(int& count, int*& arr, int& p)
{
    int index;
    if (p == 0)
    {
        index = 0;
    }
    else if (p == 2)
    {
        index = count;
    }
    else if (p == 1)
    {
        cout << "Введите индекс элемента, который нужно удалить: ";
        do {
            cin >> index;
            if (index < 0 || index > count) cout << "Введенного индекса не существует\n\n";
        } while (index < 0 || index > count);
    }
    if (index >= 0 && index <= count)
    {
        count -= 1;
        int* buff = new int[count];
        for (int i = 0; i < index; i++)
        {
            buff[i] = arr[i];
        }
        for (int i = index; i < count; i++)
        {
            buff[i] = arr[i + 1];
        }
        delete[] arr;
        arr = buff;
        
    }
}
void AddElAfter(int& count, int*& arr)
{
    int element; int number; int z = 0, index;
    cout << "Задайте число, которое будет добавлено в массив: "; cin >> number;
    cout << "Введите элемент, после которого будет подставлено число: "; cin >> element;
    for (int i = 0; i < count && z == 0; i++)
    {
        if (arr[i] == element) { z = 1; index = i; }
    }
    if (z == 0) cout << "\nТаких элементов нет.\n";
    else
    {
        int* buff = new int[count + 1];
        for (int i = 0; i <= index; i++)
        {
            buff[i] = arr[i];
        }
        index++;
        buff[index] = number;
        for (int i = index; i < count; i++)
        {
            buff[i + 1] = arr[i];
        }
        delete[] arr;
        arr = buff;
        count = count + 1;
    }
}
void DelElSpec(int& count, int*& arr)
{
    int element; int z = 0;
    cout << "Введите элемент, который будет удалён: "; cin >> element;
    for (int i = 0; i < count; i++)
    {
        if (arr[i] == element) z++;
    }
    if (z == 0) cout << "\nТаких элементов нет.\n";
    else
    {
        int* buff = new int[count - z];
        z = 0;
        for (int i = 0; i < count; i++)
        {
            if (arr[i] == element)
            {
                z++;
            }
            else buff[i - z] = arr[i];
        }
        delete[] arr;
        arr = buff;
        count = count - z;
    }
}

