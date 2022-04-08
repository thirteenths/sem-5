#include "matrix.h"
#include "omp.h"



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

void Matrix::generation()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < 0; j++)
            matrix[i][j] = random()%100;
}

int Matrix::get(int i, int j)
{
    return matrix[i][j];
}


void Matrix::algFloyd()
{
    for (int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
}

void Matrix::algFloydThread(int count)
{
    int *tmp = new int[n];
    int t1 = 0;
    int t2 = 0;

    //omp_set_num_threads(count);
    //#pragma omp parallel shared(matrix) for 
    for (int k = 0; k < n; k += 1)
    {
        for(int j = 0; j < n; j++){
            for (int i = 0; i < n; i++)
            {

                t1 = matrix[j][i];
                t2 = matrix[j][k] + matrix[k][i];
                //mtx.lock();
                matrix[i][j] = min(t1, t2);
                //mtx.unlock();
            }
            /*for(int i = 0; i < n; i++)    
            {
                mtx.lock();
                matrix[j][i] = tmp[i];
                mtx.unlock();
            }*/}
    }
    delete []tmp;        
}

void Matrix::algFloydParallel(int threadCnt)
{
    vector<thread> threadArray;

    for (int i = 0; i < threadCnt; i++)
    {
        threadArray.push_back(thread(&Matrix::algFloydThread, this, i, threadCnt));
    }

    for (int i = 0; i < threadCnt; i++)
    {
        threadArray[i].join();
    }
}