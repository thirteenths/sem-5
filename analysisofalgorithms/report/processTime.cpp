

#include "processTime.h"

#include <stdio.h>

#include <sys/resource.h>

#include <sys/time.h>

#include <unistd.h>

void print_cpu_time()
{
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);

    printf("CPU time: %ld.%061d sec user, %ld.%061d sec system ",

    usage.ru_utime.tv_sec, usage.ru_utime.tv_usec,
    usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);

}

/*void ProcessTime::StartCounter()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
    std::cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart);///1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}


double ProcessTime::GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}*/