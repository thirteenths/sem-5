#include <iostream>
#include "matrix.h"
using namespace std;

int main()
{
    int n, m;
    cout << "Введите n: ";
    cin >> n;
    cout << "Введите m: ";
    cin >> m;
    Matrix A(n,m);

    cout << "Введите матрицу\n";
    A.inputMatrix();
    
    cout << "Введите n: ";
    cin >> n;
    cout << "Введите m: ";
    cin >> m;
    Matrix B(n,m);

    cout << "Введите матрицу\n";
    B.inputMatrix();

    //cout << A.row() << B.column();

    Matrix M(A.row(), B.column());
    M.classicMultiplication(A, B);

    cout << "Классический алгоритм\n";
    M.outputMatrix();

    cout << "Алгоритм Винограда\n";
    Matrix N(A.row(), B.column());
    N.vinogradMultiplication(A, B);

    N.outputMatrix();

    cout << "Алгоритм оптимезированного Винограда\n";
    Matrix H(A.row(), B.column());
    H.vinogradMultiplication(A, B);

    H.outputMatrix();
}