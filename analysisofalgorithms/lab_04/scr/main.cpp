#include <iostream>
using namespace std;

#include "getCPUTime.h"

#include "matrix.h"

#include <ctime>

void beginTimeTest()
{
    int countSize = 5;
    int sizes[] = { 32, 100, 250, 500, 1000  };

    char algorithmNames[][100] = {"Classic Floyd", "Parallel Floyd"};

    //for (int k = 0; )
    for (int i = 0; i < countSize; i++)
    {
        Matrix A(sizes[i], sizes[i]);
        A.generation();
        
        double finishTime = 0;
        
        double startTime, endTime, countTime;

        for (int j = 0; j < 10; j++)
        {
            startTime = clock();
            A.algFloyd();
            endTime = clock();
            finishTime += (endTime - startTime)/ CLOCKS_PER_SEC;
            //StartCounter();
            //classicMultiplication(a, b, sizes[i], sizes[i], sizes[i]);
            //finishTime += GetCounter();
        }

        finishTime /= 10;

        cout << "\nFor " << algorithmNames[0] << "\t-> Row - " << sizes[i] 
                                              << "\tColumn - " << sizes[i]
                                              << "\tTime - " << finishTime;
    }

    cout << "\n\n";

    //matrixType (*algorithms[])(matrixType, matrixType, int, int, int, int) = {multiplicationParallelRow, 
                                                                              //multiplicationParallelColumn};
    /*Индекс отвечает за смену имени алгоритмов*/
    int p = 1;

    int nThreads[] = { 1, 2, 4, 8, 16, 32 };

    
        for (int i = 0; i < countSize; i++)
        {
            for (int threads = 0; threads < 6; threads++)
            {
                Matrix B(sizes[i], sizes[i]);
                B.generation();
                //matrixType a = generateMatrix(sizes[i], sizes[i]);
                //matrixType b = generateMatrix(sizes[i], sizes[i]);

                double finishTime = 0;
                double startTime, endTime, countTime;

                for (int j = 0; j < 10 ; j++)
                {
                    startTime = clock();//getCPUTime();
                    B.algFloydThread(nThreads[threads]);
                    endTime = clock();//getCPUTime();
                    finishTime += (endTime - startTime) /  CLOCKS_PER_SEC;
                    //StartCounter();
                    //mult(a, b, sizes[i], sizes[i], sizes[i], nThreads[threads]);
                    //finishTime += GetCounter();
                }

                finishTime /= 10;

                cout << "\nFor " << algorithmNames[1] << "\t-> Row - " << sizes[i] 
                                              << "\tColumn - " << sizes[i]
                                              << "\tTime - " << finishTime
                                              << "\tTreads - " << nThreads[threads];

                /*Индекс отвечает за смену имени алгоритмов*/

            }
            cout << "\n\n";
        }
    
}


int main()
{
    beginTimeTest();
    int n;
    cout << "Size: ";
    cin >> n;
    Matrix A(n, n);
    //A.inputMatrix();
    //A.algFloyd();
    //A.outputMatrix();

    //Matrix B(n, n);
    //B.inputMatrix();
    //B.algFloydParallel(2);

    //B.outputMatrix();

    return 0;
}