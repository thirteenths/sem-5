#include <string>
#include <fstream>
#include <iostream>
#include <vector>

struct entry{
    std::string value;
    std::string key;
} ;

struct segment{
    char first;
    std::vector<int> arrInt;
};


class Dictionary{
public:
    Dictionary(std::string fname);
    ~Dictionary();

    std::string completeBust(std::string key);
    std::string binSearch(std::string key, int start, int end);
    std::string freqAnalysis(std::string key);


    void output();

private:
    void createSeg();
    void bin(std::string key, int start, int end);
    void sort();
    void swap(int i, int j);


private:
    int count;
    entry arr[2000];
    segment seg[10];
};

