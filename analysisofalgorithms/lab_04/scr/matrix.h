#include <memory>
#include <iostream>
using namespace std;

#include <mutex>
#include <vector>
#include <thread>

#pragma once

class Matrix
{
public:
    Matrix() = default;
    Matrix(const int &n, const int &m);

    ~Matrix();

    void inputMatrix();
    void outputMatrix();
    void generation();

    int get(int i, int j);
    void set(int &i, int &j, int &value);

    int column(){return m;}
    int row(){return n;}


    void algFloyd();
    void algFloydThread(int count);
    void algFloydParallel(int threadCnt);


    //void classicMultiplication(Matrix A, Matrix B);


private:
    int** matrix;
    int n, m;
    mutex mtx;
};