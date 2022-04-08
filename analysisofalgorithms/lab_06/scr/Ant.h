#pragma once

#include "matrix.h"
#include "array.h"

typedef struct 
{
    Array way; //посетил
    Array route; //должен посетить
} Ant;

/*class Ant
{
public:
    Ant(int count);
    ~Ant();

    void generateAnts(int n);
    void choiceNextCity(Matrix &pheromones, Matrix &A, double alpha, double beta);
    void antsChooseWay();
private:
    bool *way; //
    int wayCount = 0; // кол-во городов
    int *route;
    int routeCount = 0; // кол-во посещенных городов
    
};*/