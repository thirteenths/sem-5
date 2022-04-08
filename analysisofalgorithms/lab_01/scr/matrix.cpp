#include "matrix.h"

Matrix::Matrix(const int &n, const int &m)
{
    this->n = n;
    this->m = m;
    matrix = new int *[n];
    for (int i = 0; i < n; i++)
        matrix[i] = new int [m];
}

Matrix::~Matrix()
{
    for(int i; i < n; i++)
        delete []matrix[i];
    delete []matrix;    
}

void Matrix::inputMatrix()
{
    for (int i = 0; i < n; i++)
        for (int j=0; j < m; j++)
            cin >> matrix[i][j];
}

void Matrix::outputMatrix()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout << matrix[i][j] << " ";
        cout << endl;    
    }
}

int Matrix::get(int &i, int &j)
{
    return matrix[i][j];
}

void Matrix::classicMultiplication(Matrix &A, Matrix &B)
{
    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->m; j++)
            this->matrix[i][j] = 0;

    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->m; j++)
            for (int k = 0; k < this->n; k++)
                this->matrix[i][j] += A.matrix[i][k] * B.get(k, j);
}

void Matrix::vinogradMultiplication(Matrix &A, Matrix &B)
{

}