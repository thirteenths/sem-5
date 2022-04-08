#include <memory>
#include <iostream>
using namespace std;

class Matrix
{
public:
    Matrix() = default;
    Matrix(const int &n, const int &m);

    ~Matrix();

    void inputMatrix();
    void outputMatrix();

    int get(int &i, int &j);
    void set(int &i, int &j, int &value);

    void classicMultiplication(Matrix &A, Matrix &B);
    void vinogradMultiplication(Matrix &A, Matrix &B);
    void vinogradOptimizationMultiplication(Matrix &A, Matrix &B);

private:
    int** matrix;
    int n, m;
};