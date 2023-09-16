#include <iostream>
#include <cstring>
using namespace std;

const int MAX_LENGTH = 2048;
const int MAX_KEYS = 1000000;
const int MASK = 256;

struct KeyValue {
    unsigned long long key;
    int value;
};

void countSort(KeyValue*&array,KeyValue*&tempArray,int*&count,int digit, int size){
    memset(count, 0, MASK * sizeof(int));
    unsigned char* bytes = new unsigned char[size];
    for (int i = 0; i < size; i++) {
        bytes[i] = (array[i].key >> (8 * digit)) & (MASK - 1);
        count[bytes[i]]++;
    }
    for (int i = 1; i < MASK; i++) {
        count[i] = count[i-1] + count[i];
    }
    for (int i = size-1; i >= 0; i--) {
        unsigned char byte = bytes[i];
        tempArray[count[byte]-1] = array[i];
        count[byte]--;
    }
    delete[] bytes;
}


int main() {
    KeyValue *array = new KeyValue[MAX_KEYS];
    string *storage = new string[MAX_KEYS];
    int limit = MAX_KEYS;
    int size = 0;
    while (cin >> array[size].key >> storage[size] ) {
        array[size].value=size;
        size++;
        if (limit<size){
            limit = limit + 1000;
            KeyValue *big_array = new KeyValue[limit];
            memcpy(big_array, array, (size-1) * sizeof(KeyValue));
            swap(big_array, array);
            delete[] big_array;
        }
    }

    KeyValue *tempArray = new KeyValue[size];
    int *count = new int[MASK];
    bool flag =0;
    for (int digit = 0; digit < sizeof(unsigned long long); digit++) {
        if((digit & 1) == 0){
            countSort(array,tempArray,count, digit, size);
            flag =1;
        } else {
            countSort(tempArray,array,count, digit, size);
            flag =0;
        }     
    }
    if (flag){
        copy(&tempArray[0],&tempArray[size-1],array);
    }
    
    delete[] tempArray;
    delete[] count;
    for (int i = 0; i < size; i++) {
        cout << array[i].key << "\t" << storage[array[i].value] << "\n";
    }
    delete[] array;
    return 0;
}