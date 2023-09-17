#include "levenshtein.h"

Levenshtein::Levenshtein(char *A, char *B)
{
    n = strlen(A);
    m = strlen(B);

    fString = new char[n];
    sString = new char[m];

    strcpy(fString, A);
    strcpy(sString, B);

    createMatrix(n + 1, m + 1);
}

Levenshtein::~Levenshtein()
{
    delete[]fString;
    delete[]sString;
    deleteMatrix();
}

int Levenshtein::recursive()
{
    int i = n;
    int j = m;
    return getDistance(i, j);
}

int Levenshtein::getDistance(int i, int j)
{
    if (!i)
        return j;
    if (!j)
        return i;
    flag = 1;
    if (fString[i - 1] == sString[j - 1])
        flag = 0;
    return min(min(getDistance(i, j - 1) + 1, getDistance(i - 1, j) + 1), getDistance(i - 1, j - 1) + flag);      
}

int Levenshtein::iterativeMatrix()
{
    resetMatrix();
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < m + 1; j++)
        {
            if (fString[i - 1] == sString[j - 1])
                flag = 0;
            else
                flag = 1;
            matrix[i][j] = min(matrix[i - 1][j] + 1, min(matrix[i][j - 1] + 1, matrix[i - 1][j - 1] + flag));        
        }
    }
    outputMatrix();
    return matrix[n][m];
}

int Levenshtein::recursiveMatrix()
{
    resetMatrix();
    int i = n;
    int j = m;
    getDistanceRec(i, j);
    
    outputMatrix();
    return matrix[n][m];
}

int Levenshtein::getDistanceRec(int i, int j)
{
    if (matrix[i][j] != -1)
        return matrix[i][j];
    if (!i)
    {
        matrix[i][j] = j;
        return matrix[i][j];
    }    
    if (!j)
    {
        matrix[i][j] = i;
        return matrix[i][j];
    }
    flag = 1;
    if (fString[i - 1] == sString[j - 1])
        flag = 0;
    matrix[i][j] = min(min(getDistance(i, j - 1) + 1, getDistance(i - 1, j) + 1),
     getDistance(i - 1, j - 1) + flag);    
    return matrix[i][j];
}

int Levenshtein::damerauLevenshtein()
{
    resetMatrix();
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < m + 1; j++)
        {
            if (fString[i - 1] == sString[j - 1])
                flag = 0;
            else
                flag = 1;
            matrix[i][j] = min(matrix[i - 1][j] + 1, min(matrix[i][j - 1] + 1, matrix[i - 1][j - 1] + flag)); 
            if ((i > 1) && (j > 1)  && ((fString[i - 1] == sString[j - 2]) || (fString[i - 2] == sString[j - 1])))
                matrix[i][j] = min(matrix[i][j], matrix[i - 2][j - 2] + 1);      
        }
    }
    outputMatrix();
    return matrix[n][m];
}

void Levenshtein::createMatrix(const int &n, const int &m)
{
    //this->n = n;
    //this->m = m;
    matrix = new int *[n];
    for (int i = 0; i < n; i++)
        matrix[i] = new int [m];
}

void Levenshtein::resetMatrix()
{      
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            matrix[i][j] = -1;
            if (!(i))
                matrix[i][j] = j;
            if (!(j))
                matrix[i][j] = i;    
        }
}

void Levenshtein::deleteMatrix()
{
    for(int i; i < n; i++)
        delete []matrix[i];
    delete []matrix;  
}

void Levenshtein::outputMatrix()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout << matrix[i][j] << " ";
        cout << endl;    
    }
}