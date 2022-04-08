#include "array.h"

Array::Array()
{
    this->n = 0;
    array = new int[100] ;
}

Array::~Array()
{
    delete []array;
}

void Array::add(int value)
{
    array[n] = value;
    n++;
}

int Array::get(int index)
{
    return array[index];
}

void Array::del(int index)
{
    for (int i = index; i < n - 1; i++)
        array[i] = array[i + 1];
    n--;    
}

void Array::inputArray()
{
    for (int i = 0; i < n; i++)
        cin >> array[i];
}

void Array::outputArray()
{
    for (int i = 0; i < n; i++)
        cout << array[i] << " ";
    cout << endl;    
}

void Array::swap(int &a, int &b)
{
    int value = a;
    a = b;
    b = value;
}

void Array::sortBubble()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - 1; j++)
            if (array[j] > array[j + 1])
                swap(array[j], array[j + 1]);
}

void Array::sortInsert()
{
    int key = 0;
    int temp = 0;
    for (int i = 0; i < n - 1; i++)
    {
        key = i + 1;
        temp = array[key];
        for (int j = i + 1; j > 0; j--)
        {
            if (temp < array[j - 1])
            {
                array[j] = array[j - 1];
                key = j - 1;
            }
        }
        array[key] = temp;
    }
}

void Array::sortShaker()
{
    int left = 0;
    int right = n - 1;
    int flag = 1;

    while((left < right))
    {
        //flag = 0;
        for (int i = left; i < right; i++)
        {
            if (array[i] > array[i + 1])
            {
                swap(array[i], array[i + 1]);
                //flag = 1;
            }
        }
        right--;
        for (int i = right; i > left; i--)
        {
            if (array[i - 1] > array[i])
            {
                swap(array[i - 1], array[i]);
                //flag = 1;
            }
        }
        left++;
    }
}

void Array::randomArray()
{
    for (int i = 0; i < n; i++)
        array[i] = rand()%100 + 0;
}


void Array::sortArray()
{
    for (int i = 0; i < n; i++)
        array[i] = i ;
}


void Array::unsortArray()
{
    for (int i = 0; i < n; i++)
        array[i] = n - i;
}

