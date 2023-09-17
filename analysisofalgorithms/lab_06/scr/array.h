#pragma once

#include <iostream>
using namespace std;

#define LEN 100;

class Array
{
public:
    //Array() = default;
    explicit Array();
    ~Array();

    void randomArray();
    void sortArray();
    void unsortArray();
    void inputArray();
    void outputArray();

    void add(int value);
    int get(int index);
    void del(int index);

    void sortBubble();
    void sortInsert();
    void sortShaker();

    //void beginTimeTest();

private:
    void swap(int &a, int &b);

private:
    int* array;
    int n = 0;
};