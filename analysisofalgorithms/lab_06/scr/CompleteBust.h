#include "matrix.h"
#include "iostream"
using namespace std;

class CompleteBust
{
public:
    CompleteBust(int city);
    ~CompleteBust();

    void run(Matrix &A);
private:
    void getRoutes(Matrix &A);
    int getPathCost(Matrix &A);
    void printPath();


private:
    int count = 0;   
    int cost = 0;
    int Max = 0;
    int city = 0;
    int *path; 
    bool *notVisited;
};