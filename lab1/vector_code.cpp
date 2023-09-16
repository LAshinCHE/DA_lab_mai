#include <iostream>


struct KeyValue
{
    unsigned long long key;
    char str[2049];
    
    KeyValue(){
        key =  0;
        str = '\0';
    }

    KeyValue(const KeyValue & k){
        this->key = k.key;
        this->str  = k.str;
    }// конструктор копирования 

    KeyValue(const unsigned long long & k, const std::string & s){
        key =  k;
        str = s;
    }

};


struct Dict{
    KeyValue* data;
    int size;
    int capacity;
    
    Dict(){
        size = 0;
        capacity = 4;
        data = new KeyValue[capacity];
    }

    Dict(int c){
        size = 0;
        capacity = c;
        data = new KeyValue[capacity];
    }
    Dict(const KeyValue k){
        size = 1;
        capacity = 4;
        data = new KeyValue[capacity];
        data->key = k.key;
        data->str = k.str;
    }

    void AddValue(const KeyValue & k){
        if (size >= capacity){
            KeyValue* temp = new KeyValue[2 * capacity];
            
            for (size_t i = 0; i < size; i++){
                temp[i] = data[i];
            }

            delete [] data;
            capacity *= 2;
            data = temp;
        }
        data[size] =  k;
        size += 1;
    }
    int GetSize(){
        return size;
    }
    ~Dict(){
        delete [] data;
    }
};


unsigned long long FindMaxKey(const Dict & d){
    unsigned long long maxKey = 0; 
    for (size_t i = 0; i < d.size; i++){
        if (d.data[i].key > maxKey)
            maxKey = d.data[i].key;
    }
    return maxKey;
}

void CountingSort(Dict& d, Dict& tempDict,int digit,int dictSize, int bitShift){
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
        tempDict.data[bitArray[dataByte] - 1].key = d.data[i].key;
        tempDict.data[bitArray[dataByte] -  1].str = d.data[i].str;
        bitArray[dataByte] -= 1;
    }

}

void RadixSort(Dict& d, const unsigned long long maxKey,int dictSize){
    Dict tempDict(dictSize); 
    for (int digit =  0 ; digit < 8 ; digit++){
        if ((digit & 1) == 0)
            CountingSort(d,tempDict,digit, dictSize,digit * 8);
        else
            CountingSort(tempDict,d,digit, dictSize,digit * 8);
    }
    
}

int main(){
    unsigned long long a;
    char value[2048]; 

    Dict d;
    KeyValue k;
    while (std::cin >> a >> value){
        k  = {a,a1};
        d.AddValue(k);
    }
    RadixSort(d);

    for(int i = 0; i < d.GetSize(); i++){
        std::cout << d.data[i].key << '\t' << d.data[i].str << '\n';
    }
    return 0;
}