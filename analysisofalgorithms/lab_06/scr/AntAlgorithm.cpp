#include "AntAlgorithm.h"


AntAlgorithm::AntAlgorithm(int count)
{
    this->count = count;
    ant = new Ant[count];

    for (int i = 0; i < count; i++)
    {
        bestWay.add(i);
    }
}

AntAlgorithm::~AntAlgorithm()
{
    delete []ant;
}


void AntAlgorithm::initAnt()
{
    for (int i = 0; i < count; i++)
    {
        ant[i].way.add(i);
        for (int j = 0; j < count; j++)
        {
            if (j != i)
                ant[i].route.add(j);
        }
    }
}

int AntAlgorithm::costWay(Matrix &A, Array &way)
{
    int cost = 0;
    for (int i = 1; i < count; i++)
    {
        cost += A.get( (way.get(i - 1)), (way.get(i)));
    }
    return cost;
}

void AntAlgorithm::run(Matrix &A, int tMAX)
{
    //init
    initAnt();
    for(int i = 0; i < count; i++)
    {
        ant[i].way.outputArray();
        ant[i].route.outputArray();
        cout << endl;
    }

    bestWay.outputArray();
    cout << costWay(A, bestWay);
}