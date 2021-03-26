#include <iostream>
#include <iomanip>
#include <math.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

using namespace std;



int checkFile();
int GetN();
void newMatrix(double**& M, int n, int m);
void deleteMatrix(double**& M, int n, int m);
void printMatrix(double** M, int n, int m, const char* namematr);
void printVector(double* x, int n, const char* namematr);
void mult(double** M1, double** M2, int n1, int m1, int n2, int m2);
bool minor(double**& M, int n, int m, double& Det);
void transposition(double**& M, int n, int m, int k, double& Det);
bool solveGaus(double**& M, double* x, int n, int m, double& Det);
double determinant(double** M, int n, int m);
void choose(double**& M, int n, int m);
void clone(double**& M, int n, int m, double** M1);
double checkSolve(double** M1, int n, int m, double* x);
bool inverseMatrix(double** A, int n, int m, double& Det, double**& rev);


int main() {
    setlocale(LC_ALL, "Russian");

    int choice = 1;
    double det = 1;
    int n;

    int check = checkFile();
    if (!check) {
        cout << "Файл содержит ошибку или не существует!" << endl;
        return 0;
    }

    cout << "Лабораторная работа №2" << endl;
    cout << "Введите размер матрицы: ";
    n = GetN();

    do {
        int m = n + 1;
        double** A;
        double** A1;
        double** rev;
        double* x = new double[n];

        newMatrix(A, n, m);
        choose(A, n, m);

        newMatrix(A1, n, m);
        clone(A, n, m, A1);

        newMatrix(rev, n, n);
        printMatrix(A, n, m, "A");

        if (solveGaus(A, x, n, m, det)) {
            printVector(x, n, "x");
            cout << "Эпсилон  = " << checkSolve(A1, n, m, x) << endl << endl;
        }
        else cout << "Нет решений" << endl;

        cout << "Определитель матрицы = " << det * determinant(A, n, m) << endl;

        if (inverseMatrix(A1, n, m, det, rev)) {
            printMatrix(rev, n, n, "Обратная матрица:");
            mult(A1, rev, n, m - 1, n, n);
        }
        else cout << "Обратной матрицы нет" << endl;

        deleteMatrix(A, n, m);
        deleteMatrix(A1, n, m);
        deleteMatrix(rev, n, n);
        delete[] x;
        x = NULL;
    } while (choice);
    return 0;
}

void choose(double**& M, int n, int m) {

    int k;
    cout << "Выберите тип матрицы: " << endl;
    cout << "_______________________" << endl;
    cout << "1. Матрица, заданная явно" << endl;
    cout << "2. Матрица, заданная случайным образом" << endl;
    cout << "3. Единичная матрица" << endl;
    cout << "4. Нулевая матрица" << endl;
    cout << "5. Матрица Гильберта" << endl;
    cout << "_______________________" << endl;
    cin >> k;

        switch (k)
        {


        case 1: {
            system("cls");
            fstream A("array.txt", ios::in);
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    A >> M[i][j];
            A.close();
            break;
        }

        case 2: {
            system("cls");
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++) {
                    M[i][j] = ((rand() % 101) - 50);
                }
            break;
        }

        case 3: {
            system("cls");
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    if (i == j) M[i][j] = 1;
                    else M[i][j] = 0;
            break;
        }

        case 4: {
            system("cls");
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    M[i][j] = 0;
            break;
        }

        case 5: {
            system("cls");
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    M[i][j] = 1. / (i + j + 1);
            break;
        }

        }
     
}

int GetN() {
    float n;

    do {
        cin >> n;
        if (n <= 0 || (n - (int)n))
            cout << "Ошибка, попробуйте снова..." << endl;
    } while (n <= 0 || (n - (int)n));

    return n;
}

void newMatrix(double**& M, int n, int m) {
    M = new double* [n];

    for (int i = 0; i < n; i++)
        M[i] = new double[m];
}

void deleteMatrix(double**& M, int n, int m) {
    for (int i = 0; i < n; i++)
        delete[] M[i];

    delete[] M;
}

