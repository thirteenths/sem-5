#include <iostream>
using namespace std;

#include "array.h"
//#include "processTime.h"
//#include "timeTest.h"

int main()
{
    int n;
    char option;
    cout << "Hey guys, today I gonna..." << endl;
    
    cout << "Input lenght of array: ";
    cin >> n;
    Array A(n);
    
    while(true)
    {
        cout << "Input or generation array? [i/g]: ";
        cin >> option;
        
        if (option == 'i')
        {
            cout << "Input array: ";
            A.inputArray();
        }
        else if (option == 'g')
        {
            A.randomArray();
            cout << "Generation array: ";
            A.outputArray();
        }
        else
        {
            cout << "You are wrong!!! Try agane..." << endl; continue;
        }
        break;
    }
    /*while (true)
    {    
        //cout << "What sort of sorting do you want? (Bubble, Insert, Shaker) [b/i/s]: ";
        //cin >> option;

        if (option == 'b')
        {
            A.sortBubble();
            cout << "Sorted array: ";
            A.outputArray();
        }
        else if (option == 'i')
        {
            A.sortInsert();
            cout << "Sorted array: ";
            A.outputArray();
        }
        else if (option == 's')
        {
            A.sortShaker();
            cout << "Sorted array: ";
            A.outputArray();
        }
        else
        {
            cout << "You are wrong!!! Try agane..." << endl; continue;
        }
        break;
    }   */

    A.quicksort(0, n);

}