#include "array.h"
#include "getCPUTime.h"

int main()
{
    int countSizes = 6;
    int sizes[] = {100, 200, 300, 1000, 10000, 100000};
    int count[] = {1000, 100, 100, 100, 10, 1};

    {
    double startTime, endTime, countTime;

    for (int i = 0; i < countSizes; i++)
        {
            Array testArray(sizes[i]);
            testArray.randomArray();
            
            double finishTime = 0;

            for (int j = 0; j < count[i]; j++)
            {
                //t.StartCounter();
                startTime = getCPUTime();
                testArray.sortBubble();
                endTime = getCPUTime();
                finishTime = endTime - startTime;
                //finishTime += t.GetCounter();
            }

            finishTime /= count[i];
            
            std::cout << "\nFor " << "Bubble" << "\t-> Size - " << sizes[i] << "\t\tTime - " << finishTime << "c";

        }

        std::cout << "\n---------------------";
    }

    {
        //ProcessTime t;
    double startTime, endTime, countTime;    
    for (int i = 0; i < countSizes; i++)
    {
        Array testArray(sizes[i]);
        testArray.randomArray();
        
        double finishTime = 0;

        for (int j = 0; j < count[i]; j++)
        {
            //t.StartCounter();
            
            startTime = getCPUTime();
            testArray.sortInsert();    
            endTime = getCPUTime();
            finishTime = endTime - startTime;
            //finishTime += t.GetCounter();
        }

        finishTime /= count[i];
        
        std::cout << "\nFor " << "Insert" << "\t-> Size - " << sizes[i] << "\t\t Time - " << finishTime << "c";

    }
    }

    std::cout << "\n---------------------";

    {
        //ProcessTime t;
    double startTime, endTime, countTime;    
    for (int i = 0; i < countSizes; i++)
    {
        Array testArray(sizes[i]);
        testArray.randomArray();
        
        double finishTime = 0;

        for (int j = 0; j < count[i]; j++)
        {
            //t.StartCounter();
            startTime = getCPUTime();
            testArray.sortShaker();
            endTime = getCPUTime();
            finishTime = endTime - startTime;
            //finishTime += t.GetCounter();
        }

        finishTime /= count[i];
        
        std::cout << "\nFor " << "Shaker" << "\t-> Size - " << sizes[i] << "\t\tTime - " << finishTime << "c";

    }
    }

    

        {
    double startTime, endTime, countTime;

    for (int i = 0; i < countSizes; i++)
        {
            Array testArray(sizes[i]);
            testArray.sortArray();
            
            double finishTime = 0;

            for (int j = 0; j < count[i]; j++)
            {
                //t.StartCounter();
                startTime = getCPUTime();
                testArray.sortBubble();
                endTime = getCPUTime();
                finishTime = endTime - startTime;
                //finishTime += t.GetCounter();
            }

            finishTime /= count[i];
            
            std::cout << "\nFor " << "Bubble" << "\t-> Size - " << sizes[i] << "\t\tTime - " << finishTime << "c";

        }

        std::cout << "\n---------------------";
    }

    {
        //ProcessTime t;
    double startTime, endTime, countTime;    
    for (int i = 0; i < countSizes; i++)
    {
        Array testArray(sizes[i]);
        testArray.sortArray();
        
        double finishTime = 0;

        for (int j = 0; j < count[i]; j++)
        {
            //t.StartCounter();
            
            startTime = getCPUTime();
            testArray.sortInsert();    
            endTime = getCPUTime();
            finishTime = endTime - startTime;
            //finishTime += t.GetCounter();
        }

        finishTime /= count[i];
        
        std::cout << "\nFor " << "Insert" << "\t-> Size - " << sizes[i] << "\t\t Time - " << finishTime << "c";

    }
    }

    std::cout << "\n---------------------";

    {
        //ProcessTime t;
    double startTime, endTime, countTime;    
    for (int i = 0; i < countSizes; i++)
    {
        Array testArray(sizes[i]);
        testArray.sortArray();
        
        double finishTime = 0;

        for (int j = 0; j < count[i]; j++)
        {
            //t.StartCounter();
            startTime = getCPUTime();
            testArray.sortShaker();
            endTime = getCPUTime();
            finishTime = endTime - startTime;
            //finishTime += t.GetCounter();
        }

        finishTime /= count[i];
        
        std::cout << "\nFor " << "Shaker" << "\t-> Size - " << sizes[i] << "\t\tTime - " << finishTime << "c";

    }
    }
          {
    double startTime, endTime, countTime;

    for (int i = 0; i < countSizes; i++)
        {
            Array testArray(sizes[i]);
            testArray.unsortArray();
            
            double finishTime = 0;

            for (int j = 0; j < count[i]; j++)
            {
                //t.StartCounter();
                startTime = getCPUTime();
                testArray.sortBubble();
                endTime = getCPUTime();
                finishTime = endTime - startTime;
                //finishTime += t.GetCounter();
            }

            finishTime /= count[i];
            
            std::cout << "\nFor " << "Bubble" << "\t-> Size - " << sizes[i] << "\t\tTime - " << finishTime << "c";

        }

        std::cout << "\n---------------------";
    }

    {
        //ProcessTime t;
    double startTime, endTime, countTime;    
    for (int i = 0; i < countSizes; i++)
    {
        Array testArray(sizes[i]);
        testArray.unsortArray();
        
        double finishTime = 0;

        for (int j = 0; j < count[i]; j++)
        {
            //t.StartCounter();
            
            startTime = getCPUTime();
            testArray.sortInsert();    
            endTime = getCPUTime();
            finishTime = endTime - startTime;
            //finishTime += t.GetCounter();
        }

        finishTime /= count[i];
        
        std::cout << "\nFor " << "Insert" << "\t-> Size - " << sizes[i] << "\t\t Time - " << finishTime << "c";

    }
    }

    std::cout << "\n---------------------";

    {
        //ProcessTime t;
    double startTime, endTime, countTime;    
    for (int i = 0; i < countSizes; i++)
    {
        Array testArray(sizes[i]);
        testArray.unsortArray();
        
        double finishTime = 0;

        for (int j = 0; j < count[i]; j++)
        {
            //t.StartCounter();
            startTime = getCPUTime();
            testArray.sortShaker();
            endTime = getCPUTime();
            finishTime = endTime - startTime;
            //finishTime += t.GetCounter();
        }

        finishTime /= count[i];
        
        std::cout << "\nFor " << "Shaker" << "\t-> Size - " << sizes[i] << "\t\tTime - " << finishTime << "c";

    }
    }

    std::cout << "\n---------------------\n";
}