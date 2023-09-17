#include <iostream>
#include <string>

using namespace std;

#include "levenshtein.h"

int main()
{
    char a[100];
    char b[100];
    cout << "Hey guys, today I gonna..." << endl;

    cout << "Input first string: ";
    cin >> a;

    cout << "Input second string: ";
    cin >> b;

    Levenshtein l(a, b);

    cout << "Recursive : " << l.recursive() << endl;

    cout << "Recursive + Matrix: " << l.recursiveMatrix() << endl;

    cout << "Iterative Matrix: " << l.iterativeMatrix() << endl;

    cout << "DamerauLevenshtein: " << l.damerauLevenshtein() << endl;
}