void printMatrix(double** M, int n, int m, const char* namematr) {
    cout << endl << " " << namematr << ":" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << setw(15) << M[i][j];
        cout << endl;
    }
    cout << endl;
}

void printVector(double* x, int n, const char* namematr) {
    cout << endl << " " << namematr << ":" << endl;
    for (int i = 0; i < n; i++) {
        cout << setw(5) << x[i];
        cout << endl;
    }
    cout << endl;
}

void transposition(double**& M, int n, int m, int k, double& Det) {
    for (int i = k + 1; i < n; i++) {
        if (M[i][k] != 0) {
            double temp;
            for (int i1 = 0; i1 < m; i1++) {
                temp = M[k][i1];
                M[k][i1] = M[i][i1];
                M[i][i1] = temp;
            }
            Det *= -1;
            break;
        }
    }
}

bool minor(double**& M, int n, int m, double& Det) {
    for (int i = 0; i < n; i++) {
        if (M[i][i] == 0) transposition(M, n, m, i, Det);
        if (M[i][i] == 0) return false;
        for (int i1 = i + 1; i1 < n; i1++)
            for (int i2 = i + 1; i2 < m; i2++)
                M[i1][i2] = M[i][i] * M[i1][i2] - M[i][i2] * M[i1][i];
        for (int j = i + 1; j < n; j++) {
            M[j][i] = 0;
        }
    }

    return true;
}

bool solveGaus(double**& M, double* x, int n, int m, double& Det) {
    double res = 0;

    if (!minor(M, n, m, Det)) return false;

    for (int i = n - 1; i >= 0; i--) {
        res = 0;
        for (int j = i + 1; j <= n - 1; j++)
            res = res - x[j] * M[i][j];
        res += M[i][n];
        x[i] = res / M[i][i];
    }

    return true;
}

double determinant(double** M, int n, int m) {
    double det = 1;

    for (int i = 0; i < n; i++) {
        if (M[i][i] == 0) return 0;
        det *= M[i][i] / pow(M[i][i], n - 1 - i);
    }

    return det;
}

void clone(double**& M, int n, int m, double** M1) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            M1[i][j] = M[i][j];
}

double checkSolve(double** M1, int n, int m, double* x) {
    long double epsilon = 0;
    double s;

    for (int i = 0; i < n; i++) {
        s = 0;
        for (int k = 0; k < m - 1; k++)
            s += M1[i][k] * x[k];
        if (fabs(M1[i][m - 1] - s) > epsilon)
            epsilon = fabs(M1[i][m - 1] - s);
    }

    return epsilon;
}

bool inverseMatrix(double** M, int n, int m, double& Det, double**& rev) {
    double* x = new double[n];
    bool metka = true;

    for (int i = 0; i < n; i++) {
        double** buff;
        newMatrix(buff, n, m);
        clone(M, n, m, buff);
        for (int j = 0; j < n; j++) {
            if (i == j) buff[j][m - 1] = 1;
            else buff[j][m - 1] = 0;
        }
        if (!solveGaus(buff, x, n, m, Det)) metka = false;
        for (int j = 0; j < n; j++)
            rev[j][i] = x[j];
        deleteMatrix(buff, n, m);
    }

    delete[] x;
    x = NULL;
    return metka;
}

void mult(double** M1, double** M2, int n1, int m1, int n2, int m2) {
    double** buff;
    newMatrix(buff, n1, m2);
    double S;
    if (m1 != n2) {
        cout << "Ошибка" << endl;
        deleteMatrix(buff, n1, m2);
    }
    for (int i = 0; i < n1; i++)
        for (int j = 0; j < m2; j++) {
            S = 0;
            for (int k = 0; k < m1; k++)
                S += M1[i][k] * M2[k][j];
            buff[i][j] = S;
        }
    printMatrix(buff, n1, m2, "проверка");
    deleteMatrix(buff, n1, m2);
}

int checkFile() {
    double a;
    int k = 0;
    fstream A("array.txt", ios::in);
    while (A >> a) {
        k++;
    }
    A.close();
    return k;
}