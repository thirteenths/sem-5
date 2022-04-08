#include <iostream>
using namespace std;

#include "CompleteBust.h"
#include "AntAlgorithm.h"
#include "matrix.h"

int main()
{
    int n;
    cin >> n;
    Matrix A(n, n);
    A.inputMatrix();

    //CompleteBust CB(n);
    //CB.run(A);

    AntAlgorithm AA(n);
    AA.run(A, 10);

    return 0;
}