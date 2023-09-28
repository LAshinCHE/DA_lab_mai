#include "sorting.hpp"

void nSorting::CountingSort(nKeyAndValue::TDict& d, nKeyAndValue::TDict& tempDict,const int& digit,const int& dictSize,const int& bitShift){
    const int bitMask = 256;
    int bitArray[bitMask]  = {0};
    int dataByte;

    for (int i = 0; i < dictSize; i++){
        dataByte =  (d.data[i].key >> bitShift) & (bitMask - 1);
        bitArray[dataByte] += 1; 
    }
    
    for (int i = 1; i < bitMask; i++)
        bitArray[i] = bitArray[i - 1] + bitArray[i];


    for (int i = dictSize - 1; i >= 0; i--){
        dataByte = (d.data[i].key >> bitShift) & (bitMask - 1);
        tempDict.data[bitArray[dataByte] - 1] = d.data[i];
        bitArray[dataByte] -= 1;
    }

}

void nSorting::RadixSort(nKeyAndValue::TDict& d, const unsigned long long& maxKey,const int& dictSize){
    nKeyAndValue::TDict tempDict(dictSize); 
    for (int digit =  0 ; digit < 8 ; digit++){
        if ((digit & 1) == 0)
            nSorting::CountingSort(d,tempDict,digit, dictSize,digit * 8);
        else
            nSorting::CountingSort(tempDict,d,digit, dictSize,digit * 8);
    }
    
}


void nSorting::BubbleSort(nKeyAndValue::TDict& d, const int& dictSize) {
    for (int i = 0; i < dictSize - 1; i++) {
        for (int j = 0; j < dictSize - i - 1; j++) {
            if (d.data[j].key > d.data[j + 1].key) {
                std::swap(d.data[j], d.data[j + 1]);
            }
        }
    }
}