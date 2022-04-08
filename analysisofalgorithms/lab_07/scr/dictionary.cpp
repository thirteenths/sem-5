#include "dictionary.h"

Dictionary::Dictionary(std::string fname){
    count = 2000;
    std::ifstream fin(fname);
    char buff[100];
    for (int i = 0; i < count; i++){
        fin >> arr[i].key;
        fin.getline(buff, 100);
        arr[i].value = buff;
    }
    fin.close();
    sort();

    for (int i = 0; i < 10; i++)
    {
        seg[i].first = (char)i;
    }
    createSeg();
}

Dictionary::~Dictionary(){
    
}

void Dictionary::output(){
    for (int i = 0; i < 2000; i++)
        std::cout << i << " " << arr[i].key << " " << arr[i].value << '\n' ;
}

void Dictionary::createSeg(){
    int f;
    
    for (int i = 0; i < count; i++)
    {
        f = arr[i].key[0] - '0';
        seg[f].arrInt.push_back(i);
        //std::cout << f;
    }
}

std::string Dictionary::completeBust(std::string key){
    std::string val = "meh";
    for (int i = 0; i < count; i++){
        if (key == arr[i].key)
            val = arr[i].value;
    }
    return val;
}

void Dictionary::swap(int i, int j)
{
    std::string key, value;
    key = arr[i].key;
    value = arr[i].value;

    arr[i].key = arr[j].key;
    arr[i].value = arr[j].value;

    arr[j].key = key;
    arr[j].value = value;
}

void Dictionary::sort()
{
    for (int i = 0; i < count; i++)
        for (int j = i; j < count; j++)
        {
            if (arr[i].key > arr[j].key)
                swap(i, j);
        }
}

std::string Dictionary::binSearch(std::string key, int start, int end){
    
    std::string val = "meh";
    //std::cout << "\n" << start << " " << end << " " << arr[start].key << " " << key << " "  << arr[end].key <<"\n";
    if (end - start < 2)
    {
        if (key == arr[start].key)
            return arr[start].value;
        if (key == arr[end].key)
            return arr[end].value;    
        return val;
    }
    int mid = (end - start)/2;
    if (key == arr[mid + start].key)
        return arr[mid + start].value;
    if (key > arr[mid + start].key)
        return binSearch(key, start + mid, end);
    else
        return binSearch(key, start, start + mid);
    //return val;
}

std::string Dictionary::freqAnalysis(std::string key){
    int f = key[0] - '0';
    int s; 
    //std::cout << key[0] << " " << f << " " << seg[f].arrInt.size();
    int size = seg[f].arrInt.size();
    //std::cout << seg[f].arrInt[0] << " " << seg[f].arrInt[size - 1];
    return binSearch(key, seg[f].arrInt[0], seg[f].arrInt[size - 1]);

    /*for (int i = 0; i < seg[f].arrInt.size(); i++){
        s = seg[f].arrInt[i];
        if (key == arr[s].key)
        {
            return arr[s].value;
        }
    }*/
    return "meh"    ;
}