#include <iostream>
using namespace std; 

bool checkPrimeNumber(int n) 
{ 
    bool isPrime = true; 
    if (n == 0 || n == 1 || n < 0) 
    { 
        isPrime = false;
    } 
    else 
    { 
        for (int i = 2; i <= n / 2; ++i) 
        { 
            if (n % i == 0) 
            { 
                isPrime = false; break; 
            } 
        } 
    } 
    return isPrime; 
}

int main() 
{ 
    int n; 
    cout << "\nEnter a positive integer: "; 
    cin >> n; 
    if (checkPrimeNumber(n)) 
        cout << n << " is a prime number.\n"; 
    else 
        cout << n << " is not a prime number.\n"; 
    return 0; 
} 


