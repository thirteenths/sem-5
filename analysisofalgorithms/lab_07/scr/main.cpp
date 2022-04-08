#include <iostream>
using namespace std;

#include "dictionary.h"
#include "getCPUTime.h"

#include <ctime>

void testTime()
{
    int count = 100;
    Dictionary dict("data.txt");
    //------------------------------------------------------
    string key[] = {"0002530407440900", "5091479945279275", "9997951582572083", "8103345577657810", "76598763489"};

    string alg[] = {"CompleteBust\t", "BinSearch\t", "FreqAnalysis\t"};
    string about[] = {"first key\t", "average key\t", "last key\t", "random key\t", "not exist key\t"};

    
    for (int i = 0; i < 5; i++)
    {
        double finishTime = 0;
        double startTime, endTime, countTime;
        
        for (int j = 0; j < count; j++)
        {
            startTime = clock();//getCPUTime();
            dict.completeBust(key[i]);
            endTime = clock();//getCPUTime();
            finishTime += (endTime - startTime);
        }

        finishTime /= count;
        cout << alg[0] << " " << about[i] << " " << finishTime << "\n";
    }

    //------------------------------------------------------
    cout << "---------------------------------------------\n";

    for (int i = 0; i < 5; i++)
    {
        double finishTime = 0;
        double startTime, endTime, countTime;
        
        for (int j = 0; j < count; j++)
        {
            startTime = clock();//getCPUTime();
            dict.binSearch(key[i], 0, 2000);
            endTime = clock();//getCPUTime();
            finishTime += (endTime - startTime);
        }

        finishTime /= count;
        cout <<alg[1] << " " << about[i] << " "  << finishTime << "\n";
    }


    //------------------------------------------------------
    cout << "---------------------------------------------\n";

    for (int i = 0; i < 5; i++)
    {
        double finishTime = 0;
        double startTime, endTime, countTime;
        
        for (int j = 0; j < count; j++)
        {
            startTime = clock();//getCPUTime();
            dict.freqAnalysis(key[i]);
            endTime = clock();//getCPUTime();
            finishTime += (endTime - startTime);
        }

        finishTime /= count;
        cout <<alg[2] << " " << about[i] << " "  << finishTime << "\n";
    }

}

int main()
{
    string key;
    Dictionary dict("data.txt");
    dict.output();

    cout << "---------------------------------------------\n";

    //cin >> key;

    //cout << dict.completeBust(key) << "\n";

    cout << "---------------------------------------------\n";

    //cout << dict.binSearch(key, 0, 2000);

    cout << "---------------------------------------------\n";

    //cout << dict.freqAnalysis(key);

    testTime();

    return 0;
}