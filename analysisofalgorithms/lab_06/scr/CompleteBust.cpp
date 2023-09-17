#include "CompleteBust.h"

void CompleteBust::run(Matrix &A)
{
    getRoutes(A);
}

CompleteBust::CompleteBust(int city)
{
    this->city = city;
    path = new int [city];
    notVisited = new bool [city];
    for (int i = 0; i < city; i++)
    {
        notVisited[i] = true;
    }
}

CompleteBust::~CompleteBust()
{
    delete []path;
    delete []notVisited; 
}

void CompleteBust::getRoutes(Matrix &A)
{
    if (count == city)
    {
        printPath();
        getPathCost(A);
        if (Max < cost)
            Max = cost;
        cout << Max;
    }
    if (!count)
    {
        path[0] = 0;
        count++;
        notVisited[0] = false;
    }
    for (int i = 0; i < city; i++)
    {
        if (notVisited[i])
        {
            notVisited[i] = false;
            path[count++] = i;
            getRoutes(A);
            notVisited[i] = true;
            count--;
        }
        
    }
}

int CompleteBust::getPathCost(Matrix &A)
{
    cost = 0;
    for (int i = 0; i < city - 1; i++)
    {
        cost += A.get(i, i + 1);
    }
    return cost;
}

void CompleteBust::printPath()
{
    cout << "Path: ";
    for (int i = 0; i < city; i++)
    {
        cout << path[i] << " ";
    }
    cout << endl;
}