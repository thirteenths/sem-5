#include <iostream>
using namespace std;

long double fact(int N)
{
    if(N < 0) 
        return 0; 
    if (N == 0) 
        return 1; 
    else 
        return N * fact(N - 1); 
}

int main()
{
    int N;
    cout << "Input number to calculate the factorial: ";
    cin >> N;
    int result = fact(N);
    if (result)
        cout << "Factorial " << N << " = " << fact(N) << endl << endl; 
    else
        cout << "Error";    
    return 0;
}