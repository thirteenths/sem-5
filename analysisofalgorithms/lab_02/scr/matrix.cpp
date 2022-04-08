#include "matrix.h"

Matrix::Matrix(const int &n, const int &m)
{
    this->n = n;
    this->m = m;
    matrix = new int *[n];
    for (int i = 0; i < n; i++)
        matrix[i] = new int [m];

    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->m; j++)
            this->matrix[i][j] = 0;
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

int Matrix::get(int i, int j)
{
    return matrix[i][j];
}

void Matrix::classicMultiplication(Matrix &A, Matrix &B)
{

    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->m; j++)
            for (int k = 0; k < A.column(); k++)
                this->matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
}

void Matrix::vinogradMultiplication(Matrix &A, Matrix &B)
{
    precomputeRows(A);
    precomputeCols(B);

    for(int i = 0; i < A.row(); i++)
        for (int j = 0; j < B.column(); j++)
        {
            this->matrix[i][j] -= tmpA[i] + tmpB[j];
            for (int k = 0; k < B.row()/2; k++)
            {
                this->matrix[i][j] = this->matrix[i][j] +
                    (A.get(i, k*2) + B.get(k*2 + 1, j)) *
                        (A.get(i, k*2 + 1) + B.get(k*2 , j));
            }
        }

    if (B.row()%2)
    {
        for (int i = 0 ; i < A.row(); i++)
            for (int j = 0; j < B.column(); j++)
            {
                this->matrix[i][j] = this->matrix[i][j] +
                    A.get(i, B.row() - 1) * B.get(B.row() - 1, j);
            }
            
    }

    delete []tmpA;
    delete []tmpB;

}

void Matrix::precomputeRows(Matrix &A)
{
    tmpA = new int [A.row()];

    for (int i = 0; i < A.row(); i++)
    {
        for (int j = 0; j < A.column()/2 ;j++)
        {
            tmpA[i] = tmpA[i] + A.get(i, j*2) * A.get(i, j*2 + 1);
        }
    }
}

void Matrix::precomputeCols(Matrix &B)
{
    tmpB = new int [B.column()];

    for (int i = 0; i < B.column(); i++)
    {
        for (int j = 0; j < B.row()/2 ;j++)
        {
            tmpB[i] = tmpB[i] + B.get(j*2, i) * B.get(j*2 + 1, i);
        }
    }
}

void Matrix::vinogradOptimizationMultiplication(Matrix &A, Matrix &B)
{
    precomputeRowsOpt(A);
    precomputeColsOpt(B);

    int temp = 0;

    for(int i = 0; i < A.row(); i++)
        for (int j = 0; j < B.column(); j++)
        {
            temp = -1*(tmpA[i] - tmpB[j]);
            for (int k = 0; k < B.row()/2; k++)
            {
                temp += (A.get(i, k-1) + B.get(k, j)) *
                    (A.get(i, k) + B.get(k-1, j));
            }
            this->matrix[i][j] = temp;
        }

    if (B.row()%2)
    {
        for (int i = 0 ; i < A.row(); i++)
            for (int j = 0; j < B.column(); j++)
            {
                this->matrix[i][j] += 
                    A.get(i, B.row() - 1) * B.get(B.row() - 1, j);
            }
            
    }

    delete []tmpA;
    delete []tmpB;
}


void Matrix::precomputeRowsOpt(Matrix &A)
{
    tmpA = new int [A.row()];

    for (int i = 0; i < A.row(); i++)
    {
        for (int j = 0; j < A.column() ;j+=2)
        {
            tmpA[i] = A.get(i, j-1) * A.get(i, j);
        }
    }
}

void Matrix::precomputeColsOpt(Matrix &B)
{
    tmpB = new int [B.column()];

    for (int i = 0; i < B.column(); i++)
    {
        for (int j = 0; j < B.row() ;j++)
        {
            tmpB[i] = B.get(j-1, i) * B.get(j, i);
        }
    }
}