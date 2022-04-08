#include "conveyor.h"

#include <iostream>
#include <fstream>

int main(void)
{
    int nconveyors = 20;
    int nrequest = 200;

    Conveyor *conveyors[20];
    double times[200][9] { 0 };

    for (int i = 0; i < nconveyors; i++)
    {
        conveyors[i] = new Conveyor(nrequest, 1000000);
        conveyors[i]->run();
    }

    std::list<Request*> results[20];

    for (int i = 0; i < nconveyors; i++)
        results[i] = conveyors[i]->getResult();

    int c;

    // Output time for second part
    //std::cout << ">>> Second part time:\n";
    for (int i = 0; i < nconveyors; i++)
    {
        c = 0;
        for (auto res : results[i])
        {
            times[c][0] += res->timeInSeqondQ();
            times[c][1] += res->timeInThirdQ();
            times[c][2] += res->summaryTimeQ();
            
            times[c][3] = res->timeS[0];
            times[c][4] = res->timeS[1];
            times[c][5] = res->timeS[2];

            times[c][6] = res->timeE[0];
            times[c][7] = res->timeE[1];
            times[c][8] = res->timeE[2];

            c++;
        }
    }
    for (int i = 0; i < nrequest; i++)
    {
        std::cout << i << " " << '\t' << times[i][3] << '\t' << times[i][6] << '\t' << times[i][0] / nconveyors<< '\t' << times[i][4] << '\t' << times[i][7]  << '\t' << times[i][1] / nconveyors<< '\t' << times[i][5] << '\t' << times[i][8]  << '\t' << times[i][2] / nconveyors << '\n';
        times[i][0] = 0;
        times[i][1] = 0;
        times[i][2] = 0;
    }

    //std::cout << "<<< Max time second part" << max(times[0]) ;


    // Output time for third part 
    //std::cout << "\n\n>>> Third part time:\n";
    for (int i = 0; i < nconveyors; i++)
    {
        c = 0;
        for (auto res : results[i])
        {
            //times[c] += res->timeInThirdQ();
            c++;
        }
    }
    for (int i = 0; i < nrequest; i++)
    {
        //std::cout << i << " " << times[i] / nconveyors << '\n';
        //times[i] = 0;
    }


    // Output summary time
    //std::cout << "\n\n>>> Summary time:\n";
    for (int i = 0; i < nconveyors; i++)
    {
        c = 0;
        for (auto res : results[i])
        {
            //times[c] += res->summaryTimeQ();
            c++;
        }
    }
    for (int i = 0; i < nrequest; i++)
    {
        //std::cout << i << " " << times[i] / nconveyors << '\n';
    }

    for (int i = 0; i < nconveyors; i++)
        delete conveyors[i];
}
