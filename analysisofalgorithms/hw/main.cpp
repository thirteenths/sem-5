//#include <stdafx.h>
#include <limits>
#include <limits.h>
#include <iostream>
using namespace std;
const int V=6;


//алгоритм Дейкстры
void Dijkstra(int GR[V][V], int st)
{
    int distance[V], count, index, i, u, m=st+1; //1
    bool visited[V];                             //2
    for (i = 0; i < V; i++)                      //3
    {
        distance[i] = INT_MAX;                   //4
        visited[i] = false;                      //5
    }
    distance[st] = 0;                            //6
    for (count = 0; count < V - 1; count++)      //7
    {
        int min = INT_MAX;                       //8
        for (i = 0; i < V; i++)                  //9
            if (!visited[i] && distance[i] <= min) //10
            {
                min = distance[i];                 //11
                index = i;                         //12
            }
            u = index;                             //13
            visited[u] = true;                     //14
        for (i = 0; i < V; i++)                    //15
            if (!visited[i] && GR[u][i] && distance[u] != INT_MAX && distance[u] + GR[u][i] < distance[i]) //16
                distance[i] = distance[u] + GR[u][i];  //17
    }
    cout<<"Стоимость пути из начальной вершины до остальных:\t\n";
    for (i = 0; i < V; i++) 
    
    if (distance[i] != INT_MAX)
        cout << m << " > " << i + 1 << " = " << distance[i] << endl;
    else 
        cout << m << " > " << i + 1 << " = " << "маршрут недоступен" << endl;
}
//главная функция
int main()
{
    setlocale(LC_ALL, "Rus");
    int start, GR[V][V]={
    {0, 1, 4, 0, 2, 0},
    {0, 0, 0, 9, 0, 0},
    {4, 0, 0, 7, 0, 0},
    {0, 9, 7, 0, 0, 2},
    {0, 0, 0, 0, 0, 8},
    {0, 0, 0, 0, 0, 0}};
    cout<<"Начальная вершина >> "; 
    cin>>start;
    Dijkstra(GR, start-1);
//system("pause>>void");
}