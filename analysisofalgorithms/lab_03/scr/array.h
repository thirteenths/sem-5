#pragma once

#include <iostream>
using namespace std;

class Array
{
public:
    Array() = default;
    explicit Array(int &n);
    ~Array();

    void randomArray();
    void sortArray();
    void unsortArray();
    void inputArray();
    void outputArray();

    void sortBubble();
    void sortInsert();
    void sortShaker();

    void quicksort(int left, int right);

    void qsortRecursive(int size);

    //void beginTimeTest();

private:
    void swap(int &a, int &b);
    void move(int s, int e);

private:
    int* array;
    int n = 0;
};