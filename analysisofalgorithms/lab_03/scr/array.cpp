#include "array.h"

Array::Array(int &n)
{
    this->n = n;
    array = new int[n];
}

Array::~Array()
{
    delete []array;
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

// void Array::beginTimeTest()
// {
//     int iteration = 5;
//     int sizes[] = {100, 200, 300, 1000, 10000};
//     int count[] = {100, 100, 100, 10, 1}

//     for (int i = 0; i < iteration; i++)
//     {
        
//     }
// }

void Array::move(int s, int e)
{
    int f = std::abs(s - e)/ (s - e);
    for (int i = s; i < e; i += f)
    {
        swap(array[i], array[i + 1]);
    }
}



void Array::quicksort(int left, int right)
{
    std::cout << left << " " << right << endl;
    if (std::abs(right - left)  <= 2)
        return;

    int index = left + (right - left) / 2;
    int ind_l = index;
    int ind_r = index;
    int flag = 0;
    int flag_l = left;
    int flag_r = right;

    while (true)
    {
        flag = 0;
        flag_l = 0;
        flag_r = 0;
        for (int i = left; i < index; i++)
        {
            if (array[i] > array[index])
                {ind_l = i; flag_l++;  break;}
        }

        for (int j = right; j > index; j--)
        {
            if (array[j] < array[index])
            {
                {ind_r = j; flag_r++;  break;}
            }
        }
        if (flag_r + flag_l == 2)
            swap(array[ind_r], array[ind_l]);
        else if (flag_l)
            move(index, ind_l);
        else if (flag_r)
            move(index, ind_r);       
        else break;    
    }

    outputArray();

    //quicksort(left, index);
    //quicksort(index, right);
    

}


void Array::qsortRecursive(int size) {\
    //Указатели в начало и в конец массива
    int i = 0;
    int j = size - 1;

    //Центральный элемент массива
    int mid = array[size / 2];

    //Делим массив
    do {
        //Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        //В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
        while(array[i] < mid) {
            i++;
        }
        //В правой части пропускаем элементы, которые больше центрального
        while(array[j] > mid) {
            j--;
        }

        //Меняем элементы местами
        if (i <= j) {
            int tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);


    //Рекурсивные вызовы, если осталось, что сортировать
    if(j > 0) {
        //"Левый кусок"
        qsortRecursive( j + 1);
    }
    if (i < size) {
        //"Првый кусок"
        qsortRecursive(&mas[i], size - i);
    }
}