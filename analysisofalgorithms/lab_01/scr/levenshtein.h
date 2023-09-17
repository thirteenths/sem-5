#include <string>
#include <math.h>
#include <iostream>
#include <cstring>
using namespace std;


class Levenshtein
{
public:
    Levenshtein() = default;
    Levenshtein(char *A, char *B);
    ~Levenshtein();

    int recursive();
    int recursiveMatrix();
    int iterativeMatrix();
    int damerauLevenshtein();

private:
    int getDistance(int i, int j);
    int getDistanceRec(int i, int j);
    
    void createMatrix(const int &n, const int &m);
    void resetMatrix();
    void deleteMatrix();
    void outputMatrix();

private:
    char * fString;
    char * sString;
    int** matrix;
    int n, m;
    int flag;
};