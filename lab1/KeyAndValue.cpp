#include "KeyAndValue.hpp"




nKeyAndValue::TKeyAndValue::TKeyAndValue() : key(0), str() {}

nKeyAndValue::TKeyAndValue::TKeyAndValue(const unsigned long long & k,const std::string s):key(k),str(s){}

nKeyAndValue::TKeyAndValue::TKeyAndValue(const TKeyAndValue& mkv):key(mkv.key),str(mkv.str){}// конструктор копирования

nKeyAndValue::TKeyAndValue& nKeyAndValue::TKeyAndValue::operator=(const TKeyAndValue& el){
    this->key = el.key;
    this->str = el.str;
    return *this;
}//оператор присваивания 


nKeyAndValue::TDict::TDict(){
    capacity = 125000;
    size = 0;
    data = new TKeyAndValue[capacity];
}
nKeyAndValue::TDict::TDict(const int & n): size(0), capacity(n){
    data = new TKeyAndValue[n];
}
nKeyAndValue::TDict::~TDict(){
    delete [] data;
}

void nKeyAndValue::TDict::AddElement(const TKeyAndValue& el){
    if(capacity <= size){
        TKeyAndValue* temp = new TKeyAndValue[2 * capacity];
        std::copy(&data[0],&data[size],temp);
        std::swap(temp,data);
        capacity *= 2;
        delete [] temp;
    }
    data[size] = el;
    size += 1;
}
int nKeyAndValue::TDict::GetSize(){
    return size;
}