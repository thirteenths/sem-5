#pragma once

#include "matrix.h"
#include "Ant.h"


class AntAlgorithm
{
public:
    AntAlgorithm(int count);
    ~AntAlgorithm();
    void run(Matrix &A, int tMAX);
private:
    int calculateQ();
    void addPheromones();
    void correctPheromones();
    void evaporation();

    void initAnt();
    int costWay(Matrix &A, Array &way);

    //friend class Ant;

private:
    double alpha;
    double beta;
    double e;
    double Q;
    double tau0;

    int *path;
    int Max = 0;
    int cost = 0;

    int count;

    Ant *ant;
    Array bestWay;
    //Ant Ants();
};